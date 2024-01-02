#include <string>
#include <math.h>
class position { //Helping class
	friend class helper;
public: // Public interface
	//Constructor
	position(int tiles[9], std::string moves) {
		for (int i = 0; i < 9; i++) this->tiles[i] = tiles[i];
		this->moves = moves;
		score = moves.length() + getMDistance();
	}
	//Accessor method to be used to retrieve the correct path
	std::string getPath() {
		return moves;
	}

	//Accessor method to find the location of the hole
	int getHole() {
		return hole;
	}

	//Method to determine if a position is in its final position
	bool isAnswer() {
		for (int i = 0; i < 8; i++)	if (tiles[i] != i + 1) return false;
		return true;
	}

	//Method to facilitate a move based on input character
	//'U' -> move UP, 'D' -> move DOWN, 'L' -> move LEFT , 'R' -> move RIGHT
	void move(char c) {
		moves += c;
		if (c == 'U')swap(hole, hole - 3);
		else if (c == 'D')swap(hole, hole + 3);
		else if (c == 'L')swap(hole, hole - 1);
		else if (c == 'R')swap(hole, hole + 1);
		score = moves.length() + getMDistance();
	}

	//Equality operator to be used by the hash table inside of VSet
	bool operator==(const position& other) const {
		for (int i = 0; i < 9; i++) if (this->tiles[i] != other.tiles[i]) return false;
		return true;
	}

private: //Private Data Members and helper functions

	//Manhattan distance finding function
	int getMDistance() {
		int MDistance = 0;
		for (int i = 0; i < 9; i++) { //Manhattan distance = change in rows + change in columns
			if (tiles[i] != 0) {
				MDistance += abs((i % 3) - ((tiles[i] - 1) % 3)); //Change in columns
				MDistance += abs((i / 3) - ((tiles[i] - 1) / 3)); //Change in rows
			}
			else hole = i; //While finding the Manhattan distance we can also find the hole for free :)
		}
		return MDistance;
	}

	//Helper function to faciliate moves
	void swap(int a, int b) {
		int temp = tiles[a];
		tiles[a] = tiles[b];
		tiles[b] = temp;
	}

	//Private Data members
	int hole;
	int score;
	int tiles[9];
	std::string moves;

};

//Class to help with comparisons for priority queue and hashing for unordered set
class helper {
public:
	bool operator()(const position& a, const position& b) { return (a.score > b.score); }
	size_t operator()(const position& p) const {
		int sum = 0, pow = 1;
		for (int i = 0; i < 9; i++) {
			sum += i * pow;
			pow *= 10;
		}
		return sum;
	}
};

