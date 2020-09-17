#pragma once
#include"Piece.h"
class Rook :public Piece
{
public:
	//Rook();
	Rook(Position p, COOLOR c, Board* b);
	virtual bool ISLegel(Position EP, bool IsRealMove = false, bool SelfCheck = false);//override
	virtual void Draw();
	virtual void UnDraw();
	virtual char Tokken();

};

