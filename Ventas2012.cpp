//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("basedatos.cpp", BD); /* TDataModule: File Type */
USEFORM("principal.cpp", FormPrincipal);
USEFORM("archivoclientes.cpp", FormArchivoClientes);
USEFORM("archivoproductos.cpp", FormArchivoProductos);
USEFORM("registrodocumentos.cpp", FormRegistroDocumentos);
USEFORM("buscarclientes.cpp", FormBuscarClientes);
USEFORM("buscarproductos.cpp", FormBuscarProductos);
USEFORM("dialogocliente.cpp", FormDialogoCliente);
USEFORM("dialogoproducto.cpp", FormDialogoProducto);
USEFORM("itemsclientes.cpp", FormItemsClientes);
USEFORM("itemsproductos.cpp", FormItemsProductos);
USEFORM("seleccionarcliente.cpp", FormSeleccionarCliente);
USEFORM("seleccionarproducto.cpp", FormSeleccionarProducto);
USEFORM("facturacion.cpp", FormFacturacion);
USEFORM("cuentacorriente.cpp", FormCuentaCorriente);
USEFORM("configuracion.cpp", FormConfiguracion);
USEFORM("saldos.cpp", FormSaldos);
USEFORM("registroventasdiario.cpp", FormRegistroVentasDiario);
USEFORM("registroventasmensual.cpp", FormRegistroVentasMensual);
USEFORM("registroventasanual.cpp", FormRegistroVentasAnual);
USEFORM("mensaje.cpp", FormMensaje);
USEFORM("impresion.cpp", FormImpresion);
USEFORM("Identificacion.cpp", FormIdentificacion);
USEFORM("registroproductosdiario.cpp", FormRegistroProductosDiario);
USEFORM("registroproductosmensual.cpp", FormRegistroProductosMensual);
USEFORM("registroproductosanual.cpp", FormRegistroProductosAnual);
USEFORM("registroproductosstock.cpp", FormRegistroProductosStock);
USEFORM("registrokilogramosmensual.cpp", FormRegistroKilogramosMensual);
USEFORM("seleccionarperiodo.cpp", FormSeleccionarPeriodo);
USEFORM("dialogoafip.cpp", FormDialogoAFIP);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        /* Configuración regional */
        DecimalSeparator = '.';
        ThousandSeparator = ',';
        ShortDateFormat = "dd/mm/yyyy";
        LongTimeFormat = "HH:nn";
        CurrencyDecimals = 2;
        DateSeparator = '/';

        try
        {
                 Application->Initialize();
                 Application->Title = "Ventas2012";
                 Application->CreateForm(__classid(TBD), &BD);
                 Application->CreateForm(__classid(TFormPrincipal), &FormPrincipal);
                 Application->CreateForm(__classid(TFormIdentificacion), &FormIdentificacion);
                 Application->CreateForm(__classid(TFormArchivoClientes), &FormArchivoClientes);
                 Application->CreateForm(__classid(TFormArchivoProductos), &FormArchivoProductos);
                 Application->CreateForm(__classid(TFormDialogoCliente), &FormDialogoCliente);
                 Application->CreateForm(__classid(TFormDialogoProducto), &FormDialogoProducto);
                 Application->CreateForm(__classid(TFormBuscarClientes), &FormBuscarClientes);
                 Application->CreateForm(__classid(TFormBuscarProductos), &FormBuscarProductos);
                 Application->CreateForm(__classid(TFormSeleccionarCliente), &FormSeleccionarCliente);
                 Application->CreateForm(__classid(TFormSeleccionarProducto), &FormSeleccionarProducto);
                 Application->CreateForm(__classid(TFormRegistroDocumentos), &FormRegistroDocumentos);
                 Application->CreateForm(__classid(TFormItemsClientes), &FormItemsClientes);
                 Application->CreateForm(__classid(TFormItemsProductos), &FormItemsProductos);
                 Application->CreateForm(__classid(TFormFacturacion), &FormFacturacion);
                 Application->CreateForm(__classid(TFormCuentaCorriente), &FormCuentaCorriente);
                 Application->CreateForm(__classid(TFormConfiguracion), &FormConfiguracion);
                 Application->CreateForm(__classid(TFormSaldos), &FormSaldos);
                 Application->CreateForm(__classid(TFormRegistroProductosStock), &FormRegistroProductosStock);
                 Application->CreateForm(__classid(TFormRegistroProductosAnual), &FormRegistroProductosAnual);
                 Application->CreateForm(__classid(TFormRegistroVentasDiario), &FormRegistroVentasDiario);
                 Application->CreateForm(__classid(TFormRegistroVentasMensual), &FormRegistroVentasMensual);
                 Application->CreateForm(__classid(TFormRegistroVentasAnual), &FormRegistroVentasAnual);
                 Application->CreateForm(__classid(TFormMensaje), &FormMensaje);
                 Application->CreateForm(__classid(TFormImpresion), &FormImpresion);
                 Application->CreateForm(__classid(TFormSeleccionarPeriodo), &FormSeleccionarPeriodo);
                 Application->CreateForm(__classid(TFormRegistroProductosDiario), &FormRegistroProductosDiario);
                 Application->CreateForm(__classid(TFormDialogoAFIP), &FormDialogoAFIP);
                 Application->CreateForm(__classid(TFormRegistroKilogramosMensual), &FormRegistroKilogramosMensual);
                 Application->CreateForm(__classid(TFormRegistroProductosMensual), &FormRegistroProductosMensual);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
