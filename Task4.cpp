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
	dataDomino* Head();
	dataDomino* Tail();
	int placableHeadValue;
	int placableTailValue;
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
	dataDomino* GetRandomPiece();
	vector<dataDomino*> allDominoes;
private:
	vector<dataDomino*> availableDominoes;
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
	dataDomino* ChooseDomino(int currentPlayer);
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
	void DominoPlacementOperation(int currentPlayer);

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

void Task4::API()
{
	CreateDominoes();
	DrawDominoes();
	WhoFirst();
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
		for (int j = 0; j < NUMBER_OF_PLAYERS; i++)
		{
			dataDomino* piece = dominoes->GetRandomPiece();
			players[j].TakeDomino(piece);
		}
	}
};

int Task4::WhoFirst()
{
	int firstPlayer = CRandom::GetRandomPublic(0, NUMBER_OF_PLAYERS);
	return firstPlayer;
};

void Task4::FirstPiece()
{
	table->PlaceDominoOnHead(dominoes->GetRandomPiece());
};

void Task4::RunGame()
{
	bool winner;
	int currentPlayer = WhoFirst();
	do
	{
		// Loop until player successfully places domino
		DominoPlacementOperation(currentPlayer);

		// Check for winner
		if (players[currentPlayer].playerDominoes.size() == 0)
			winner = true;
		// Go to next player
		else if (currentPlayer == NUMBER_OF_PLAYERS)
			currentPlayer = 0;
		else
			currentPlayer++;
	}while (!winner);
	cout << "The winner is Player " << currentPlayer;
};

CTable::CTable()
{
};

CTable::~CTable()
{
	std::cout << "Deleting CTable Object.";
}

bool CTable::PlaceDominoOnHead(dataDomino * newHeadDomino)
{
	//if (newHeadDomino->left == )
	placedDominoes.push_back(newHeadDomino);
}

bool CTable::PlaceDominoOnTail(dataDomino * newTailDomino)
{

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
void Task4::DominoPlacementOperation(int currentPlayer)
{
	int response;
	bool done;
	do
	{
		cout << "Do you want to place on the head or tail? (0 or 1):" << endl;
		cin >> response;
		done = players[currentPlayer].PlaceDomino(table, players[currentPlayer].ChooseDomino(currentPlayer), response);
	} while (!done);
}

CDominoes::CDominoes()
{
};

CDominoes::~CDominoes()
{
	std::cout << "Deleting CDominoes Object.";
};

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

void CDominoes::PrintDomino(dataDomino *piece)
{
	std::cout << "[" << piece->left << "|" << piece->right << "] \nStatus:  " << piece->available << endl;
};

dataDomino* CDominoes::GetRandomPiece() {
	dataDomino* piece;

	//do // This is gonna get messy...
	//{
	//	piece = allDominoes.at(CRandom::GetRandomPublic(0, allDominoes.size()));
	//}
	//while (piece->available != 1);

	piece = availableDominoes.back();
	availableDominoes.pop_back();
	piece->available = 0;

	std::cout << "Random piece drawn: ";
	PrintDomino(piece);

	return(piece);
};

CPlayer::CPlayer()
{
};

CPlayer::~CPlayer()
{
	std::cout << "Deleting CPlayer Object.";
};

void CPlayer::TakeDomino(dataDomino* newDomino)
{
	playerDominoes.push_back(newDomino);
};

bool CPlayer::PlaceDomino(CTable* table, dataDomino* domino, bool head)
{
	if (head)
	{
		if (table->PlaceDominoOnHead(domino))
			return true;
		else return false;
	}
	else
	{
		if (table->PlaceDominoOnTail(domino))
			return true;
		else return false;
	}
}
dataDomino * CPlayer::ChooseDomino(int currentPlayer)
{
	int chosenSpot;
	cout << "Here is Player " << currentPlayer << "'s hand:" << endl;
	for (int i = 0; i < playerDominoes.size(); i++)
	{
		cout << "Domino " << i << ": ";
		CDominoes::PrintDomino(playerDominoes.at(i));
	}

	cout << "Choose a piece: " << endl;
	cin >> chosenSpot;

	return playerDominoes.at(chosenSpot);
};

int main(void)
{
	time_t timer;
	time(&timer);
	srand(timer);

	Task4 task4;
	return 0;
}
