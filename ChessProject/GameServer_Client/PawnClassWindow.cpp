//---------------------------------------------------------------------------
#include <vcl.h>
#include <memory>
#pragma hdrstop
#include "ChessMyClasses.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------


// PAWN LOGIC

bool ChessPiece::PawnMechanic(int i, int j)  // Mecanica Pion
{
        bool canMove = false;
        if(!board[i][j]->IsGameObjectHere())  
        {
                if(!this->GetColor())
                {
                        if(this->GetY() - 1 == i and this->GetX() == j)
                        {
                                canMove = true;
                        }
                        if(this->GetY() == 6 and !board[this->GetY()-1][this->GetX()]->IsGameObjectHere() and this->GetY() - 2 == i and this->GetX() == j)
                        {
                                canMove = true;
                        }
                        // en passant in sah la pioni
                        if(this->GetY() == 3 and i == 2 and (this->GetX() - 1 == j or this->GetX() + 1 == j))
                        {
                                for(int k = 8; k < TABLE_LENGTH*2 ; k++)
                                        if(ChessRound.en_passant[k] == 2) // conditia sa stim daca nu a stat mai mult decat o runda acolo
                                                if(piece[k]->GetY() == 3 and piece[k]->GetY() - 1 == i and piece[k]->GetX() == j)
                                                        if(this->GetX() - 1 == piece[k]->GetX() or this->GetX() + 1 == piece[k]->GetX())
                                                        {
                                                                        canMove = true;
                                                                        ChessRound.Can_en_passant = true;
                                                                        ChessRound.en_passant_id = k;
                                                        }
                        }
                }
                else
                {
                        if(this->GetY() + 1 == i and this->GetX() == j)
                        {
                                canMove = true;
                        }
                        if(this->GetY() == 1 and !board[this->GetY()+1][this->GetX()]->IsGameObjectHere() and this->GetY() + 2 == i and this->GetX() == j)
                        {
                                canMove = true;
                        }
                         // en passant pt piesele negre
                        if(this->GetY() == 4 and i == 5 and (this->GetX() - 1 == j or this->GetX() + 1 == j))
                        {
                                for(int k = 0; k < TABLE_LENGTH ; k++)
                                        if(ChessRound.en_passant[k] == 2) // conditia sa stim daca nu a stat mai mult decat o runda acolo
                                                if(piece[k]->GetY() == 4 and piece[k]->GetY() + 1 == i and piece[k]->GetX() == j)
                                                        if(this->GetX() - 1 == piece[k]->GetX() or this->GetX() + 1 == piece[k]->GetX())
                                                        {
                                                                        canMove = true;
                                                                        ChessRound.Can_en_passant = true;
                                                                        ChessRound.en_passant_id = k;
                                                        }
                        }
                }
        }

        if(canMove)
                canMove = this->CanPieceMoveThere(i,j);
        return canMove;
}



bool ChessPiece::PawnAttack(ChessPiece *AttackedPiece) // PION IN MOD DE ATAC
{
        bool canMove = false;
        if(!AttackedPiece->isPieceKing())
        {
                if(!this->GetColor())
                {
                        if(this->GetY() - 1 == AttackedPiece->GetY() and (this->GetX() - 1 == AttackedPiece->GetX() or this->GetX() + 1 == AttackedPiece->GetX()))
                        {
                                canMove = true;
                        }
                }
                else
                {
                        if(this->GetY() + 1 == AttackedPiece->GetY() and (this->GetX() - 1 == AttackedPiece->GetX() or this->GetX() + 1 == AttackedPiece->GetX()))
                        {
                                canMove = true;
                        }
                }
        }
        if(canMove)
                canMove = this->CanPieceAttackThere(AttackedPiece);
        return canMove;
}

void ChessPiece::PawnToQueen()
{
        this->SetType(QUEEN);
}





