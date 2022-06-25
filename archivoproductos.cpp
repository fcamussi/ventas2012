//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector.h>
#include <inifiles.hpp>
#pragma hdrstop

#include "archivoproductos.h"
#include "dialogoproducto.h"
#include "basedatos.h"
#include "buscarproductos.h"
#include "configuracion.h"
#include "auxiliar.h"
#include "impresion.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormArchivoProductos *FormArchivoProductos;

//---------------------------------------------------------------------------
__fastcall TFormArchivoProductos::TFormArchivoProductos(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TFormArchivoProductos::Mostrar()
{
        ShowModal();
}
//---------------------------------------------------------------------------

bool TFormArchivoProductos::HayProductos()
{
        return ! BD->TableProductos->IsEmpty();
}
//---------------------------------------------------------------------------

void TFormArchivoProductos::AgregarProducto()
{
        /* Agrego un registro y seteo los datos "read only" */
        BD->TableProductos->Append();
        BD->TableProductos->FieldValues["Fecha"] = Date();
        BD->TableProductos->FieldValues["Stock"] = 0;

        FormDialogoProducto->Mostrar(DLG_PTO_AGREGAR);
}
//---------------------------------------------------------------------------

void TFormArchivoProductos::EditarProducto()
{
        FormDialogoProducto->Mostrar(DLG_PTO_EDITAR);
}
//---------------------------------------------------------------------------

void TFormArchivoProductos::EliminarProducto()
{
        BD->TableProductos->Delete();
}
//---------------------------------------------------------------------------

bool TFormArchivoProductos::ConfirmarEliminacion()
{
        AnsiString mensaje;
        int valor;
        AnsiString codigoproducto;
        AnsiString descripcion;

        codigoproducto = BD->TableProductos->FieldValues["CodigoProducto"];
        descripcion = BD->TableProductos->FieldValues["Descripcion"];
        mensaje = "Se eliminará el producto con código: " + codigoproducto +
                  ", bajo la descripción: " + descripcion +
                  ". ¿Realmente desea hacerlo?";
        valor = MessageBox(Handle, mensaje.c_str(), Application->Title.c_str(),
                           MB_APPLMODAL | MB_YESNO | MB_ICONQUESTION);
        return (valor == IDYES? true: false);
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoProductos::MenuItemAgregarClick(TObject *Sender)
{
        AgregarProducto();
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoProductos::MenuItemEditarClick(TObject *Sender)
{
        if (HayProductos())
        {
                EditarProducto();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoProductos::MenuItemEliminarClick(TObject *Sender)
{
        if (HayProductos())
        {
                if(ConfirmarEliminacion())
                {
                        EliminarProducto();
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoProductos::MenuItemBuscarClick(TObject *Sender)
{
        if (HayProductos())
        {
                AnsiString codigoproducto = FormBuscarProductos->Mostrar();
                if (! codigoproducto.IsEmpty())
                {
                        BuscarClave(BD->TableProductos, "CodigoProducto",
                                    Variant(codigoproducto));
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoProductos::MenuItemCerrarClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoProductos::FormCreate(TObject *Sender)
{
        ListaMenuOrdenar lista;
        lista["ISCodigoProducto"] = "Código producto";
        lista["ISFecha"] = "Fecha";
        lista["ISDescripcion"] = "Descripción";
        lista["ISFamilia"] = "Familia";
        lista["ISUnidad"] = "Unidad";
        lista["ISPrecio1"] = "Precio 1";
        lista["ISPrecio2"] = "Precio 2";
        lista["ISPrecio3"] = "Precio 3";
        CrearMenuOrdenar(lista, "ISDescripcion", BD->TableProductos,
                         MenuItemOrdenar, MenuItemOrdCol);
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoProductos::MenuItemOrdCol(TObject *Sender)
{
        SetearMenuOrdenar(BD->TableProductos, static_cast< TMenuItem * >(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoProductos::DBGridKeyPress(TObject *Sender,
      char &Key)
{
        if (Key == VK_RETURN)
        {
                EditarProducto();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoProductos::FormShow(TObject *Sender)
{
        /* Seteo el index por defecto y muevo a la primera fila */
        DefectoMenuOrdenar(BD->TableProductos, MenuItemOrdenar);
        BD->TableProductos->First();
}
//---------------------------------------------------------------------------

void TFormArchivoProductos::ModificarPrecios(double porcentaje)
{
        TBookmark actual = BD->TableProductos->GetBookmark();
        BD->TableProductos->DisableControls();

        BD->TableProductos->First();
        do
        {
                BD->TableProductos->Edit();
                double precio1 = BD->TableProductos->FieldValues["Precio1"];
                precio1 += precio1 * porcentaje / 100;
                BD->TableProductos->FieldValues["Precio1"] = precio1;
                double precio2 = BD->TableProductos->FieldValues["Precio2"];
                precio2 += precio2 * porcentaje / 100;
                BD->TableProductos->FieldValues["Precio2"] = precio2;
                double precio3 = BD->TableProductos->FieldValues["Precio3"];
                precio3 += precio3 * porcentaje / 100;
                BD->TableProductos->FieldValues["Precio3"] = precio3;
                BD->TableProductos->Post();
                BD->TableProductos->Next();
        } while (! BD->TableProductos->Eof);

        BD->TableProductos->GotoBookmark(actual);
        BD->TableProductos->FreeBookmark(actual);
        BD->TableProductos->EnableControls();
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoProductos::MenuItemIncrementarPreciosClick(
      TObject *Sender)
{
        if (HayProductos())
        {
                AnsiString texto = "Ingrese el porcentaje que desea incrementar los "
                                   "precios.";
                AnsiString tmp = "0";
                bool valor = InputQuery("Incrementar precios", texto, tmp);
                if (valor)
                {
                        double porcentaje;
                        try {
                                porcentaje = tmp.ToDouble();
                                if (porcentaje < 0) throw "Error";
                        }
                        catch (...)
                        {
                                AnsiString mensaje = "El porcentaje es incorrecto.";
                                MessageBox(Handle, mensaje.c_str(),
                                           Application->Title.c_str(),
                                           MB_APPLMODAL | MB_ICONWARNING);
                                return;
                        }
                        texto = "Se modificarán todos los precios. ¿Realmente "
                                "desea hacerlo?";
                        int valor = MessageBox(Handle, texto.c_str(), Application->Title.c_str(),
                                               MB_APPLMODAL | MB_YESNO | MB_ICONQUESTION);
                        if (valor == IDNO) return;
                        ModificarPrecios(porcentaje);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoProductos::MenuItemDecrementarPreciosClick(
      TObject *Sender)
{
        if (HayProductos())
        {
                AnsiString texto = "Ingrese el porcentaje que desea decrementar "
                                   "los precios.";
                AnsiString tmp = "0";
                bool valor = InputQuery("Decrementar precios", texto, tmp);
                if (valor)
                {
                        double porcentaje;
                        try {
                                porcentaje = tmp.ToDouble();
                                if (porcentaje < 0) throw "Error";
                        }
                        catch (...)
                        {
                                AnsiString mensaje = "El porcentaje es incorrecto.";
                                MessageBox(Handle, mensaje.c_str(),
                                           Application->Title.c_str(),
                                           MB_APPLMODAL | MB_ICONWARNING);
                                return;
                        }
                        texto = "Se modificarán todos los precios. ¿Realmente "
                                "desea hacerlo?";
                        int valor = MessageBox(Handle, texto.c_str(), Application->Title.c_str(),
                                               MB_APPLMODAL | MB_YESNO | MB_ICONQUESTION);
                        if (valor == IDNO) return;
                        ModificarPrecios(-porcentaje);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoProductos::MenuItemImprimirClick(
      TObject *Sender)
{
        if (BD->TableProductos->IsEmpty()) return;

        Impresion imp;
        imp.ImprimirProductos(false);
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoProductos::ToolButtonImprimirClick(
      TObject *Sender)
{
        MenuItemImprimir->Click();        
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoProductos::ToolButtonAgregarClick(
      TObject *Sender)
{
        MenuItemAgregar->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoProductos::MenuItemVisualizarClick(
      TObject *Sender)
{
        if (BD->TableProductos->IsEmpty()) return;

        Impresion imp;
        imp.ImprimirProductos(true);
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoProductos::ExportarListaPreciosClick(
      TObject *Sender)
{
        Impresion imp;

        SaveDialog->DefaultExt = ".txt";
        SaveDialog->Filter = "Documento TXT (*.txt)|*.txt";
        SaveDialog->Options << ofOverwritePrompt << ofFileMustExist << ofHideReadOnly;

        AnsiString current = GetCurrentDir();
        if (SaveDialog->Execute())
        {
                imp.ExportarListaPrecios(SaveDialog->FileName);
        }
        SetCurrentDir(current);
}
//---------------------------------------------------------------------------

