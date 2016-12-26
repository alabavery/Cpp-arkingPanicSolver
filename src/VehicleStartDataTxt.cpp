/*
 * VehicleStartDataTxt.cpp
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "VehicleStartDataTxt.h"
using namespace std;


VehicleStartDataTxt::VehicleStartDataTxt(string txtFileName) {
	this->txtFileName = txtFileName;

	string sz_squaresOccupiedByVehicle;
	this->numberOfVehicles = 0;

	ifstream txtFileStream (txtFileName);

	if (txtFileStream.is_open()) {
		while ( getline (txtFileStream, sz_squaresOccupiedByVehicle) ) {
			this->incrementNumberOfVehicles();
			this->addVehicleStartPosition(sz_squaresOccupiedByVehicle);
		}
		txtFileStream.close();
	}
	else {
		cout << "Unable to open" << endl;
	}
}

void VehicleStartDataTxt::incrementNumberOfVehicles() {
	this->numberOfVehicles++;
}


void VehicleStartDataTxt::addVehicleStartPosition(string sz_squaresOccupiedByVehicle) {
	stringstream squaresOccupiedByVehicleSStream (sz_squaresOccupiedByVehicle);
	vector<int> squaresOccupiedByVehicleVector;
	string aSquareOccupiedByVehicle;
	while ( getline (squaresOccupiedByVehicleSStream, aSquareOccupiedByVehicle, ' ') ) {
		int aSquareOccupiedByVehicleAsInt = std::stoi(aSquareOccupiedByVehicle);
		squaresOccupiedByVehicleVector.push_back(aSquareOccupiedByVehicleAsInt);
	}
	this->vehicleStartPositions.push_back(squaresOccupiedByVehicleVector);
}

int VehicleStartDataTxt::getNumberOfVehicles() {
	return this->numberOfVehicles;
}

vector< vector<int> > VehicleStartDataTxt::getVehicleStartPositions() {
	return this->vehicleStartPositions;
}

