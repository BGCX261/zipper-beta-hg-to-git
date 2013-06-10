#include "tree.h"
#include <stdio.h>

Tree::Tree(const std::string& zipName)
{
    root_ = new Node(zipName, NULL);
}

Tree::Tree(const Tree& orig)
{
    root_ = new Node(*(orig.getRoot()));
}

Tree::~Tree()
{
    delete root_;
}

Node* Tree::getNode(const std::string& path)
{
    if (path.empty())
    {
        return NULL;
    }

    return root_->getNode(path);
}

void Tree::add(const std::string& path)
{
    if (path.empty())
    {
        return;
    }

    root_->add(path);
}

int Tree::countNodes()
{
    return root_->countChildren() + 1;
}

void Tree::list(int level, std::ostream& output)
{
    root_->show(level, output);
}