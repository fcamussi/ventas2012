//---------------------------------------------------------------------------

#ifndef registroproductosanualH
#define registroproductosanualH
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
class TFormRegistroProductosAnual : public TForm
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
        void __fastcall MenuItemCerrarClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
        void __fastcall MenuItemOrdCol(TObject *Sender);
public:		// User declarations
        __fastcall TFormRegistroProductosAnual(TComponent* Owner);
        void Mostrar();
        void CargarCantidad(int tipodocumento, AnsiString codigo, int ano, int cantidad);
        void DescargarCantidad(int tipodocumento, AnsiString codigo, int ano, int cantidad);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormRegistroProductosAnual *FormRegistroProductosAnual;
//---------------------------------------------------------------------------
#endif
