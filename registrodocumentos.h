//---------------------------------------------------------------------------

#ifndef registrodocumentosH
#define registrodocumentosH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <AppEvnts.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormRegistroDocumentos : public TForm
{
__published:	// IDE-managed Components
        TDBGrid *DBGrid;
        TMainMenu *MainMenu;
        TMenuItem *MenuItemArchivo;
        TMenuItem *MenuItemCerrar;
        TMenuItem *MenuItemVer;
        TMenuItem *MenuItemOrdenar;
        TMenuItem *MenuItemDocumento;
        TMenuItem *MenuItemImprimir;
        TMenuItem *MenuItemAnular;
        TMenuItem *MenuItemMostrar;
        TMenuItem *MenuItemEditar;
        TPopupMenu *PopupMenu;
        TMenuItem *MenuItemMostrar2;
        TMenuItem *MenuItemImprimir2;
        TMenuItem *MenuItemEditar2;
        TMenuItem *MenuItemAnular2;
        TMenuItem *MenuItemImprimirPeriodo;
        TToolBar *ToolBar;
        TToolButton *ToolButtonImprimirPeriodo;
        TImageList *ImageList;
        TToolButton *ToolButtonEditar;
        TToolButton *ToolButtonAnular;
        TToolButton *ToolButtonMostrar;
        TToolButton *ToolButton6;
        TMenuItem *MenuItemVisualizarPeriodo;
        TSaveDialog *SaveDialog;
        TMenuItem *MenuItemHerramientas;
        TMenuItem *MenuItemExportarPlanilla;
        TMenuItem *MenuItemExportarVentas;
        TMenuItem *MenuItemEliminar;
        TMenuItem *MenuItemEliminar2;
        void __fastcall MenuItemCerrarClick(TObject *Sender);
        void __fastcall MenuItemMostrarClick(TObject *Sender);
        void __fastcall MenuItemEditarClick(TObject *Sender);
        void __fastcall MenuItemImprimirClick(TObject *Sender);
        void __fastcall MenuItemAnularClick(TObject *Sender);
        void __fastcall DBGridDrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall MenuItemDocumentoClick(TObject *Sender);
        void __fastcall MenuItemImprimirPeriodoClick(TObject *Sender);
        void __fastcall ToolButtonImprimirPeriodoClick(TObject *Sender);
        void __fastcall ToolButtonMostrarClick(TObject *Sender);
        void __fastcall ToolButtonEditarClick(TObject *Sender);
        void __fastcall ToolButtonAnularClick(TObject *Sender);
        void __fastcall MenuItemVisualizarPeriodoClick(TObject *Sender);
        void __fastcall MenuItemExportarPlanillaClick(TObject *Sender);
        void __fastcall MenuItemExportarVentasClick(TObject *Sender);
        void __fastcall MenuItemEliminarClick(TObject *Sender);
private:	// User declarations

        void __fastcall MenuItemOrdCol(TObject *Sender);
        void ImprimirPendientes(int tipodocumento);
public:		// User declarations
        __fastcall TFormRegistroDocumentos(TComponent* Owner);

        /* Mis declaraciones */
        void Mostrar();
        void AnularDocumento(int tipodocumento, int numerodocumento);
        void MostrarDocumento(int tipodocumento, int numerodocumento);
        //void ReducirAnulados(int conservar);
        void EliminarDocumento(int tipodocumento, int numerodocumento);
};

//---------------------------------------------------------------------------
extern PACKAGE TFormRegistroDocumentos *FormRegistroDocumentos;
//---------------------------------------------------------------------------
#endif
