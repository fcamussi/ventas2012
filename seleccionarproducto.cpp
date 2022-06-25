//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "seleccionarproducto.h"
#include "basedatos.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSeleccionarProducto *FormSeleccionarProducto;
static AnsiString codigoproducto;

//---------------------------------------------------------------------------
__fastcall TFormSeleccionarProducto::TFormSeleccionarProducto(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormSeleccionarProducto::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        TableProductos->Filtered = false;
        TableProductos->Active = false;
}
//---------------------------------------------------------------------------

AnsiString TFormSeleccionarProducto::Mostrar(AnsiString defecto)
{
        TableProductos->Active = True;
        if (! defecto.IsEmpty())
        {
                TableProductos->FindKey(ARRAYOFCONST((defecto)));
        }
        codigoproducto = "";
        ShowModal();
        return codigoproducto;
}
//---------------------------------------------------------------------------

void __fastcall TFormSeleccionarProducto::BitBtnCerrarClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormSeleccionarProducto::FormShow(TObject *Sender)
{
        if (TableProductos->IsEmpty())
        {
                EditTexto->Enabled = false;
                BitBtnSeleccionar->Enabled = false;
        }
        else
        {
                EditTexto->Enabled = true;
                BitBtnSeleccionar->Enabled = true;
                EditTexto->Text = "";
                EditTexto->SetFocus();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormSeleccionarProducto::BitBtnSeleccionarClick(TObject *Sender)
{
        codigoproducto = TableProductos->FieldValues["CodigoProducto"];
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormSeleccionarProducto::DBGridDblClick(TObject *Sender)
{
        if (BitBtnSeleccionar->Enabled == true)
        {
                BitBtnSeleccionar->Click();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormSeleccionarProducto::EditTextoChange(TObject *Sender)
{
        if (EditTexto->Text.IsEmpty())
        {
                TableProductos->Filtered = false;
                BitBtnSeleccionar->Enabled = true;
        }
        else
        {
                TableProductos->Filtered = true;

                if (TableProductos->IsEmpty())
                {
                        BitBtnSeleccionar->Enabled = false;
                }
                else
                {
                        BitBtnSeleccionar->Enabled = true;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormSeleccionarProducto::FormCreate(TObject *Sender)
{
        TableProductos->DatabaseName = BD->TableProductos->DatabaseName;        
}
//---------------------------------------------------------------------------

void __fastcall TFormSeleccionarProducto::TableProductosFilterRecord(
      TDataSet *DataSet, bool &Accept)
{
        AnsiString codigoproducto, descripcion, familia, unidad;
        AnsiString texto;

        codigoproducto = DataSet->FieldByName("CodigoProducto")->AsString;
        descripcion = DataSet->FieldByName("Descripcion")->AsString;
        familia = DataSet->FieldByName("Familia")->AsString;
        unidad = DataSet->FieldByName("Unidad")->AsString;

        codigoproducto = codigoproducto.UpperCase();
        descripcion = descripcion.UpperCase();
        familia = familia.UpperCase();
        unidad = unidad.UpperCase();

        texto = EditTexto->Text.UpperCase();

        // Filtro
        if (codigoproducto.Pos(texto) > 0 ||
            descripcion.Pos(texto) > 0 ||
            familia.Pos(texto) > 0 ||
            unidad.Pos(texto) > 0)
        {
                Accept = true;
        }
        else
        {
                Accept = false;
        }
}
//---------------------------------------------------------------------------

