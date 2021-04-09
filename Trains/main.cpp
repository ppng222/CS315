/* TRAINS PROGRAM BY PHONG NGUYEN
   linkblue: ppng222
   CS315 2021
*/   

#include <iostream>
#include "trains.h"
using namespace std;

// function implementations
unsigned int rngGenerator(unsigned int n)
{
    // this function creates a randomly generated number in a specific range
    unsigned int randomValue;
    cin >> randomValue;
    return randomValue % n;
}

int simulateTrain(unsigned int turnNum, Train trainArray[], int n, int c, int t)
{
    /* this function simulates a train switching station according to the program documentation */

    // declare the required variables needed and grab the trains using the random number generator function
    Node* donorCar;
    unsigned int trainOneIndex = rngGenerator(n);
    unsigned int frontOrBack = rngGenerator(2);
    unsigned int trainTwoIndex = rngGenerator(n);
    Train* trainOne = &trainArray[trainOneIndex];
    Train* trainTwo = &trainArray[trainTwoIndex];
    
    // print out the turn and which train does what
    // also pop the required car and store it into donorCar
    string direction = "";
    if (frontOrBack)
    {
        direction = "end";
        donorCar = trainOne->popFromEnd();
    }
    else
    {
        direction = "front";
        donorCar = trainOne->popFromFront();
    }
    cout << "Turn " << turnNum << ": train " << trainOneIndex+1 << " sends a car to train " << trainTwoIndex+1 <<", from " << direction << "\n";

    // append the donor car to trainTwo
    trainTwo->appendGivenCar(donorCar);

    // variables related to checking whether a train is empty or not
    int mvpTrainVal = 0;
    int mvpTrainNum = 0;
    bool trainBreakFlag = false;
    int emptyTrain = -1;

    // loop through all the trains
    //  print out the train number and calculate/display the value of the train
    for (int trainNum = 0; trainNum < n; trainNum++)
    {
        unsigned int trainValue = trainArray[trainNum].printTrainNumAndValue(trainNum);
        if (trainValue <= mvpTrainVal)
        {
            // if the current train has less value than the greatest one
            if (!trainValue){
                // if trainValue is 0, set the break flag and establish the empty train
                trainBreakFlag = true;
                emptyTrain = trainNum;  
            }
        }   
        else
        {
            // the current train is the greatest, set that train
            mvpTrainVal =  trainValue;
            mvpTrainNum = trainNum;
        }
    }
    if (trainBreakFlag)
    {
        // one train is empty and we need to exit the program.
        cout << "Simulation is over, Train "<< emptyTrain+1 << " has no cars left.\n";
        exit(0);
    }
    return mvpTrainNum;
}
int main (int argc, char** argv)
{
    int returnValue; // most valued train when simulateTrain is run

    if (argc != 4)
    {
        // only run if the terminal arguments are not correct
        cout << "Usage: " << argv[0] << " numTrains numCars numSteps\n";
        return 1;
    }
    // cmd args are sent in as chars so we have to convert them to integers
    int n = stoi(argv[1]);
    int c = stoi(argv[2]);
    int t = stoi(argv[3]);

    /* hard code debug so i can test in vscode 
    int n = 5;
    int c = 6;
    int t = 1000;
    */

    if (n <= 0 || c <= 0 || t < 0)
    {
        // check to make sure the given parameters are within proper range
        cout << "The number of trains and cars have to be positive\nThe number of turns must be greater than 0.\n";
        return -1;
    }

    // establish the train array here
    Train trainArray[n];
    for (int train = 0; train < n; train++)
    {
        for (int car = c; car > 0; car--)
        {
            // create cars for each train
            Node* newCar = new Node(car);
            trainArray[train].appendGivenCar(newCar);
        }
        // evaluate the trains value at the end
        trainArray[train].evalTrainVal();
    }
    for (int i = 1; i <= t; i++)
        // simulate the switching station t times.
        returnValue = simulateTrain(i,trainArray,n,c,t);
    // ran out of turns, print out most valued train
    cout << "No more turns. Train " << returnValue+1 << " has the highest value.\n";
    return 0;
}
