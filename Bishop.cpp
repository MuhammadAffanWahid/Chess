#include"Bishop.h"
#include"Board.h"

Bishop::Bishop(Position p, COOLOR c, Board* b) : Piece(p, c, b)
{

}

bool Bishop::ISLegel(Position EP, bool IsRealMove, bool SelfCheck )
{
	if (SelfCheck && Brd->IsCheckAfterMove())
		return false;//
	return((IsDiagonalMove(P, EP) && IsDiagonalPathClear(P, EP, Brd)));
}
void Bishop::Draw()
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

	int A[] = { x, y - 10,x + 10,y + 10,x - 10,y + 10,x,y - 10 };
	setcolor(culr);
	setfillstyle(SOLID_FILL, culr);
	fillpoly(4, A);
}
void Bishop::UnDraw()
{
	cout << " ";
}


char Bishop::Tokken()
{
	if (C == BLEACK)
		return 'b';
	else
		return 'B';
}
