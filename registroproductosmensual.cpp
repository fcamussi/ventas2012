//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "registroproductosmensual.h"
#include "basedatos.h"
#include "auxiliar.h"
#include "impresion.h"
#include "facturacion.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormRegistroProductosMensual *FormRegistroProductosMensual;
//---------------------------------------------------------------------------
__fastcall TFormRegistroProductosMensual::TFormRegistroProductosMensual(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TFormRegistroProductosMensual::Mostrar()
{
        ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosMensual::MenuItemCerrarClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void TFormRegistroProductosMensual::CargarCantidad(int tipodocumento, AnsiString codigo, int mes, int ano, int cantidad)
{
        if (BuscarClave(BD->TableProductosMensual, "CodigoProducto;Mes;Ano",
                        Variant(codigo), Variant(mes), Variant(ano)))
        {
                BD->TableProductosMensual->Edit();
        }
        else
        {
                BD->TableProductosMensual->Append();
                BD->TableProductosMensual->FieldValues["CodigoProducto"] = codigo;
                BD->TableProductosMensual->FieldValues["Ano"] = ano;
                BD->TableProductosMensual->FieldValues["Mes"] = mes;
                BD->TableProductosMensual->FieldValues["CantidadRemito"] = 0;
                BD->TableProductosMensual->FieldValues["CantidadFactura"] = 0;
                BD->TableProductosMensual->FieldValues["CantidadTotal"] = 0;
        }
        if (tipodocumento == DOC_REMITO ||
            tipodocumento == DOC_CREDITOREMITO)
        {
                BD->TableProductosMensual->FieldByName("CantidadRemito")->AsFloat += cantidad;
        }
        else if (tipodocumento == DOC_FACTURA ||
                 tipodocumento == DOC_CREDITOFACTURA ||
                 tipodocumento == DOC_FACTURAELECT ||
                 tipodocumento == DOC_CREDITOELECT ||
                 tipodocumento == DOC_DEBITOELECT)
        {
                BD->TableProductosMensual->FieldByName("CantidadFactura")->AsFloat += cantidad;
        }
        BD->TableProductosMensual->FieldByName("CantidadTotal")->AsFloat += cantidad;
        BD->TableProductosMensual->Post();
}
//---------------------------------------------------------------------------

void TFormRegistroProductosMensual::DescargarCantidad(int tipodocumento, AnsiString codigo, int mes, int ano, int cantidad)
{
        if (BuscarClave(BD->TableProductosMensual, "CodigoProducto;Mes;Ano",
                        Variant(codigo), Variant(mes), Variant(ano)))
        {
                BD->TableProductosMensual->Edit();
        }
        else
        {
                BD->TableProductosMensual->Append();
                BD->TableProductosMensual->FieldValues["CodigoProducto"] = codigo;
                BD->TableProductosMensual->FieldValues["Ano"] = ano;
                BD->TableProductosMensual->FieldValues["Mes"] = mes;
                BD->TableProductosMensual->FieldValues["CantidadRemito"] = 0;
                BD->TableProductosMensual->FieldValues["CantidadFactura"] = 0;
                BD->TableProductosMensual->FieldValues["CantidadTotal"] = 0;
        }
        if (tipodocumento == DOC_REMITO ||
            tipodocumento == DOC_CREDITOREMITO)
        {
                BD->TableProductosMensual->FieldByName("CantidadRemito")->AsFloat -= cantidad;
        }
        else if (tipodocumento == DOC_FACTURA ||
                 tipodocumento == DOC_CREDITOFACTURA ||
                 tipodocumento == DOC_FACTURAELECT ||
                 tipodocumento == DOC_CREDITOELECT ||
                 tipodocumento == DOC_DEBITOELECT)
        {
                BD->TableProductosMensual->FieldByName("CantidadFactura")->AsFloat -= cantidad;
        }
        BD->TableProductosMensual->FieldByName("CantidadTotal")->AsFloat -= cantidad;
        BD->TableProductosMensual->Post();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosMensual::FormCreate(TObject *Sender)
{
        ListaMenuOrdenar lista;
        lista["ISAnoMes"] = "Año / Mes";
        lista["ISCantidadTotal"] = "Cantidad total";
        CrearMenuOrdenar(lista, "ISAnoMes", BD->TableProductosMensual,
                         MenuItemOrdenar, MenuItemOrdCol);
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosMensual::MenuItemOrdCol(TObject *Sender)
{
        SetearMenuOrdenar(BD->TableProductosMensual, static_cast< TMenuItem * >(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosMensual::FormShow(TObject *Sender)
{
        /* Seteo el index por defecto y muevo a la última fila */
        DefectoMenuOrdenar(BD->TableProductosMensual, MenuItemOrdenar);
        BD->TableProductosMensual->Last();
}
//---------------------------------------------------------------------------

