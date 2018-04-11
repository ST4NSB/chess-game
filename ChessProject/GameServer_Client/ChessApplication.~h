//---------------------------------------------------------------------------
#ifndef ChessApplicationH
#define ChessApplicationH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ScktComp.hpp>
//---------------------------------------------------------------------------
class TfMain : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *hjuh1;
        TMenuItem *NewGame1;
        TMenuItem *Help1;
        TMenuItem *Exit1;
        TMenuItem *Colors1;
        TMenuItem *BackgroundColor1;
        TMenuItem *GamelogColor1;
        TMenuItem *FontColor1;
        TMenuItem *FontSize1;
        TMenuItem *Resolution1;
        TMenuItem *N1280x8001;
        TMenuItem *About1;
        TMenuItem *N800x6001;
        TMenuItem *N1024x6001;
        TMenuItem *Grey1;
        TMenuItem *Blue1;
        TMenuItem *Black1;
        TMenuItem *White1;
        TMenuItem *Black2;
        TMenuItem *White2;
        TMenuItem *Teal1;
        TMenuItem *Maroon1;
        TMenuItem *Grey2;
        TMenuItem *Blue2;
        TMenuItem *Teal2;
        TMenuItem *Maroon2;
        TMenuItem *Black3;
        TMenuItem *White3;
        TMenuItem *Blue3;
        TMenuItem *Teal3;
        TMenuItem *Maroon3;
        TMenuItem *Grey3;
        TMenuItem *N151;
        TMenuItem *N181;
        TMenuItem *N241;
        TMenuItem *N182;
        TMenuItem *N301;
        TClientSocket *ClientSocket;
        TServerSocket *ServerSocket;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall NewGame1Click(TObject *Sender);
        void __fastcall Help1Click(TObject *Sender);
        void __fastcall About1Click(TObject *Sender);
        void __fastcall N1280x8001Click(TObject *Sender);
        void __fastcall N800x6001Click(TObject *Sender);
        void __fastcall N1024x6001Click(TObject *Sender);
        void __fastcall Grey1Click(TObject *Sender);
        void __fastcall Blue1Click(TObject *Sender);
        void __fastcall Black1Click(TObject *Sender);
        void __fastcall White1Click(TObject *Sender);
        void __fastcall Black2Click(TObject *Sender);
        void __fastcall White2Click(TObject *Sender);
        void __fastcall Teal1Click(TObject *Sender);
        void __fastcall Maroon1Click(TObject *Sender);
        void __fastcall Grey2Click(TObject *Sender);
        void __fastcall Blue2Click(TObject *Sender);
        void __fastcall Teal2Click(TObject *Sender);
        void __fastcall Maroon2Click(TObject *Sender);
        void __fastcall Black3Click(TObject *Sender);
        void __fastcall White3Click(TObject *Sender);
        void __fastcall Grey3Click(TObject *Sender);
        void __fastcall Blue3Click(TObject *Sender);
        void __fastcall Teal3Click(TObject *Sender);
        void __fastcall Maroon3Click(TObject *Sender);
        void __fastcall N151Click(TObject *Sender);
        void __fastcall N181Click(TObject *Sender);
        void __fastcall N241Click(TObject *Sender);
        void __fastcall N182Click(TObject *Sender);
        void __fastcall N301Click(TObject *Sender);
        void __fastcall ServerSocketAccept(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocketConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocketRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ServerSocketClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall FormConstrainedResize(TObject *Sender,
          int &MinWidth, int &MinHeight, int &MaxWidth, int &MaxHeight);
private:
public:
        __fastcall TfMain(TComponent* Owner);
        // Size variables
        int BoardDist;
        int BoardSize;
        int BoardStartY;
        int BoardStartX;
        int GamelogFontSize;
        int GamelogSize;
        int GamelogY;
        int GamelogX;
        int distPiece;
        int imageSize;
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif
