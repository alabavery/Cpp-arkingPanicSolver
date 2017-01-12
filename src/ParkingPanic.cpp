//============================================================================
// Name        : ParkingPanic.cpp
// Author      : Al
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <fstream>
#include <sstream>

#include "ArrangementNode.h"
#include "VehicleStartDataTxt.h"
#include "Vehicle.h"
#include "refineArrangementSequence.cpp"






void writeAchievablePositionsToTxtFile(string txtFilePath, vector<Vehicle> allVehicles) {
	ofstream achievablePositionFile;
	achievablePositionFile.open(txtFilePath);
	for (int vehicleCtr = 0; vehicleCtr < allVehicles.size(); vehicleCtr++) {
		achievablePositionFile << allVehicles[vehicleCtr].returnAchievablePositionsString();
	}
	achievablePositionFile.close();
}




int main() {
	/*	This program reads from a text file that describes the starting positions of the
	*	vehicles for a given level of Parking Panic and writes to another text file a
	*	description of the moves needed to get from this start to the completion of the level.
	*	See VehicleStartData.h for details on the starting position text file.
	*	See refineArrangementSequence.cpp for details on the written text file.
	*
	*
	*	Terminology:
	*
	*		Vehicle 	-- A vehicle in the Parking Panic parking lot.  Program makes an object for
	*					each... see Vehicle.h
	*
	*		Hero 		-- the vehicle that we are trying to get to the exit (the red car)
	*
	*		Arrangement -- The way in which the vehicles are positioned across the parking lot
	*					at any given point in time.  An example in plain english: The hero is
	*					in the first square from the left in the second to top row, there is
	*					another car in the second square from the right in the bottom row, etc.
	*					...Not to be confused with ArrangementNode objects, which describe
	*					arrangements but include more data than just the positions of vehicles.
	*
	*		Vehicle's Achievable Positions -- All of the positions that the vehicle can inhabit
	*
	*		Position Index -- The index of a given position in a vehicle's achievable positions.
	*					The term 'vehicle position indices' will be used to denote the array
	*					of every vehicle's position index in a given arrangement.
	*/

	VehicleStartDataTxt vehicleStartDataTxt = VehicleStartDataTxt("level1.txt");
	vector< vector<int> > vehicleStartPositions = vehicleStartDataTxt.getVehicleStartPositions();

	vector<Vehicle> allVehicles = createAllVehicles(vehicleStartPositions);

	vector< vector< vector<int> > > allAchievablePositions = getAllAchievablePositions(allVehicles);
	writeAchievablePositionsToTxtFile("achievablePositionsWriteFile.txt", allVehicles);

	vector<int> initialVehiclePositionIndices = returnInitialVehiclePositionIndices(allVehicles);


	vector< vector<int> > unoptimizedSequence = returnUnoptimizedSequenceOfPositionIndices(allAchievablePositions, initialVehiclePositionIndices);

	vector< vector<int> > optimizedSequence = refineSequenceOfPositionIndices(unoptimizedSequence);
	writeArrangementSequenceToFile(optimizedSequence, "arrangementSequenceWriteFile.txt");

	return 0;
}
