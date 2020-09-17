#include "Piece.h"
#include"Board.h"
//int Piece :: PC=0, pc=15, culr=0;

Piece::Piece(Position p, COOLOR c, Board* b) :P(p), C(c)
{
	Brd = b;
}

void Piece::Move(Position EP, bool IsReal)
{
	Position T = P;
	P = EP;
	Brd->Move(T, EP);
}

COOLOR Piece::getColor()
{
	return C;
}

Piece::~Piece()
{

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                     Moves and Path Clear
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Piece::IsHorizontalMove(Position S, Position E)
{
	return S.ri == E.ri;
}
bool Piece::IsVerticleMove(Position S, Position E)
{
	return S.ci == E.ci;
}
bool Piece::IsDiagonalMove(Position S, Position E)
{
	int Dri = E.ri - S.ri;
	int Dci = E.ci - S.ci;
	return (abs(Dri) == abs(Dci));
}
bool Piece::IsHorizontalPathClear(Position S, Position E, Board* B)
{
	if (S.ci < E.ci)
	{
		for (int i = S.ci + 1; i < E.ci; i++)
		{
			if (B->B[S.ri][i] != nullptr)
				return false;
		}
	}
	if (S.ci > E.ci)
	{
		for (int i = E.ci + 1; i < S.ci; i++)
		{
			if (B->B[S.ri][i] != nullptr)
				return false;
		}
	}

	return true;
}
bool Piece::IsVerticlePathClear(Position S, Position E, Board* B)
{
	if (S.ri < E.ri)
	{
		for (int i = S.ri + 1; i < E.ri; i++)
		{
			if (B->B[i][S.ci] != nullptr)
				return false;
		}
	}
	else 
	{
		for (int i = E.ri + 1; i < S.ri; i++)
		{
			if (B->B[i][S.ci] != nullptr)
				return false;
		}
	}

	return true;

}
bool Piece::IsDiagonalPathClear(Position S, Position E, Board* B)
{
	if (S.ci < E.ci && S.ri < E.ri)
	{
		for (int i = 1; i < E.ci - S.ci; i++)
		{
			if (B->B[S.ri + i][S.ci + i] != nullptr) return false;
		}
		return true;
	}


	if (S.ci < E.ci && S.ri > E.ri)
	{
		for (int i = 1; i < E.ci - S.ci; i++)
		{
			if (B->B[S.ri - i][S.ci + i] != nullptr)
				return false;
		}
		return true;
	}
	if (S.ci > E.ci && S.ri < E.ri)
	{
		for (int i = 1; i < S.ci - E.ci; i++)
		{
			if (B->B[S.ri + i][S.ci - i] != nullptr)
				return false;
		}
		return true;
	}
	if (S.ci > E.ci && S.ri > E.ri)
	{
		for (int i = 1; i < S.ci - E.ci; i++)
		{
			if (B->B[S.ri - i][S.ci - i] != nullptr)
				return false;
		}
		return true;
	}
}


//bool Piece:: IsKill(Board* b, Position Str, Position End, int Turn, COOLOR C)
//{
   // if (Turn == WHOITE)
   // {

   // }
//}