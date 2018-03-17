//Filename:		ServerResources.h
//Name:			Tan Shi Terng Leon
//Declaration:	I did not pass my program to anyone in the class or copy anyone's work 
//				and I am willing to accept whatever penalty given to me and also to all
//				related parties involved
#include "EmailQueue.h"
#include <algorithm>

using namespace std;

//Used to store the number of attempts before a message is successfully sent
struct Attempts
{
	//Constructor
	Attempts (int attempts, int numOfMails)
	{
		this -> attempts = attempts;
		this -> numOfMails = numOfMails;
	}

	//Overloads operator ==
	bool operator== (const int &a)
	{
		return (this -> attempts == a);
	}

	int attempts;	//Number of attempts
	int numOfMails;	//Number of mails with the corresponding number of attempts
					//before it is successfully sent
};

//Stores statistical data that needs to be updated during runtime
//This class is a singleton
class ServerResources
{
public:
	~ServerResources (void);

	static ServerResources *getInstance ();	//Gets the pointer to this object

	void setTotalMins (int);			//Set total minutes of simulation
	void addNumProcessed (int);			//Adds the number of mails processed (each minute)
	void addNumArrived (int);			//Adds the number of mails arrived (each minute)
	void addNumSent (int);				//Adds the number of mails sent (each minute)
	void addNumInQueue (int);			//Adds the number of mails in the queue (end of each minute)

	void registerMail (Mail*);			//Registers the (newly received) mail to the system
	void updateAttempts (Mail*);		//Updates the number of attempts before sent statistics
	void incrementTotalRequeues ();		//Increments the total number of requeues performed
	void incrementTotalMailsRequeued ();//Increments the total number of mails that have
										//been requeued

	void saveReceivedQueue (EmailQueue);//Save queue state after receiving messages
	void saveSentQueue (EmailQueue);	//Save queue state after sending messages

	int getTotalMins () const;			//Gets the total minutes of simulation
	int getNumProcessed (int) const;	//Gets the number of mails processed at the given minute
	int getNumArrived (int) const;		//Gets the number of mails arrived at the given minute
	int getNumSent (int) const;			//Gets the number of mails sent at the given minute
	int getNumInQueue (int) const;		//Gets the number of mails in the queue at
										//the end of the given minute
	int getAttemptsBeforeSent (int);	//Gets the number of mails given the number of attempts
										//before it is successfully sent
	int getNextID ();					//Gets the next id to register mail

	int getTotalProcessed () const;		//Computes the total number of mails processed
	int getTotalArrived () const;		//Computes the total number of mails arrived
	int getTotalSent () const;			//Computes the total number of mails sent
	int getTotalQueueSize () const;		//Computes the sum of the queue sizes
										//at the end of every minute
	int getTotalRequeues () const;		//Gets the total requeues performed
	int getTotalMailsRequeued () const;	//Gets the total number of messages that
										//have been requeued
	int getMaxAttempts () const;		//Gets and computes the maximum number of attempts
										//before a message is sent

	double getAvgProcessed () const;	//Computes the average number of mails processed
	double getAvgArrived () const;		//Computes the average number of mails arrived
	double getAvgSent () const;			//Computes the average number of mails sent
	double getAvgQueueSize () const;	//Computes the average queue size
	double getAvgTimeMailRequeued () const;	//Computes the average time a mail is requeued
											//excluding messages sent on the first time

	void printStatistics ();			//Prints the statistics
	void printNumOfAttempts ();			//Prints the number of attempts before sent
										//and the corresponding number of mails

	void printMailDetails (int);		//Prints the details of a mail given its id
	Mail* getMailByID (int);			//Gets a mail given its id

	void printMinDetails (int);			//Print the statistics of the minute

	void printAfterArrivedAtMin (int);	//Prints queue state after receiving given a minute
	void printAfterSentAtMin (int);		//Prints queue state after sending given a minute

private:
	ServerResources (void);		//Constructor kept private to prevent
								//multiple instances of the class

	static ServerResources *serverResourcesPtr;	//Pointer to this singleton object

	int totalMins;			//Total minutes simulated
	int nextID;				//Next ID to be generated for the next mail
	int totalRequeues;		//Total number of requeues performed
	int totalMailsRequeued;	//Total number of mails that have been requeued
	
	//Stores the number of mail processed, arrived, sent, contain in the queue
	//for each minute respectively
	vector<int> numProcessed, numArrived, numSent, numInQueue;

	//Stores the number of attempts before sent and the corresponding number of mails
	vector<Attempts> attemptsBeforeSent;

	//Stores the list of generated (received) mails
	vector<Mail*> emailList;

	//Stores the states of the queue at every minute
	vector<EmailQueue> afterArrived, afterSent;

	//Computes the sum of a vector
	int getTotal (vector<int>) const;
};
