//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Identificacion.h"
#include "configuracion.h"
#include "principal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormIdentificacion *FormIdentificacion;
//---------------------------------------------------------------------------
__fastcall TFormIdentificacion::TFormIdentificacion(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormIdentificacion::ButtonEntrarClick(TObject *Sender)
{
        if (EditClave->Text == FormConfiguracion->ClaveIdentificacion())
        {
                ModalResult = mrOk;
        }
}
//---------------------------------------------------------------------------

int TFormIdentificacion::Mostrar()
{
        return ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormIdentificacion::FormCreate(TObject *Sender)
{
        Caption = AnsiString("Identificación para ") + Application->Title.c_str();        
}
//---------------------------------------------------------------------------

