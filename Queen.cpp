#include "Queen.h"
#include"Board.h"

Queen::Queen(Position p, COOLOR c, Board* b) : Piece(p, c, b)
{

}

bool Queen::ISLegel(Position EP, bool IsRealMove, bool SelfCheck)
{
	if (SelfCheck && Brd->IsCheckAfterMove())
		return false;//
	return((IsHorizontalMove(P, EP) && IsHorizontalPathClear(P, EP, Brd)) || (IsVerticleMove(P, EP) && IsVerticlePathClear(P, EP, Brd)) || (IsDiagonalMove(P, EP) && IsDiagonalPathClear(P, EP, Brd)));
}
void Queen::Draw()
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

	int A[] = { x, y - 10 - 3,x + 10,y + 10 - 3,x - 10,y + 10 - 3,x,y - 10 - 3 };
	int B[] = { x, y + 13,x - 10,y - 7,x + 10,y - 7,x,y + 13 };
	setfillstyle(SOLID_FILL, culr);
	fillpoly(4, B);
	fillpoly(4, A);
}
void Queen::UnDraw()
{
	cout << " ";
}



char Queen::Tokken()
{
	if (C == BLEACK)
		return 'q';
	else
		return 'Q';
}