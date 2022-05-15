#include "OrgChart.hpp"

using namespace std;

namespace ariel
{

    Node *OrgChart::find(std::string val)
    {
        if (this->_root == nullptr)
        {
            throw std::invalid_argument("root is null");
        }
        return find(val, this->_root);
    }

    // based on https://stackoverflow.com/questions/20735708/how-to-get-an-element-in-n-ary-trees
    Node *OrgChart::find(std::string val, Node *currentNode)
    {
        if (currentNode == nullptr)
        {
            return nullptr;
        }
        if (currentNode->_value == val)
        {
            return currentNode;
        }
        for (Node *node : currentNode->_children)
        {
            Node *found = find(val, node);
            if (found != nullptr)
            {
                return found;
            }
        }
        return nullptr;
    }

    void OrgChart::printChart(std::ostream &os, const std::string &prefix, const Node *node) const
    {
    }

    // OrgChart::~OrgChart()
    // {
    //     std::queue<Node *> toRemove;
    //     for (auto it = this->begin_preorder(); it != this->end_preorder(); ++it)
    //     {
    //         toRemove.push(&it.Node());
    //     }
    //     while (!toRemove.empty())
    //     {
    //         delete toRemove.front();
    //         toRemove.pop();
    //     }
    // }

    OrgChart &OrgChart::add_root(string val)
    {
        if (this->_root == nullptr)
        {
            this->_root = new Node(val);
        }
        this->_root->_value = val;
        return *this;
    }

    OrgChart &OrgChart::add_sub(string parent, string sub)
    {
        Node *parentNode = find(parent);
        if (parentNode == nullptr)
        {
            throw std::invalid_argument("First value is not in the chart");
        }
        parentNode->add_child(sub);
        return *this;
    }

    std::ostream &operator<<(std::ostream &os, const OrgChart &chart)
    {
        os << chart._root->_value << std::endl;
        chart.printChart(os, "", chart._root);
        os << std::endl;
        return os;
    }

    

}