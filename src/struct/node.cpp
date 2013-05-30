#include "node.h"
#include <stdio.h>

/**
 * Tree path structure that helps to parse a path.
 * Build two string one containing the first folder of the path and the second containing the rest 
 * of the path.
 * For example: Given a/b/c will build a struture with a folder "a" and the rest "b/c"
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

Node::Node(const std::string& name, Node* parent) : name_(name), parent_(parent)
{
}

Node::Node(const Node& orig)
{
}

Node::~Node()
{
}

Node* Node::getNode(const std::string& path)
{
    printf("getNode-Node: %s - ChildsCount: %d\n", name_.c_str(), children_.size());
    TreePath newPath(path);
    bool found = false;

    for (std::list<Node*>::iterator it = children_.begin(); it != children_.end() && !found; it++)
    {
        Node* node = *it;
        if (node->name_.compare(newPath.folder) == 0)
        {
            found = true;
            if (newPath.rest.empty())
            {
                return node;
            }
            else
            {
                return node->getNode(newPath.rest);
            }
        }
    }

    return NULL;
}

void Node::add(const std::string& path)
{
    printf("AddMethod-Node: %s - ChildsCount: %d\n", name_.c_str(), children_.size());
    TreePath newPath(path);

    Node* existentNode = getNode(newPath.folder);

    if (existentNode)
    {
        existentNode->add(newPath.rest);
    }
    else
    {
        Node* node = new Node(newPath.folder, this);
        children_.push_back(node);
        if (!newPath.rest.empty())
        {
            node->add(newPath.rest);
        }
    }
}

int Node::countChildren()
{
    int res = 0;

    for (std::list<Node*>::iterator it = children_.begin(); it != children_.end(); it++)
    {
        Node* node = *it;
        res += node->countChildren() + 1;
    }
    
    return res;
}

