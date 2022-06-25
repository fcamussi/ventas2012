//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "saldos.h"
#include "basedatos.h"
#include "auxiliar.h"
#include "impresion.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSaldos *FormSaldos;
//---------------------------------------------------------------------------
__fastcall TFormSaldos::TFormSaldos(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TFormSaldos::Mostrar()
{
        ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormSaldos::DBGridDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumn *Column,
      TGridDrawState State)
{
        if (BD->TableClientes->IsEmpty()) return;
        
        TDBGrid *grid = static_cast<TDBGrid*>(Sender);
        if(BD->TableClientes->FieldValues["SaldoCC"] < -0.001)
        {
                grid->Canvas->Font->Color = clRed;
        }
        grid->DefaultDrawColumnCell(Rect, DataCol, Column, State);
}
//---------------------------------------------------------------------------

void __fastcall TFormSaldos::FormCreate(TObject *Sender)
{
        ListaMenuOrdenar lista;
        lista["ISNumeroCliente"] = "Número cliente";
        lista["ISNombreCliente"] = "Nombre cliente";
        lista["ISNombreNegocio"] = "Nombre negocio";
        lista["ISSaldoCC"] = "Saldo";
        CrearMenuOrdenar(lista, "ISNombreCliente", BD->TableClientes,
                         MenuItemOrdenar, MenuItemOrdCol);
}
//---------------------------------------------------------------------------

void __fastcall TFormSaldos::MenuItemOrdCol(TObject *Sender)
{
        SetearMenuOrdenar(BD->TableClientes, static_cast< TMenuItem * >(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TFormSaldos::FormShow(TObject *Sender)
{
        /* Seteo el index por defecto y muevo a la primera fila */
        DefectoMenuOrdenar(BD->TableClientes, MenuItemOrdenar);
        CalcularSaldoTotal();
        BD->TableClientes->First();
}
//---------------------------------------------------------------------------

void __fastcall TFormSaldos::MenuItemCerrarClick(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void __fastcall TFormSaldos::MenuItemImprimirClick(TObject *Sender)
{
        if (BD->TableClientes->IsEmpty()) return;

        Impresion imp;
        imp.ImprimirSaldos(false);
}
//---------------------------------------------------------------------------

void __fastcall TFormSaldos::ToolButtonImprimirDesdeClick(TObject *Sender)
{
        MenuItemImprimir->Click();        
}
//---------------------------------------------------------------------------

void TFormSaldos::CalcularSaldoTotal()
{
        double saldototal = 0;

        if (BD->TableClientes->IsEmpty())
        {
                StaticTextSaldoTotal->Caption = "";
                return;
        }
        BD->TableClientes->DisableControls();
        BD->TableClientes->First();

        while (! BD->TableClientes->Eof)
        {
                saldototal += BD->TableClientes->FieldByName("SaldoCC")->AsFloat;
                BD->TableClientes->Next();
        }
        StaticTextSaldoTotal->Caption = FormatFloat("0.00", saldototal);

        BD->TableClientes->EnableControls();
}
//---------------------------------------------------------------------------

void __fastcall TFormSaldos::MenuItemVisualizarClick(TObject *Sender)
{
        if (BD->TableClientes->IsEmpty()) return;

        Impresion imp;
        imp.ImprimirSaldos(true);
}
//---------------------------------------------------------------------------

