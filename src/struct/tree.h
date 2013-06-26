/* 
 * File:   tree.h
 * Author: Daniela Meneses
 * Description: File that will implement the tree class a directory tree.
 *
 * Created on May 30, 2013, 5:06 PM
 */

#ifndef TREE_H
#define	TREE_H
#include <string>
#include "node.h"
#include <ostream>
#include <iostream>
#include "../log/LoggerManager.h"

extern LoggerManager* g_logger;

/**
 * Tree structure implementation that will be used to manage directory hierarchy.
 */
class Tree
{
public:
    /**
     * Constructor that will create the root node with the given zip name.
     * 
     * @param zipName Name of the root file.
     */
    Tree(const std::string& zipName);
    
    Tree(const Tree& orig);
    virtual ~Tree();

    /**
     * Return the root node of the tree.
     * 
     * @return Root node of the tree.
     */
    Node* getRoot() const
    {
        return root_;
    }

    /**
     * Given a path, return a node in the tree that the path indicates. If the path doesn't exist
     * as created nodes will return NULL.
     * 
     * @param path Given path to find the required node.
     * 
     * @return Node that the path indicates. If is not found returns NULL.
     */
    Node* getNode(const std::string& path);
    
    /**
     * Add the necessary node that the path indicates.
     * For example: If the path is "a/b/c", the tree will create 3 nodes where 'a' will be parent node
     * of 'b' and b will be parent node of 'c'. 'c' will be a leaf node.
     * 
     * @param path Path that indicates the nodes that will be created.
     */
    void add(const std::string& path);
    
    /**
     * Count the nodes that the tree owns.
     * 
     * @return Tree node count.
     */
    int countNodes();
    
    /**
     * List the tree by levels.
     * 
     * @param level Tells until what tree level stop. If is -1 will show all the available tree levels.
     * @param output Where the stream will be printed.
     */
    void traverse(int level, std::ostream& output = std::cout);

private:
    /**
     * Root node of the tree.
     */
    Node* root_;
};

#endif	/* TREE_H */

