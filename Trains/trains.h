#ifndef TRAIN_H
#define TRAIN_H
class Node
{
    public:
        Node();
        Node(unsigned int newCarValue);
        friend class Train;
    private:
        int data;
        Node* next;
        Node* prev; 
};
class Train
{
    public:
        // Default constructor
        Train();
        Node* popFromFront();
        Node* popFromEnd();
        unsigned int printTrainNumAndValue(int trainNum);
        void appendGivenCar(Node* newCar);
        void evalTrainVal();
    private:
        Node* trainHead;
        unsigned int carAmount;
        unsigned int trainValue;
};
#endif
