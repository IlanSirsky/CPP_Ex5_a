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

        void printChart(std::ostream &os, const Node *node, std::vector<bool> flag, int depth = 0) const;

        size_t numOfNodes() const;

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

            void son(size_t idx)
            {
                this->prev = this->ptr_current;
                this->ptr_current = this->ptr_current->_children.at(idx);
            }

            void brother()
            {
                this->prev = this->ptr_current;
                // size_t d = 0;
                    for (auto it = this->ptr_current->_parent->_children.begin(); it != ptr_current->_parent->_children.end(); it++)
                    {
                        if ((*it) == this->ptr_current && has_brothers())
                        {
                            it++;
                            this->ptr_current = (*it);
                            break;
                        }
                    }
                    // d++;
                    parent();
                           // std::vector<ariel::Node *>::iterator it = std::find(temp.begin(), temp.end(), this->ptr_current);
                    auto find = std::find(this->ptr_current->_children.begin(), this->ptr_current->_children.end(), this->prev);
                    int next_index = find - this->ptr_current->_children.begin();
                    next_index++;
                    std:vector<int> next;
                    /*
                        NEED TO IMPLEMENT NEXT INDEX FOR EVERY DEPTH IN CURRENT SUBTREE
                        GOOD NIGHT
                        ZAIN BAAIN
                    */
                    int count = 1;
                    while(count != 0){
                        if(ptr_current->_children.size() <= next_index){
                            parent();
                            count++;
                        }
                        else{
                            this->ptr_current = this->ptr_current->_children.at((size_t)next_index);
                            count--;
                        }
                        next_index = std::find(this->ptr_current->_children.begin(), this->ptr_current->_children.end(), this->prev) - this->ptr_current->_children.begin();
                        next_index++;
                    }
                        
                    
                
            }

        public:
            iterator(Node *root, Node *curr, Order type) : _type(type), _root(root), ptr_current(curr)
            {
                this->last = this->_root;
                if (this->_root != nullptr)
                {
                    if (this->_type == Order::LEVELORDER)
                    {
                        {
                            while (!this->last->_children.empty())
                            {
                                this->last = this->last->_children.at(this->last->_children.size() - 1);
                            }
                        }
                    }
                }
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

            bool has_brothers()
            {
                std::vector<ariel::Node *> temp = this->ptr_current->_parent->_children;
                std::vector<ariel::Node *>::iterator it = std::find(temp.begin(), temp.end(), this->ptr_current);
                it++;
                return (it != temp.end());
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
                    {
                        if (!this->ptr_current->_parent)
                        {
                            // this->ptr_current = this->_root;
                            if(has_children()){
                                son(0);
                                break;
                            }
                            
                        }
                        ariel::Node *parentVector = this->ptr_current->_parent;
                        if (has_brothers())
                        {
                            brother();
                            break;
                        }
                        int depth = 0;
                        std::vector<size_t> current_index;
                        current_index.push_back(0);
                        while (this->ptr_current->_parent != nullptr)
                        {
                            depth++;
                            current_index.push_back(0);
                            
                            this->ptr_current = this->ptr_current->_parent;
                        }
                        for (size_t i = 0; i <= depth; i++)
                        {
                            if (has_children())
                            {
                                this->ptr_current = this->ptr_current->_children.at(current_index.at(i)++);
                            }
                            else// if(has_brothers())
                            {
                                brother();
                                i--;
                            }
                            // else{
                            //     parent();
                            //     current_index.at(i-1)++;
                            //     i--;
                            // }
                        }
                        break;
                    }
                    case Order::REVERSEORDER:
                    {
                        this->ptr_current = nullptr;
                        break;
                    }
                    case Order::PREORDER:
                    {
                        // if (this->prev == nullptr)
                        // {
                        //     if (this->has_children())
                        //     {
                        //         this->son();
                        //         break;
                        //     }
                        //     this->ptr_current = nullptr;
                        // }
                        // if (this->prev == this->ptr_current->_parent)
                        // {
                        //     if (this->has_children())
                        //     {
                        //         this->son();
                        //         break;
                        //     }
                        // }
                        this->ptr_current = nullptr;
                        break;
                    }
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
                Node *p = this->_root;
                while (!p->_children.empty())
                {
                    p = p->_children.at(0);
                }
                return iterator(this->_root, p, iterator::Order::REVERSEORDER);
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