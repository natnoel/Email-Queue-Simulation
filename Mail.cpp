//Filename:		Mail.cpp
//Name:			Tan Shi Terng Leon
//Declaration:	I did not pass my program to anyone in the class or copy anyone's work 
//				and I am willing to accept whatever penalty given to me and also to all
//				related parties involved
#include "Mail.h"

//Default constructor
Mail::Mail(void)
{
	id = -1;
	minArrived = -1;
	secArrived = -1;
	timeArrived = -1;
	minSent = -1;
	secSent = -1;
	timeSent = -1;
}

//This constructor sets the id, minArrived and secArrived
//and also indirectly sets the timeArrived
Mail::Mail(int id, int minArrived, int secArrived)
{
	this -> id = id;
	this -> minArrived = minArrived;
	this -> secArrived = secArrived;

	timeArrived = minArrived * 60 + secArrived;

	minSent = -1;
	secSent = -1;
	timeSent = -1;
}

Mail::~Mail(void)
{
}

//Returns the ID of the mail
int Mail::getID () const
{
	return id;
}

//Return the minute it arrived
int Mail::getMinArrived () const
{
	return minArrived;
}

//Returns the second it arrived
int Mail::getSecArrived () const
{
	return secArrived;
}

//Returns the time it arrived in seconds
int Mail::getTimeArrived () const
{
	return timeArrived;
}

//Returns the minute it is sent
int Mail::getMinSent () const
{
	return minSent;
}

//Returns the second it is sent (nice pun)
int Mail::getSecSent () const
{
	return secSent;
}

//Returns the time it is sent in seconds
int Mail::getTimeSent () const
{
	return timeSent;
}

//Gets the number of times the message has been requeued
int Mail::getNumOfTimesRequeued () const
{
	return timeRequeued.size();
}

//Gets the time it is requeued
int Mail::getTimeRequeued (int requeueNo) const
{
	return timeRequeued.at (requeueNo);
}

//Sets the time it is sent
void Mail::setTimeSent (int minSent, int secSent)
{
	this -> minSent = minSent;
	this -> secSent = secSent;

	timeSent = minSent * 60 + secSent;
}

//Adds the time it is requeued
void Mail::addTimeRequeued (int min)
{
	timeRequeued.push_back (min);
}

//Checks if the message has been sent
bool Mail::hasBeenSent () const
{
	return (timeSent != -1);
}

//Returns the time taken to send the message in seconds
int Mail::timeTakenToSend () const
{
	return timeSent - timeArrived;
}

//Print the details of the mail
void Mail::printMailDetails () const
{
	cout<<"Mail ID: "<<id<<endl
		<<"Time arrived: "<<getMinArrived ()<<" min, "<<getSecArrived ()<<" secs"<<endl;

	//If it has been sent, display status, time sent and time taken to send
	if (hasBeenSent ())
		cout<<"Status: sent"<<endl
			<<"Time sent: "<<getMinSent ()<<" min, "<<getSecSent ()<<" secs"<<endl
			<<"Time taken to send: "<<timeTakenToSend ()<<" secs"<<endl;
	//If not just display the status
	else
		cout<<"Status: pending"<<endl;

	cout<<"Number of time requeued: "<<getNumOfTimesRequeued ()<<endl;

	//Displays times it is requeued
	for (int i = 0; i < static_cast<int> (timeRequeued.size ()); i++)
		cout<<"\tRequeued at "<<timeRequeued.at(i)<<" min"<<endl;
}
