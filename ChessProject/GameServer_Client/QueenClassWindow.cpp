//---------------------------------------------------------------------------
#include <vcl.h>
#include <memory>
#pragma hdrstop
#include "ChessMyClasses.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------


// QUEEN LOGIC

bool ChessPiece::QueenMechanic(int i, int j)
{
        bool canMove = this->RookMechanic(i,j);
        if(canMove)
                return canMove;
        else
                canMove = this->BishopMechanic(i,j);
        return canMove;
}

bool ChessPiece::QueenAttack(ChessPiece *AttackedPiece)
{
        bool canMove = this->RookAttack(AttackedPiece);
        if(canMove)
                return canMove;
        else
                canMove = this->BishopAttack(AttackedPiece);
        return canMove;
}

