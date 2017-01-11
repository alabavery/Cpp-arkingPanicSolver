/*
 * ArrangementNode.cpp
 *
 *  Created on: Dec 12, 2016
 *      Author: alavery
 */
#include <iostream>
#include <sstream>
#include "ArrangementNode.h"


vector< vector<int> > ArrangementNode::visitedIndicesCombos;
vector< vector<int> > ArrangementNode::vehiclePositionIndicesStack;









ArrangementNode::ArrangementNode(vector< vector< vector<int> > > allAchievablePositions, vector<int> vehiclePositionIndices) {
	this->allAchievablePositions = allAchievablePositions;
	this->vehiclePositionIndices = vehiclePositionIndices;
	this->level = vehiclePositionIndices[0];
	this->squaresOccupationStatus = this->getSqrOccStatusFromPositionIndices(vehiclePositionIndices);
}









vector<int> ArrangementNode::getSqrOccStatusFromPositionIndices(vector<int> vehiclePositionIndices) {
	vector<int> squaresOccupationStatus;
	for (int squareCtr = 0; squareCtr < 36; squareCtr++) {
		squaresOccupationStatus.push_back(0);
	}
	for (int vehicleCtr = 0; vehicleCtr < vehiclePositionIndices.size(); vehicleCtr++) {
		vector< vector<int> > thisVehicleAchievablePositions = this->allAchievablePositions[vehicleCtr];
		vector <int> thisVehiclePosition = thisVehicleAchievablePositions[vehiclePositionIndices[vehicleCtr]];
		for (int squareCtr = 0; squareCtr < thisVehiclePosition.size(); squareCtr++) {
			squaresOccupationStatus[thisVehiclePosition[squareCtr]] = 1;
		}
	}

	return squaresOccupationStatus;
}










void ArrangementNode::moveVehicle(int changedVehicleIndex, int moveDirection) {
	int newPositionIndex = this->vehiclePositionIndices[changedVehicleIndex] + moveDirection;
	this->setVehiclePositionIndices(changedVehicleIndex, newPositionIndex);

	this->squaresOccupationStatus = this->getSqrOccStatusFromPositionIndices(this->vehiclePositionIndices);
}
















void ArrangementNode::setVehiclePositionIndices(int changedVehicleIndex, int newPositionIndex) {
	this->vehiclePositionIndices[changedVehicleIndex] = newPositionIndex;
}






















bool ArrangementNode::testForVisited(int changedVehicleIndex, int newPositionIndex) {

	vector<int> positionIndicesToTest;
	for (int vehicleCtr = 0; vehicleCtr < this->vehiclePositionIndices.size(); vehicleCtr++) {
		if (vehicleCtr == changedVehicleIndex) {
			positionIndicesToTest.push_back(newPositionIndex);
		} else {
			positionIndicesToTest.push_back(this->vehiclePositionIndices[vehicleCtr]);
		}
	}

	// if positionIndicesToTest in this->visitedIndicesCombo, return false
	for (int visitedCtr = 0; visitedCtr < this->visitedIndicesCombos.size(); visitedCtr++) {
		if (positionIndicesToTest == this->visitedIndicesCombos[visitedCtr]) {
			return false;
		}
	}
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










ArrangementNode ArrangementNode::returnNewArrangementNode(int changedVehicleIndex, int moveDirection) {
	ArrangementNode newArrangementNode = ArrangementNode(this->allAchievablePositions, this->vehiclePositionIndices);

	newArrangementNode.moveVehicle(changedVehicleIndex, moveDirection);
	return newArrangementNode;
}













ArrangementNode ArrangementNode::returnNextArrangement() {

	visitedIndicesCombos.push_back(vehiclePositionIndices);

	vector<int> infoForNextMove = this->returnInfoForNextMove();
	if (infoForNextMove[1] == 0) {

		vector<int> previousVehiclePositionIndices = this->vehiclePositionIndicesStack[this->vehiclePositionIndicesStack.size() - 1];
		ArrangementNode previousArrangement = ArrangementNode(this->allAchievablePositions, previousVehiclePositionIndices);

		this->vehiclePositionIndicesStack.pop_back();
		return previousArrangement;

	} else {
		this->vehiclePositionIndicesStack.push_back(this->vehiclePositionIndices);
		return this->returnNewArrangementNode(infoForNextMove[0], infoForNextMove[1]);
	}
}









string ArrangementNode::positionIndicesToString() {
	ostringstream indicesStream;
	for (int vehicleCtr = 0; vehicleCtr < this->vehiclePositionIndices.size(); vehicleCtr++) {
		indicesStream << this->vehiclePositionIndices[vehicleCtr];
	}
	return indicesStream.str();
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
	cout << endl << "vehiclePositionIndicesStack: " << flush;
	for (int stackCtr = 0; stackCtr < vehiclePositionIndicesStack.size(); stackCtr++) {
		for (int vehicleCtr = 0; vehicleCtr < this->vehiclePositionIndices.size(); vehicleCtr++) {
			cout << vehiclePositionIndicesStack[stackCtr][vehicleCtr] << flush;
		}
		cout << "  " << flush;
	}
	cout << endl;
}






















vector<int> returnInitialVehiclePositionIndices(vector<Vehicle> vehicles) {
	vector<int> initialVehiclePositionIndices;
	for (int vehicleCtr = 0; vehicleCtr < vehicles.size(); vehicleCtr++) {
		initialVehiclePositionIndices.push_back(vehicles[vehicleCtr].getStartingPositionIndex());
	}
	return initialVehiclePositionIndices;
}









vector< vector<int> > returnUnoptimizedSequenceOfPositionIndices(vector< vector< vector<int> > > allAchievablePositions, vector<int> initialVehiclePositionIndices) {

	ArrangementNode activeArrangement = ArrangementNode(allAchievablePositions, initialVehiclePositionIndices);
	vector< vector<int> > unoptimizedSequence;
	while (activeArrangement.level != 4) {
		unoptimizedSequence.push_back(activeArrangement.vehiclePositionIndices);
		activeArrangement = activeArrangement.returnNextArrangement();
	}

	return unoptimizedSequence;
}
