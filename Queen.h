#pragma once
#include "Piece.h"
class Queen : public Piece
{
public:
	Queen(Position p, COOLOR c, Board* b);
	virtual bool ISLegel(Position EP, bool IsRealMove = false, bool SelfCheck = false);
	virtual void Draw();
	virtual void UnDraw();
	virtual char Tokken();

};

