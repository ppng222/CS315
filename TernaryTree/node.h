#include <string>
using namespace std;
#ifndef NODE_H
#define NODE_H
class Node
{
    public:
        Node();
        Node(int a);
        Node(int a, int b);
        void insert(int p);
        string traverse(bool isRoot);
    private:
        int a,b;
        Node* left;
        Node* mid;
        Node* right;
};
#endif
