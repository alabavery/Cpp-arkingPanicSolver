//============================================================================
// Name        : ParkingPanic.cpp
// Author      : Al
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

#include "ArrangementNode.h"
#include "VehicleStartDataTxt.h"
#include "Vehicle.h"

using namespace std;

int main() {

	VehicleStartDataTxt vehicleStartDataTxt = VehicleStartDataTxt("level1.txt");
	vector< vector<int> > vehicleStartPositions = vehicleStartDataTxt.getVehicleStartPositions();


	vector<Vehicle> allVehicles = createAllVehicles(vehicleStartPositions);

	vector< vector< vector<int> > > allAchievablePositions = getAllAchievablePositions(allVehicles);

	vector<int> initialSquaresOccupationStatus = returnInitialSquaresOccupationStatus(vehicleStartPositions);
	vector<int> initialVehiclePositionIndices = returnInitialVehiclePositionIndices(allVehicles);


	ArrangementNode activeArrangement = ArrangementNode(allAchievablePositions, initialVehiclePositionIndices, initialSquaresOccupationStatus);
	activeArrangement.printNode();
	activeArrangement = activeArrangement.returnNextArrangement();
	activeArrangement.printNode();
	activeArrangement = activeArrangement.returnNextArrangement();
	activeArrangement.printNode();


//	while (activeArrangement.level != 2) {
//		activeArrangement = activeArrangement.returnNextArrangement();
//		activeArrangement.printNode();
//	}

	return 0;
}
