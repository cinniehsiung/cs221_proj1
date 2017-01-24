/*---------------------------------------------------------------------
                  Driver program to test the Queue class.
  ----------------------------------------------------------------------*/

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
	Queue q1;
	cout << "Queue created.  Empty? " << boolalpha << q1.empty() << endl;

	cout << "How many elements to add to the queue? ";
	int numItems;
	cin >> numItems;
	for (int i = 1; i <= numItems; i++)
		q1.enqueue(100 * i);

	cout << "Contents of queue q1 (via  print):\n";
	print(q1);
	cout << endl;

	Queue q2;
	q2 = q1;
	cout << "Contents of queue q2 after q2 = q1 (via  print):\n";
	print(q2);
	cout << endl;

	cout << "Queue q2 empty? " << q2.empty() << endl;

	cout << "Front value in q2: " << q2.front() << endl;

	while (!q2.empty())
	{
		cout << "Remove front -- Queue contents: ";
		q2.dequeue();
		q2.display(cout);
	}
	cout << "Queue q2 empty? " << q2.empty() << endl;
	cout << "Front value in q2?" << endl << q2.front() << endl;
	cout << "Trying to remove front of q2: " << endl;
	q2.dequeue();

	// Testing move_to_front function
	cout << "-------------" << endl;
	cout << "Testing move_to_front" << endl;

	Queue q3;
	for (int i = 1; i <= 10; i++)
		q3.enqueue(i);

	//move arbitary middle node to front
	q3.move_to_front(3);
	print(q3);

	std::array<int, 10> testArr1;
	std::array<int, 10> answerArr1 { 3, 1, 2, 4, 5, 6, 7, 8, 9, 10 };
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

	//move back node to front
	for (int i = 1; i <= 10; i++)
		q3.enqueue(i);
	q3.move_to_front(3);
	q3.move_to_front(10);
	print(q3);

	std::array<int, 10> testArr2;
	std::array<int, 10> answerArr2 { 10, 3, 1, 2, 4, 5, 6, 7, 8, 9};
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

	//move front node to front
	for (int i = 1; i <= 10; i++)
		q3.enqueue(i);
	q3.move_to_front(3);
	q3.move_to_front(10);
	print(q3);

	std::array<int, 10> testArr3;
	std::array<int, 10> answerArr3 { 10, 3, 1, 2, 4, 5, 6, 7, 8, 9};
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
		q4.enqueue(rand() % 100);  //enqueue 10 random integers

	Queue q5;
	for (int i = 1; i <= 10; i++)
		q5.enqueue(rand() % 100);
		
	cout << "First queue: " << endl;
	print(q4);
	cout << "Second queue: " << endl;
	print(q5);
	q4.merge_two_queues(q4, q5);
	cout << "Merged queues: " << endl;
	print(q4);

   system("PAUSE");
   return 0;
}
