/*
 * ArrangementNode.cpp
 *
 *  Created on: Dec 12, 2016
 *      Author: alavery
 */
#include <iostream>
using namespace std;

#include "ArrangementNode.h"




vector< vector<int> > ArrangementNode::visitedIndicesCombos;







ArrangementNode::ArrangementNode(vector< vector< vector<int> > > allAchievablePositions, vector<int> vehiclePositionIndices, vector<int> squaresOccupationStatus) {
	this->allAchievablePositions = allAchievablePositions;
	this->vehiclePositionIndices = vehiclePositionIndices;
	this->level = vehiclePositionIndices[0];
	this->squaresOccupationStatus = squaresOccupationStatus;
}












void ArrangementNode::moveVehicle(int changedVehicleIndex, int moveDirection) {
	int newPositionIndex = this->vehiclePositionIndices[changedVehicleIndex] + moveDirection;
	this->setVehiclePositionIndices(changedVehicleIndex, newPositionIndex);
	this->setSquaresOccupationStatus(changedVehicleIndex, newPositionIndex);
}














void ArrangementNode::setVehiclePositionIndices(int changedVehicleIndex, int newPositionIndex) {
	this->vehiclePositionIndices[changedVehicleIndex] = newPositionIndex;
}












void ArrangementNode::setSquaresOccupationStatus(int changedVehicleIndex, int newPositionIndex) {
	int oldChangedVehiclePositionIndex = this->vehiclePositionIndices[changedVehicleIndex];
	vector <int> oldChangedVehiclePosition = this->allAchievablePositions[changedVehicleIndex][oldChangedVehiclePositionIndex];
	vector <int> newChangedVehiclePosition = this->allAchievablePositions[changedVehicleIndex][newPositionIndex];


	int squareLeft;
	int squareEntered;
	cout << newPositionIndex << endl;
	cout << oldChangedVehiclePositionIndex << endl;
	if (newPositionIndex > oldChangedVehiclePositionIndex) {
		squareLeft = oldChangedVehiclePosition[0];
		squareEntered = newChangedVehiclePosition[newChangedVehiclePosition.size() - 1];
	} else {
		squareLeft = oldChangedVehiclePosition[oldChangedVehiclePosition.size() - 1];
		squareEntered = newChangedVehiclePosition[0];
	}

	cout << "SqrEntered: " << squareEntered << "  " << flush;
	cout << "SqrLeft: " << squareLeft << "  " << endl;
	this->squaresOccupationStatus[squareLeft] = 0;
	this->squaresOccupationStatus[squareEntered] = 1;
}













bool ArrangementNode::testForVisited(int changedVehicleIndex, int newPositionIndex) {

	// make a copy of this->vehiclePositionIndices except with the changed Vehicle's index at its new value
	vector<int> positionIndicesToTest;
	for (int vehicleCtr = 0; vehicleCtr < this->vehiclePositionIndices.size(); vehicleCtr++) {
		if (vehicleCtr == changedVehicleIndex) {
			positionIndicesToTest.push_back(newPositionIndex);
		} else {
			positionIndicesToTest.push_back(this->vehiclePositionIndices[vehicleCtr]);
		}
	}

	// if positionIndicesToTest in this->visitedIndicesCombo, return false
	return true;
}






bool ArrangementNode::testPositionIndexIsValid(vector< vector<int> > changedVehiclesPositions, int newPositionIndex) {
	if (newPositionIndex < 0 || newPositionIndex == changedVehiclesPositions.size()) {
		return false;
	}
	return true;
}







bool ArrangementNode::testForOccupation(vector< vector<int> > changedVehiclesPositions, int newPositionIndex, int moveDirection) {

	vector<int> newPosition = changedVehiclesPositions[newPositionIndex];

	int newSquare;

	if (moveDirection == 1) {
		newSquare = newPosition[newPosition.size() - 1];
	}
	else {
		newSquare = newPosition[0];
	}

	if (this->squaresOccupationStatus[newSquare] == 1) {
		return false;
	} else return true;
}








bool ArrangementNode::testMove(int changedVehicleIndex, int moveDirection) {

	int newPositionIndex = this->vehiclePositionIndices[changedVehicleIndex] + moveDirection;
	vector< vector<int> > changedVehiclesPositions = this->allAchievablePositions[changedVehicleIndex];

	if (this->testPositionIndexIsValid(changedVehiclesPositions, newPositionIndex)) {
		if (this->testForOccupation(changedVehiclesPositions, newPositionIndex, moveDirection)) {
			if (this->testForVisited(changedVehicleIndex, newPositionIndex)) {
				return true;
			}
		}
	}
	return false;
}












vector<int> ArrangementNode::returnInfoForNextMove() {

	/* This function contains the core algorithm for the program.
	* The function returns vector of {index of vehicle to move, 1 or -1 for
	* direction to move it}.  e.g. {2, -1} is translated to "move vehicle at
	* index 2 backwards."  Also, it can return vector of {0, 0}, which will be
	* interpreted as 'no valid move existing from this Arrangement.'
	*
	* The algorithm consists of four sequential questions.  If the answer to any
	* question is yes, return a vector indicating that such is the case.  If the
	* answer to all four is no, return the {0, 0} vector.
	* The four questions are:
	* 	(1) Can we move hero vehicle forward (i.e., toward the exit)?
	* 	(2) Can we move any other vehicle forward?
	* 		- (Note that 'forward' is really arbitrary for all but the hero;
	* 		-  we actually have no preference which direction we move them)
	* 	(3) Can we move any other vehicle backward?
	* 	(4) Can we move the hero backward?
	*/

	vector<int> returnVector;

	// (1) Can we move hero vehicle forward (i.e., toward the exit)?
	if (this->testMove(0, 1)) {
		returnVector.push_back(0);
		returnVector.push_back(1);
		return returnVector;
	}


	// (2) Can we move any other vehicle forward?
	for (int vehicleCtr = 1; vehicleCtr < this->vehiclePositionIndices.size(); vehicleCtr++) {
		if (this->testMove(vehicleCtr, 1)) {
			returnVector.push_back(vehicleCtr);
			returnVector.push_back(1);
			return returnVector;
		}
	}


	// (3) Can we move any other vehicle backward?
	for (int vehicleCtr = 1; vehicleCtr < this->vehiclePositionIndices.size(); vehicleCtr++) {
		if (this->testMove(vehicleCtr, -1)) {
			returnVector.push_back(vehicleCtr);
			returnVector.push_back(-1);
			return returnVector;
		}
	}



	// (4) Can we move the hero backward?
	if (this->testMove(0, -1)) {
		returnVector.push_back(0);
		returnVector.push_back(-1);
		return returnVector;
	}



	// (...) Nothing worked; return the vector indicating such
	returnVector.push_back(0);
	returnVector.push_back(0);
	return returnVector;
}










ArrangementNode ArrangementNode::returnChildArrangementNode(int changedVehicleIndex, int moveDirection) {
	// ArrangementNode childArrangementNode = ArrangementNode(this, this->allAchievablePositions, this->vehiclePositionIndices, this->squaresOccupationStatus);


	ArrangementNode childArrangementNode = ArrangementNode(this->allAchievablePositions, this->vehiclePositionIndices, this->squaresOccupationStatus);

	childArrangementNode.moveVehicle(changedVehicleIndex, moveDirection);
	return childArrangementNode;
}













ArrangementNode ArrangementNode::returnNextArrangement() {

	visitedIndicesCombos.push_back(vehiclePositionIndices);
	vector<int> infoForNextMove = this->returnInfoForNextMove();
//	if (infoForNextMove[1] == 0) {
//		return this->parent;
//	}

	ArrangementNode childNode = this->returnChildArrangementNode(infoForNextMove[0], infoForNextMove[1]);
	return childNode;
}














void ArrangementNode::printNode() {

	cout << endl << "squaresOccupationStatus: " << flush;
	for (int squareCtr = 0; squareCtr < 36; squareCtr++) {
		cout << this->squaresOccupationStatus[squareCtr] << flush;
	}

	cout << endl << "vehiclePositionIndices: " << flush;
	for (int vehicleCtr = 0; vehicleCtr < this->vehiclePositionIndices.size(); vehicleCtr++) {
		cout << this->vehiclePositionIndices[vehicleCtr] << flush;
	}
	cout << endl << "Vehicle Positions: " << flush;
	for (int vehicleCtr = 0; vehicleCtr < this->vehiclePositionIndices.size(); vehicleCtr++) {
		for (int squareCtr = 0; squareCtr < this->allAchievablePositions[vehicleCtr][0].size(); squareCtr++) {
			cout << this->allAchievablePositions[vehicleCtr][vehiclePositionIndices[vehicleCtr]][squareCtr] << "-" << flush;
		}
		cout << "  " << flush;
	}
	cout << endl << "visitedIndicesCombos: " << flush;
	for (int visitedCtr = 0; visitedCtr < visitedIndicesCombos.size(); visitedCtr++) {
		for (int vehicleCtr = 0; vehicleCtr < this->vehiclePositionIndices.size(); vehicleCtr++) {
			cout << visitedIndicesCombos[visitedCtr][vehicleCtr] << flush;
		}
		cout << "  " << flush;
	}
	cout << endl;
}











vector<int> returnInitialSquaresOccupationStatus(vector< vector<int> > vehicleStartPositions) {
	vector<int> squaresOccupationStatus;
	for (int squareCtr = 0; squareCtr < 36; squareCtr++) {
		squaresOccupationStatus.push_back(0);
	}
	for (int vehicleCtr = 0; vehicleCtr < vehicleStartPositions.size(); vehicleCtr++) {
		for (int squareCtr = 0; squareCtr < vehicleStartPositions[vehicleCtr].size(); squareCtr++) {
			squaresOccupationStatus[vehicleStartPositions[vehicleCtr][squareCtr]] = 1;
		}
	}

	return squaresOccupationStatus;
}












vector<int> returnInitialVehiclePositionIndices(vector<Vehicle> vehicles) {
	vector<int> initialVehiclePositionIndices;
	for (int vehicleCtr = 0; vehicleCtr < vehicles.size(); vehicleCtr++) {
		initialVehiclePositionIndices.push_back(vehicles[vehicleCtr].getStartingPositionIndex());
	}
	return initialVehiclePositionIndices;
}







