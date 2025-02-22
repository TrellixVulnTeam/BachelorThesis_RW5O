#pragma once
#include "AnnealingSchedule.h"
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <sstream>

class Lineary :
	public AnnealingSchedule
{
public:
	Lineary();
	Lineary(double T_0, double mu);
	double getTemperature(int step);
	std::string getName();
	std::string getFunction();
private:
	double T_0;
	/**
	values of a fluctuate between 0.8 and 0.99.!!
	*/
	double mu;
};

