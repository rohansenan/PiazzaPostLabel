// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"

using namespace std;


TEST(test_size) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    tree.insert(1);
    ASSERT_EQUAL(tree.size(), 4);
}

TEST(test_height)
{
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    tree.insert(1);
    ASSERT_EQUAL(tree.height(), 3);
}

TEST(copy_nodes)
{
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    tree.insert(1);
    BinarySearchTree<int> treeCopy(tree);
    ASSERT_EQUAL(tree.to_string(), treeCopy.to_string());
}

TEST(find_node)
{
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    tree.insert(1);
    ASSERT_TRUE(tree.find(1) != tree.end());
}

TEST(find_node_not_found)
{
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    tree.insert(1);
    ASSERT_TRUE(tree.find(2) == tree.end());
}

TEST_MAIN()
