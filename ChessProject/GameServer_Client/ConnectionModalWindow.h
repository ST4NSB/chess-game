//---------------------------------------------------------------------------

#ifndef ConnectionModalWindowH
#define ConnectionModalWindowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TConnectionForm : public TForm
{
__published:	// IDE-managed Components
        TButton *ServerBtn;
        TLabel *PortLabel;
        TEdit *ServerPortEdit;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *ClientPortEdit;
        TLabel *Label5;
        TEdit *ClientAddressEdit;
        TButton *ClientBtn;
        void __fastcall ServerBtnClick(TObject *Sender);
        void __fastcall ClientBtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TConnectionForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TConnectionForm *ConnectionForm;
//---------------------------------------------------------------------------
#endif
