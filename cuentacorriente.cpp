//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "cuentacorriente.h"
#include "basedatos.h"
#include "configuracion.h"
#include "seleccionarcliente.h"
#include "registrodocumentos.h"
#include "auxiliar.h"
#include "impresion.h"
#include "facturacion.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormCuentaCorriente *FormCuentaCorriente;
//---------------------------------------------------------------------------
__fastcall TFormCuentaCorriente::TFormCuentaCorriente(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TFormCuentaCorriente::Mostrar(int numerocliente)
{
        /* Localizo el cliente en la tabla */
        BuscarClave(BD->TableClientes, "NumeroCliente", Variant(numerocliente));

        /* Muestro la ventana */
        ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::DBGridColExit(TObject *Sender)
{
        /* Si se cambia de columna se envía un post */
        if (BD->TableCuentasCorrientes->State == dsEdit)
        {
                BD->TableCuentasCorrientes->Post();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::DBGridExit(TObject *Sender)
{
        /* Si se sale de la grilla se envía un post */
        if (BD->TableCuentasCorrientes->State == dsEdit)
        {
                BD->TableCuentasCorrientes->Post();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::DBGridKeyPress(TObject *Sender,
      char &Key)
{
        /* Impide que se escriba cuando esta vacía */
        if (BD->TableCuentasCorrientes->IsEmpty())
        {
                Abort();
        }
        /* Si se presiona enter se envía un post */
        if (BD->TableCuentasCorrientes->State == dsEdit && Key == VK_RETURN)
        {
                BD->TableCuentasCorrientes->Post();
                if (! DBGrid->EditorMode) Abort(); /* Cancela el enter */
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        /* Si se cierra el form se envía un post */
        if (BD->TableCuentasCorrientes->State == dsEdit)
        {
                BD->TableCuentasCorrientes->Post();
        }
}
//---------------------------------------------------------------------------

bool TFormCuentaCorriente::HayRegistros()
{
        return ! BD->TableCuentasCorrientes->IsEmpty();
}
//---------------------------------------------------------------------------

void TFormCuentaCorriente::AgregarRegistro(AnsiString fecha, AnsiString hora,
                                           double debe, double haber, int tipodocumento,
                                           double numerodocumento)
{
        int numeroregistro, numerocliente;

        numerocliente = BD->TableClientes->FieldValues["NumeroCliente"];
        numeroregistro = BD->TableClientes->FieldValues["NumeroRegistrosCC"];
        numeroregistro++;

        BD->TableClientes->Edit();
        BD->TableClientes->FieldValues["NumeroRegistrosCC"] = numeroregistro;
        BD->TableClientes->Post();

        BD->TableCuentasCorrientes->Append();
        BD->TableCuentasCorrientes->FieldValues["NumeroCliente"] = numerocliente;
        BD->TableCuentasCorrientes->FieldValues["NumeroRegistro"] = numeroregistro;
        BD->TableCuentasCorrientes->FieldValues["Fecha"] = StrToDate(fecha);
        BD->TableCuentasCorrientes->FieldValues["Hora"] = StrToTime(hora);
        BD->TableCuentasCorrientes->FieldValues["Debe"] = debe;
        BD->TableCuentasCorrientes->FieldValues["Haber"] = haber;
        BD->TableCuentasCorrientes->FieldValues["SaldoParcial"] = 0;
        BD->TableCuentasCorrientes->FieldValues["TipoDocumento"] = tipodocumento;
        BD->TableCuentasCorrientes->FieldValues["NumeroDocumento"] = numerodocumento;
        BD->TableCuentasCorrientes->Post();

        //Reducir(FormConfiguracion->ConservarRegistrosCC());
        BD->TableCuentasCorrientes->Last();
}
//---------------------------------------------------------------------------

bool TFormCuentaCorriente::ConfirmarEliminacion()
{
        int numeroregistro = BD->TableCuentasCorrientes
                               ->FieldByName("NumeroRegistro")->AsInteger;
        AnsiString mensaje = "Se eliminará el registro número " +
                             IntToStr(numeroregistro) +
                             ". ¿Realmente desea hacerlo?";
        int valor = MessageBox(Handle, mensaje.c_str(),
                               Application->Title.c_str(), MB_APPLMODAL |
                               MB_YESNO | MB_ICONQUESTION);
        return (valor == IDYES? true: false);
}
//---------------------------------------------------------------------------

void TFormCuentaCorriente::EliminarRegistro()
{
        BD->TableCuentasCorrientes->Delete();
        ActualizarSaldos();
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::MenuItemCambiarClienteClick(TObject *Sender)
{
        int numerocliente = FormSeleccionarCliente->Mostrar(
                                            DBEditNumeroCliente->Text.ToInt());
        if (numerocliente > 0)
        {
                /* Localizo el cliente en la tabla */
                BuscarClave(BD->TableClientes, "NumeroCliente", Variant(numerocliente));
                ActualizarSaldoTotal(); // Se posiciona al final //
                ActualizarCantidadRegistros();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::MenuItemCerrarClick(
      TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::MenuItemAgregarClick(TObject *Sender)
{
        AgregarRegistro(Date(), Time(), 0, 0, -1, -1);
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::MenuItemEliminarClick(
      TObject *Sender)
{
        if (HayRegistros() && ConfirmarEliminacion())
        {
                int tipodocumento = BD->TableCuentasCorrientes->FieldValues["TipoDocumento"];
                int numerodocumento = BD->TableCuentasCorrientes->FieldValues["NumeroDocumento"];

                if (tipodocumento < 0)
                {
                        EliminarRegistro();
                }
                else
                {
                        FormRegistroDocumentos->AnularDocumento(tipodocumento, numerodocumento);
                }
        }
}
//---------------------------------------------------------------------------

void TFormCuentaCorriente::ActualizarSaldoParcial()
{
        double saldoparcial;

        BD->TableCuentasCorrientes->Prior(); // Se mueve al anterior //
        if (BD->TableCuentasCorrientes->Bof) // Si no había anterior //
        {
                saldoparcial = 0;
        }
        else
        {
                saldoparcial = BD->TableCuentasCorrientes
                                 ->FieldByName("SaldoParcial")->AsFloat;
                BD->TableCuentasCorrientes->Next();
        }

        /* Se desactiva el AfterPost porque se provocan Posts */
        BD->ActivarTableCuentasCorrientesAfterPost(false);
        /* Se desactiva el BeforeEdit para poder editar sin problemas */
        BD->ActivarTableCuentasCorrientesBeforeEdit(false);

        do {
                BD->TableCuentasCorrientes->Edit();
                saldoparcial += BD->TableCuentasCorrientes->FieldByName("Debe")
                                                          ->AsFloat
                              - BD->TableCuentasCorrientes->FieldByName("Haber")
                                                          ->AsFloat;
                BD->TableCuentasCorrientes->FieldValues["SaldoParcial"] = saldoparcial;
                BD->TableCuentasCorrientes->Post();
                BD->TableCuentasCorrientes->Next();
        } while (! BD->TableCuentasCorrientes->Eof);

        BD->ActivarTableCuentasCorrientesBeforeEdit(true);
        BD->ActivarTableCuentasCorrientesAfterPost(true);
}
//---------------------------------------------------------------------------

void TFormCuentaCorriente::ActualizarSaldoTotal()
{
        /* Insisto en la separacion visual y la de los datos */
        BD->TableClientes->Edit();
        if (BD->TableCuentasCorrientes->IsEmpty())
        {
                if (FormCuentaCorriente->Visible == true)
                {
                        StaticTextSaldo->Caption = "";
                }
                BD->TableClientes->FieldValues["SaldoCC"] = 0;
        }
        else
        {
                BD->TableCuentasCorrientes->Last();
                double saldo = BD->TableCuentasCorrientes
                                 ->FieldByName("SaldoParcial")->AsFloat;
                if (FormCuentaCorriente->Visible == true)
                {
                        StaticTextSaldo->Caption = "$ " + FormatFloat("0.00", saldo);
                        if (saldo < -0.001)
                        {
                                DBGrid->Font->Color = clRed;
                                StaticTextSaldo->Font->Color = clRed;
                        }
                        else
                        {
                                DBGrid->Font->Color = clBlack;
                                StaticTextSaldo->Font->Color = clBlack;
                        }
                }
                BD->TableClientes->FieldValues["SaldoCC"] = saldo;
        }
        BD->TableClientes->Post();
}
//---------------------------------------------------------------------------
void TFormCuentaCorriente::ActualizarSaldos()
{
        /* Guardamos la posicion en la tabla */
        TBookmark posicion = BD->TableCuentasCorrientes->GetBookmark();

        BD->TableCuentasCorrientes->DisableControls();

        if (! BD->TableCuentasCorrientes->IsEmpty())
        {
                ActualizarSaldoParcial();
        }
        ActualizarSaldoTotal();

        BD->TableCuentasCorrientes->EnableControls();

        /* Restauramos la posición */
        BD->TableCuentasCorrientes->GotoBookmark(posicion);
        BD->TableCuentasCorrientes->FreeBookmark(posicion);
}
//---------------------------------------------------------------------------

void TFormCuentaCorriente::ActualizarCantidadRegistros()
{
        LabelCantidadRegistros->Caption = BD->TableCuentasCorrientes->RecordCount;
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::FormShow(TObject *Sender)
{
        ActualizarSaldoTotal(); // Se posiciona al final //
        ActualizarCantidadRegistros();
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::Button1Click(TObject *Sender)
{
        for (int c = 0; c < 1000; c++)
        {
                AgregarRegistro(Date(), Time(), 0, 0, -1, -1);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::DBGridKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
        // Anulo los atajos por defecto para agregar y eliminar filas
        if ((Shift.Contains(ssCtrl) && Key == VK_DELETE) || Key == VK_INSERT)
        {
                Abort();
        }
        if (Key == VK_DOWN && BD->TableCuentasCorrientes->RecNo >=
            BD->TableCuentasCorrientes->RecordCount)
        {
                Abort();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::MenuItemMostrarClick(TObject *Sender)
{
        if (HayRegistros())
        {
                int tipodocumento = BD->TableCuentasCorrientes->FieldValues["TipoDocumento"];
                int numerodocumento = BD->TableCuentasCorrientes->FieldValues["NumeroDocumento"];
                FormRegistroDocumentos->MostrarDocumento(tipodocumento, numerodocumento);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::MenuItemRegistroClick(
      TObject *Sender)
{
        if (BD->TableCuentasCorrientes->IsEmpty()) return;

        int tipodocumento = BD->TableCuentasCorrientes->FieldByName("TipoDocumento")->AsInteger;

        if (tipodocumento < 0)
        {
                MenuItemMostrar->Enabled = false;
                MenuItemMostrar2->Enabled = false;
                MenuItemEliminar->Enabled = true;
                MenuItemEliminar2->Enabled = true;
        }
        else if (tipodocumento == DOC_FACTURAELECT ||
                 tipodocumento == DOC_CREDITOELECT ||
                 tipodocumento == DOC_DEBITOELECT)
        {
                MenuItemMostrar->Enabled = true;
                MenuItemMostrar2->Enabled = true;
                MenuItemEliminar->Enabled = false;
                MenuItemEliminar2->Enabled = false;
        }
        else
        {
                MenuItemEliminar->Enabled = true;
                MenuItemEliminar2->Enabled = true;
                MenuItemMostrar->Enabled = true;
                MenuItemMostrar2->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void TFormCuentaCorriente::Imprimir(bool vistaprevia)
{
        BD->TableCuentasCorrientes->DisableControls();
        TBookmark bookmark = BD->TableCuentasCorrientes->GetBookmark();
        BD->TableCuentasCorrientes->Last();
        for (int c = 0; c < FormConfiguracion->CantidadImprimirCC() - 1; c++)
        {
                BD->TableCuentasCorrientes->Prior();
        }
        int desde = BD->TableCuentasCorrientes->RecNo;
        BD->TableCuentasCorrientes->GotoBookmark(bookmark);
        BD->TableCuentasCorrientes->FreeBookmark(bookmark);
        BD->TableCuentasCorrientes->EnableControls();

        Impresion imp;
        imp.ImprimirCuentaCorriente(desde, vistaprevia);
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::MenuItemImprimirDesdeClick(
      TObject *Sender)
{
        if (BD->TableCuentasCorrientes->IsEmpty()) return;

        int desde = BD->TableCuentasCorrientes->RecNo;

        AnsiString mensaje = "Se va a imprimir desde el registro seleccionado "
                             "hasta el final. ¿Desea continuar?";

        int valor = MessageBox(Handle, mensaje.c_str(),
                               Application->Title.c_str(), MB_APPLMODAL |
                               MB_YESNO | MB_ICONQUESTION);
        if (valor == IDYES)
        {
                Impresion imp;
                imp.ImprimirCuentaCorriente(desde, false);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::MenuItemImprimirClick(
      TObject *Sender)
{
        if (BD->TableCuentasCorrientes->IsEmpty()) return;
        Imprimir(false);
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::ToolButtonCambiarClienteClick(TObject *Sender)
{
        MenuItemCambiarCliente->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::ToolButtonImprimirClick(
      TObject *Sender)
{
        MenuItemImprimir->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::MenuItemVisualizarClick(TObject *Sender)
{
        if (BD->TableCuentasCorrientes->IsEmpty()) return;
        Imprimir(true);
}
//---------------------------------------------------------------------------

void __fastcall TFormCuentaCorriente::MenuItemVisualizarDesdeClick(
      TObject *Sender)
{
        if (BD->TableCuentasCorrientes->IsEmpty()) return;

        int desde = BD->TableCuentasCorrientes->RecNo;

        AnsiString mensaje = "Se va a visualizar desde el registro seleccionado "
                             "hasta el final. ¿Desea continuar?";

        int valor = MessageBox(Handle, mensaje.c_str(),
                               Application->Title.c_str(), MB_APPLMODAL |
                               MB_YESNO | MB_ICONQUESTION);
        if (valor == IDYES)
        {
                Impresion imp;
                imp.ImprimirCuentaCorriente(desde, true);
        }

}
//---------------------------------------------------------------------------

