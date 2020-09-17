#include "Pawn.h"
#include"Board.h"
#include"Queen.h"
using namespace std;



Pawn::Pawn(Position p, COOLOR c, Board* b) :Piece(p, c, b)
{
}
bool Pawn::ISLegel(Position EP, bool IsRealMove, bool SelfCheck)
{
	if (SelfCheck && Brd->IsCheckAfterMove())
		return false;

	int dr = EP.ri - P.ri;
	int dc = EP.ci - P.ci;

	if (abs(dc) == 0 && Brd->B[EP.ri][EP.ci] != nullptr) //affan
		return false;

	if (C == WHOITE)
	{
		if (dr < 0 || abs(dr) > 2)
			return false;
		if (abs(dc) > 1)
			return false;
		if (abs(dr) == 2 && (P.ri != 1 || dc != 0))
			return false;
		if (!IsVerticlePathClear(P, EP, Brd))
			return false;
		if (dr == 0 && dc != 0)
			return 0;
		if (IsDiagonalMove(P, EP))
		{

			if (P.ci != 0 && P.ri != 0 && Brd->IsEnemyPiece(EP))
				return 1;
			else if (P.ci != 7 && P.ri != 0 && Brd->IsEnemyPiece(EP))
				return 1;
			else
				return false;
		}
	}
	else
	{
		if (dr > 0 || abs(dr) > 2)
			return false;
		if (abs(dc) > 1)
			return false;
		if (!IsVerticlePathClear(P, EP, Brd))
			return false;
		if (abs(dr) == 2 && (P.ri != 6 || dc != 0))
			return false;
		if (dr == 0 && dc != 0)
			return 0;
	}

	if (IsDiagonalMove(P, EP))
	{
		if (P.ci != 7 && P.ri != 7 && Brd->IsEnemyPiece(EP))
			return 1;
		else if (P.ci != 0 && P.ri != 0 && Brd->IsEnemyPiece(EP))
			return 1;
		else
			return false;
	}
}

void Pawn::Move(Position EP, bool IsReal)
{
	if (IsReal)
	{
		if ((C == WHOITE && EP.ri == 7) || (C == BLEACK && EP.ri == 0))
		{
			Position T = P;
			P = EP;
			Brd->Move(T, EP);
			Brd->B[P.ri][P.ci] = new Queen(P, C, Brd);
		}
		else 
	    {
			Position T = P;
	     	P = EP;
		    Brd->Move(T, EP);
			}
	    }
	else
	{
		Position T = P;
		P = EP;
		Brd->Move(T, EP);
	}

}


void Pawn::Draw()
{
	if (C == WHOITE)
	{
	  culr =PC;
	}
	else
	{
	  culr = pc;
	}
		setcolor(culr);
		setfillstyle(SOLID_FILL, culr);
		circle(P.ci*100+50,P.ri*100+50, 10);
		floodfill(P.ci * 100 + 50, P.ri * 100 + 50,culr);
}
void Pawn::UnDraw()
{
	cout << "-";
	IsFirstStep = false;
}




char Pawn::Tokken()
{
	if (C == BLEACK)
		return 'p';
	else
		return 'P';
}

Pawn::~Pawn()
{

}