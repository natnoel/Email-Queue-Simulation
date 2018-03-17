//Filename:		EmailQueue.h
//Name:			Tan Shi Terng Leon
//Declaration:	I did not pass my program to anyone in the class or copy anyone's work 
//				and I am willing to accept whatever penalty given to me and also to all
//				related parties involved
#include "Mail.h"

using namespace std;

//Describes an Email Queue
class EmailQueue
{
public:
	EmailQueue (void);
	~EmailQueue (void);

	int getSize() const;	//Gets the size of the queue
	Mail* get(int) const;	//Gets the mail at a certain postion in the queue
	Mail* front() const;	//Gets the mail at the front of the queue

	void enqueue (Mail*);	//Enqueues a mail
	void dequeue ();		//Dequeues a mail

	bool isEmpty () const;	//Checks if the queue is empty
	void print ();			//Prints the contents of the queue

private:
	vector<Mail*> q;		//A vector containing the mails
};
