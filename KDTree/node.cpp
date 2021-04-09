/*
    MULTIPLE CLASS IMPLEMENTATIONS ARE PRESENT IN THIS CPP INCLUDING:
    Node, Point, and Other Extraneous required Functions
    Author: Phong Nguyen
*/
#include <cstdlib>
#include <iostream>
#include "node.h"

using namespace std;

const int b = 10; // constant b for leaf nodes

/**********************************\
|          POINT CLASS             |
\**********************************/
Point::Point()
{
    this->d = 0;
}
Point::Point(int dimension)
{
    this->d = dimension;
}
int &Point::operator[](int i)
{
    // custom [] operator
    return this->data[i];
}
    
int Point::insertIntoPoint(int val)
{
    // this takes one value and pushes it into the point ONLY if
    // the point isn't full. It returns the size of the point, otherwise -1
    if ((int)this->data.size() < this->d)
    {
        this->data.push_back(val);
        return this->data.size();
    } else
        return -1;
}
int Point::getDimension()
{
    return this->d;
}

int Point::size()
{
    return (int)this->data.size();
}
ostream& operator<<(ostream &out, Point& pointData)
{
    // prints point data out to ostream
    for (int i = 0; i < pointData.size(); i++)
    {
        out << pointData[i] << " ";
    }
    return out;
}
/**********************************\
|           NODE CLASS             |
\**********************************/
Node::Node()
{
    this->l = 0;
    this->left = NULL;
    this->right = NULL;
}
Node::Node(int level)
{
    this->l = level;
    this->left = NULL;
    this->right = NULL;
}
Node::Node(int level, vector<Point> pointData)
{
    this->data = pointData;
    this->l = level;
    this->left = NULL;
    this->right = NULL;
}

void Node::createFromList(int level, int initialSplitDimension, vector<Point> newPointList) 
{
    // this function takes a vector list and splits into two lists based on a discriminate (median)
    this->l = level; // store the level into the node, used later on in other functions

    // we need to check if the data is smaller than the provided B threshold, if it is
    // this node becomes a leaf node that stores the data
    if (newPointList.size() <= b)
    {
        this->data = newPointList;
        return;
    }
    
    // we find the best dimension to split on based on the range here
    int pointListSize = (int)newPointList.size();
    int dimensions = newPointList[0].getDimension();
    int bestSplit = kdVectorRange(newPointList,dimensions); // find the dimension here
    this->splitD = bestSplit; // store the split dimension in the node so we can use it for probe later

    // we start to get the median here and split the list into two
    int medianLength = 0, medianIndex = 0, kthIndex = -1;
    vector<Point> leftList, rightList;

    // find the median length to plug in kSmallest value function
    medianLength = pointListSize/2;
    medianIndex = kSmallest(newPointList,medianLength,bestSplit);

    this->data.push_back(newPointList[medianIndex]); // store the kSmallest point into the node so we can use it later on for probes
    for (int i = 1; i < medianLength+1; i++)
    {
        // find all numbers SMALLER than the median
        kthIndex = kSmallest(newPointList,i,bestSplit);
        leftList.push_back(newPointList[kthIndex]);
    }
    for (int i = medianLength+1; i < pointListSize+1; i++)
    {
        // find all numbers LARGER than the median
        kthIndex = kSmallest(newPointList,i,bestSplit);
        rightList.push_back(newPointList[kthIndex]);
    }
    
    // recursive function call to create further kd nodes
    this->left = new Node();
    this->left->createFromList(level+1,bestSplit,leftList);
    this->right = new Node();
    this->right->createFromList(level+1,bestSplit,rightList);

}
void Node::probeData(int d, int splitStart, Point probeData)
{

    if (this->left == NULL && this->right == NULL)
    {
        // weve reached the bucket and we need to print it
        cout << "Probe " << probeData << " reaches bucket: " << this->data.size() << " elements\n";
        for (int i = 0; i < (int)this->data.size(); i++)
        {
            cout << this->data[i] << endl;
        }
        

    } else {
        // we havent reached the bucket, continue to go down the tree recursively
        if (probeData[this->splitD] <= this->data[0][this->splitD])
            this->left->probeData(d, splitStart, probeData);
        else if (this->data[0][this->splitD] < probeData[this->splitD])
            this->right->probeData(d, splitStart, probeData);
    }
}

/**********************************\
|          EXTRA FUNCS             |
\**********************************/

int partition(vector<Point>& pointList, vector<int>& indiceList, int low, int high, int dimension)
{
    // implementation of Lomuto's partitioning method
    int pivot = pointList[high][dimension];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (pointList[j][dimension] <= pivot)
        {
            i++;
            swap(pointList[i],pointList[j]);
            swap(indiceList[i],indiceList[j]);
        }
    }
    swap(pointList[i+1],pointList[high]);
    swap(indiceList[i+1],indiceList[high]);
    return (i+1);
}

int quickSelect(vector<Point>& pointList, int left, int right, int k, int dimension)
{
    // implementation of quickselect algorithm, but modified so it can work on a k-dimension of a vector 
    // we need to create an index list to keep track of where the median goes
    vector<int> origIndices;
    for (int i = 0; i < (int)pointList.size(); i++)
    {
        origIndices.push_back(i);
    }

    while (left <= right)
    {
        int pivotIndex = partition(pointList, origIndices, left, right, dimension);

        if (pivotIndex == k - 1)
            return origIndices[pivotIndex];
        else if (pivotIndex > k - 1)
            right = pivotIndex - 1;
        else
            left = pivotIndex + 1;
    }
    return -1;
}

int kSmallest(vector<Point> pointList, int k, int d)
{
    // wrapper for quickSelect, returns kSmallest value in k dimension of vector
    int pointLength = (int)pointList.size();
    int index = quickSelect(pointList, 0, pointLength - 1, k, d);
    return index;
}

int kdVectorRange(vector<Point> pointList, int dimensions)
{
    // iterates through all dimensions of a vector and returns the
    // index of the vector with the largest range
    int largestRange = 0, largestIndex = -1;
    for (int i = 0; i < dimensions; i++)
    {
        int smallest = pointList[kSmallest(pointList, 1, i)][i];
        int largest = pointList[kSmallest(pointList, pointList.size(), i)][i];
        int range = largest-smallest;
        if (range > largestRange)
        {
            largestRange = range;
            largestIndex = i;
        }

    }
    return largestIndex;
}