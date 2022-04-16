#include "csvstream.h"
#include "unit_test_framework.h"
#include "BinarySearchTree.h"
#include <iostream>
#include <string>
#include "Map.h"

using namespace std;


TEST(test_empty)
{
    Map<string, int> words;
    ASSERT_TRUE(words.empty());
}

TEST(test_empty_false)
{
    Map<string, int> words;
    pair<string, int> word = {"hello", 1};
    words.insert(word); 
    ASSERT_FALSE(words.empty());
}

TEST(test_size)
{
    Map<string, int> words;
    pair<string, int> word1 = {"hello", 1};
    pair<string, int> word2 = {"and", 2};
    pair<string, int> word3 = {"tree", 3};
    words.insert(word1);
    words.insert(word2);
    words.insert(word3);
    ASSERT_EQUAL(words.size(), 3);
}

TEST(test_size_empty)
{
    map<string, int> words;
    ASSERT_EQUAL(words.size(), 0);
}

TEST(test_find)
{
    Map<string, int> words;
    pair<string, int> word1 = {"hello", 1};
    pair<string, int> word2 = {"and", 2};
    pair<string, int> word3 = {"tree", 3};
    words.insert(word1);
    words.insert(word2);
    words.insert(word3);
    ASSERT_TRUE(words.find("hello") != words.end());
    ASSERT_EQUAL((*words.find("hello")).first, "hello")
}

TEST(test_find_empty)
{
    Map<string, int> words;
    ASSERT_FALSE(words.find("hello") != words.end());
}

TEST(test_map_insert)
{
    Map<string, int> words;
    pair<string, int> word1 = {"hello", 1};
    pair<string, int> word2 = {"and", 2};
    pair<string, int> word3 = {"tree", 3};
    words.insert(word1);
    words.insert(word2);
    words.insert(word3);
    auto inserted = words.insert(word2);
    ASSERT_FALSE(inserted.second);
    ASSERT_TRUE(inserted.first != words.end());
    ASSERT_EQUAL(inserted.first, words.begin());
}


TEST_MAIN()