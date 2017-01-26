/*--- LQueue.cpp ----------------------------------------------------------
  This file implements LQueue member functions.
  From:  "ADTs, Data Structures, and Problem Solving with C++", 2nd edition
         by Larry Nyhoff
-------------------------------------------------------------------------*/
 
#include <iostream>
using namespace std;

#include "LQueue.h"

//--- Definition of Queue constructor
Queue::Queue()
: myFront(0), myBack(0)
{}

//--- Definition of Queue copy constructor
Queue::Queue(const Queue & original)
{
   myFront = myBack = 0;
   if (!original.empty())
   {
      // Copy first node
      myFront = myBack = new Queue::Node(original.front());

      // Set pointer to run through original's linked list
      Queue::NodePointer origPtr = original.myFront->next;
      while (origPtr != 0)
      {
         myBack->next = new Queue::Node(origPtr->data);
         myBack = myBack->next;
         origPtr = origPtr->next;
      }
   }
}

//--- Definition of Queue destructor
Queue::~Queue()
{ 
  // Set pointer to run through the queue
  Queue::NodePointer prev = myFront,
                     ptr;
  while (prev != 0)
    {
      ptr = prev->next;
      delete prev;
      prev = ptr;
    }
}

//--- Definition of assignment operator
const Queue & Queue::operator=(const Queue & rightHandSide)
{
   if (this != &rightHandSide)         // check that not q = q
   {
      this->~Queue();                  // destroy current linked list
      if (rightHandSide.empty())       // empty queue
         myFront = myBack = 0;
      else
      {                                // copy rightHandSide's list
         // Copy first node
         myFront = myBack = new Queue::Node(rightHandSide.front());

         // Set pointer to run through rightHandSide's linked list
         Queue::NodePointer rhsPtr = rightHandSide.myFront->next;
         while (rhsPtr != 0)
         {
           myBack->next = new Queue::Node(rhsPtr->data);
           myBack = myBack->next;
           rhsPtr = rhsPtr->next;
         }
      }
   }
   return *this;
}

//--- Definition of empty()
bool Queue::empty() const
{ 
   return (myFront == 0); 
}

//--- Definition of enqueue()
void Queue::enqueue(const QueueElement & value1, const int & value2)
{
   Queue::NodePointer newptr = new Queue::Node(value1, value2);
   if (empty())
      myFront = myBack = newptr;
   else
   {
      myBack->next = newptr;
      myBack = newptr;
   }
}

//--- Definition of display()
void Queue::display(ostream & out) const
{
   Queue::NodePointer ptr;
   for (ptr = myFront; ptr != 0; ptr = ptr->next)
     out << ptr->data << "  ";
   out << endl;
}

//--- Definition of front()
QueueElement Queue::front() const
{
   if (!empty())
      return (myFront->data);
   else
   {
	return 0;
   }
}

//--- Definition of frontTime()
int Queue::frontTime() const
{
    if (!empty())
        return (myFront->startTime);
    else
    {
        return 0;
    }
}

//--- Definition of dequeue()
void Queue::dequeue()
{
   if (!empty())
   {
      Queue::NodePointer ptr = myFront;
      myFront = myFront->next;
      delete ptr;
      if (myFront == 0)     // queue is now empty
         myBack = 0;
   }   
   else
      cerr << "*** Queue is empty -- can't remove a value ***\n";
}

//--- Definition of move_to_front()
void Queue::move_to_front(const QueueElement & value)
{
    
    if(myFront->data == value){
        return;
    }
    
    Queue::NodePointer ptr;
    Queue::NodePointer prevPtr = NULL;
    for (ptr = myFront; ptr != 0; ptr = ptr->next){
        if(ptr->data == value){
            
            if(ptr == myBack){
                prevPtr->next = 0;
                myBack = prevPtr;
            }
            
            else{
                prevPtr->next = ptr->next;
            }
           
            ptr->next = myFront;
            myFront = ptr;
            break;
        }
        
        prevPtr = ptr;
    }
}

//--- Definition of merge_two_queues()
void Queue::merge_two_queues(Queue & queue1, Queue & queue2)
{
    //CHECK THIS FOR BUGS
    while(!queue1.empty()){
        queue2.Queue::enqueue(queue1.myFront->data, queue1.myFront->startTime);
        queue1.Queue::dequeue();
    }
    
    Queue::NodePointer ptr;
    while(!queue2.empty()){
        
        QueueElement minValue = queue2.myFront->data;
        for (ptr = queue2.myFront; ptr != 0; ptr = ptr->next){
            if(ptr->data<minValue){
                minValue=ptr->data;
            }
        }
        
        queue2.move_to_front(minValue);
        queue1.enqueue(queue2.myFront->data, queue2.myFront -> startTime);
        queue2.dequeue();
    }
}

//--- Definition of size()
int Queue::size()
{
    int size = 0;
    Queue::NodePointer ptr;

    for (ptr = myFront; ptr != 0; ptr = ptr->next){
        size++;
    }
    
    return size;
}
