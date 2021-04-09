/* this struct represents a train car */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "trains.h"
using namespace std;
// node constructors
Node::Node()
{
    next = NULL;
    prev = NULL;
}
Node::Node(unsigned int newCarValue)
{
    next = NULL;
    prev = NULL;
    data = newCarValue;
}
// train constructor
Train::Train()
{
    trainHead = NULL;
    trainValue = 0;
    carAmount = 0;
}

void Train::evalTrainVal()
{
    // this function evals the trains worth by iterating through the linked list until NULL is hit.
    // sum of cars position and cars value
    unsigned int tmpVal = 0;
    Node* currentCar = trainHead;
    unsigned int carPosition = 0;
    while(carPosition != carAmount)
    {
        carPosition += 1;
        int carValue = carPosition * currentCar->data;
        tmpVal += carValue;
        currentCar = currentCar->prev;
    }
    trainValue = tmpVal;
}
void Train::appendGivenCar(Node* newCar)
{
    /* this function will append a given train car to the FRONT*/
    // check if the trainHead is a null, otherwise add to front
    if (trainHead == NULL)
    {
        trainHead = newCar;
    }
    else
    {
        trainHead->next = newCar;
        newCar->next = NULL;
        newCar->prev = trainHead;
        trainHead = newCar;
    }
    this->carAmount += 1;
}
Node* Train::popFromFront()
{
    Node* popCar = trainHead;
    carAmount -= 1;
    // check if this is a singular car on the train
    if ((trainHead->prev == NULL) && (trainHead->next == NULL))
        return popCar;
    else
    {
        trainHead->prev->next = NULL;
        trainHead = trainHead->prev;
        return popCar;
    }
}
Node* Train::popFromEnd()
{
    Node* lastCar = trainHead;
    carAmount -= 1;
    // check if this is a singular car on the train
    while (lastCar->prev != NULL)
    {
        lastCar = lastCar->prev;
    }    
    // weve found the last car, we need to edit the car ahead to point to null
    if ((lastCar->prev == NULL) && (lastCar->next == NULL))
        return lastCar;
    else
    {
        lastCar->next->prev = NULL;
        return lastCar;
    }
}

unsigned int Train::printTrainNumAndValue(int trainNum)
{
    // print out the train number and its value
    cout << "\tTrain " << trainNum+1 << ": " ;
    // calculate the value of the train
    this->evalTrainVal();
    cout << "value: " << trainValue << "\n";
    return trainValue;
}
