#pragma once
#include"Piece.h"

class Pawn :public Piece
{
	bool IsFirstStep = 1;
public:
	Pawn(Position p, COOLOR c, Board* b);
	virtual bool ISLegel(Position EP, bool IsRealMove = false, bool SelfCheck = false);
	void Move(Position,bool IsReal=false)override;
	virtual void Draw();
	virtual void UnDraw();
	virtual char Tokken();
	~Pawn();
};

