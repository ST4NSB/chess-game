//---------------------------------------------------------------------------
#include <vcl.h>
#include <memory>
#pragma hdrstop
#include "ChessMyClasses.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------


// KING LOGIC

bool ChessPiece::isPieceKing()
{
        return (this->GetType() == KING);
}

bool ChessPiece::KingMechanic(int i, int j)
{
        bool canMove = false;
        int AvaibleMovesY[8] = {0,-1,-1,-1,0,1,1,1};
        int AvaibleMovesX[8] = {-1,-1,0,1,1,1,0,-1};
        if(!board[i][j]->IsGameObjectHere())
        {
                for(int iter = 0 ; iter < 8 ; iter++)
                {
                        if(this->GetY() + AvaibleMovesY[iter] == i and this->GetX() + AvaibleMovesX[iter] == j)
                                if(this->CanKingMoveThere(i,j))
                                {
                                        canMove = true;
                                }
                }
                if(!this->GetColor()) // white
                {
                        // ROCADA MARE WHITE
                        if(piece[24]->GetGameObjectState() and !ChessRound.CastlingPieceMovedWhite[0] and !ChessRound.CastlingPieceMovedWhite[1] and i==7 and this->GetX() - 2 == j and !board[i][j]->IsGameObjectHere() and !board[i][j+1]->IsGameObjectHere() and !board[i][j-1]->IsGameObjectHere())
                                if(this->CanKingMoveThere(i,j) and this->CanKingMoveThere(i,j+1))
                                        if(!this->isKingInCheck())
                                        {
                                                ChessRound.CastlingTypeNumber[0] = true;
                                                if(fMain->ServerSocket->Active)
                                                        fMain->ServerSocket->Socket->Connections[0]->SendText("[CAN_CASTLING_NR]" + IntToStr(0));
                                                if(fMain->ClientSocket->Active)
                                                        fMain->ClientSocket->Socket->SendText("[CAN_CASTLING_NR]" + IntToStr(0));
                                                canMove = true;
                                                ShowMessagePos("You are proceeding for a Big CASTLE!",fMain->Left + fMain->ClientWidth / 2, fMain->Top + fMain->ClientHeight / 2);
                                        }
                        // ROCADA MICA WHITE
                        if(piece[25]->GetGameObjectState() and !ChessRound.CastlingPieceMovedWhite[0] and !ChessRound.CastlingPieceMovedWhite[2] and i==7 and this->GetX() + 2 == j and !board[i][j]->IsGameObjectHere() and !board[i][j-1]->IsGameObjectHere())
                                if(this->CanKingMoveThere(i,j) and this->CanKingMoveThere(i,j-1))
                                        if(!this->isKingInCheck())
                                        {
                                                ChessRound.CastlingTypeNumber[1] = true;
                                                if(fMain->ServerSocket->Active)
                                                        fMain->ServerSocket->Socket->Connections[0]->SendText("[CAN_CASTLING_NR]" + IntToStr(1));
                                                if(fMain->ClientSocket->Active)
                                                        fMain->ClientSocket->Socket->SendText("[CAN_CASTLING_NR]" + IntToStr(1));
                                                canMove = true;
                                                ShowMessagePos("You are proceeding for a Small CASTLE!",fMain->Left + fMain->ClientWidth / 2, fMain->Top + fMain->ClientHeight / 2);
                                        }
                }
                else
                {
                        // ROCADA MARE BLACK
                        if(piece[26]->GetGameObjectState() and !ChessRound.CastlingPieceMovedBlack[0] and !ChessRound.CastlingPieceMovedBlack[1] and i==0 and this->GetX() - 2 == j and !board[i][j]->IsGameObjectHere() and !board[i][j+1]->IsGameObjectHere() and !board[i][j-1]->IsGameObjectHere())
                                if(this->CanKingMoveThere(i,j) and this->CanKingMoveThere(i,j+1)) 
                                        if(!this->isKingInCheck())
                                        {
                                                ChessRound.CastlingTypeNumber[2] = true;
                                                if(fMain->ServerSocket->Active)
                                                        fMain->ServerSocket->Socket->Connections[0]->SendText("[CAN_CASTLING_NR]" + IntToStr(2));
                                                if(fMain->ClientSocket->Active)
                                                        fMain->ClientSocket->Socket->SendText("[CAN_CASTLING_NR]" + IntToStr(2));
                                                canMove = true;
                                                ShowMessagePos("You are proceeding for a Big CASTLE!",fMain->Left + fMain->ClientWidth / 2, fMain->Top + fMain->ClientHeight / 2);
                                        }
                        // ROCADA MICA BLACK
                        if(piece[27]->GetGameObjectState() and !ChessRound.CastlingPieceMovedBlack[0] and !ChessRound.CastlingPieceMovedBlack[2] and i==0 and this->GetX() + 2 == j and !board[i][j]->IsGameObjectHere() and !board[i][j-1]->IsGameObjectHere())
                                if(this->CanKingMoveThere(i,j) and this->CanKingMoveThere(i,j-1))
                                        if(!this->isKingInCheck())
                                        {
                                                ChessRound.CastlingTypeNumber[3] = true;
                                                if(fMain->ServerSocket->Active)
                                                        fMain->ServerSocket->Socket->Connections[0]->SendText("[CAN_CASTLING_NR]" + IntToStr(3));
                                                if(fMain->ClientSocket->Active)
                                                        fMain->ClientSocket->Socket->SendText("[CAN_CASTLING_NR]" + IntToStr(3));
                                                canMove = true;
                                                ShowMessagePos("You are proceeding for a Small CASTLE!",fMain->Left + fMain->ClientWidth / 2, fMain->Top + fMain->ClientHeight / 2);
                                        }
                }
        }
        return canMove;
}

bool ChessPiece::KingAttack(ChessPiece *AttackedPiece)
{
        bool canMove = false;
        int AvaibleMovesY[8] = {0,-1,-1,-1,0,1,1,1};
        int AvaibleMovesX[8] = {-1,-1,0,1,1,1,0,-1};
        if(!AttackedPiece->isPieceKing())
        {
                for(int iter = 0 ; iter < 8 ; iter++)
                        if(this->GetY() + AvaibleMovesY[iter] == AttackedPiece->GetY() and this->GetX() + AvaibleMovesX[iter] == AttackedPiece->GetX())
                                if(this->CanKingMoveThere(AttackedPiece->GetY(), AttackedPiece->GetX()))
                                {
                                        canMove = true;
                                }
        }
        return canMove;
}

bool ChessPiece::isKingInCheck()
{
        bool KingCheck = false;
        for(int i = 0 ; i < PIECES_MAX ; i++)
        {
                if(piece[i]->GetGameObjectState())
                {
	                if(piece[i]->GetType() == PAWN)
	                        if(piece[i]->GetColor() != this->GetColor() and !this->GetColor())
	                        {
	                                if(this->GetY()-1 == piece[i]->GetY() and this->GetX()-1 == piece[i]->GetX())
	                                        KingCheck = true;
	                                if(this->GetY()-1 == piece[i]->GetY() and this->GetX()+1 == piece[i]->GetX())
	                                        KingCheck = true;
	                        }
	                        else if(piece[i]->GetColor() != this->GetColor() and this->GetColor())
	                        {
	                                if(this->GetY()+1 == piece[i]->GetY() and this->GetX()-1 == piece[i]->GetX())
	                                        KingCheck = true;
	                                if(this->GetY()+1 == piece[i]->GetY() and this->GetX()+1 == piece[i]->GetX())
	                                        KingCheck = true;
	                        }
	                switch(piece[i]->GetType())
	                {
	                        case KNIGHT:
	                                if(this->GetColor() != piece[i]->GetColor())
	                                {
	                                        int avaibleMovesY[8] = {-1,-2,-2,-1,1,2,2,1};
	                                        int avaibleMovesX[8] = {-2,-1,1,2,2,1,-1,-2};
	                                        for(int iter = 0 ; iter < 8 ; iter++)
	                                                if(this->GetY() + avaibleMovesY[iter] == piece[i]->GetY() and this->GetX() + avaibleMovesX[iter] == piece[i]->GetX())
	                                                        KingCheck = true;
	                                }
	                                break;
	                        case BISHOP:
	                                if(this->GetColor() != piece[i]->GetColor())
	                                {
	                                        int AvaibleMovesY[4] = {-1,-1,1,1};
	                                        int AvaibleMovesX[4] = {-1,1,1,-1};
	                                        int iter = 0;
	                                                bool placeHere = false;
	                                                while(iter < 4)
	                                                {
	                                                        if(this->GetY() + AvaibleMovesY[iter] == piece[i]->GetY() and this->GetX() + AvaibleMovesX[iter] == piece[i]->GetX())
	                                                        {
	                                                                break;
	                                                        }
	                                                        else
	                                                        {
	                                                                AvaibleMovesY[iter] < 0 ? AvaibleMovesY[iter]-- : AvaibleMovesY[iter]++;
	                                                                AvaibleMovesX[iter] < 0 ? AvaibleMovesX[iter]-- : AvaibleMovesX[iter]++;
	                                                                if(AvaibleMovesY[iter] <= -8 or AvaibleMovesY[iter] >= 8 or AvaibleMovesX[iter] >= 8 or AvaibleMovesX[iter] <= -8)
	                                                                iter++;
	                                                        }
	                                                }
	                                                if(iter != 4)
	                                                {
	                                                        placeHere = true;
	                                                        int maxPos = abs(this->GetY() - piece[i]->GetY());
	                                                        bool objectPieceKing = false;
	                                                        for(int rep = 0 ; rep < maxPos ; rep++)
	                                                        {
	                                                                int CheckForY = this->GetY() + AvaibleMovesY[iter];
	                                                                int CheckForX = this->GetX() + AvaibleMovesX[iter];
	                                                                if(board[CheckForY][CheckForX]->IsGameObjectHere())
	                                                                {
	                                                                        if(!objectPieceKing)
	                                                                                objectPieceKing = true;
	                                                                        else
	                                                                        {
	                                                                                placeHere = false;
	                                                                        }
	                                                                }
	                                                        AvaibleMovesY[iter] < 0 ? AvaibleMovesY[iter]++ : AvaibleMovesY[iter]--;
	                                                        AvaibleMovesX[iter] < 0 ? AvaibleMovesX[iter]++ : AvaibleMovesX[iter]--;
	                                                        }
	                                                }
	                                                if(placeHere)
	                                                        KingCheck = true;
	                                }
	                                break;
	                        case ROOK:
	                                if(this->GetColor() != piece[i]->GetColor())
	                                {
	                                        int AvaibleMovesY[4] = {-1,0,1,0};
	                                        int AvaibleMovesX[4] = {0,1,0,-1};
	                                        int iter = 0;
	                                                bool placeHere = false;
	                                                while(iter < 4)
	                                                {
	                                                        if(this->GetY() + AvaibleMovesY[iter] == piece[i]->GetY() and this->GetX() + AvaibleMovesX[iter] == piece[i]->GetX())
	                                                        {
	                                                                break;
	                                                        }
	                                                        else
	                                                        {
	                                                                if(AvaibleMovesY[iter] != 0)
	                                                                        AvaibleMovesY[iter] < 0 ? AvaibleMovesY[iter]-- : AvaibleMovesY[iter]++;
	                                                                if(AvaibleMovesX[iter] != 0)
	                                                                        AvaibleMovesX[iter] < 0 ? AvaibleMovesX[iter]-- : AvaibleMovesX[iter]++;
	                                                                if(AvaibleMovesY[iter] <= -8 or AvaibleMovesY[iter] >= 8 or AvaibleMovesX[iter] >= 8 or AvaibleMovesX[iter] <= -8)
	                                                                        iter++;
	                                                        }
	                                                }
	                                                if(iter != 4)
	                                                {
	                                                        placeHere = true;
	                                                        int maxPos = abs(this->GetY() - piece[i]->GetY());
	                                                        if(!maxPos)
	                                                                maxPos = abs(this->GetX() - piece[i]->GetX());
	                                                        bool objectPieceKing = false;
	                                                        for(int rep = 0 ; rep < maxPos ; rep++)
	                                                        {
	                                                                int CheckForY = this->GetY() + AvaibleMovesY[iter];
	                                                                int CheckForX = this->GetX() + AvaibleMovesX[iter];
	                                                                if(board[CheckForY][CheckForX]->IsGameObjectHere())
	                                                                {
	                                                                        if(!objectPieceKing)
	                                                                                objectPieceKing = true;
	                                                                        else
	                                                                        {
	                                                                                placeHere = false;
	                                                                        }
	                                                                }
	                                                                if(AvaibleMovesY[iter] != 0)
	                                                                        AvaibleMovesY[iter] < 0 ? AvaibleMovesY[iter]++ : AvaibleMovesY[iter]--;
	                                                                if(AvaibleMovesX[iter] != 0)
	                                                                        AvaibleMovesX[iter] < 0 ? AvaibleMovesX[iter]++ : AvaibleMovesX[iter]--;
	                                                        }
	                                                }
	                                                if(placeHere)
	                                                        KingCheck = true;
	                                }
	                                break;
	                        case QUEEN:
	                                if(this->GetColor() != piece[i]->GetColor())
	                                {
	                                        int AvaibleMovesY[4] = {-1,-1,1,1};
	                                        int AvaibleMovesX[4] = {-1,1,1,-1};
	                                        int iter = 0;
	                                                bool placeHere = false;
	                                                while(iter < 4)
	                                                {
	                                                        if(this->GetY() + AvaibleMovesY[iter] == piece[i]->GetY() and this->GetX() + AvaibleMovesX[iter] == piece[i]->GetX())
	                                                        {
	                                                                break;
	                                                        }
	                                                        else
	                                                        {
	                                                                AvaibleMovesY[iter] < 0 ? AvaibleMovesY[iter]-- : AvaibleMovesY[iter]++;
	                                                                AvaibleMovesX[iter] < 0 ? AvaibleMovesX[iter]-- : AvaibleMovesX[iter]++;
	                                                                if(AvaibleMovesY[iter] <= -8 or AvaibleMovesY[iter] >= 8 or AvaibleMovesX[iter] >= 8 or AvaibleMovesX[iter] <= -8)
	                                                                iter++;
	                                                        }
	                                                }
	                                                if(iter != 4)
	                                                {
	                                                        placeHere = true;
	                                                        int maxPos = abs(this->GetY() - piece[i]->GetY());
	                                                        bool objectPieceKing = false;
	                                                        for(int rep = 0 ; rep < maxPos ; rep++)
	                                                        {
	                                                                int CheckForY = this->GetY() + AvaibleMovesY[iter];
	                                                                int CheckForX = this->GetX() + AvaibleMovesX[iter];
	                                                                if(board[CheckForY][CheckForX]->IsGameObjectHere())
	                                                                {
	                                                                        if(!objectPieceKing)
	                                                                                objectPieceKing = true;
	                                                                        else
	                                                                        {
	                                                                                placeHere = false;
	                                                                        }
	                                                                }
	                                                        AvaibleMovesY[iter] < 0 ? AvaibleMovesY[iter]++ : AvaibleMovesY[iter]--;
	                                                        AvaibleMovesX[iter] < 0 ? AvaibleMovesX[iter]++ : AvaibleMovesX[iter]--;
	                                                        }
	                                                }
	                                                if(placeHere)
	                                                        KingCheck = true;
	                                }
	                                if(this->GetColor() != piece[i]->GetColor())
	                                {
	                                        int AvaibleMovesY[4] = {-1,0,1,0};
	                                        int AvaibleMovesX[4] = {0,1,0,-1};
	                                        int iter = 0;
	                                                bool placeHere = false;
	                                                while(iter < 4)
	                                                {
	                                                        if(this->GetY() + AvaibleMovesY[iter] == piece[i]->GetY() and this->GetX() + AvaibleMovesX[iter] == piece[i]->GetX())
	                                                        {
	                                                                break;
	                                                        }
	                                                        else
	                                                        {
	                                                                if(AvaibleMovesY[iter] != 0)
	                                                                        AvaibleMovesY[iter] < 0 ? AvaibleMovesY[iter]-- : AvaibleMovesY[iter]++;
	                                                                if(AvaibleMovesX[iter] != 0)
	                                                                        AvaibleMovesX[iter] < 0 ? AvaibleMovesX[iter]-- : AvaibleMovesX[iter]++;
	                                                                if(AvaibleMovesY[iter] <= -8 or AvaibleMovesY[iter] >= 8 or AvaibleMovesX[iter] >= 8 or AvaibleMovesX[iter] <= -8)
	                                                                        iter++;
	                                                        }
	                                                }
	                                                if(iter != 4)
	                                                {
	                                                        placeHere = true;
	                                                        int maxPos = abs(this->GetY() - piece[i]->GetY());
	                                                        if(!maxPos)
	                                                                maxPos = abs(this->GetX() - piece[i]->GetX());
	                                                        bool objectPieceKing = false;
	                                                        for(int rep = 0 ; rep < maxPos ; rep++)
	                                                        {
	                                                                int CheckForY = this->GetY() + AvaibleMovesY[iter];
	                                                                int CheckForX = this->GetX() + AvaibleMovesX[iter];
	                                                                if(board[CheckForY][CheckForX]->IsGameObjectHere())
	                                                                {
	                                                                        if(!objectPieceKing)
	                                                                                objectPieceKing = true;
	                                                                        else
	                                                                        {
	                                                                                placeHere = false;
	                                                                        }
	                                                                }
	                                                                if(AvaibleMovesY[iter] != 0)
	                                                                        AvaibleMovesY[iter] < 0 ? AvaibleMovesY[iter]++ : AvaibleMovesY[iter]--;
	                                                                if(AvaibleMovesX[iter] != 0)
	                                                                        AvaibleMovesX[iter] < 0 ? AvaibleMovesX[iter]++ : AvaibleMovesX[iter]--;
	                                                        }
	                                                }
	                                                if(placeHere)
	                                                        KingCheck = true;
	                                }
	                                break;
                                case KING:
                                        if(this->GetColor() != piece[i]->GetColor())
                                        {
                                                int avaibleMovesY[8] = {0,-1,-1,-1,0,1,1,1};
                                                int avaibleMovesX[8] = {-1,-1,0,1,1,1,0,-1};
	                                        for(int iter = 0 ; iter < 8 ; iter++)
	                                                if(this->GetY() + avaibleMovesY[iter] == piece[i]->GetY() and this->GetX() + avaibleMovesX[iter] == piece[i]->GetX())
	                                                        KingCheck = true;
                                        }
                                        break;
	                        }
                }
        }

        return KingCheck;
}


bool ChessPiece::CanKingMoveThere(int posY, int posX, bool CheckOnlyAround)
{
        if(CheckOnlyAround)
        {
                int AvaibleMovesY[8] = {0,-1,-1,-1,0,1,1,1};
                int AvaibleMovesX[8] = {-1,-1,0,1,1,1,0,-1};
                bool AvaiblePosVerif = false;
                for(int k = 0; k < 8 ; k++)
                        if(this->GetY() + AvaibleMovesY[k] == posY and this->GetX() + AvaibleMovesX[k] == posX)
                                AvaiblePosVerif = true;
                if(!AvaiblePosVerif)
                {
                        return AvaiblePosVerif;
                }
        }

        bool KingCanMove = true;
        bool KingColor = this->GetColor();

        for(int i = 0 ; i < PIECES_MAX ; i++)
                if(piece[i]->GetY() == posY and piece[i]->GetX() == posX)
                        if(KingColor == piece[i]->GetColor())
                                if(piece[i]->GetGameObjectState())
                                        KingCanMove = false;

        if(!KingCanMove)
                return KingCanMove;
        else
        {
                bool PieceExisted;
                int PieceFoundAtID;
                int actualY = this->GetY();
                int actualX = this->GetX();
                if(board[posY][posX]->IsGameObjectHere())
                {
                        this->SetY(posY);
                        this->SetX(posX);
                        board[actualY][actualX]->DeleteGameObjectHere();
                        PieceExisted = true;
                        for(int i = 0 ; i < PIECES_MAX - 2 ; i++)
                                if(piece[i]->GetY() == posY and piece[i]->GetX() == posX)
                                        if(piece[i]->GetGameObjectState())     // piesa e automat opusul culorii regelui
                                        {
                                                piece[i]->SetGameObjectState(false);
                                                PieceFoundAtID = i;
                                        }
                }
                else
                {
                        this->PieceMovedToNewCoords(posY,posX);
                        PieceExisted = false;
                }

                if(this->isKingInCheck())
                        KingCanMove = false;

                if(PieceExisted)
                {
                        this->SetY(actualY);
                        this->SetX(actualX);
                        board[actualY][actualX]->SetGameObjectHere();
                        piece[PieceFoundAtID]->SetGameObjectState(true);
                }
                else
                {
                        this->PieceMovedToNewCoords(actualY,actualX);
                }
                return KingCanMove;
        }
}
