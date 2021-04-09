#include <iostream>
#include "node.h"
using namespace std;


/*
vscode debugging related
int arrayNum[] = {4, 6, 4, 18, 8, 2, 14, 7, 15, 5, 19, 12, 15, 5, 9, 0, 17, 2, 2, 19};
int len = sizeof(arrayNum)/4;
*/
int main(int argc, char* argv[])
{
    // check if a value number is being passed
    // no? quit the program
/* GRADER COMMENT
Great job !*/
    if (argc != 2)
    {
        cout << "USAGE: " << argv[0] << " NUMVALUES";
        return -1;
    }
    // initalize some values
    int loopLen = stoi(argv[1]);
    // create an empty tree
    Node* mainTree = new Node();
    string treeString;
    for (int i = 0; i < loopLen; i++)
    {
        // insert all values from randGen
        int insertVal;
        cin >> insertVal;
        mainTree->insert(insertVal);
    }
    treeString = mainTree->traverse(true);
    cout << treeString;
    return 0;
}
