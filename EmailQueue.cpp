//Filename:		EmailQueue.cpp
//Name:			Tan Shi Terng Leon
//Declaration:	I did not pass my program to anyone in the class or copy anyone's work 
//				and I am willing to accept whatever penalty given to me and also to all
//				related parties involved
#include "EmailQueue.h"

//Default constructor
EmailQueue::EmailQueue(void)
{
}

EmailQueue::~EmailQueue(void)
{
}

//Returns the size of the queue
int EmailQueue::getSize() const
{
	return q.size();
}

//Returns a mail at position idx of the queue
Mail* EmailQueue::get(int idx) const
{
	return q.at(idx);
}

//Return the mail at the front of the queue
Mail* EmailQueue::front() const
{
	return q.front();
}

//Enqueues a mail to the back of the queue
void EmailQueue::enqueue(Mail *mail)
{
	q.push_back (mail);
}

//Dequeues a mail from the front of the queue
void EmailQueue::dequeue()
{
	q.erase (q.begin ());
}

//Returns true if queue is empty, false otherwise
bool EmailQueue::isEmpty() const
{
	return q.empty ();
}

//Prints the contents of the queue
void EmailQueue::print()
{
	for (vector<Mail*>::iterator it = q.begin (); it != q.end (); it++)
		cout<<(*it) -> getID ()<<", ";

	cout<<endl;
}
