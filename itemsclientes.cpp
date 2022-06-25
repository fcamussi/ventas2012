//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "itemsclientes.h"
#include "basedatos.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormItemsClientes *FormItemsClientes;
//---------------------------------------------------------------------------
__fastcall TFormItemsClientes::TFormItemsClientes(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormItemsClientes::ToolButtonAgregarClick(TObject *Sender)
{
        if (PageControl->ActivePageIndex == 0)
        {
                DBGridLocalidades->SetFocus();
                BD->TableLocalidades->Append();
        }
        else if (PageControl->ActivePageIndex == 1)
        {
                DBGridTiposNegocios->SetFocus();
                BD->TableTiposNegocios->Append();
        }
}
//---------------------------------------------------------------------------


void __fastcall TFormItemsClientes::ToolButtonEliminarClick(
      TObject *Sender)
{
        if (PageControl->ActivePageIndex == 0)
                BD->TableLocalidades->Delete();
        if (PageControl->ActivePageIndex == 1)
                BD->TableTiposNegocios->Delete();
}
//---------------------------------------------------------------------------

void TFormItemsClientes::Mostrar(int numero)
{
        PageControl->ActivePageIndex = numero;
        ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormItemsClientes::DBGridKeyDown(
      TObject *Sender, WORD &Key, TShiftState Shift)
{
        // Anulo los atajos por defecto para agregar y eliminar filas
        if ((Shift.Contains(ssCtrl) && Key == VK_DELETE) || Key == VK_INSERT)
        {
                Abort();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormItemsClientes::MenuItemAgregarClick(TObject *Sender)
{
        ToolButtonAgregar->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormItemsClientes::MenuItemEliminarClick(TObject *Sender)
{
        ToolButtonEliminar->Click();
}
//---------------------------------------------------------------------------



