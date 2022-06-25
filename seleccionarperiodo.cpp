//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "seleccionarperiodo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSeleccionarPeriodo *FormSeleccionarPeriodo;
//---------------------------------------------------------------------------
__fastcall TFormSeleccionarPeriodo::TFormSeleccionarPeriodo(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

TModalResult TFormSeleccionarPeriodo::Mostrar()
{
        DateTimePickerDesde->DateTime = Date();
        DateTimePickerHasta->DateTime = Date();
        return ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormSeleccionarPeriodo::ButtonAceptarClick(
      TObject *Sender)
{
        if (DateTimePickerDesde->DateTime > DateTimePickerHasta->DateTime)
        {
                MessageBox(Handle, "El periodo seleccionado es incongruente.",
                           Application->Title.c_str(), MB_APPLMODAL |
                           MB_OK | MB_ICONWARNING);
        }
        else
        {
                ModalResult = mrOk;
        }
}
//---------------------------------------------------------------------------
void __fastcall TFormSeleccionarPeriodo::ButtonCancelarClick(
      TObject *Sender)
{
        ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void TFormSeleccionarPeriodo::ObtenerPeriodo(TDate &desde, TDate &hasta)
{
        desde = DateTimePickerDesde->DateTime;
        hasta = DateTimePickerHasta->DateTime;
}
//---------------------------------------------------------------------------

