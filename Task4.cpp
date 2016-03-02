#include <time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

// Stores information about a domino
struct dataDomino {
	int right, left, available;
};

// Contains method for getting a random integer. (Should be static)
static class CRandom
{
public:
	// Generates uniform distribution between rangeLow and rangeHigh
	static int GetRandomPublic(int rangeLow, int rangeHigh) {
		double myRand = rand() / (1.0 + RAND_MAX);
		int range = rangeHigh - rangeLow + 1;
		int myRand_scaled = (myRand * range) + rangeLow;
		return myRand_scaled;
	}
};

// Shows/Displays the sorted pieces
class CTable
{
public:
	CTable();
	~CTable();
	bool PlaceDominoOnHead(dataDomino*);
	bool PlaceDominoOnTail(dataDomino*);
	void DisplayPlacedDominos();
	dataDomino* Head();
	dataDomino* Tail();
	int placableHeadValue = -1;
	int placeableTailValue = -1;
private:
	deque<dataDomino*> placedDominoes;
};

// Contains the data structure with pieces
class CDominoes
{
public:
	CDominoes();
	~CDominoes();
	void InitializeDominoes(void);
	static void PrintDomino(dataDomino*);
	static void PrintDominoFlipped(dataDomino*);
	dataDomino* GetRandomPiece();
	vector<dataDomino*> allDominoes;
	vector<dataDomino*> availableDominoes;
private:
};

// Select a randomly picked domino and sequentially show the selected pieces
class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void TakeDomino(dataDomino*);
	bool PlaceDomino(CTable*, dataDomino*, bool);
	deque<dataDomino*> playerDominoes;
};

// Main class that handles domino game
class Task4
{
public:
	Task4();
	~Task4();
private:
	void API();
	void CreateDominoes();
	void DrawDominoes();
	int WhoFirst();
	void FirstPiece();
	void RunGame();
	void PlacementLoop(int currentPlayer);

	CTable *table;
	CDominoes *dominoes;
	CPlayer *players;

	const int STARTING_HAND_SIZE = 7;
	const int NUMBER_OF_PLAYERS = 2;
};

Task4::Task4()
{
	this->players = new CPlayer[NUMBER_OF_PLAYERS];
	this->table = new CTable;
	this->dominoes = new CDominoes;
	API();
};

Task4::~Task4()
{
	std::cout << "Deleting Task4 Object.";
	delete [] players;
	delete table;
	delete dominoes;
};

// Initializes the game and runs the loop until a winner is found
void Task4::API()
{
	CreateDominoes();
	DrawDominoes();
	FirstPiece();
	RunGame();
};

void Task4::CreateDominoes()
{
	dominoes->InitializeDominoes();
};

void Task4::DrawDominoes()
{
	for (int i = 0; i < STARTING_HAND_SIZE; i++)
	{
		for (int j = 0; j < NUMBER_OF_PLAYERS; j++)
		{
			dataDomino* piece = dominoes->GetRandomPiece();
			players[j].TakeDomino(piece);
		}
	}
};

int Task4::WhoFirst()
{
	int firstPlayer = CRandom::GetRandomPublic(0, NUMBER_OF_PLAYERS-1);
	return firstPlayer;
};

void Task4::FirstPiece()
{
	table->PlaceDominoOnHead(dominoes->GetRandomPiece());
};

void Task4::RunGame()
{
	bool endCheck = false;
	int currentPlayer = WhoFirst();
	do
	{
		// Loop until player successfully places domino
		PlacementLoop(currentPlayer);

		// Check for winner
		if (players[currentPlayer].playerDominoes.size() == 0)
		{
			endCheck = true;
			cout << "The winner is Player " << currentPlayer << "!";
		}
		/*else if (dominoes->availableDominoes.size() == 0)
		{
			cout << "Tie!" << endl;
			endCheck = true;
		}*/
		// Go to next player
		else if (currentPlayer == NUMBER_OF_PLAYERS - 1)
			currentPlayer = 0;
		else
			currentPlayer++;
	}while (!endCheck);
	// TODO handle tie situation?
};

CTable::CTable()
{
};

CTable::~CTable()
{
	std::cout << "Deleting CTable Object.";
}

// Places a domino on the head of the board
bool CTable::PlaceDominoOnHead(dataDomino * newHeadDomino)
{
	if (placableHeadValue != -1)
	{
		if (newHeadDomino->left == placableHeadValue)
		{
			placedDominoes.push_back(newHeadDomino);
			placableHeadValue = newHeadDomino->right;
			return true;
		}
		else if (newHeadDomino->right == placableHeadValue)
		{
			placedDominoes.push_back(newHeadDomino);
			placableHeadValue = newHeadDomino->left;
			return true;
		}
		else return false;
	}
	else
	{
		cout << "Placing first domino" << endl;
		placedDominoes.push_back(newHeadDomino);
		placableHeadValue = newHeadDomino->right;
		placeableTailValue = newHeadDomino->left;
		return true;

	}
}

// Places domino on tail of board
bool CTable::PlaceDominoOnTail(dataDomino * newTailDomino)
{
	if (newTailDomino->left == placeableTailValue)
	{
		placedDominoes.push_front(newTailDomino);
		placeableTailValue = newTailDomino->right;
		return true;
	}
	else if (newTailDomino->right == placeableTailValue)
	{
		placedDominoes.push_front(newTailDomino);
		placeableTailValue = newTailDomino->left;
		return true;
	}
	else return false;
}

// Print the board
void CTable::DisplayPlacedDominos()
{
	CDominoes::PrintDomino(placedDominoes.at(0));

	for (int i = 1; i < placedDominoes.size(); i++)
	{
		if (placedDominoes.at(i)->left != placedDominoes.at(i-1)->right)
			CDominoes::PrintDominoFlipped(placedDominoes.at(i));
		else CDominoes::PrintDomino(placedDominoes.at(i));
	}
	cout << endl;
}

dataDomino * CTable::Head()
{
	return placedDominoes.back();
}

dataDomino * CTable::Tail()
{
	return placedDominoes.front();
}

// Loops through until the current player places a domino
void Task4::PlacementLoop(int currentPlayer)
{
	int headOrTail, chosenSpot;
	char passCheck;

	bool done = false;
	do
	{
		headOrTail = -1;
		chosenSpot = -1;

		// Show the board
		table->DisplayPlacedDominos();
		cout << "Domino Head: " << table->placableHeadValue;
		cout << endl;
		cout << "Domino Tail: " << table->placeableTailValue;
		cout << endl;

		// Show player hand
		cout << "Here is Player " << currentPlayer << "'s hand:" << endl;
		for (int i = 0; i < players[currentPlayer].playerDominoes.size(); i++)
		{
			cout << "Domino " << i << ": ";
			CDominoes::PrintDomino(players[currentPlayer].playerDominoes.at(i));
			cout << endl;
		}
		
		// Prompt user to pass or not
		cout << "Enter P to pass, or anything else to continue.\nIf you pass and there are still dominoes available, \nyou will draw dominoes until you can place one:" << endl;
		cin >> passCheck;
		if (passCheck != 'P')
		{
			// Player chooses piece
			do
			{
				cin.clear();
				cin.ignore();
				cout << "Choose a piece: " << endl;
				cin >> chosenSpot;
				if (cin.fail())
				{
					cout << "Error. Invalid input." << endl;
				}
			} while (cin.fail() || chosenSpot >> 28 || chosenSpot < 0);

			// Player chooses to place on head or tail
			do
			{
				cin.clear();
				cin.ignore();
				cout << "Do you want to place on the head or tail? (1 or 0):" << endl;
				cin >> headOrTail;
				if (cin.fail())
				{
					cout << "Error: Invalid input." << endl;
				}
			} while (cin.fail() || headOrTail > 1 || headOrTail < 0);
			done = players[currentPlayer].PlaceDomino(table, players[currentPlayer].playerDominoes.at(chosenSpot), headOrTail);
			if (!done)
			{
				cout << "You can't place that domino there!" << endl;
			}
		}
		else
		{
			if (dominoes->availableDominoes.size() > 0)
			{
				players[currentPlayer].TakeDomino(dominoes->GetRandomPiece()); // Draw
			}
			else
			{
				done = true;
				cout << "Player " << currentPlayer << " passed." << endl;
			}	
		}
	} while (!done);
	cout << "Player " << currentPlayer << "'s turn has ended." << endl;
}

CDominoes::CDominoes()
{
};

CDominoes::~CDominoes()
{
	std::cout << "Deleting CDominoes Object.";
};

// Creates the domino objects at the beginning of the game
void CDominoes::InitializeDominoes(void) {

	for (int right = 0; right < 7; right++)
	{
		for (int left = 0; left < 7; left++)
		{
			dataDomino* piece = new dataDomino;
			piece->right = right;
			piece->left = left;
			piece->available = 1;

			allDominoes.push_back(piece);
			availableDominoes.push_back(piece);
		}
	}
	std::random_shuffle(availableDominoes.begin(), availableDominoes.end());
}

// Prints out a domino-looking object
void CDominoes::PrintDomino(dataDomino *piece)
{
	cout << "[" << piece->left << "|" << piece->right << "]";
};

// Prints out a flipped domino-looking object
void CDominoes::PrintDominoFlipped(dataDomino *piece)
{
	cout << "[" << piece->right << "|" << piece->left << "]";
};

// Randomly draws a piece. This is also used to start the game.
dataDomino* CDominoes::GetRandomPiece() {
	dataDomino* piece;

	piece = availableDominoes.back();
	availableDominoes.pop_back();
	piece->available = 0;

	std::cout << "Random piece drawn: ";
	PrintDomino(piece);
	cout << endl;

	return(piece);
};

CPlayer::CPlayer()
{
};

CPlayer::~CPlayer()
{
	std::cout << "Deleting CPlayer Object.";
};

// Grabs a domino from the pile and adds to the player's hand
void CPlayer::TakeDomino(dataDomino* newDomino)
{
	playerDominoes.push_back(newDomino);
};

// Handles placing a domino on the table
// Bool parameter decides if the domino is placed on the head or tail. (1 for head, 0 for tail)
// Returns true if the placement was successful.
bool CPlayer::PlaceDomino(CTable* table, dataDomino* domino, bool head)
{
	// Head
	if (head)
	{
		if (table->PlaceDominoOnHead(domino))
		{
			for (int i = 0; i < playerDominoes.size(); i++)
			{
				if (domino == playerDominoes.at(i))
				{
					playerDominoes.erase(playerDominoes.begin() + i);
				}
			}
			return true;
		}
		else return false;
	}
	// Tail
	else
	{
		if (table->PlaceDominoOnTail(domino))
		{
			for (int i = 0; i < playerDominoes.size(); i++)
			{
				if (domino == playerDominoes.at(i))
				{
					playerDominoes.erase(playerDominoes.begin() + i);
				}
			}
			return true;
		}
		else return false;
	}
}

int main(void)
{
	time_t timer;
	time(&timer);
	srand(timer);

	Task4 task4;
	return 0;
}
