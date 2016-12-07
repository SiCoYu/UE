#pragma once

#include "CreateAndLinkDLLFile.h"


//Exported method that invertes a given boolean
bool DLL_EXPORT getInvertedBool(bool boolState)
{
	return bool(!boolState);
}

//Exported method that iterates a given int value
int DLL_EXPORT getIntPlusPlus(int lastInt)
{
	return int(++lastInt);
}

//Exported method that calculates the are of a circle by a given radius
float DLL_EXPORT getCircleArea(float radius)
{
	return float(3.1416f * (radius * radius));
}


//BUGGY: Exported method that adds a string to a given string
std::string DLL_EXPORT getAdditionalString(std::string baseString)
{
	std::string additionalString = baseString + " + AdditionalStringFromDLL";
	
	return std::string(additionalString);
}