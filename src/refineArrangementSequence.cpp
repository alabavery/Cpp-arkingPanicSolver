/*
 * writeArrangementSequenceToFile() (see function body below) writes to a text file the information
 * needed to describe the sequence of vehicle arrangements that take the parking lot
 * from its starting arrangement to an arrangement in which the hero vehicle is
 * exiting.  That information is in the form of a sequence of vehicle position indices.
 * Each line in the written text file is the position indices for one arrangement.  From one
 * line in the file to the next, exactly one position index will have changed.
 *
 * Combining the file written by writeArrangementSequenceToFile() and the file written by
 * writeAchievablePositionsToTxtFile() (see ParkingPanic.cpp for that function), the Python
 * script has enough information to display the solution to the level.
 */



bool testDirectMove(vector<int> positionIndices1, vector<int> positionIndices2) {
	int numOfDifferences = 0;
	for (int i = 0; i < positionIndices1.size(); i++) {

		int change = positionIndices1[i] - positionIndices2[i];
		if (abs(change) > 1) {
			return false;

		} else if (abs(change) == 1){
			numOfDifferences++;
			if (numOfDifferences > 1) {
				return false; // go ahead and return early since we can and it will increase speed
			}
		}
	}
	if (numOfDifferences == 0) {
		return false;
	}
	return true;
}









vector< vector<int> > refineSequenceOfPositionIndices(vector< vector<int> > unoptimizedSequence) {

	vector< vector<int> > optimizedSequence;
	optimizedSequence.push_back(unoptimizedSequence[0]);

	int latestMoveMarker = 0;
	int reverseCtr = unoptimizedSequence.size() - 1;

	while (true) {
		if (latestMoveMarker == unoptimizedSequence.size() - 1) {
			return optimizedSequence;
		}
		if (testDirectMove(unoptimizedSequence[latestMoveMarker], unoptimizedSequence[reverseCtr])) {
			optimizedSequence.push_back(unoptimizedSequence[reverseCtr]);
			latestMoveMarker = reverseCtr;
			reverseCtr = unoptimizedSequence.size() - 1;
		} else {
			reverseCtr--;
		}
	}
}









string intVectorToString(vector<int> intVector) {
	ostringstream indicesStream;
	for (int intCtr = 0; intCtr < intVector.size(); intCtr++) {
		indicesStream << intVector[intCtr];
	}
	return indicesStream.str();
}









void writeArrangementSequenceToFile(vector< vector<int> > optimizedSequence, string filePath) {
	ofstream arrangementSequenceFileStream;
	arrangementSequenceFileStream.open(filePath);
	for (int i = 0; i < optimizedSequence.size(); i++) {
		arrangementSequenceFileStream << intVectorToString(optimizedSequence[i]);
		arrangementSequenceFileStream << "\n";
	}
	arrangementSequenceFileStream.close();
}
