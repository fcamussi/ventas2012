//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "numeracion.h"
#include "facturacion.h"
#include "basedatos.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
static AnsiString DOCUMENTOS[DOC_N] = {"Remito",
                                       "Factura",
                                       "CreditoRemito",
                                       "CreditoFactura",
                                       "FacturaElect",
                                       "CreditoElect",
                                       "DebitoElect",
                                       "Pedido"};
//---------------------------------------------------------------------------

int NumeroDocumentos(int tipodocumento)
{
        AnsiString col;
        int num;

        BD->TableNumeracion->First();
        col = "Numero" + DOCUMENTOS[tipodocumento];
        num = BD->TableNumeracion->FieldValues[col];
        return num;
}
//---------------------------------------------------------------------------

void IncrementarNumeroDocumentos(int tipodocumento)
{
        AnsiString col;
        int num;

        BD->TableNumeracion->First();
        BD->TableNumeracion->Edit();
        col = "Numero" + DOCUMENTOS[tipodocumento];
        num = BD->TableNumeracion->FieldValues[col];
        num++;
        BD->TableNumeracion->FieldValues[col] = num;
        BD->TableNumeracion->Post();
}
//---------------------------------------------------------------------------

int NumeroClientes()
{
        int num;

        BD->TableNumeracion->First();
        BD->TableNumeracion->Edit();
        num = BD->TableNumeracion->FieldValues["NumeroCliente"];
        return num;
}
//---------------------------------------------------------------------------

void IncrementarNumeroClientes()
{
        int num;

        BD->TableNumeracion->First();
        BD->TableNumeracion->Edit();
        num = BD->TableNumeracion->FieldValues["NumeroCliente"];
        num++;
        BD->TableNumeracion->FieldValues["NumeroCliente"] = num;
        BD->TableNumeracion->Post();
}
//---------------------------------------------------------------------------

