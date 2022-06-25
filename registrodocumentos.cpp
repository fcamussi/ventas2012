//---------------------------------------------------------------------------

#include <vcl.h>
#include <FileCtrl.hpp>
#pragma hdrstop

#include "registrodocumentos.h"
#include "seleccionarcliente.h"
#include "facturacion.h"
#include "basedatos.h"
#include "cuentacorriente.h"
#include "auxiliar.h"
#include "registroventasdiario.h"
#include "registroventasmensual.h"
#include "registroventasanual.h"
#include "configuracion.h"
#include "impresion.h"
#include "registroproductosdiario.h"
#include "registroproductosmensual.h"
#include "registroproductosanual.h"
#include "seleccionarperiodo.h"
#include "registroproductosstock.h"
#include "registrokilogramosmensual.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormRegistroDocumentos *FormRegistroDocumentos;
//---------------------------------------------------------------------------
__fastcall TFormRegistroDocumentos::TFormRegistroDocumentos(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TFormRegistroDocumentos::Mostrar()
{
        ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::MenuItemCerrarClick(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::MenuItemEditarClick(TObject *Sender)
{
        int numerocliente;
        int tipodocumento, numerodocumento;
        int valor;

        if (BD->TableDocumentos->IsEmpty()) return;

        numerocliente = BD->TableDocumentos->FieldValues["NumeroCliente"];
        tipodocumento = BD->TableDocumentos->FieldValues["TipoDocumento"];
        numerodocumento = BD->TableDocumentos->FieldValues["NumeroDocumento"];

        if (! BuscarClave(BD->TableClientes, "NumeroCliente", Variant(numerocliente)))
        {
                AnsiString mensaje = "El cliente número " +
                                     IntToStr(numerocliente) +
                                     " ya no existe. ¿Desea asociar el "
                                     "documento a otro cliente?";
                valor = MessageBox(Handle, mensaje.c_str(),
                                   Application->Title.c_str(),
                                   MB_APPLMODAL | MB_YESNO | MB_ICONERROR);
                if (valor == IDYES)
                {
                        numerocliente = FormSeleccionarCliente->Mostrar(0);
                }
                else
                {
                        numerocliente = 0;
                }
        }
        if (numerocliente > 0)
        {
                FormFacturacion->EditarDocumento(numerocliente, tipodocumento,
                                                 numerodocumento);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::MenuItemMostrarClick(
      TObject *Sender)
{
        if (! BD->TableDocumentos->IsEmpty())
        {
                int tipodocumento = BD->TableDocumentos->FieldValues["TipoDocumento"];
                int numerodocumento = BD->TableDocumentos->FieldValues["NumeroDocumento"];
                MostrarDocumento(tipodocumento, numerodocumento);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::MenuItemImprimirClick(
      TObject *Sender)
{
        if (BD->TableDocumentos->IsEmpty()) return;
        int tipodocumento = BD->TableDocumentos->FieldValues["TipoDocumento"];

        Impresion imp;
        imp.ImprimirDocumento(tipodocumento, false);
        BD->TableDocumentos->Edit();
        BD->TableDocumentos->FieldValues["Estado"] = EST_IMPRESO;
        BD->TableDocumentos->Post();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::MenuItemAnularClick(
      TObject *Sender)
{
        if (BD->TableDocumentos->IsEmpty()) return;
        if (BD->TableDocumentos->FieldValues["Estado"] == EST_ANULADO)
        {
                AnsiString mensaje = "El documento ya se encuentra anulado.";
                MessageBox(Handle, mensaje.c_str(), Application->Title.c_str(),
                           MB_APPLMODAL | MB_ICONWARNING);
                return;
        }
        int tipodocumento = BD->TableDocumentos->FieldValues["TipoDocumento"];
        int numerodocumento = BD->TableDocumentos->FieldValues["NumeroDocumento"];

        AnularDocumento(tipodocumento, numerodocumento);
}
//---------------------------------------------------------------------------

void TFormRegistroDocumentos::AnularDocumento(int tipodocumento, int numerodocumento)
{
        if (tipodocumento == DOC_FACTURAELECT ||
            tipodocumento == DOC_CREDITOELECT ||
            tipodocumento == DOC_DEBITOELECT ||
            tipodocumento == DOC_PEDIDO)
        {
                Abort();
        }

        BuscarClave(BD->TableDocumentos, "TipoDocumento;NumeroDocumento",
                    Variant(tipodocumento), Variant(numerodocumento));
        int numerocliente = BD->TableDocumentos->FieldValues["NumeroCliente"];
        int valor;
        AnsiString mensaje = "¿Está seguro que desea anular el documento " +
                             FormFacturacion->Documentos(tipodocumento) +
                             " número " + numerodocumento + "? Se eliminará "
                             "de la cuenta corriente y se descontará de los "
                             "registros.";
        valor = MessageBox(Handle, mensaje.c_str(), Application->Title.c_str(),
                                   MB_APPLMODAL | MB_YESNO | MB_ICONWARNING);
        if (valor == IDNO) Abort();

        if (BuscarClave(BD->TableClientes, "NumeroCliente", Variant(numerocliente)))
        {
                if (BuscarClave(BD->TableCuentasCorrientes, "TipoDocumento;NumeroDocumento",
                                Variant(tipodocumento), Variant(numerodocumento)))
                {
                        BD->TableCuentasCorrientes->Delete();
                        FormCuentaCorriente->ActualizarSaldos();
                }
        }

        BD->TableDocumentos->Edit();
        BD->TableDocumentos->FieldValues["Estado"] = EST_ANULADO;
        BD->TableDocumentos->Post();

        TDate fecha = BD->TableDocumentos->FieldValues["Fecha"];
        double monto = BD->TableDocumentos->FieldValues["Total"];
        int mes = fecha.FormatString("m").ToInt();
        int ano = fecha.FormatString("yyyy").ToInt();

        switch(tipodocumento)
        {
          case DOC_REMITO:
          case DOC_FACTURA:
                FormRegistroVentasDiario->DescargarMonto(tipodocumento, fecha, monto);
                FormRegistroVentasMensual->DescargarMonto(tipodocumento, mes, ano, monto);
                FormRegistroVentasAnual->DescargarMonto(tipodocumento, ano, monto);
          break;
          case DOC_CREDITOREMITO:
          case DOC_CREDITOFACTURA:
                FormRegistroVentasDiario->CargarMonto(tipodocumento, fecha, monto);
                FormRegistroVentasMensual->CargarMonto(tipodocumento, mes, ano, monto);
                FormRegistroVentasAnual->CargarMonto(tipodocumento, ano, monto);
          break;
        }

        BD->TableDocumentosDetalles->First();
        for (int c = 0; c < BD->TableDocumentosDetalles->RecordCount; c++)
        {
                AnsiString codigo = BD->TableDocumentosDetalles->FieldValues["CodigoProducto"];
                int cantidad = BD->TableDocumentosDetalles->FieldValues["Cantidad"];
                bool sincargo = BD->TableDocumentosDetalles->FieldValues["SinCargo"];
                BuscarClave(BD->TableProductos, "CodigoProducto", codigo);
                int gramos = BD->TableProductos->FieldByName("Gramos")->AsInteger;
                BD->TableDocumentosDetalles->Next();
                switch(tipodocumento)
                {
                  case DOC_REMITO:
                  case DOC_FACTURA:
                        FormRegistroProductosStock->CargarStock(codigo, cantidad);
                        if (sincargo) continue;
                        FormRegistroProductosDiario->DescargarCantidad(tipodocumento, codigo, fecha, cantidad);
                        FormRegistroProductosMensual->DescargarCantidad(tipodocumento, codigo, mes, ano, cantidad);
                        FormRegistroProductosAnual->DescargarCantidad(tipodocumento, codigo, ano, cantidad);
                        FormRegistroKilogramosMensual->DescargarCantidad(tipodocumento, mes, ano, cantidad * (double)gramos / 1000);
                  break;
                  case DOC_CREDITOREMITO:
                  case DOC_CREDITOFACTURA:
                        FormRegistroProductosStock->DescargarStock(codigo, cantidad);
                        if (sincargo) continue;
                        FormRegistroProductosDiario->CargarCantidad(tipodocumento, codigo, fecha, cantidad);
                        FormRegistroProductosMensual->CargarCantidad(tipodocumento, codigo, mes, ano, cantidad);
                        FormRegistroProductosAnual->CargarCantidad(tipodocumento, codigo, ano, cantidad);
                        FormRegistroKilogramosMensual->CargarCantidad(tipodocumento, mes, ano, cantidad * (double)gramos / 1000);
                  break;
                }
        }

        TBookmark posicion = BD->TableDocumentos->GetBookmark();
        //ReducirAnulados(FormConfiguracion->ConservarAnuladosRD());
        BD->TableDocumentos->GotoBookmark(posicion);
        BD->TableDocumentos->FreeBookmark(posicion);
}
//---------------------------------------------------------------------------

void TFormRegistroDocumentos::MostrarDocumento(int tipodocumento, int numerodocumento)
{

        if (BuscarClave(BD->TableDocumentos, "TipoDocumento;NumeroDocumento",
                        Variant(tipodocumento), Variant(numerodocumento)))
        {
                Impresion imp;
                imp.ImprimirDocumento(tipodocumento, true);
        }
        else
        {
                AnsiString mensaje = "El documento no existe.";
                MessageBox(Handle, mensaje.c_str(), Application->Title.c_str(),
                           MB_APPLMODAL | MB_ICONWARNING);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::DBGridDrawColumnCell(
      TObject *Sender, const TRect &Rect, int DataCol, TColumn *Column,
      TGridDrawState State)
{
        TDBGrid *grid = static_cast<TDBGrid*>(Sender);
        if(BD->TableDocumentos->FieldValues["TipoDocumento"] == DOC_PEDIDO)
        {
                grid->Canvas->Font->Color = clFuchsia;
        }
        if(BD->TableDocumentos->FieldValues["Estado"] == EST_ANULADO)
        {
                grid->Canvas->Font->Color = clGray;
        }
        grid->DefaultDrawColumnCell(Rect, DataCol, Column, State);
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::FormCreate(TObject *Sender)
{
        ListaMenuOrdenar lista;
        lista["ISFechaHora"] = "Fecha / Hora";
        lista["ISTipoNumero"] = "Tipo documento / Número documento";
        lista["ISNombreFactura"] = "Nombre factura";
        lista["ISTotal"] = "Total";
        lista["ISEstado"] = "Estado";
        CrearMenuOrdenar(lista, "ISFechaHora", BD->TableDocumentos,
                         MenuItemOrdenar, MenuItemOrdCol);
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::MenuItemOrdCol(TObject *Sender)
{
        SetearMenuOrdenar(BD->TableDocumentos, static_cast< TMenuItem * >(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::FormShow(TObject *Sender)
{
        /* Seteo el index por defecto y muevo a la última fila */
        DefectoMenuOrdenar(BD->TableDocumentos, MenuItemOrdenar);
        BD->DataSourceDocumentos->Enabled = false;
        BD->DataSourceDocumentos->Enabled = true;
        BD->TableDocumentos->Last();
}
//---------------------------------------------------------------------------

void TFormRegistroDocumentos::EliminarDocumento(int tipodocumento, int numerodocumento)
{
        if (tipodocumento != DOC_PEDIDO)
        {
                Abort();
        }

        AnsiString mensaje = "¿Está seguro que desea eliminar el documento " +
                             FormFacturacion->Documentos(tipodocumento) +
                             " número " + numerodocumento + "?";
        int valor = MessageBox(Handle, mensaje.c_str(), Application->Title.c_str(),
                               MB_APPLMODAL | MB_YESNO | MB_ICONWARNING);
        if (valor == IDNO) Abort();

        if (BuscarClave(BD->TableDocumentos, "TipoDocumento;NumeroDocumento",
                        Variant(tipodocumento), Variant(numerodocumento)))
        {
                while (! BD->TableDocumentosDetalles->IsEmpty())
                {
                        BD->TableDocumentosDetalles->Delete();
                }
                BD->TableDocumentos->Delete();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::MenuItemDocumentoClick(
      TObject *Sender)
{
        if (BD->TableDocumentos->FieldByName("TipoDocumento")->AsInteger == DOC_FACTURAELECT ||
            BD->TableDocumentos->FieldByName("TipoDocumento")->AsInteger == DOC_CREDITOELECT ||
            BD->TableDocumentos->FieldByName("TipoDocumento")->AsInteger == DOC_DEBITOELECT)
        {
                MenuItemAnular->Enabled = false;
                MenuItemAnular2->Enabled = false;
                MenuItemImprimir->Enabled = true;
                MenuItemImprimir2->Enabled = true;
                MenuItemEliminar->Enabled = false;
                MenuItemEliminar2->Enabled = false;
        }
        else if (BD->TableDocumentos->FieldByName("TipoDocumento")->AsInteger == DOC_PEDIDO)
        {
                        MenuItemAnular->Enabled = false;
                        MenuItemAnular2->Enabled = false;
                        MenuItemImprimir->Enabled = true;
                        MenuItemImprimir2->Enabled = true;
                        MenuItemEliminar->Enabled = true;
                        MenuItemEliminar2->Enabled = true;
        }
        else
        {
                if (BD->TableDocumentos->FieldByName("Estado")->AsInteger == EST_ANULADO)
                {
                        MenuItemAnular->Enabled = false;
                        MenuItemAnular2->Enabled = false;
                        MenuItemImprimir->Enabled = false;
                        MenuItemImprimir2->Enabled = false;
                        MenuItemEliminar->Enabled = false;
                        MenuItemEliminar2->Enabled = false;
                }
                else
                {
                        MenuItemAnular->Enabled = true;
                        MenuItemAnular2->Enabled = true;
                        MenuItemImprimir->Enabled = true;
                        MenuItemImprimir2->Enabled = true;
                        MenuItemEliminar->Enabled = false;
                        MenuItemEliminar2->Enabled = false;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::MenuItemImprimirPeriodoClick(
      TObject *Sender)
{
        Impresion imp;
        TDate desde, hasta;

        if (BD->TableDocumentos->IsEmpty()) return;

        if (FormSeleccionarPeriodo->Mostrar() == mrOk)
        {
                FormSeleccionarPeriodo->ObtenerPeriodo(desde, hasta);
                imp.ImprimirRegistroDocumentos(desde, hasta, false);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::ToolButtonImprimirPeriodoClick(
      TObject *Sender)
{
        MenuItemImprimirPeriodo->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::ToolButtonMostrarClick(
      TObject *Sender)
{
        MenuItemMostrar->Click();        
}
//---------------------------------------------------------------------------


void __fastcall TFormRegistroDocumentos::ToolButtonEditarClick(
      TObject *Sender)
{
        MenuItemEditar->Click();        
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::ToolButtonAnularClick(
      TObject *Sender)
{
        MenuItemAnular->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::MenuItemVisualizarPeriodoClick(
      TObject *Sender)
{
        Impresion imp;
        TDate desde, hasta;

        if (BD->TableDocumentos->IsEmpty()) return;

        if (FormSeleccionarPeriodo->Mostrar() == mrOk)
        {
                FormSeleccionarPeriodo->ObtenerPeriodo(desde, hasta);
                imp.ImprimirRegistroDocumentos(desde, hasta, true);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::MenuItemExportarPlanillaClick(
      TObject *Sender)
{
        Impresion imp;
        TDate desde, hasta;

        if (FormSeleccionarPeriodo->Mostrar() == mrOk)
        {
                FormSeleccionarPeriodo->ObtenerPeriodo(desde, hasta);
                SaveDialog->DefaultExt = ".txt";
                SaveDialog->Filter = "Documento TXT (*.txt)|*.txt";
                SaveDialog->Options << ofOverwritePrompt << ofFileMustExist << ofHideReadOnly;

                AnsiString current = GetCurrentDir();
                if (SaveDialog->Execute())
                {
                        imp.ExportarPlanillaProductos(desde, hasta, SaveDialog->FileName);
                }
                SetCurrentDir(current);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::MenuItemExportarVentasClick(
      TObject *Sender)
{
        Impresion imp;
        TDate desde, hasta;
        AnsiString directorio;

        if (FormSeleccionarPeriodo->Mostrar() == mrOk)
        {
                FormSeleccionarPeriodo->ObtenerPeriodo(desde, hasta);
                SaveDialog->DefaultExt = ".txt";
                SaveDialog->Filter = "Documento TXT (*.txt)|*.txt";
                SaveDialog->Options << ofOverwritePrompt << ofFileMustExist << ofHideReadOnly;

                AnsiString current = GetCurrentDir();

                if (SelectDirectory("Seleccione un directorio donde guardar los ficheros",
                                    "", directorio))
                {
                        imp.ExportarRegistroVentas(desde, hasta, directorio);
                }

                SetCurrentDir(current);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroDocumentos::MenuItemEliminarClick(
      TObject *Sender)
{
        if (BD->TableDocumentos->IsEmpty()) Abort();
        int tipodocumento = BD->TableDocumentos->FieldValues["TipoDocumento"];
        int numerodocumento = BD->TableDocumentos->FieldValues["NumeroDocumento"];

        EliminarDocumento(tipodocumento, numerodocumento);
}
//---------------------------------------------------------------------------

