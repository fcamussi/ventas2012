//---------------------------------------------------------------------------

#include <vcl.h>
#include <FileCtrl.hpp>
#pragma hdrstop

#include "configuracion.h"
#include "archivoclientes.h"
#include "archivoproductos.h"
#include "registrodocumentos.h"
#include "cuentacorriente.h"
#include "facturacion.h"
#include "saldos.h"
#include "registroventasdiario.h"
#include "registroventasmensual.h"
#include "registroventasanual.h"
#include "itemsclientes.h"
#include "itemsproductos.h"
#include "principal.h"
#include "impresion.h"
#include "registroproductosdiario.h"
#include "registroproductosmensual.h"
#include "registroproductosanual.h"
#include "registroproductosstock.h"
#include "registrokilogramosmensual.h"
#include "basedatos.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormConfiguracion *FormConfiguracion;
TIniFile *fichero;
AnsiString Impresiones[IMP_N] = {"Remito",
                                 "Factura",
                                 "Cuenta corriente",
                                 "Saldos",
                                 "Productos",
                                 "Registros",
                                 "Pedido"};
//---------------------------------------------------------------------------
__fastcall TFormConfiguracion::TFormConfiguracion(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TFormConfiguracion::Mostrar()
{
        ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormConfiguracion::BitBtnAceptarClick(TObject *Sender)
{
        int cantidadimprimirCC = EditCantidadImprimirCC->Text.ToIntDef(-1);
        if (cantidadimprimirCC < 2)
        {
                MessageBox(Handle, "El valor ingresado para Cantidad registros "
                                   "a imprimir en Cuentas corrientes debe ser "
                                   "un número entero mayor a 1.",
                           Application->Title.c_str(), MB_APPLMODAL |
                           MB_OK | MB_ICONEXCLAMATION);
                return;
        }

        int espaciosposteriorRO = EditEspaciosPosteriorRO->Text.ToIntDef(-1);
        if (espaciosposteriorRO < 0 || espaciosposteriorRO > 100)
        {
                MessageBox(Handle, "El valor ingresado para Posterior remito "
                                   "original en Impresion Espacios debe ser "
                                   "un número entero entre 0 y 100.",
                           Application->Title.c_str(), MB_APPLMODAL |
                           MB_OK | MB_ICONEXCLAMATION);
                return;
        }

        int espaciosposteriorRD = EditEspaciosPosteriorRD->Text.ToIntDef(-1);
        if (espaciosposteriorRD < 0 || espaciosposteriorRD > 100)
        {
                MessageBox(Handle, "El valor ingresado para Posterior remito "
                                   "duplicado en Impresion Espacios debe ser "
                                   "un número entero entre 0 y 100.",
                           Application->Title.c_str(), MB_APPLMODAL |
                           MB_OK | MB_ICONEXCLAMATION);
                return;
        }

        int espaciosposteriorFO = EditEspaciosPosteriorFO->Text.ToIntDef(-1);
        if (espaciosposteriorFO < 0 || espaciosposteriorFO > 100)
        {
                MessageBox(Handle, "El valor ingresado para Posterior factura "
                                   "original en Impresion Espacios debe ser "
                                   "un número entero entre 0 y 100.",
                           Application->Title.c_str(), MB_APPLMODAL |
                           MB_OK | MB_ICONEXCLAMATION);
                return;
        }

        int espaciosposteriorFD = EditEspaciosPosteriorFD->Text.ToIntDef(-1);
        if (espaciosposteriorFD < 0 || espaciosposteriorFD > 100)
        {
                MessageBox(Handle, "El valor ingresado para Posterior factura "
                                   "duplicado en Impresion Espacios debe ser "
                                   "un número entero entre 0 y 100.",
                           Application->Title.c_str(), MB_APPLMODAL |
                           MB_OK | MB_ICONEXCLAMATION);
                return;
        }

        int espaciosposteriorCC = EditEspaciosPosteriorCC->Text.ToIntDef(-1);
        if (espaciosposteriorCC < 0 || espaciosposteriorCC > 100)
        {
                MessageBox(Handle, "El valor ingresado para Posterior cuenta "
                                   "corriente en Impresion Espacios debe ser "
                                   "un número entero entre 0 y 100.",
                           Application->Title.c_str(), MB_APPLMODAL |
                           MB_OK | MB_ICONEXCLAMATION);
                return;
        }

        int espaciosposteriorpedido = EditEspaciosPosteriorPedido->Text.ToIntDef(-1);
        if (espaciosposteriorpedido < 0 || espaciosposteriorpedido > 100)
        {
                MessageBox(Handle, "El valor ingresado para Posterior pedido "
                                   "en Impresion Espacios debe ser "
                                   "un número entero entre 0 y 100.",
                           Application->Title.c_str(), MB_APPLMODAL |
                           MB_OK | MB_ICONEXCLAMATION);
                return;
        }

        int ejecucionescompactar = EditEjecucionesCompactar->Text.ToIntDef(-1);
        if (ejecucionescompactar < 1)
        {
                MessageBox(Handle, "El valor ingresado para Ejecuciones "
                                   "compactar en Base de datos debe ser "
                                   "un número entero mayor a 0.",
                           Application->Title.c_str(), MB_APPLMODAL |
                           MB_OK | MB_ICONEXCLAMATION);
                return;
        }

        int backupsconservar = EditBackupsConservar->Text.ToIntDef(-1);
        if (backupsconservar < 1)
        {
                MessageBox(Handle, "El valor ingresado para Backups "
                                   "convervar en Copia de seguridad debe ser "
                                   "un número entero mayor a 0.",
                           Application->Title.c_str(), MB_APPLMODAL |
                           MB_OK | MB_ICONEXCLAMATION);
                return;
        }

        GuardarConfiguracion();
        ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TFormConfiguracion::BitBtnCancelarClick(TObject *Sender)
{
        ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TFormConfiguracion::ButtonItemsClientesClick(
      TObject *Sender)
{
        FormItemsClientes->Mostrar(0);
}
//---------------------------------------------------------------------------

void __fastcall TFormConfiguracion::ButtonItemsProductosClick(
      TObject *Sender)
{
        FormItemsProductos->Mostrar(0);
}
//---------------------------------------------------------------------------

double TFormConfiguracion::ValorIVA()
{
        double valor;
        valor = fichero->ReadFloat("AFIP", "Valor IVA", 21);
        return valor;
}
//---------------------------------------------------------------------------

int TFormConfiguracion::NumeroRenglones(int tipodocumento)
{
        AnsiString tipo = FormFacturacion->Documentos(tipodocumento);
        return fichero->ReadInteger("Facturacion", "Renglones " + tipo, 15);
}
//---------------------------------------------------------------------------

int TFormConfiguracion::CantidadImprimirCC()
{
        return fichero->ReadInteger("Cuentas Corrientes", "Cantidad imprimir", 20);
}
//---------------------------------------------------------------------------

AnsiString TFormConfiguracion::Comunicado()
{
        return fichero->ReadString("Facturacion", "Comunicado", "");
}
//---------------------------------------------------------------------------

void TFormConfiguracion::Comunicado(AnsiString texto)
{
        fichero->WriteString("Facturacion", "Comunicado", texto);
        fichero->UpdateFile();
}
//---------------------------------------------------------------------------

AnsiString TFormConfiguracion::CopiaDirectorio()
{
        return fichero->ReadString("Copia de seguridad", "Directorio", "C:\\");
}
//---------------------------------------------------------------------------

int TFormConfiguracion::BackupsConservar()
{
        return fichero->ReadInteger("Copia de seguridad", "Backups conservar", 5);
}
//---------------------------------------------------------------------------

bool TFormConfiguracion::CopiaSalir()
{
        return fichero->ReadBool("Copia de seguridad", "Salir", true);
}
//---------------------------------------------------------------------------

int TFormConfiguracion::EjecucionesCompactar()
{
        return fichero->ReadInteger("Compactar", "Ejecuciones", 50);
}
//---------------------------------------------------------------------------

AnsiString TFormConfiguracion::Impresora(int tipoimpresion)
{
        return fichero->ReadString("Impresoras", Impresiones[tipoimpresion], "");
}
//---------------------------------------------------------------------------

bool TFormConfiguracion::ModoRAW(int tipoimpresion)
{
        return fichero->ReadBool("Impresoras", "RAW " + Impresiones[tipoimpresion], false);
}
//---------------------------------------------------------------------------

int TFormConfiguracion::EspaciosPosteriorRO()
{
        return fichero->ReadInteger("Espacios", "Posterior RO", 5);
}
//---------------------------------------------------------------------------

int TFormConfiguracion::EspaciosPosteriorRD()
{
        return fichero->ReadInteger("Espacios", "Posterior RD", 5);
}
//---------------------------------------------------------------------------

int TFormConfiguracion::EspaciosPosteriorFO()
{
        return fichero->ReadInteger("Espacios", "Posterior FO", 4);
}
//---------------------------------------------------------------------------

int TFormConfiguracion::EspaciosPosteriorFD()
{
        return fichero->ReadInteger("Espacios", "Posterior FD", 4);
}
//---------------------------------------------------------------------------

int TFormConfiguracion::EspaciosPosteriorCC()
{
        return fichero->ReadInteger("Espacios", "Posterior CC", 4);
}
//---------------------------------------------------------------------------

int TFormConfiguracion::EspaciosPosteriorPedido()
{
        return fichero->ReadInteger("Espacios", "Posterior Pedido", 5);
}
//---------------------------------------------------------------------------

AnsiString TFormConfiguracion::ClaveIdentificacion()
{
        return fichero->ReadString("Identificacion", "Clave", "");
}
//---------------------------------------------------------------------------

bool TFormConfiguracion::ImprimirDuplicadoRemito()
{
        return fichero->ReadBool("Duplicado", "Duplicado remito", true);
}
//---------------------------------------------------------------------------

AnsiString TFormConfiguracion::CUIT()
{
        return fichero->ReadString("AFIP", "CUIT", "00-00000000-0");
}
//---------------------------------------------------------------------------

int TFormConfiguracion::PuntoVenta()
{
        return fichero->ReadInteger("AFIP", "Punto venta", 0);
}
//---------------------------------------------------------------------------

AnsiString TFormConfiguracion::Certificado()
{
        return fichero->ReadString("AFIP", "Certificado", "certificado.crt");
}
//---------------------------------------------------------------------------

AnsiString TFormConfiguracion::ClavePrivada()
{
        return fichero->ReadString("AFIP", "Clave privada", "claveprivada.key");
}
//---------------------------------------------------------------------------

void __fastcall TFormConfiguracion::FormDestroy(TObject *Sender)
{
        delete fichero;
}
//---------------------------------------------------------------------------

void TFormConfiguracion::CargarConfiguracion()
{
        EditCantidadImprimirCC->Text = CantidadImprimirCC();
        EditCopiaDirectorio->Text = CopiaDirectorio();
        EditBackupsConservar->Text = BackupsConservar();
        CheckBoxCopiaSalir->Checked = CopiaSalir();
        EditEjecucionesCompactar->Text = EjecucionesCompactar();
        ComboBoxImpresoraRemito->Text = Impresora(IMP_REMITO);
        ComboBoxImpresoraFactura->Text = Impresora(IMP_FACTURA);
        ComboBoxImpresoraCuentaCorriente->Text = Impresora(IMP_CUENTA);
        ComboBoxImpresoraSaldos->Text = Impresora(IMP_SALDOS);
        ComboBoxImpresoraProductos->Text = Impresora(IMP_PRODUCTOS);
        ComboBoxImpresoraRegistros->Text = Impresora(IMP_REGISTROS);
        ComboBoxImpresoraPedido->Text = Impresora(IMP_PEDIDO);
        CheckBoxRAWRemito->Checked = ModoRAW(IMP_REMITO);
        CheckBoxRAWFactura->Checked = ModoRAW(IMP_FACTURA);
        CheckBoxRAWCuentaCorriente->Checked = ModoRAW(IMP_CUENTA);
        CheckBoxRAWSaldos->Checked = ModoRAW(IMP_SALDOS);
        CheckBoxRAWProductos->Checked = ModoRAW(IMP_PRODUCTOS);
        CheckBoxRAWRegistros->Checked = ModoRAW(IMP_REGISTROS);
        CheckBoxRAWPedido->Checked = ModoRAW(IMP_PEDIDO);
        EditEspaciosPosteriorRO->Text = EspaciosPosteriorRO();
        EditEspaciosPosteriorRD->Text = EspaciosPosteriorRD();
        EditEspaciosPosteriorFO->Text = EspaciosPosteriorFO();
        EditEspaciosPosteriorFD->Text = EspaciosPosteriorFD();
        EditEspaciosPosteriorCC->Text = EspaciosPosteriorCC();
        EditEspaciosPosteriorPedido->Text = EspaciosPosteriorPedido();
        EditClaveIdentificacion->Text = ClaveIdentificacion();
        CheckBoxImprimirDuplicadoRemito->Checked = ImprimirDuplicadoRemito();
}
//---------------------------------------------------------------------------

void TFormConfiguracion::GuardarConfiguracion()
{
        fichero->WriteInteger("Cuentas corrientes", "Cantidad imprimir",
                              EditCantidadImprimirCC->Text.ToInt());
        fichero->WriteString("Copia de seguridad", "Directorio",
                              EditCopiaDirectorio->Text);
        fichero->WriteInteger("Copia de seguridad", "Backups conservar",
                              EditBackupsConservar->Text.ToInt());
        fichero->WriteBool("Copia de seguridad", "Salir",
                              CheckBoxCopiaSalir->Checked);
        fichero->WriteInteger("Compactar", "Ejecuciones",
                              EditEjecucionesCompactar->Text.ToInt());
        fichero->WriteString("Impresoras", "Remito",
                             ComboBoxImpresoraRemito->Text);
        fichero->WriteString("Impresoras", "Factura",
                             ComboBoxImpresoraFactura->Text);
        fichero->WriteString("Impresoras", "Cuenta corriente",
                             ComboBoxImpresoraCuentaCorriente->Text);
        fichero->WriteString("Impresoras", "Saldos",
                             ComboBoxImpresoraSaldos->Text);
        fichero->WriteString("Impresoras", "Productos",
                             ComboBoxImpresoraProductos->Text);
        fichero->WriteString("Impresoras", "Registros",
                             ComboBoxImpresoraRegistros->Text);
        fichero->WriteString("Impresoras", "Pedido",
                             ComboBoxImpresoraPedido->Text);
        fichero->WriteBool("Impresoras", "RAW Remito",
                           CheckBoxRAWRemito->Checked);
        fichero->WriteBool("Impresoras", "RAW Factura",
                           CheckBoxRAWFactura->Checked);
        fichero->WriteBool("Impresoras", "RAW Cuenta corriente",
                           CheckBoxRAWCuentaCorriente->Checked);
        fichero->WriteBool("Impresoras", "RAW Saldos",
                           CheckBoxRAWSaldos->Checked);
        fichero->WriteBool("Impresoras", "RAW Productos",
                           CheckBoxRAWProductos->Checked);
        fichero->WriteBool("Impresoras", "RAW Registros",
                           CheckBoxRAWRegistros->Checked);
        fichero->WriteBool("Impresoras", "RAW Pedido",
                           CheckBoxRAWPedido->Checked);
        fichero->WriteInteger("Espacios", "Posterior RO",
                              EditEspaciosPosteriorRO->Text.ToInt());
        fichero->WriteInteger("Espacios", "Posterior RD",
                              EditEspaciosPosteriorRD->Text.ToInt());
        fichero->WriteInteger("Espacios", "Posterior FO",
                              EditEspaciosPosteriorFO->Text.ToInt());
        fichero->WriteInteger("Espacios", "Posterior FD",
                              EditEspaciosPosteriorFD->Text.ToInt());
        fichero->WriteInteger("Espacios", "Posterior CC",
                              EditEspaciosPosteriorCC->Text.ToInt());
        fichero->WriteInteger("Espacios", "Posterior Pedido",
                              EditEspaciosPosteriorPedido->Text.ToInt());
        fichero->WriteString("Identificacion", "Clave",
                             EditClaveIdentificacion->Text);
        fichero->WriteBool("Duplicado", "Duplicado remito",
                           CheckBoxImprimirDuplicadoRemito->Checked);
        fichero->UpdateFile();
}
//---------------------------------------------------------------------------

void __fastcall TFormConfiguracion::FormShow(TObject *Sender)
{
        CargarConfiguracion();
        CargarImpresoras();
        PageControl->ActivePageIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFormConfiguracion::FormCreate(TObject *Sender)
{
        fichero = new TIniFile(FICHCONFIG);
}
//---------------------------------------------------------------------------

void __fastcall TFormConfiguracion::BitBtnDirectorioCopiaClick(TObject *Sender)
{
        AnsiString dir;
        // SelectDirectory does not change the value of the current directory.
        if (SelectDirectory("Seleccione la carpeta donde desea que se haga "
                            "la copia de seguridad.", "" , dir))
        {
                EditCopiaDirectorio->Text = dir;
        }
}
//---------------------------------------------------------------------------

void TFormConfiguracion::CargarImpresoras()
{
        TPrinter *impresora = new TPrinter;
        if (impresora->Printers->Count > 0)
        {
                FormConfiguracion->ComboBoxImpresoraRemito->Items->Assign(impresora->Printers);
                FormConfiguracion->ComboBoxImpresoraFactura->Items->Assign(impresora->Printers);
                FormConfiguracion->ComboBoxImpresoraCuentaCorriente->Items->Assign(impresora->Printers);
                FormConfiguracion->ComboBoxImpresoraSaldos->Items->Assign(impresora->Printers);
                FormConfiguracion->ComboBoxImpresoraProductos->Items->Assign(impresora->Printers);
                FormConfiguracion->ComboBoxImpresoraRegistros->Items->Assign(impresora->Printers);
                FormConfiguracion->ComboBoxImpresoraPedido->Items->Assign(impresora->Printers);
        }
}
//---------------------------------------------------------------------------

void TFormConfiguracion::EjecucionesSinCompactar(int cantidad)
{
        fichero->WriteInteger("Compactar", "Ejecuciones sin compactar", cantidad);
}
//---------------------------------------------------------------------------

int TFormConfiguracion::EjecucionesSinCompactar()
{
        return fichero->ReadInteger("Compactar", "Ejecuciones sin compactar", 0);
}
//---------------------------------------------------------------------------

void TFormConfiguracion::CargarEstadoVentanas()
{
        FormArchivoClientes->WindowState =
        (TWindowState)fichero->ReadInteger("Estado ventanas", "Archivo clientes", wsMaximized);
        FormArchivoProductos->WindowState =
        (TWindowState)fichero->ReadInteger("Estado ventanas", "Archivo productos", wsMaximized);
        FormCuentaCorriente->WindowState =
        (TWindowState)fichero->ReadInteger("Estado ventanas", "Cuenta corriente", wsMaximized);
        FormFacturacion->WindowState =
        (TWindowState)fichero->ReadInteger("Estado ventanas", "Facturacion", wsMaximized);
        FormPrincipal->WindowState =
        (TWindowState)fichero->ReadInteger("Estado ventanas", "Principal", wsMaximized);
        FormRegistroVentasAnual->WindowState =
        (TWindowState)fichero->ReadInteger("Estado ventanas", "Registro ventas anual", wsMaximized);
        FormRegistroDocumentos->WindowState =
        (TWindowState)fichero->ReadInteger("Estado ventanas", "Registro documentos", wsMaximized);
        FormRegistroVentasDiario->WindowState =
        (TWindowState)fichero->ReadInteger("Estado ventanas", "Registro ventas diario", wsMaximized);
        FormRegistroVentasMensual->WindowState =
        (TWindowState)fichero->ReadInteger("Estado ventanas", "Registro ventas mensual", wsMaximized);
        FormSaldos->WindowState =
        (TWindowState)fichero->ReadInteger("Estado ventanas", "Saldos", wsMaximized);
        FormImpresion->WindowState =
        (TWindowState)fichero->ReadInteger("Estado ventanas", "Impresion", wsNormal);
        FormRegistroProductosDiario->WindowState =
        (TWindowState)fichero->ReadInteger("Estado ventanas", "Registro productos diario", wsMaximized);
        FormRegistroProductosMensual->WindowState =
        (TWindowState)fichero->ReadInteger("Estado ventanas", "Registro productos mensual", wsMaximized);
        FormRegistroProductosAnual->WindowState =
        (TWindowState)fichero->ReadInteger("Estado ventanas", "Registro productos anual", wsMaximized);
        FormRegistroProductosStock->WindowState =
        (TWindowState)fichero->ReadInteger("Estado ventanas", "Registro productos stock", wsMaximized);
        FormRegistroKilogramosMensual->WindowState =
        (TWindowState)fichero->ReadInteger("Estado ventanas", "Registro kilogramos mensual", wsMaximized);
}
//---------------------------------------------------------------------------

void TFormConfiguracion::GuardarEstadoVentanas()
{
        fichero->WriteInteger("Estado ventanas", "Archivo clientes",
                              FormArchivoClientes->WindowState);
        fichero->WriteInteger("Estado ventanas", "Archivo productos",
                              FormArchivoProductos->WindowState);
        fichero->WriteInteger("Estado ventanas", "Cuenta corriente",
                              FormCuentaCorriente->WindowState);
        fichero->WriteInteger("Estado ventanas", "Facturacion",
                              FormFacturacion->WindowState);
        fichero->WriteInteger("Estado ventanas", "Principal",
                              FormPrincipal->WindowState);
        fichero->WriteInteger("Estado ventanas", "Registro ventas anual",
                              FormRegistroVentasAnual->WindowState);
        fichero->WriteInteger("Estado ventanas", "Registro documentos",
                              FormRegistroDocumentos->WindowState);
        fichero->WriteInteger("Estado ventanas", "Registro ventas diario",
                              FormRegistroVentasDiario->WindowState);
        fichero->WriteInteger("Estado ventanas", "Registro ventas mensual",
                              FormRegistroVentasMensual->WindowState);
        fichero->WriteInteger("Estado ventanas", "Impresion",
                              FormImpresion->WindowState);
        fichero->WriteInteger("Estado ventanas", "Registro productos diario",
                              FormRegistroProductosDiario->WindowState);
        fichero->WriteInteger("Estado ventanas", "Registro productos mensual",
                              FormRegistroProductosMensual->WindowState);
        fichero->WriteInteger("Estado ventanas", "Registro productos anual",
                              FormRegistroProductosAnual->WindowState);
        fichero->WriteInteger("Estado ventanas", "Registro productos stock",
                              FormRegistroProductosStock->WindowState);
        fichero->WriteInteger("Estado ventanas", "Registro kilogramos mensual",
                              FormRegistroKilogramosMensual->WindowState);
}
//---------------------------------------------------------------------------

void __fastcall TFormConfiguracion::ButtonPadronCacheClick(TObject *Sender)
{
        while (! BD->TablePadronAFIP->IsEmpty())
        {
                BD->TablePadronAFIP->Delete();
        }
}
//---------------------------------------------------------------------------

