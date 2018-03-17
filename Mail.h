//Filename:		Mail.h
//Name:			Tan Shi Terng Leon
//Declaration:	I did not pass my program to anyone in the class or copy anyone's work 
//				and I am willing to accept whatever penalty given to me and also to all
//				related parties involved
#include <vector>
#include <iostream>
using namespace std;

class Mail
{
public:
	Mail(void);
	Mail(int, int, int);	//Constructor also sets id and the time arrived
	~Mail(void);

	//Accessor functions
	int getID () const;					//Gets the id of the mail
	int getMinArrived () const;			//Gets the minute it arrived
	int getSecArrived () const;			//Gets the second it arrived
	int getTimeArrived () const;		//Gets the time in second it arrived
	int getMinSent () const;			//Gets the minute it is sent
	int getSecSent () const;			//Gets the second it is sent
	int getTimeSent () const;			//Gets the time in seconds it is sent
	int getNumOfTimesRequeued () const;	//Gets the number of time it is requeued
	int getTimeRequeued (int) const;	//Gets the time it is requeued

	void setTimeSent (int, int);		//Sets the time it was sent
	void addTimeRequeued (int);			//Adds the time it is requeued

	bool hasBeenSent () const;			//Checks if message have been sent
	int timeTakenToSend () const;		//Returns the number of seconds it took to send

	void printMailDetails () const;		//Prints the details of the mail

private:
	int id;						//The ID of the message
	int minArrived, secArrived;	//The minute and second the message arrived respectively
	int minSent, secSent;		//The minute and second the message was sent respectively
	int timeArrived;			//The time in seconds the message arrived
	int timeSent;				//The time in seconds the message was sent
	vector<int> timeRequeued;	//The time a message is requeued

};
