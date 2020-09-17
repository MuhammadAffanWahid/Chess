#include"Pawn.h"
//#include"Position.h"
#include"Rook.h"
#include"Piece.h"
#include"Knight.h"
#include"Bishop.h"
#include"Queen.h"
#include"King.h"
#include"fstream"
#include<windows.h>
#include<time.h>
#include<iostream>
#include "Board.h"
#include"graphics.h"
#include"stdio.h"
#include"dos.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////                   IMPORTANT FUNCIONS                ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	COOLOR Turn; //


void Board::getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void Board::gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void Board::color(int k)

{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}







//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




Board::Board()
{
	//Init();
	//Turn = WHOITE;
}

bool Board:: IsMyPiece(Position Pos)
{
	if (B[Pos.ri][Pos.ci] == nullptr)
		return false;
	COOLOR Piececolor = B[Pos.ri][Pos.ci]->getColor();
	return !(Piececolor != Turn);
}
bool Board:: IsEnemyPiece(Position Pos)
{
	if (B[Pos.ri][Pos.ci] == nullptr)
		return false;
	return !IsMyPiece(Pos);
}


void  Board::TurnChange()
{
	if (Turn == WHOITE)
		Turn = BLEACK;
	else
		Turn = WHOITE;
}



void Board::Init()
{
	char A[8][8];
	initwindow(2500, 900, "CHESS");
	bool savetxt=0;	
	int turn;
	string FN;
	
																			cleardevice();
																			setbkcolor(4);
																			setfillstyle(SOLID_FILL, 4);
																			bar(1200, 600, 1300, 700);
																			settextstyle(8, 0, 3);
																			outtextxy(1230, 640, "NEW");
																			setbkcolor(1);
																			setfillstyle(SOLID_FILL, 1);
																			bar(1400, 600,1500, 700);
																			settextstyle(8, 0, 3);
																			outtextxy(1425, 640, "Load");
																			setbkcolor(0);
																		do
																		{
																			SelectPiece();
																			if (S.ri==6)
																			{
																				if (S.ci == 12)
																				{
																					FN = "Load.txt";
																					break;
																				}
																				else 
																				{
																					FN = "Save.txt";
																					savetxt = 1;
																					break;
																				}
																			}
																		} while (true);


	ifstream Rdr(FN);

	if (savetxt)
	{
		Rdr >> turn;
		Turn = (turn == -1 ? BLEACK : WHOITE);
	}
	else
		Turn = (time(0)%2 ? BLEACK : WHOITE);

	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			Rdr >> A[ri][ci];
		}
	}


	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
         {
			if (A[ri][ci] == 'p')             B[ri][ci] = new Pawn(Position(ri, ci), WHOITE, this);
			else if (A[ri][ci] == 'P')     B[ri][ci] = new Pawn(Position(ri, ci), BLEACK, this);

			else if (A[ri][ci] == 'r')     B[ri][ci] = new Rook(Position(ri, ci), WHOITE, this);
			else if (A[ri][ci] == 'R')     B[ri][ci] = new Rook(Position(ri, ci), BLEACK, this);

			else if (A[ri][ci] == 'b')     B[ri][ci] = new Bishop(Position(ri, ci), WHOITE, this);
			else if (A[ri][ci] == 'B')     B[ri][ci] = new Bishop(Position(ri, ci), BLEACK, this);

			else if (A[ri][ci] == 'h')     B[ri][ci] = new Knights(Position(ri, ci), WHOITE, this);
			else if (A[ri][ci] == 'H')     B[ri][ci] = new Knights(Position(ri, ci), BLEACK, this);

			else if (A[ri][ci] == 'k')     B[ri][ci] = new King(Position(ri, ci), WHOITE, this);
			else if (A[ri][ci] == 'K')     B[ri][ci] = new King(Position(ri, ci), BLEACK, this);

			else if (A[ri][ci] == 'q')     B[ri][ci] = new Queen(Position(ri, ci), WHOITE, this);
			else if (A[ri][ci] == 'Q')     B[ri][ci] = new Queen(Position(ri, ci), BLEACK, this);

			else  B[ri][ci] = nullptr;
		}
	}
}

bool Board::IsStaleMate()
{
	int a;
	for (int Sr = 0; Sr < 8; Sr++)
	{
		for (int Sc = 0; Sc < 8; Sc++)
		{
			S.ri = Sr;
			S.ci = Sc;

			if (IsValidSelection())
			{
				for (int Er = 0; Er < 8; Er++)
				{
					for (int Ec = 0; Ec < 8; Ec++)
					{
						E.ri = Er;
						E.ci = Ec;
						if (IsValidDestination() && B[S.ri][S.ci]->ISLegel(E,false,true))
						{
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

bool Board::IsCheckMate()
{
	if (!IsCheck())
		return false;
	return IsStaleMate();
}



void Board::PrintBox(int ri, int ci)
{
	if ((ri + ci) % 2 == 0)
		setfillstyle(SOLID_FILL, 7);
	else
		setfillstyle(SOLID_FILL, 8);
	bar(ci * 100, ri * 100, (ci + 1) * 100 - 0, (ri + 1) * 100 - 0);
}

void Board::UnHighlightBox(int ri, int ci)
{
	if ((ri + ci) % 2 == 0)
	{
		HighlightBox(ri, ci, 7, 12);
	}
	else
		HighlightBox(ri, ci, 8, 12);
}

void Board::UnHighlight()
{
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			E = Position(r, c);
			if (IsValidDestination() && B[S.ri][S.ci]->ISLegel(E,false,true))
			{
				if((r != S.ri && c != S.ci) && (r != E.ri && c != E.ci))
				UnHighlightBox(r, c);
			}
		}
	}
}

void Board::HighlightBox(int ri, int ci,int color,int Thickness)
{
	Position TP(ri, ci);
	if (B[ri][ci] != nullptr && IsEnemyPiece(TP))
		color = 4;
		setcolor(color);

	setfillstyle(SOLID_FILL, color);
	int sync = Thickness / 2;
	bar(ci * 100, ri * 100, (ci + 1) * 100 - 0, (ri + 1) * 100 - 0);
	if ((ri + ci) % 2 == 0)
	setcolor(7);
	else
	setcolor(8);

	rectangle(ci * 100, ri * 100, (ci + 1) * 100 - 0, (ri + 1) * 100 - 0);
	if(B[ri][ci]!=nullptr)
	B[ri][ci]->Draw();
	setcolor(15);
}

void Board::Highlight(int color)
{
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			E = Position(r, c);
			if (IsValidDestination() && B[S.ri][S.ci]->ISLegel(E,false,true))
			{
				HighlightBox(r, c, color, 12);
			}
		}
	}
}

void Board::PrintBoard()
{
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
				
			PrintBox(ri, ci);
			if (B[ri][ci] != nullptr)
				B[ri][ci]->Draw();
		}
	}
	setbkcolor(4);
	setfillstyle(SOLID_FILL, 4);
	bar(1200, 600, 1300, 700);
	settextstyle(8, 0, 3);
	outtextxy(1225,640,"Undo");
	setbkcolor(1);
	setfillstyle(SOLID_FILL, 1);
	bar(1400, 600,1500, 700);
	outtextxy(1425,640, "Redo");
	setbkcolor(2);
	setfillstyle(SOLID_FILL,2);
	bar(1300, 200, 1400, 300);
	settextstyle(8, 0, 3);
	outtextxy(1320,240, "Save");
	setbkcolor(0);
}



void Board::Move(Position S, Position E)
{
	B[E.ri][E.ci] = B[S.ri][S.ci];
	B[S.ri][S.ci] = nullptr;
}
void Board::SelectPiece()
{
																int ET,ST = time(0);
																bool SingleTurnOver = 0, DoubleTurnOver = 0;
	do
	{
																	ET= time(0);
																	char Text[50];
																	setcolor(11);
																	if(30 - (ET - ST) % 30 < 10)
																	outtextxy(1320, 100, " ");
																	if (15 - (ET - ST) % 15 < 10)
																		outtextxy(1520, 100, " ");
																	settextstyle(8,0,3);
																	sprintf(Text, "TIMER: %d", 15 - (ET - ST) % 15);
																	if (!SingleTurnOver)
																	{
																		if (15 - (ET - ST) % 15 > 1)
																		{
																			outtextxy(1400, 100, Text);
																		}
																		else
																		{
																			sprintf(Text, "TIMER: %d", 1);
																			outtextxy(1400, 100, Text);
																			SingleTurnOver = true;
																			TurnChange();
																			DisplayMsg();
																			continue;
																		}
																	}
																	
																	if (!DoubleTurnOver)
																	{
																		sprintf(Text, "TIMER: %d", 30 - (ET - ST) % 30);
																		if (30 - (ET - ST) % 30 > 1)
																		{
																			outtextxy(1200, 100, Text);
																		}
																		else
																		{
																			sprintf(Text, "TIMER: %d", 1);
																			outtextxy(1200, 100, Text);
																			DoubleTurnOver = true;
																		}
																	}
	} while (!ismouseclick(WM_LBUTTONDOWN));
	getmouseclick(WM_LBUTTONDOWN, S.ci, S.ri);
	Beep(1023, 50);
	S.ci = S.ci / 100;
	S.ri = S.ri / 100;
}
void Board::SelectDestination()
{
	do
	{

	} while (!ismouseclick(WM_LBUTTONDOWN));
	getmouseclick(WM_LBUTTONDOWN,E.ci, E.ri);
	Beep(2023, 50);
	E.ci = E.ci / 100;
	E.ri = E.ri / 100;
}
bool Board::IsValidSelection()
{
	if (S.ri < 0 || S.ri>7 || S.ci < 0 || S.ci>7)
		return false;

	return (B[S.ri][S.ci] != nullptr && B[S.ri][S.ci]->getColor() == Turn);
}
bool Board::IsValidDestination()
{
	if (S.ri < 0 || S.ri>7 || S.ci < 0 || S.ci>7)
		return false;
	return (B[E.ri][E.ci] == nullptr || B[E.ri][E.ci]->getColor() != Turn);
}
void Board::DisplayMsg()
{
	setfillstyle(SOLID_FILL, 8);
	bar(850, 550, 1010, 710);

	gotoRowCol(8, 0);
	if (Turn == WHOITE)
	{
		setfillstyle(SOLID_FILL, 0);
		//cout << "WHOITE's Turn(ri,ci)";
	}
	else
	{
		//cout << "BLEACK's Turn(ri,ci)";
		setfillstyle(SOLID_FILL, 15);
	}
	bar(900,600,960,660);

}


Position Board::KingAt()
{
	King* KPtr;
	Position Posii(-1, -1);
	for (int R = 0; R < 8; R++)
	{
		for (int C = 0; C < 8; C++)
		{
			
			if (B[R][C] != nullptr && Turn == B[R][C]->getColor())
			{
				KPtr = dynamic_cast<King*>(B[R][C]);
				if (KPtr == B[R][C])
				{
					Position Posi(R,C);
					return Posi;
				}
			}
		}
	}
	return Posii;
}

bool Board::IsCheck()
{
	Position Ptemp;
	Ptemp = KingAt();
	E.ri = Ptemp.ri;
	E.ci = Ptemp.ci;
	TurnChange();
	for (int R = 0; R < 8; R++)
	{
		for (int C = 0; C < 8; C++)
		{
			S.ri = R;
			S.ci = C;
			if (IsValidSelection() && IsValidDestination() && B[S.ri][S.ci]->ISLegel(E))///////////////////////
			{
				TurnChange();
				return true;
			}
		}
	}
	TurnChange();
	return false;
}


bool Board:: IsCheckAfterMove()
{
	bool Is = false;
	Piece* SP;
	Position TS = S;
	Position TE=  E;

	SP = B[E.ri][E.ci];
	B[S.ri][S.ci]->Move(E);
	if (IsCheck()) Is = true;
	S = TS;
	E = TE;
	

	B[E.ri][E.ci]->P.ri = S.ri; //->ChangePos(S.ri, S.ci);
	B[E.ri][E.ci]->P.ci = S.ci;

	B[S.ri][S.ci] = B[E.ri][E.ci];
	B[E.ri][E.ci] = SP;
	return Is;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////           Extensions             ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Board::CopyBoard()
{
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			Undu[r][c] = B[r][c];
		}
	}
}


void Board:: Sync()
{
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			if (B[r][c] != nullptr)
			{
				B[r][c]->P.ri = r;
				B[r][c]->P.ci = c;
			}
		}
	}
}

void Board::Save_Exit()
{

	ofstream Wtr("Save.txt");

	Wtr << Turn;

	for (int r = 7; r >= 0; r--)
	{
		for (int c = 0; c < 8; c++)
		{
			if (B[r][c] == nullptr)
				Wtr << '-' << " ";
			else
				Wtr << B[r][c]->Tokken() << " ";
		}
		Wtr << endl;
	}

	Wtr << endl;
	Wtr.close();

	gotoRowCol(13, 13);
	cout << "Game Save";
	exit(0);
}

void Board::UndoMove()
{
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			B[r][c] = Undu[r][c];
		}
	}
	TurnChange();
}


void Board::RedoMove()
{
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			B[r][c] = Redo[r][c];
		}
	}

	TurnChange();
}


void Board::CopyBoardBeforeUndo()
{
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			Redo[r][c] = B[r][c];
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Board:: Play()
{
	time_t ST,ET;
	bool TimeEnd = 0,TTimeEnd = 0;
	Init();
	while (!IsCheckMate() && !IsStaleMate() && !TimeEnd)
	{
		ST = time(0);
		do
		{
			TimeEnd = 0, TTimeEnd = 0;
			PrintBoard();

			if (IsCheck())
				HighlightBox(KingAt().ri, KingAt().ci, 4, 20);
			DisplayMsg();
			do
			{ 
				
				SelectPiece();
															
															//{
															//		ET = time(0);
															//		if (ET - ST > 5)
															//		{
															//			TurnChange();
															//			TTimeEnd = true;
															//			if (ET - ST > 15)
															//				TimeEnd = true;
															//			//break;
															//		}
															//}

															if (S.ri == 2 && S.ci == 13)
															{
																Save_Exit();
															}

															
															if (S.ri==6)//600 >= S.ri && S.ri <= 660)
															{

																if (S.ci == 12)//S.ci >= 1400 && S.ci < 1460)
																{
																	if(Undo!=true)
																	{   CopyBoardBeforeUndo();
																		UndoMove();
																		Sync();
																		PrintBoard();
																		DisplayMsg();
																		Undo = true;
																		continue;
																	}
																}

																	if (S.ci==14)//S.ci >= 1500 && S.ci < 1560)
																	{
																		RedoMove();
																		Sync();
																		PrintBoard();
																		DisplayMsg();
																		Undo = false;
																		continue;
																	}

															}
			} while (!IsValidSelection());
															{
															  if (TTimeEnd)
																break;
															}
			Highlight(2);
			SelectDestination();
		} while (!IsValidDestination());
															{
																if (TimeEnd)
																	break;
																if (TTimeEnd)
																	continue;
															}
		if ((B[S.ri][S.ci]->ISLegel(E,false,true)))
		{
			CopyBoard();
			B[S.ri][S.ci]->Move(E,true);
			UnHighlightBox(S.ri, S.ci);
			UnHighlightBox(E.ri,E.ci);
			TurnChange();
		}
		ET = time(0);
	}
	cout << "\n\n\n\n\n";

	closegraph();
	
   cout << "     *     .--. .-,       .-..-.__                ___        *           " << endl;
   cout << " .       .'(`.-` /_.-'-./`  |/_( '/__   *        /   /           .       " << endl;
   cout << "       __.>\ ';  _;---,._|   / __/`'--)         / / / /                * " << endl;
	 cout<<"     /.--.  : |/' _.--.<|  /  | |              |   @   |       *         "<<endl;   
	cout<<"  _..-'    `\     /' /`  /_/ _/_/             , |       | ,               "<<endl;   
    cout<<" >_.-``-. `Y  /' _;---.`|/))))      *         \/(       )\/        .      "<<endl;   
   cout<<"  ` .-''. \|:  \.'   __, .-''`                   | )   ( |                 "<<endl;  
   cout<<"  .'--._ `-:  \/:  /'  '.\             _|_       |(     )|                 "<<endl;   
	cout<<"     /.'`\ :;   /'      `-           `-|-`      ||   | |'            *    "<<endl;   
	 cout<<"   -`    |     |                      |         |   | |                  "<<endl;   
	 cout<<"         :.; : |        *         .-'~^~`-.     |   | |                  "<<endl;   
	 cout<<"         |:    |                .'  NOFAL  `.   |   /-'                  "<<endl;   
	 cout<<"         |:.   |                |   MANSHA  |   |_.'                     "<<endl;   
	 cout<<"         :. :  |                |    RIP    |                            "<<endl;   
	 cout<<"        ,... : ;                | 4/5/2020  |                            "<<endl;   
	 cout<<".'-/\\/:::.    `\.'-._-_'.'-'_\-|...........|///..-..--.-.-.-..-..-'-..- "<<endl;

	
	 cout << "\n\n\n                                     GAME OVER \n\n";


	system("pause");
}

Board::~Board() {}

