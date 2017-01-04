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


int main() {

	VehicleStartDataTxt vehicleStartDataTxt = VehicleStartDataTxt("level1.txt");
	vector< vector<int> > vehicleStartPositions = vehicleStartDataTxt.getVehicleStartPositions();


	vector<Vehicle> allVehicles = createAllVehicles(vehicleStartPositions);
	ofstream achievablePositionFile;
	achievablePositionFile.open("achievablePositionsWriteFile.txt");
	for (int vehicleCtr = 0; vehicleCtr < allVehicles.size(); vehicleCtr++) {
		achievablePositionFile << allVehicles[vehicleCtr].returnAchievablePositionsString();
	}
	achievablePositionFile.close();

	vector< vector< vector<int> > > allAchievablePositions = getAllAchievablePositions(allVehicles);

	vector<int> initialSquaresOccupationStatus = returnInitialSquaresOccupationStatus(vehicleStartPositions);
	vector<int> initialVehiclePositionIndices = returnInitialVehiclePositionIndices(allVehicles);


	ArrangementNode activeArrangement = ArrangementNode(allAchievablePositions, initialVehiclePositionIndices);

	ofstream myfile;
	myfile.open("arrangementSequenceWriteFile.txt");

	vector< vector<int> > unoptimizedSequence;
	while (activeArrangement.level != 4) {
		unoptimizedSequence.push_back(activeArrangement.vehiclePositionIndices);
		activeArrangement = activeArrangement.returnNextArrangement();
//		myfile << activeArrangement.positionIndicesToString();
//		myfile << "\n";
	}


	vector< vector<int> > optimizedSequence = refineSequenceOfPositionIndices(unoptimizedSequence);
	for (int i = 0; i < optimizedSequence.size(); i++) {
		myfile << intVectorToString(optimizedSequence[i]);
		myfile << "\n";
	}
	myfile.close();
	return 0;
}
