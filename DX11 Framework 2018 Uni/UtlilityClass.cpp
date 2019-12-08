#include "UtlilityClass.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;



UtlilityClass::UtlilityClass()
{
}


UtlilityClass::~UtlilityClass()
{
}

bool Util::compareXMFLOAT3(XMFLOAT3 first, XMFLOAT3 second)
{
	if (first.x == second.x) {
		if (first.y == second.y) {
			if (first.z == second.z) {
				return true;
			}
		}
	}
	return false;
}



void Util::SaveToMeshPositionsToFile()
{
}
