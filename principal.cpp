//---------------------------------------------------------------------------

#include <vcl.h>
#include <io.h>
#pragma hdrstop
#include <fstream>
#include <map>

#include "principal.h"
#include "archivoclientes.h"
#include "archivoproductos.h"
#include "configuracion.h"
#include "seleccionarcliente.h"
#include "seleccionarproducto.h"
#include "registrodocumentos.h"
#include "cuentacorriente.h"
#include "facturacion.h"
#include "saldos.h"
#include "buscarclientes.h"
#include "buscarproductos.h"
#include "itemsclientes.h"
#include "itemsproductos.h"
#include "registroventasdiario.h"
#include "registroventasmensual.h"
#include "registroventasanual.h"
#include "basedatos.h"
#include "auxiliar.h"
#include "mensaje.h"
#include "impresion.h"
#include "identificacion.h"
#include "registroproductosdiario.h"
#include "registroproductosmensual.h"
#include "registroproductosanual.h"
#include "numeracion.h"
#include "dialogoproducto.h"
#include "registroproductosstock.h"
#include "AFIP.h"
#include "registrokilogramosmensual.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPrincipal *FormPrincipal;
AFIP *afip;

//---------------------------------------------------------------------------
__fastcall TFormPrincipal::TFormPrincipal(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TFormPrincipal::MenuItemConfiguracionClick(TObject *Sender)
{
        FormConfiguracion->Mostrar();
}
//---------------------------------------------------------------------------


void __fastcall TFormPrincipal::MenuItemCuentasCorrientesClick(
      TObject *Sender)
{
        int numerocliente = FormSeleccionarCliente->Mostrar(0);
        if (numerocliente > 0)
        {
                FormCuentaCorriente->Mostrar(numerocliente);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemRemitoClick(TObject *Sender)
{
        int numerocliente = FormSeleccionarCliente->Mostrar(0);
        if (numerocliente > 0)
        {
                FormFacturacion->NuevoDocumento(numerocliente, DOC_REMITO);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemDocumentosClick(TObject *Sender)
{
        FormRegistroDocumentos->Mostrar();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemSaldosClick(TObject *Sender)
{
        FormSaldos->Mostrar();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ApplicationEventsMessage(tagMSG &Msg,
      bool &Handled)
{
        //if (Msg.message == WM_SHOWWINDOW) ShowMessage("hola");

        if (Msg.message == WM_MOUSEWHEEL &&
            (FormArchivoClientes->DBGrid->Focused() ||
             FormArchivoProductos->DBGrid->Focused() ||
             FormCuentaCorriente->DBGrid->Focused() ||
             FormRegistroDocumentos->DBGrid->Focused() ||
             FormBuscarClientes->DBGrid->Focused() ||
             FormBuscarProductos->DBGrid->Focused() ||
             FormSeleccionarCliente->DBGrid->Focused() ||
             FormSeleccionarProducto->DBGrid->Focused() ||
             FormItemsClientes->DBGridLocalidades->Focused() ||
             FormItemsClientes->DBGridProvincias->Focused() ||
             FormItemsClientes->DBGridTiposNegocios->Focused() ||
             FormItemsProductos->DBGridFamilias->Focused() ||
             FormItemsProductos->DBGridUnidades->Focused() ||
             FormSaldos->DBGrid->Focused() ||
             FormRegistroVentasDiario->DBGrid->Focused() ||
             FormRegistroVentasMensual->DBGrid->Focused() ||
             FormRegistroVentasAnual->DBGrid->Focused() ||
             FormRegistroProductosDiario->DBGrid->Focused() ||
             FormRegistroProductosMensual->DBGrid->Focused() ||
             FormRegistroProductosAnual->DBGrid->Focused() ||
             FormRegistroProductosStock->DBGrid->Focused() ||
             FormRegistroKilogramosMensual->DBGrid->Focused()))
        {
                Msg.message = WM_KEYDOWN;
                Msg.lParam = 0;
                int i = Msg.wParam;
                if (i > 0)
                {
                        Msg.wParam = VK_UP;
                }
                else
                {
                        Msg.wParam = VK_DOWN;
                }
                
                Handled = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemVentasDiarioClick(TObject *Sender)
{
        FormRegistroVentasDiario->Mostrar();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemVentasMensualClick(TObject *Sender)
{
        FormRegistroVentasMensual->Mostrar();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemVentasAnualClick(TObject *Sender)
{
        FormRegistroVentasAnual->Mostrar();
}
//---------------------------------------------------------------------------

void TFormPrincipal::Cerrar()
{
        // Guardo siempre saldos (no es una opción :-))
        bool res = BD->GuardarSaldos();
        if (! res)
        {
                MessageBox(Handle, "El directorio configurado para crear el "
                                   "listado de saldos no existe o no se tiene "
                                   "acceso al mismo.", Application->Title.c_str(),
                                   MB_APPLMODAL | MB_OK | MB_ICONERROR);
        }

        FormConfiguracion->GuardarEstadoVentanas();

        BD->ActivarBaseDatos(false);

        if (FormConfiguracion->CopiaSalir())
        {
                HacerCopiaSeguridad();
        }

        int cantidad = FormConfiguracion->EjecucionesSinCompactar();
        cantidad++;
        FormConfiguracion->EjecucionesSinCompactar(cantidad);
        if (cantidad >= FormConfiguracion->EjecucionesCompactar())
        {
                HacerCompactacion();
                FormConfiguracion->EjecucionesSinCompactar(0);
        }
}
//---------------------------------------------------------------------------

void TFormPrincipal::HacerCopiaSeguridad()
{
        Mensaje mensaje("Haciendo copia de seguridad. Espere.");
        mensaje.Mostrar();
        AnsiString nombre = FechaHoraBackup();
        bool res = BD->CopiaSeguridad(FormConfiguracion->CopiaDirectorio(), nombre);
        mensaje.Cerrar();
        if (! res)
        {
                MessageBox(Handle, "El directorio configurado para hacer la "
                                   "copia de seguridad no existe o no se tiene "
                                   "acceso al mismo.", Application->Title.c_str(),
                                   MB_APPLMODAL | MB_OK | MB_ICONERROR);
        }
}
//---------------------------------------------------------------------------

void TFormPrincipal::HacerCompactacion()
{
        Mensaje mensaje("Compactando la base de datos. Espere.");
        mensaje.Mostrar();
        BD->Compactar();
        mensaje.Cerrar();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemCopiaSeguridadClick(
      TObject *Sender)
{
        BD->ActivarBaseDatos(false);
        HacerCopiaSeguridad();
        BD->ActivarBaseDatos(true);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::FormCreate(TObject *Sender)
{
        Inicializar();
        Caption = Application->Title.c_str();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ToolButtonRemitoClick(TObject *Sender)
{
        MenuItemRemito->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ToolButtonFacturaElectronicaClick(
      TObject *Sender)
{
        MenuItemFacturaElectronica->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ToolButtonCuentasCorrientesClick(
      TObject *Sender)
{
        MenuItemCuentasCorrientes->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ToolButtonSaldosClick(TObject *Sender)
{
        MenuItemSaldos->Click();        
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ToolButtonRegistroDocumentosClick(
      TObject *Sender)
{
        MenuItemDocumentos->Click();        
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ToolButtonRegistroVentasDiarioClick(
      TObject *Sender)
{
        MenuItemVentasDiario->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::FormShow(TObject *Sender)
{
        if (FormIdentificacion->Mostrar() != mrOk)
        {
                Application->Terminate();
        }
        FormConfiguracion->CargarEstadoVentanas();

        // AFIP
        AnsiString fichcert = GetCurrentDir() + "\\" + FormConfiguracion->Certificado();
        AnsiString fichclave = GetCurrentDir() + "\\" + FormConfiguracion->ClavePrivada();

        try
        {
                if (access(fichcert.c_str(), 04) != 0)
                {
                        throw "No se encontró el fichero de certificado \"" +
                              fichcert + "\"";
                }
                if (access(fichclave.c_str(), 04) != 0)
                {
                        throw "No se encontró el fichero de clave privada \"" +
                              fichclave + "\"";
                }
                try
                {
                        afip = new AFIP(fichcert, fichclave);
                }
                catch(EAFIP &e)
                {
                        throw e.Message;
                }
        }
        catch(AnsiString &error)
        {
                MessageBox(Handle, (error + ". El programa se cerrará.").c_str(),
                           Application->Title.c_str(), MB_APPLMODAL | MB_OK | MB_ICONERROR);
                Application->Terminate();
                Abort();
        }

        afip->cuit = FormConfiguracion->CUIT();
        afip->punto_vta = FormConfiguracion->PuntoVenta();
}
//---------------------------------------------------------------------------

void TFormPrincipal::Inicializar()
{
        if (! CrearLockFile()) // Tambien retorna false si no tiene permisos para crear el fichero
        {
                Application->Terminate();
        }

        /* Seteo el alias y activo la base de datos */
        if (! BD->SetearAlias("Ventas2012_BD"))
        {
                MessageBox(Handle, "No se puede configurar el alias para la "
                                   "base de datos. Puede ser que no "
                                   "tenga los permisos suficientes. El programa "
                                   "se cerrará.", Application->Title.c_str(),
                                   MB_APPLMODAL | MB_OK | MB_ICONERROR);
                Application->Terminate();
        }
        if (! BD->ActivarBaseDatos(true))
        {
                MessageBox(Handle, "No se puede activar la conexión con la "
                                   "base de datos. Puede ser que falten "
                                   "ficheros, estén corruptos o no se tenga "
                                   "acceso a los mismos. El programa se "
                                   "cerrará.", Application->Title.c_str(),
                                   MB_APPLMODAL | MB_OK | MB_ICONERROR);
                Application->Terminate();
        }

        if (access("plantillas\\factura_a.bmp", 04) != 0 ||
            access("plantillas\\factura_b.bmp", 04) != 0 ||
            access("plantillas\\factura.csv", 04) != 0 ||
            access("plantillas\\logo.png", 04) != 0)
        {
                MessageBox(Handle, "No se puede iniciar el programa debido "
                                   "a que no se pudieron encontrar uno o más "
                                   "ficheros necesarios. El programa se "
                                   "cerrará.", Application->Title.c_str(),
                                   MB_APPLMODAL | MB_OK | MB_ICONERROR);
                Application->Terminate();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemProductosDiarioClick(TObject *Sender)
{
        FormRegistroProductosDiario->Mostrar();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemProductosMensualClick(TObject *Sender)
{
        FormRegistroProductosMensual->Mostrar();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemProductosAnualClick(TObject *Sender)
{
        FormRegistroProductosAnual->Mostrar();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemCreditoRemitoClick(TObject *Sender)
{
        int numerocliente = FormSeleccionarCliente->Mostrar(0);
        if (numerocliente > 0)
        {
                FormFacturacion->NuevoDocumento(numerocliente, DOC_CREDITOREMITO);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemCreditoTradicionalClick(
      TObject *Sender)
{
        int numerocliente = FormSeleccionarCliente->Mostrar(0);
        if (numerocliente > 0)
        {
                FormFacturacion->NuevoDocumento(numerocliente, DOC_CREDITOFACTURA);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemFacturaTradicionalClick(
      TObject *Sender)
{
        int numerocliente = FormSeleccionarCliente->Mostrar(0);
        if (numerocliente > 0)
        {
                FormFacturacion->NuevoDocumento(numerocliente, DOC_FACTURA);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemStockClick(TObject *Sender)
{
        FormRegistroProductosStock->Mostrar();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
        Cerrar();
        CanClose = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemFacturaElectronicaClick(
      TObject *Sender)
{
        int numerocliente = FormSeleccionarCliente->Mostrar(0);
        if (numerocliente > 0)
        {
                FormFacturacion->NuevoDocumento(numerocliente, DOC_FACTURAELECT);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemCreditoElectronicaClick(
      TObject *Sender)
{
        int numerocliente = FormSeleccionarCliente->Mostrar(0);
        if (numerocliente > 0)
        {
                FormFacturacion->NuevoDocumento(numerocliente, DOC_CREDITOELECT);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemDebitoElectronicaClick(
      TObject *Sender)
{
        int numerocliente = FormSeleccionarCliente->Mostrar(0);
        if (numerocliente > 0)
        {
                FormFacturacion->NuevoDocumento(numerocliente, DOC_DEBITOELECT);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemGramosMensualClick(TObject *Sender)
{
        FormRegistroKilogramosMensual->Mostrar();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ToolButtonPedidoClick(TObject *Sender)
{
        MenuItemPedido->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemPedidoClick(TObject *Sender)
{
        int numerocliente = FormSeleccionarCliente->Mostrar(0);
        if (numerocliente > 0)
        {
                FormFacturacion->NuevoDocumento(numerocliente, DOC_PEDIDO);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemClientesClick(TObject *Sender)
{
        FormArchivoClientes->Mostrar();        
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuItemProductosClick(TObject *Sender)
{
        FormArchivoProductos->Mostrar();
}
//---------------------------------------------------------------------------

