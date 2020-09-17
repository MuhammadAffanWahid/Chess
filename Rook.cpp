#include"Rook.h"
#include"Board.h"

Rook::Rook(Position p, COOLOR c, Board* b) : Piece(p, c, b)
{
}

 bool Rook::ISLegel(Position EP, bool IsRealMove, bool SelfCheck)//override
{
	 if (SelfCheck && Brd->IsCheckAfterMove())
		 return false;//
	return((IsHorizontalMove(P, EP) && IsHorizontalPathClear(P, EP, Brd)) || (IsVerticleMove(P, EP) && IsVerticlePathClear(P, EP, Brd)));
}
void Rook::Draw()
{
	int x = P.ci * 100 + 50, y = P.ri * 100 + 50;
	if (C == WHOITE)
	{
		culr = PC;
	}
	else
	{
		culr = pc;
	}

	setfillstyle(SOLID_FILL, culr);
	bar(x - 10, y - 10, x + 10, y + 10);
}
void Rook::UnDraw()
{
	cout << " ";
}



char Rook::Tokken()
{
	if (C == BLEACK)
		return 'r';
	else
		return 'R';
}