//---------------------------------------------------------------------------
#include <vcl.h>
#include <memory>
#pragma hdrstop
#include "ChessMyClasses.h"
#pragma package(smart_init)

// --------------   GameObject   ------------------- //
GameObject::GameObject() {}

GameObject::~GameObject(){}

void GameObject::SetGameObjectHere()
{
        this->GameObjectExistence = true;
}
bool GameObject::IsGameObjectHere()
{
        return this->GameObjectExistence;
}
void GameObject::DeleteGameObjectHere()
{
        this->GameObjectExistence = false;
}
// --------------   Axis   ------------------- //

Axis::Axis() {}

Axis::Axis(int y, int x)
{
        this->y = y;
        this->x = x;
}

Axis::~Axis() {}

int Axis::GetY()
{
        return this->y;
}
int Axis::GetX()
{
        return this->x;
}
void Axis::SetY(int y)
{
        this->y = y;
}
void Axis::SetX(int x)
{
        this->x = x;
}
int Axis::GetOldY()
{
        return this->oldposy;
}
int Axis::GetOldX()
{
        return this->oldposx;
}
void Axis::SetOldPositions(int y, int x)
{
        this->oldposy = y;
        this->oldposx = x;
}
//-------------   Attributes   -------------------//
Attributes::Attributes(){}

Attributes::Attributes(int type, int color, int y, int x, bool ObjectState) : Axis(y,x)
{
        this->type = type;
        this->color = color;
        this->GameObjectState = ObjectState;
}

Attributes::~Attributes() {}

void Attributes::SetType(int type)
{
        this->type = type;
}
int Attributes::GetType()
{
        return this->type;
}
bool Attributes::GetColor()
{
        return this->color;
}
void Attributes::SetColor(bool color)
{
        this->color = color;
}
void Attributes::SetGameObjectState(bool newState)
{
        this->GameObjectState = newState;
}
bool Attributes::GetGameObjectState()
{
        return this->GameObjectState;
}
// -------------   ChessBoard   -------------------//

ChessBoard::ChessBoard(int y,int x) : Axis(y,x) {}

ChessBoard::~ChessBoard(){}

 // --------------   ChessPiece  -------------------//

ChessPiece::ChessPiece(){}

ChessPiece::ChessPiece(int type,bool color,int y,int x,bool ObjectState) : Attributes(type,color,y,x,ObjectState) {}

ChessPiece::~ChessPiece(){}

bool ChessPiece::CanPieceMoveThere(int i, int j)
{
        bool canMove = true;
        int actualY = this->GetY();
        int actualX = this->GetX();

        this->PieceMovedToNewCoords(i,j);

        if(!this->GetColor())
                if(WHITE_KING->isKingInCheck())
                        canMove = false;
        if(this->GetColor())
                if(BLACK_KING->isKingInCheck())
                        canMove = false;

        this->PieceMovedToNewCoords(actualY,actualX);
        return canMove;
}

bool ChessPiece::CanPieceAttackThere(ChessPiece *AttackedPiece)
{
        bool canMove = true;
        int actualY = this->GetY();
        int actualX = this->GetX();


        this->PieceMovedToNewCoords(AttackedPiece->GetY(), AttackedPiece->GetX());
        AttackedPiece->SetGameObjectState(false);

        if(!this->GetColor())
                if(WHITE_KING->isKingInCheck())
                        canMove = false;
        if(this->GetColor())
                if(BLACK_KING->isKingInCheck())
                        canMove = false;

        this->PieceMovedToNewCoords(actualY,actualX,false);
        AttackedPiece->SetGameObjectState(true);
        return canMove;
}

void ChessPiece::ConvertAxisToChessNotation(String &str_y, String &str_x, int y, int x)
{
        switch(y)
        {
                case 0: str_y = '8';break;
                case 1: str_y = '7';break;
                case 2: str_y = '6';break;
                case 3: str_y = '5';break;
                case 4: str_y = '4';break;
                case 5: str_y = '3';break;
                case 6: str_y = '2';break;
                case 7: str_y = '1';break;
        }
        switch(x)
        {
              case 0: str_x = 'a';break;
              case 1: str_x = 'b';break;
              case 2: str_x = 'c';break;
              case 3: str_x = 'd';break;
              case 4: str_x = 'e';break;
              case 5: str_x = 'f';break;
              case 6: str_x = 'g';break;
              case 7: str_x = 'h';break;
        }
}


void ChessPiece::GetDataForMove(int MatchState, bool attacked,bool &DataForCastlingByWhite, bool &DataForCastlingByBlack,int newY, int newX, int oldY, int oldX)
{
        String move; // full text
        String str_y, str_x;  // new y,x
        String str_oy, str_ox;  // old y,x
        String captured; // daca piesa a atacat o alta piesa
        attacked ? captured = "x" : captured = ":";
        move += "[" + IntToStr(ChessRound.GetGameRoundTurn()) + "] ";
        (!this->GetColor())? move += "White: " : move += "Black ";
        switch(this->GetType())
        {
                case PAWN: move += "P" + captured; break;
                case KNIGHT: move += "N" + captured; break;
                case BISHOP: move += "B" + captured; break;
                case ROOK: move += "R" + captured; break;
                case QUEEN: move += "Q" + captured; break;
                case KING: move += "K" + captured; break;
        }
        ConvertAxisToChessNotation(str_oy,str_ox,oldY, oldX);
        ConvertAxisToChessNotation(str_y,str_x,newY, newX);
        move += str_ox + str_oy + "-" + str_x + str_y;
        if(!ChessRound.DataForCastlingByWhite)
                if(ChessRound.ChessCastlingMade[0])
                {
                        if(ChessRound.CastlingPieceMovedWhite[1])
                                move += " O-O-O";
                        else if(ChessRound.CastlingPieceMovedWhite[2])
                                move += " O-O";
                        DataForCastlingByWhite = true;
                }
        if(!ChessRound.DataForCastlingByBlack)
                if(ChessRound.ChessCastlingMade[1])
                {
                        if(ChessRound.CastlingPieceMovedBlack[1])
                                move += " O-O-O";
                        else if(ChessRound.CastlingPieceMovedBlack[2])
                                move += " O-O";
                        ChessRound.DataForCastlingByBlack = true;
                }
        if(MatchState == -1)
        {
                move = move + "+";
        }
        else if(MatchState == 1)
        {
                move = move + "=";
                GameLog->Lines->Add(move);
                move = "This Match is a DRAW!";
        }
        else if(MatchState == 2)
        {
                move = move + "++  0-1";
                GameLog->Lines->Add(move);
                move = "BLACK WON! WHITE has been defeated!";
        }
        else if(MatchState == 3)
        {
                move = move + "++  1-0";
                GameLog->Lines->Add(move);
                move = "WHITE WON! BLACK has been defeated!";
        }
        GameLog->Lines->Add(move);
}

bool ChessPiece::CanPieceMoveToSaveKing(int posY, int posX)
{
        bool canMove = false;
        if(!board[posY][posX]->IsGameObjectHere())
        {
                switch(this->GetType())
                {
                        case PAWN: canMove = this->PawnMechanic(posY,posX); break;
                        case KNIGHT: canMove = this->KnightMechanic(posY,posX); break;
                        case BISHOP: canMove = this->BishopMechanic(posY,posX); break;
                        case ROOK: canMove = this->RookMechanic(posY,posX); break;
                        case QUEEN: canMove = this->QueenMechanic(posY,posX); break;
                }
        }
        else 
        {
                for(int i = 0; i < PIECES_MAX - 2; i++)
                        if(piece[i]->GetY() == posY and piece[i]->GetX() == posX)
                                if(piece[i]->GetGameObjectState())
                                        if(piece[i]->GetColor() != this->GetColor())
                                                switch(this->GetType())
                                                {
                                                        case PAWN: canMove = this->PawnAttack(piece[i]); break;
                                                        case KNIGHT: canMove = this->KnightAttack(piece[i]); break;
                                                        case BISHOP: canMove = this->BishopAttack(piece[i]); break;
                                                        case ROOK: canMove = this->RookAttack(piece[i]); break;
                                                        case QUEEN: canMove = this->QueenAttack(piece[i]); break;
                                                }
        }
        return canMove;
}



// -------------- Game ------------------------------//
ChessGame::ChessGame()
{
	this->GameTurn = 0;
        this->GameState = false;
}
ChessGame::~ChessGame(){}

void ChessGame::NextTurn()
{
	this->GameTurn++;
}
void ChessGame::ResetGameRoundTurn()
{
        this->GameTurn = 0;
}
int ChessGame::GetGameRoundTurn()
{
	return GameTurn;
}
void ChessGame::SetGameRoundTurn(int turn)
{
        this->GameTurn = turn;
}
void ChessGame::SetGameRoundState(bool active)
{
        this->GameState = active;
}
bool ChessGame::IsGameRoundActive()
{
        return this->GameState;
}

void __fastcall ChessGame::CreateAndStartChessGame()
{
        if(GameLog)
                delete GameLog;
        fMain->NewGame1->Checked = true; // arata checked in dreptul lui cand jocul e functional
        fMain->NewGame1->Enabled = false; // nu te lasa sa incepi un joc nou cand unul deja este in miscare
        fMain->Resolution1->Enabled = false;  // nu lasa sa schimbi rezolutia in timp ce joci
        GameChessBoard->Stretch = true;
        GameChessBoard->Height = fMain->BoardSize;   //
        GameChessBoard->Width = fMain->BoardSize;    //
        GameChessBoard->Visible = true;
        GameChessBoard->Transparent = true;
        GameChessBoard->Top = fMain->BoardDist;     //
        GameChessBoard->Left = fMain->BoardDist;    //

        GameLog = new TMemo(fMain);
        GameLog->Parent = fMain;
        GameLog->ScrollBars = ssVertical;
        GameLog->ReadOnly = true;
        GameLog->BorderStyle = bsNone;
        //
        GameLog->Font->Size = fMain->GamelogFontSize;
        GameLog->Font->Color = clBlack;
        GameLog->Color = clWhite;
        //
        GameLog->Height = fMain->GamelogSize;   //
        GameLog->Width = fMain->GamelogSize;    //
        GameLog->Top = fMain->GamelogY;        //
        GameLog->Left = fMain->GamelogX;       //

        // <----- Initiator variabile ------>
        this->SetGameRoundState(true);
        this->ResetGameRoundTurn();
        pieceClickedFirst = WHITE;
        lastColorPieceSelected = WHITE;
        LastPieceClickedID = 0, LastPieceAttackedID = 0;
        for(int i = 0 ; i < 4 ; i++)
                CastlingTypeNumber[i] = false;
        CastlingPieceMovedWhite[0] = false; CastlingPieceMovedWhite[1] = false; CastlingPieceMovedWhite[2] = false;
        CastlingPieceMovedBlack[0] = false; CastlingPieceMovedBlack[1] = false; CastlingPieceMovedBlack[2] = false;
        AnotherPieceClicked = false;
        ChessCastlingType = 0;
        ChessCastlingMade[0] = false; ChessCastlingMade[1] = false;
        DataForCastlingByWhite = false;
        DataForCastlingByBlack = false;
        for(int i = 0 ; i < TABLE_LENGTH*2 ; i++)
        {
                en_passant[i] = 0;
        }
        Can_en_passant = false;
        // <-------------------------------->
        this->StartRoundofChess();
        GameLog->Text = "Game has started!";
        GameLog->Lines->Add("White moves!");
        // Initiere  imagininile board
        for(int i = 0 ; i < TABLE_LENGTH ; i++)
                for(int j = 0 ; j < TABLE_LENGTH ; j++)
                {
                        PictureBoard[i][j]->Parent = fMain;
                        PictureBoard[i][j]->Transparent = true;
                        PictureBoard[i][j]->Visible = true;
                        PictureBoard[i][j]->Height = fMain->imageSize;
                        PictureBoard[i][j]->Width = fMain->imageSize;
                        PictureBoard[i][j]->Center = true;
                        PictureBoard[i][j]->Cursor = crDefault;
                        PictureBoard[i][j]->Top = board[i][j]->GetY();
                        PictureBoard[i][j]->Left = board[i][j]->GetX();
                        PictureBoard[i][j]->OnClick = board[i][j]->BoardClick;
                        PictureBoard[i][j]->Picture->LoadFromFile(rsTransparent);
                }
        // Initiere imaginile piece
        for(int i = 0 ; i < PIECES_MAX ; i++)  // ALL PIECES IMG
        {
                PicturePiece[i]->Parent = fMain;
                PicturePiece[i]->Transparent = true;
                PicturePiece[i]->Visible = true;
                PicturePiece[i]->Height = fMain->imageSize;
                PicturePiece[i]->Width = fMain->imageSize;
                PicturePiece[i]->Center = true;
                PicturePiece[i]->Cursor = crHandPoint;
                PicturePiece[i]->Top = board[piece[i]->GetY()][piece[i]->GetX()]->GetY();
                PicturePiece[i]->Left = board[piece[i]->GetY()][piece[i]->GetX()]->GetX();
                PicturePiece[i]->OnClick = piece[i]->PieceClicked;
        }
        for(int i = 0 ; i < PIECES_MAX ; i++)
                switch(piece[i]->GetType())
                {
                        case PAWN:
                        if(!piece[i]->GetColor())
                                PicturePiece[i]->Picture->LoadFromFile(rsPawnW);
                        else
                                PicturePiece[i]->Picture->LoadFromFile(rsPawnB); break;
                        case KNIGHT:
                        if(!piece[i]->GetColor())
                                PicturePiece[i]->Picture->LoadFromFile(rsKnightW);
                        else
                                PicturePiece[i]->Picture->LoadFromFile(rsKnightB); break;
                        case BISHOP:
                        if(!piece[i]->GetColor())
                                PicturePiece[i]->Picture->LoadFromFile(rsBishopW);
                        else
                                PicturePiece[i]->Picture->LoadFromFile(rsBishopB); break;
                        case ROOK:
                        if(!piece[i]->GetColor())
                                PicturePiece[i]->Picture->LoadFromFile(rsRookW);
                        else
                                PicturePiece[i]->Picture->LoadFromFile(rsRookB); break;
                        case QUEEN:
                        if(!piece[i]->GetColor())
                                PicturePiece[i]->Picture->LoadFromFile(rsQueenW);
                        else
                                PicturePiece[i]->Picture->LoadFromFile(rsQueenB); break;
                        case KING:
                        if(!piece[i]->GetColor())
                                PicturePiece[i]->Picture->LoadFromFile(rsKingW);
                        else
                                PicturePiece[i]->Picture->LoadFromFile(rsKingB); break;
                }
}

void ChessGame::StartRoundofChess()
{
        int TypeInitiator[PIECES_MAX] = {PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, KNIGHT, KNIGHT, KNIGHT, KNIGHT, BISHOP, BISHOP, BISHOP, BISHOP, ROOK, ROOK, ROOK, ROOK, QUEEN, QUEEN, KING, KING};
        bool ColorInitiator[PIECES_MAX] = {WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, WHITE,WHITE, BLACK, BLACK, WHITE,WHITE, BLACK, BLACK, WHITE,WHITE, BLACK, BLACK, WHITE, BLACK, WHITE, BLACK};
        int YAxisInitiator[PIECES_MAX] = {6, 6, 6, 6, 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 7, 7, 0, 0, 7, 7, 0, 0, 7, 7, 0, 0, 7, 0, 7, 0};
        int XAxisInitiator[PIECES_MAX] = {0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 1, 6, 1, 6, 2, 5, 2, 5, 0, 7, 0, 7, 3, 3, 4, 4};
        // initiere obiecte ChessBoard
        if(fMain->ServerSocket->Active)
        {
                GameChessBoard->Picture->LoadFromFile(rsBoardServer);
                if(fMain->ClientWidth == 800 and fMain->ClientHeight == 600)
                {
                        fMain->BoardSize = 568;
                        fMain->BoardStartY = 74;
                        fMain->BoardStartX = 73;
                        fMain->distPiece = fMain->BoardSize / 9.5337;
                }
                else if(fMain->ClientWidth == 1024 and fMain->ClientHeight == 600)
                {
                        fMain->BoardSize = 568;
                        fMain->BoardStartY = 74;
                        fMain->BoardStartX = 73;
                        fMain->distPiece = fMain->BoardSize / 9.5337;
                }
                else if(fMain->ClientWidth == 1280 and fMain->ClientHeight == 800)
                {
                        fMain->BoardSize = 682;
                        fMain->BoardStartY = 104;
                        fMain->BoardStartX = 100;
                        fMain->distPiece = fMain->BoardSize / 9.5337;
                }
        }
        if(fMain->ClientSocket->Active)
        {
                if(fMain->ClientWidth == 800 and fMain->ClientHeight == 600)
                {
                        fMain->BoardSize = 568;
                        fMain->BoardStartY = 74;
                        fMain->BoardStartX = 73;
                        fMain->distPiece = fMain->BoardSize / 9.5337;
                }
                else if(fMain->ClientWidth == 1024 and fMain->ClientHeight == 600)
                {
                        fMain->BoardSize = 568;
                        fMain->BoardStartY = 74;
                        fMain->BoardStartX = 73;
                        fMain->distPiece = fMain->BoardSize / 9.5337;
                }
                else if(fMain->ClientWidth == 1280 and fMain->ClientHeight == 800)
                {
                        fMain->BoardSize = 682;
                        fMain->BoardStartY = 104;
                        fMain->BoardStartX = 100;
                        fMain->distPiece = fMain->BoardSize / 9.5337;
                }
                GameChessBoard->Picture->LoadFromFile(rsBoardClient);
                fMain->BoardStartY = fMain->distPiece * (TABLE_LENGTH - 1) + fMain->BoardStartY - fMain->BoardDist / (fMain->BoardDist / 1.5);
                fMain->BoardStartX = fMain->distPiece * (TABLE_LENGTH - 1) + fMain->BoardStartX - fMain->BoardDist / (fMain->BoardDist / 1.5);
                if(fMain->distPiece > 0)
                        fMain->distPiece = 0 - fMain->distPiece;
        }
        board[0][0] = new ChessBoard(fMain->BoardStartY, fMain->BoardStartX);
        for(int i = 0 ; i < TABLE_LENGTH ; i++)
                for(int j = 0 ; j < TABLE_LENGTH ; j++)
                      board[i][j] = new ChessBoard(board[0][0]->GetY() + fMain->distPiece * i, board[0][0]->GetX() + fMain->distPiece * j);
        // tabelul GameObject in pos (i , j) = (y , x)
        for(int i = 0 ; i < TABLE_LENGTH ; i++)
                for(int j = 0 ; j < TABLE_LENGTH ; j++)
                        board[i][j]->DeleteGameObjectHere();
        // initiere obiecte ChessPiece
        for(int i = 0 ; i < PIECES_MAX ; i++)
        {
                piece[i] = new ChessPiece(TypeInitiator[i], ColorInitiator[i], YAxisInitiator[i], XAxisInitiator[i]);
                board[piece[i]->GetY()][piece[i]->GetX()]->SetGameObjectHere();
        }
}

void __fastcall ChessGame::OnPlayerExit()
{
        if(this->IsGameRoundActive())
        {
                this->SetGameRoundState(false);
                if(fMain->ServerSocket->Active)
                        fMain->ServerSocket->Socket->Connections[0]->SendText("[SURRENDER]");
                if(fMain->ClientSocket->Active)
                        fMain->ClientSocket->Socket->SendText("[SURRENDER]");
        }
        // inchidere sockets
        fMain->ServerSocket->Close();
        fMain->ClientSocket->Close();
        // delete pointeri
        for(int i = 0 ; i < PIECES_MAX ; i++)
                delete piece[i];
        for(int i = 0 ; i < TABLE_LENGTH ; i++)
                for(int j = 0 ; j < TABLE_LENGTH ; j++)
                        delete board[i][j];
        delete GameLog;
        //
        delete GameChessBoard;
        for(int i = 0 ; i < TABLE_LENGTH ; i++)
                for(int j = 0 ; j < TABLE_LENGTH ; j++)
                {
                        delete PictureBoard[i][j];
                }
        for(int i = 0 ; i < PIECES_MAX ; i++)  // ALL PIECES IMG
        {
                delete PicturePiece[i];
        }
}


int ChessGame::GameMatchState()
{
        const int DrawMatch = 1, BlackWon = 2, WhiteWon = 3;
        int deadPieces = 0;
        // SAH PT ALB SI COND. PT WIN NEGRU
        if(WHITE_KING->isKingInCheck())
        {
                ShowMessagePos("CHECK at White King!",fMain->Left + fMain->ClientWidth / 2, fMain->Top + fMain->ClientHeight / 2);
                bool canMove = false;
                bool PieceCanSave = false;
                // pt piese
                for(int k = 0; k < PIECES_MAX - 2; k++)
                        if(!piece[k]->GetColor() and piece[k]->GetGameObjectState())
                                for(int i = 0; i < TABLE_LENGTH ; i++)
                                        for(int j = 0; j < TABLE_LENGTH; j++)
                                        {
                                                canMove = piece[k]->CanPieceMoveToSaveKing(i,j);
                                                if(canMove)
                                                        PieceCanSave = true;
                                        }
                // pt rege
                for(int i = 0; i < TABLE_LENGTH; i++)
                        for(int j = 0; j < TABLE_LENGTH; j++)
                                if(WHITE_KING->CanKingMoveThere(i,j,true))
                                        canMove = true;
                // verif finala
                if(!canMove and !PieceCanSave)
                        return BlackWon;
                else return -1;
        }

        // SAH PT NEGRU SI COND. PT WIN ALB
        if(BLACK_KING->isKingInCheck())
        {
                ShowMessagePos("CHECK at Black King!",fMain->Left + fMain->ClientWidth / 2, fMain->Top + fMain->ClientHeight / 2);
                bool canMove = false;
                bool PieceCanSave = false;
                // pt piese
                for(int k = 0; k < PIECES_MAX - 2; k++)
                        if(piece[k]->GetColor() and piece[k]->GetGameObjectState())
                                for(int i = 0; i < TABLE_LENGTH; i++)
                                        for(int j = 0; j < TABLE_LENGTH; j++)
                                        {
                                                canMove = piece[k]->CanPieceMoveToSaveKing(i,j);
                                                if(canMove)
                                                        PieceCanSave = true;
                                        }
                // pt rege
                for(int i = 0; i < TABLE_LENGTH; i++)
                        for(int j = 0; j < TABLE_LENGTH; j++)
                                if(BLACK_KING->CanKingMoveThere(i,j,true))
                                        canMove = true;
                // verif. finala
                if(!canMove and !PieceCanSave)
                        return WhiteWon;
                else return -1;
        }

        // COND. PT EGALITATE
        int PID = -1, PID2 = -1;
        for(int k = 0; k < PIECES_MAX - 2; k++)
                if(!piece[k]->GetGameObjectState())
                        deadPieces++;
                else
                {
                        if(PID == -1)
                                PID = k;
                        if(piece[k]->GetColor() != piece[PID]->GetColor() and PID != -1)
                                PID2 = k;
                }
        if(deadPieces == 30)
                return DrawMatch;
        if(deadPieces == 29 and PID != -1 and piece[PID]->GetType() == KNIGHT)
                return DrawMatch;
        if(deadPieces == 29 and PID != -1 and piece[PID]->GetType() == BISHOP)
                return DrawMatch;
        if(deadPieces == 28 and PID != -1 and PID2 != -1 and ((PID == 21 and PID2 == 22) or (PID == 20 and PID2 == 23))) // nebunii de culoarea patratelei aceeleasi
                return DrawMatch;
        // egal. -> pt alb
        if(!WHITE_KING->isKingInCheck())
        {
                bool canMove = false;
                bool PieceCanMove = false;
                // pt piese
                for(int k = 0; k < PIECES_MAX - 2; k++)
                        if(!piece[k]->GetColor() and piece[k]->GetGameObjectState())
                                for(int i = 0; i < TABLE_LENGTH; i++)
                                        for(int j = 0; j < TABLE_LENGTH; j++)
                                        {
                                                canMove = piece[k]->CanPieceMoveToSaveKing(i,j);
                                                if(canMove)
                                                        PieceCanMove = true;
                                        }
                // pt rege
                for(int i = 0; i < TABLE_LENGTH; i++)
                        for(int j = 0; j < TABLE_LENGTH; j++)
                                if(WHITE_KING->CanKingMoveThere(i,j,true))
                                        canMove = true;
                // verif finala
                if(!canMove and !PieceCanMove)
                        return DrawMatch;
        }
        // egal. -> pt negru
        if(!BLACK_KING->isKingInCheck())
        {
                bool canMove = false;
                bool PieceCanMove = false;
                // pt piese
                for(int k = 0; k < PIECES_MAX - 2; k++)
                        if(piece[k]->GetColor() and piece[k]->GetGameObjectState())
                                for(int i = 0; i < TABLE_LENGTH; i++)
                                        for(int j = 0; j < TABLE_LENGTH; j++)
                                        {
                                                canMove = piece[k]->CanPieceMoveToSaveKing(i,j);
                                                if(canMove)
                                                        PieceCanMove = true;
                                        }
                // pt rege
                for(int i = 0; i < TABLE_LENGTH; i++)
                        for(int j = 0; j < TABLE_LENGTH; j++)
                                if(BLACK_KING->CanKingMoveThere(i,j,true))
                                        canMove = true;
                // verif finala
                if(!canMove and !PieceCanMove)
                        return DrawMatch;
        }
        return 0;
}

void ChessGame::GameMatchStateVerification(int PCID,bool attackedPiece)
{
        int match = ChessRound.GameMatchState();
        if(match == 1)
        {
                ShowMessagePos("Draw!",fMain->Left + fMain->ClientWidth / 2, fMain->Top + fMain->ClientHeight / 2);
                ChessRound.SetGameRoundState(false);
        }
        else if(match == 2)
        {
                ShowMessagePos("Black WON!",fMain->Left + fMain->ClientWidth / 2, fMain->Top + fMain->ClientHeight / 2);
                ChessRound.SetGameRoundState(false);
        }
        else if(match == 3)
        {
                ShowMessagePos("White WON!",fMain->Left + fMain->ClientWidth / 2, fMain->Top + fMain->ClientHeight / 2);
                ChessRound.SetGameRoundState(false);
        }

        if(match == 1 or match == 2 or match == 3)
        {
                fMain->NewGame1->Checked = false;
                fMain->NewGame1->Enabled = true;
        }
        //  gamelog text
        piece[PCID]->GetDataForMove(match,attackedPiece,DataForCastlingByWhite,DataForCastlingByBlack,piece[PCID]->GetY(), piece[PCID]->GetX(), piece[PCID]->GetOldY(), piece[PCID]->GetOldX());
}



