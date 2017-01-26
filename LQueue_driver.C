/*---------------------------------------------------------------------
 Driver program to test the Queue class.
 ----------------------------------------------------------------------*/
/*
#include <iostream>
#include "LQueue.h"
#include <array>
#include <stdlib.h>
#include <time.h>
using namespace std;


void print(Queue q)
{ q.display(cout); }

int main(void)
{
    srand((int) time(NULL));
    cout << "Enter:" << endl;
    
    int landingTime;
    cout << "Time for a plane to land (in minutes): ";
    cin >> landingTime;
    cout << endl;
    
    int takeoffTime;
    cout << "Time for a plane to takeoff (in minutes): ";
    cin >> takeoffTime;
    
    int landingRate;
    cout << "Landing rate (planes per hour): ";
    cin >> landingRate;
    
    int takeoffRate;
    cout << "Takeoff Rate (planes per hour): ";
    cin >> takeoffRate;
    
    int simLength;
    cout << "How long to run the simulation (in minutes): ";
    cin >> simLength;
    
    Queue landingQueue;
    Queue takeoffQueue;
    Queue landingEnqueuedTimesQueue;
    Queue takeoffEnqueuedTimesQueue;
    
    int sumLandingTimes = 0;
    int sumTakeoffTimes= 0;
    int totalLandingPlanes=0;
    int totalTakeoffPlanes=0;
    
    int planeNum = 1000;
    int maxTakeoffSize = 0;
    int maxLandingSize = 0;
    int takeoffStartTime = -1-takeoffTime;
    int landingStartTime = -1-landingTime;
    
    int currTime = 0;
    bool runwayInUse = false;
    while(true){
        int randLand;
        int randTakeoff;
        cout << "Time = " << currTime << endl;
        
        if(currTime == simLength){
            cout << "No new takeoffs or landings will be generated" << endl;
        }
        
        // generate new takeoffs/landings
        if(currTime < simLength){
            randLand = rand() % 60;
            randTakeoff = rand() % 60;
            
            if(randLand < landingRate){
                cout << "Plane " << planeNum << " wants to land; added to landing queue; ";
                landingQueue.enqueue(planeNum++);
                int sizeOfLandingQueue = landingQueue.size();
                
                if(sizeOfLandingQueue > maxLandingSize){
                    maxLandingSize = sizeOfLandingQueue;
                }
                
                cout << sizeOfLandingQueue << " in queue" << endl;
                
                //stats
                landingEnqueuedTimesQueue.enqueue(currTime);
                totalLandingPlanes++;
                
            }
            
            if(randTakeoff < takeoffRate){
                cout << "Plane " << planeNum << " wants to takeoff; added to takeoff queue; ";
                takeoffQueue.enqueue(planeNum++);
                int sizeOfTakeoffQueue = takeoffQueue.size();
                
                if(sizeOfTakeoffQueue > maxTakeoffSize){
                    maxTakeoffSize = sizeOfTakeoffQueue;
                }
                
                cout << takeoffQueue.size() << " in queue" << endl;
                
                //stats
                takeoffEnqueuedTimesQueue.enqueue(currTime);
                totalTakeoffPlanes++;
            }
        }
        
        // if the runway is not in use
        if(!runwayInUse){
            if(!takeoffQueue.empty() && landingQueue.empty()){
                cout<< "Taking off: Plane " << takeoffQueue.front() << endl;
                takeoffStartTime = currTime;
                runwayInUse = true;
                
                //stats
                sumTakeoffTimes += currTime - takeoffEnqueuedTimesQueue.front();
                takeoffEnqueuedTimesQueue.dequeue();
            }
            
            else if(!landingQueue.empty()){
                cout<< "Landing: Plane " << landingQueue.front() << endl;
                landingStartTime = currTime;
                runwayInUse = true;
                
                //stats
                sumLandingTimes += currTime - landingEnqueuedTimesQueue.front();
                landingEnqueuedTimesQueue.dequeue();
            }
        }
        
        // if the runway is being used
        else{
            if((currTime-takeoffStartTime) == takeoffTime){
                takeoffQueue.dequeue();
                cout << "Takeoff Complete; " << takeoffQueue.size() << " in queue" << endl;
                runwayInUse = false;
                
                
            }
            else if((currTime-landingStartTime) == landingTime){
                landingQueue.dequeue();
                cout << "Landing Complete; " << landingQueue.size() << " in queue" << endl;
                runwayInUse = false;
                
            }
        }
        
        // check whether simulation ended
        if((currTime > simLength) && landingQueue.empty() && takeoffQueue.empty()){
            cout << "End of program." << endl;
            break;
        }
        
        currTime++;
    }
    
    //stats
    int avgLandingTime = 0;
    int avgTakeofftime = 0;
    
    if(totalLandingPlanes != 0){
        avgLandingTime = sumLandingTimes/totalLandingPlanes;
    }
    if(totalTakeoffPlanes != 0){
        avgTakeofftime = sumTakeoffTimes/totalTakeoffPlanes;
    }
    
    cout << "STATISTICS" << endl;
    cout << "Maximum number of planes in landing queue was: " << maxLandingSize << endl;
    cout << "Average minutes spent waiting to land: " << avgLandingTime << endl;
    cout << "Maximum number of planes in takeoff queue was: " << maxTakeoffSize << endl;
    cout << "Average minutes spent waiting to takeoff: " << avgTakeofftime << endl;
    
    system("PAUSE");
    return 0;
}

*/
