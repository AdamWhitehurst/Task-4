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

	CTable table;
	CDominoes dominoes;
	CPlayer playerOne, playerTwo;

	const int STARTING_HAND_SIZE = 10;

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
};

// Contains the data structure with pieces
class CDominoes
{
public:
	CDominoes();
	~CDominoes();
	void InitializeDominoes(void);
	deque<dataDomino*> allDominoes, dominoesPile, placedDominoes;
	dataDomino* GetPiece();
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
	void PlaceDomino();
	// Current hand variable?
};

Task4::Task4()
{
	CTable table();
	CDominoes dominoes();
	CPlayer playerOne();
	CPlayer playerTwo();
	API();
};

Task4::~Task4()
{
	cout << "Deleting Task4 Object.";
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
	dominoes.InitializeDominoes();
};

void Task4::DrawDominoes()
{
	for (int i = 0; i < STARTING_HAND_SIZE; i++)
	{

	}
};

void Task4::WhoFirst()
{
	// TODO randomly decide who's first
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
	dataDomino piece;
	int rangeLow = 0, rangeHigh = 1;
	for (int right = 0; right<7; right++)
	{
		for (int left = right; left<7; left++)
		{
			piece.right = right;
			piece.left = left;
			piece.available = 1; // randOBJ.getRandomPublic(rangeLow, rangeHigh);

			cout << "[" << piece.left << "|" << piece.right << "] Status(" << piece.available << ")  ";
			allDominoes.push_back(&piece);
		}

		cout << endl;
	}
	cout << "allDominoes stores " << (int)allDominoes.size() << " pieces.\n";
	cout << "dominoesPile stores " << (int)dominoesPile.size() << " pieces.\n";
};

dataDomino* CDominoes::GetPiece() {
	dataDomino* piece;
	do // This is gonna get messy...
		dataDomino* piece = allDominoes.at(CRandom::GetRandomPublic(0, allDominoes.size()));
	while (piece->available != 1);

	cout << "[" << piece->left << "|" << piece->right << "]"
		 << " available = " << piece->available << endl;

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

void CPlayer::PlaceDomino()
{

};

int main(void)
{
	Task4 task4;
	return 0;
}
