//---------------------------------------------------------------------------

#ifndef facturacionH
#define facturacionH
//---------------------------------------------------------------------------
#include <vector.h>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <Dialogs.hpp>
#include "AFIP.h"
#include <jpeg.hpp>
//---------------------------------------------------------------------------

enum {
        DOC_REMITO,
        DOC_FACTURA, // tradicional
        DOC_CREDITOREMITO,
        DOC_CREDITOFACTURA, // tradicional
        DOC_FACTURAELECT,
        DOC_CREDITOELECT,
        DOC_DEBITOELECT,
        DOC_PEDIDO,
        DOC_N
};

enum {
        EST_IMPRESO,
        EST_SINIMPRIMIR,
        EST_ANULADO,
        EST_N
};
//---------------------------------------------------------------------------

class TFormFacturacion : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelFactura1;
        TStringGrid *StringGridCodigos;
        TPanel *PanelSuperior;
        TGroupBox *GroupBox1;
        TLabel *Label4;
        TDBEdit *DBEditNombreFactura;
        TLabel *Label6;
        TDBEdit *DBEditDireccion;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label5;
        TDBEdit *DBEditNumeroCliente;
        TDBEdit *DBEditLocalidad;
        TDBEdit *DBEditProvincia;
        TPanel *PanelFactura2;
        TStringGrid *StringGridFactura;
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TLabel *Label2;
        TEdit *EditSubtotal;
        TLabel *Label3;
        TEdit *EditDescuentoTotal;
        TLabel *Label13;
        TEdit *EditSubtotal2;
        TLabel *Label14;
        TEdit *EditIVATotal;
        TLabel *Label15;
        TEdit *EditTotal;
        TPanel *Panel4;
        TMemo *MemoComunicado;
        TLabel *Label16;
        TLabel *Label1;
        TEdit *EditDescuento;
        TLabel *Label19;
        TLabel *LabelTipoDocumento;
        TComboBox *ComboBoxTipoDocumento;
        TLabel *LabelDescuento;
        TLabel *LabelIVA;
        TPopupMenu *PopupMenuCodigos;
        TMenuItem *MenuItemSeleccionar2;
        TMenuItem *MenuItemSinCargo2;
        TBitBtn *BitBtnRecuperarUltimo;
        TPanel *Panel5;
        TButton *ButtonSiguiente;
        TButton *ButtonCancelar;
        TPanel *Panel6;
        TButton *ButtonImprimir;
        TButton *ButtonSinImprimir;
        TButton *ButtonVolver;
        TButton *ButtonCancelar2;
        TGroupBox *GroupBox2;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TEdit *EditNumeroDocumento;
        TEdit *EditFecha;
        TDBEdit *DBEditPosicionIVA;
        TDBEdit *DBEditCUIT;
        TMainMenu *MainMenu;
        TMenuItem *MenuItemArchivo;
        TMenuItem *MenuItemCambiarCliente;
        TMenuItem *MenuItemCerrar;
        TMenuItem *MenuItemProducto;
        TMenuItem *MenuItemSeleccionar;
        TMenuItem *MenuItemSinCargo;
        TEdit *EditHora;
        TToolBar *ToolBar;
        TImageList *ImageList;
        TToolButton *ToolButtonCambiarCliente;
        TPanel *PanelNumeroComprobante;
        TEdit *EditNumeroComprobante;
        TLabel *Label17;
        TEdit *EditPuntoVenta;
        TLabel *Label18;
        TPanel *PanelComprobanteAsociado;
        TLabel *Label20;
        TLabel *Label21;
        TEdit *EditNumeroComprobanteAsociado;
        TEdit *EditPuntoVentaComprobanteAsociado;
        TPanel *PanelAFIP;
        TImage *ImageAFIP;
        void __fastcall StringGridCodigosKeyPress(TObject *Sender,
          char &Key);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ButtonSiguienteClick(TObject *Sender);
        void __fastcall ButtonVolverClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall EditDescuentoKeyPress(TObject *Sender, char &Key);
        void __fastcall ComboBoxTipoDocumentoChange(TObject *Sender);
        void __fastcall ButtonImprimirSinImprimirClick(TObject *Sender);
        void __fastcall StringGridCodigosContextPopup(TObject *Sender,
          TPoint &MousePos, bool &Handled);
        void __fastcall BitBtnRecuperarUltimoClick(TObject *Sender);
        void __fastcall StringGridCodigosDrawCell(TObject *Sender,
          int ACol, int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall MenuItemCerrarClick(TObject *Sender);
        void __fastcall MenuItemCambiarClienteClick(TObject *Sender);
        void __fastcall MenuItemSeleccionarClick(TObject *Sender);
        void __fastcall MenuItemSinCargoClick(TObject *Sender);
        void __fastcall MenuItemProductoClick(TObject *Sender);
        void __fastcall ToolButtonCambiarClienteClick(TObject *Sender);
        void __fastcall StringGridFacturaDrawCell(TObject *Sender,
          int ACol, int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall EditNumeroComprobanteKeyPress(TObject *Sender,
          char &Key);
private:	// User declarations
        /* Mis declaraciones */
        vector<bool> SinCargo;
        void ConfigurarRenglones(int tipodocumento);
        bool TraducirCodigos();
        bool CalcularFactura();
        void LimpiarRenglones();
        void ArchivarDocumento(int);
        void CargarEnCuentaCorriente();
        void CargarRenglones(int, int);
        void ArchivarDatosFE(FE &fe);
        AnsiString ObtenerNombreAFIP(AnsiString cuit);

public:		// User declarations
        __fastcall TFormFacturacion(TComponent* Owner);

        /* Mis declaraciones */
        void NuevoDocumento(int, int);
        void EditarDocumento(int, int, int);
        AnsiString Documentos(int);
        AnsiString Estados(int);
        void CargarFE(FE &fe);
        void CargarDatosFE(FE &fe);
        void ArchivarDatosFT();
        void AgregarComprobanteAsociado(FE &fe);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormFacturacion *FormFacturacion;
//---------------------------------------------------------------------------
#endif
