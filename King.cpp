#include "King.h"
#include"Board.h"

King:: King(Position p, COOLOR c, Board* b) : Piece(p, c, b)
{
}
bool King:: ISLegel(Position EP, bool IsRealMove, bool SelfCheck)
{
	if (SelfCheck && Brd->IsCheckAfterMove())
		return false;//
	return !(abs(EP.ri - P.ri) > 1 || abs(EP.ci - P.ci) > 1);
	//return((IsHorizontalMove(P, EP) && IsHorizontalPathClear(P, EP, Brd)) || (IsVerticleMove(P, EP) && IsVerticlePathClear(P, EP, Brd)) || (IsDiagonalMove(P, EP) && IsDiagonalPathClear(P, EP, Brd)));
}
void King::Draw()
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
	bar(x - 3, y - 10, x + 3, y + 10);
	bar(x - 10, y - 3, x + 10, y + 3);
}

void King::UnDraw()
{
	cout << "-";
}


char King::Tokken()
{
	if (C == BLEACK)
		return 'k';
	else
		return 'K';
}