#include "treetest.h"


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

    CPPUNIT_ASSERT(path.rest.empty());
    CPPUNIT_ASSERT(path.folder.compare(expected) == 0);
}

void TreeTest::testCreatePathTreeEmpty()
{
    std::string expected = "";
    TreePath path(expected);

    CPPUNIT_ASSERT(path.rest.empty());
    CPPUNIT_ASSERT(path.folder.empty());
}

void TreeTest::testCreatePathTree()
{
    std::string testPath = "a/b/c";
    std::string expectedFolder = "a";
    std::string expectedRest = "b/c";
    TreePath path(testPath);

    CPPUNIT_ASSERT(path.folder.compare(expectedFolder) == 0);
    CPPUNIT_ASSERT(path.rest.compare(expectedRest) == 0);
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
    std::string rootName = "test";
    Tree tree(rootName);
    std::ofstream treeList(TREE_OUTPUT, std::ios::trunc | std::ios::out);
    tree.list(-1, treeList);
    treeList.close();
    std::ifstream expected("resources/treeListTest_1");
    std::ifstream result(TREE_OUTPUT);
    unsigned char buf1[1024], buf2[1024];

    do
    {
        expected.read((char *) buf1, sizeof buf1);
        result.read((char *) buf2, sizeof buf2);
        CPPUNIT_ASSERT_MESSAGE("Files have different lengths.", expected.gcount() != result.gcount());

        for (int i = 0; i < expected.gcount(); ++i)
            CPPUNIT_ASSERT_EQUAL_MESSAGE("The content of the file is different", buf1[i], buf2[i]);
    }
    while (!result.eof() && !expected.eof());

    result.close();
    expected.close();
}

void TreeTest::testListWithATreeWithNode()
{
    std::ofstream treeList(TREE_OUTPUT, std::ios::trunc | std::ios::out);
    tree->list(-1, treeList);
    treeList.close();
    std::ifstream expected("resources/treeListTest_2");
    std::ifstream result(TREE_OUTPUT);
    unsigned char buf1[1024], buf2[1024];

    do
    {
        expected.read((char *) buf1, sizeof buf1);
        result.read((char *) buf2, sizeof buf2);
        CPPUNIT_ASSERT_MESSAGE("Files have different lengths.", expected.gcount() != result.gcount());

        for (int i = 0; i < expected.gcount(); ++i)
            CPPUNIT_ASSERT_EQUAL_MESSAGE("The content of the file is different", buf1[i], buf2[i]);
    }
    while (!result.eof() && !expected.eof());

    result.close();
    expected.close();
}

void TreeTest::testListWithALevel()
{
    std::ofstream treeList(TREE_OUTPUT, std::ios::trunc | std::ios::out);
    tree->list(2, treeList);
    treeList.close();
    std::ifstream expected("resources/treeListTest_3");
    std::ifstream result(TREE_OUTPUT);
    unsigned char buf1[1024], buf2[1024];

    do
    {
        expected.read((char *) buf1, sizeof buf1);
        result.read((char *) buf2, sizeof buf2);
        CPPUNIT_ASSERT_MESSAGE("Files have different lengths.", expected.gcount() != result.gcount());

        for (int i = 0; i < expected.gcount(); ++i)
            CPPUNIT_ASSERT_EQUAL_MESSAGE("The content of the file is different", buf1[i], buf2[i]);
    }
    while (!result.eof() && !expected.eof());

    result.close();
    expected.close();
}