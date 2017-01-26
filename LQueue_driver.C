/*---------------------------------------------------------------------
 Driver program to test the Queue class.
 ----------------------------------------------------------------------*/

#include <iostream>
#include "LQueue.h"
#include <array>
#include <stdlib.h>
#include <time.h>
using namespace std;

void startRunway(Queue & queue, string queueType, int currTime, int & startTime, bool & runwayInUse, int & sumTime, string message);

void endRunway(Queue & queue, string message, string queueType, bool & runwayInUse);

void enqueue(Queue & queue, int & planeNum, string queueType, int currTime, int & totalPlanes, int & maxSize);

double getAvg(int sumTimes, int numberOfPlanes);

void print(Queue q)
{ q.display(cout); }

int main(void)
{
    srand((int) time(NULL));
    cout << "Enter:" << endl;
    
    int landingTime;
    cout << "Time for a plane to land (in minutes): ";
    cin >> landingTime;
    
    int takeoffTime;
    cout << "Time for a plane to takeoff (in minutes): ";
    cin >> takeoffTime;
    
    int landingRate;
    cout << "Landing rate (planes per hour): ";
    cin >> landingRate;
    
    int takeoffRate;
    cout << "Takeoff Rate (planes per hour): ";
    cin >> takeoffRate;
    
    int tornadoRate;
    cout << "Rate of merges (per hour): ";
    cin >> tornadoRate;
    
    int simLength;
    cout << "How long to run the simulation (in minutes): ";
    cin >> simLength;
    
    Queue landingQueueA, landingQueueB;
    Queue takeoffQueueA, takeoffQueueB;
    
    int sumLandingTimesA = 0, sumLandingTimesB = 0;
    int sumTakeoffTimesA = 0, sumTakeoffTimesB = 0;
    int totalLandingPlanesA = 0, totalLandingPlanesB = 0;
    int totalTakeoffPlanesA = 0, totalTakeoffPlanesB = 0;
    
    int planeNum = 1000;
    int maxTakeoffSizeA = 0, maxTakeoffSizeB = 0;
    int maxLandingSizeA = 0, maxLandingSizeB = 0;
    int takeoffStartTimeA= -1-takeoffTime, takeoffStartTimeB = -1-takeoffTime;
    int landingStartTimeA= -1-landingTime, landingStartTimeB = -1-landingTime;
    
    int currTime = 0;
    bool runwayInUseA = false, runwayInUseB = false;
    bool tornadoTrigger = false;
    
    while(true){
        int randLand;
        int randTakeoff;
        int randTornado;
        cout << "Time = " << currTime << endl;
        
        if(currTime == simLength){
            cout << '\t'<< "No new takeoffs or landings will be generated" << endl;
        }
        
        // generate new takeoffs/landings
        if(currTime < simLength){
            randTornado = rand()%60;
            randLand = rand() % 60;
            randTakeoff = rand() % 60;
            
            if(randTornado < tornadoRate){
                tornadoTrigger = true;
                if(randTornado % 2){
                    landingQueueA.merge_two_queues(landingQueueA, landingQueueB);
                    takeoffQueueA.merge_two_queues(takeoffQueueA, takeoffQueueB);
                    cout << '\t'<< "TORNADO WARNING: Runway B out of service. " << endl;
                    runwayInUseB = false;
                }
                else{
                    landingQueueB.merge_two_queues(landingQueueB, landingQueueA);
                    takeoffQueueB.merge_two_queues(takeoffQueueB, takeoffQueueA);
                    cout << '\t'<< "TORNADO WARNING: Runway A out of service. " << endl;
                    runwayInUseA = false;
                }
            }
            
            if(randLand < landingRate){
                cout << '\t'<< "Plane " << planeNum << " wants to land; added to landing queue;";
                
                //if there are fewer planes in A, enqueue to runway A
                if(landingQueueA.size() < landingQueueB.size()){
                    enqueue(landingQueueA, planeNum, "A", currTime, totalLandingPlanesA, maxLandingSizeA);
                }
                else{
                    enqueue(landingQueueB, planeNum, "B", currTime, totalLandingPlanesB, maxLandingSizeB);
                    
                }
            }
            
            if(randTakeoff < takeoffRate){
                cout << '\t'<< "Plane " << planeNum << " wants to takeoff; added to takeoff queue;";
                
                //if there are fewer planes in A, enqueue to runway A
                if(takeoffQueueA.size() < takeoffQueueB.size()){
                    enqueue(takeoffQueueA, planeNum, "A", currTime, totalTakeoffPlanesA, maxTakeoffSizeA);
                }
                else{
                    enqueue(takeoffQueueB, planeNum, "B", currTime, totalTakeoffPlanesB, maxTakeoffSizeB);
                }
            }
        }
        
        // if the runway A is not in use
        if(!runwayInUseA){
            if(!takeoffQueueA.empty() && landingQueueA.empty()){
                startRunway(takeoffQueueA, "A", currTime, takeoffStartTimeA, runwayInUseA, sumTakeoffTimesA, "Taking off");
            }
            else if(!landingQueueA.empty()){
                startRunway(landingQueueA, "A", currTime, landingStartTimeA, runwayInUseA, sumLandingTimesA, "Landing");
            }
        }
        // if the runway is being used
        else{
            if((currTime-takeoffStartTimeA) == takeoffTime && !takeoffQueueA.empty()){
                endRunway(takeoffQueueA, "Takeoff ", "A", runwayInUseA);
            }
            else if((currTime-landingStartTimeA) == landingTime && !landingQueueA.empty()){
                endRunway(landingQueueA, "Landing ", "A", runwayInUseA);
            }
        }
        
        // if the runway B is not in use
        if(!runwayInUseB){
            if(!takeoffQueueB.empty() && landingQueueB.empty()){
                startRunway(takeoffQueueB, "B", currTime, takeoffStartTimeB, runwayInUseB, sumTakeoffTimesB, "Taking off");
            }
            
            else if(!landingQueueB.empty()){
                startRunway(landingQueueB, "B", currTime, landingStartTimeB, runwayInUseB, sumLandingTimesB, "Landing");
            }
        }
        else{
            if((currTime-takeoffStartTimeB) == takeoffTime && !takeoffQueueB.empty()){
                endRunway(takeoffQueueB, "Takeoff ", "B", runwayInUseB);
            }
            else if((currTime-landingStartTimeB) == landingTime && !landingQueueB.empty()){
                endRunway(landingQueueB, "Landing ", "B", runwayInUseB);
            }
        }
        
        
        // check whether simulation ended
        if((currTime > simLength) && landingQueueA.empty() && takeoffQueueA.empty()){
            cout << "End of program." << endl;
            break;
        }
        
        currTime++;
    }
    
    //stats
    cout << "STATISTICS A" << endl;
    cout << "Maximum number of planes in landing queue was: " << maxLandingSizeA << endl;
    cout << "Average minutes spent waiting to land: " << getAvg(sumLandingTimesA, totalLandingPlanesA) << endl;
    cout << "Maximum number of planes in takeoff queue was: " << maxTakeoffSizeA << endl;
    cout << "Average minutes spent waiting to takeoff: " << getAvg(sumTakeoffTimesA, totalTakeoffPlanesA) << endl;
    
    cout << "STATISTICS B" << endl;
    cout << "Maximum number of planes in landing queue was: " << maxLandingSizeB << endl;
    cout << "Average minutes spent waiting to land: " << getAvg(sumLandingTimesB, totalLandingPlanesB) << endl;
    cout << "Maximum number of planes in takeoff queue was: " << maxTakeoffSizeB << endl;
    cout << "Average minutes spent waiting to takeoff: " << getAvg(sumTakeoffTimesB, totalTakeoffPlanesB) << endl;
    
    system("PAUSE");
    return 0;
}

void startRunway(Queue & queue, string queueType, int currTime, int & startTime, bool & runwayInUse, int & sumTime, string message)
{
    cout<< '\t'<< message << " from Queue " << queueType << " Plane " << queue.front() << endl;
    startTime = currTime;
    runwayInUse = true;
    
    //stats
    sumTime += currTime - queue.frontTime();
}

void endRunway(Queue & queue, string message, string queueType, bool & runwayInUse){
    queue.dequeue();
    cout << '\t'<<message << "complete; " << queue.size() << " in Queue " << queueType << endl;
    runwayInUse = false;
}

void enqueue(Queue & queue, int & planeNum, string queueType, int currTime, int & totalPlanes, int & maxSize){
    queue.enqueue(planeNum++, currTime);
    int sizeOfQueue = queue.size();
    cout << sizeOfQueue << " in Queue " << queueType  << endl;
    
    //stats
    totalPlanes++;
    
    if(sizeOfQueue > maxSize){
        maxSize = sizeOfQueue;
    }
}

double getAvg(int sumTimes, int numberOfPlanes){
    
    if(numberOfPlanes == 0){
        return 0;
    }
    
    return ((double) sumTimes)/numberOfPlanes;
}

