/*
 * Vehicle.h
 *
 *  Created on: Dec 19, 2016
 *      Author: alavery
 */

#include <vector>
#include <fstream>
using namespace std;

#ifndef VEHICLE_H_
#define VEHICLE_H_




class Vehicle {


private:

	int vehicleLength;

	vector<int> startingPosition; // e.g. {12, 13}

	vector<int> traversedRowOrColumn; // e.g. {0, 6, 12, 18, 24, 30}

	vector< vector<int> > achievablePositions; // e.g: { {0, 1}, {1, 2}, {2, 3}, {3, 4} }

	int startingPositionIndex;

	int identifyTraversedRowColumnIndex();

	void assignAchievablePositions();

	void assignStartingPositionIndex();

public:

	static int ARR_ROWS_AND_COLUMNS[12][6];

	vector< vector<int> > VEC_ROWS_AND_COLUMNS; // should be static...

	Vehicle(vector<int> startingPosition);

	int getStartingPositionIndex();

	vector <vector<int> > getAchievablePositions();

	string returnAchievablePositionsString();

	void printVehicle();
};




vector<Vehicle> createAllVehicles(vector< vector<int> > vehicleStartPositions);

vector< vector< vector<int> > > getAllAchievablePositions(vector<Vehicle> vehicles);


#endif /* VEHICLE_H_ */
