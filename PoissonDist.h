//Filename:		PoissonDist.h
//Name:			Tan Shi Terng Leon
//Declaration:	I did not pass my program to anyone in the class or copy anyone's work 
//				and I am willing to accept whatever penalty given to me and also to all
//				related parties involved
#include <cmath>

//Describes a poisson distribution
class PoissonDist
{
public:
	PoissonDist ();
	PoissonDist (double);
	
	//Gets the probabilty of getting a value
	double getProbability (int) const;

	//Gets the probability of getting a value between 2 given values
	double getProbability (int, int) const;

	//Returns the factorial of a number
	int factorial (int) const;

	//Sets the lambda of the poisson distribution
	void setLambda (double);

private:
	static const double e;
	double lambda;
};
