#include "sources/OrgChart.hpp"
#include "doctest.h"

using namespace std;
using namespace ariel;

TEST_CASE("TEST ITERATORS1")
{
    vector<string> expected_levelorder{"0", "1", "2", "3", "4", "5"};
    vector<string> expected_reverseorder{"4", "5", "1", "2", "3", "0"};
    vector<string> expected_preorder{"0", "1", "4", "2", "3", "5"};
    vector<string> res;

    OrgChart organization;
    organization.add_root("0")
      .add_sub("0", "1") 
      .add_sub("0", "2")   
      .add_sub("0", "3")        
      .add_sub("1", "4")
      .add_sub("3", "5");
    cout << organization << endl;

    for (auto i = organization.begin(); i != organization.end(); ++i)
    {
        res.push_back(*i);
    }
    for (size_t i = 0; i < res.size(); i++)
    {
        CHECK_EQ(res.at(i), expected_levelorder.at(i));
    }
    res.clear();

    for (auto i : organization)
    {
        res.push_back(i);
    }
    for (size_t i = 0; i < res.size(); i++)
    {
        CHECK_EQ(res.at(i), expected_levelorder.at(i));
    }
    res.clear();

    for (auto i = organization.begin_level_order(); i != organization.end_level_order(); ++i)
    {
        res.push_back(*i);
    }
    for (size_t i = 0; i < res.size(); i++)
    {
        CHECK_EQ(res.at(i), expected_levelorder.at(i));
    }
    res.clear();

    for (auto i = organization.begin_reverse_order(); i != organization.reverse_order(); ++i)
    {
        res.push_back(*i);
    }
    for (size_t i = 0; i < res.size(); i++)
    {
        CHECK_EQ(res.at(i), expected_reverseorder.at(i));
    }
    res.clear();

    for (auto i = organization.begin_preorder(); i != organization.end_preorder(); ++i)
    {
        res.push_back(*i);
    }
    for (size_t i = 0; i < res.size(); i++)
    {
        CHECK_EQ(res.at(i), expected_preorder.at(i));
    }
}

TEST_CASE("TEST ITERATORS2")
{
    vector<string> expected_levelorder{"Managing Director", "Sales Manager", "Quality Commitee", "Production Manager", "EPCs", "End User" ,
                                         "Production Office" , "Manufacturing Workshop" , "Occupational Hazards"};
    vector<string> expected_reverseorder{"EPCs", "End User", "Production Office" , "Manufacturing Workshop" , "Occupational Hazards",
                                         "Sales Manager", "Quality Commitee", "Production Manager", "Managing Director"};
    vector<string> expected_preorder{"Managing Director", "Sales Manager", "EPCs", "End User", "Quality Commitee", "Production Manager",
                                         "Production Office" , "Manufacturing Workshop" , "Occupational Hazards"};
    vector<string> res;

    OrgChart organization;
    organization.add_root("Managing Director")
      .add_sub("Managing Director", "Sales Manager") 
      .add_sub("Managing Director", "Quality Commitee")   
      .add_sub("Managing Director", "Production Manager")        
      .add_sub("Sales Manager", "EPCs")
      .add_sub("Sales Manager", "End User")
      .add_sub("Production Manager", "Production Office")
      .add_sub("Production Manager", "Manufacturing Workshop")
      .add_sub("Production Manager", "Occupational Hazards");
    cout << organization << endl;
    
    for (auto i = organization.begin(); i != organization.end(); ++i)
    {
        res.push_back(*i);
    }
    for (size_t i = 0; i < res.size(); i++)
    {
        CHECK_EQ(res.at(i), expected_levelorder.at(i));
    }
    res.clear();

    for (auto i : organization)
    {
        res.push_back(i);
    }
    for (size_t i = 0; i < res.size(); i++)
    {
        CHECK_EQ(res.at(i), expected_levelorder.at(i));
    }
    res.clear();

    for (auto i = organization.begin_level_order(); i != organization.end_level_order(); ++i)
    {
        res.push_back(*i);
    }
    for (size_t i = 0; i < res.size(); i++)
    {
        CHECK_EQ(res.at(i), expected_levelorder.at(i));
    }
    res.clear();

    for (auto i = organization.begin_reverse_order(); i != organization.reverse_order(); ++i)
    {
        res.push_back(*i);
    }
    for (size_t i = 0; i < res.size(); i++)
    {
        CHECK_EQ(res.at(i), expected_reverseorder.at(i));
    }
    res.clear();

    for (auto i = organization.begin_preorder(); i != organization.end_preorder(); ++i)
    {
        res.push_back(*i);
    }
    for (size_t i = 0; i < res.size(); i++)
    {
        CHECK_EQ(res.at(i), expected_preorder.at(i));
    }
}


TEST_CASE("EXCEPTIONS")
{
    OrgChart organization;
    organization.add_root("0")
      .add_sub("0", "1") 
      .add_sub("0", "2")   
      .add_sub("0", "3")        
      .add_sub("1", "4")
      .add_sub("3", "5");

    CHECK_THROWS(organization.add_sub("8", "7"));
    CHECK_THROWS(organization.add_sub("15", "8"));
    CHECK_NOTHROW(organization.add_root("10"));
    CHECK_NOTHROW(organization.add_sub("4", "8"));
    CHECK_THROWS(organization.add_sub("0", "9"));
    CHECK_NOTHROW(organization.add_sub("10", "9"));
    CHECK_NOTHROW(organization.add_sub("9","11"));
}

TEST_CASE("Changes")
{
    vector<string> expected_levelorder{"0", "1", "2", "3", "4", "5"};
    vector<string> expected_reverseorder{"4", "5", "1", "2", "3", "0"};
    vector<string> expected_preorder{"8", "1", "4", "2", "3", "5"};
    vector<string> res;

    OrgChart organization;
    organization.add_root("0")
      .add_sub("0", "1") 
      .add_sub("0", "2")   
      .add_sub("0", "3")        
      .add_sub("1", "4")
      .add_sub("3", "5");
    
    organization.add_root("8");
    expected_levelorder.at(0) = "8";
    expected_reverseorder.at(5) = "8";
    expected_preorder.at(0) = "8";
    cout << organization << endl;

    for (auto i = organization.begin(); i != organization.end(); ++i)
    {
        res.push_back(*i);
    }
    for (size_t i = 0; i < res.size(); i++)
    {
        CHECK_EQ(res.at(i), expected_levelorder.at(i));
    }
    res.clear();

    for (auto i : organization)
    {
        res.push_back(i);
    }
    for (size_t i = 0; i < res.size(); i++)
    {
        CHECK_EQ(res.at(i), expected_levelorder.at(i));
    }
    res.clear();

    for (auto i = organization.begin_level_order(); i != organization.end_level_order(); ++i)
    {
        res.push_back(*i);
    }
    for (size_t i = 0; i < res.size(); i++)
    {
        CHECK_EQ(res.at(i), expected_levelorder.at(i));
    }
    res.clear();

    for (auto i = organization.begin_reverse_order(); i != organization.reverse_order(); ++i)
    {
        res.push_back(*i);
    }
    for (size_t i = 0; i < res.size(); i++)
    {
        CHECK_EQ(res.at(i), expected_reverseorder.at(i));
    }
    res.clear();

    organization.add_sub("3", "10");
    expected_preorder.push_back("10");

    for (auto i = organization.begin_preorder(); i != organization.end_preorder(); ++i)
    {
        res.push_back(*i);
    }
    for (size_t i = 0; i < res.size(); i++)
    {
        CHECK_EQ(res.at(i), expected_preorder.at(i));
    }
}



