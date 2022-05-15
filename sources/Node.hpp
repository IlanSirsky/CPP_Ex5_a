#pragma once

#include <string>
#include <vector>

// based on https://www.geeksforgeeks.org/insertion-in-n-ary-tree-in-given-order-and-level-order-traversal/

namespace ariel
{
    class Node
    {
    public:
        std::string _value;
        Node *_parent;
        std::vector<Node *> _children;

        void add_child(std::string val)
        {
            Node *newNode = new Node(std::move(val));
            this->_children.push_back(newNode);
            for (Node *node : this->_children)
            {
                if (node->_parent == nullptr)
                {
                    node->_parent = this;
                }
            }
        }

        Node() : _parent(nullptr) {}
        Node(std::string val) : _value(std::move(val)), _parent(nullptr) {}
    };
}