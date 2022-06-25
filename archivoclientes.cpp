//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector.h>
#include <inifiles.hpp>
#pragma hdrstop

#include "archivoclientes.h"
#include "dialogocliente.h"
#include "basedatos.h"
#include "buscarclientes.h"
#include "configuracion.h"
#include "numeracion.h"
#include "auxiliar.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormArchivoClientes *FormArchivoClientes;

//---------------------------------------------------------------------------
__fastcall TFormArchivoClientes::TFormArchivoClientes(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TFormArchivoClientes::Mostrar()
{
        ShowModal();
}
//---------------------------------------------------------------------------

bool TFormArchivoClientes::HayClientes()
{
        return ! BD->TableClientes->IsEmpty();
}
//---------------------------------------------------------------------------

void TFormArchivoClientes::AgregarCliente()
{
        int numerocliente;

        /* Obtengo el número para el cliente */
        numerocliente = NumeroClientes() + 1;

        /* Agrego un registro y seteo los datos "read only" */
        BD->TableClientes->Append();
        BD->TableClientes->FieldValues["NumeroCliente"] = numerocliente;
        BD->TableClientes->FieldValues["Fecha"] = Date();

        if (FormDialogoCliente->Mostrar(DLG_CTE_AGREGAR) == mrOk)
        {
                IncrementarNumeroClientes();
        }
}
//---------------------------------------------------------------------------

void TFormArchivoClientes::EditarCliente()
{
        FormDialogoCliente->Mostrar(DLG_CTE_EDITAR);
}
//---------------------------------------------------------------------------

void TFormArchivoClientes::EliminarCliente()
{
        while (! BD->TableCuentasCorrientes->IsEmpty())
        {
                BD->TableCuentasCorrientes->Delete();
        }
        BD->TableClientes->Delete();
}
//---------------------------------------------------------------------------

bool TFormArchivoClientes::ConfirmarEliminacion()
{
        AnsiString mensaje;
        int valor;
        int numerocliente;
        AnsiString nombrecliente;

        numerocliente = BD->TableClientes->FieldValues["NumeroCliente"];
        nombrecliente = BD->TableClientes->FieldValues["NombreCliente"];
        mensaje = "Se eliminará el cliente número: " + IntToStr(numerocliente) +
                  ", bajo el nombre: " + nombrecliente + ". ¿Realmente desea "
                  "hacerlo?";
        valor = MessageBox(Handle, mensaje.c_str(), Application->Title.c_str(),
                           MB_APPLMODAL | MB_YESNO | MB_ICONQUESTION);
        if (valor != IDYES) return false;

        mensaje = "Al borrar el cliente también se perderán todos los datos "
                  "relacionados con el mismo, como su cuenta corriente. "
                  "¿Desea continuar?";
        valor = MessageBox(Handle, mensaje.c_str(), Application->Title.c_str(),
                           MB_APPLMODAL | MB_YESNO | MB_ICONWARNING);
        return (valor == IDYES? true: false);
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoClientes::MenuItemAgregarClick(TObject *Sender)
{
        AgregarCliente();
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoClientes::MenuItemEditarClick(TObject *Sender)
{
        if (HayClientes())
        {
                EditarCliente();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoClientes::MenuItemEliminarClick(TObject *Sender)
{
        if (HayClientes())
        {
                if (ConfirmarEliminacion())
                {
                        EliminarCliente();
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoClientes::MenuItemBuscarClick(TObject *Sender)
{
        if (HayClientes())
        {
                int numerocliente = FormBuscarClientes->Mostrar();
                if (numerocliente > 0)
                {
                        BuscarClave(BD->TableClientes, "NumeroCliente",
                                    Variant(numerocliente));
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoClientes::MenuItemCerrarClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoClientes::FormCreate(TObject *Sender)
{
        ListaMenuOrdenar lista;
        lista["ISNumeroCliente"] = "Número cliente";
        lista["ISFecha"] = "Fecha";
        lista["ISNombreCliente"] = "Nombre cliente";
        lista["ISDireccion"] = "Dirección";
        lista["ISLocalidad"] = "Localidad";
        lista["ISProvincia"] = "Provincia";
        lista["ISNombreNegocio"] = "Nombre negocio";
        lista["ISTipoNegocio"] = "Tipo negocio";
        lista["ISNombreFactura"] = "Nombre factura";
        lista["ISPosicionIVA"] = "Posición IVA";
        lista["ISFormaPago"] = "Forma de pago";
        lista["ISDescuento"] = "Descuento";
        CrearMenuOrdenar(lista, "ISNombreCliente", BD->TableClientes,
                         MenuItemOrdenar, MenuItemOrdCol);
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoClientes::MenuItemOrdCol(TObject *Sender)
{
        SetearMenuOrdenar(BD->TableClientes, static_cast< TMenuItem * >(Sender));
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoClientes::DBGridKeyPress(TObject *Sender,
      char &Key)
{
        if (Key == VK_RETURN)
        {
                MenuItemEditar->Click();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormArchivoClientes::FormShow(TObject *Sender)
{
        /* Seteo el index por defecto y muevo a la primera fila */
        DefectoMenuOrdenar(BD->TableClientes, MenuItemOrdenar);
        BD->TableClientes->First();
}
//---------------------------------------------------------------------------


