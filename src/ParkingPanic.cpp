//============================================================================
// Name        : ParkingPanic.cpp
// Author      : Al
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "ArrangementNode.h"
#include "VehicleStartDataTxt.h"
#include "Vehicle.h"
#include "refineArrangementSequence.cpp"

using namespace std;


string intVectorToString(vector<int> intVector) {
	ostringstream indicesStream;
	for (int intCtr = 0; intCtr < intVector.size(); intCtr++) {
		indicesStream << intVector[intCtr];
	}
	return indicesStream.str();
}

void writeAchievablePositionsToTxt(string txtFilePath, vector<Vehicle> allVehicles) {
	ofstream achievablePositionFile;
	achievablePositionFile.open(txtFilePath);
	for (int vehicleCtr = 0; vehicleCtr < allVehicles.size(); vehicleCtr++) {
		achievablePositionFile << allVehicles[vehicleCtr].returnAchievablePositionsString();
	}
	achievablePositionFile.close();
}


int main() {


	// Preparation Steps
	VehicleStartDataTxt vehicleStartDataTxt = VehicleStartDataTxt("level1.txt");

	vector< vector<int> > vehicleStartPositions = vehicleStartDataTxt.getVehicleStartPositions();

	vector<Vehicle> allVehicles = createAllVehicles(vehicleStartPositions);

	vector< vector< vector<int> > > allAchievablePositions = getAllAchievablePositions(allVehicles);

	writeAchievablePositionsToTxt("achievablePositionsWriteFile.txt", allVehicles);

	vector<int> initialSquaresOccupationStatus = returnInitialSquaresOccupationStatus(vehicleStartPositions);

	vector<int> initialVehiclePositionIndices = returnInitialVehiclePositionIndices(allVehicles);
	// end prep steps



	// Obtain sequence of arrangements that go from start to finish
	ArrangementNode activeArrangement = ArrangementNode(allAchievablePositions, initialVehiclePositionIndices);
	vector< vector<int> > unoptimizedSequence;
	while (activeArrangement.level != 4) {
		unoptimizedSequence.push_back(activeArrangement.vehiclePositionIndices);
		activeArrangement = activeArrangement.returnNextArrangement();
	}
	// end obtaining sequence of arrangements that go from start to finish


	// refine the sequence of arrangements to only necessary steps; write to txt file
	ofstream arrangementSequenceFileStream;
	arrangementSequenceFileStream.open("arrangementSequenceWriteFile.txt");
	vector< vector<int> > optimizedSequence = refineSequenceOfPositionIndices(unoptimizedSequence);
	for (int i = 0; i < optimizedSequence.size(); i++) {
		arrangementSequenceFileStream << intVectorToString(optimizedSequence[i]);
		arrangementSequenceFileStream << "\n";
	}
	arrangementSequenceFileStream.close();
	// end refine the sequence of arrangements to only necessary steps

	return 0;
}
