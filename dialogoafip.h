//---------------------------------------------------------------------------

#ifndef dialogoafipH
#define dialogoafipH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormDialogoAFIP : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel2;
        TMemo *Memo;
        TButton *ButtonLeido;
        TTimer *Timer;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall TimerTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormDialogoAFIP(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDialogoAFIP *FormDialogoAFIP;
//---------------------------------------------------------------------------
#endif
