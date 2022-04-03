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

TEST(test_size_empty)
{
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.size(), 0);
}

TEST(template_check)
{
    BinarySearchTree<string> tree;
    tree.insert("alpha");
    tree.insert("beta");
    tree.insert("charlie");
    cout << *tree.max_element() << endl;
    ASSERT_EQUAL(*tree.max_element(), "charlie");
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

TEST(test_height_empty)
{
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.height(), 0);
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

TEST(copy_nodes_empty)
{
    BinarySearchTree<int> tree;
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

TEST(find_node_empty)
{
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.find(2) == tree.end());
}

TEST(min_element_of_tree)
{
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    tree.insert(1);
    ASSERT_EQUAL(*tree.min_element(), 1); 
}

TEST(min_element_empty)
{
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.min_element(), tree.end());
}

TEST(min_element_only_one)
{
    BinarySearchTree<int> tree;
    tree.insert(4);
    ASSERT_EQUAL(*tree.min_element(), 4);
}

TEST(max_element_of_tree)
{
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    tree.insert(1);
    ASSERT_EQUAL(*tree.max_element(), 10);
}

TEST(max_element_empty)
{
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.max_element(), tree.end());
}

TEST(max_element_only_one)
{
    BinarySearchTree<int> tree;
    tree.insert(4);
    ASSERT_EQUAL(*tree.max_element(), 4);
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
    cout << tree.to_string() << endl;
    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(check_sorting_invariant_true)
{
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    tree.insert(1);
    ASSERT_TRUE(tree.check_sorting_invariant());
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

TEST(traverse_inorder_empty)
{
    BinarySearchTree<int> tree;
    ostringstream output;
    tree.traverse_inorder(output);
    ostringstream correct_output;
    correct_output << "";
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

TEST(traverse_preorder_empty)
{
    BinarySearchTree<int> tree;
    ostringstream output;
    tree.traverse_preorder(output);
    ostringstream correct_output;
    correct_output << "";
    ASSERT_EQUAL(output.str(), correct_output.str());
}

TEST(min_greater_than)
{
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    tree.insert(1);
    ASSERT_EQUAL(tree.find(4), tree.min_greater_than(3));
}

TEST(min_greater_than_equal)
{
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    tree.insert(1);
    ASSERT_EQUAL(tree.find(5), tree.min_greater_than(4));
}

TEST(min_greater_than_empty)
{
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.min_greater_than(3), tree.end());
}

TEST(min_greater_than_not_found)
{
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    tree.insert(1);
    ASSERT_EQUAL(tree.min_greater_than(11), tree.end());
}

TEST_MAIN()
