#pragma once

#include "Node.hpp"
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <string>
#include <queue>
#include <vector>

namespace ariel
{
    class OrgChart
    {
    private:
        Node *_root = nullptr;

        Node *find(std::string val);

        Node *find(std::string val, Node *currentNode);

        void printChart(std::ostream &os, const std::string &prefix, const Node *node) const;

    public:
        OrgChart() : _root(nullptr) {}

        //~OrgChart();

        OrgChart &add_root(std::string val);

        OrgChart &add_sub(std::string parent, std::string sub);

        friend std::ostream &operator<<(std::ostream &os, const OrgChart &chart);

        class iterator
        {
        public:
            enum Order
            {
                LEVELORDER,
                REVERSEORDER,
                PREORDER
            };

        private:
            Node *ptr_current;
            Node *_root;
            Node *prev = nullptr;
            Node *last;
            Order _type; // 0 = LEVELORDER, 1 = REVERSEORDER, 2 = PREORDER

            void parent()
            {
                this->prev = this->ptr_current;
                this->ptr_current = this->ptr_current->_parent;
            }

            void son()
            {
                this->prev = this->ptr_current;
                this->ptr_current = this->ptr_current->_children.at(0);
            }

            void brother()
            {
                this->prev = this->ptr_current;
                for (auto it = this->ptr_current->_parent->_children.begin(); it != ptr_current->_parent->_children.end(); it++){
                    if ((*it) == this->ptr_current){
                        it++;
                        this->ptr_current = (*it);
                        break;
                    }
                }           
            }


        public:
            iterator(Node *root, Node *curr, Order type) : _type(type), _root(root), ptr_current(curr)
            {

            }

            iterator(Node *root, Order type) : _type(type), _root(root)
            {
                this->ptr_current = root;
                this->last = this->_root;
                if (this->_root != nullptr)
                {
                    if (this->_type == Order::REVERSEORDER || this->_type == Order::PREORDER)
                    {
                        while (!this->last->_children.empty())
                        {
                            this->last = this->last->_children.at(0);
                        }
                    }
                }
            }

            Node &Node()
            {
                return *(this->ptr_current);
            }

            bool has_children()
            {
                return !this->ptr_current->_children.empty();
            }

            bool has_brothers(){
                std::vector<ariel::Node *> temp = this->ptr_current->_parent->_children;
                std::vector<ariel::Node *>::iterator it = std::find(temp.begin(), temp.end() , this->ptr_current);
                it++;
                return (*it != nullptr);
            }

            std::string &operator*() const
            {
                return ptr_current->_value;
            }

            std::string *operator->() const
            {
                return &(ptr_current->_value);
            }

            bool operator==(const iterator &iter) const
            {
                return (ptr_current == iter.ptr_current);
            }

            bool operator!=(const iterator &iter) const
            {
                return (ptr_current != iter.ptr_current);
            }

            iterator &operator++()
            {
                if (this->ptr_current == this->last)
                {
                    this->ptr_current = nullptr;
                    return *this;
                }

                switch (this->_type)
                {
                case Order::LEVELORDER:
                    this->ptr_current = nullptr;
                    break;
                case Order::REVERSEORDER:
                    this->ptr_current = nullptr;
                    break;
                case Order::PREORDER:
                    this->ptr_current = nullptr;
                    break;
                }
                return *this;
            }

            iterator operator++(int)
            {
                iterator temp{this->_root, this->ptr_current, this->_type};
                this->operator++();
                return temp;
            }
        };

        iterator begin_level_order()
        {
            if (this->_root == nullptr)
            {
                return iterator(nullptr, iterator::Order::LEVELORDER);
            }
            return iterator(_root, _root, iterator::Order::LEVELORDER);
        }

        iterator end_level_order()
        {
            return iterator(nullptr, iterator::Order::LEVELORDER);
        }

        iterator begin_reverse_order()
        {
            if (this->_root == nullptr)
            {
                return iterator(nullptr, iterator::Order::REVERSEORDER);
            }
            //need to check if correct
            return iterator(_root, _root, iterator::Order::REVERSEORDER);
        }

        iterator reverse_order()
        {
            return iterator(nullptr, iterator::Order::REVERSEORDER);
        }

        iterator begin_preorder()
        {
            if (this->_root == nullptr)
            {
                return iterator(nullptr, iterator::Order::PREORDER);
            }
            return iterator(this->_root, iterator::Order::PREORDER);
        }
        iterator end_preorder()
        {
            return iterator(nullptr, iterator::Order::PREORDER);
        }

        iterator begin()
        {
            return this->begin_level_order();
        }
        iterator end()
        {
            return this->end_level_order();
        }
    };
}