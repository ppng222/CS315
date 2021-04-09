#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "node.h"

using namespace std;

const int INVALID = -256;

Node::Node()
{
    this->a = this->b = INVALID;

}
Node::Node(int x)
{
    this->a = x;
    this->b = INVALID;
    
}
void Node::insert(int p)
{
    // does this node even have data???
    if (a == INVALID && b == INVALID)
    {
        this->left = new Node();
        this->mid = new Node();
        this->right = new Node();
    }
    if (a == INVALID)
    {
        a = p;
    }
    // well a has something, but does b?
    else if (b == INVALID)
    {
        // insert based on the value comparison
        if (a < p)
            b = p;
        else    
        {
            // p is larger than the existing data, swap the two vars
            int tmp = a;
            a = p;
            b = tmp;
        }    
    }
    // both of the vars have data, add based on value
    else
    {
        // insert the data dependent on the value
        if (p <= a)
        {
            this->left->insert(p);
        }
        else if (a < p && p <= b)
        {
            this->mid->insert(p);
        }
        else if (b < p)
        {
            this->right->insert(p);
        }
    }
}
string Node::traverse(bool isRoot)
{
    // this function traverses through all branches using recursion
    string treeString;
    if (a == INVALID && b == INVALID)
        // the node is invalid and empty, just return the empty string
        return treeString;
    
    if (a != INVALID && b == INVALID)
    {
        // only a has data, we can print this separately
        treeString += "(" + to_string(a) + ") ";
        return treeString;
    }
    if (!isRoot)
        // check if this is a root element, if its not
        // add the open bracket
        treeString += "(";
    // go through each branch and add their strings to the main string
    // also print a and b
    treeString += left->traverse(false);
    treeString += to_string(a) + " ";
    treeString += mid->traverse(false);
    treeString += to_string(b) + " ";
    treeString += right->traverse(false);
    if (!isRoot)
    {
        // check if this is a root element, if its not
        // add the closing bracket, replacing the already existing space
        treeString.pop_back();
        treeString += ") ";
    }
    return treeString;
}
