//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "registrokilogramosmensual.h"
#include "basedatos.h"
#include "auxiliar.h"
#include "facturacion.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormRegistroKilogramosMensual *FormRegistroKilogramosMensual;
//---------------------------------------------------------------------------
__fastcall TFormRegistroKilogramosMensual::TFormRegistroKilogramosMensual(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TFormRegistroKilogramosMensual::Mostrar()
{
        ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroKilogramosMensual::MenuItemCerrarClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void TFormRegistroKilogramosMensual::CargarCantidad(int tipodocumento, int mes, int ano, double cantidad)
{
        if (BuscarClave(BD->TableKilogramosMensual, "Mes;Ano", Variant(mes), Variant(ano)))
        {
                BD->TableKilogramosMensual->Edit();
        }
        else
        {
                BD->TableKilogramosMensual->Append();
                BD->TableKilogramosMensual->FieldValues["Ano"] = ano;
                BD->TableKilogramosMensual->FieldValues["Mes"] = mes;
                BD->TableKilogramosMensual->FieldValues["CantidadRemito"] = 0;
                BD->TableKilogramosMensual->FieldValues["CantidadFactura"] = 0;
                BD->TableKilogramosMensual->FieldValues["CantidadTotal"] = 0;
        }
        if (tipodocumento == DOC_REMITO ||
            tipodocumento == DOC_CREDITOREMITO)
        {
                BD->TableKilogramosMensual->FieldByName("CantidadRemito")->AsFloat += cantidad;
        }
        else if (tipodocumento == DOC_FACTURA ||
                 tipodocumento == DOC_CREDITOFACTURA ||
                 tipodocumento == DOC_FACTURAELECT ||
                 tipodocumento == DOC_CREDITOELECT ||
                 tipodocumento == DOC_DEBITOELECT)
        {
                BD->TableKilogramosMensual->FieldByName("CantidadFactura")->AsFloat += cantidad;
        }
        BD->TableKilogramosMensual->FieldByName("CantidadTotal")->AsFloat += cantidad;
        BD->TableKilogramosMensual->Post();
}
//---------------------------------------------------------------------------

void TFormRegistroKilogramosMensual::DescargarCantidad(int tipodocumento, int mes, int ano, double cantidad)
{
        if (BuscarClave(BD->TableKilogramosMensual, "Mes;Ano", Variant(mes), Variant(ano)))
        {
                BD->TableKilogramosMensual->Edit();
        }
        else
        {
                BD->TableKilogramosMensual->Append();
                BD->TableKilogramosMensual->FieldValues["Ano"] = ano;
                BD->TableKilogramosMensual->FieldValues["Mes"] = mes;
                BD->TableKilogramosMensual->FieldValues["CantidadRemito"] = 0;
                BD->TableKilogramosMensual->FieldValues["CantidadFactura"] = 0;
                BD->TableKilogramosMensual->FieldValues["CantidadTotal"] = 0;
        }
        if (tipodocumento == DOC_REMITO ||
            tipodocumento == DOC_CREDITOREMITO)
        {
                BD->TableKilogramosMensual->FieldByName("CantidadRemito")->AsFloat -= cantidad;
        }
        else if (tipodocumento == DOC_FACTURA ||
                 tipodocumento == DOC_CREDITOFACTURA ||
                 tipodocumento == DOC_FACTURAELECT ||
                 tipodocumento == DOC_CREDITOELECT ||
                 tipodocumento == DOC_DEBITOELECT)
        {
                BD->TableKilogramosMensual->FieldByName("CantidadFactura")->AsFloat -= cantidad;
        }
        BD->TableKilogramosMensual->FieldByName("CantidadTotal")->AsFloat -= cantidad;
        BD->TableKilogramosMensual->Post();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroKilogramosMensual::FormCreate(TObject *Sender)
{
        ListaMenuOrdenar lista;
        lista["ISAnoMes"] = "Año / Mes";
        lista["ISCantidadTotal"] = "Cantidad total";
        CrearMenuOrdenar(lista, "ISAnoMes", BD->TableKilogramosMensual,
                         MenuItemOrdenar, MenuItemOrdCol);
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroKilogramosMensual::MenuItemOrdCol(TObject *Sender)
{
        SetearMenuOrdenar(BD->TableKilogramosMensual, static_cast< TMenuItem * >(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroKilogramosMensual::FormShow(TObject *Sender)
{
        /* Seteo el index por defecto y muevo a la última fila */
        DefectoMenuOrdenar(BD->TableKilogramosMensual, MenuItemOrdenar);
        BD->TableKilogramosMensual->Last();
}
//---------------------------------------------------------------------------

