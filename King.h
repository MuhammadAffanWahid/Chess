#pragma once
#include"Piece.h"
class King :public Piece
{
public:

	King(Position p, COOLOR c, Board* b);
	//virtual void Move(Position EP, bool VirtualMove = false);
	virtual bool ISLegel(Position EP, bool IsRealMove = false, bool SelfCheck=false);
	virtual void Draw();
	virtual void UnDraw();
	virtual char Tokken();
};
