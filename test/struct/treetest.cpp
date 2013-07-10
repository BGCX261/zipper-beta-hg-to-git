#include "treetest.h"

#include <sstream>
#include <stdlib.h>

CPPUNIT_TEST_SUITE_REGISTRATION(TreeTest);
#define TREE_COUNT 8
#define TREE_OUTPUT "treeListOutput"

TreeTest::TreeTest()
{
    tree = new Tree("test");
    tree->add("a/b");
    tree->add("a/e");
    tree->add("a/m");
    tree->add("a/b/c");
    tree->add("c/d");
}

TreeTest::~TreeTest()
{
    remove(TREE_OUTPUT);
}

void TreeTest::setUp()
{
}

void TreeTest::tearDown()
{
    delete tree;
}

void TreeTest::testGetNodeWithEmptyPath()
{
    Node* node = tree->getNode("");
    CPPUNIT_ASSERT_MESSAGE("The given node must be null.", NULL == node);
}

void TreeTest::testGetNodeWhenDoNotExist()
{
    Node* node = tree->getNode("a/c");
    CPPUNIT_ASSERT_MESSAGE("The node shouldn't exist.", NULL == node);
}

void TreeTest::testGetNodeWithChildren()
{
    int expectedChildren = 3;
    Node* node = tree->getNode("a");

    if (node)
    {
        int childrenCount = node->getChildren().size();
        CPPUNIT_ASSERT_EQUAL(expectedChildren, childrenCount);
    }
    else
    {
        CPPUNIT_FAIL("The returned node is null.");
    }
}

void TreeTest::testGetNodeWithoutChildren()
{
    int expectedChildren = 0;
    Node* node = tree->getNode("a/b/c");

    if (node)
    {
        int childrenCount = node->getChildren().size();
        CPPUNIT_ASSERT_EQUAL(expectedChildren, childrenCount);
    }
    else
    {
        CPPUNIT_FAIL("The returned node is null.");
    }
}

void TreeTest::testCreatePathTreeWithoutSlash()
{
    std::string expected = "test";
    TreePath path(expected);

    CPPUNIT_ASSERT(path.areChildrenRemaining());
    CPPUNIT_ASSERT(path.currentNode.compare(expected) == 0);
}

void TreeTest::testCreatePathTreeEmpty()
{
    std::string expected = "";
    TreePath path(expected);

    CPPUNIT_ASSERT(path.areChildrenRemaining());
    CPPUNIT_ASSERT(path.currentNode.empty());
}

void TreeTest::testCreatePathTree()
{
    std::string testPath = "a/b/c";
    std::string expectedFolder = "a";
    std::string expectedRest = "b/c";
    TreePath path(testPath);

    CPPUNIT_ASSERT(path.currentNode.compare(expectedFolder) == 0);
    CPPUNIT_ASSERT(path.remainingChildren.compare(expectedRest) == 0);
}

void TreeTest::testCreateTree()
{
    std::string rootName = "Test";
    Tree tree(rootName);
    CPPUNIT_ASSERT(tree.getRoot() != NULL);
    CPPUNIT_ASSERT(tree.getRoot()->getName().compare(rootName) == 0);
}

void TreeTest::testAddTheSameNode()
{
    tree->add("a/b/c");
    int result = tree->countNodes();
    CPPUNIT_ASSERT_EQUAL(TREE_COUNT, result);
}

void TreeTest::testAddWhenIsEmpty()
{
    Tree tree("TEST");
    tree.add("a");
    int countResult = tree.countNodes();
    int expected = 2;
    CPPUNIT_ASSERT_EQUAL(expected, countResult);
}

void TreeTest::testAddEmptyPath()
{
    tree->add("");
    int result = tree->countNodes();
    CPPUNIT_ASSERT_EQUAL(TREE_COUNT, result);
}

void TreeTest::testAddNodesUnderRoot()
{
    int countRootChildren = tree->getRoot()->getChildren().size();
    int expected = 2;
    CPPUNIT_ASSERT_EQUAL(expected, countRootChildren);
}

void TreeTest::testAddNodesUnderARootChild()
{
    int expectedChildren = 3;
    Node* node = tree->getNode("a");

    if (node)
    {
        int childrenCount = node->getChildren().size();
        CPPUNIT_ASSERT_EQUAL(expectedChildren, childrenCount);
    }
    else
    {
        CPPUNIT_FAIL("The returned node is null.");
    }
}

void TreeTest::testListWithAEmptyTree()
{
    Tree tree("test");
    std::ostringstream output;
    tree.traverse(-1, output);
    std::string result = output.str();
    std::string expected = readFileContent(5, "resources/treeListTest_1");

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Files have different lengths.", expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The content of the file is different", expected, result);
}

std::string readFileContent(int size, const char* filename)
{
    std::ifstream input(filename);
    char* buffer = new char[size];
    input.read(buffer, size);
    input.close();
    std::string res(buffer, size);
    delete[] buffer;
    return res;
}

void TreeTest::testListWithATreeWithNode()
{
    std::ostringstream output;
    tree->traverse(-1, output);
    std::string result = output.str();
    std::string expected = readFileContent(45, "resources/treeListTest_2");

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Files have different lengths.", expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The content of the file is different", expected, result);
}

void TreeTest::testListWithALevel()
{
    std::ostringstream output;
    tree->traverse(2, output);
    std::string result = output.str();
    std::string expected = readFileContent(13, "resources/treeListTest_3");

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Files have different lengths.", expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The content of the file is different", expected, result);
}