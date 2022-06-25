//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "dialogocliente.h"
#include "basedatos.h"
#include "itemsclientes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormDialogoCliente *FormDialogoCliente;
static AnsiString Dialogos[DLG_CTE_N] = {"Agregar cliente", "Editar cliente"};

//---------------------------------------------------------------------------
__fastcall TFormDialogoCliente::TFormDialogoCliente(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

TModalResult TFormDialogoCliente::Mostrar(int tipo)
{
        Caption = Dialogos[tipo];
        return ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormDialogoCliente::BitBtnAceptarClick(TObject *Sender)
{
        /* Se verifica que estén los datos obligatorios */
        if (DBEditNombreCliente->Text.IsEmpty())
        {
                MessageBox(Handle, "Debe especificar un nombre para el "
                           "cliente.", Application->Title.c_str(),
                           MB_APPLMODAL | MB_OK | MB_ICONINFORMATION);
                return;
        }
        if (DBComboBoxNombreFactura->Text.IsEmpty())
        {
                MessageBox(Handle, "Debe especificar un nombre para "
                           "hacer la facturación.", Application->Title.c_str(),
                           MB_APPLMODAL | MB_OK | MB_ICONINFORMATION);
                return;
        }
        if (DBComboBoxPosicionIVA->Text.IsEmpty())
        {
                MessageBox(Handle, "Debe especificar una posición ante el IVA.",
                           Application->Title.c_str(), MB_APPLMODAL |
                           MB_OK | MB_ICONINFORMATION);
                return;
        }
        if (DBEditDescuento->Text.IsEmpty())
        {
                MessageBox(Handle, "Debe especificar un descuento para el "
                           "cliente.",
                           Application->Title.c_str(), MB_APPLMODAL |
                           MB_OK | MB_ICONINFORMATION);
                return;
        }
        
        /* Se verifican que los datos sean correctos */
        try
        {
                double descuento = DBEditDescuento->Text.ToDouble();
                if (descuento < 0 || descuento > 100) throw EConvertError("");
        }
        catch (EConvertError &converterror)
        {
                MessageBox(Handle,
                           "El valor ingresado para Descuento no es válido.",
                           Application->Title.c_str(),
                           MB_APPLMODAL | MB_OK | MB_ICONWARNING);
                return;
        }

        /* Si es un nuevo cliente o se está editando uno, entonces se envían
           los datos */
        /* El post lo hacemos acá porque cuando se cierra el dialogo se
           sale del modo insert */
        if (BD->TableClientes->State == dsInsert ||
            BD->TableClientes->State == dsEdit)
        {
                BD->TableClientes->Post();
        }

        ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TFormDialogoCliente::BitBtnCancelarClick(TObject *Sender)
{
        ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TFormDialogoCliente::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        /* Se cancelan las modificaciones del registro actual no enviadas */
        BD->TableClientes->Cancel();
}
//---------------------------------------------------------------------------

void __fastcall TFormDialogoCliente::FormShow(TObject *Sender)
{
        ActualizarNombresFactura();
        PageControl->ActivePageIndex = 0;
        DBEditNombreCliente->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFormDialogoCliente::BitBtnLocalidadesClick(
      TObject *Sender)
{
        TBitBtn *boton = static_cast< TBitBtn * >(Sender);
        FormItemsClientes->Mostrar(boton->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TFormDialogoCliente::DBEditDescuentoKeyPress(
      TObject *Sender, char &Key)
{
        if (Key == '+' || Key == '-')
                Abort();
        if (Key == '.')
                if (DBEditDescuento->Text.AnsiPos(".") &&
                    ! DBEditDescuento->SelText.AnsiPos(".")) Abort();
}
//---------------------------------------------------------------------------

void __fastcall TFormDialogoCliente::DBEditNombreNegocioExit(
      TObject *Sender)
{
        ActualizarNombresFactura();
}
//---------------------------------------------------------------------------

void __fastcall TFormDialogoCliente::DBEditNombreClienteExit(
      TObject *Sender)
{
        ActualizarNombresFactura();
}
//---------------------------------------------------------------------------

void TFormDialogoCliente::ActualizarNombresFactura()
{
        AnsiString nombrefactura = BD->TableClientes->FieldByName("NombreFactura")->AsString;
        DBComboBoxNombreFactura->Items->Clear();
        DBComboBoxNombreFactura->Items->Add(DBEditNombreCliente->Text);
        DBComboBoxNombreFactura->Items->Add(DBEditNombreNegocio->Text);
        if (DBComboBoxNombreFactura->Items->Strings[0] == nombrefactura)
        {
                DBComboBoxNombreFactura->ItemIndex = 0;
        }
        else if (DBComboBoxNombreFactura->Items->Strings[1] == nombrefactura)
        {
                DBComboBoxNombreFactura->ItemIndex = 1;
        }
}
//---------------------------------------------------------------------------


