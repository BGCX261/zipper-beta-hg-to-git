/* 
 * File:   node.h
 * Author: Daniela Meneses
 * Description: File that will implement the node class for a tree structure.
 * 
 * Created on May 30, 2013, 5:11 PM
 */

#ifndef NODE_H
#define	NODE_H
#include <string>
#include <list>
#include <ostream>
#include <iostream>

/**
 * Class that represent a node in the tree structure.
 */
class Node
{
public:
    /**
     * Constructor that just set the values.
     * 
     * @param name Node name.
     * @param parent Node Parent.
     */
    Node(const std::string& name, Node* parent);

    Node(const Node& orig);
    virtual ~Node();

    /**
     * Return the node parent.
     * 
     * @return Node parent.
     */
    Node* getParent() const
    {
        return parent_;
    }

    /**
     * Return the children of this node.
     * 
     * @return Node children.
     */
    std::list<Node*> getChildren() const
    {
        return children_;
    }

    /**
     * Return the name of the node.
     * 
     * @return Node name.
     */
    std::string getName() const
    {
        return name_;
    }

    /**
     * Tells if the node is a root node.
     * 
     * @return True if the node is a root node of a tree, false in other case.
     */
    bool isRoot()
    {
        if (parent_ == NULL)
        {
            return true;
        }

        return false;
    }

    /**
     * Given a path, search in the current node or its children follow that path.
     * If the path doesn't exist as created nodes will return NULL.
     * 
     * @param path Given path to find the required node.
     * 
     * @return Node that the path indicates. If is not found returns NULL.
     */
    Node* getNode(const std::string& path);

    /**
     * Add nodes following the path inside this node. If the path already exist with created nodes 
     * don't do anything.
     * 
     * @param path Given path to add.
     */
    void add(const std::string& path);

    /**
     * Return the children count of this node.
     * 
     * @return Children count.
     */
    int countChildren();
    
    /**
     * Show the name of the node and its children hierarchically.
     * 
     * @param level Control what is the level of the children to know if will show the rest or not.
     * @param ouput Where the produced stream will be printed.
     * @param spaces Spaces for the indentation.
     */
    void show(int level, std::ostream& output = std::cout, int spaces = 0);

private:
    
    /**
     * Node name.
     */
    std::string name_;
    /**
     * Parent node.
     */
    Node* parent_;

    /**
     * Node children.
     */
    std::list<Node*> children_;
};

/**
 * Tree path structure that helps to parse a path.
 * Build two string one containing the first folder of the path and the second containing the rest 
 * of the path.
 * For example: Given a/b/c will build a structure with a folder "a" and the rest "b/c"
 */
struct TreePath
{
    std::string folder;
    std::string rest;

    TreePath(const std::string& path)
    {
        int index = path.find("/");

        if (index > 0)
        {
            folder = path.substr(0, index);
            rest = path.substr(index + 1);
        }
        else
        {
            folder = path;
        }
    }
};

#endif	/* NODE_H */

