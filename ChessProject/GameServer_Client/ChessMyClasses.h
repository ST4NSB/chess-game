//---------------------------------------------------------------------------
#ifndef ChessMyClassesH
#define ChessMyClassesH
#include "ChessApplication.h"
#include "ConnectionModalWindow.h"
/* =============== DEFINE ============== */
/* <---------------------------------> */
#define and &&
#define or ||
#define TABLE_LENGTH 8    //  cate patratele contine o linie/coloana
#define PIECES_MAX 32  // toate piesele din joc
#define WHITE false    // piesa alba
#define BLACK true     // piesa neagra
#define PAWN 1         // Type -> pawn
#define KNIGHT 2
#define BISHOP 3
#define ROOK 4
#define QUEEN 5
#define KING 6
#define WHITE_KING piece[30]
#define BLACK_KING piece[31]
/* ====================================== */
//---------------------------------------------------------------------------
/* =============== CLASSES CHESS =================== */
class GameObject
{
private:
        bool GameObjectExistence;  // true daca exista / false daca NU exista piesa pe board
public:
        // con & dec
        GameObject();
        virtual ~GameObject();
        // logic
        void SetGameObjectHere();
        bool IsGameObjectHere();
        void DeleteGameObjectHere();
};
class Axis
{
private:
        int y;
        int x;
        int oldposy;
        int oldposx;
public:
        // con & dec
        Axis();
        Axis(int y, int x);
        virtual ~Axis();
        // logic
        int GetY();
        int GetX();
        void SetY(int y);
        void SetX(int x);
        int GetOldY();
        int GetOldX();
        void SetOldPositions(int y, int x);
};
class ChessBoard : public Axis, public GameObject
{
public:
        // con & dec
        ChessBoard(int y,int x);
        virtual ~ChessBoard();
        // logic
        void __fastcall BoardClick(TObject *Sender);
};
class Attributes : public Axis
{
private:
        int type; // 1pawn/2knight/3bishop/4rook/5queen/6king
        bool color; // false - WHITE ; true - BLACK // int pt mai multe culori
        bool GameObjectState; // true - daca piesa inca mai e pe tabla / false - daca piesa nu e pe tabla
public:
        // con & dec
        Attributes();
        Attributes(int type, int color, int y, int x, bool ObjectState);
        virtual ~Attributes();
        // logic
        void SetType(int type);
        int GetType();
        void SetColor(bool color);
        bool GetColor();
        void SetGameObjectState(bool newState);   // false pt non existence // true pt existence
        bool GetGameObjectState();
};
class ChessPiece : public Attributes
{
public:
        // constructor & destuctor
        ChessPiece(); 
        ChessPiece(int type,bool color,int y,int x,bool ObjectState = true);
        virtual ~ChessPiece();
        // metode != construtor
        void PieceMovedToNewCoords(int posY, int posX, bool DelActualPos = true);
        void __fastcall PieceClicked(TObject *Sender);
        // arata green dots unde poti muta
        void ShowWhereToMove();
        void DeleteGreenDot();
        // daca piece pot muta aici daca regele va intra in sah
        bool CanPieceMoveThere(int i, int j); // != king
        bool CanPieceMoveToSaveKing(int posY,int posX); // verifica daca piesele pot sa stea in fata regelui care e in sah
        bool CanPieceAttackThere(ChessPiece *AttackedPiece);  // != king
        // data pt gamelog
        void GetDataForMove(int MatchState, bool attacked,bool &DataForCastlingByWhite,bool &DataForCastlingByBlack,int newY, int newX,int oldY, int oldX);
        void ConvertAxisToChessNotation(String &str_y, String &str_x, int y, int x);
        // mutari si atacuri
        bool PieceMechanic(int i,int j);
        bool PieceAttack(ChessPiece *AttackedPiece);
        // mutari,atacuri, mutari speciale pt sockets
        void PieceMovedOnTable(int PCID, int i, int j);
        void PieceAttackedOnTable(int PCID, int APID);
        void EN_PASSANT_PID(int PID);
        void CASTLING_ROOK_PID(int PID);
        void CASTLING_KING_PID(int PID);
        //pawn
        void PawnToQueen();
        bool PawnMechanic(int i, int j);
        bool PawnAttack(ChessPiece *AttackedPiece);
        //knight
        bool KnightMechanic(int i,int j);
        bool KnightAttack(ChessPiece *AttackedPiece);
        //bishop
        bool BishopMechanic(int i, int j);
        bool BishopAttack(ChessPiece *AttackedPiece);
        //rook
        bool RookMechanic(int i, int j);
        bool RookAttack(ChessPiece *AttackedPiece);
        //queen
        bool QueenMechanic(int i, int j);
        bool QueenAttack(ChessPiece *AttackedPiece);
        //king
        bool isPieceKing();
        bool KingMechanic(int i, int j);
        bool KingAttack(ChessPiece *AttackedPiece);
        bool isKingInCheck();
        bool CanKingMoveThere(int posY, int posX, bool CheckOnlyAround = false);
};

class ChessGame : public ChessPiece
{
private:
        bool GameState;  // true daca jocul e activ / false daca nu
	int GameTurn; // pt turnul jocului
public:
        // VARIABILE ajutatoare la joc
        bool pieceClickedFirst;
        bool lastColorPieceSelected;
        int LastPieceClickedID, LastPieceAttackedID ; //  pt piececlicked sa retina id-ul
        bool AnotherPieceClicked; // tine de greendot si deletegreendot
        // var pt castling si en_passant
        bool CastlingTypeNumber[4];
        bool CastlingPieceMovedWhite[3]; // rege_alb, tura1_alb (piece[24]) , tura2_alb (piece[25])
        bool CastlingPieceMovedBlack[3]; // rege_negru, tura1_negru (piece[26]), tura2_negru (piece[27])
        int ChessCastlingType;  // 24-tura de la 7,0 ; 25 - tura de la 7,7 ; 26 - tura de la 0,0 ; 27 - tura de la 0,7
        bool ChessCastlingMade[2]; // v[0] e pt white, v[1] pt black
        bool DataForCastlingByWhite;
        bool DataForCastlingByBlack;
        int en_passant[TABLE_LENGTH*2];
        bool Can_en_passant;
        int en_passant_id;
        // constructor & destructor
	ChessGame();
        virtual ~ChessGame();
        // logic
        void ResetGameRoundTurn();
	void NextTurn();
	int GetGameRoundTurn();
        void SetGameRoundTurn(int turn);
        void SetGameRoundState(bool active);
        bool IsGameRoundActive();
        // pt incepere joc
        void __fastcall CreateAndStartChessGame();
        void StartRoundofChess();
        // pt sfarsit de joc daca un player iese
        void __fastcall OnPlayerExit();
        // pt verificari daca exista sah mat sau nu
        int GameMatchState();  // return: -1 - pt sah oricarui rege, 0 - pt continuare daca regii nu sunt in sah, 1 - pt remiza, 2 - pt sah mat la alb, 3- pt sah mat la negru
        void GameMatchStateVerification(int PCID,bool attackedPiece = false);
};

/* ====================================================== */
/* =============== EXTERN PACKAGES =================== */
extern PACKAGE TfMain *fMain;
extern PACKAGE ChessGame ChessRound;
extern PACKAGE ChessBoard *board[8][8];
extern PACKAGE ChessPiece *piece[32];
extern PACKAGE TImage *PictureBoard[8][8];
extern PACKAGE TImage *PicturePiece[32];
extern PACKAGE TImage *GameChessBoard;
extern PACKAGE TMemo *GameLog;
//---------------------------------------------- //
extern PACKAGE const String ImagePath; // primul path
extern PACKAGE const String ImagePiecePath;
extern PACKAGE const String rsBoardServer;
extern PACKAGE const String rsBoardClient;
extern PACKAGE const String rsPawnW;// albe
extern PACKAGE const String rsRookW;
extern PACKAGE const String rsKnightW;
extern PACKAGE const String rsBishopW;
extern PACKAGE const String rsKingW;
extern PACKAGE const String rsQueenW;
extern PACKAGE const String rsPawnB;// negre
extern PACKAGE const String rsRookB;
extern PACKAGE const String rsKnightB;
extern PACKAGE const String rsBishopB;
extern PACKAGE const String rsKingB;
extern PACKAGE const String rsQueenB;
extern PACKAGE const String rsTransparent;
extern PACKAGE const String rsGreenDot;
extern PACKAGE const String rsPieceClickedLines;
// --------------------------------------------//
// <==================================================================>
//---------------------------------------------------------------------------
#endif
