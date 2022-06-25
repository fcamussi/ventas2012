//---------------------------------------------------------------------------

#ifndef registroproductosstockH
#define registroproductosstockH
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
//---------------------------------------------------------------------------
class TFormRegistroProductosStock : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu;
        TMenuItem *MenuItemArchivo;
        TMenuItem *MenuItemCerrar;
        TMenuItem *MenuItemVer;
        TMenuItem *MenuItemOrdenar;
        TDBGrid *DBGrid;
        TImageList *ImageList;
        TToolBar *ToolBar;
        TToolButton *ToolButtonImprimirDesde;
        TMenuItem *MenuItemHerramientas;
        TMenuItem *MenuItemResetearStock;
        TMenuItem *MenuItemImprimir;
        TMenuItem *MenuItemVisualizar;
        TPopupMenu *PopupMenu;
        TMenuItem *MenuItemAgregar2;
        TMenuItem *MenuItemQuitar2;
        TMenuItem *MenuItemStock;
        TMenuItem *MenuItemAgregar;
        TMenuItem *MenuItemQuitar;
        TMenuItem *MenuItemSeleccionar;
        TMenuItem *MenuItemSeleccionar2;
        TMenuItem *N1;
        void __fastcall MenuItemCerrarClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall DBGridKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall DBGridColExit(TObject *Sender);
        void __fastcall DBGridExit(TObject *Sender);
        void __fastcall DBGridKeyPress(TObject *Sender, char &Key);
        void __fastcall MenuItemResetearStockClick(TObject *Sender);
        void __fastcall MenuItemImprimirClick(TObject *Sender);
        void __fastcall ToolButtonImprimirDesdeClick(TObject *Sender);
        void __fastcall MenuItemVisualizarClick(TObject *Sender);
        void __fastcall DBGridDrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
        void __fastcall MenuItemSeleccionarClick(TObject *Sender);
        void __fastcall MenuItemAgregarClick(TObject *Sender);
        void __fastcall MenuItemQuitarClick(TObject *Sender);
        void __fastcall MenuItemAgregar2Click(TObject *Sender);
        void __fastcall MenuItemQuitar2Click(TObject *Sender);
        void __fastcall MenuItemSeleccionar2Click(TObject *Sender);
private:	// User declarations
        void __fastcall MenuItemOrdCol(TObject *Sender);
public:		// User declarations
        __fastcall TFormRegistroProductosStock(TComponent* Owner);
        void Mostrar();
        void ResetearStock();
        void DescargarStock(AnsiString codigo, int cantidad);
        void CargarStock(AnsiString codigo, int cantidad);
        int CantidadStock(AnsiString codigo);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormRegistroProductosStock *FormRegistroProductosStock;
//---------------------------------------------------------------------------
#endif
