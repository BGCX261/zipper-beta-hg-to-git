#include "node.h"
#include <stdio.h>
#include <iostream>

Node::Node(const std::string& name, Node* parent) : name_(name), parent_(parent)
{
}

Node::Node(const Node& orig)
{
    name_ = orig.name_;
    parent_ = new Node(*(orig.parent_));
}

Node::~Node()
{   
    std::list<Node*>::iterator it = children_.begin();
    for (; it != children_.end(); it++){
        delete *it;
    }
    
    children_.clear();
}

Node* Node::getNode(const std::string& path)
{
    TreePath newPath(path);

    for (std::list<Node*>::iterator it = children_.begin(); it != children_.end(); it++)
    {
        Node* node = *it;
        if (node->name_.compare(newPath.currentNode) == 0)
        {
            return (newPath.areChildrenRemaining()) ? node : node->getNode(newPath.remainingChildren);
        }
    }

    return NULL;
}

void Node::add(const std::string& path)
{
    if (path.empty()) return;
    TreePath newPath(path);

    Node* existentNode = getNode(newPath.currentNode);

    if (existentNode)
    {
        existentNode->add(newPath.remainingChildren);
    }
    else
    {
        Node* node = new Node(newPath.currentNode, this);
        children_.push_back(node);
        node->add(newPath.remainingChildren);
    }
}

int Node::countChildren()
{
    int res = 0;

    for (std::list<Node*>::iterator it = children_.begin(); it != children_.end(); it++)
    {
        Node* node = *it;
        res += node->countChildren() + 1; // counts child's nodes and child itself
    }

    return res;
}

void Node::show(int level, std::ostream& output, int spaces)
{
    if(level == 0) return;
    if(level > 0) level--;

    int tabs = spaces;
    while (tabs--)
    {
        output << "  ";
    }

    output << name_ << std::endl;

    for (std::list<Node*>::iterator it = children_.begin(); it != children_.end(); it++)
    {
        Node* node = *it;
        node->show(level, output, spaces + 1);
    }
}