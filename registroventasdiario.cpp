//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "registroventasdiario.h"
#include "facturacion.h"
#include "basedatos.h"
#include "auxiliar.h"
#include "impresion.h"
#include "seleccionarperiodo.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormRegistroVentasDiario *FormRegistroVentasDiario;
//---------------------------------------------------------------------------
__fastcall TFormRegistroVentasDiario::TFormRegistroVentasDiario(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TFormRegistroVentasDiario::Mostrar()
{
        ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroVentasDiario::MenuItemCerrarClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void TFormRegistroVentasDiario::CargarMonto(int tipodocumento, TDate fecha, double monto)
{
        if (BuscarClave(BD->TableVentasDiario, "Fecha", Variant(fecha)))
        {
                BD->TableVentasDiario->Edit();
        }
        else
        {
                BD->TableVentasDiario->Append();
                BD->TableVentasDiario->FieldValues["Fecha"] = fecha;
                BD->TableVentasDiario->FieldValues["MontoRemitos"] = 0;
                BD->TableVentasDiario->FieldValues["MontoFacturas"] = 0;
                BD->TableVentasDiario->FieldValues["MontoTotal"] = 0;
        }
        if (tipodocumento == DOC_REMITO ||
            tipodocumento == DOC_CREDITOREMITO)
        {
                BD->TableVentasDiario->FieldByName("MontoRemitos")->AsFloat += monto;
        }
        else if (tipodocumento == DOC_FACTURA ||
                 tipodocumento == DOC_CREDITOFACTURA ||
                 tipodocumento == DOC_FACTURAELECT ||
                 tipodocumento == DOC_CREDITOELECT ||
                 tipodocumento == DOC_DEBITOELECT)
        {
                BD->TableVentasDiario->FieldByName("MontoFacturas")->AsFloat += monto;
        }
        BD->TableVentasDiario->FieldByName("MontoTotal")->AsFloat += monto;
        BD->TableVentasDiario->Post();
}
//---------------------------------------------------------------------------

void TFormRegistroVentasDiario::DescargarMonto(int tipodocumento, TDate fecha, double monto)
{
        if (BuscarClave(BD->TableVentasDiario, "Fecha", Variant(fecha)))
        {
                BD->TableVentasDiario->Edit();
        }
        else
        {
                BD->TableVentasDiario->Append();
                BD->TableVentasDiario->FieldValues["Fecha"] = fecha;
                BD->TableVentasDiario->FieldValues["MontoRemitos"] = 0;
                BD->TableVentasDiario->FieldValues["MontoFacturas"] = 0;
                BD->TableVentasDiario->FieldValues["MontoTotal"] = 0;
        }
        if (tipodocumento == DOC_REMITO ||
            tipodocumento == DOC_CREDITOREMITO)
        {
                BD->TableVentasDiario->FieldByName("MontoRemitos")->AsFloat -= monto;
        }
        else if (tipodocumento == DOC_FACTURA ||
                 tipodocumento == DOC_CREDITOFACTURA ||
                 tipodocumento == DOC_FACTURAELECT ||
                 tipodocumento == DOC_CREDITOELECT ||
                 tipodocumento == DOC_DEBITOELECT)
        {
                BD->TableVentasDiario->FieldByName("MontoFacturas")->AsFloat -= monto;
        }
        BD->TableVentasDiario->FieldByName("MontoTotal")->AsFloat -= monto;
        BD->TableVentasDiario->Post();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroVentasDiario::FormCreate(TObject *Sender)
{
        ListaMenuOrdenar lista;
        lista["ISFecha"] = "Fecha";
        lista["ISMontoRemitos"] = "Monto remitos";
        lista["ISMontoFacturas"] = "Monto facturas";
        lista["ISMontoTotal"] = "Monto total";
        CrearMenuOrdenar(lista, "ISFecha", BD->TableVentasDiario,
                         MenuItemOrdenar, MenuItemOrdCol);
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroVentasDiario::MenuItemOrdCol(TObject *Sender)
{
        SetearMenuOrdenar(BD->TableVentasDiario, static_cast< TMenuItem * >(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroVentasDiario::FormShow(TObject *Sender)
{
        /* Seteo el index por defecto y muevo a la última fila */
        DefectoMenuOrdenar(BD->TableVentasDiario, MenuItemOrdenar);
        BD->TableVentasDiario->Last();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroVentasDiario::ToolButtonImprimirPeriodoClick(
      TObject *Sender)
{
        MenuItemImprimirPeriodo->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroVentasDiario::MenuItemImprimirPeriodoClick(
      TObject *Sender)
{
        Impresion imp;
        TDate desde, hasta;

        if (BD->TableVentasDiario->IsEmpty()) return;

        if (FormSeleccionarPeriodo->Mostrar() == mrOk)
        {
                FormSeleccionarPeriodo->ObtenerPeriodo(desde, hasta);
                imp.ImprimirRegistroVentasDiario(desde, hasta, false);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroVentasDiario::MenuItemVisualizarPeriodoClick(
      TObject *Sender)
{
        Impresion imp;
        TDate desde, hasta;

        if (BD->TableVentasDiario->IsEmpty()) return;

        if (FormSeleccionarPeriodo->Mostrar() == mrOk)
        {
                FormSeleccionarPeriodo->ObtenerPeriodo(desde, hasta);
                imp.ImprimirRegistroVentasDiario(desde, hasta, true);
        }
}
//---------------------------------------------------------------------------

