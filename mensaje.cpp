//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mensaje.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMensaje *FormMensaje;
//---------------------------------------------------------------------------
__fastcall TFormMensaje::TFormMensaje(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

Mensaje::Mensaje(AnsiString texto)
{
        FormMensaje->Label->Caption = texto;
        FormMensaje->Caption = texto;
}
//---------------------------------------------------------------------------

void Mensaje::Mostrar()
{
        FormMensaje->Show();
        FormMensaje->Refresh();
}
//---------------------------------------------------------------------------

void Mensaje::Cerrar()
{
        FormMensaje->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormMensaje::FormCreate(TObject *Sender)
{
        Graphics::TBitmap *bmp = new Graphics::TBitmap;
        ImageList->GetBitmap(0, bmp);
//        ImageList->GetBitmap(ImageList->Tag, bmp);
        Image->Canvas->Draw(0, 0, bmp);
        delete bmp;
//        ImageList->Tag = (ImageList->Tag + 1) % 6;
}
//---------------------------------------------------------------------------

