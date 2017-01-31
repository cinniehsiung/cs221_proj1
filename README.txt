CPSC 221
Programming Project 1: Queues, Simulation of an Airport Runway

Name(s): 		Cinnie Hsiung	Yuqing Du
Student ID:		12859147	24417140
UGrad Login: 		f2r0b		v7c0b

----------------------Project Description----------------------

The LQueue_driver program contains both Part 1 and Part 2 of the project. To access
testing of Part 1 (merge_two_queues and move_to_front), user must enter 0 
for test mode. To access simulation of Part 2, user must enter 1. This simulates
two airport runways through queues. Each runway is represented by two queues, 
one for takeoff and one for landing. We decided to add the unique feature of simulating 
two runways simultaneously, where queueing of flights is based on which runway 
is more available (smaller size). In addition, there is a random chance that a runway
is hit by a tornado, and will have to merge all incoming/outgoing flights onto the 
other (unaffected) runway for safety measures.

----------------------Brief Description of Submitted Files----------------------

	LQueue_driver.C - our main C++ file for the program.
			- simulates two runways named 'A' and 'B' simultaneously.
			 User-supplied inputs are:
			'Time for plane to land', 'Time for plane to takeoff', 
			'Landing rate', 'Takeoff rate', 'Merge rate', and 
			'Simulation length'. 
	LQueue.C - our queue ADT implementation.
			- standard queue functionality (enqueue, dequeue, 
			accessing front, etc.)
			- additional functionality (move_to_front, merge_two_queues)
	LQueue.h - our queue header file. Contains specifications for move_to_front, 
			merge_two_queues, and size
		
