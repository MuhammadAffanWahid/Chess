#pragma once
//#include"Rook.h"
//#include"Pawn.h"
#include"Position.h"
class Piece;


class Board
{
protected:
	char HL[8][8];
	Position S, E;
	friend class Piece;



public:
	Piece* B[8][8];
	////
	Piece* Undu[8][8];
	Piece* Redo[8][8];
	char   Load[8][8];
	bool   Undo;
	////
	Board();
	void DisplayMsg();
	void Init();
	void Move(Position S, Position E);
	void SelectPiece();
	void SelectDestination();
	void TurnChange();
	bool IsValidSelection();
	bool IsValidDestination();
	void Play();
	void PrintBoard();
	void PrintBox(int, int);
	void Highlight(int);
	void HighlightBox(int, int, int, int);
	void UnHighlight();
	void UnHighlightBox(int ri, int ci);
	bool IsMyPiece(Position);
	bool IsEnemyPiece(Position);
	bool IsCheck();
	bool IsStaleMate();
	bool IsCheckMate();
	bool IsCheckAfterMove();
	Position KingAt();
	~Board();
	///////////////

	void CopyBoard();
	void CopyBoardBeforeUndo();
	void Sync();
	void Save_Exit();
	void UndoMove();
	void RedoMove();
	///////////////
	void gotoRowCol(int rpos, int cpos);
	void getRowColbyLeftClick(int&, int&);
	void color(int);
};

