//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "registroproductosstock.h"
#include "basedatos.h"
#include "impresion.h"
#include "auxiliar.h"
#include "seleccionarproducto.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormRegistroProductosStock *FormRegistroProductosStock;
//---------------------------------------------------------------------------
__fastcall TFormRegistroProductosStock::TFormRegistroProductosStock(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TFormRegistroProductosStock::Mostrar()
{
        ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::MenuItemCerrarClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::FormCreate(TObject *Sender)
{
        ListaMenuOrdenar lista;
        lista["ISCodigoProducto"] = "Código producto";
        lista["ISDescripcion"] = "Descripción";
        lista["ISUnidad"] = "Unidad";
        lista["ISStock"] = "Stock";
        CrearMenuOrdenar(lista, "ISCodigoProducto", BD->TableProductos,
                         MenuItemOrdenar, MenuItemOrdCol);
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::MenuItemOrdCol(TObject *Sender)
{
        SetearMenuOrdenar(BD->TableProductos, static_cast< TMenuItem * >(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::FormShow(TObject *Sender)
{
        /* Seteo el index por defecto y muevo a la primera fila */
        DefectoMenuOrdenar(BD->TableProductos, MenuItemOrdenar);
        BD->TableProductos->First();
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::DBGridKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
        // Anulo los atajos por defecto para agregar y eliminar filas
        if ((Shift.Contains(ssCtrl) && Key == VK_DELETE) || Key == VK_INSERT)
        {
                Abort();
        }
        if (Key == VK_DOWN && BD->TableProductos->RecNo >=
            BD->TableProductos->RecordCount)
        {
                Abort();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::DBGridColExit(TObject *Sender)
{
        /* Si se cambia de columna se envía un post */
        if (BD->TableProductos->State == dsEdit)
        {
                BD->TableProductos->Post();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::DBGridExit(TObject *Sender)
{
        /* Si se sale de la grilla se envía un post */
        if (BD->TableProductos->State == dsEdit)
        {
                BD->TableProductos->Post();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::DBGridKeyPress(TObject *Sender,
      char &Key)
{
        /* Impide que se escriba cuando esta vacía */
        if (BD->TableProductos->IsEmpty())
        {
                Abort();
        }
        /* Si se presiona enter se envía un post */
        if (BD->TableProductos->State == dsEdit && Key == VK_RETURN)
        {
                BD->TableProductos->Post();
                if (! DBGrid->EditorMode) Abort(); /* Cancela el enter */
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::MenuItemResetearStockClick(
      TObject *Sender)
{
        AnsiString mensaje;
        int valor;

        mensaje = "Todo el stock se seteará a cero ¿Realmente desea hacerlo?";
        valor = MessageBox(Handle, mensaje.c_str(), Application->Title.c_str(),
                           MB_APPLMODAL | MB_YESNO | MB_ICONQUESTION);
        if (valor == IDYES)
        {
                ResetearStock();
        }
}
//---------------------------------------------------------------------------

void TFormRegistroProductosStock::ResetearStock()
{
        TBookmark actual = BD->TableProductos->GetBookmark();
        BD->TableProductos->DisableControls();

        BD->TableProductos->First();
        do
        {
                BD->TableProductos->Edit();
                BD->TableProductos->FieldValues["Stock"] = 0;
                BD->TableProductos->Post();
                BD->TableProductos->Next();
        } while (! BD->TableProductos->Eof);

        BD->TableProductos->GotoBookmark(actual);
        BD->TableProductos->FreeBookmark(actual);
        BD->TableProductos->EnableControls();
}
//---------------------------------------------------------------------------

void TFormRegistroProductosStock::DescargarStock(AnsiString codigo, int cantidad)
{
        BuscarClave(BD->TableProductos, "CodigoProducto", Variant(codigo));
        BD->TableProductos->Edit();
        BD->TableProductos->FieldByName("Stock")->AsInteger -= cantidad;
        BD->TableProductos->Post();
}
//---------------------------------------------------------------------------

void TFormRegistroProductosStock::CargarStock(AnsiString codigo, int cantidad)
{
        BuscarClave(BD->TableProductos, "CodigoProducto", Variant(codigo));
        BD->TableProductos->Edit();
        BD->TableProductos->FieldByName("Stock")->AsInteger += cantidad;
        BD->TableProductos->Post();
}
//---------------------------------------------------------------------------

int TFormRegistroProductosStock::CantidadStock(AnsiString codigo)
{
        BuscarClave(BD->TableProductos, "CodigoProducto", Variant(codigo));
        return BD->TableProductos->FieldByName("Stock")->AsInteger;
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::MenuItemImprimirClick(
      TObject *Sender)
{
        Impresion imp;

        if (BD->TableProductos->IsEmpty()) return;
        imp.ImprimirRegistroProductosStock(false);
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::ToolButtonImprimirDesdeClick(
      TObject *Sender)
{
        MenuItemImprimir->Click();        
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::MenuItemVisualizarClick(
      TObject *Sender)
{
        Impresion imp;

        if (BD->TableProductos->IsEmpty()) return;
        imp.ImprimirRegistroProductosStock(true);
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::DBGridDrawColumnCell(
      TObject *Sender, const TRect &Rect, int DataCol, TColumn *Column,
      TGridDrawState State)
{
        if (BD->TableProductos->IsEmpty()) return;

        TDBGrid *grid = static_cast<TDBGrid*>(Sender);
        if(BD->TableProductos->FieldValues["Stock"] < 0)
        {
                grid->Canvas->Font->Color = clRed;
        }
        grid->DefaultDrawColumnCell(Rect, DataCol, Column, State);
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::MenuItemSeleccionarClick(
      TObject *Sender)
{
        AnsiString defecto = BD->TableProductos->FieldValues["CodigoProducto"];
        AnsiString codigoproducto = FormSeleccionarProducto->Mostrar(defecto);
        if (! codigoproducto.IsEmpty())
        {
                /* Localizo el producto en la tabla */
                BuscarClave(BD->TableProductos, "CodigoProducto", Variant(codigoproducto));
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::MenuItemAgregarClick(
      TObject *Sender)
{
        if (! BD->TableProductos->IsEmpty())
        {
                AnsiString codigo = BD->TableProductos->FieldValues["CodigoProducto"];
                AnsiString texto = "Ingrese la cantidad que desea agregar "
                                   "de stock.";
                AnsiString tmp = "0";
                bool valor = InputQuery("Agregar stock", texto, tmp);
                if (valor)
                {
                        int cantidad;
                        try {
                                cantidad = tmp.ToInt();
                                if (cantidad < 0) throw "Error";
                        }
                        catch (...)
                        {
                                AnsiString mensaje = "La cantidad es incorrecta.";
                                MessageBox(Handle, mensaje.c_str(),
                                           Application->Title.c_str(),
                                           MB_APPLMODAL | MB_ICONWARNING);
                                return;
                        }
                        CargarStock(codigo, cantidad);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::MenuItemQuitarClick(
      TObject *Sender)
{
        if (! BD->TableProductos->IsEmpty())
        {
                AnsiString codigo = BD->TableProductos->FieldValues["CodigoProducto"];
                AnsiString texto = "Ingrese la cantidad que desea quitar "
                                   "de stock.";
                AnsiString tmp = "0";
                bool valor = InputQuery("Quitar stock", texto, tmp);
                if (valor)
                {
                        int cantidad;
                        try {
                                cantidad = tmp.ToInt();
                                if (cantidad < 0) throw "Error";
                        }
                        catch (...)
                        {
                                AnsiString mensaje = "La cantidad es incorrecta.";
                                MessageBox(Handle, mensaje.c_str(),
                                           Application->Title.c_str(),
                                           MB_APPLMODAL | MB_ICONWARNING);
                                return;
                        }
                        DescargarStock(codigo, cantidad);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::MenuItemAgregar2Click(
      TObject *Sender)
{
        MenuItemAgregar->Click();        
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::MenuItemQuitar2Click(
      TObject *Sender)
{
        MenuItemQuitar->Click();        
}
//---------------------------------------------------------------------------

void __fastcall TFormRegistroProductosStock::MenuItemSeleccionar2Click(
      TObject *Sender)
{
        MenuItemSeleccionar->Click();        
}
//---------------------------------------------------------------------------

