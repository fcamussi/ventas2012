//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "seleccionarcliente.h"
#include "basedatos.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSeleccionarCliente *FormSeleccionarCliente;
static int numerocliente;

//---------------------------------------------------------------------------
__fastcall TFormSeleccionarCliente::TFormSeleccionarCliente(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormSeleccionarCliente::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        TableClientes->Filtered = false;
        TableClientes->Active = false;
}
//---------------------------------------------------------------------------

int TFormSeleccionarCliente::Mostrar(int defecto)
{
        TableClientes->Active = true;
        if (defecto > 0)
        {
                TableClientes->FindKey(ARRAYOFCONST((defecto)));
        }
        numerocliente = 0;
        ShowModal();
        return numerocliente;
}
//---------------------------------------------------------------------------

void __fastcall TFormSeleccionarCliente::BitBtnCerrarClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormSeleccionarCliente::FormShow(TObject *Sender)
{
        if (TableClientes->IsEmpty())
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

void __fastcall TFormSeleccionarCliente::BitBtnSeleccionarClick(TObject *Sender)
{
        numerocliente = TableClientes->FieldValues["NumeroCliente"];
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormSeleccionarCliente::DBGridDblClick(TObject *Sender)
{
        if (BitBtnSeleccionar->Enabled == true)
        {
                BitBtnSeleccionar->Click();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormSeleccionarCliente::EditTextoChange(TObject *Sender)
{
        if (EditTexto->Text.IsEmpty())
        {
                TableClientes->Filtered = false;
                BitBtnSeleccionar->Enabled = true;
        }
        else
        {
                TableClientes->Filtered = true;

                if (TableClientes->IsEmpty())
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

void __fastcall TFormSeleccionarCliente::FormCreate(TObject *Sender)
{
        TableClientes->DatabaseName = BD->TableClientes->DatabaseName;
}
//---------------------------------------------------------------------------

void __fastcall TFormSeleccionarCliente::TableClientesFilterRecord(
      TDataSet *DataSet, bool &Accept)
{
        int _numerocliente;
        AnsiString numerocliente, nombrecliente, nombrenegocio, nombrefactura;
        AnsiString texto;

        _numerocliente = DataSet->FieldByName("NumeroCliente")->AsInteger;
        nombrecliente = DataSet->FieldByName("NombreCliente")->AsString;
        nombrenegocio = DataSet->FieldByName("NombreNegocio")->AsString;
        nombrefactura = DataSet->FieldByName("NombreFactura")->AsString;

        numerocliente = AnsiString(_numerocliente);
        nombrecliente = nombrecliente.UpperCase();
        nombrenegocio = nombrenegocio.UpperCase();
        nombrefactura = nombrefactura.UpperCase();

        texto = EditTexto->Text.UpperCase();

        // Filtro
        if (numerocliente.Pos(texto) > 0 ||
            nombrecliente.Pos(texto) > 0 ||
            nombrenegocio.Pos(texto) > 0 ||
            nombrefactura.Pos(texto) > 0)
        {
                Accept = true;
        }
        else
        {
                Accept = false;
        }
}
//---------------------------------------------------------------------------

