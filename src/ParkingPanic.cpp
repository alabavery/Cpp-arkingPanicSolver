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




void writeAchievablePositionsToTxt(string txtFilePath, vector<Vehicle> allVehicles) {
	ofstream achievablePositionFile;
	achievablePositionFile.open(txtFilePath);
	for (int vehicleCtr = 0; vehicleCtr < allVehicles.size(); vehicleCtr++) {
		achievablePositionFile << allVehicles[vehicleCtr].returnAchievablePositionsString();
	}
	achievablePositionFile.close();
}


int main() {

	VehicleStartDataTxt vehicleStartDataTxt = VehicleStartDataTxt("level1.txt");
	vector< vector<int> > vehicleStartPositions = vehicleStartDataTxt.getVehicleStartPositions();

	vector<Vehicle> allVehicles = createAllVehicles(vehicleStartPositions);

	vector< vector< vector<int> > > allAchievablePositions = getAllAchievablePositions(allVehicles);
	writeAchievablePositionsToTxt("achievablePositionsWriteFile.txt", allVehicles);

	vector<int> initialVehiclePositionIndices = returnInitialVehiclePositionIndices(allVehicles);


	vector< vector<int> > unoptimizedSequence = returnUnoptimizedSequenceOfPositionIndices(allAchievablePositions, initialVehiclePositionIndices);

	vector< vector<int> > optimizedSequence = refineSequenceOfPositionIndices(unoptimizedSequence);
	writeArrangementSequenceToFile(optimizedSequence, "arrangementSequenceWriteFile.txt");

	return 0;
}
