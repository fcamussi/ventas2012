//---------------------------------------------------------------------------

#include <vcl.h>
#include <StrUtils.hpp>
#include <fstream>
#pragma hdrstop

#include "impresion.h"
#include "basedatos.h"
#include "facturacion.h"
#include "configuracion.h"
#include "auxiliar.h"

#define MARGEN_SUP 8
#define MARGEN_IZQ 15
#define NOM_FUENTE "Courier"
#define TAM_FUENTE 11
#define COL_FUENTE clBlack
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormImpresion *FormImpresion;
extern AFIP *afip;
//---------------------------------------------------------------------------
__fastcall TFormImpresion::TFormImpresion(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

Reporte::Reporte()
{
        FormImpresion->Image->Canvas->Font->Name = NOM_FUENTE;
        FormImpresion->Image->Canvas->Font->Size = TAM_FUENTE;
        FormImpresion->Image->Canvas->Font->Color = COL_FUENTE;
        FormImpresion->Image->Canvas->Font->Pitch = fpFixed;
}
//---------------------------------------------------------------------------

void Reporte::PrepararLienzo()
{
        int alto = 0, ancho = 0;
        int pos;
        AnsiString linea;
        int alto_letra = FormImpresion->Image->Canvas->TextHeight(" ");
        int ancho_letra = FormImpresion->Image->Canvas->TextWidth(" ");
        bool seguir = true;
        AnsiString tmp = texto;

        /* Calculo el tamaño del texto y ajusto el canvas */
        while (seguir)
        {
                pos = tmp.Pos("\n");
                if (pos == 0)
                {
                        seguir = false;
                }
                linea = tmp.SubString(1, pos - 1);
                alto += alto_letra;
                if (ancho < linea.Length() * ancho_letra)
                {
                        ancho = linea.Length() * ancho_letra;
                }
                tmp = tmp.SubString(pos + 1, tmp.Length());
        }
        alto += MARGEN_SUP * 2;
        ancho += MARGEN_IZQ * 2;

        FormImpresion->Image->Picture->Bitmap->Height = alto;
        FormImpresion->Image->Picture->Bitmap->Width = ancho;

        /* Limpio */
        FormImpresion->Image->Canvas->Brush->Style = bsSolid;
        FormImpresion->Image->Canvas->Pen->Color = clWhite;
        FormImpresion->Image->Canvas->Rectangle(0, 0, ancho, alto);

        /* Dibujo imagen */
        if (! imagen.IsEmpty())
        {
                FormImpresion->Image->Picture->LoadFromFile(imagen);
                FormImpresion->Image->Canvas->Font->Name = NOM_FUENTE;
                FormImpresion->Image->Canvas->Font->Size = TAM_FUENTE;
                FormImpresion->Image->Canvas->Font->Color = COL_FUENTE;
                FormImpresion->Image->Canvas->Font->Pitch = fpFixed;
        }

        FormImpresion->Image->Canvas->Brush->Style = bsClear;
}
//---------------------------------------------------------------------------

void Reporte::PrepararImpresora()
{
        TPrinter *printer = Printer();

        printer->Canvas->Font->Name = NOM_FUENTE;
        printer->Canvas->Font->Size = TAM_FUENTE;
        printer->Canvas->Font->Color = COL_FUENTE;
        printer->Canvas->Font->Pitch = fpFixed;
}
//---------------------------------------------------------------------------

void Reporte::DibujarTexto(TCanvas *canvas)
{
        int alto = 0;
        int pos;
        AnsiString linea;
        int alto_letra = canvas->TextHeight(" ");
        bool seguir = true;
        AnsiString tmp = texto.UpperCase();

        alto = MARGEN_SUP;

        /* Dibujo el texto */
        while (seguir)
        {
                pos = tmp.Pos("\n");
                if (pos == 0)
                {
                        pos = tmp.Length() + 1;
                        seguir = false;
                }
                linea = tmp.SubString(1, pos - 1);
                canvas->TextOutA(MARGEN_IZQ, alto, linea);
                alto += alto_letra;
                tmp = tmp.SubString(pos + 1, tmp.Length());
        }
}
//---------------------------------------------------------------------------

void Reporte::Mostrar()
{
        FormImpresion->Image->Visible = true;
        FormImpresion->ToolButtonGuardarBMP->Visible = true;
        FormImpresion->ToolButtonGuardarPDF->Visible = false;
        FormImpresion->OleContainer->Visible = false;

        PrepararLienzo();
        DibujarTexto(FormImpresion->Image->Canvas);
        FormImpresion->ShowModal();
}
//---------------------------------------------------------------------------

bool Reporte::ImprimirDirecto(AnsiString impresora, AnsiString nombretrabajo)
{
        AnsiString buffer = AnsiReplaceStr(Reporte::texto, "\n", "\n\r").UpperCase();
	boolean estado;
	HANDLE imp;
	DOC_INFO_1 InfoDoc;
	DWORD dwTrabajo;
	DWORD dwBytesEscritos;
        char *szNombreImpresora = impresora.c_str();

 	// Abrimos un apuntador a la impresora.
	estado = OpenPrinter((LPTSTR)szNombreImpresora, &imp, NULL);
	if (estado)
        {
                // Relleno en la estructura con información acerca de este "document".
                memset(&InfoDoc, 0, sizeof(InfoDoc));
	        InfoDoc.pDocName = nombretrabajo.c_str();
	        InfoDoc.pOutputFile = NULL;
		InfoDoc.pDatatype = "RAW";

		// Informamos al spooler que el documento empezó.
		dwTrabajo = StartDocPrinter(imp, 1, (LPBYTE)&InfoDoc);
		if (dwTrabajo > 0)
                {
		        // Incio de la página.
			estado = StartPagePrinter(imp);
			if (estado)
                        {
			        // Enviamos los datos a la impresora.
				estado = WritePrinter(imp, buffer.c_str(), buffer.Length(),
                                                      &dwBytesEscritos);
				estado = EndPagePrinter(imp);
			}
			// Informamos al spooler que finalizó el documento.
			estado = EndDocPrinter(imp);
		}
		// Cerramos el apuntador a la impresora.
		ClosePrinter(imp);
	}
	// Comprobamos que se hayan escrito el número correcto de bytes.
	if (! estado || ((int)dwBytesEscritos != buffer.Length()))
        {
		return false;
        }
	else
        {
		return true;
        }
}
//---------------------------------------------------------------------------

void Reporte::Imprimir(AnsiString impresora, AnsiString nombretrabajo, bool directo)
{
        if (directo)
        {
                //http://www.delphigroups.info/3/12/1055.html
                ImprimirDirecto(impresora, nombretrabajo);
        }
        else
        {
                TPrinter *printer = Printer();
                bool existe = false;

                for (int c = 0; c < printer->Printers->Count; c++)
                {
                        if (printer->Printers->Strings[c] == impresora) existe = true;
                }
                if (existe == true)
                {
                        printer->SetPrinterA(impresora.c_str(), "", "", NULL);
                        printer->Title = nombretrabajo;

                        printer->BeginDoc();
                        PrepararImpresora();
                        DibujarTexto(printer->Canvas);
                        printer->EndDoc();
                }
        }
}
//---------------------------------------------------------------------------

Reporte & Reporte::operator<<(AnsiString texto)
{
        Reporte::texto += texto;
        return *this;
}
//---------------------------------------------------------------------------

Reporte & Reporte::operator<<(int espacios)
{
        for (int a = 0; a < espacios; a++)
        {
                texto += " ";
        }
        return *this;
}
//---------------------------------------------------------------------------

void Reporte::Imagen(AnsiString imagen)
{
        Reporte::imagen = imagen;
}
//---------------------------------------------------------------------------

void Reporte::ExportarTexto(AnsiString fichero)
{
        ofstream f;
        f.open(fichero.c_str(), ofstream::out);
        f << (Reporte::texto).c_str();
        f.close();
}
//---------------------------------------------------------------------------

void Impresion::InsertarRemito(Reporte &rep, int tipocopia)
{
        TTable *tabla = static_cast<TTable *>(BD->TableDocumentos);
        TTable *tabladetalles = static_cast<TTable *>(BD->TableDocumentosDetalles);
        AnsiString fecha = tabla->FieldByName("Fecha")->AsDateTime.FormatString("dd/mm/yyyy");
        AnsiString numerodocumento = tabla->FieldByName("NumeroDocumento")->AsInteger;
        AnsiString nombrefactura = tabla->FieldByName("NombreFactura")->AsString;
        AnsiString numerocliente = tabla->FieldByName("NumeroCliente")->AsInteger;
        AnsiString direccion = tabla->FieldByName("Direccion")->AsString;
        AnsiString localidad = tabla->FieldByName("Localidad")->AsString;
        AnsiString provincia = tabla->FieldByName("Provincia")->AsString;
        AnsiString copia[COPIA_N] = {"ORIGINAL", "### DUPLICADO ###"};

        rep << 23 << "DOCUMENTO NO VÁLIDO COMO FACTURA\n\n"
            << nombrefactura << " (" << numerocliente << ")"
            << 58 - nombrefactura.Length() - numerocliente.Length()
            << "NRO: " << numerodocumento << "\n"
            << direccion << 61 - direccion.Length() << "Fecha: " << fecha << "\n"
            << localidad << 61 - localidad.Length() << copia[tipocopia] << 16 - copia[tipocopia].Length() << "\n"
            << provincia << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "Cantidad" << 2 << "Unidad" << 6 << "Descripción" << 25 << "P. Unit."
            << 5 << "Importe\n"
            << AnsiString::StringOfChar('=', 78) << "\n";
        tabladetalles->First();
        AnsiString cantidad, unidad, descripcion, precio, importe;
        while (! tabladetalles->Eof)
        {
                cantidad = tabladetalles->FieldByName("Cantidad")->AsInteger;
                unidad = tabladetalles->FieldByName("Unidad")->AsString;
                descripcion = tabladetalles->FieldByName("Descripcion")->AsString;
                precio = FormatFloat("0.00", tabladetalles->FieldByName("Precio")->AsFloat);
                importe = FormatFloat("0.00", tabladetalles->FieldByName("Importe")->AsFloat);

                rep << cantidad << 10 - cantidad.Length() << unidad << 12 - unidad.Length()
                    << descripcion << 32 - descripcion.Length() << 12 - precio.Length() << precio
                    << 12 - importe.Length() << importe << "\n";
                tabladetalles->Next();
        }
        int renglonesvacios = FormConfiguracion->NumeroRenglones(DOC_REMITO)
                              - tabladetalles->RecordCount;
        for (int c = 0; c < renglonesvacios; c++) rep << "\n";

        AnsiString subtotal = FormatFloat("0.00", tabla->FieldByName("Subtotal")->AsFloat);
        AnsiString descuento = tabla->FieldByName("Descuento")->AsFloat;
        AnsiString descuentototal = FormatFloat("0.00", tabla->FieldByName("DescuentoTotal")->AsFloat);
        AnsiString total = FormatFloat("0.00", tabla->FieldByName("Total")->AsFloat);
        AnsiString comunicado = tabla->FieldByName("Comunicado")->AsString;
        AnsiString comu1 = comunicado.SubString(1, 40);
        AnsiString comu2 = comunicado.SubString(41, 40);
        AnsiString comu3 = comunicado.SubString(81, 40);

        rep << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "\n"
            << 4 << comu1 << 49 - comu1.Length() << "SUBTOTAL: " << 15 - subtotal.Length()
            << subtotal << "\n";

        if (tabla->FieldByName("Descuento")->AsFloat > 0)
        {
                rep << 4 << comu2 << 49 - comu2.Length() << "DESC." << descuento
                    << "%:" << 6 - descuento.Length()
                    << 12 - descuentototal.Length() << descuentototal << "\n";
        }
        else
        {
                rep << 4 << comu2 << "\n";
        }
        rep << 4 << comu3 << 49 - comu3.Length() << "TOTAL:" << 19 - total.Length() << total << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n";
}
//---------------------------------------------------------------------------

void Impresion::InsertarNotaCreditoRemito(Reporte &rep, int tipocopia)
{
        TTable *tabla = static_cast<TTable *>(BD->TableDocumentos);
        TTable *tabladetalles = static_cast<TTable *>(BD->TableDocumentosDetalles);
        AnsiString fecha = tabla->FieldByName("Fecha")->AsDateTime.FormatString("dd/mm/yyyy");
        AnsiString numerodocumento = tabla->FieldByName("NumeroDocumento")->AsInteger;
        AnsiString nombrefactura = tabla->FieldByName("NombreFactura")->AsString;
        AnsiString numerocliente = tabla->FieldByName("NumeroCliente")->AsInteger;
        AnsiString direccion = tabla->FieldByName("Direccion")->AsString;
        AnsiString localidad = tabla->FieldByName("Localidad")->AsString;
        AnsiString provincia = tabla->FieldByName("Provincia")->AsString;
        AnsiString copia[COPIA_N] = {"ORIGINAL", "### DUPLICADO ###"};

        rep << 31 << "NOTA DE CRÉDITO\n\n"
            << nombrefactura << " (" << numerocliente << ")"
            << 58 - nombrefactura.Length() - numerocliente.Length()
            << "NRO: " << numerodocumento << "\n"
            << direccion << 61 - direccion.Length() << "Fecha: " << fecha << "\n"
            << localidad << 61 - localidad.Length() << copia[tipocopia] << 16 - copia[tipocopia].Length() << "\n"
            << provincia << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "Cantidad" << 2 << "Unidad" << 6 << "Descripción" << 25 << "P. Unit."
            << 5 << "Importe\n"
            << AnsiString::StringOfChar('=', 78) << "\n";
        tabladetalles->First();
        AnsiString cantidad, unidad, descripcion, precio, importe;
        while (! tabladetalles->Eof)
        {
                cantidad = tabladetalles->FieldByName("Cantidad")->AsInteger;
                unidad = tabladetalles->FieldByName("Unidad")->AsString;
                descripcion = tabladetalles->FieldByName("Descripcion")->AsString;
                precio = FormatFloat("0.00", tabladetalles->FieldByName("Precio")->AsFloat);
                importe = FormatFloat("0.00", tabladetalles->FieldByName("Importe")->AsFloat);

                rep << cantidad << 10 - cantidad.Length() << unidad << 12 - unidad.Length()
                    << descripcion << 32 - descripcion.Length() << 12 - precio.Length() << precio
                    << 12 - importe.Length() << importe << "\n";
                tabladetalles->Next();
        }
        int renglonesvacios = FormConfiguracion->NumeroRenglones(DOC_REMITO)
                              - tabladetalles->RecordCount;
        for (int c = 0; c < renglonesvacios; c++) rep << "\n";

        AnsiString subtotal = FormatFloat("0.00", tabla->FieldByName("Subtotal")->AsFloat);
        AnsiString descuento = tabla->FieldByName("Descuento")->AsFloat;
        AnsiString descuentototal = FormatFloat("0.00", tabla->FieldByName("DescuentoTotal")->AsFloat);
        AnsiString total = FormatFloat("0.00", tabla->FieldByName("Total")->AsFloat);
        AnsiString comunicado = tabla->FieldByName("Comunicado")->AsString;
        AnsiString comu1 = comunicado.SubString(1, 40);
        AnsiString comu2 = comunicado.SubString(41, 40);
        AnsiString comu3 = comunicado.SubString(81, 40);

        rep << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "\n"
            << 4 << comu1 << 49 - comu1.Length() << "SUBTOTAL: " << 15 - subtotal.Length()
            << subtotal << "\n";

        if (tabla->FieldByName("Descuento")->AsFloat > 0)
        {
                rep << 4 << comu2 << 49 - comu2.Length() << "DESC." << descuento
                    << "%:" << 6 - descuento.Length()
                    << 12 - descuentototal.Length() << descuentototal << "\n";
        }
        else
        {
                rep << 4 << comu2 << "\n";
        }
        rep << 4 << comu3 << 49 - comu3.Length() << "TOTAL:" << 19 - total.Length() << total << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n";
}
//---------------------------------------------------------------------------

void Impresion::InsertarFactura(Reporte &rep)
{
        TTable *tabla = static_cast<TTable *>(BD->TableDocumentos);
        TTable *tabladetalles = static_cast<TTable *>(BD->TableDocumentosDetalles);
        AnsiString fecha = tabla->FieldByName("Fecha")->AsDateTime.FormatString("dd/mm/yyyy");
        AnsiString numerodocumento = tabla->FieldByName("NumeroDocumento")->AsInteger;
        AnsiString nombrefactura = tabla->FieldByName("NombreFactura")->AsString;
        AnsiString numerocliente = tabla->FieldByName("NumeroCliente")->AsInteger;
        AnsiString direccion = tabla->FieldByName("Direccion")->AsString;
        AnsiString localidad = tabla->FieldByName("Localidad")->AsString;
        AnsiString posicionIVA = tabla->FieldByName("PosicionIVA")->AsString;
        AnsiString formapago = tabla->FieldByName("FormaPago")->AsString;
        AnsiString CUIT = tabla->FieldByName("CUIT")->AsString;

        rep << "\n\n\n\n"
            << 41 << "NRO CTRL: " << numerodocumento << 18 - numerodocumento.Length()
            << fecha << "\n"
            << "\n\n\n"
            << "\n\n\n"
            << 9 << nombrefactura << " (" << numerocliente << ")\n"
            << "\n"
            << 9 << direccion << 30 - direccion.Length() << 11 << localidad << "\n"
            << "\n\n"
            << 9 << posicionIVA << 30 - posicionIVA.Length() << 11 << CUIT << "\n"
            << "\n"
            << 9 << formapago << "\n"
            << "\n\n\n\n";

        tabladetalles->First();
        AnsiString cantidad, unidad, descripcion, precio, importe;
        while (! tabladetalles->Eof)
        {
                cantidad = tabladetalles->FieldByName("Cantidad")->AsInteger;
                unidad = tabladetalles->FieldByName("Unidad")->AsString;
                descripcion = tabladetalles->FieldByName("Descripcion")->AsString;
                precio = FormatFloat("0.00", tabladetalles->FieldByName("Precio")->AsFloat);
                importe = FormatFloat("0.00", tabladetalles->FieldByName("Importe")->AsFloat);

                rep << cantidad << 10 - cantidad.Length() << unidad << 12 - unidad.Length()
                    << descripcion << 32 - descripcion.Length() << 12 - precio.Length() << precio
                    << 12 - importe.Length() << importe << "\n";
                tabladetalles->Next();
        }
        int renglonesvacios = FormConfiguracion->NumeroRenglones(DOC_REMITO)
                              - tabladetalles->RecordCount;
        for (int c = 0; c < renglonesvacios; c++) rep << "\n";

        AnsiString subtotal = FormatFloat("0.00", tabla->FieldByName("Subtotal")->AsFloat);
        AnsiString descuento = tabla->FieldByName("Descuento")->AsFloat;
        AnsiString descuentototal = FormatFloat("0.00", tabla->FieldByName("DescuentoTotal")->AsFloat);
        AnsiString subtotal2 = FormatFloat("0.00", tabla->FieldByName("Subtotal2")->AsFloat);
        AnsiString IVA = tabla->FieldByName("IVA")->AsFloat;
        AnsiString IVAtotal = FormatFloat("0.00", tabla->FieldByName("IVATotal")->AsFloat);
        AnsiString total = FormatFloat("0.00", tabla->FieldByName("Total")->AsFloat);
        AnsiString comunicado = tabla->FieldByName("Comunicado")->AsString;
        AnsiString c1 = comunicado.SubString(1, 30);
        AnsiString c2 = comunicado.SubString(31, 30);
        AnsiString c3 = comunicado.SubString(61, 30);
        AnsiString c4 = comunicado.SubString(91, 30);

        rep << "\n\n"
            << 78 - subtotal.Length() << subtotal << "\n";

        if (tabla->FieldByName("IVATotal")->AsFloat > 0) // FACTURA A
        {
                if (tabla->FieldByName("Descuento")->AsFloat > 0)
                {
                        rep << 4 << c1 << 55 - c1.Length() << descuento << "%"
                            << 6 - descuento.Length()
                            << 12 - descuentototal.Length() << descuentototal << "\n";
                }
                else
                {
                        rep << 4 << c1 << "\n";
                }
                rep << 4 << c2 << "\n"
                    << 4 << c3 << 49 - c3.Length() << 25 - subtotal2.Length()
                    << subtotal2 << "\n"
                    << 4 << c4 << 55 - c4.Length() << IVA << "%" << 6 - IVA.Length()
                    << 12 - IVAtotal.Length() << IVAtotal << "\n"
                    << "\n"
                    << 78 - total.Length() << total;
        }
        else // FACTURA B
        {
                rep << 4 << c1 << "\n"
                    << 4 << c2 << "\n"
                    << 4 << c3 << "\n";
                if (tabla->FieldByName("Descuento")->AsFloat > 0)
                {
                        rep << 4 << c4 << 55 - c4.Length() << descuento
                            << "%" << 6 - descuento.Length()
                            << 12 - descuentototal.Length() << descuentototal << "\n";
                }
                else
                {
                        rep << 4 << c4 << "\n";
                }
                rep << "\n"
                    << 78 - total.Length() << total;
        }
}
//---------------------------------------------------------------------------

void Impresion::InsertarNotaCreditoFactura(Reporte &rep)
{
        TTable *tabla = static_cast<TTable *>(BD->TableDocumentos);
        TTable *tabladetalles = static_cast<TTable *>(BD->TableDocumentosDetalles);
        AnsiString fecha = tabla->FieldByName("Fecha")->AsDateTime.FormatString("dd/mm/yyyy");
        AnsiString numerodocumento = tabla->FieldByName("NumeroDocumento")->AsInteger;
        AnsiString nombrefactura = tabla->FieldByName("NombreFactura")->AsString;
        AnsiString numerocliente = tabla->FieldByName("NumeroCliente")->AsInteger;
        AnsiString direccion = tabla->FieldByName("Direccion")->AsString;
        AnsiString localidad = tabla->FieldByName("Localidad")->AsString;
        AnsiString posicionIVA = tabla->FieldByName("PosicionIVA")->AsString;
        AnsiString formapago = tabla->FieldByName("FormaPago")->AsString;
        AnsiString CUIT = tabla->FieldByName("CUIT")->AsString;

        rep << "\n\n\n\n"
            << 41 << "NRO CTRL: " << numerodocumento << 18 - numerodocumento.Length()
            << fecha << "\n"
            << "\n\n\n"
            << "\n\n\n"
            << 9 << nombrefactura << " (" << numerocliente << ")\n"
            << "\n"
            << 9 << direccion << 30 - direccion.Length() << 11 << localidad << "\n"
            << "\n\n"
            << 9 << posicionIVA << 30 - posicionIVA.Length() << 11 << CUIT << "\n"
            << "\n"
            << 9 << formapago << "\n"
            << "\n\n\n\n";

        tabladetalles->First();
        AnsiString cantidad, unidad, descripcion, precio, importe;
        while (! tabladetalles->Eof)
        {
                cantidad = tabladetalles->FieldByName("Cantidad")->AsInteger;
                unidad = tabladetalles->FieldByName("Unidad")->AsString;
                descripcion = tabladetalles->FieldByName("Descripcion")->AsString;
                precio = FormatFloat("0.00", tabladetalles->FieldByName("Precio")->AsFloat);
                importe = FormatFloat("0.00", tabladetalles->FieldByName("Importe")->AsFloat);

                rep << cantidad << 10 - cantidad.Length() << unidad << 12 - unidad.Length()
                    << descripcion << 32 - descripcion.Length() << 12 - precio.Length() << precio
                    << 12 - importe.Length() << importe << "\n";
                tabladetalles->Next();
        }
        int renglonesvacios = FormConfiguracion->NumeroRenglones(DOC_REMITO)
                              - tabladetalles->RecordCount;
        for (int c = 0; c < renglonesvacios; c++) rep << "\n";

        AnsiString subtotal = FormatFloat("0.00", tabla->FieldByName("Subtotal")->AsFloat);
        AnsiString descuento = tabla->FieldByName("Descuento")->AsFloat;
        AnsiString descuentototal = FormatFloat("0.00", tabla->FieldByName("DescuentoTotal")->AsFloat);
        AnsiString subtotal2 = FormatFloat("0.00", tabla->FieldByName("Subtotal2")->AsFloat);
        AnsiString IVA = tabla->FieldByName("IVA")->AsFloat;
        AnsiString IVAtotal = FormatFloat("0.00", tabla->FieldByName("IVATotal")->AsFloat);
        AnsiString total = FormatFloat("0.00", tabla->FieldByName("Total")->AsFloat);
        AnsiString comunicado = tabla->FieldByName("Comunicado")->AsString;
        AnsiString c1 = comunicado.SubString(1, 30);
        AnsiString c2 = comunicado.SubString(31, 30);
        AnsiString c3 = comunicado.SubString(61, 30);
        AnsiString c4 = comunicado.SubString(91, 30);

        rep << "\n\n"
            << 78 - subtotal.Length() << subtotal << "\n";

        if (tabla->FieldByName("IVATotal")->AsFloat > 0) // FACTURA A
        {
                if (tabla->FieldByName("Descuento")->AsFloat > 0)
                {
                        rep << 4 << c1 << 55 - c1.Length() << descuento << "%"
                            << 6 - descuento.Length()
                            << 12 - descuentototal.Length() << descuentototal << "\n";
                }
                else
                {
                        rep << 4 << c1 << "\n";
                }
                rep << 4 << c2 << "\n"
                    << 4 << c3 << 49 - c3.Length() << 25 - subtotal2.Length()
                    << subtotal2 << "\n"
                    << 4 << c4 << 55 - c4.Length() << IVA << "%" << 6 - IVA.Length()
                    << 12 - IVAtotal.Length() << IVAtotal << "\n"
                    << "\n"
                    << 78 - total.Length() << total;
        }
        else // FACTURA B
        {
                rep << 4 << c1 << "\n"
                    << 4 << c2 << "\n"
                    << 4 << c3 << "\n";
                if (tabla->FieldByName("Descuento")->AsFloat > 0)
                {
                        rep << 4 << c4 << 55 - c4.Length() << descuento
                            << "%" << 6 - descuento.Length()
                            << 12 - descuentototal.Length() << descuentototal << "\n";
                }
                else
                {
                        rep << 4 << c4 << "\n";
                }
                rep << "\n"
                    << 78 - total.Length() << total;
        }
}
//---------------------------------------------------------------------------

void Impresion::InsertarProductos(Reporte &rep)
{
        TTable *tabla = BD->TableProductos;
        TDateTime t;

        rep << "\n\n"
            << "PRODUCTOS" << 53 << t.CurrentDateTime().FormatString("dd/mm/yyyy hh:nn") << "\n"
            << "\n\n\n\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "DESCRIPCION" << 28 << "UNIDAD" << 27 << "PRECIO\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "\n";
        TBookmark actual = tabla->GetBookmark();
        tabla->DisableControls();
        tabla->First();
        AnsiString descripcion, unidad, precio;
        while (! tabla->Eof)
        {
                descripcion = tabla->FieldByName("Descripcion")->AsString;
                unidad = tabla->FieldByName("Unidad")->AsString;
                precio = FormatFloat("0.00", tabla->FieldByName("Precio3")->AsFloat);

                rep << descripcion << 39 - descripcion.Length()
                    << unidad << 25 - unidad.Length()
                    << 14 - precio.Length() << precio << "\n";
                tabla->Next();
        }
        rep << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n";
        tabla->GotoBookmark(actual);
        tabla->FreeBookmark(actual);
        tabla->EnableControls();
        rep << "\n";
}
//---------------------------------------------------------------------------

void Impresion::InsertarListaPrecios(Reporte &rep)
{
        TTable *tabla = BD->TableProductos;
        AnsiString index = tabla->IndexName;

        rep << "DESCRIPCION" << 28 << "UNIDAD" << 27 << "PRECIO\n\n";
        TBookmark actual = tabla->GetBookmark();
        tabla->DisableControls();
        tabla->IndexName = "ISFamiliaDescUnidad";
        tabla->First();
        AnsiString descripcion, unidad, precio;
        AnsiString familia = tabla->FieldByName("Familia")->AsString;
        AnsiString tmp;
        rep << familia << "\n";
        while (! tabla->Eof)
        {
                tmp = tabla->FieldByName("Familia")->AsString;
                if (familia != tmp)
                {
                        familia = tmp;
                        rep << "\n" << familia << "\n";
                }
                descripcion = tabla->FieldByName("Descripcion")->AsString;
                unidad = tabla->FieldByName("Unidad")->AsString;
                precio = FormatFloat("0.00", tabla->FieldByName("Precio3")->AsFloat);

                rep << descripcion << 39 - descripcion.Length()
                    << unidad << 25 - unidad.Length()
                    << 14 - precio.Length() << precio << "\n";
                tabla->Next();
        }

        tabla->IndexName = index;
        tabla->GotoBookmark(actual);
        tabla->FreeBookmark(actual);
        tabla->EnableControls();
}
//---------------------------------------------------------------------------

void Impresion::InsertarSaldos(Reporte &rep)
{
        TTable *tabla = BD->TableClientes;
        AnsiString index = tabla->IndexName;
        TDateTime t;

        rep << "\n\n"
            << "SALDOS" << 56 << t.CurrentDateTime().FormatString("dd/mm/yyyy hh:nn") << "\n"
            << "\n\n\n\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "NOMBRE CLIENTE" << 18 << "NOMBRE NEGOCIO" << 27 << "SALDO" << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "\n";
        TBookmark actual = tabla->GetBookmark();
        tabla->DisableControls();
        tabla->IndexName = "ISNombreFactura";
        tabla->First();
        AnsiString numerocliente, nombrecliente, nombrenegocio, saldo, saldototal;
        double _saldo, _saldototal = 0;
        while (! tabla->Eof)
        {
                nombrecliente = tabla->FieldByName("NombreCliente")->AsString;
                nombrenegocio = tabla->FieldByName("NombreNegocio")->AsString;
                double _saldo = tabla->FieldByName("SaldoCC")->AsFloat;
                _saldototal += _saldo;
                saldo = FormatFloat("0.00", _saldo);

                rep << nombrecliente << 32 - nombrecliente.Length()
                    << nombrenegocio << 32 - nombrenegocio.Length()
                    << 14 - saldo.Length() << saldo << "\n";
                tabla->Next();
        }
        tabla->IndexName = index;
        tabla->GotoBookmark(actual);
        tabla->FreeBookmark(actual);
        tabla->EnableControls();
        saldototal = FormatFloat("0.00", _saldototal);
        rep << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "\n"
            << 51 << "SALDO TOTAL: " << 14 - saldototal.Length() << saldototal << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n";
}
//---------------------------------------------------------------------------

void Impresion::InsertarCuentaCorriente(Reporte &rep, int desde)
{
        TTable *tabla = static_cast<TTable *>(BD->TableClientes);
        AnsiString numerocliente = tabla->FieldByName("NumeroCliente")->AsInteger;
        AnsiString nombrefactura = tabla->FieldByName("NombreFactura")->AsString;
        AnsiString direccion = tabla->FieldByName("Direccion")->AsString;
        AnsiString localidad = tabla->FieldByName("Localidad")->AsString;
        AnsiString provincia = tabla->FieldByName("Provincia")->AsString;
        TDateTime t;

        rep << nombrefactura << " (" << numerocliente << ")"
            << 58 - nombrefactura.Length() - numerocliente.Length()
            << "Fecha: " << t.CurrentDateTime().FormatString("dd/mm/yyyy") << "\n"
            << direccion << 61 - direccion.Length() << "\n"
            << localidad << 61 - localidad.Length() << "\n"
            << provincia << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "Fecha" << 29 << "Debe" << 15 << "Haber" << 7 << "Saldo parcial" << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n";

        tabla = static_cast<TTable *>(BD->TableCuentasCorrientes);
        TBookmark actual = tabla->GetBookmark();
        tabla->DisableControls();
        int numeroregistro;
        AnsiString fecha, debe, haber, saldoparcial;
        int cantidad = 0;
        tabla->RecNo = desde;
        while (cantidad <= tabla->RecordCount - desde)
        {
                fecha = tabla->FieldByName("Fecha")->AsDateTime.FormatString("dd/mm/yyyy");
                debe = FormatFloat("0.00", tabla->FieldByName("Debe")->AsFloat);
                haber = FormatFloat("0.00", tabla->FieldByName("Haber")->AsFloat);
                saldoparcial = FormatFloat("0.00", tabla->FieldByName("SaldoParcial")->AsFloat);

                rep << fecha << 18 - fecha.Length() << 20 - debe.Length() << debe
                    << 20 - haber.Length() << haber
                    << 20 - saldoparcial.Length() << saldoparcial << "\n";
                tabla->Next();
                cantidad++;
        }
        int renglonesvacios = FormConfiguracion->CantidadImprimirCC()
                              - cantidad;
        for (int c = 0; c < renglonesvacios; c++) rep << "\n";

        AnsiString saldo = FormatFloat("0.00", tabla->FieldByName("SaldoParcial")->AsFloat);

        rep << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "\n"
            << 56 << "SALDO: " << 15 - saldo.Length() << saldo << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n";

        tabla->GotoBookmark(actual);
        tabla->FreeBookmark(actual);
        tabla->EnableControls();
}
//---------------------------------------------------------------------------

void Impresion::InsertarRegistroDocumentos(Reporte &rep, TDate desde, TDate hasta)
{
        TTable *tabla = BD->TableDocumentos;
        TDateTime t;
        AnsiString DOCUMENTOS[DOC_N] = {"Remito", "Factura", "Credito", "Credito", "Factura", "Credito", "Debito", "Pedido"};
        AnsiString ESTADOS[EST_N] = {"Impreso", "Sin imp", "Anulado"};
        AnsiString index = tabla->IndexName;

        TFilterOptions FilterOptions;
        FilterOptions.Clear();
        FilterOptions << foCaseInsensitive;
        AnsiString filtro = "Fecha >= '" + desde.DateString() + "' AND Fecha <= '"
                          + hasta.DateString() + "'";

        rep << "\n\n"
            << "REGISTRO DE DOCUMENTOS" << 40 << t.CurrentDateTime().FormatString("dd/mm/yyyy hh:nn") << "\n"
            << "\n\n\n\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "FECHA" << 8 << "T. DOC." << 3 << "NOMBRE FACTURA" << 27 << "TOTAL" << 2 << "ESTADO" << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "\n";

        TBookmark actual = tabla->GetBookmark();
        tabla->DisableControls();
        tabla->IndexName = "ISFechaHora";
        tabla->Filter = filtro;
        tabla->FilterOptions = FilterOptions;
        tabla->Filtered = true;
        tabla->First();

        AnsiString fecha, tipodocumento, nombrefactura, total, estado;
        while (! tabla->Eof)
        {
                fecha = tabla->FieldByName("Fecha")->AsDateTime.FormatString("dd/mm/yyyy");
                tipodocumento = DOCUMENTOS[tabla->FieldByName("TipoDocumento")->AsInteger];
                nombrefactura = tabla->FieldByName("NombreFactura")->AsString;
                total = FormatFloat("0.00", tabla->FieldByName("Total")->AsFloat);
                estado = ESTADOS[tabla->FieldByName("Estado")->AsInteger];

                rep << fecha << 13 - fecha.Length()
                    << tipodocumento << 10 - tipodocumento.Length()
                    << nombrefactura << 32 - nombrefactura.Length()
                    << 14 - total.Length() << total
                    << 2 << estado << "\n";
                tabla->Next();
        }
        rep << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n";

        tabla->Filtered = false;
        tabla->IndexName = index;
        tabla->GotoBookmark(actual);
        tabla->FreeBookmark(actual);
        tabla->EnableControls();
}
//---------------------------------------------------------------------------

void Impresion::InsertarRegistroVentasDiario(Reporte &rep, TDate desde, TDate hasta)
{
        TTable *tabla = BD->TableVentasDiario;
        TDateTime t;
        AnsiString index = tabla->IndexName;

        TFilterOptions FilterOptions;
        FilterOptions.Clear();
        FilterOptions << foCaseInsensitive;
        AnsiString filtro = "Fecha >= '" + desde.DateString() + "' AND Fecha <= '"
                          + hasta.DateString() + "'";

        rep << "\n\n"
            << "REGISTRO DIARIO DE VENTAS" << 37 << t.CurrentDateTime().FormatString("dd/mm/yyyy hh:nn") << "\n"
            << "\n\n\n\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "FECHA" << 20 << "MONTO REMITOS" << 6 << "MONTO FACTURAS" << 9 << "MONTO TOTAL" << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "\n";

        TBookmark actual = tabla->GetBookmark();
        tabla->DisableControls();
        tabla->IndexName = "ISFecha";
        tabla->Filter = filtro;
        tabla->FilterOptions = FilterOptions;
        tabla->Filtered = true;
        tabla->First();

        AnsiString fecha, montoremito, montofactura, montototal;
        while (! tabla->Eof)
        {
                fecha = tabla->FieldByName("Fecha")->AsDateTime.FormatString("dd/mm/yyyy");
                montoremito = FormatFloat("0.00", tabla->FieldByName("MontoRemitos")->AsFloat);
                montofactura = FormatFloat("0.00", tabla->FieldByName("MontoFacturas")->AsFloat);
                montototal = FormatFloat("0.00", tabla->FieldByName("MontoTotal")->AsFloat);

                rep << fecha << 18 - fecha.Length()
                    << 20 - montoremito.Length() << montoremito
                    << 20 - montofactura.Length() << montofactura
                    << 20 - montototal.Length() << montototal << "\n";
                tabla->Next();
        }
        rep << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n";

        tabla->Filtered = false;
        tabla->IndexName = index;
        tabla->GotoBookmark(actual);
        tabla->FreeBookmark(actual);
        tabla->EnableControls();
}
//---------------------------------------------------------------------------

void Impresion::InsertarPlanillaProductos(Reporte &rep, TDate desde, TDate hasta)
{
        TTable *tabla = static_cast<TTable *>(BD->TableDocumentos);
        TTable *tabladetalles = static_cast<TTable *>(BD->TableDocumentosDetalles);
        TDateTime t;
        AnsiString fecha, nombrefactura, cantidad, descripcion, unidad, direccion;
        AnsiString index = tabla->IndexName;
        TDate lote;

        TFilterOptions FilterOptions;
        FilterOptions.Clear();
        FilterOptions << foCaseInsensitive;
        AnsiString filtro = "Fecha >= '" + desde.DateString() + "' AND Fecha <= '"
                          + hasta.DateString() + "' AND Estado <> '"
                          + EST_ANULADO + "' AND (TipoDocumento = '"
                          + DOC_FACTURA + "' OR TipoDocumento = '"
                          + DOC_FACTURAELECT + "')";

        rep << "FECHA" << 8 << "NOMBRE FACTURA" << 19 << "DIRECCION" << 24 << "CANTIDAD" << 5 << "UNIDAD" << 7 << "DESCRIPCION" << 22 << "LOTE" << "\n\n";

        // Disablecontrols me deshabilita la tabla detalle
        //tabla->BlockReadSize = 32;
        TBookmark actual = tabla->GetBookmark();
        tabla->IndexName = "ISFechaHora";
        tabla->Filter = filtro;
        tabla->FilterOptions = FilterOptions;
        tabla->Filtered = true;
        tabla->First();
        while (! tabla->Eof)
        {
                fecha = tabla->FieldByName("Fecha")->AsDateTime.FormatString("dd/mm/yyyy");
                nombrefactura = tabla->FieldByName("NombreFactura")->AsString;
                direccion = tabla->FieldByName("Direccion")->AsString;
                tabladetalles->First();
                while (! tabladetalles->Eof)
                {
                        cantidad = tabladetalles->FieldByName("Cantidad")->AsInteger;
                        unidad = tabladetalles->FieldByName("Unidad")->AsString;
                        descripcion = tabladetalles->FieldByName("Descripcion")->AsString;
                        lote = StrToDate(fecha) - rand() % 8;
                        rep << fecha << 13 - fecha.Length()
                            << nombrefactura << 33 - nombrefactura.Length()
                            << direccion << 33 - direccion.Length()
                            << cantidad << 13 - cantidad.Length()
                            << unidad << 13 - unidad .Length()
                            << descripcion << 33 - descripcion.Length()
                            << lote.DateString()
                            << "\n";
                        tabladetalles->Next();
                }
                tabla->Next();
        }

        tabla->Filtered = false;
        tabla->IndexName = index;
        tabla->GotoBookmark(actual);
        tabla->FreeBookmark(actual);
        //tabla->BlockReadSize = 0;
}
//---------------------------------------------------------------------------

void Impresion::InsertarRegistroProductosStock(Reporte &rep)
{
        TTable *tabla = BD->TableProductos;
        TDateTime t;

        rep << "\n\n"
            << "REGISTRO STOCK DE PRODUCTOS" << 35 << t.CurrentDateTime().FormatString("dd/mm/yyyy hh:nn") << "\n"
            << "\n\n\n\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "DESCRIPCION" << 27 << "UNIDAD" << 26 << "CANTIDAD" << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "\n";

        TBookmark actual = tabla->GetBookmark();
        tabla->DisableControls();
        tabla->First();
        AnsiString descripcion, unidad, cantidad;
        while (! tabla->Eof)
        {
                descripcion = tabla->FieldByName("Descripcion")->AsString;
                unidad = tabla->FieldByName("Unidad")->AsString;
                cantidad = tabla->FieldByName("Stock")->AsString;

                rep << descripcion << 38 - descripcion.Length()
                    << unidad << 20 - unidad.Length()
                    << 20 - cantidad.Length() << cantidad << "\n";
                tabla->Next();
        }
        rep << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n";
        tabla->GotoBookmark(actual);
        tabla->FreeBookmark(actual);
        tabla->EnableControls();
        rep << "\n";
}
//---------------------------------------------------------------------------

void Impresion::InsertarRegistroVentas(Reporte &rep1, Reporte &rep2, Reporte &rep3,
                                       TDate desde, TDate hasta)
{
        TTable *tabla = BD->TableDocumentos;
        TDateTime t;
        AnsiString index = tabla->IndexName;
        double monotributo = 0, inscripto = 0;

        TFilterOptions FilterOptions;
        FilterOptions.Clear();
        FilterOptions << foCaseInsensitive;
        AnsiString filtro = "Fecha >= '" + desde.DateString() + "' AND Fecha <= '"
                          + hasta.DateString() + "' AND Estado <> '" + EST_ANULADO + "'";

        TBookmark actual = tabla->GetBookmark();
        //tabla->DisableControls();
        tabla->IndexName = "ISFechaHora";
        tabla->Filter = filtro;
        tabla->FilterOptions = FilterOptions;
        tabla->Filtered = true;

        tabla->First();
        while (! tabla->Eof)
        {
                FE fe;
                int tipodocumento = tabla->FieldByName("TipoDocumento")->AsInteger;

                if (! (tipodocumento == DOC_FACTURA ||
                       tipodocumento == DOC_FACTURAELECT ||
                       tipodocumento == DOC_CREDITOELECT ||
                       tipodocumento == DOC_DEBITOELECT))
                {
                        tabla->Next();
                        continue;
                }

                try
                {
                        FormFacturacion->CargarFE(fe);
                }
                catch(...)
                {
                        tabla->Next();
                        continue;
                }

                AnsiString nombre = tabla->FieldByName("NombreFactura")->AsString.SubString(1,30);
                double nro_doc;
                try
                {
                        nro_doc = SinGuiones(fe.nro_doc).ToDouble();
                }
                catch(...)
                {
                        nro_doc = 0;
                }
                int numerocomprobante;
                int punto_vta;
                if (tipodocumento == DOC_FACTURA)
                {
                        numerocomprobante = BD->TableFacturaTradicional->FieldByName("Cbte_nro")->AsInteger;
                        punto_vta = 1; // factura pre-impresa
                }
                else if (tipodocumento == DOC_FACTURAELECT ||
                         tipodocumento == DOC_CREDITOELECT ||
                         tipodocumento == DOC_DEBITOELECT)
                {
                        numerocomprobante = BD->TableFacturaElectronica->FieldByName("Cbte_nro")->AsInteger;
                        punto_vta = afip->punto_vta;
                }

                rep1 << fe.fecha_cbte.FormatString("yyyymmdd")
                     << FormatFloat("000", fe.tipo_cbte)
                     << FormatFloat("00000", punto_vta)
                     << FormatFloat(AnsiString::StringOfChar('0', 20), numerocomprobante)
                     << FormatFloat(AnsiString::StringOfChar('0', 20), numerocomprobante)
                     << AnsiString(80)
                     << FormatFloat(AnsiString::StringOfChar('0', 20), nro_doc)
                     << nombre << 30 - nombre.Length()
                     << FormatFloat(AnsiString::StringOfChar('0', 15), fe.imp_total * 100)
                     << AnsiString::StringOfChar('0', 15)
                     << AnsiString::StringOfChar('0', 15)
                     << AnsiString::StringOfChar('0', 15)
                     << AnsiString::StringOfChar('0', 15)
                     << AnsiString::StringOfChar('0', 15)
                     << AnsiString::StringOfChar('0', 15)
                     << AnsiString::StringOfChar('0', 15)
                     << "PES"
                     << "0001000000"
                     << AnsiString(1)
                     << AnsiString(0)
                     << AnsiString::StringOfChar('0', 15)
                     << AnsiString::StringOfChar('0', 8)
                     << "\n";

                rep2 << FormatFloat("000", fe.tipo_cbte)
                     << FormatFloat("00000", punto_vta)
                     << FormatFloat(AnsiString::StringOfChar('0', 20), numerocomprobante)
                     << FormatFloat(AnsiString::StringOfChar('0', 15), fe.imp_neto * 100)
                     << "0005"
                     << FormatFloat(AnsiString::StringOfChar('0', 15), fe.imp_iva * 100)
                     << "\n";

                switch(tipodocumento)
                {
                  case DOC_FACTURA:
                  case DOC_FACTURAELECT:
                  case DOC_DEBITOELECT:
                        if (fe.id_impositivo == "Responsable monotributo")
                        {
                                monotributo += fe.imp_total;
                        }
                        else if (fe.id_impositivo == "Responsable inscripto")
                        {
                                inscripto += fe.imp_total;
                        }
                  break;
                  case DOC_CREDITOELECT:
                        if (fe.id_impositivo == "Responsable monotributo")
                        {
                                monotributo -= fe.imp_total;
                        }
                        else if (fe.id_impositivo == "Responsable inscripto")
                        {
                                inscripto -= fe.imp_total;
                        }
                  break;
                }

                tabla->Next();
        }

        rep3 << "Responsable monotributo: " << FormatFloat("0.00", monotributo)
             << "\n"
             << "Responsable inscripto: " << FormatFloat("0.00", inscripto)
             << "\n"
             << "Total: " << FormatFloat("0.00", monotributo + inscripto)
             << "\n";

        tabla->Filtered = false;
        tabla->IndexName = index;
        tabla->GotoBookmark(actual);
        tabla->FreeBookmark(actual);
        //tabla->EnableControls();
}
//---------------------------------------------------------------------------

void Impresion::InsertarPedido(Reporte &rep)
{
        TTable *tabla = static_cast<TTable *>(BD->TableDocumentos);
        TTable *tabladetalles = static_cast<TTable *>(BD->TableDocumentosDetalles);
        AnsiString fecha = tabla->FieldByName("Fecha")->AsDateTime.FormatString("dd/mm/yyyy");
        AnsiString numerodocumento = tabla->FieldByName("NumeroDocumento")->AsInteger;
        AnsiString nombrefactura = tabla->FieldByName("NombreFactura")->AsString;
        AnsiString numerocliente = tabla->FieldByName("NumeroCliente")->AsInteger;
        AnsiString direccion = tabla->FieldByName("Direccion")->AsString;
        AnsiString localidad = tabla->FieldByName("Localidad")->AsString;
        AnsiString provincia = tabla->FieldByName("Provincia")->AsString;

        rep << 33 << "PEDIDO INTERNO\n\n"
            << nombrefactura << " (" << numerocliente << ")"
            << 58 - nombrefactura.Length() - numerocliente.Length()
            << "NRO: " << numerodocumento << "\n"
            << direccion << 61 - direccion.Length() << "Fecha: " << fecha << "\n"
            << localidad << 61 - localidad.Length() << "\n"
            << provincia << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "Cantidad" << 2 << "Unidad" << 6 << "Descripción" << 25 << "P. Unit."
            << 5 << "Importe\n"
            << AnsiString::StringOfChar('=', 78) << "\n";
        tabladetalles->First();
        AnsiString cantidad, unidad, descripcion, precio, importe;
        while (! tabladetalles->Eof)
        {
                cantidad = tabladetalles->FieldByName("Cantidad")->AsInteger;
                unidad = tabladetalles->FieldByName("Unidad")->AsString;
                descripcion = tabladetalles->FieldByName("Descripcion")->AsString;
                precio = FormatFloat("0.00", tabladetalles->FieldByName("Precio")->AsFloat);
                importe = FormatFloat("0.00", tabladetalles->FieldByName("Importe")->AsFloat);

                rep << cantidad << 10 - cantidad.Length() << unidad << 12 - unidad.Length()
                    << descripcion << 32 - descripcion.Length() << 12 - precio.Length() << precio
                    << 12 - importe.Length() << importe << "\n";
                tabladetalles->Next();
        }
        int renglonesvacios = FormConfiguracion->NumeroRenglones(DOC_PEDIDO)
                              - tabladetalles->RecordCount;
        for (int c = 0; c < renglonesvacios; c++) rep << "\n";

        AnsiString subtotal = FormatFloat("0.00", tabla->FieldByName("Subtotal")->AsFloat);
        AnsiString descuento = tabla->FieldByName("Descuento")->AsFloat;
        AnsiString descuentototal = FormatFloat("0.00", tabla->FieldByName("DescuentoTotal")->AsFloat);
        AnsiString total = FormatFloat("0.00", tabla->FieldByName("Total")->AsFloat);
        AnsiString comunicado = tabla->FieldByName("Comunicado")->AsString;
        AnsiString comu1 = comunicado.SubString(1, 40);
        AnsiString comu2 = comunicado.SubString(41, 40);
        AnsiString comu3 = comunicado.SubString(81, 40);

        rep << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n"
            << "\n"
            << 4 << comu1 << 49 - comu1.Length() << "SUBTOTAL: " << 15 - subtotal.Length()
            << subtotal << "\n";

        if (tabla->FieldByName("Descuento")->AsFloat > 0)
        {
                rep << 4 << comu2 << 49 - comu2.Length() << "DESC." << descuento
                    << "%:" << 6 - descuento.Length()
                    << 12 - descuentototal.Length() << descuentototal << "\n";
        }
        else
        {
                rep << 4 << comu2 << "\n";
        }
        rep << 4 << comu3 << 49 - comu3.Length() << "TOTAL:" << 19 - total.Length() << total << "\n"
            << AnsiString::StringOfChar('=', 78) << "\n";
}
//---------------------------------------------------------------------------

void Impresion::MostrarDoc(int tipodocumento)
{
        TTable *tabla = static_cast<TTable *>(BD->TableDocumentos);

        switch(tipodocumento)
        {
          case DOC_REMITO:
          {
                Reporte rep;
                InsertarRemito(rep, COPIA_ORIGINAL);
                rep.Mostrar();
          }
          break;
          case DOC_CREDITOREMITO:
          {
                Reporte rep;
                InsertarNotaCreditoRemito(rep, COPIA_ORIGINAL);
                rep.Mostrar();
          }
          break;
          case DOC_FACTURA:
          {
                Reporte rep;
                if (tabla->FieldByName("IVATotal")->AsFloat > 0) // FACTURA A
                {
                        rep.Imagen("plantillas\\factura_a.bmp");
                }
                else // FACTURA B
                {
                       rep.Imagen("plantillas\\factura_b.bmp");

                }
                InsertarFactura(rep);
                rep.Mostrar();
          }
          break;
          case DOC_CREDITOFACTURA:
          {
                Reporte rep;
                InsertarNotaCreditoFactura(rep);
                rep.Mostrar();
          }
          break;
          case DOC_FACTURAELECT:
          case DOC_CREDITOELECT:
          case DOC_DEBITOELECT:
          {
                  FE fe;
                  AnsiString fichpdf = GetTempDir() + "\\factura.pdf";

                  FormFacturacion->CargarFE(fe);
                  FormFacturacion->CargarDatosFE(fe);
                  try
                  {
                        afip->GenerarPDF(fe, fichpdf);
                  }
                  catch(...)
                  {
                        Abort();
                  }
                  FormImpresion->OleContainer->CreateObjectFromFile(fichpdf, false);
                  FormImpresion->OleContainer->Visible = true;
                  FormImpresion->Image->Visible = false;
                  FormImpresion->ToolButtonGuardarBMP->Visible = false;
                  FormImpresion->ToolButtonGuardarPDF->Visible = true;
                  FormImpresion->ShowModal();
          break;
          }
          case DOC_PEDIDO:
          {
                Reporte rep;
                InsertarPedido(rep);
                rep.Mostrar();
          }
          break;
        }
}
//---------------------------------------------------------------------------

void Impresion::ImprimirDoc(int tipodocumento)
{
        Reporte rep;

        switch(tipodocumento)
        {
          case DOC_REMITO:
          {
                InsertarRemito(rep, COPIA_ORIGINAL);
                for (int a = 0; a < FormConfiguracion->EspaciosPosteriorRO(); a++)
                {
                        rep << "\n";
                }
                if (FormConfiguracion->ImprimirDuplicadoRemito())
                {
                        InsertarRemito(rep, COPIA_DUPLICADO);
                        for (int a = 0; a < FormConfiguracion->EspaciosPosteriorRD(); a++)
                        {
                                rep << "\n";
                        }
                }
                rep.Imprimir(FormConfiguracion->Impresora(IMP_REMITO),
                             Application->Title + " - Remito",
                             FormConfiguracion->ModoRAW(IMP_REMITO));
          }
          break;
          case DOC_CREDITOREMITO:
          {
                InsertarNotaCreditoRemito(rep, COPIA_ORIGINAL);
                for (int a = 0; a < FormConfiguracion->EspaciosPosteriorRO(); a++)
                {
                        rep << "\n";
                }
                if (FormConfiguracion->ImprimirDuplicadoRemito())
                {
                        InsertarNotaCreditoRemito(rep, COPIA_DUPLICADO);
                        for (int a = 0; a < FormConfiguracion->EspaciosPosteriorRD(); a++)
                        {
                                rep << "\n";
                        }
                }
                rep.Imprimir(FormConfiguracion->Impresora(IMP_REMITO),
                             Application->Title + " - Nota de crédito (remito)",
                             FormConfiguracion->ModoRAW(IMP_REMITO));
          }
          break;
          case DOC_FACTURA:
          {
                InsertarFactura(rep);
                for (int a = 0; a < FormConfiguracion->EspaciosPosteriorFO(); a++)
                {
                        rep << "\n";
                }
                InsertarFactura(rep);
                for (int a = 0; a < FormConfiguracion->EspaciosPosteriorFD(); a++)
                {
                        rep << "\n";
                }
                rep.Imprimir(FormConfiguracion->Impresora(IMP_FACTURA),
                             Application->Title + " - Factura",
                             FormConfiguracion->ModoRAW(IMP_FACTURA));
          }
          break;
          case DOC_CREDITOFACTURA:
          {
                InsertarNotaCreditoFactura(rep);
                for (int a = 0; a < FormConfiguracion->EspaciosPosteriorFO(); a++)
                {
                        rep << "\n";
                }
                InsertarNotaCreditoFactura(rep);
                for (int a = 0; a < FormConfiguracion->EspaciosPosteriorFD(); a++)
                {
                        rep << "\n";
                }
                rep.Imprimir(FormConfiguracion->Impresora(IMP_FACTURA),
                             Application->Title + " - Nota de crédito (factura)",
                             FormConfiguracion->ModoRAW(IMP_FACTURA));
          }
          break;
          case DOC_FACTURAELECT:
          case DOC_CREDITOELECT:
          case DOC_DEBITOELECT:
          {
                  FE fe;
                  AnsiString fichpdf = GetTempDir() + "\\factura.pdf";

                  FormFacturacion->CargarFE(fe);
                  FormFacturacion->CargarDatosFE(fe);
                  try
                  {
                        afip->GenerarPDF(fe, fichpdf);
                  }
                  catch(...)
                  {
                        Abort();
                  }

                  ShellExecute(NULL, "print", fichpdf.c_str(), NULL, NULL, SW_HIDE);
          }
          break;
          case DOC_PEDIDO:
          {
                InsertarPedido(rep);
                for (int a = 0; a < FormConfiguracion->EspaciosPosteriorPedido(); a++)
                {
                        rep << "\n";
                }
                rep.Imprimir(FormConfiguracion->Impresora(IMP_PEDIDO),
                             Application->Title + " - Pedido",
                             FormConfiguracion->ModoRAW(IMP_PEDIDO));
          }
          break;
        }
}
//---------------------------------------------------------------------------

void Impresion::ImprimirDocumento(int tipodocumento, bool vistaprevia)
{
        if (vistaprevia)
        {
                MostrarDoc(tipodocumento);
        }
        else
        {
                ImprimirDoc(tipodocumento);
        }
}
//---------------------------------------------------------------------------

void Impresion::ImprimirProductos(bool vistaprevia)
{
        Reporte rep;

        InsertarProductos(rep);
        if (vistaprevia)
        {
                rep.Mostrar();
        }
        else
        {
                rep.Imprimir(FormConfiguracion->Impresora(IMP_PRODUCTOS),
                             Application->Title + " - Productos",
                             FormConfiguracion->ModoRAW(IMP_PRODUCTOS));
        }
}
//---------------------------------------------------------------------------

void Impresion::ImprimirSaldos(bool vistaprevia)
{
        Reporte rep;

        InsertarSaldos(rep);
        if (vistaprevia)
        {
                rep.Mostrar();
        }
        else
        {
                rep.Imprimir(FormConfiguracion->Impresora(IMP_SALDOS),
                             Application->Title + " - Saldos",
                             FormConfiguracion->ModoRAW(IMP_SALDOS));
        }
}
//---------------------------------------------------------------------------

void Impresion::ImprimirCuentaCorriente(int desde, bool vistaprevia)
{
        Reporte rep;

        InsertarCuentaCorriente(rep, desde);
        if (vistaprevia)
        {
                rep.Mostrar();
        }
        else
        {
                for (int a = 0; a < FormConfiguracion->EspaciosPosteriorCC(); a++)
                {
                        rep << "\n";
                }
                rep.Imprimir(FormConfiguracion->Impresora(IMP_CUENTA),
                             Application->Title + " - Cuenta corriente",
                             FormConfiguracion->ModoRAW(IMP_CUENTA));
        }
}
//---------------------------------------------------------------------------

void Impresion::ImprimirRegistroDocumentos(TDate desde, TDate hasta, bool vistaprevia)
{
        Reporte rep;

        InsertarRegistroDocumentos(rep, desde, hasta);
        if (vistaprevia)
        {
                rep.Mostrar();
        }
        else
        {
                rep.Imprimir(FormConfiguracion->Impresora(IMP_REGISTROS),
                             Application->Title + " - Registro de documentos",
                             FormConfiguracion->ModoRAW(IMP_REGISTROS));
        }
}
//---------------------------------------------------------------------------

void Impresion::ImprimirRegistroVentasDiario(TDate desde, TDate hasta, bool vistaprevia)
{
        Reporte rep;

        InsertarRegistroVentasDiario(rep, desde, hasta);
        if (vistaprevia)
        {
                rep.Mostrar();
        }
        else
        {
                rep.Imprimir(FormConfiguracion->Impresora(IMP_REGISTROS),
                             Application->Title + " - Registro diario de ventas",
                             FormConfiguracion->ModoRAW(IMP_REGISTROS));
        }
}
//---------------------------------------------------------------------------

void Impresion::ImprimirRegistroProductosStock(bool vistaprevia)
{
        Reporte rep;

        InsertarRegistroProductosStock(rep);
        if (vistaprevia)
        {
                rep.Mostrar();
        }
        else
        {
                rep.Imprimir(FormConfiguracion->Impresora(IMP_REGISTROS),
                             Application->Title + " - Registro stock de productos",
                             FormConfiguracion->ModoRAW(IMP_REGISTROS));
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormImpresion::FormResize(TObject *Sender)
{
        TControl *visor;

        if (Image->Visible == true)
        {
                visor = Image;
        }
        else
        {
                visor = OleContainer;
        }

        if (FormImpresion->ClientHeight > visor->Height)
        {
                visor->Top = (FormImpresion->ClientHeight - visor->Height) / 2;
        }
        else
        {
                visor->Top = 0;
        }
        if (FormImpresion->ClientWidth > visor->Width)
        {
                visor->Left = (FormImpresion->ClientWidth - visor->Width) / 2;
        }
        else
        {
                visor->Left = 0;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormImpresion::FormShow(TObject *Sender)
{
        FormImpresion->AutoScroll = false;
        FormResize(this);
        FormImpresion->AutoScroll = true;
}
//---------------------------------------------------------------------------

void Impresion::ExportarSaldos(AnsiString fichero)
{
        Reporte rep;

        InsertarSaldos(rep);
        rep.ExportarTexto(fichero);
}
//---------------------------------------------------------------------------

void Impresion::ExportarListaPrecios(AnsiString fichero)
{
        Reporte rep;

        InsertarListaPrecios(rep);
        rep.ExportarTexto(fichero);
}
//---------------------------------------------------------------------------

void Impresion::ExportarPlanillaProductos(TDate desde, TDate hasta, AnsiString fichero)
{
        Reporte rep;

        InsertarPlanillaProductos(rep, desde, hasta);
        rep.ExportarTexto(fichero);
}
//---------------------------------------------------------------------------

void Impresion::ExportarRegistroVentas(TDate desde, TDate hasta, AnsiString directorio)
{
        Reporte rep1, rep2, rep3;

        InsertarRegistroVentas(rep1, rep2, rep3, desde, hasta);
        rep1.ExportarTexto(directorio + "\\comprobantes.txt");
        rep2.ExportarTexto(directorio + "\\alicuotas.txt");
        rep3.ExportarTexto(directorio + "\\ventas.txt");
}
//---------------------------------------------------------------------------

void __fastcall TFormImpresion::ToolButtonGuardarBMPClick(TObject *Sender)
{
        SaveDialog->DefaultExt = ".bmp";
        SaveDialog->FileName = "remito.bmp";
        SaveDialog->Filter = "Imagen BMP (*.bmp)|*.bmp";
        SaveDialog->Options << ofOverwritePrompt << ofFileMustExist << ofHideReadOnly;

        AnsiString current = GetCurrentDir();
        if (SaveDialog->Execute())
        {
                AnsiString bmp = SaveDialog->FileName;
                Image->Picture->SaveToFile(bmp);
        }
        SetCurrentDir(current);
}
//---------------------------------------------------------------------------

void __fastcall TFormImpresion::ToolButtonGuardarPDFClick(TObject *Sender)
{
        AnsiString fichpdf = GetTempDir() + "\\factura.pdf";

        SaveDialog->DefaultExt = ".pdf";
        SaveDialog->FileName = "factura.pdf";
        SaveDialog->Filter = "Imagen PDF (*.pdf)|*.pdf";
        SaveDialog->Options << ofOverwritePrompt << ofFileMustExist << ofHideReadOnly;

        AnsiString current = GetCurrentDir();
        if (SaveDialog->Execute())
        {
                AnsiString pdf = SaveDialog->FileName;
                CopyFile(fichpdf.c_str(), pdf.c_str(), false);
        }
        SetCurrentDir(current);
}
//---------------------------------------------------------------------------

