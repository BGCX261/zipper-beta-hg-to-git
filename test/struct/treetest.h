/*
 * File:   TreeTest.h
 * Author: Daniela Meneses
 * Description: Implement test for the tree structure.
 *
 * Created on May 30, 2013, 11:35:55 AM
 */

#ifndef TREETEST_H
#define	TREETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "struct/tree.h"

class TreeTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TreeTest);

    CPPUNIT_TEST(testGetNodeWithEmptyPath);
    CPPUNIT_TEST(testGetNodeWhenDoNotExist);
    CPPUNIT_TEST(testGetNodeWithChildren);
    CPPUNIT_TEST(testGetNodeWithoutChildren);
    CPPUNIT_TEST(testCreatePathTreeWithoutSlash);
    CPPUNIT_TEST(testCreatePathTreeEmpty);
    CPPUNIT_TEST(testCreatePathTree);
    CPPUNIT_TEST(testCreateTree);
    CPPUNIT_TEST(testAddTheSameNode);
    CPPUNIT_TEST(testAddWhenIsEmpty);
    CPPUNIT_TEST(testAddEmptyPath);
    CPPUNIT_TEST(testAddNodesUnderRoot);
    CPPUNIT_TEST(testAddNodesUnderARootChild);
    CPPUNIT_TEST(testListWithAEmptyTree);
    CPPUNIT_TEST(testListWithATreeWithNode);

    CPPUNIT_TEST_SUITE_END();

public:
    TreeTest();
    virtual ~TreeTest();
    void setUp();
    void tearDown();

private:
    void testGetNodeWithEmptyPath();
    void testGetNodeWhenDoNotExist();
    void testGetNodeWithChildren();
    void testGetNodeWithoutChildren();
    void testCreatePathTreeWithoutSlash();
    void testCreatePathTreeEmpty();
    void testCreatePathTree();
    void testCreateTree();
    void testAddTheSameNode();
    void testAddWhenIsEmpty();
    void testAddEmptyPath();
    void testAddNodesUnderRoot();
    void testAddNodesUnderARootChild();
    void testListWithAEmptyTree();
    void testListWithATreeWithNode();
    Tree* tree;
};

#endif	/* TREETEST_H */

