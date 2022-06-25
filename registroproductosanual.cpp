//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "registroproductosanual.h"
#include "basedatos.h"
#include "auxiliar.h"
#include "impresion.h"
#include "facturacion.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormRegistroProductosAnual *FormRegistroProductosAnual;
//---------------------------------------------------------------------------
__fastcall TFormRegistroProductosAnual::TFormRegistroProductosAnual(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TFormRegistroProductosAnual::Mostrar()
{
        ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosAnual::MenuItemCerrarClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void TFormRegistroProductosAnual::CargarCantidad(int tipodocumento, AnsiString codigo, int ano, int cantidad)
{
        if (BuscarClave(BD->TableProductosAnual, "CodigoProducto;Ano",
                        Variant(codigo), Variant(ano)))
        {
                BD->TableProductosAnual->Edit();
        }
        else
        {
                BD->TableProductosAnual->Append();
                BD->TableProductosAnual->FieldValues["CodigoProducto"] = codigo;
                BD->TableProductosAnual->FieldValues["Ano"] = ano;
                BD->TableProductosAnual->FieldValues["CantidadRemito"] = 0;
                BD->TableProductosAnual->FieldValues["CantidadFactura"] = 0;
                BD->TableProductosAnual->FieldValues["CantidadTotal"] = 0;
        }
        if (tipodocumento == DOC_REMITO ||
            tipodocumento == DOC_CREDITOREMITO)
        {
                BD->TableProductosAnual->FieldByName("CantidadRemito")->AsFloat += cantidad;
        }
        else if (tipodocumento == DOC_FACTURA ||
                 tipodocumento == DOC_CREDITOFACTURA ||
                 tipodocumento == DOC_FACTURAELECT ||
                 tipodocumento == DOC_CREDITOELECT ||
                 tipodocumento == DOC_DEBITOELECT)
        {
                BD->TableProductosAnual->FieldByName("CantidadFactura")->AsFloat += cantidad;
        }
        BD->TableProductosAnual->FieldByName("CantidadTotal")->AsFloat += cantidad;
        BD->TableProductosAnual->Post();
}
//---------------------------------------------------------------------------

void TFormRegistroProductosAnual::DescargarCantidad(int tipodocumento, AnsiString codigo, int ano, int cantidad)
{
        if (BuscarClave(BD->TableProductosAnual, "CodigoProducto;Ano",
                        Variant(codigo), Variant(ano)))
        {
                BD->TableProductosAnual->Edit();
        }
        else
        {
                BD->TableProductosAnual->Append();
                BD->TableProductosAnual->FieldValues["CodigoProducto"] = codigo;
                BD->TableProductosAnual->FieldValues["Ano"] = ano;
                BD->TableProductosAnual->FieldValues["CantidadRemito"] = 0;
                BD->TableProductosAnual->FieldValues["CantidadFactura"] = 0;
                BD->TableProductosAnual->FieldValues["CantidadTotal"] = 0;
        }
        if (tipodocumento == DOC_REMITO ||
            tipodocumento == DOC_CREDITOREMITO)
        {
                BD->TableProductosAnual->FieldByName("CantidadRemito")->AsFloat -= cantidad;
        }
        else if (tipodocumento == DOC_FACTURA ||
                 tipodocumento == DOC_CREDITOFACTURA ||
                 tipodocumento == DOC_FACTURAELECT ||
                 tipodocumento == DOC_CREDITOELECT ||
                 tipodocumento == DOC_DEBITOELECT)
        {
                BD->TableProductosAnual->FieldByName("CantidadFactura")->AsFloat -= cantidad;
        }
        BD->TableProductosAnual->FieldByName("CantidadTotal")->AsFloat -= cantidad;
        BD->TableProductosAnual->Post();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosAnual::FormCreate(TObject *Sender)
{
        ListaMenuOrdenar lista;
        lista["ISAno"] = "Año";
        lista["ISCantidadTotal"] = "Cantidad total";
        CrearMenuOrdenar(lista, "ISAno", BD->TableProductosAnual,
                         MenuItemOrdenar, MenuItemOrdCol);
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosAnual::MenuItemOrdCol(TObject *Sender)
{
        SetearMenuOrdenar(BD->TableProductosAnual, static_cast< TMenuItem * >(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosAnual::FormShow(TObject *Sender)
{
        /* Seteo el index por defecto y muevo a la última fila */
        DefectoMenuOrdenar(BD->TableProductosAnual, MenuItemOrdenar);
        BD->TableProductosAnual->Last();
}
//---------------------------------------------------------------------------




