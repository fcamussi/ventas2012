//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "itemsproductos.h"
#include "basedatos.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormItemsProductos *FormItemsProductos;
//---------------------------------------------------------------------------
__fastcall TFormItemsProductos::TFormItemsProductos(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormItemsProductos::ToolButtonAgregarClick(TObject *Sender)
{
        if (PageControl->ActivePageIndex == 0)
        {
                DBGridFamilias->SetFocus();
                BD->TableFamilias->Append();
        }
        else if (PageControl->ActivePageIndex == 1)
        {
                DBGridUnidades->SetFocus();
                BD->TableUnidades->Append();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormItemsProductos::ToolButtonEliminarClick(
      TObject *Sender)
{
        if (PageControl->ActivePageIndex == 0)
                BD->TableFamilias->Delete();
        if (PageControl->ActivePageIndex == 1)
                BD->TableUnidades->Delete();
}
//---------------------------------------------------------------------------

void TFormItemsProductos::Mostrar(int numero)
{
        PageControl->ActivePageIndex = numero;
        ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormItemsProductos::DBGridKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
        // Anulo los atajos por defecto para agregar y eliminar filas
        if ((Shift.Contains(ssCtrl) && Key == VK_DELETE) || Key == VK_INSERT)
        {
                Abort();
        }
}

//---------------------------------------------------------------------------

void __fastcall TFormItemsProductos::MenuItemAgregarClick(TObject *Sender)
{
        ToolButtonAgregar->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormItemsProductos::MenuItemEliminarClick(TObject *Sender)
{
        ToolButtonEliminar->Click();
}
//---------------------------------------------------------------------------

