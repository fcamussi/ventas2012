//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "registroventasanual.h"
#include "basedatos.h"
#include "auxiliar.h"
#include "facturacion.h"
#include "impresion.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormRegistroVentasAnual *FormRegistroVentasAnual;
//---------------------------------------------------------------------------
__fastcall TFormRegistroVentasAnual::TFormRegistroVentasAnual(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TFormRegistroVentasAnual::Mostrar()
{
        ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroVentasAnual::MenuItemCerrarClick(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void TFormRegistroVentasAnual::CargarMonto(int tipodocumento, int ano, double monto)
{
        if (BuscarClave(BD->TableVentasAnual, "Ano", Variant(ano)))
        {
                BD->TableVentasAnual->Edit();
        }
        else
        {
                BD->TableVentasAnual->Append();
                BD->TableVentasAnual->FieldValues["Ano"] = ano;
                BD->TableVentasAnual->FieldValues["MontoRemitos"] = 0;
                BD->TableVentasAnual->FieldValues["MontoFacturas"] = 0;
                BD->TableVentasAnual->FieldValues["MontoTotal"] = 0;
        }
        if (tipodocumento == DOC_REMITO ||
            tipodocumento == DOC_CREDITOREMITO)
        {
                BD->TableVentasAnual->FieldByName("MontoRemitos")->AsFloat += monto;
        }
        else if (tipodocumento == DOC_FACTURA ||
                 tipodocumento == DOC_CREDITOFACTURA ||
                 tipodocumento == DOC_FACTURAELECT ||
                 tipodocumento == DOC_CREDITOELECT ||
                 tipodocumento == DOC_DEBITOELECT)
        {
                BD->TableVentasAnual->FieldByName("MontoFacturas")->AsFloat += monto;
        }
        BD->TableVentasAnual->FieldByName("MontoTotal")->AsFloat += monto;
        BD->TableVentasAnual->Post();
}
//---------------------------------------------------------------------------

void TFormRegistroVentasAnual::DescargarMonto(int tipodocumento, int ano, double monto)
{
        if (BuscarClave(BD->TableVentasAnual, "Ano", Variant(ano)))
        {
                BD->TableVentasAnual->Edit();
        }
        else
        {
                BD->TableVentasAnual->Append();
                BD->TableVentasAnual->FieldValues["Ano"] = ano;
                BD->TableVentasAnual->FieldValues["MontoRemitos"] = 0;
                BD->TableVentasAnual->FieldValues["MontoFacturas"] = 0;
                BD->TableVentasAnual->FieldValues["MontoTotal"] = 0;
        }
        if (tipodocumento == DOC_REMITO ||
            tipodocumento == DOC_CREDITOREMITO)
        {
                BD->TableVentasAnual->FieldByName("MontoRemitos")->AsFloat -= monto;
        }
        else if (tipodocumento == DOC_FACTURA ||
                 tipodocumento == DOC_CREDITOFACTURA ||
                 tipodocumento == DOC_FACTURAELECT ||
                 tipodocumento == DOC_CREDITOELECT ||
                 tipodocumento == DOC_DEBITOELECT)
        {
                BD->TableVentasAnual->FieldByName("MontoFacturas")->AsFloat -= monto;
        }
        BD->TableVentasAnual->FieldByName("MontoTotal")->AsFloat -= monto;
        BD->TableVentasAnual->Post();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroVentasAnual::FormCreate(TObject *Sender)
{
        ListaMenuOrdenar lista;
        lista["ISAno"] = "Año";
        lista["ISMontoRemitos"] = "Monto remitos";
        lista["ISMontoFacturas"] = "Monto facturas";
        lista["ISMontoTotal"] = "Monto total";
        CrearMenuOrdenar(lista, "ISAno", BD->TableVentasAnual,
                         MenuItemOrdenar, MenuItemOrdCol);
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroVentasAnual::MenuItemOrdCol(TObject *Sender)
{
        SetearMenuOrdenar(BD->TableVentasAnual, static_cast< TMenuItem * >(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroVentasAnual::FormShow(TObject *Sender)
{
        /* Seteo el index por defecto y muevo a la última fila */
        DefectoMenuOrdenar(BD->TableVentasAnual, MenuItemOrdenar);
        BD->TableVentasAnual->Last();
}
//---------------------------------------------------------------------------

