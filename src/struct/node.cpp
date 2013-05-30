#include "node.h"
#include <stdio.h>

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
    TreePath newPath(path);
    bool found = false;

    std::list<Node*>::iterator it = children_.begin();

    while (it != children_.end() && !found)
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
        
        it++;
    }

    return NULL;
}

void Node::add(const std::string& path)
{
    TreePath newPath(path);

    Node* existentNode = getNode(newPath.folder);

    if (existentNode)
    {
        if (!newPath.rest.empty())
        {
            existentNode->add(newPath.rest);
        }
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

