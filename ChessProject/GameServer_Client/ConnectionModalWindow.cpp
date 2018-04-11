//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ConnectionModalWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConnectionForm *ConnectionForm;
//---------------------------------------------------------------------------
__fastcall TConnectionForm::TConnectionForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TConnectionForm::ServerBtnClick(TObject *Sender)
{
        ConnectionForm->ModalResult = mrOk;
        ConnectionForm->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TConnectionForm::ClientBtnClick(TObject *Sender)
{
        ConnectionForm->ModalResult = mrYes;
        ConnectionForm->Hide();        
}
//---------------------------------------------------------------------------




