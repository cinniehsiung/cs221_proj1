/*---------------------------------------------------------------------
 Driver program to test the Queue class.
 ----------------------------------------------------------------------*/

#include <iostream>
#include "LQueue.h"
#include <array>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

/*-----------------------------------------------------------------------
Runs the plane runway simulation (Part 2 of assignment).
-----------------------------------------------------------------------*/
void runSim();

/*-----------------------------------------------------------------------
Runs the test cases for move_to_front and merge_two_queues 
(Part 1 of assignment).
-----------------------------------------------------------------------*/
void testMode();

/*-----------------------------------------------------------------------
Initiates the takeoff/landing of the plane at the front of a given queue
on a given runway. Also calculates the wait time of the plane. 

Precondition: 
	Queue queue			- queue whose front element is the plane that is
						taking off / landing
	string queueType	- name of runway (either "A" or "B") 
	int currTime		- current time in simulation
	bool runwayInUse	- indicates whether the given runway is in use or not 
						should be false before calling this function.
	int sumTime			- sum of planes' waiting times for the given queue. 
	string message		- indicates whether the queue is for landing or takeoff 
						by printing to console. 
-----------------------------------------------------------------------*/
void startRunway(Queue * queue, string queueType, int currTime, int & startTime, bool & runwayInUse, int & sumTime, string message);

/*-----------------------------------------------------------------------
Removes the plane from the given queue after take off / landing is complete,
and frees the runway. 

Precondition:
	Queue queue			- queue whose front element is the plane that has completeted
						landing / takeoff.
	string message		- indicates whether the queue is for landing or takeoff
						by printing to console.
	string queueType	- name of runway (either "A" or "B")
	bool runwayInUse	- indcates whether the given runway is in use or not
						should be true before calling this function
-----------------------------------------------------------------------*/
void endRunway(Queue * queue, string message, string queueType, bool & runwayInUse);

/*-----------------------------------------------------------------------
Adds plane to the given take off / landing queue. 

Precondition:
	Queue queue			- queue to add plane to (begin wait).
	int planeNum		- indicates plane identification number.
	string queueType	- name of runway (either "A" or "B")
	int currTime		- current time in simulation
	int totalPlanes		- total number of planes that have gone through this queue
	int maxSize			- maximum number of planes in the given queue at any time
-----------------------------------------------------------------------*/
void beginWait(Queue * queue, int & planeNum, string queueType, int currTime, int & totalPlanes, int & maxSize);

/*-----------------------------------------------------------------------
Gets the average waiting times.

Precondition:
	int sumTimes		- sum of waiting times of all planes. 
	int numberOfPlanes	- total number of planes.	 
-----------------------------------------------------------------------*/
double getAvg(int sumTimes, int numberOfPlanes);

void print(Queue q)
{ q.display(cout); }

int main(void)
{
	int userInput = false; 

	cout << "Enter 1 for simulation, or 0 for test mode." << endl;
	cin >> userInput; 

	if (userInput) {
		runSim();
	}
	else {
		testMode();
	}

    system("PAUSE");
    return 0;
}

void startRunway(Queue * queue, string queueType, int currTime, int & startTime, bool & runwayInUse, int & sumTime, string message)
{
	cout << '\t' <<  message << " from Queue " << queueType << " Plane " << queue->front() << endl; 
    startTime = currTime;
    runwayInUse = true;
    
    //for calculating stats
    sumTime += currTime - queue->frontTime();
}

void endRunway(Queue * queue, string message, string queueType, bool & runwayInUse){
    queue->dequeue();
    cout << '\t'<<message << "complete; " << queue->size() << " in Queue " << queueType << endl;
    runwayInUse = false;
}

void beginWait(Queue * queue, int & planeNum, string queueType, int currTime, int & totalPlanes, int & maxSize){
    queue->enqueue(planeNum++, currTime);
    int sizeOfQueue = queue->size();
    cout << sizeOfQueue << " in Queue " << queueType  << endl;
    
    //for calculating stats
    totalPlanes++;
    
    if(sizeOfQueue > maxSize){
        maxSize = sizeOfQueue;
    }
}

double getAvg(int sumTimes, int numberOfPlanes){
    if(numberOfPlanes == 0){
        return 0;
    }
    return roundf((((double) sumTimes)/numberOfPlanes)*100)/100;
}

void runSim() {

	srand((int)time(NULL));
	
	//simulation inputs
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


	//initiate variables
	Queue * landingQueueA = new Queue(), * landingQueueB = new Queue();
	Queue * takeoffQueueA = new Queue(), * takeoffQueueB = new Queue();

	int sumLandingTimesA = 0, sumLandingTimesB = 0;
	int sumTakeoffTimesA = 0, sumTakeoffTimesB = 0;
	int totalLandingPlanesA = 0, totalLandingPlanesB = 0;
	int totalTakeoffPlanesA = 0, totalTakeoffPlanesB = 0;

	int planeNum = 1000;
	int maxTakeoffSizeA = 0, maxTakeoffSizeB = 0;
	int maxLandingSizeA = 0, maxLandingSizeB = 0;
	int takeoffStartTimeA = -1 - takeoffTime, takeoffStartTimeB = -1 - takeoffTime;
	int landingStartTimeA = -1 - landingTime, landingStartTimeB = -1 - landingTime;

	int currTime = 0;
	bool runwayInUseA = false, runwayInUseB = false;

	//loop to run simulation
	while (true) {
		int randLand;
		int randTakeoff;
		int randTornado;
		cout << "Time = " << currTime << endl;

		//end simluation generating planes
		if (currTime == simLength) {
			cout << '\t' << "No new takeoffs or landings will be generated" << endl;
		}

		// generate new takeoffs/landings
		if (currTime < simLength) {
			randTornado = rand() % 60;
			randLand = rand() % 60;
			randTakeoff = rand() % 60;

			//simulate a tornado 
			if (randTornado < tornadoRate) {
				//affect runway A if randTornado is even
				if (randTornado % 2) {
					landingQueueA->merge_two_queues(landingQueueB);
					takeoffQueueA->merge_two_queues(takeoffQueueB);
					cout << '\t' << "TORNADO WARNING: Runway B out of service. " << endl;
					runwayInUseB = false;
				}
				//affect runway B if randTornado is odd
				else {
					landingQueueB->merge_two_queues(landingQueueA);
					takeoffQueueB->merge_two_queues(takeoffQueueA);
					cout << '\t' << "TORNADO WARNING: Runway A out of service. " << endl;
					runwayInUseA = false;
				}
			}
			//simluate landing
			if (randLand < landingRate) {
				cout << '\t' << "Plane " << planeNum << " wants to land; added to landing queue;";
				//if there are fewer planes in A, enqueue to runway A
				if (landingQueueA->size() < landingQueueB->size()) {
					beginWait(landingQueueA, planeNum, "A", currTime, totalLandingPlanesA, maxLandingSizeA);
				}
				else {
					beginWait(landingQueueB, planeNum, "B", currTime, totalLandingPlanesB, maxLandingSizeB);
				}
			}
			//simlate takeoff
			if (randTakeoff < takeoffRate) {
				cout << '\t' << "Plane " << planeNum << " wants to takeoff; added to takeoff queue;";

				//if there are fewer planes in A, enqueue to runway A
				if (takeoffQueueA->size() < takeoffQueueB->size()) {
					beginWait(takeoffQueueA, planeNum, "A", currTime, totalTakeoffPlanesA, maxTakeoffSizeA);
				}
				else {
					beginWait(takeoffQueueB, planeNum, "B", currTime, totalTakeoffPlanesB, maxTakeoffSizeB);
				}
			}
		}

		// if runway A is not in use
		if (!runwayInUseA) {
			//can only takeoff if landing queue is empty
			if (!takeoffQueueA->empty() && landingQueueA->empty()) { 
				startRunway(takeoffQueueA, "A", currTime, takeoffStartTimeA, runwayInUseA, sumTakeoffTimesA, "Taking off");
			}
			else if (!landingQueueA->empty()) {
				startRunway(landingQueueA, "A", currTime, landingStartTimeA, runwayInUseA, sumLandingTimesA, "Landing");
			}
		}
		// if runway A is being used
		else {
			if ((currTime - takeoffStartTimeA) == takeoffTime && !takeoffQueueA->empty()) {
				endRunway(takeoffQueueA, "Takeoff ", "A", runwayInUseA);
			}
			else if ((currTime - landingStartTimeA) == landingTime && !landingQueueA->empty()) {
				endRunway(landingQueueA, "Landing ", "A", runwayInUseA);
			}
		}

		// if the runway B is not in use
		if (!runwayInUseB) {
			if (!takeoffQueueB->empty() && landingQueueB->empty()) {
				startRunway(takeoffQueueB, "B", currTime, takeoffStartTimeB, runwayInUseB, sumTakeoffTimesB, "Taking off");
			}
			else if (!landingQueueB->empty()) {
				startRunway(landingQueueB, "B", currTime, landingStartTimeB, runwayInUseB, sumLandingTimesB, "Landing");
			}
		}
		//if runway B is in use
		else {
			if ((currTime - takeoffStartTimeB) == takeoffTime && !takeoffQueueB->empty()) {
				endRunway(takeoffQueueB, "Takeoff ", "B", runwayInUseB);
			}
			else if ((currTime - landingStartTimeB) == landingTime && !landingQueueB->empty()) {
				endRunway(landingQueueB, "Landing ", "B", runwayInUseB);
			}
		}

		// check whether simulation ended
		if ((currTime > simLength) && landingQueueA->empty() && takeoffQueueA->empty()) {
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
}

void testMode() {
	// Testing move_to_front function
	cout << "-------------" << endl;
	cout << "Original Queue: 1 2 3 4 5 6 7 8 9" << endl;

	cout << "Test case: move random node to front. Testing move_to_front(3)" << endl;

	Queue q3;
	for (int i = 1; i <= 10; i++)
		q3.enqueue(i, 0);

	//move arbitary middle node to front
	q3.move_to_front(3);
	print(q3);

	std::array<int, 10> testArr1;
	std::array<int, 10> answerArr1{ 3, 1, 2, 4, 5, 6, 7, 8, 9, 10 };
	for (int i = 1; i <= 10; i++) {
		testArr1.at(i - 1) = q3.front();
		q3.dequeue();
	}

	if (testArr1 == answerArr1) {
		cout << "Passed move 3 to front" << endl;
	}
	else {
		cout << "Failed move 3 to front" << endl;
	}
	cout << endl;

	cout << "Test case: move last node to front. Testing move_to_front(10)" << endl;
	
	//move back node to front
	for (int i = 1; i <= 10; i++)
		q3.enqueue(i, 0);
	q3.move_to_front(3);
	q3.move_to_front(10);
	print(q3);

	std::array<int, 10> testArr2;
	std::array<int, 10> answerArr2{ 10, 3, 1, 2, 4, 5, 6, 7, 8, 9 };
	for (int i = 1; i <= 10; i++) {
		testArr2.at(i - 1) = q3.front();
		q3.dequeue();
	}

	if (testArr2 == answerArr2) {
		cout << "Passed move last node (10) to front" << endl;
	}
	else {
		cout << "Failed move last node (10) to front" << endl;
	}
	cout << endl;

	cout << "Test case: move front node to front. Testing move_to_front(10)" << endl;
	//move front node to front
	for (int i = 1; i <= 10; i++)
		q3.enqueue(i, 0);
	q3.move_to_front(3);
	q3.move_to_front(10);
	print(q3);

	std::array<int, 10> testArr3;
	std::array<int, 10> answerArr3{ 10, 3, 1, 2, 4, 5, 6, 7, 8, 9 };
	for (int i = 1; i <= 10; i++) {
		testArr3.at(i - 1) = q3.front();
		q3.dequeue();
	}

	if (testArr3 == answerArr3) {
		cout << "Passed move front node (10) to front" << endl;
	}
	else {
		cout << "Failed move front node (10) to front" << endl;
	}

	// Testing merge_two_queues function
	cout << "-------------" << endl;
	cout << "Testing merge_two_queues" << endl;

	srand(time(NULL));
	Queue q4;
	for (int i = 1; i <= 10; i++)
		q4.enqueue(rand() % 100, 0);  //enqueue 10 random integers

	Queue * q5 = new Queue();
	for (int i = 1; i <= 10; i++)
		q5->enqueue(rand() % 100, 0);

	cout << "First queue: " << endl;
	print(q4);
	cout << "Second queue: " << endl;
	print(*q5);
	q4.merge_two_queues(q5);
	cout << "Merged queues: " << endl;
	print(q4);
}