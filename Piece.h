#pragma once

#include"Position.h"
#include"graphics.h"
#include<iostream>

using namespace std;
enum COOLOR { BLEACK = -1, WHOITE = 1 };
class Board;

class Piece
{
protected:

public:
	/*static*/ int PC=0, pc=15,culr;
	COOLOR C;
	Position P;
    Board* Brd;
	
	friend class Board;
	Piece(Position p, COOLOR c, Board* b);
	virtual bool ISLegel(Position EP,bool IsRealMove=false,bool SelfCheck=false)=0;
	virtual void Move(Position,bool IsReal=false);
	virtual void Draw() = 0;
	virtual void UnDraw() = 0;
	virtual char Tokken() = 0;
	//bool IsKill(Board*,Position,Position,int,COOLOR);
	COOLOR getColor();
	~Piece();

protected:
	static bool IsHorizontalMove(Position S, Position E);
	static bool IsVerticleMove(Position S, Position E);
	static bool IsDiagonalMove(Position S, Position E);

	static bool IsHorizontalPathClear(Position S, Position E, Board* B);
	static bool IsVerticlePathClear(Position S, Position E, Board* B);
	static bool IsDiagonalPathClear(Position S, Position E, Board* B);

};

