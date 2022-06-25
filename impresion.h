//---------------------------------------------------------------------------

#ifndef impresionH
#define impresionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <OleCtnrs.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>

//---------------------------------------------------------------------------
class TFormImpresion : public TForm
{
__published:	// IDE-managed Components
        TImage *Image;
        TSaveDialog *SaveDialog;
        TOleContainer *OleContainer;
        TToolBar *ToolBar;
        TToolButton *ToolButtonGuardarBMP;
        TToolButton *ToolButtonGuardarPDF;
        TImageList *ImageList;
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ToolButtonGuardarBMPClick(TObject *Sender);
        void __fastcall ToolButtonGuardarPDFClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormImpresion(TComponent* Owner);
};


enum {
        COPIA_ORIGINAL,
        COPIA_DUPLICADO,
        COPIA_N
};


class Reporte {
private:
        AnsiString texto;
        AnsiString imagen;
        void PrepararLienzo();
        void PrepararImpresora();
        void DibujarTexto(TCanvas *canvas);
        bool ImprimirDirecto(AnsiString impresora, AnsiString nombretrabajo);
public:
        Reporte();
        Reporte & operator<<(AnsiString texto);
        Reporte & operator<<(int espacios);
        void Imagen(AnsiString imagen);
        void Mostrar();
        void Imprimir(AnsiString impresora, AnsiString nombretrabajo, bool directo);
        void ExportarTexto(AnsiString fichero);
};


class Impresion {
private:
        void InsertarRemito(Reporte &rep, int tipocopia);
        void InsertarNotaCreditoRemito(Reporte &rep, int tipocopia);
        void InsertarFactura(Reporte &rep);
        void InsertarNotaCreditoFactura(Reporte &rep);
        void InsertarProductos(Reporte &rep);
        void InsertarListaPrecios(Reporte &rep);
        void InsertarSaldos(Reporte &rep);
        void InsertarCuentaCorriente(Reporte &rep, int desde);
        void InsertarRegistroDocumentos(Reporte &rep, TDate desde, TDate hasta);
        void InsertarRegistroVentasDiario(Reporte &rep, TDate desde, TDate hasta);
        void InsertarPlanillaProductos(Reporte &rep, TDate desde, TDate hasta);
        void InsertarRegistroProductosStock(Reporte &rep);
        void InsertarRegistroVentas(Reporte &rep1, Reporte &rep2, Reporte &rep3,
                                    TDate desde, TDate hasta);
        void Impresion::InsertarPedido(Reporte &rep);
        void MostrarDoc(int tipodocumento);
        void ImprimirDoc(int tipodocumento);
public:
        void ImprimirDocumento(int tipodocumento, bool vistaprevia);
        void ImprimirProductos(bool vistaprevia);
        void ExportarListaPrecios(AnsiString fichero);
        void ImprimirSaldos(bool vistaprevia);
        void ImprimirCuentaCorriente(int desde, bool vistaprevia);
        void ImprimirRegistroDocumentos(TDate desde, TDate hasta, bool vistaprevia);
        void ImprimirRegistroVentasDiario(TDate desde, TDate hasta, bool vistaprevia);
        void ImprimirRegistroProductosStock(bool vistaprevia);
        void ExportarSaldos(AnsiString fichero);
        void ExportarPlanillaProductos(TDate desde, TDate hasta, AnsiString fichero);
        void ExportarRegistroVentas(TDate desde, TDate hasta, AnsiString directorio);
};


//---------------------------------------------------------------------------
extern PACKAGE TFormImpresion *FormImpresion;
//---------------------------------------------------------------------------
#endif

