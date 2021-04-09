/*
    HEADER FILE FOR MULTIPLE CLASSES AND EXTRA FUNCTIONS REQUIRED
    Author: Phong Nguyen
*/
#include <vector>
using namespace std;



#ifndef POINT_H
#define POINT_H
class Point
{
    public:
        Point();
        Point(int dimension);
        int &operator[](int i);
        friend ostream& operator<<(ostream &out, const Point& pointData);
        int insertIntoPoint(int newData);
        int size();
        int getDimension();
    private:
        int d;
        vector<int> data;
};
#endif

#ifndef NODE_H
#define NODE_H
class Node
{
    public:
        Node();
        Node(int level);
        Node(int level, vector<Point> pointData);
        void createFromList(int level, int splitDimension, vector<Point> newData);
        void probeData(int d, int splitstart, Point probeData);
    private:
        int l, splitD;
        vector<Point> data;
        Node* left;
        Node* right;
};
#endif

#ifndef XTRA_H
#define XTRA_H

int partition(vector<Point>& pointList, vector<int>& indiceList, int low, int high, int dimension);
int quickSelect(vector<Point>& pointList, int left, int right, int k, int dimension);
int kSmallest(vector<Point> pointList, int k, int d);
int kdVectorRange(vector<Point> pointList, int d);

#endif