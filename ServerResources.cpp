//Filename:		ServerResources.cpp
//Name:			Tan Shi Terng Leon
//Declaration:	I did not pass my program to anyone in the class or copy anyone's work 
//				and I am willing to accept whatever penalty given to me and also to all
//				related parties involved
#include "ServerResources.h"

ServerResources* ServerResources::serverResourcesPtr = NULL;

ServerResources::ServerResources (void)
{
	//Initialization
	totalMins = 0;
	nextID = 0;
	totalRequeues = 0;
	totalMailsRequeued = 0;
}

ServerResources::~ServerResources (void)
{
}

//Returns a static pointer to the object
//If object not created, creates object
ServerResources* ServerResources::getInstance ()
{
	if (!serverResourcesPtr)
		serverResourcesPtr = new ServerResources ();

	return serverResourcesPtr;
}

//Sets total minutes for simulation
void ServerResources::setTotalMins (int totalMins)
{
	this -> totalMins = totalMins;
}

//Adds number of mails processed at a minute
void ServerResources::addNumProcessed (int numProcessed)
{
	this -> numProcessed.push_back (numProcessed);
}

//Adds number of mails arrived at a minute
void ServerResources::addNumArrived (int numArrived)
{
	this -> numArrived.push_back (numArrived);
}

//Adds number of mails sent at a minute
void ServerResources::addNumSent (int numSent)
{
	this -> numSent.push_back (numSent);
}

//Registers mail to the system
void ServerResources::addNumInQueue (int numInQueue)
{
	this -> numInQueue.push_back (numInQueue);
}

//Registers the mail to the system
void ServerResources::registerMail (Mail* mailPtr)
{
	emailList.push_back (mailPtr);
}

//Updates the number of messages sent under their corresponding attempts
void ServerResources::updateAttempts (Mail* m)
{
	//Number of attempts is the number of times requeued + 1 (includes the first time)
	int numOfAttmpts = m -> getNumOfTimesRequeued () + 1;

	vector<Attempts>::iterator it = find (attemptsBeforeSent.begin (), attemptsBeforeSent.end (), numOfAttmpts);

	if (it == attemptsBeforeSent.end ())							//If number of attempts does not exist
		attemptsBeforeSent.push_back (Attempts (numOfAttmpts, 1));	//create a new object
	else															//otherwise
		it -> numOfMails++;											//just increment the number of mails
}

//Increments the total requeues performed
void ServerResources::incrementTotalRequeues ()
{
	totalRequeues++;
}

//Increments the total number of mails requeued at least once
void ServerResources::incrementTotalMailsRequeued ()
{
	totalMailsRequeued++;
}

//Save the state of the queue after receiving mails at a minute
void ServerResources::saveReceivedQueue (EmailQueue q)
{
	afterArrived.push_back (q);
}

//Save the state of the queue after sending mails at a minute
void ServerResources::saveSentQueue (EmailQueue q)
{
	afterSent.push_back (q);
}

//Gets the total minutes of simulation
int ServerResources::getTotalMins () const
{
	return totalMins;
}

//Returns the ID to register the next mail and increments it after that
//A way to make sure ID is unique
int ServerResources::getNextID ()
{
	return nextID++;
}

//Returns the number of mails processed given the particular minute
int ServerResources::getNumProcessed (int pos) const
{
	return numProcessed.at (pos);
}

//Returns the number of mails arrived given the particular minute
int ServerResources::getNumArrived (int pos) const
{
	return numArrived.at (pos);
}

//Returns the number of mails sent given the particular minute
int ServerResources::getNumSent (int pos) const
{
	return numSent.at (pos);
}

//Returns the number of mails in the queue given the particular minute
int ServerResources::getNumInQueue (int pos) const
{
	return numInQueue.at (pos);
}

//Returns the number of mails sent before a certain number of attempts
int ServerResources::getAttemptsBeforeSent (int numOfAttempts)
{
	int numOfMails = 0;	//Default to zero

	vector<Attempts>::iterator it = find (attemptsBeforeSent.begin (), attemptsBeforeSent.end (), numOfAttempts);

	if (it != attemptsBeforeSent.end ())	//If number of attempts exists, 
		numOfMails = it -> numOfMails;		//returns the number of mails with that number of attempts

	return numOfMails;
}

//Sums up the values in a given vector
int ServerResources::getTotal (vector<int> list) const
{
	int total = 0;

	for (vector<int>::const_iterator it = list.begin (); it != list.end (); it++)
		total += *it;

	return total;
}

//Returns the total number of mails processed
int ServerResources::getTotalProcessed () const
{
	return getTotal (numProcessed);
}

//Returns the total number of mails arrived
int ServerResources::getTotalArrived () const
{
	return getTotal (numArrived);
}

//Returns the total number of mails sent
int ServerResources::getTotalSent () const
{
	return getTotal (numSent);
}

//Returns the sum of all the queue sizes for every minute of the simulation
int ServerResources::getTotalQueueSize () const
{
	return getTotal (numInQueue);
}

//Returns the total number of requeues performed
int ServerResources::getTotalRequeues () const
{
	return totalRequeues;
}

//Returns the total number of mails requeued at least once
int ServerResources::getTotalMailsRequeued () const
{
	return totalMailsRequeued;
}

//Returns the maximum attempts recorded before a mail is sent
int ServerResources::getMaxAttempts () const
{
	int maxAttmpts = -1;

	for (int i = 0; i < static_cast<int> (attemptsBeforeSent.size ()); i++)
		maxAttmpts = max (attemptsBeforeSent.at (i).attempts, maxAttmpts);

	return maxAttmpts;
}

//Computes the average number of mails processed per minute
double ServerResources::getAvgProcessed () const
{
	double avgProcessed;
	avgProcessed = static_cast<double> (getTotalProcessed ()) / totalMins;

	return avgProcessed;
}

//Computes the average number of arrived processed per minute
double ServerResources::getAvgArrived () const
{
	double avgArrived;
	avgArrived = static_cast<double> (getTotalArrived ()) / totalMins;

	return avgArrived;
}

//Computes the average number of mails sent per minute
double ServerResources::getAvgSent () const
{
	double avgSent;
	avgSent = static_cast<double> (getTotalSent ()) / totalMins;

	return avgSent;
}

//Computes the average number of mails in the queue per minute
double ServerResources::getAvgQueueSize () const
{
	double avgSize;
	avgSize = static_cast<double> (getTotalQueueSize ()) / totalMins;

	return avgSize;
}

//Computes the average time a mail is requeued
//Excludes mails successfully sent on the first time
double ServerResources::getAvgTimeMailRequeued () const
{
	double avgTimes = 0;

	if (totalMailsRequeued != 0)	//Avoids divide by zero
		avgTimes = static_cast<double> (totalRequeues) / totalMailsRequeued;

	return avgTimes;
}

//Prints the statiscal information
void ServerResources::printStatistics ()
{
	cout<<"Statistics"<<endl
		<<"----------"<<endl
		<<"Total minutes simulated: "<<getTotalMins ()<<endl
		<<"Total messages processed: "<<getTotalArrived ()<<endl
		<<"Total messages sent: "<<getTotalSent ()<<endl
		<<"Total requeues performed: "<<getTotalRequeues ()<<endl
		<<"Total messages requeued at least once: "<<getTotalMailsRequeued ()<<endl<<endl
		<<"Average arrival rate (per minute): "<<getAvgArrived ()<<endl
		<<"Average number of messages sent per minute: "<<getAvgSent ()<<endl
		<<"Average number of messages in the queue in a minute: "<<getAvgQueueSize ()<<endl<<endl;

	printNumOfAttempts ();

	cout<<endl;
	cout<<"Average number of times problem messages had to be requeued: "<<getAvgTimeMailRequeued ()<<endl;
}

//For prints the number of attempts and the number of mails that are successfully sent
//after there corresponding attempts
void ServerResources::printNumOfAttempts ()
{
	for (int i = 1; i <= getMaxAttempts (); i++)
	{
		cout<<"Number of messages sent on the "<<i;

		if (i % 10 == 1)
			cout<<"st ";
		else if (i % 10 == 2)
			cout<<"nd ";
		else if (i % 10 == 3)
			cout<<"rd ";
		else
			cout<<"th ";

		cout<<"attempt: "<<getAttemptsBeforeSent (i)<<endl;
	}
}

//Prints the details of the mail given its ID
void ServerResources::printMailDetails (int id)
{
	Mail *mailPtr = getMailByID (id);

	if (mailPtr)
		mailPtr -> printMailDetails ();
	else	//If ID does not exist
		cout<<"This mail does not exist in records!"<<endl;
}

//Returns the mail given its ID
Mail* ServerResources::getMailByID (int id)
{
	Mail *mailPtr = NULL;

	for (vector<Mail*>::iterator it = emailList.begin (); it != emailList.end (); it++)
	{
		if ((*it) -> getID () == id)
			mailPtr = *it;
	}

	return mailPtr;
}

//Prints statistical information of that minute
void ServerResources::printMinDetails (int min)
{
	int idx = min - 1;

	cout<<"Minute "<<min<<endl
		<<"---------"<<endl;
	cout<<"Queue after receiving"<<endl;
	printAfterArrivedAtMin (min);
	cout<<endl
		<<"Queue after sending"<<endl;
	printAfterSentAtMin (min);
	cout<<endl;
	cout<<"Number of mails received: "<<getNumArrived (idx)<<endl
		<<"Number of mails sent: "<<getNumSent (idx)<<endl
		<<"Number of mails requeued: "<<getNumProcessed (idx) - getNumSent (idx)<<endl
		<<"Length of queue: "<<getNumInQueue (idx)<<endl;
}

//Prints the state of the queue after receiving mails at a given minute
void ServerResources::printAfterArrivedAtMin (int min)
{
	afterArrived.at (min - 1).print ();
}

//Prints the state of the queue after sending mails at a given minute
void ServerResources::printAfterSentAtMin (int min)
{
	afterSent.at (min - 1).print ();
}
