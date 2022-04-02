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

TEST(max_element)
{
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    tree.insert(1);
    BinarySearchTree<int>::Iterator maxIter = tree.max_element();
    ASSERT_EQUAL(*maxIter, 10);
}

TEST(check_sorting_invariant)
{
    BinarySearchTree<int> tree;
    tree.insert(10);
    BinarySearchTree<int>::Iterator iter = tree.begin();
    tree.insert(2);
    tree.insert(15);
    tree.insert(8);
    tree.insert(1);
    tree.insert(3);
    *iter = 5;
    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(traverse_inorder)
{
    BinarySearchTree<int> tree;
    tree.insert(6);
    tree.insert(10);
    tree.insert(4);
    tree.insert(1);
    tree.insert(5);
    tree.insert(11);
    tree.insert(9);
    ostringstream output;
    tree.traverse_inorder(output);
    ostringstream correct_output;
    correct_output << "1 4 5 6 9 10 11 ";
    ASSERT_EQUAL(output.str(), correct_output.str());
}

TEST(traverse_preorder)
{
    BinarySearchTree<int> tree;
    tree.insert(6);
    tree.insert(10);
    tree.insert(4);
    tree.insert(1);
    tree.insert(5);
    tree.insert(11);
    tree.insert(9);
    ostringstream output;
    tree.traverse_preorder(output);
    ostringstream correct_output;
    correct_output << "6 4 1 5 10 9 11 ";
    ASSERT_EQUAL(output.str(), correct_output.str());
}

TEST(min_greater_than)
{
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    tree.insert(1);
    BinarySearchTree<int>::Iterator correctIter = tree.find(4);
    BinarySearchTree<int>::Iterator iter = tree.min_greater_than(3);
    cout << *correctIter << endl;
    cout << *iter << endl;
    ASSERT_EQUAL(correctIter, iter);
}

TEST_MAIN()
