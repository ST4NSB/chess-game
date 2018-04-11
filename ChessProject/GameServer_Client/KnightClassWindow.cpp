//---------------------------------------------------------------------------
#include <vcl.h>
#include <memory>
#pragma hdrstop
#include "ChessMyClasses.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

// KNIGHT LOGIC
bool ChessPiece::KnightMechanic(int i, int j)
{
        bool canMove = false;
        int avaibleMovesY[8] = {-1,-2,-2,-1,1,2,2,1};
        int avaibleMovesX[8] = {-2,-1,1,2,2,1,-1,-2};
        if(!board[i][j]->IsGameObjectHere())
        {
                if(!this->GetColor() or this->GetColor()) // white or black
                {
                        for(int iter = 0 ; iter < 8 ; iter++)
                                if(this->GetY() + avaibleMovesY[iter] == i and this->GetX() + avaibleMovesX[iter] == j)
                                {
                                        canMove = true;
                                }
                }
        }
        if(canMove)
                canMove = this->CanPieceMoveThere(i,j);
        return canMove;
}

bool ChessPiece::KnightAttack(ChessPiece *AttackedPiece)
{
        bool canMove = false;
        int avaibleMovesY[8] = {-1,-2,-2,-1,1,2,2,1};
        int avaibleMovesX[8] = {-2,-1,1,2,2,1,-1,-2};
        if(!AttackedPiece->isPieceKing())
        {
                if(!this->GetColor() or this->GetColor())
                {
                       for(int iter = 0 ; iter < 8 ; iter++)
                                if(this->GetY() + avaibleMovesY[iter] == AttackedPiece->GetY() and this->GetX() + avaibleMovesX[iter] == AttackedPiece->GetX())
                                {
                                        canMove = true;
                                }
                }
        }
        if(canMove)
                canMove = this->CanPieceAttackThere(AttackedPiece);
        return canMove;
}
