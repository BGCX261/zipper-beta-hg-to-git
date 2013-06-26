#include "tree.h"
#include <stdio.h>

Tree::Tree(const std::string& zipName)
{
    INFO("%s", "Creating a tree.");
    root_ = new Node(zipName, NULL);
}

Tree::Tree(const Tree& orig)
{
    INFO("%s", "Creating a tree from another tree.");
    root_ = new Node(*(orig.getRoot()));
}

Tree::~Tree()
{
    INFO("%s", "Deleting tree.");
    delete root_;
}

Node* Tree::getNode(const std::string& path)
{
    INFO("Searching for a node in this path: %s", path.c_str());
    if (path.empty())
    {
        return NULL;
    }

    return root_->getNode(path);
}

void Tree::add(const std::string& path)
{
    INFO("Adding a node following this path: %s", path.c_str());
    if (path.empty())
    {
        return;
    }

    root_->add(path);
}

int Tree::countNodes()
{
    INFO("%s", "Counting nodes in the tree.");
    return root_->countChildren() + 1;
}

void Tree::traverse(int level, std::ostream& output)
{
    INFO("%s", "Printing the tree content.");
    root_->show(level, output);
}