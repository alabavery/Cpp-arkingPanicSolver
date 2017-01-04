/*
 * Vehicle.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: alavery
 */
#include <iostream>
#include <vector>
# include "Vehicle.h"

# include <sstream>

using namespace std;




int Vehicle::ARR_ROWS_AND_COLUMNS[12][6] = {
		// ROWS
		{0, 1, 2, 3, 4, 5},
		{6, 7, 8, 9, 10, 11},
		{12, 13, 14, 15, 16, 17},
		{18, 19, 20, 21, 22, 23},
		{24, 25, 26, 27, 28, 29},
		{30, 31, 32, 33, 34, 35},
		// COLUMNS
		{0, 6, 12, 18, 24, 30},
		{1, 7, 13, 19, 25, 31},
		{2, 8, 14, 20, 26, 32},
		{3, 9, 15, 21, 27, 33},
		{4, 10, 16, 22, 28, 34},
		{5, 11, 17, 23, 29, 35},
};






Vehicle::Vehicle(vector<int> startingPosition) {

	this->startingPosition = startingPosition;

	this->vehicleLength = startingPosition.size();

	{ // fill rows and columns vector with values from ros and columns array.  This is
		// obviously not the best way to do it, since the vector should rally be static
		// and should not be declared each time in the constructor.  Try to fix...
	for (int i = 0; i < 12; i++) {
		vector<int> rowOrColumn;
		for (int j = 0; j < 6; j++) {
			rowOrColumn.push_back(this->ARR_ROWS_AND_COLUMNS[i][j]);
		}
		// vector<int> rowOrColumn (ARR_ROWS_AND_COLUMNS[i], ARR_ROWS_AND_COLUMNS[i] + sizeof(ARR_ROWS_AND_COLUMNS[i])/ARR_ROWS_AND_COLUMNS[i][0]);
		this->VEC_ROWS_AND_COLUMNS.push_back(rowOrColumn);
	}
	} // fill rows and columns vector with values from ros and columns array


	int traversedRowOrColumnIndex = this->identifyTraversedRowColumnIndex();
	this->traversedRowOrColumn = this->VEC_ROWS_AND_COLUMNS[traversedRowOrColumnIndex];
	this->assignAchievablePositions();
	this->assignStartingPositionIndex();
}







int Vehicle::identifyTraversedRowColumnIndex() {
	for (int rowColumnCounter = 0; rowColumnCounter < 12; rowColumnCounter++) {
		for (int squareCounter = 0; squareCounter < 6; squareCounter++) {
			if (this->startingPosition[0] == this->VEC_ROWS_AND_COLUMNS[rowColumnCounter][squareCounter]) {
				for (int squareCounter = 0; squareCounter < 6; squareCounter++) {
					if (this->startingPosition[1] == this->VEC_ROWS_AND_COLUMNS[rowColumnCounter][squareCounter]) {
						return rowColumnCounter;
					}
				}
			}
		}
	}
}







void Vehicle::assignAchievablePositions() {
	int limit = 6 - this->vehicleLength;

	for (int assignedPositionsCounter = 0; assignedPositionsCounter <= limit; assignedPositionsCounter++) {
		vector<int> thisPosition;

		for (int squareCounter = 0; squareCounter < this->vehicleLength; squareCounter++) {
			thisPosition.push_back(this->traversedRowOrColumn[assignedPositionsCounter+squareCounter]);
		}
		this->achievablePositions.push_back(thisPosition);
	}
}







void Vehicle::assignStartingPositionIndex() {
	for (int positionCounter = 0; positionCounter < this->achievablePositions.size(); positionCounter++) {
		if (this->achievablePositions[positionCounter] == this->startingPosition) {
			this->startingPositionIndex = positionCounter;
		}
	}
}








void Vehicle::printVehicle() {
	cout << "--------------------------------" << endl;
	cout << "Length: " << this->vehicleLength << endl;

	cout << "Starting Position: " << flush;
	for (int squareCounter = 0; squareCounter < this->vehicleLength; squareCounter++) {
		cout << this->startingPosition[squareCounter] << " ";
	}
	cout << "\n";
	cout << "traversedRowOrColumn: " << flush;
	for (int squareCounter = 0; squareCounter < 6; squareCounter++) {
		cout << this->traversedRowOrColumn[squareCounter] << " " << flush;
	}
	cout << "achievablePositions: " << flush;
	for (int positionCounter = 0; positionCounter < 6 - this->vehicleLength; positionCounter++) {
		for (int squareCounter = 0; squareCounter < this->vehicleLength; squareCounter++) {
			cout << this->achievablePositions[positionCounter][squareCounter] << " " << flush;
		}
		cout << "| " << flush;
	}
	cout << endl;
}



string Vehicle::returnAchievablePositionsString() {
	ostringstream oss;
	for (int positionCounter = 0; positionCounter < 7 - this->vehicleLength; positionCounter++) {
		for (int squareCounter = 0; squareCounter < this->vehicleLength; squareCounter++) {
			oss << this->achievablePositions[positionCounter][squareCounter] << " ";
		}
		oss << "|";
	}
	oss << "\n";
	return oss.str();
}




int Vehicle::getStartingPositionIndex() {
	return this->startingPositionIndex;
}


vector< vector<int> > Vehicle::getAchievablePositions() {
	return this->achievablePositions;
}




vector<Vehicle> createAllVehicles(vector< vector<int> > vehicleStartPositions) {
	vector<Vehicle> allVehicles;
	for (int vehicleCounter = 0; vehicleCounter < vehicleStartPositions.size(); vehicleCounter++) {
		allVehicles.push_back(Vehicle(vehicleStartPositions[vehicleCounter]));
	}
	return allVehicles;
}





vector< vector< vector<int> > > getAllAchievablePositions(vector<Vehicle> vehicles) {
	vector< vector< vector<int> > > allAchievablePositions;
	for (int vehicleCounter = 0; vehicleCounter < vehicles.size(); vehicleCounter++) {
		allAchievablePositions.push_back(vehicles[vehicleCounter].getAchievablePositions());
	}
	return allAchievablePositions;
}
