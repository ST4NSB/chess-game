//---------------------------------------------------------------------------
#include <vcl.h>
#include <memory>
#pragma hdrstop
#include "ChessMyClasses.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------


// FUNCTIILE PRINCIPALE


void ChessPiece::EN_PASSANT_PID(int PID)
{
    if(!piece[PID]->GetColor())
    {
        for(int i = 0 ; i < TABLE_LENGTH ; i++)
                if(i == PID)
                {
                        ChessRound.en_passant[i]++;
                        break;
                }
    }
    else
    {
        for(int i = 8 ; i < TABLE_LENGTH*2 ; i++)
                if(i == PID)
                {
                        ChessRound.en_passant[i]++;
                        break;
                }
    }
}


void ChessPiece::CASTLING_ROOK_PID(int PID)
{
        if(!piece[PID]->GetColor())
        {
                if(PID == 24)
                        ChessRound.CastlingPieceMovedWhite[1] = true;
                if(PID == 25)
                        ChessRound.CastlingPieceMovedWhite[2] = true;
        }
        else if(piece[PID]->GetColor())
        {
                if(PID == 26)
                        ChessRound.CastlingPieceMovedBlack[1] = true;
                if(PID == 27)
                        ChessRound.CastlingPieceMovedBlack[2] = true;
        }
}

void ChessPiece::CASTLING_KING_PID(int PID)
{
        if(!piece[PID]->GetColor())
                ChessRound.CastlingPieceMovedWhite[0] = true;
        else if(piece[PID]->GetColor())
                ChessRound.CastlingPieceMovedBlack[0] = true;
}

bool ChessPiece::PieceMechanic(int i,int j)
{
        bool CanMoveOnBoard = false;
        switch(this->GetType())
        {
                case PAWN:
                {
                        CanMoveOnBoard = this->PawnMechanic(i,j);
                        if(CanMoveOnBoard)
                        {
                                EN_PASSANT_PID(ChessRound.LastPieceClickedID);
                                if(fMain->ServerSocket->Active)
                                        fMain->ServerSocket->Socket->Connections[0]->SendText("[EN_PASSANT_MOVE]" + IntToStr(ChessRound.LastPieceClickedID));
                                if(fMain->ClientSocket->Active)
                                        fMain->ClientSocket->Socket->SendText("[EN_PASSANT_MOVE]" + IntToStr(ChessRound.LastPieceClickedID));
                        }
                }
                break;
                case KNIGHT: CanMoveOnBoard = this->KnightMechanic(i,j); break;
                case BISHOP: CanMoveOnBoard = this->BishopMechanic(i,j); break;
                case ROOK:
                {
                        CanMoveOnBoard = this->RookMechanic(i,j);
                        if(CanMoveOnBoard)
                        {
                                CASTLING_ROOK_PID(ChessRound.LastPieceClickedID);
                                if(fMain->ServerSocket->Active)
                                        fMain->ServerSocket->Socket->Connections[0]->SendText("[CASTLING_ROOK_MOVE]" + IntToStr(ChessRound.LastPieceClickedID));
                                if(fMain->ClientSocket->Active)
                                        fMain->ClientSocket->Socket->SendText("[CASTLING_ROOK_MOVE]" + IntToStr(ChessRound.LastPieceClickedID));
                        }
                }
                break;
                case QUEEN: CanMoveOnBoard = this->QueenMechanic(i,j); break;
                case KING:
                {
                        CanMoveOnBoard = this->KingMechanic(i,j);
                        if(CanMoveOnBoard)
                        {
                                CASTLING_KING_PID(ChessRound.LastPieceClickedID);
                                if(fMain->ServerSocket->Active)
                                        fMain->ServerSocket->Socket->Connections[0]->SendText("[CASTLING_KING_MOVE]" + IntToStr(ChessRound.LastPieceClickedID));
                                if(fMain->ClientSocket->Active)
                                        fMain->ClientSocket->Socket->SendText("[CASTLING_KING_MOVE]" + IntToStr(ChessRound.LastPieceClickedID));
                        }
                }
                break;
        }
        return CanMoveOnBoard;
}

void ChessPiece::PieceMovedToNewCoords(int posY, int posX,bool DelActualPos)
{
        if(DelActualPos)
        {
                board[this->GetY()][this->GetX()]->DeleteGameObjectHere();
        }
        this->SetY(posY);
        this->SetX(posX);
        board[this->GetY()][this->GetX()]->SetGameObjectHere();
}

void ChessPiece::PieceMovedOnTable(int PCID, int i, int j)
{
        // save old pos
        piece[PCID]->SetOldPositions(piece[PCID]->GetY(),piece[PCID]->GetX());
        // move piece
        piece[PCID]->PieceMovedToNewCoords(i,j);
        // image moving
        PicturePiece[PCID]->Top = board[i][j]->GetY();
        PicturePiece[PCID]->Left = board[i][j]->GetX();
        // pawn to queen
        if(piece[PCID]->GetType() == PAWN and ((piece[PCID]->GetY() == 0 and !piece[PCID]->GetColor()) or (piece[PCID]->GetY() == 7 and piece[PCID]->GetColor())))
        {
                piece[PCID]->PawnToQueen();
                if(!piece[PCID]->GetColor())
                        PicturePiece[PCID]->Picture->LoadFromFile(rsQueenW);
                else
                        PicturePiece[PCID]->Picture->LoadFromFile(rsQueenB);
        }
        // en passant pawn move
        if(ChessRound.Can_en_passant and !piece[PCID]->GetColor() and piece[PCID]->GetType() == PAWN and i == 2 and piece[ChessRound.en_passant_id]->GetX() == j)
        {
                PicturePiece[ChessRound.en_passant_id]->Visible = false;
                piece[ChessRound.en_passant_id]->SetGameObjectState(false);
                board[i+1][j]->DeleteGameObjectHere();
        }
        if(ChessRound.Can_en_passant and piece[PCID]->GetColor() and piece[PCID]->GetType() == PAWN and i == 5 and piece[ChessRound.en_passant_id]->GetX() == j)
        {
                PicturePiece[ChessRound.en_passant_id]->Visible = false;
                piece[ChessRound.en_passant_id]->SetGameObjectState(false);
                board[i-1][j]->DeleteGameObjectHere();
        }

        for(int i = 0 ; i < TABLE_LENGTH*2 ; i++)
                if(ChessRound.en_passant[i] != 0)
                {
                        ChessRound.en_passant[i]++;
                        ChessRound.Can_en_passant = false;
                }
        // castling
        if(ChessRound.CastlingTypeNumber[0])
        {
                piece[24]->PieceMovedToNewCoords(7,3);  // tura 2 alba de la 7,0
                ChessRound.ChessCastlingType = 24;
                ChessRound.ChessCastlingMade[0] = true;
                ChessRound.CastlingPieceMovedWhite[1] = true;
                ChessRound.CastlingTypeNumber[0] = false;
        }
        if(ChessRound.CastlingTypeNumber[1])
        {
                piece[25]->PieceMovedToNewCoords(7,5);  // tura 2 alba de la 7,7
                ChessRound.ChessCastlingType = 25;
                ChessRound.ChessCastlingMade[0] = true;
                ChessRound.CastlingPieceMovedWhite[2] = true;
                ChessRound.CastlingTypeNumber[1] = false;
        }
        if(ChessRound.CastlingTypeNumber[2])
        {
                piece[26]->PieceMovedToNewCoords(0,3);  // tura 3 de la 0,0
                ChessRound.ChessCastlingType = 26;
                ChessRound.ChessCastlingMade[1] = true;
                ChessRound.CastlingPieceMovedBlack[1] = true;
                ChessRound.CastlingTypeNumber[2] = false;
        }
        if(ChessRound.CastlingTypeNumber[3])
        {
                piece[27]->PieceMovedToNewCoords(0,5);  // tura 4 de la 0,7
                ChessRound.ChessCastlingType = 27;
                ChessRound.ChessCastlingMade[1] = true;
                ChessRound.CastlingPieceMovedBlack[2] = true;
                ChessRound.CastlingTypeNumber[3] = false;
        }
        // image castling
        if(ChessRound.ChessCastlingMade[0])
        {
                PicturePiece[ChessRound.ChessCastlingType]->Top = board[piece[ChessRound.ChessCastlingType]->GetY()][piece[ChessRound.ChessCastlingType]->GetX()]->GetY();
                PicturePiece[ChessRound.ChessCastlingType]->Left = board[piece[ChessRound.ChessCastlingType]->GetY()][piece[ChessRound.ChessCastlingType]->GetX()]->GetX();
        }
        if(ChessRound.ChessCastlingMade[1])
        {
                PicturePiece[ChessRound.ChessCastlingType]->Top = board[piece[ChessRound.ChessCastlingType]->GetY()][piece[ChessRound.ChessCastlingType]->GetX()]->GetY();
                PicturePiece[ChessRound.ChessCastlingType]->Left = board[piece[ChessRound.ChessCastlingType]->GetY()][piece[ChessRound.ChessCastlingType]->GetX()]->GetX();
        }
        // increment round turn
        ChessRound.NextTurn();
        // check on king + check mate if exist
        ChessRound.GameMatchStateVerification(PCID);
}


// BOARD CLICK ONLY
void __fastcall ChessBoard::BoardClick(TObject *Sender) // CLICK PE TABLA (UNDE NU E PIESA)
{
        for(int i = 0 ; i < TABLE_LENGTH ; i++)
                for(int j = 0 ; j < TABLE_LENGTH ; j++)
                        if(PictureBoard[i][j] == Sender)
                        {
                                if(ChessRound.pieceClickedFirst)
                                {
                                        bool CanMoveOnBoard = piece[ChessRound.LastPieceClickedID]->PieceMechanic(i,j);
                                        if(CanMoveOnBoard)
                                        {
                                                piece[ChessRound.LastPieceClickedID]->PieceMovedOnTable(ChessRound.LastPieceClickedID,i,j);
                                                // transmiteri de socket
                                                if(fMain->ServerSocket->Active)
                                                        fMain->ServerSocket->Socket->Connections[0]->SendText("[MOVE]" + IntToStr(ChessRound.LastPieceClickedID) + "|" + IntToStr(i) + "|" + IntToStr(j));
                                                if(fMain->ClientSocket->Active)
                                                        fMain->ClientSocket->Socket->SendText("[MOVE]" + IntToStr(ChessRound.LastPieceClickedID) + "|" + IntToStr(i) + "|" + IntToStr(j));
                                        } // altfel nu poate ataca acolo
                                        /* <--------- Delete green dots ----------> */
                                        ChessPiece del;
                                        del.DeleteGreenDot();
                                         /* <-------------------------------------> */
                                        ChessRound.AnotherPieceClicked = false;
                                        ChessRound.pieceClickedFirst = false;
                                        //===== schimbare in mouse pointer default =======//
                                        for(int i = 0 ; i < TABLE_LENGTH ; i++)
                                                for(int j = 0 ; j < TABLE_LENGTH ; j++)
                                                        PictureBoard[i][j]->Cursor = crDefault;
                                        //================================//
                                }
                        }
}

bool ChessPiece::PieceAttack(ChessPiece *AttackedPiece)
{
         bool CanAttackOnBoard = false;
         switch(this->GetType())
         {
                case PAWN: CanAttackOnBoard = this->PawnAttack(AttackedPiece); break;
                case KNIGHT: CanAttackOnBoard = this->KnightAttack(AttackedPiece); break;
                case BISHOP: CanAttackOnBoard = this->BishopAttack(AttackedPiece); break;
                case ROOK:
                {
                        CanAttackOnBoard = this->RookAttack(AttackedPiece);
                        if(CanAttackOnBoard)
                        {
                                CASTLING_ROOK_PID(ChessRound.LastPieceClickedID);
                                if(fMain->ServerSocket->Active)
                                        fMain->ServerSocket->Socket->Connections[0]->SendText("[CASTLING_ROOK_MOVE]" + IntToStr(ChessRound.LastPieceClickedID));
                                if(fMain->ClientSocket->Active)
                                        fMain->ClientSocket->Socket->SendText("[CASTLING_ROOK_MOVE]" + IntToStr(ChessRound.LastPieceClickedID));
                        }
                }
                break;
                case QUEEN: CanAttackOnBoard = this->QueenAttack(AttackedPiece); break;
                case KING:
                {
                        CanAttackOnBoard = this->KingAttack(AttackedPiece);
                        if(CanAttackOnBoard)
                        {
                                CASTLING_KING_PID(ChessRound.LastPieceClickedID);
                                if(fMain->ServerSocket->Active)
                                        fMain->ServerSocket->Socket->Connections[0]->SendText("[CASTLING_KING_MOVE]" + IntToStr(ChessRound.LastPieceClickedID));
                                if(fMain->ClientSocket->Active)
                                        fMain->ClientSocket->Socket->SendText("[CASTLING_KING_MOVE]" + IntToStr(ChessRound.LastPieceClickedID));
                        }
                }
                break;
         }
         return CanAttackOnBoard;
}

void ChessPiece::PieceAttackedOnTable(int PCID, int APID)
{
        // save old pos
        piece[PCID]->SetOldPositions(piece[PCID]->GetY(),piece[PCID]->GetX());
        // move piece
        piece[PCID]->PieceMovedToNewCoords(piece[APID]->GetY(),piece[APID]->GetX());
        // delete piece + image
        piece[APID]->SetGameObjectState(false);
        PicturePiece[APID]->Visible = false;
        // image moving
        PicturePiece[PCID]->Top = board[piece[PCID]->GetY()][piece[PCID]->GetX()]->GetY();
        PicturePiece[PCID]->Left = board[piece[PCID]->GetY()][piece[PCID]->GetX()]->GetX();
        // pawn to queen
        if(piece[PCID]->GetType() == PAWN and ((piece[PCID]->GetY() == 0 and !piece[PCID]->GetColor()) or (piece[PCID]->GetY() == 7 and piece[PCID]->GetColor())))
        {
                piece[PCID]->PawnToQueen();
                if(!piece[PCID]->GetColor())
                        PicturePiece[PCID]->Picture->LoadFromFile(rsQueenW);
                else
                        PicturePiece[PCID]->Picture->LoadFromFile(rsQueenB);
        }
        // en passant pawn move
        for(int i = 0 ; i < TABLE_LENGTH*2 ; i++)
                if(ChessRound.en_passant[i] != 0)
                {
                        ChessRound.en_passant[i]++;
                        ChessRound.Can_en_passant = false;
                }
        // increment round turn
        ChessRound.NextTurn();
        // check on king + checkmate on king if exist
        ChessRound.GameMatchStateVerification(PCID,true);
}

// PIECE CLICK ONLY
void __fastcall ChessPiece::PieceClicked(TObject *Sender)
{
        bool canSearchForPos = true;

        // server - alb / client - negru
        if(fMain->ServerSocket->Active and ChessRound.GetGameRoundTurn() % 2 == 1)
                canSearchForPos = false;
        if(fMain->ClientSocket->Active and ChessRound.GetGameRoundTurn() % 2 == 0)
                canSearchForPos = false;

        // CONDITII DACA APESI ALTA CULOARE A PIESEI TALE
        for(int i = 0 ; i < PIECES_MAX ; i++)
                if(PicturePiece[i] == Sender and !ChessRound.pieceClickedFirst and canSearchForPos)
                {
                        if(ChessRound.GetGameRoundTurn() % 2 == 0 and piece[i]->GetColor() != WHITE)
                                canSearchForPos = false;
                        if(ChessRound.GetGameRoundTurn() % 2 == 1 and piece[i]->GetColor() != BLACK)
                                canSearchForPos = false;
                }

        // daca meciul nu este activ atunci playerul nu poate selecta piesa
        if(!ChessRound.IsGameRoundActive())
                canSearchForPos = false;

        if(canSearchForPos)  // if can, then do it
        {
                for(int i = 0 ; i < PIECES_MAX ; i++)
                        if(PicturePiece[i] == Sender)
                        {
                                if(ChessRound.pieceClickedFirst and (this->GetColor() != ChessRound.lastColorPieceSelected))
                                {
                                        ChessRound.LastPieceAttackedID = i;
                                        bool CanAttackOnBoard = piece[ChessRound.LastPieceClickedID]->PieceAttack(piece[ChessRound.LastPieceAttackedID]);
                                        if(CanAttackOnBoard)
                                        {
                                                piece[ChessRound.LastPieceClickedID]->PieceAttackedOnTable(ChessRound.LastPieceClickedID,ChessRound.LastPieceAttackedID);
                                                // transmiteri de socket
                                                if(fMain->ServerSocket->Active)
                                                        fMain->ServerSocket->Socket->Connections[0]->SendText("[ATTACK]" + IntToStr(ChessRound.LastPieceClickedID) + "|" + IntToStr(ChessRound.LastPieceAttackedID));
                                                if(fMain->ClientSocket->Active)
                                                        fMain->ClientSocket->Socket->SendText("[ATTACK]" + IntToStr(ChessRound.LastPieceClickedID) + "|" + IntToStr(ChessRound.LastPieceAttackedID));
                                        } // altfel nu poate ataca acolo
                                        /* <-------- delete green dots ----------> */
                                        ChessPiece del;
                                        del.DeleteGreenDot();
                                        /* <-------------------------------------> */
                                        ChessRound.AnotherPieceClicked = false;
                                        ChessRound.pieceClickedFirst = false;
                                        //===== schimbare cursor pointer default =======//
                                        for(int i = 0 ; i < TABLE_LENGTH ; i++)
                                                for(int j = 0 ; j < TABLE_LENGTH ; j++)
                                                        PictureBoard[i][j]->Cursor = crDefault;
                                        //============================================//
                                }
                                else
                                {
                                        if(ChessRound.AnotherPieceClicked)
                                        {
                                                ChessPiece del;
                                                del.DeleteGreenDot();
                                        }
                                        ChessRound.lastColorPieceSelected = this->GetColor();
                                        ChessRound.LastPieceClickedID = i;
                                        this->ShowWhereToMove();    // asta arata green dots
                                        PictureBoard[piece[i]->GetY()][piece[i]->GetX()]->Picture->LoadFromFile(rsPieceClickedLines); // asta pune liniile albastre
                                        if(fMain->ServerSocket->Active)
                                                fMain->ServerSocket->Socket->Connections[0]->SendText("[ThisPieceSelected]" + IntToStr(i));
                                        if(fMain->ClientSocket->Active)
                                                fMain->ClientSocket->Socket->SendText("[ThisPieceSelected]" + IntToStr(i));
                                        ChessRound.AnotherPieceClicked = true;
                                        ChessRound.pieceClickedFirst = true;
                                        //===== schimbare cursor pointer handpoint =======//
                                        for(int i = 0 ; i < TABLE_LENGTH ; i++)
                                                for(int j = 0 ; j < TABLE_LENGTH ; j++)
                                                        PictureBoard[i][j]->Cursor = crHandPoint;
                                        //==============================================//
                                }
                        }
        }
}





































