#include <time.h>
#include <iostream>

using namespace std;

class Task4
{
public:
	Task4();
	~Task4();
private:
	void API();
	void createDominoes();
	void drawDominoes();
	void whoFirst();
	void firstPiece();
	void runGame();
};

Task4::Task4()
{
	API();
}

Task4::~Task4()
{
	cout << "Deleting Task4 Object.";
}

void Task4::API()
{
	createDominoes();
	drawDominoes();
	whoFirst();
	firstPiece();

}

void Task4::createDominoes()
{
	// TODO create 28 random pieces that are all available for drawing
}

void Task4::drawDominoes()
{
	// TODO randomly give 10 to each player
}

void Task4::whoFirst()
{
	// TODO randomly decide who's first
}

void Task4::firstPiece()
{
	// TODO draw a random piece and place it
}

void Task4::runGame()
{
	// TODO Create loop that plays the game:
	// Check winner (end if there is a winner, empty hand)
	// next player
	// find piece match
	// can play? if yes, flip piece over if needed; place piece in train
	// if no, draw piece -> can draw? yes, go to find piece match
	// if no, pass
}

// sorting approach for the sequence that the 
// domino pieces will be shown/picked
class CRandom
{

};

// show/display the sorted pieces
class CTable : CRandom
{

};

// contain the data structure with pieces
class CDominoes
{
public:
	CDominoes();
	~CDominoes();
private:

};

CDominoes::CDominoes()
{

}

CDominoes::~CDominoes()
{

}


// select a randomly picked and sequentially show the selected pieces
class CPlayer
{
public:
	CPlayer();
	~CPlayer();
private:
	void draw();
	void place();
	// Current hand variable?
};


CPlayer::CPlayer()
{

}

CPlayer::~CPlayer()
{

}

void CPlayer::draw()
{

}

void CPlayer::place()
{

}

int main(void) {
	Task4 task4;
	return 0;
}
