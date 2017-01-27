CPSC 221
Programming Project 1: Queues, Simulation of an Airport Runway

Name(s): 		Cinnie Hsiung	Yuqing Du
Student ID:		12859147	24417140
UGrad Login: 		f2r0b		v7c0b

Project Description

The LQueue_driver program simulates two airport runways through queues. Each 
runway is represented by two queues, one for takeoff and one for landing.
In order to further the functionality of the queues, we implemented a function
to move a particular queue element to the head of the queue, as well as a function
that would merge two queues and sort the combined queue non-descendingly. 

We decided to add the unique feature of simulating two runways simultaneously,
where queueing of flights is based on which runway is more available. In addition,
there is a random chance that a runway is hit by a tornado, and will have to merge
all flights onto the other unaffected runway for safety measures.

Brief Description of Submitted Files
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
	LQueue.h - our queue header file.
		
