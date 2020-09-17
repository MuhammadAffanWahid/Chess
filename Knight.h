#pragma once
#include"Piece.h"
#include"Board.h"
class Knights :public Piece
{
public:
	Knights();
	Knights(Position p, COOLOR c, Board* b);
	virtual bool ISLegel(Position EP, bool IsRealMove = false, bool SelfCheck = false);
	virtual void Draw();
	virtual void UnDraw();
	virtual char Tokken();

};

