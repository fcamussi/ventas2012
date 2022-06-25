//---------------------------------------------------------------------------

#include <vcl.h>
#include <fstream>
#pragma hdrstop

#include "facturacion.h"
#include "basedatos.h"
#include "configuracion.h"
#include "cuentacorriente.h"
#include "seleccionarcliente.h"
#include "seleccionarproducto.h"
#include "numeracion.h"
#include "registrodocumentos.h"
#include "auxiliar.h"
#include "registroventasdiario.h"
#include "registroventasmensual.h"
#include "registroventasanual.h"
#include "impresion.h"
#include "registroproductosdiario.h"
#include "registroproductosmensual.h"
#include "registroproductosanual.h"
#include "registroproductosstock.h"
#include "mensaje.h"
#include "dialogoafip.h"
#include "registrokilogramosmensual.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormFacturacion *FormFacturacion;
AnsiString DOCUMENTOS[DOC_N] = {"Remito",
                                "Factura (Tradicional)",
                                "Nota de crédito (Remito)",
                                "Nota de crédito (Tradicional)",
                                "Factura (Electrónica)",
                                "Nota de crédito (Electrónica)",
                                "Nota de débito (Electrónica)",
                                "Pedido"};
AnsiString ESTADOS[EST_N] = {"Impreso",
                             "Sin imprimir",
                             "Anulado"};
extern AFIP *afip;

//---------------------------------------------------------------------------
__fastcall TFormFacturacion::TFormFacturacion(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

AnsiString TFormFacturacion::Documentos(int tipodocumento)
{
        return DOCUMENTOS[tipodocumento];
}
//---------------------------------------------------------------------------

AnsiString TFormFacturacion::Estados(int estado)
{
        return ESTADOS[estado];
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::StringGridCodigosKeyPress(TObject *Sender,
      char &Key)
{
        if (Key == VK_RETURN && StringGridCodigos->EditorMode)
        {
                if (StringGridCodigos->Col == 0)
                {
                        StringGridCodigos->Col = 1;
                }
                else
                {
                        if (StringGridCodigos->Row < StringGridCodigos->RowCount - 1)
                        {
                                StringGridCodigos->Col = 0;
                                StringGridCodigos->Row++;
                        }
                }
        }
        if (StringGridCodigos->Col == 1) Key = toupper(Key);
}
//---------------------------------------------------------------------------

void TFormFacturacion::ConfigurarRenglones(int tipodocumento)
{
        /* Se setea la cantidad de renglones */
        int numerorenglones = FormConfiguracion->NumeroRenglones(tipodocumento);
        StringGridCodigos->RowCount = numerorenglones + 1;
        StringGridFactura->RowCount = numerorenglones + 1;
}
//---------------------------------------------------------------------------

void TFormFacturacion::NuevoDocumento(int numerocliente, int tipodocumento)
{
        BuscarClave(BD->TableClientes, "NumeroCliente", Variant(numerocliente));

        EditFecha->Text = Date();
        EditHora->Text = Time();
        ComboBoxTipoDocumento->ItemIndex = tipodocumento;
        EditNumeroDocumento->Text = NumeroDocumentos(tipodocumento) + 1;
        ConfigurarRenglones(tipodocumento);
        LimpiarRenglones();
        /* Limpio el array de sin cargo */
        SinCargo.assign(StringGridCodigos->RowCount - 1, false);
        MemoComunicado->Clear();
        /* Asigno el descuento por defecto */
        EditDescuento->Text = BD->TableClientes->FieldValues["Descuento"];

        ShowModal();
}
//---------------------------------------------------------------------------

void TFormFacturacion::EditarDocumento(int numerocliente, int tipodocumento,
                                       int numerodocumento)
{
        BuscarClave(BD->TableClientes, "NumeroCliente", Variant(numerocliente));
        BuscarClave(BD->TableDocumentos, "TipoDocumento;NumeroDocumento",
                    Variant(tipodocumento), Variant(numerodocumento));

        EditFecha->Text = Date();
        EditHora->Text = Time();
        ComboBoxTipoDocumento->ItemIndex = tipodocumento;
        EditNumeroDocumento->Text = NumeroDocumentos(tipodocumento) + 1;
        ConfigurarRenglones(tipodocumento);
        LimpiarRenglones();
        SinCargo.assign(StringGridCodigos->RowCount - 1, false);
        CargarRenglones(tipodocumento, numerodocumento);
        MemoComunicado->Text = BD->TableDocumentos->FieldValues["Comunicado"];
        EditDescuento->Text = BD->TableDocumentos->FieldValues["Descuento"];

        ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::FormCreate(TObject *Sender)
{
        /* Títulos para la grilla de los codigos */
        StringGridCodigos->Cells[0][0] = "Cantidad";
        StringGridCodigos->Cells[1][0] = "Código";

        /* Títulos para la grilla de la factura */
        StringGridFactura->Cells[0][0] = "Cantidad";
        StringGridFactura->Cells[1][0] = "Unidad";
        StringGridFactura->Cells[2][0] = "Descripción";
        StringGridFactura->Cells[3][0] = "Precio";
        StringGridFactura->Cells[4][0] = "Importe";

        for (int c = 0; c < DOC_N; c++)
        {
                ComboBoxTipoDocumento->Items->Add(DOCUMENTOS[c]);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::ButtonSiguienteClick(TObject *Sender)
{
        if (TraducirCodigos())
        {
                if (CalcularFactura())
                {
                        /* Cambio de panel */
                        PanelFactura1->Visible = false;
                        PanelFactura2->Visible = true;

                        MenuItemCambiarCliente->Enabled = false;
                        MenuItemProducto->Enabled = false;
                        ToolButtonCambiarCliente->Enabled = false;
                }
        }
        else
        {
                MessageBox(Handle, "Se ha encontrado un error. "
                           "Por favor corrijalo y vuelva a intentarlo.",
                           Application->Title.c_str(),
                           MB_APPLMODAL | MB_OK | MB_ICONWARNING);
                StringGridCodigos->SetFocus();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::ButtonVolverClick(TObject *Sender)
{
        /* Cambio de panel */
        PanelFactura2->Visible = false;
        PanelFactura1->Visible = true;

        MenuItemCambiarCliente->Enabled = true;
        MenuItemProducto->Enabled = true;
        ToolButtonCambiarCliente->Enabled = true;

        StringGridCodigos->SetFocus();
}
//---------------------------------------------------------------------------

bool TFormFacturacion::TraducirCodigos()
{
        AnsiString cantidad;
        int cant;
        AnsiString codigo;
        double precio;
        AnsiString columnaprecio;

        if (DBEditPosicionIVA->Text == "Consumidor final" &&
            ComboBoxTipoDocumento->ItemIndex != DOC_REMITO &&
            ComboBoxTipoDocumento->ItemIndex != DOC_CREDITOREMITO &&
            ComboBoxTipoDocumento->ItemIndex != DOC_PEDIDO)
        {
                MessageBox(Handle, "No puede realizarse este tipo de documentos "
                           "para consumidores finales", Application->Title.c_str(),
                           MB_APPLMODAL | MB_OK | MB_ICONWARNING);
                           Abort();
        }

        if (ComboBoxTipoDocumento->ItemIndex == DOC_REMITO ||
            ComboBoxTipoDocumento->ItemIndex == DOC_CREDITOREMITO)
        {
                columnaprecio = "Precio1";
        }
        else if (ComboBoxTipoDocumento->ItemIndex == DOC_FACTURA ||
                 ComboBoxTipoDocumento->ItemIndex == DOC_CREDITOFACTURA ||
                 ComboBoxTipoDocumento->ItemIndex == DOC_FACTURAELECT ||
                 ComboBoxTipoDocumento->ItemIndex == DOC_CREDITOELECT ||
                 ComboBoxTipoDocumento->ItemIndex == DOC_DEBITOELECT)
        {
                if (DBEditPosicionIVA->Text == "Responsable inscripto" ||
                    DBEditPosicionIVA->Text == "Responsable monotributo")
                {
                        columnaprecio = "Precio2";
                }
                if (DBEditPosicionIVA->Text == "Otro")
                {
                        columnaprecio = "Precio3";
                }
        }
        else if (ComboBoxTipoDocumento->ItemIndex == DOC_PEDIDO)
        {
                columnaprecio = "";
        }

        /* Traduzco los códigos */
        for (int c = 1; c <= StringGridCodigos->RowCount; c++)
        {
                cantidad = StringGridCodigos->Cells[0][c].Trim();
                codigo = StringGridCodigos->Cells[1][c].Trim();

                if (cantidad.IsEmpty() && codigo.IsEmpty())
                {
                        StringGridFactura->Rows[c]->Clear();
                        continue;
                }

                cant = cantidad.ToIntDef(0);
                if (cant <= 0)
                {
                        StringGridCodigos->Col = 0;
                        StringGridCodigos->Row = c;
                        return false;
                }

                if (! BuscarClave(BD->TableProductos, "CodigoProducto", Variant(codigo)))
                {
                        StringGridCodigos->Col = 1;
                        StringGridCodigos->Row = c;
                        return false;
                }

                StringGridFactura->Cells[0][c] = cant;

                StringGridFactura->Cells[1][c] = BD->TableProductos
                                                   ->FieldByName("Unidad")
                                                   ->AsString;

                StringGridFactura->Cells[2][c] = BD->TableProductos
                                                   ->FieldByName("Descripcion")
                                                   ->AsString;

                if (SinCargo[c - 1] == true ||
                    ComboBoxTipoDocumento->ItemIndex == DOC_PEDIDO)
                {
                        precio = 0;
                }
                else
                {
                        precio = BD->TableProductos->FieldByName(columnaprecio)
                                                   ->AsFloat;
                }
                StringGridFactura->Cells[3][c] = FormatFloat("0.00", precio);
        }

        return true;
}
//---------------------------------------------------------------------------

bool TFormFacturacion::CalcularFactura()
{
        /* Calculo la factura */
        int cantidad;
        double precio, importe, subtotal = 0;

        for (int c = 1; c <= StringGridCodigos->RowCount; c++)
        {
                cantidad = StringGridFactura->Cells[0][c].ToIntDef(0);
                if (cantidad == 0) continue;
                precio = StringGridFactura->Cells[3][c].ToDouble();
                importe = cantidad * precio;
                StringGridFactura->Cells[4][c] = FormatFloat("0.00", importe);
                subtotal += importe;
        }

        EditSubtotal->Text = FormatFloat("0.00", subtotal);

        double descuento;
        try {
                descuento = EditDescuento->Text.ToDouble();
                if (descuento < 0 || descuento > 100) throw EConvertError("");
        }
        catch (EConvertError &E)
        {
                MessageBox(Handle, "El valor ingresado para Descuento no es"
                           "válido.", Application->Title.c_str(),
                           MB_APPLMODAL | MB_OK | MB_ICONWARNING);
                return false;
        }
        LabelDescuento->Caption = "(" + FloatToStr(descuento) + "%)";

        double descuentototal = (subtotal * descuento) / 100;
        EditDescuentoTotal->Text = FormatFloat("0.00", descuentototal);

        double subtotal2 = subtotal - descuentototal;
        EditSubtotal2->Text = FormatFloat("0.00", subtotal2);

        double ivatotal = 0;
        LabelIVA->Caption = "";
        EditIVATotal->Text = 0;
        if (ComboBoxTipoDocumento->ItemIndex == DOC_FACTURA ||
            ComboBoxTipoDocumento->ItemIndex == DOC_CREDITOFACTURA ||
            ComboBoxTipoDocumento->ItemIndex == DOC_FACTURAELECT ||
            ComboBoxTipoDocumento->ItemIndex == DOC_CREDITOELECT ||
            ComboBoxTipoDocumento->ItemIndex == DOC_DEBITOELECT)
        {
                if (DBEditPosicionIVA->Text == "Responsable inscripto" ||
                    DBEditPosicionIVA->Text == "Responsable monotributo")
                {
                        double iva = FormConfiguracion->ValorIVA();
                        LabelIVA->Caption = "(" + FloatToStr(iva) + "%)";
                        ivatotal = (subtotal2 * iva) / 100;
                        EditIVATotal->Text = FormatFloat("0.00", ivatotal);
                }
        }

        double total = subtotal2 + ivatotal;
        EditTotal->Text = FormatFloat("0.00", total);
        return true;
}
//---------------------------------------------------------------------------

void TFormFacturacion::LimpiarRenglones()
{
        for (int c = 1; c <= StringGridCodigos->RowCount; c++)
                StringGridCodigos->Rows[c]->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::FormShow(TObject *Sender)
{
        PanelFactura2->Visible = false;
        PanelFactura1->Visible = true;

        MenuItemCambiarCliente->Enabled = true;
        MenuItemProducto->Enabled = true;
        ToolButtonCambiarCliente->Enabled = true;

        StringGridCodigos->Col = 0;
        StringGridCodigos->Row = 1;
        StringGridFactura->Col = 0;
        StringGridFactura->Row = 1;
        StringGridCodigos->SetFocus();

        if (ComboBoxTipoDocumento->ItemIndex == DOC_REMITO ||
            ComboBoxTipoDocumento->ItemIndex == DOC_CREDITOREMITO ||
            ComboBoxTipoDocumento->ItemIndex == DOC_CREDITOFACTURA ||
            ComboBoxTipoDocumento->ItemIndex == DOC_PEDIDO)
        {
                PanelAFIP->Visible = false;
                PanelNumeroComprobante->Visible = false;
                PanelComprobanteAsociado->Visible = false;
        }
        else if (ComboBoxTipoDocumento->ItemIndex == DOC_FACTURA)
        {
                PanelAFIP->Visible = false;
                PanelNumeroComprobante->Visible = true;
                PanelComprobanteAsociado->Visible = false;
        }
        else if (ComboBoxTipoDocumento->ItemIndex == DOC_FACTURAELECT)
        {
                PanelAFIP->Visible = true;
                PanelNumeroComprobante->Visible = false;
                PanelComprobanteAsociado->Visible = false;
        }
        else if (ComboBoxTipoDocumento->ItemIndex == DOC_CREDITOELECT ||
                 ComboBoxTipoDocumento->ItemIndex == DOC_DEBITOELECT)
        {
                PanelAFIP->Visible = true;
                PanelNumeroComprobante->Visible = false;
                PanelComprobanteAsociado->Visible = true;
        }

        EditNumeroComprobante->Text = "";
        EditNumeroComprobanteAsociado->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::EditDescuentoKeyPress(TObject *Sender,
      char &Key)
{
        if (Key == '+' || Key == '-')
                Abort();
        if (Key == '.')
                if (EditDescuento->Text.AnsiPos(".") &&
                    ! EditDescuento->SelText.AnsiPos(".")) Abort();
}
//---------------------------------------------------------------------------

void TFormFacturacion::ArchivarDocumento(int estado)
{
        int tipodocumento = ComboBoxTipoDocumento->ItemIndex;
        int numerodocumento = EditNumeroDocumento->Text.ToInt();
        TTable *tabla = static_cast<TTable *>(BD->TableDocumentos);
        TTable *tabladetalles = static_cast<TTable *>(BD->TableDocumentosDetalles);
        int cantidad;

        /* Se agrega a la tabla de documentos */
        tabla->Append();
        tabla->FieldValues["TipoDocumento"] = tipodocumento;
        tabla->FieldValues["NumeroDocumento"] = numerodocumento;
        tabla->FieldValues["NumeroCliente"] = DBEditNumeroCliente->Text.ToInt();
        tabla->FieldValues["Fecha"] = StrToDate(EditFecha->Text);
        tabla->FieldValues["Hora"] = StrToTime(EditHora->Text);
        tabla->FieldValues["NombreFactura"] = DBEditNombreFactura->Text;
        tabla->FieldValues["Subtotal"] = EditSubtotal->Text.ToDouble();
        tabla->FieldValues["Descuento"] = EditDescuento->Text.ToDouble();
        tabla->FieldValues["DescuentoTotal"] = EditDescuentoTotal->Text.ToDouble();
        tabla->FieldValues["Subtotal2"] = EditSubtotal2->Text.ToDouble();
        tabla->FieldValues["IVA"] = FormConfiguracion->ValorIVA();
        tabla->FieldValues["IVATotal"] = EditIVATotal->Text.ToDouble();
        tabla->FieldValues["Total"] = EditTotal->Text.ToDouble();
        tabla->FieldValues["Estado"] = estado;
        tabla->FieldValues["Direccion"] = DBEditDireccion->Text;
        tabla->FieldValues["Localidad"] = DBEditLocalidad->Text;
        tabla->FieldValues["Provincia"] = DBEditProvincia->Text;
        tabla->FieldValues["PosicionIVA"] = DBEditPosicionIVA->Text;
        tabla->FieldValues["FormaPago"] = BD->TableClientes->FieldByName("FormaPago")->AsString;
        tabla->FieldValues["CUIT"] = DBEditCUIT->Text;
        tabla->FieldValues["Comunicado"] = MemoComunicado->Text;
        tabla->Post();

        if (tipodocumento == DOC_FACTURA) ArchivarDatosFT();

        /* Se guardan los detalles */
        for (int c = 1; c <= StringGridCodigos->RowCount; c++)
        {
                cantidad = StringGridFactura->Cells[0][c].ToIntDef(0);
                if (cantidad == 0) continue;
                tabladetalles->Append();
                tabladetalles->FieldValues["TipoDocumento"] = tipodocumento;
                tabladetalles->FieldValues["NumeroDocumento"] = numerodocumento;
                tabladetalles->FieldValues["NumeroRenglon"] = c;
                tabladetalles->FieldValues["Cantidad"] = cantidad;
                tabladetalles->FieldValues["CodigoProducto"] = StringGridCodigos->Cells[1][c];
                tabladetalles->FieldValues["Unidad"] = StringGridFactura->Cells[1][c];
                tabladetalles->FieldValues["Descripcion"] = StringGridFactura->Cells[2][c];
                tabladetalles->FieldValues["Precio"] = StringGridFactura->Cells[3][c].ToDouble();
                tabladetalles->FieldValues["SinCargo"] = static_cast<bool>(SinCargo[c - 1]);
                tabladetalles->FieldValues["Importe"] = StringGridFactura->Cells[4][c].ToDouble();
                tabladetalles->Post();
        }

        TDate fecha = StrToDate(EditFecha->Text);
        double monto = EditTotal->Text.ToDouble();
        int mes = fecha.FormatString("m").ToInt();
        int ano = fecha.FormatString("yyyy").ToInt();

        switch(tipodocumento)
        {
          case DOC_REMITO:
          case DOC_FACTURA:
          case DOC_FACTURAELECT:
          case DOC_DEBITOELECT:
                FormRegistroVentasDiario->CargarMonto(tipodocumento, fecha, monto);
                FormRegistroVentasMensual->CargarMonto(tipodocumento, mes, ano, monto);
                FormRegistroVentasAnual->CargarMonto(tipodocumento, ano, monto);
          break;
          case DOC_CREDITOREMITO:
          case DOC_CREDITOFACTURA:
          case DOC_CREDITOELECT:
                FormRegistroVentasDiario->DescargarMonto(tipodocumento, fecha, monto);
                FormRegistroVentasMensual->DescargarMonto(tipodocumento, mes, ano, monto);
                FormRegistroVentasAnual->DescargarMonto(tipodocumento, ano, monto);
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
                  case DOC_FACTURAELECT:
                  case DOC_DEBITOELECT:
                        FormRegistroProductosStock->DescargarStock(codigo, cantidad);
                        if (sincargo) continue;
                        FormRegistroProductosDiario->CargarCantidad(tipodocumento, codigo, fecha, cantidad);
                        FormRegistroProductosMensual->CargarCantidad(tipodocumento, codigo, mes, ano, cantidad);
                        FormRegistroProductosAnual->CargarCantidad(tipodocumento, codigo, ano, cantidad);
                        FormRegistroKilogramosMensual->CargarCantidad(tipodocumento, mes, ano, cantidad * (double)gramos / 1000);
                  break;
                  case DOC_CREDITOREMITO:
                  case DOC_CREDITOFACTURA:
                  case DOC_CREDITOELECT:
                        FormRegistroProductosStock->CargarStock(codigo, cantidad);
                        if (sincargo) continue;
                        FormRegistroProductosDiario->DescargarCantidad(tipodocumento, codigo, fecha, cantidad);
                        FormRegistroProductosMensual->DescargarCantidad(tipodocumento, codigo, mes, ano, cantidad);
                        FormRegistroProductosAnual->DescargarCantidad(tipodocumento, codigo, ano, cantidad);
                        FormRegistroKilogramosMensual->DescargarCantidad(tipodocumento, mes, ano, cantidad * (double)gramos / 1000);
                  break;
                }
        }
}
//---------------------------------------------------------------------------

void TFormFacturacion::CargarEnCuentaCorriente()
{
        double numerodocumento = EditNumeroDocumento->Text.ToDouble();
        int tipodocumento = ComboBoxTipoDocumento->ItemIndex;
        double total = EditTotal->Text.ToDouble();
        // El saldo parcial se calcula automaticamente cuando se hace el post //
        switch(tipodocumento)
        {
          case DOC_REMITO:
          case DOC_FACTURA:
          case DOC_FACTURAELECT:
          case DOC_DEBITOELECT:
                FormCuentaCorriente->AgregarRegistro(EditFecha->Text, EditHora->Text,
                                                     total, 0, tipodocumento, numerodocumento);
          break;
          case DOC_CREDITOREMITO:
          case DOC_CREDITOFACTURA:
          case DOC_CREDITOELECT:
                FormCuentaCorriente->AgregarRegistro(EditFecha->Text, EditHora->Text,
                                                     0, total, tipodocumento, numerodocumento);
          break;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::ComboBoxTipoDocumentoChange(
      TObject *Sender)
{
        int tipodocumento = ComboBoxTipoDocumento->ItemIndex;
        EditNumeroDocumento->Text = NumeroDocumentos(tipodocumento) + 1;
        int antes = StringGridCodigos->RowCount;
        ConfigurarRenglones(ComboBoxTipoDocumento->ItemIndex);
        if (StringGridCodigos->RowCount > antes)
        {
                SinCargo.resize(StringGridCodigos->RowCount - 1, false);
        }

        if (ComboBoxTipoDocumento->ItemIndex == DOC_REMITO ||
            ComboBoxTipoDocumento->ItemIndex == DOC_CREDITOREMITO ||
            ComboBoxTipoDocumento->ItemIndex == DOC_CREDITOFACTURA ||
            ComboBoxTipoDocumento->ItemIndex == DOC_PEDIDO)
        {
                PanelAFIP->Visible = false;
                PanelNumeroComprobante->Visible = false;
                PanelComprobanteAsociado->Visible = false;
        }
        else if (ComboBoxTipoDocumento->ItemIndex == DOC_FACTURA)
        {
                PanelAFIP->Visible = false;
                PanelNumeroComprobante->Visible = true;
                PanelComprobanteAsociado->Visible = false;
        }
        else if (ComboBoxTipoDocumento->ItemIndex == DOC_FACTURAELECT)
        {
                PanelAFIP->Visible = true;
                PanelNumeroComprobante->Visible = false;
                PanelComprobanteAsociado->Visible = false;
        }
        else if (ComboBoxTipoDocumento->ItemIndex == DOC_CREDITOELECT ||
                 ComboBoxTipoDocumento->ItemIndex == DOC_DEBITOELECT)
        {
                PanelAFIP->Visible = true;
                PanelNumeroComprobante->Visible = false;
                PanelComprobanteAsociado->Visible = true;
        }

        EditNumeroComprobante->Text = "";
        EditNumeroComprobanteAsociado->Text = "";

}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::ButtonImprimirSinImprimirClick(TObject *Sender)
{
        TComponent *button = (TComponent *)Sender;
        FE fe;
        AnsiString msg;

        if (ComboBoxTipoDocumento->ItemIndex == DOC_FACTURA &&
            EditNumeroComprobante->Text.ToIntDef(0) == 0)
        {
                MessageBox(Handle, "Debe ingresar el número de comprobante",
                           Application->Title.c_str(),
                           MB_APPLMODAL | MB_OK | MB_ICONERROR);
                Abort();
        }

        if ((ComboBoxTipoDocumento->ItemIndex == DOC_CREDITOELECT ||
             ComboBoxTipoDocumento->ItemIndex == DOC_DEBITOELECT) &&
            EditNumeroComprobanteAsociado->Text.ToIntDef(0) == 0)
        {
                MessageBox(Handle, "Debe ingresar el número de comprobante asociado",
                           Application->Title.c_str(),
                           MB_APPLMODAL | MB_OK | MB_ICONERROR);
                Abort();
        }

        BD->FlushEnabled(false);
        BD->Database->StartTransaction();

        IncrementarNumeroDocumentos(ComboBoxTipoDocumento->ItemIndex);
        if (button->Name == "ButtonImprimir")
        {
                ArchivarDocumento(EST_IMPRESO);
        }
        else if (button->Name == "ButtonSinImprimir")
        {
                ArchivarDocumento(EST_SINIMPRIMIR);
        }
        if (ComboBoxTipoDocumento->ItemIndex != DOC_PEDIDO)
        {
                CargarEnCuentaCorriente();
        }

        if (ComboBoxTipoDocumento->ItemIndex == DOC_FACTURAELECT ||
            ComboBoxTipoDocumento->ItemIndex == DOC_CREDITOELECT ||
            ComboBoxTipoDocumento->ItemIndex == DOC_DEBITOELECT)
        {
                Mensaje mensaje("Solicitando autorización a la AFIP...");
                mensaje.Mostrar();

                try
                {
                        CargarFE(fe);
                        if (ComboBoxTipoDocumento->ItemIndex == DOC_CREDITOELECT ||
                            ComboBoxTipoDocumento->ItemIndex == DOC_DEBITOELECT)
                        {
                                    AgregarComprobanteAsociado(fe);
                        }
                        fe.nombre_cliente = ObtenerNombreAFIP(fe.nro_doc);
                        afip->AutorizarComprobante(fe);
                }
                catch(EAFIP &e)
                {
                        BD->CancelarTablas();
                        BD->Database->Rollback();
                        BD->RefrescarTablas();
                        BD->FlushEnabled(true);
                        mensaje.Cerrar();
                        msg = "### AFIP ERROR ###\n\n" + e.Message;
                        MessageBox(Handle, msg.c_str(), Application->Title.c_str(),
                                   MB_APPLMODAL | MB_OK | MB_ICONERROR);
                        Abort();
                }
                catch(EAFIPAdv &e)
                {
                        mensaje.Cerrar();
                        msg = "### AFIP ADVERTENCIA ###\n\n" + e.Message;
                        MessageBox(Handle, msg.c_str(), Application->Title.c_str(),
                                   MB_APPLMODAL | MB_OK | MB_ICONWARNING);
                }
                catch (...)
                {
                        BD->CancelarTablas();
                        BD->Database->Rollback();
                        BD->RefrescarTablas();
                        BD->FlushEnabled(true);
                        mensaje.Cerrar();
                        msg = "Sucedió algo inesperado en el módulo AFIP. "
                              "Contacte con el programador.";
                        MessageBox(Handle, msg.c_str(), Application->Title.c_str(),
                                   MB_APPLMODAL | MB_OK | MB_ICONERROR);
                        throw;
                }

                ArchivarDatosFE(fe);
                mensaje.Cerrar();
        }

        BD->Database->Commit();
        BD->FlushTablas();
        BD->FlushEnabled(true);

        if (! MemoComunicado->Text.IsEmpty())
        {
                FormConfiguracion->Comunicado(MemoComunicado->Text);
        }

        if (button->Name == "ButtonImprimir")
        {
                Impresion imp;
                imp.ImprimirDocumento(ComboBoxTipoDocumento->ItemIndex, false);
        }

        if (ComboBoxTipoDocumento->ItemIndex == DOC_FACTURAELECT ||
            ComboBoxTipoDocumento->ItemIndex == DOC_CREDITOELECT ||
            ComboBoxTipoDocumento->ItemIndex == DOC_DEBITOELECT)
        {
                AnsiString texto;

                if (! fe.obs_afip.IsEmpty())
                {
                        texto += "Observaciones:\r\n" + fe.obs_afip + "\r\n\r\n";
                }
                if (fe.eventos.size() > 0)
                {
                        vector<AnsiString>::const_iterator it;

                        texto += "Eventos:\r\n";
                        for (it = fe.eventos.begin(); it != fe.eventos.end(); it++)
                        {
                                texto += *it;
                                texto += "\r\n";
                        }
                        texto += "\r\n";
                }
                if (! texto.IsEmpty())
                {
                        FormDialogoAFIP->Memo->Text = texto;
                        FormDialogoAFIP->ShowModal();
                }
        }

        Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::StringGridCodigosContextPopup(
      TObject *Sender, TPoint &MousePos, bool &Handled)
{
        TGridCoord coord = StringGridCodigos->MouseCoord(MousePos.x, MousePos.y);
        if (!(coord.X < 0 || coord.Y < 1))
        {
                StringGridCodigos->Col = coord.X;
                StringGridCodigos->Row = coord.Y;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::BitBtnRecuperarUltimoClick(TObject *Sender)
{
        MemoComunicado->Text = FormConfiguracion->Comunicado();
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::StringGridCodigosDrawCell(
      TObject *Sender, int ACol, int ARow, TRect &Rect,
      TGridDrawState State)
{
        TStringGrid *grid = static_cast<TStringGrid *>(Sender);
        TCanvas *canvas = grid->Canvas;
        if (SinCargo[ARow - 1] == true)
        {
                canvas->Brush->Color = clGreen;
                canvas->FillRect(Rect);
                canvas->Font->Color = clWhite;
                // DT_VCENTER no anda
                Rect.top += 2;
                Rect.left += 2;
                // pero parece que esto lo soluciona :-)
                DrawText(canvas->Handle, grid->Cells[ACol][ARow].c_str(),
                grid->Cells[ACol][ARow].Length(), &Rect, DT_LEFT);
        }
}
//---------------------------------------------------------------------------

void TFormFacturacion::CargarRenglones(int tipodocumento, int numerodocumento)
{
        int renglones;
        TTable *tabla = static_cast<TTable *>(BD->TableDocumentos);
        TTable *tabladetalles = static_cast<TTable *>(BD->TableDocumentosDetalles);

        BuscarClave(tabla, "TipoDocumento;NumeroDocumento", Variant(tipodocumento),
                    Variant(numerodocumento));

        renglones = min(StringGridCodigos->RowCount - 1,
                        tabladetalles->RecordCount);

        tabladetalles->First();
        for (int c = 1; c <= renglones; c++)
        {
                StringGridCodigos->Cells[0][c] = tabladetalles->FieldValues["Cantidad"];
                StringGridCodigos->Cells[1][c] = tabladetalles->FieldValues["CodigoProducto"];
                SinCargo[c - 1] = tabladetalles->FieldValues["SinCargo"];
                tabladetalles->Next();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::MenuItemCerrarClick(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::MenuItemCambiarClienteClick(
      TObject *Sender)
{
        int numerocliente = FormSeleccionarCliente->Mostrar(
                                            DBEditNumeroCliente->Text.ToInt());
        if (numerocliente > 0)
        {
                /* Localizo el cliente en la tabla */
                BuscarClave(BD->TableClientes, "NumeroCliente", Variant(numerocliente));
                /* Asigno el descuento por defecto */
                EditDescuento->Text = BD->TableClientes->FieldValues["Descuento"];
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::MenuItemSeleccionarClick(TObject *Sender)
{
        AnsiString defecto = StringGridCodigos->Cells[1][StringGridCodigos->Row];
        AnsiString codigoproducto = FormSeleccionarProducto->Mostrar(defecto);
        if (! codigoproducto.IsEmpty())
        {
                StringGridCodigos->Cells[1][StringGridCodigos->Row] = codigoproducto;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::MenuItemSinCargoClick(TObject *Sender)
{
        TMenuItem *menuitem = static_cast<TMenuItem *>(Sender);

        SinCargo[StringGridCodigos->Row - 1] = ! menuitem->Checked;

        // Refresco para que se dibuje de nuevo
        StringGridCodigos->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::MenuItemProductoClick(TObject *Sender)
{
        MenuItemSinCargo->Checked = SinCargo[StringGridCodigos->Row - 1];
        MenuItemSinCargo2->Checked = SinCargo[StringGridCodigos->Row - 1];
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::ToolButtonCambiarClienteClick(
      TObject *Sender)
{
        MenuItemCambiarCliente->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::StringGridFacturaDrawCell(
      TObject *Sender, int ACol, int ARow, TRect &Rect,
      TGridDrawState State)
{
        TStringGrid *grid = static_cast<TStringGrid *>(Sender);
        TCanvas *canvas = grid->Canvas;

        if (ARow == 0) return; // Títulos

        AnsiString cantidad = StringGridCodigos->Cells[0][ARow].Trim();
        AnsiString codigo = StringGridCodigos->Cells[1][ARow].Trim();

        if (cantidad.IsEmpty() && codigo.IsEmpty()) return; // Vacíos

        if (FormRegistroProductosStock->CantidadStock(codigo) < cantidad.ToInt())
        {
                canvas->Brush->Color = clRed;
                canvas->FillRect(Rect);
                canvas->Font->Color = clWhite;
                // DT_VCENTER no anda
                Rect.top += 2;
                Rect.left += 2;
                // pero parece que esto lo soluciona :-)
                DrawText(canvas->Handle, grid->Cells[ACol][ARow].c_str(),
                grid->Cells[ACol][ARow].Length(), &Rect, DT_LEFT);
        }
}
//---------------------------------------------------------------------------

void TFormFacturacion::CargarFE(FE &fe)
{
        TTable *tabla = static_cast<TTable *>(BD->TableDocumentos);
        TTable *tabladetalles = static_cast<TTable *>(BD->TableDocumentosDetalles);

        fe.nro_doc = tabla->FieldByName("CUIT")->AsString;
        fe.fecha_cbte = tabla->FieldByName("Fecha")->AsDateTime;
        fe.id_impositivo = tabla->FieldByName("PosicionIVA")->AsString;
        fe.domicilio_cliente = tabla->FieldByName("Direccion")->AsString;
        fe.localidad_cliente = tabla->FieldByName("Localidad")->AsString;
        fe.provincia_cliente = tabla->FieldByName("Provincia")->AsString;
        fe.desc = tabla->FieldByName("Descuento")->AsFloat;
        fe.imp_desc = tabla->FieldByName("DescuentoTotal")->AsFloat;
        fe.nro_ctrl = tabla->FieldByName("NumeroDocumento")->AsInteger;
        fe.obs_generales = tabla->FieldByName("Comunicado")->AsString;

        tabladetalles->First();
        int cantidad;
        AnsiString unidad, descripcion;
        double precio, importe;
        while (! tabladetalles->Eof)
        {
                cantidad = tabladetalles->FieldByName("Cantidad")->AsInteger;
                unidad = tabladetalles->FieldByName("Unidad")->AsString;
                descripcion = tabladetalles->FieldByName("Descripcion")->AsString;
                precio = tabladetalles->FieldByName("Precio")->AsFloat;
                importe = tabladetalles->FieldByName("Importe")->AsFloat;
                fe.items.push_back(Item(cantidad,
                                        descripcion + " (" + unidad + ")",
                                        precio,
                                        importe));
                tabladetalles->Next();
        }

        if (fe.id_impositivo == "Responsable inscripto" ||
            fe.id_impositivo == "Responsable monotributo")
        {
                switch(tabla->FieldByName("TipoDocumento")->AsInteger)
                {
                    case DOC_FACTURA:
                    case DOC_FACTURAELECT:
                        fe.tipo_cbte = 1; // Factura A
                    break;
                    case DOC_CREDITOELECT:
                        fe.tipo_cbte = 3; // Nota de Crédito A
                    break;
                    case DOC_DEBITOELECT:
                        fe.tipo_cbte = 2; // Nota de Débito A
                    break;
                    default:
                        throw;
                }
                fe.imp_neto = tabla->FieldByName("Subtotal2")->AsFloat;
                fe.imp_iva = tabla->FieldByName("IVATotal")->AsFloat;
                fe.imp_total = tabla->FieldByName("Total")->AsFloat;

        }
        else if (fe.id_impositivo == "Otro")
        {
                switch(tabla->FieldByName("TipoDocumento")->AsInteger)
                {
                    case DOC_FACTURA:
                    case DOC_FACTURAELECT:
                        fe.tipo_cbte = 6; // Factura B
                    break;
                    case DOC_CREDITOELECT:
                        fe.tipo_cbte = 8; // Nota de Crédito B
                    break;
                    case DOC_DEBITOELECT: // Nota de Débito B
                        fe.tipo_cbte = 7;
                    break;
                    default:
                        throw;
                }
                fe.imp_total = tabla->FieldByName("Total")->AsFloat;
                fe.imp_neto = FormatFloat("0.00", fe.imp_total / 1.21).ToDouble(); // Deberia hacerse en el modulo AFIP?
                fe.imp_iva = fe.imp_total - fe.imp_neto;
        }
        else throw Exception("");
}
//---------------------------------------------------------------------------

void TFormFacturacion::ArchivarDatosFE(FE &fe)
{
        int tipodocumento = ComboBoxTipoDocumento->ItemIndex;
        int numerodocumento = EditNumeroDocumento->Text.ToInt();
        TTable *tabla = static_cast<TTable *>(BD->TableFacturaElectronica);

        tabla->Append();
        tabla->FieldValues["TipoDocumento"] = tipodocumento;
        tabla->FieldValues["NumeroDocumento"] = numerodocumento;
        tabla->FieldValues["Tipo_cbte"] = fe.tipo_cbte;
        tabla->FieldValues["Cbte_nro"] = fe.cbte_nro;
        tabla->FieldValues["Cae"] = fe.cae;
        tabla->FieldValues["Vto_cae"] = fe.vto_cae;
        tabla->FieldValues["Obs_afip"] = fe.obs_afip;
        tabla->FieldValues["NombreAFIP"] = fe.nombre_cliente;
        tabla->Post();
}
//---------------------------------------------------------------------------

void TFormFacturacion::CargarDatosFE(FE &fe)
{
        TTable *tabla = static_cast<TTable *>(BD->TableFacturaElectronica);

        tabla->First();
        fe.tipo_cbte = tabla->FieldByName("Tipo_cbte")->AsInteger; // ya está cargado?
        fe.cbte_nro = tabla->FieldByName("Cbte_nro")->AsInteger;
        fe.cae = tabla->FieldByName("Cae")->AsString;
        fe.vto_cae = tabla->FieldByName("Vto_cae")->AsDateTime;
        fe.obs_afip = tabla->FieldByName("Obs_afip")->AsString;
        fe.nombre_cliente = tabla->FieldByName("NombreAFIP")->AsString;
}
//---------------------------------------------------------------------------

AnsiString TFormFacturacion::ObtenerNombreAFIP(AnsiString cuit)
{
        AnsiString denominacion;

        if (! BuscarClave(BD->TablePadronAFIP, "CUIT", Variant(cuit)))
        {
                denominacion = afip->ObtenerDenominacion(cuit);
                BD->TablePadronAFIP->Append();
                BD->TablePadronAFIP->FieldValues["CUIT"] = cuit;
                BD->TablePadronAFIP->FieldValues["NombreAFIP"] = denominacion;
                BD->TablePadronAFIP->Post();
        }

        return BD->TablePadronAFIP->FieldByName("NombreAFIP")->AsString;
}
//---------------------------------------------------------------------------

void __fastcall TFormFacturacion::EditNumeroComprobanteKeyPress(
      TObject *Sender, char &Key)
{
        if (! isdigit(Key) && Key != VK_BACK && Key != VK_DELETE) Abort();
}
//---------------------------------------------------------------------------

void TFormFacturacion::ArchivarDatosFT()
{
        int tipodocumento = ComboBoxTipoDocumento->ItemIndex;
        int numerodocumento = EditNumeroDocumento->Text.ToInt();

        BD->TableFacturaTradicional->Append();
        BD->TableFacturaTradicional->FieldValues["TipoDocumento"] = tipodocumento;
        BD->TableFacturaTradicional->FieldValues["NumeroDocumento"] = numerodocumento;
        if (DBEditPosicionIVA->Text == "Responsable inscripto" ||
            DBEditPosicionIVA->Text == "Responsable monotributo")
        {
                BD->TableFacturaTradicional->FieldValues["Tipo_cbte"] = 1;
        }
        else if (DBEditPosicionIVA->Text == "Otro")
        {
                BD->TableFacturaTradicional->FieldValues["Tipo_cbte"] = 6;
        }
        else throw;
        BD->TableFacturaTradicional->FieldValues["Cbte_nro"] = EditNumeroComprobante->Text.ToIntDef(0);
        BD->TableFacturaTradicional->Post();
}
//---------------------------------------------------------------------------

void TFormFacturacion::AgregarComprobanteAsociado(FE &fe)
{
        int tipo_cbte_asoc;
        int cbte_nro_asoc;

        // el tipo siempre es una factura
        if (DBEditPosicionIVA->Text == "Responsable inscripto" ||
            DBEditPosicionIVA->Text == "Responsable monotributo")
        {
                fe.tipo_cbte_asoc = 1;
        }
        else if (DBEditPosicionIVA->Text == "Otro")
        {
                fe.tipo_cbte_asoc = 6;
        }

        fe.cbte_nro_asoc = EditNumeroComprobanteAsociado->Text.ToIntDef(0);
}
//---------------------------------------------------------------------------

