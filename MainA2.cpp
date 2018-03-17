//Filename:		MainA2.cpp
//Name:			Tan Shi Terng Leon
//Declaration:	I did not pass my program to anyone in the class or copy anyone's work 
//				and I am willing to accept whatever penalty given to me and also to all
//				related parties involved
#include "ServerResources.h"
#include "PoissonDist.h"
#include <string>
#include <ctime>

using namespace std;

//Driver class
class EmailSimulator
{
public:
	EmailSimulator ();

	static const int SECONDS_PER_MIN = 60;
	static const int AVG_ARRIVAL_RATE = 30;
	static const int MAX_NUM_TO_PROCESS = 40;
	static const double PERCENTAGE_CANNOT_SEND;

	int main ();

private:
	ServerResources *serverResources;
	PoissonDist mailsPerSecDist;
	EmailQueue emailQueue;

	//Allows user to input the total minutes of simulation
	int getTotalMins ();

	//Receive mails for one minute
	void receiveMails (int);

	//Generates the number of mails to produce for a second
	int generateNumOfMailsForASec ();

	//Generates a random number between 0 (inclusive) to 1 (exclusive)
	double generateProbability ();


	//Determines how many and which mails to sent and which cannot be sent
	//and takes the appropriate action
	void processMails (int);

	//Generates the number of mails to be processed
	int generateNumToProcess ();

	//Generates a list of numbers corresponding to the mails
	//that cannot be sent
	vector<int> generateErrorMailList (int);

	//Dequeues and sends a mail
	void sendMail (int);

	//Dequeues and requeues the mail
	void requeueMail (int);

	//Prints the stats for every minute
	void printLoopStats (int) const;


	//Allows user to track a mail or the statistics in a given minute
	void track () const;

	//Tracks a mail
	void trackMail () const;

	//Shows statistics in a given minute
	void trackMin () const;
};

const double EmailSimulator::PERCENTAGE_CANNOT_SEND = 0.25;

EmailSimulator::EmailSimulator ()
{
	//Initializations
	serverResources = ServerResources::getInstance ();

	//The mean number of mails coming in a second is 30/60
	mailsPerSecDist.setLambda (static_cast<double> (AVG_ARRIVAL_RATE) / SECONDS_PER_MIN);

	srand ((int) time (NULL));
}

int EmailSimulator::main ()
{
	cout<<"Welcome to CSCI203 Assignment 2: Email Simulator"<<endl
		<<"------------------------------------------------"<<endl<<endl;

	//User sets the minutes of simulation
	serverResources -> setTotalMins (getTotalMins ());

	cout<<endl<<"Total mins: "<<serverResources -> getTotalMins()<<endl<<endl;

	//In each minute
	for (int min = 0; min < serverResources -> getTotalMins (); min++)
	{
		receiveMails (min);

		processMails (min + 1);

		//Prints the statistics for this minute
		printLoopStats (min + 1);

		cout<<endl<<"-------------------------------------------------------------------------------"<<endl;
	}

	//Prints the overall statistics
	serverResources ->printStatistics ();
	cout<<endl;

	//Allows user to track a mail or display the statistics of a minute of simulation
	track ();

	cout<<"Have a nice day! :D"<<endl;

	return 0;
}

//Allows user to input the minutes of simulation
int EmailSimulator::getTotalMins ()
{
	int totalMins;
	string totalMinsStr;

	do
	{
		cout<<"Enter number minutes to simulate: ";
		getline (cin, totalMinsStr);
		totalMins = atoi (totalMinsStr.c_str ());
		if (totalMins < 1)
			cout<<"Please enter a number more than 0!"<<endl;

	} while (totalMins < 1);

	return totalMins;
}

//Receives arriving mails
void EmailSimulator::receiveMails (int min)
{
	int numReceived;
	int totalReceived = 0;

	//For each second
	for (int sec = 0; sec < SECONDS_PER_MIN; sec++)
	{
		numReceived = generateNumOfMailsForASec ();

		//Adds the number of mails received this second to the queue
		for (int j = 0; j < numReceived; j++)
		{
			//Creates new mail
			Mail *newMail = new Mail (serverResources -> getNextID (), min, sec);

			//Enqueues the new mail to the queue
			emailQueue.enqueue (newMail);

			//Registers the mail
			serverResources -> registerMail (newMail);
		}

		totalReceived += numReceived;
	}

	serverResources -> addNumArrived (totalReceived);	//Updates statistics
	serverResources -> saveReceivedQueue (emailQueue);
}

//Returns the number of mail to be generated for a second
int EmailSimulator::generateNumOfMailsForASec ()
{
	double prob = generateProbability ();

	int numOfMailsThisSec = 0;

	while (prob >= mailsPerSecDist.getProbability (0, numOfMailsThisSec))
		numOfMailsThisSec++;

	return numOfMailsThisSec;
}

//Returns a random number between 0 (inclusive) to 1 (exclusive)
double EmailSimulator::generateProbability ()
{
	double probability = rand () % 1000 / 1000.0;
	return probability;
}

void EmailSimulator::processMails (int min)
{
	int numToProcess = generateNumToProcess ();
	vector<int> errorMailList = generateErrorMailList (numToProcess);

	int numSent = 0;
	int numRequeued = 0;

	for (int i = 0; i < numToProcess; i++)
	{
		if (find (errorMailList.begin (), errorMailList.end (), i) == errorMailList.end ())
		{
			//Dequeue and send
			sendMail (min);
			++numSent;
		}
		else
		{
			//Dequeue and enqueue
			requeueMail (min);
			++numRequeued;
		}
	}

	//Update statistics
	serverResources -> addNumSent (numSent);
	serverResources -> addNumProcessed (numToProcess);
	serverResources -> addNumInQueue (emailQueue.getSize ());
	serverResources -> saveSentQueue (emailQueue);
}

//Generates the number of mails to process
int EmailSimulator::generateNumToProcess ()
{
	return rand () % (MAX_NUM_TO_PROCESS + 1);
}

//Generates a list of numbers corresponding the the problem messages
vector<int> EmailSimulator::generateErrorMailList (int numToProcess)
{
	vector<int> errorMailList;
	int idx;

	//Number of problem mails
	int numOfProblemMails = static_cast<int> (numToProcess * PERCENTAGE_CANNOT_SEND);

	for (int i = 0; i < numOfProblemMails; i++)
	{
		do	//Repeat if idx already exists in the list
		{
			idx = rand () % numToProcess;

		} while (find (errorMailList.begin (), errorMailList.end (), idx) != errorMailList.end ());

		errorMailList.push_back (idx);	//Add the idx to the list
	}

	return errorMailList;
}

//Dequeues and sends the mail
void EmailSimulator::sendMail (int min)
{
	Mail *successMail = emailQueue.front ();
	successMail -> setTimeSent (min, 0);	//Updates the time sent
	emailQueue.dequeue ();					//Dequeues the mail

	serverResources -> updateAttempts (successMail);	//Updates the statistics
}

//Dequeues and requeues the mail
void EmailSimulator::requeueMail (int min)
{
	Mail *problemMail = emailQueue.front ();
	problemMail -> addTimeRequeued (min);	//Updates the time requeued
	emailQueue.dequeue ();					//Dequeues the mail
	emailQueue.enqueue (problemMail);		//Enqueues the mail again

	serverResources ->incrementTotalRequeues ();		//Updates the statistics

	if (problemMail -> getNumOfTimesRequeued () == 1)	//If the first time requeued
		serverResources -> incrementTotalMailsRequeued ();	//Update statistics
}

//Print the statistics for each minute
void EmailSimulator::printLoopStats (int min) const
{
	serverResources -> printMinDetails (min);
}

//Tracks a mail or a minute
void EmailSimulator::track () const
{
	int option;
	string optionStr;

	do
	{
		cout<<"Track a message or a minute of simulation"<<endl
			<<"-----------------------------------------"<<endl
			<<"1. Track message"<<endl
			<<"2. Track a minute"<<endl
			<<"3. Exit"<<endl<<endl;

		do
		{
			cout<<"Enter your option: ";
			getline (cin, optionStr);
			option = atoi (optionStr.c_str ());

			if (option < 1 || option > 3)
				cout<<"Please enter 1 to 3 only"<<endl;

		} while (option < 1 || option > 3);	//Ensures option is valid

		cout<<endl;

		switch (option)
		{
		case 1:
			trackMail ();
			break;
		case 2:
			trackMin ();
			break;
		default:
			;
		}

		cout<<endl;
	} while (option != 3);
}

//Tracks a mail
void EmailSimulator::trackMail () const
{
	int mailID;
	string mailIDStr;

	cout<<"Enter the message ID: ";

	getline (cin, mailIDStr);
	mailID = atoi (mailIDStr.c_str ());

	cout<<endl;

	serverResources -> printMailDetails (mailID);
}

//Tracks a minute
void EmailSimulator::trackMin () const
{
	int min;
	string minStr;
	int maxMin = serverResources -> getTotalMins ();

	do
	{
		cout<<"Enter the minute u want to track (1 - "<<maxMin<<"): ";
		getline (cin, minStr);
		min = atoi (minStr.c_str ());

		if (min < 1 || min > maxMin)
			cout<<"Please enter from 1 to "<<maxMin<<" inclusive"<<endl;
	} while (min < 1 || min > maxMin);	//Ensures entry is valid

	cout<<endl;

	serverResources -> printMinDetails (min);
}

int main ()
{
	EmailSimulator emailSimulator;
	emailSimulator.main ();

	system ("pause");
	return 0;
}
