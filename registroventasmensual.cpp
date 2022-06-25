//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "registroventasmensual.h"
#include "basedatos.h"
#include "auxiliar.h"
#include "facturacion.h"
#include "impresion.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormRegistroVentasMensual *FormRegistroVentasMensual;
//---------------------------------------------------------------------------
__fastcall TFormRegistroVentasMensual::TFormRegistroVentasMensual(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TFormRegistroVentasMensual::Mostrar()
{
        ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroVentasMensual::MenuItemCerrarClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void TFormRegistroVentasMensual::CargarMonto(int tipodocumento, int mes, int ano, double monto)
{
        if (BuscarClave(BD->TableVentasMensual, "Mes;Ano", Variant(mes), Variant(ano)))
        {
                BD->TableVentasMensual->Edit();
        }
        else
        {
                BD->TableVentasMensual->Append();
                BD->TableVentasMensual->FieldValues["Mes"] = mes;
                BD->TableVentasMensual->FieldValues["Ano"] = ano;
                BD->TableVentasMensual->FieldValues["MontoRemitos"] = 0;
                BD->TableVentasMensual->FieldValues["MontoFacturas"] = 0;
                BD->TableVentasMensual->FieldValues["MontoTotal"] = 0;
        }
        if (tipodocumento == DOC_REMITO ||
            tipodocumento == DOC_CREDITOREMITO)
        {
                BD->TableVentasMensual->FieldByName("MontoRemitos")->AsFloat += monto;
        }
        else if (tipodocumento == DOC_FACTURA ||
                 tipodocumento == DOC_CREDITOFACTURA ||
                 tipodocumento == DOC_FACTURAELECT ||
                 tipodocumento == DOC_CREDITOELECT ||
                 tipodocumento == DOC_DEBITOELECT)
        {
                BD->TableVentasMensual->FieldByName("MontoFacturas")->AsFloat += monto;
        }
        BD->TableVentasMensual->FieldByName("MontoTotal")->AsFloat += monto;
        BD->TableVentasMensual->Post();
}
//---------------------------------------------------------------------------

void TFormRegistroVentasMensual::DescargarMonto(int tipodocumento, int mes, int ano, double monto)
{
        if (BuscarClave(BD->TableVentasMensual, "Mes;Ano", Variant(mes), Variant(ano)))
        {
                BD->TableVentasMensual->Edit();
        }
        else
        {
                BD->TableVentasMensual->Append();
                BD->TableVentasMensual->FieldValues["Mes"] = mes;
                BD->TableVentasMensual->FieldValues["Ano"] = ano;
                BD->TableVentasMensual->FieldValues["MontoRemitos"] = 0;
                BD->TableVentasMensual->FieldValues["MontoFacturas"] = 0;
                BD->TableVentasMensual->FieldValues["MontoTotal"] = 0;
        }
        if (tipodocumento == DOC_REMITO ||
            tipodocumento == DOC_CREDITOREMITO)
        {
                BD->TableVentasMensual->FieldByName("MontoRemitos")->AsFloat -= monto;
        }
        else if (tipodocumento == DOC_FACTURA ||
                 tipodocumento == DOC_CREDITOFACTURA ||
                 tipodocumento == DOC_FACTURAELECT ||
                 tipodocumento == DOC_CREDITOELECT ||
                 tipodocumento == DOC_DEBITOELECT)
        {
                BD->TableVentasMensual->FieldByName("MontoFacturas")->AsFloat -= monto;
        }
        BD->TableVentasMensual->FieldByName("MontoTotal")->AsFloat -= monto;
        BD->TableVentasMensual->Post();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroVentasMensual::FormCreate(TObject *Sender)
{
        ListaMenuOrdenar lista;
        lista["ISAnoMes"] = "Año / Mes";
        lista["ISMontoRemitos"] = "Monto remitos";
        lista["ISMontoFacturas"] = "Monto facturas";
        lista["ISMontoTotal"] = "Monto total";
        CrearMenuOrdenar(lista, "ISAnoMes", BD->TableVentasMensual,
                         MenuItemOrdenar, MenuItemOrdCol);
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroVentasMensual::MenuItemOrdCol(TObject *Sender)
{
        SetearMenuOrdenar(BD->TableVentasMensual, static_cast< TMenuItem * >(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroVentasMensual::FormShow(TObject *Sender)
{
        /* Seteo el index por defecto y muevo a la última fila */
        DefectoMenuOrdenar(BD->TableVentasMensual, MenuItemOrdenar);
        BD->DataSourceVentasMensual->Enabled = false;
        BD->DataSourceVentasMensual->Enabled = true;
        BD->TableVentasMensual->Last();
}
//---------------------------------------------------------------------------





