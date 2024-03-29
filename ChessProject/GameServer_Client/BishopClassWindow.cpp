//---------------------------------------------------------------------------
#include <vcl.h>
#include <memory>
#pragma hdrstop
#include "ChessMyClasses.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

// BISHOP LOGIC

bool ChessPiece::BishopMechanic(int i, int j)
{
        bool canMove = false;
        int AvaibleMovesY[4] = {-1,-1,1,1};
        int AvaibleMovesX[4] = {-1,1,1,-1};
        if(!board[i][j]->IsGameObjectHere())
        {
                if(!this->GetColor() or this->GetColor())
                {
                        int iter = 0;
                        while(iter < 4)
                        {
                                if(this->GetY() + AvaibleMovesY[iter] == i and this->GetX() + AvaibleMovesX[iter] == j)
                                {
                                        canMove = true;
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
                                int maxPos = abs(this->GetY() - i);
                                for(int rep = 0 ; rep < maxPos ; rep++)
                                {
                                        int CheckForY = this->GetY() + AvaibleMovesY[iter];
                                        int CheckForX = this->GetX() + AvaibleMovesX[iter];
                                        if(board[CheckForY][CheckForX]->IsGameObjectHere())
                                        {
                                                canMove = false;
                                        }
                                        AvaibleMovesY[iter] < 0 ? AvaibleMovesY[iter]++ : AvaibleMovesY[iter]--;
                                        AvaibleMovesX[iter] < 0 ? AvaibleMovesX[iter]++ : AvaibleMovesX[iter]--;
                                }
                        }
                }
        }
        if(canMove)
                canMove = this->CanPieceMoveThere(i,j);
        return canMove;
}

bool ChessPiece::BishopAttack(ChessPiece *AttackedPiece)
{
        bool canMove = false;
        int AvaibleMovesY[4] = {-1,-1,1,1};
        int AvaibleMovesX[4] = {-1,1,1,-1};
        if(!AttackedPiece->isPieceKing())
        {
                if(!this->GetColor() or this->GetColor())
                {
                        int iter = 0;
                        while(iter < 4)
                        {
                                if(this->GetY() + AvaibleMovesY[iter] == AttackedPiece->GetY() and this->GetX() + AvaibleMovesX[iter] == AttackedPiece->GetX())
                                {
                                        canMove = true;
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
                                int maxPos = abs(this->GetY() - AttackedPiece->GetY());
                                bool objectPieceToCaptureFound = false;
                                for(int rep = 0 ; rep < maxPos ; rep++)
                                {
                                        int CheckForY = this->GetY() + AvaibleMovesY[iter];
                                        int CheckForX = this->GetX() + AvaibleMovesX[iter];
                                        if(board[CheckForY][CheckForX]->IsGameObjectHere())
                                        {
                                                if(!objectPieceToCaptureFound)   // pozitiile checkforxy tin pozitia unde este deja un obiect tip piesa acolo si de aceea trb sa tinem cont de acelea
                                                        objectPieceToCaptureFound = true;
                                                else
                                                {
                                                        canMove = false;
                                                }

                                        }
                                        AvaibleMovesY[iter] < 0 ? AvaibleMovesY[iter]++ : AvaibleMovesY[iter]--;
                                        AvaibleMovesX[iter] < 0 ? AvaibleMovesX[iter]++ : AvaibleMovesX[iter]--;
                                }
                        }
                }
        }
        if(canMove)
                canMove = this->CanPieceAttackThere(AttackedPiece);
        return canMove;
}
