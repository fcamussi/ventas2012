//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "buscarclientes.h"
#include "basedatos.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormBuscarClientes *FormBuscarClientes;
static int numerocliente;

//---------------------------------------------------------------------------
__fastcall TFormBuscarClientes::TFormBuscarClientes(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormBuscarClientes::FormCreate(TObject *Sender)
{
        TableClientes->DatabaseName = BD->TableClientes->DatabaseName;

        for (int c = 0; c < DBGrid->Columns->Count; c++)
        {
                ComboBoxColumna->Items->Add(DBGrid->Columns->Items[c]->Title
                                                                     ->Caption);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormBuscarClientes::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        DBGrid->DataSource = NULL;
        TableClientes->Filtered = false;
        TableClientes->Active = false;
}
//---------------------------------------------------------------------------

int TFormBuscarClientes::Mostrar()
{
        numerocliente = 0;
        ShowModal();
        return numerocliente;
}
//---------------------------------------------------------------------------

void __fastcall TFormBuscarClientes::BitBtnBuscarClick(TObject *Sender)
{
        if (BusquedaValida())
        {
                TableClientes->Filtered = true;
                DBGrid->DataSource = DataSourceClientes;

                if (TableClientes->IsEmpty())
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

void __fastcall TFormBuscarClientes::BitBtnCerrarClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormBuscarClientes::FormShow(TObject *Sender)
{
        TableClientes->Active = true;
        EditTexto->Text = "";
        ComboBoxColumna->ItemIndex = 0;
        EditTexto->SetFocus();
        BitBtnSeleccionar->Enabled = false;
}
//---------------------------------------------------------------------------

bool TFormBuscarClientes::BusquedaValida()
{
        AnsiString columna = TableClientes->FieldDefs
                                          ->Items[ComboBoxColumna->ItemIndex]
                                          ->Name;

        if (EditTexto->Text.IsEmpty())
        {
                MessageBox(Handle, "Debe especificar un valor.",
                           Application->Title.c_str(), MB_APPLMODAL | MB_OK |
                           MB_ICONINFORMATION);
                return false;
        }

        if (columna == "NumeroCliente")
        {
                int numero = EditTexto->Text.ToIntDef(0);
                if (numero < 1)
                {
                        MessageBox(Handle, "El valor ingresado no es un "
                                   "número válido.",
                                   Application->Title.c_str(), MB_APPLMODAL |
                                   MB_OK | MB_ICONWARNING);
                        return false;
                }
        }
        else if (columna == "Fecha")
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
        else if (columna == "Descuento")
        {
                try
                {
                        double descuento = EditTexto->Text.ToDouble();
                        if (descuento < 0 || descuento > 100)
                        {
                                MessageBox(Handle, "El valor ingresado no es "
                                "un descuento válido.",
                                Application->Title.c_str(), MB_APPLMODAL
                                | MB_OK | MB_ICONWARNING);
                                return false;
                        }
                }
                catch (EConvertError &converterror)
                {
                        MessageBox(Handle,
                                   "El valor ingresado no es un descuento "
                                   "válido.", Application->Title.c_str(),
                                   MB_APPLMODAL | MB_OK | MB_ICONWARNING);
                        return false;
                }
        }
        else
        {
                if (EditTexto->Text.Length() < 3)
                {
                        MessageBox(Handle, "El texto debe tener por lo menos 3 "
                                   "letras.", Application->Title.c_str(), MB_APPLMODAL
                                   | MB_OK | MB_ICONINFORMATION);
                        return false;
                }
        }

        return true;
}
//---------------------------------------------------------------------------

void __fastcall TFormBuscarClientes::BitBtnSeleccionarClick(TObject *Sender)
{
        numerocliente = TableClientes->FieldValues["NumeroCliente"];
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormBuscarClientes::DBGridDblClick(TObject *Sender)
{
        if (BitBtnSeleccionar->Enabled == true)
        {
                BitBtnSeleccionar->Click();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormBuscarClientes::TableClientesFilterRecord(
      TDataSet *DataSet, bool &Accept)
{
        AnsiString columna;

        columna = DataSet->FieldDefs->Items[ComboBoxColumna->ItemIndex]->Name;

        if (columna == "NumeroCliente" ||
            columna == "Descuento")
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
        else if (columna == "Fecha")
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

