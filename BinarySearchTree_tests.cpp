// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"


TEST(test_size) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    ASSERT_EQUAL(tree.size(), 3);
}

TEST(test_height)
{
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    ASSERT_EQUAL(tree.height(), 2);
}

TEST_MAIN()
