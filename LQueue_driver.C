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

void startRunway(Queue & queue, string queueType, int currTime, int & startTime, bool & runwayInUse, int & sumTime, string message);

void endRunway(Queue & queue, string message, string queueType, bool & runwayInUse);

void enqueue(Queue & queue, int & planeNum, string queueType, int currTime, int & totalPlanes, int & maxSize);

double getAvg(int sumTimes, int numberOfPlanes);

void runSim();

void testMode();

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

void startRunway(Queue & queue, string queueType, int currTime, int & startTime, bool & runwayInUse, int & sumTime, string message)
{
	cout << '\t' <<  message << " from Queue " << queueType << " Plane " << queue.front() << endl;
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

void runSim() {

	srand((int)time(NULL));
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
	int takeoffStartTimeA = -1 - takeoffTime, takeoffStartTimeB = -1 - takeoffTime;
	int landingStartTimeA = -1 - landingTime, landingStartTimeB = -1 - landingTime;

	int currTime = 0;
	bool runwayInUseA = false, runwayInUseB = false;

	while (true) {
		int randLand;
		int randTakeoff;
		int randTornado;
		cout << "Time = " << currTime << endl;

		if (currTime == simLength) {
			cout << '\t' << "No new takeoffs or landings will be generated" << endl;
		}

		// generate new takeoffs/landings
		if (currTime < simLength) {
			randTornado = rand() % 60;
			randLand = rand() % 60;
			randTakeoff = rand() % 60;

			if (randTornado < tornadoRate) {
				if (randTornado % 2) {
					landingQueueA.merge_two_queues(landingQueueA, landingQueueB);
					takeoffQueueA.merge_two_queues(takeoffQueueA, takeoffQueueB);
					cout << '\t' << "TORNADO WARNING: Runway B out of service. " << endl;
					runwayInUseB = false;
				}
				else {
					landingQueueB.merge_two_queues(landingQueueB, landingQueueA);
					takeoffQueueB.merge_two_queues(takeoffQueueB, takeoffQueueA);
					cout << '\t' << "TORNADO WARNING: Runway A out of service. " << endl;
					runwayInUseA = false;
				}
			}

			if (randLand < landingRate) {
				cout << '\t' << "Plane " << planeNum << " wants to land; added to landing queue;";

				//if there are fewer planes in A, enqueue to runway A
				if (landingQueueA.size() < landingQueueB.size()) {
					enqueue(landingQueueA, planeNum, "A", currTime, totalLandingPlanesA, maxLandingSizeA);
				}
				else {
					enqueue(landingQueueB, planeNum, "B", currTime, totalLandingPlanesB, maxLandingSizeB);

				}
			}

			if (randTakeoff < takeoffRate) {
				cout << '\t' << "Plane " << planeNum << " wants to takeoff; added to takeoff queue;";

				//if there are fewer planes in A, enqueue to runway A
				if (takeoffQueueA.size() < takeoffQueueB.size()) {
					enqueue(takeoffQueueA, planeNum, "A", currTime, totalTakeoffPlanesA, maxTakeoffSizeA);
				}
				else {
					enqueue(takeoffQueueB, planeNum, "B", currTime, totalTakeoffPlanesB, maxTakeoffSizeB);
				}
			}
		}

		// if the runway A is not in use
		if (!runwayInUseA) {
			if (!takeoffQueueA.empty() && landingQueueA.empty()) {
				startRunway(takeoffQueueA, "A", currTime, takeoffStartTimeA, runwayInUseA, sumTakeoffTimesA, "Taking off");
			}
			else if (!landingQueueA.empty()) {
				startRunway(landingQueueA, "A", currTime, landingStartTimeA, runwayInUseA, sumLandingTimesA, "Landing");
			}
		}
		// if the runway is being used
		else {
			if ((currTime - takeoffStartTimeA) == takeoffTime && !takeoffQueueA.empty()) {
				endRunway(takeoffQueueA, "Takeoff ", "A", runwayInUseA);
			}
			else if ((currTime - landingStartTimeA) == landingTime && !landingQueueA.empty()) {
				endRunway(landingQueueA, "Landing ", "A", runwayInUseA);
			}
		}

		// if the runway B is not in use
		if (!runwayInUseB) {
			if (!takeoffQueueB.empty() && landingQueueB.empty()) {
				startRunway(takeoffQueueB, "B", currTime, takeoffStartTimeB, runwayInUseB, sumTakeoffTimesB, "Taking off");
			}

			else if (!landingQueueB.empty()) {
				startRunway(landingQueueB, "B", currTime, landingStartTimeB, runwayInUseB, sumLandingTimesB, "Landing");
			}
		}
		else {
			if ((currTime - takeoffStartTimeB) == takeoffTime && !takeoffQueueB.empty()) {
				endRunway(takeoffQueueB, "Takeoff ", "B", runwayInUseB);
			}
			else if ((currTime - landingStartTimeB) == landingTime && !landingQueueB.empty()) {
				endRunway(landingQueueB, "Landing ", "B", runwayInUseB);
			}
		}


		// check whether simulation ended
		if ((currTime > simLength) && landingQueueA.empty() && takeoffQueueA.empty()) {
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

	cout << "Test case: move front node to front. Testing move_to_front(10)";
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

	Queue q5;
	for (int i = 1; i <= 10; i++)
		q5.enqueue(rand() % 100, 0);

	cout << "First queue: " << endl;
	print(q4);
	cout << "Second queue: " << endl;
	print(q5);
	q4.merge_two_queues(q4, q5);
	cout << "Merged queues: " << endl;
	print(q4);
}