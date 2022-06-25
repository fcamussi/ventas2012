//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "buscarproductos.h"
#include "basedatos.h"
#include "archivoproductos.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormBuscarProductos *FormBuscarProductos;
static AnsiString codigoproducto;

//---------------------------------------------------------------------------
__fastcall TFormBuscarProductos::TFormBuscarProductos(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormBuscarProductos::FormCreate(TObject *Sender)
{
        TableProductos->DatabaseName = BD->TableProductos->DatabaseName;

        for (int c = 0; c < FormArchivoProductos->DBGrid->Columns->Count; c++)
        {
                ComboBoxColumna->Items->Add(FormArchivoProductos->DBGrid
                                        ->Columns->Items[c]->Title->Caption);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormBuscarProductos::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        DBGrid->DataSource = NULL;
        TableProductos->Filtered = false;
        TableProductos->Active = false;
}
//---------------------------------------------------------------------------

AnsiString TFormBuscarProductos::Mostrar()
{
        codigoproducto = "";
        ShowModal();
        return codigoproducto;
}
//---------------------------------------------------------------------------

void __fastcall TFormBuscarProductos::BitBtnBuscarClick(TObject *Sender)
{
        if (BusquedaValida())
        {
                TableProductos->Filtered = true;
                DBGrid->DataSource = DataSourceProductos;

                if (TableProductos->IsEmpty())
                {
                        MessageBox(Handle, "No se han encontrado "
                        "coincidencias.", Application->Title.c_str(),
                        MB_APPLMODAL | MB_OK | MB_ICONINFORMATION);
                        BitBtnSeleccionar->Enabled = false;
                }
                else
                {
                        BitBtnSeleccionar->Enabled = true;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormBuscarProductos::BitBtnCerrarClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormBuscarProductos::FormShow(TObject *Sender)
{
        TableProductos->Active = True;
        EditTexto->Text = "";
        ComboBoxColumna->ItemIndex = 0;
        EditTexto->SetFocus();
        BitBtnSeleccionar->Enabled = false;
}
//---------------------------------------------------------------------------

bool TFormBuscarProductos::BusquedaValida()
{
        AnsiString columna = TableProductos->FieldDefs
                                           ->Items[ComboBoxColumna->ItemIndex]
                                           ->Name;

        if (EditTexto->Text.IsEmpty())
        {
                MessageBox(Handle, "Debe especificar un valor.",
                           Application->Title.c_str(), MB_APPLMODAL | MB_OK |
                           MB_ICONINFORMATION);
                return false;
        }

        if (columna == "Fecha")
        {
                try
                {
                        TDateTime fecha = StrToDate(EditTexto->Text);
                        EditTexto->Text = DateToStr(fecha);
                }
                catch (EConvertError &converterror)
                {
                        MessageBox(Handle, "El valor ingresado no es una "
                                   "fecha válida.",
                                   Application->Title.c_str(), MB_APPLMODAL
                                   | MB_OK | MB_ICONWARNING);
                        return false;
                }
        }
        else if (columna == "Precio1" ||
                 columna == "Precio2" ||
                 columna == "Precio3")
        {
                try
                {
                        double precio = EditTexto->Text.ToDouble();
                        if (precio < 0) throw EConvertError("");
                }
                catch (EConvertError &converterror)
                {
                        MessageBox(Handle, "El valor ingresado no es un "
                                           "precio válido.",
                                           Application->Title.c_str(),
                                           MB_APPLMODAL | MB_OK |
                                           MB_ICONWARNING);
                        return false;
                }
        }
        else if (columna == "Gramos")
        {
                try
                {
                        int gramos = EditTexto->Text.ToInt();
                        if (gramos < 0) throw EConvertError("");
                }
                catch (EConvertError &converterror)
                {
                        MessageBox(Handle, "El valor ingresado para gramos "
                                           "es inválido.",
                                           Application->Title.c_str(),
                                           MB_APPLMODAL | MB_OK |
                                           MB_ICONWARNING);
                        return false;
                }
        }
        else
        {
                if (EditTexto->Text.Length() < 2)
                {
                        MessageBox(Handle, "El texto debe tener por lo menos 2 "
                                   "letras.", Application->Title.c_str(), MB_APPLMODAL
                                   | MB_OK | MB_ICONINFORMATION);
                        return false;
                }
        }

        return true;
}
//---------------------------------------------------------------------------

void __fastcall TFormBuscarProductos::BitBtnSeleccionarClick(TObject *Sender)
{
        codigoproducto = TableProductos->FieldValues["CodigoProducto"];
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormBuscarProductos::DBGridDblClick(TObject *Sender)
{
        if (BitBtnSeleccionar->Enabled == true)
        {
                BitBtnSeleccionar->Click();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormBuscarProductos::TableProductosFilterRecord(
      TDataSet *DataSet, bool &Accept)
{
        AnsiString columna;

        columna = DataSet->FieldDefs->Items[ComboBoxColumna->ItemIndex]->Name;

        if (columna == "Fecha")
        {
                TDateTime campo, fecha;

                campo = DataSet->FieldByName(columna)->AsDateTime;
                fecha = StrToDate(EditTexto->Text);

                // Filtro
                if (campo == fecha)
                {
                        Accept = true;
                }
                else
                {
                        Accept = false;
                }
        }
        else if (columna == "Precio1" ||
                 columna == "Precio2" ||
                 columna == "Precio3")
        {
                int campo, numero;

                campo = DataSet->FieldByName(columna)->AsFloat;
                numero = EditTexto->Text.ToDouble();

                // Filtro
                if (campo == numero)
                {
                        Accept = true;
                }
                else
                {
                        Accept = false;
                }
        }
        else if (columna == "Gramos")
        {
                int campo, numero;

                campo = DataSet->FieldByName(columna)->AsInteger;
                numero = EditTexto->Text.ToInt();

                // Filtro
                if (campo == numero)
                {
                        Accept = true;
                }
                else
                {
                        Accept = false;
                }
        }
        else
        {
                AnsiString campo, texto;

                campo = DataSet->FieldByName(columna)->AsString;

                campo = campo.UpperCase();
                texto = EditTexto->Text.UpperCase();

                // Filtro
                if (campo.Pos(texto) > 0)
                {
                        Accept = true;
                }
                else
                {
                        Accept = false;
                }
        }
}
//---------------------------------------------------------------------------

