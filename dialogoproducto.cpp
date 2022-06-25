//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "dialogoproducto.h"
#include "basedatos.h"
#include "itemsproductos.h"
#include "auxiliar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormDialogoProducto *FormDialogoProducto;
static AnsiString Dialogos[DLG_PTO_N] = {"Agregar producto", "Editar producto"};

//---------------------------------------------------------------------------
__fastcall TFormDialogoProducto::TFormDialogoProducto(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

TModalResult TFormDialogoProducto::Mostrar(int tipo)
{
        Caption = Dialogos[tipo];
        return ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormDialogoProducto::BitBtnAceptarClick(TObject *Sender)
{
        /* Se verifica que estén los datos obligatorios */
        DBEditCodigo->Text = DBEditCodigo->Text.Trim();
        if (DBEditCodigo->Text.IsEmpty())
        {
                MessageBox(Handle, "Debe especificar un código para el "
                           "producto.", Application->Title.c_str(),
                           MB_APPLMODAL | MB_OK | MB_ICONINFORMATION);
                return;
        }
        if (DBEditDescripcion->Text.IsEmpty())
        {
                MessageBox(Handle, "Debe especificar una descripción para el "
                           "producto.", Application->Title.c_str(),
                           MB_APPLMODAL | MB_OK | MB_ICONINFORMATION);
                return;
        }
        if (DBEditPrecio1->Text.IsEmpty() ||
            DBEditPrecio2->Text.IsEmpty() ||
            DBEditPrecio3->Text.IsEmpty())
        {
                MessageBox(Handle, "Debe especificar todos los precios para "
                           "el producto.",
                           Application->Title.c_str(), MB_APPLMODAL |
                           MB_OK | MB_ICONINFORMATION);
                return;
        }
        if (DBEditGramos->Text.IsEmpty())
        {
                MessageBox(Handle, "Debe especificar los gramos para el "
                           "producto.", Application->Title.c_str(),
                           MB_APPLMODAL | MB_OK | MB_ICONINFORMATION);
                return;
        }

        /* Se verifican que los datos sean correctos */
        TDBEdit *dbedit;
        for (int i = 1; i <= 3; i++)
        {
                dbedit = static_cast<TDBEdit *>(FindComponent("DBEditPrecio" +
                                                              IntToStr(i)));
                try
                {
                        double precio = MonedaANumero(dbedit->Text).ToDouble();
                        if (precio < 0) throw Exception("");
                }
                catch (...)
                {
                        MessageBox(Handle, ("El valor ingresado para Precio " +
                                   IntToStr(i) + " no es válido.").c_str(),
                                   Application->Title.c_str(),
                                   MB_APPLMODAL | MB_OK | MB_ICONWARNING);
                        return;
                }
        }
        try
        {
                int gramos = DBEditGramos->Text.ToInt();
                if (gramos < 0) throw Exception("");
        }
        catch (...)
        {
                MessageBox(Handle,
                           "El valor ingresado para Gramos no es válido.",
                           Application->Title.c_str(),
                           MB_APPLMODAL | MB_OK | MB_ICONWARNING);
                Abort();
        }

        /* Si es un nuevo producto o se está editando uno, entonces se envían
           los datos */
        if (BD->TableProductos->State == dsInsert ||
            BD->TableProductos->State == dsEdit)
        {
                BD->TableProductos->Post();
        }

        ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TFormDialogoProducto::BitBtnCancelarClick(TObject *Sender)
{
        ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TFormDialogoProducto::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        /* Se cancelan las modificaciones del registro actual no enviadas */
        BD->TableProductos->Cancel();
}
//---------------------------------------------------------------------------

void __fastcall TFormDialogoProducto::FormShow(TObject *Sender)
{
        DBEditCodigo->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFormDialogoProducto::BitBtnFamiliasClick(
      TObject *Sender)
{
        TBitBtn *boton = static_cast< TBitBtn * >(Sender);
        FormItemsProductos->Mostrar(boton->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TFormDialogoProducto::DBEditPrecio1KeyPress(
      TObject *Sender, char &Key)
{
        TEdit *Precio = static_cast<TEdit *>(Sender);
        if (Key == '+' || Key == '-')
                Abort();
        if (Key == '.')
                if (Precio->Text.AnsiPos(".") &&
                    ! Precio->SelText.AnsiPos(".")) Abort();
}
//---------------------------------------------------------------------------

void __fastcall TFormDialogoProducto::DBEditCodigoKeyPress(TObject *Sender,
      char &Key)
{
        if (! (isalnum(Key) || Key == VK_BACK)) Abort();
}
//---------------------------------------------------------------------------

