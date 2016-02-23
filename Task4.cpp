#include <time.h>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <deque>

using namespace std;

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
	void WhoFirst();
	void FirstPiece();
	void RunGame();

	CTable *table;
	CDominoes *dominoes;
	CPlayer *players;

	const int STARTING_HAND_SIZE = 7;
	const int NUMBER_OF_PLAYERS = 2;
};

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
	deque<dataDomino*> placedDominoes;
};

// Contains the data structure with pieces
class CDominoes
{
public:
	CDominoes();
	~CDominoes();
	void InitializeDominoes(void);
	void PrintDomino(dataDomino*);
	deque<dataDomino*> allDominoes;
	dataDomino* GetRandomPiece();
};

// Select a randomly picked domino and sequentially show the selected pieces
class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	deque<dataDomino*> playerDominoes;

private:
	void TakeDomino(dataDomino*);
	void PlaceDomino(CTable*, dataDomino*, int);
	// Current hand variable?
};

Task4::Task4()
{
	CPlayer *players = new CPlayer[NUMBER_OF_PLAYERS];
	CTable *table = new CTable;
	CDominoes *dominoes = new CDominoes;
	API();
};

Task4::~Task4()
{
	cout << "Deleting Task4 Object.";
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

};

void Task4::CreateDominoes()
{
	dominoes->InitializeDominoes();
};

void Task4::DrawDominoes()
{
	for (int i = 0; i < STARTING_HAND_SIZE; i++)
	{

	}
};

void Task4::WhoFirst()
{
	int firstPlayer = CRandom::GetRandomPublic(0, NUMBER_OF_PLAYERS);
};

void Task4::FirstPiece()
{
	// TODO draw a random piece and place it
};

void Task4::RunGame()
{
	// TODO Create loop that plays the game:
	// Check winner (end if there is a winner, empty hand)
	// next player
	// find piece match
	// can play? if yes, flip piece over if needed; place piece in train
	// if no, draw piece -> can draw? yes, go to find piece match
	// if no, pass
};

CTable::CTable()
{
};

CTable::~CTable()
{
	cout << "Deleting CTable Object.";
};

CDominoes::CDominoes()
{
};

CDominoes::~CDominoes()
{
	cout << "Deleting CDominoes Object.";
};

void CDominoes::InitializeDominoes(void) {
	for (int right = 0; right < 7; right++)
	{
		for (int left = 0; left < 7; left++)
		{
			dataDomino piece;
			piece.right = right;
			piece.left = left;
			piece.available = 1;

			PrintDomino(&piece);
			allDominoes.push_back(&piece);
		}
		cout << endl;
	}
	cout << "allDominoes stores " << (int)allDominoes.size() << " pieces.\n";
};

void CDominoes::PrintDomino(dataDomino *piece)
{
	cout << "[" << piece->left << "|" << piece->right << "] Status(" << piece->available << ")  ";
};

dataDomino* CDominoes::GetRandomPiece() {
	dataDomino* piece;
	do // This is gonna get messy...
		dataDomino* piece = allDominoes.at(CRandom::GetRandomPublic(0, allDominoes.size()));
	while (piece->available != 1);

	cout << "Reandom piece drawn: ";
	PrintDomino(piece);

	return(piece);
};

CPlayer::CPlayer()
{
};

CPlayer::~CPlayer()
{
	cout << "Deleting CPlayer Object.";
};

void CPlayer::TakeDomino(dataDomino* newDomino)
{
	newDomino->available = 0;
	playerDominoes.push_back(newDomino);
};

void CPlayer::PlaceDomino(CTable* table, dataDomino* domino, int pos)
{
	switch (pos)
	{
	case 0:
		table->placedDominoes.push_front(domino);
		break;
	case 1:
		table->placedDominoes.push_back(domino);
		break;
	}
};

int main(void)
{
	Task4 task4;
	return 0;
}
