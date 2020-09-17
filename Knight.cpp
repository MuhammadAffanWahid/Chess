#include "Knight.h"


Knights::Knights(Position p, COOLOR c, Board* b) : Piece(p, c, b)
{

}
bool Knights::ISLegel(Position EP, bool IsRealMove, bool SelfCheck)
{
	if (SelfCheck && Brd->IsCheckAfterMove())
		return false;//
	return  (((abs(P.ri - EP.ri) == 2) && (abs(P.ci - EP.ci) == 1)) || ((abs(P.ri - EP.ri) == 1) && (abs(P.ci - EP.ci) == 2)));
}
void Knights::Draw()
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

	setcolor(culr);
	int A[] = { x - 10, y - 10,x + 5,y - 4,x + 10,y + 10,x - 10,y + 10, x - 10, y - 10 };
	setfillstyle(SOLID_FILL, culr);
	fillpoly(5, A);
}
void Knights::UnDraw()
{
	cout << " ";
}



char Knights::Tokken()
{
	if (C == BLEACK)
		return 'h';
	else
		return 'H';
}