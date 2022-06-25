//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "dialogoafip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormDialogoAFIP *FormDialogoAFIP;
//---------------------------------------------------------------------------
__fastcall TFormDialogoAFIP::TFormDialogoAFIP(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormDialogoAFIP::FormShow(TObject *Sender)
{
        ButtonLeido->Enabled = false;
        ButtonLeido->Caption = "Le�do (5)";
        Timer->Tag = 5;
        Timer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormDialogoAFIP::TimerTimer(TObject *Sender)
{
        if (Timer->Tag > 0)
        {
                ButtonLeido->Caption = AnsiString("Le�do (") + Timer->Tag + ")";
                Timer->Tag--;
        }
        else
        {
                ButtonLeido->Caption = "Le�do";
                ButtonLeido->Enabled = true;
                Timer->Enabled = false;
        }
}
//---------------------------------------------------------------------------
