//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "registroproductosdiario.h"
#include "basedatos.h"
#include "auxiliar.h"
#include "impresion.h"
#include "facturacion.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormRegistroProductosDiario *FormRegistroProductosDiario;
//---------------------------------------------------------------------------
__fastcall TFormRegistroProductosDiario::TFormRegistroProductosDiario(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TFormRegistroProductosDiario::Mostrar()
{
        ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosDiario::MenuItemCerrarClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void TFormRegistroProductosDiario::CargarCantidad(int tipodocumento, AnsiString codigo, TDate fecha, int cantidad)
{
        if (BuscarClave(BD->TableProductosDiario, "CodigoProducto;Fecha",
                        Variant(codigo), Variant(fecha)))
        {
                BD->TableProductosDiario->Edit();
        }
        else
        {
                BD->TableProductosDiario->Append();
                BD->TableProductosDiario->FieldValues["CodigoProducto"] = codigo;
                BD->TableProductosDiario->FieldValues["Fecha"] = fecha;
                BD->TableProductosDiario->FieldValues["CantidadRemito"] = 0;
                BD->TableProductosDiario->FieldValues["CantidadFactura"] = 0;
                BD->TableProductosDiario->FieldValues["CantidadTotal"] = 0;
        }
        if (tipodocumento == DOC_REMITO ||
            tipodocumento == DOC_CREDITOREMITO)
        {
                BD->TableProductosDiario->FieldByName("CantidadRemito")->AsFloat += cantidad;
        }
        else if (tipodocumento == DOC_FACTURA ||
                 tipodocumento == DOC_CREDITOFACTURA ||
                 tipodocumento == DOC_FACTURAELECT ||
                 tipodocumento == DOC_CREDITOELECT ||
                 tipodocumento == DOC_DEBITOELECT)
        {
                BD->TableProductosDiario->FieldByName("CantidadFactura")->AsFloat += cantidad;
        }
        BD->TableProductosDiario->FieldByName("CantidadTotal")->AsFloat += cantidad;
        BD->TableProductosDiario->Post();
}
//---------------------------------------------------------------------------

void TFormRegistroProductosDiario::DescargarCantidad(int tipodocumento, AnsiString codigo, TDate fecha, int cantidad)
{
        if (BuscarClave(BD->TableProductosDiario, "CodigoProducto;Fecha",
                        Variant(codigo), Variant(fecha)))
        {
                BD->TableProductosDiario->Edit();
        }
        else
        {
                BD->TableProductosDiario->Append();
                BD->TableProductosDiario->FieldValues["CodigoProducto"] = codigo;
                BD->TableProductosDiario->FieldValues["Fecha"] = fecha;
                BD->TableProductosDiario->FieldValues["CantidadRemito"] = 0;
                BD->TableProductosDiario->FieldValues["CantidadFactura"] = 0;
                BD->TableProductosDiario->FieldValues["CantidadTotal"] = 0;
        }
        if (tipodocumento == DOC_REMITO ||
            tipodocumento == DOC_CREDITOREMITO)
        {
                BD->TableProductosDiario->FieldByName("CantidadRemito")->AsFloat -= cantidad;
        }
        else if (tipodocumento == DOC_FACTURA ||
                 tipodocumento == DOC_CREDITOFACTURA ||
                 tipodocumento == DOC_FACTURAELECT ||
                 tipodocumento == DOC_CREDITOELECT ||
                 tipodocumento == DOC_DEBITOELECT)
        {
                BD->TableProductosDiario->FieldByName("CantidadFactura")->AsFloat -= cantidad;
        }
        BD->TableProductosDiario->FieldByName("CantidadTotal")->AsFloat -= cantidad;
        BD->TableProductosDiario->Post();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosDiario::FormCreate(TObject *Sender)
{
        ListaMenuOrdenar lista;
        lista["ISFecha"] = "Fecha";
        lista["ISCantidadTotal"] = "Cantidad total";
        CrearMenuOrdenar(lista, "ISFecha", BD->TableProductosDiario,
                         MenuItemOrdenar, MenuItemOrdCol);
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosDiario::MenuItemOrdCol(TObject *Sender)
{
        SetearMenuOrdenar(BD->TableProductosDiario, static_cast< TMenuItem * >(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosDiario::FormShow(TObject *Sender)
{
        /* Seteo el index por defecto y muevo a la última fila */
        DefectoMenuOrdenar(BD->TableProductosDiario, MenuItemOrdenar);
        BD->TableProductosDiario->Last();
}
//---------------------------------------------------------------------------




