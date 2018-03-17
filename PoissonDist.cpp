//Filename:		PoissonDist.cpp
//Name:			Tan Shi Terng Leon
//Declaration:	I did not pass my program to anyone in the class or copy anyone's work 
//				and I am willing to accept whatever penalty given to me and also to all
//				related parties involved
#include "PoissonDist.h"

const double PoissonDist::e = 2.7182818284;

//Default constructor
PoissonDist::PoissonDist ()
{
}

//Constructor
PoissonDist::PoissonDist (double lambda)
{
	this -> lambda = lambda;
}

//Gets the probablity for getting the value x
double PoissonDist::getProbability (int x) const
{
	double probability;
	probability = (pow(lambda, x) * pow(e, -lambda)) / factorial(x);

	return probability;
}

//Gets the probability for the getting the values between low and high inclusive
double PoissonDist::getProbability (int low, int high) const
{
	double probability = getProbability (low);

	for (int i = low + 1; i <= high; i++)
	{
		probability = probability + getProbability (i);
	}

	return probability;
}

//Returns the factorial of n
int PoissonDist::factorial (int n) const
{
	int fact;

	if (n == 0)
		fact = 1;
	else
	{
		fact = n;

		for (int i = n - 1; i > 0; i--)
			fact = fact * i;
	}

	return fact;
}

//Sets lambda of the poisson distribution
void PoissonDist::setLambda (double lambda)
{
	this -> lambda = lambda;
}
