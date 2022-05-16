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

        bool hasBrothers() const
        {
            std::vector<Node *> temp = this->_parent->_children;
            std::vector<Node *>::iterator it = std::find(temp.begin(), temp.end(), this);
            it++;
            return (*it != nullptr);
        }

        void add_child(std::string val)
        {
            Node *newNode = new Node(std::move(val));
            newNode->_parent = this;
            this->_children.push_back(newNode);
        }

        // int find_index()
        // {
        //     std::vector<Node *> * v =  this->_parent->_children;
        //     auto it = find(v.begin(), v.end(), K);
        //     if (it != v.end())
        //     {
        //         int index = it - v.begin();
        //         return index;
        //     }
        //     return -1;
        // }

        Node() : _parent(nullptr) {}
        Node(std::string val) : _value(std::move(val)), _parent(nullptr) {}
    };
}