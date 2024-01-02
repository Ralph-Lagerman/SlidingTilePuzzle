#include <queue>
#include "position.cpp"
#include <iostream>
#include <unordered_set>
//AStar algorithm
std::string AStar(int* board) {

	//Setting up variables, SQueue and VSet
	int nodes = 0, holeLoc;
	std::priority_queue<position,std::vector<position>,helper> SQueue; 
	std::unordered_set<position,helper> VSet; 

	//Setting up position variables and pushing to the queue
	position current(board, "");
	position New = current;
	SQueue.push(current);

	//Main while loop, terminates if we deplete the queue or try 30000 nodes
	while (!SQueue.empty() && nodes < 30000) {
		
		//Get top of priority queue (Lowest Score Position)
		current = SQueue.top();
		SQueue.pop();

		//If it is the answer Hooray, return
		if (current.isAnswer()) return current.getPath();

		//If the position has not already been considered, consider it
		if (VSet.find(current) == VSet.end()) {
			
			//Add to closed set and incriment nodes
			VSet.insert(current);
			nodes++;

			//Find the position's hole, based on this we can decide
			//Which moves will be legal
			holeLoc = current.getHole();
			if (holeLoc > 2) { //If hole is in the bottom two rows
				New = current;
				New.move('U'); //We can move up
				if (VSet.find(New) == VSet.end()) SQueue.push(New);
			}
			if (holeLoc < 6) { //If hole is in the top two rows
				New = current;
				New.move('D'); //We can move down
				if (VSet.find(New) == VSet.end()) SQueue.push(New);
			}
			if (holeLoc % 3 < 2) { //If hole is in the left two columns
				New = current;
				New.move('R');	   //We can move right
				if (VSet.find(New) == VSet.end()) SQueue.push(New);
			}
			if (holeLoc % 3 > 0) { //If hole is in the right two columns
				New = current;
				New.move('L');	   //We can move left
				if (VSet.find(New) == VSet.end()) SQueue.push(New);
			}
		}
	} //If we exit the loop we have not found an answer
	return "No solution found";
}

int main() {
	int puzzles[15][9] = {
		{1,2,3,4,0,5,7,8,6},
		{1,2,3,7,4,5,0,8,6},
		{1,2,3,4,8,0,7,6,5},
		{4,1,3,7,2,6,5,8,0},
		{1,6,2,5,3,0,4,7,8},
		{5,1,2,6,3,0,4,7,8},
		{1,2,6,3,5,0,4,7,8},
		{3,5,6,1,4,8,0,7,2},
		{4,3,6,8,7,1,0,5,2},
		{3,0,2,6,5,1,4,7,8},
		{0,1,2,3,4,5,6,7,8},
		{5,0,3,2,8,4,6,7,1},
		{8,7,4,3,2,0,6,5,1},
		{8,7,6,5,4,3,0,2,1},
		{8,7,6,5,4,3,2,1,0}
	};
	for (int i = 0; i < 15; i++) {
		std::cout << "Answer to puzzle #(" << i + 1 << ") - > ";
		std::cout << AStar(puzzles[i]) << std::endl;
	}
	return 0;
}