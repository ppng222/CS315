/*
    KD-TREE PROGRAM
    Author: Phong Nguyen
*/

#include <iostream>

#include "node.h"

using namespace std;


int main(int argc, char **argv)
{
    // check and retreive cmd arguments
    if (argc != 4)
    {
        cout << "Usage: " << argv[0] << " dimensions pointCount probeCount\n";
        exit(1);
    }
    int k = stoi(argv[1]);
    if (k < 0)
    {
        cout << "Number of dimensions must not be negative\n";
        exit(1);
    }
    int n = stoi(argv[2]);
    if (n < 0)
    {
        cout << "Number of points must not be negative\n";
        exit(1);
    }
    int p = stoi(argv[3]);
    if (p < 0)
    {
        cout << "Number of probes must not be negative\n";
        exit(1);
    }

    // read all the ints into a vector
    vector<Point> offlineData;

    int newData;
    for (int i = 0; i < n; i++)
    {
        Point tmpPointData = Point(k);
        for (int j = 0; j < k; j++)
        {
            cin >> newData;
            tmpPointData.insertIntoPoint(newData);
        }
        offlineData.push_back(tmpPointData);

    }
    // find the first split dimension
    int splitDimension = kdVectorRange(offlineData,k);

    Node* root = new Node();
    root->createFromList(0,splitDimension,offlineData); // create the list from the offline data
    
    // probe p points of data into the list
    for (int i = 0; i < p; i++)
    {
        Point tmpPointData = Point(k);
        for (int j = 0; j < k; j++)
        {
            cin >> newData;
            tmpPointData.insertIntoPoint(newData);
        }
        root->probeData(k,splitDimension,tmpPointData);
    }




    
    return 0;
}