//---------------------------------------------------------------------------

#ifndef registroventasdiarioH
#define registroventasdiarioH
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
class TFormRegistroVentasDiario : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu;
        TMenuItem *MenuItemArchivo;
        TMenuItem *MenuItemCerrar;
        TMenuItem *MenuItemVer;
        TMenuItem *MenuItemOrdenar;
        TDBGrid *DBGrid;
        TMenuItem *MenuItemImprimirPeriodo;
        TToolBar *ToolBar;
        TToolButton *ToolButtonImprimirPeriodo;
        TImageList *ImageList;
        TMenuItem *MenuItemVisualizarPeriodo;
        void __fastcall MenuItemCerrarClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ToolButtonImprimirPeriodoClick(TObject *Sender);
        void __fastcall MenuItemImprimirPeriodoClick(TObject *Sender);
        void __fastcall MenuItemVisualizarPeriodoClick(TObject *Sender);
private:	// User declarations
        void __fastcall MenuItemOrdCol(TObject *Sender);
public:		// User declarations
        __fastcall TFormRegistroVentasDiario(TComponent* Owner);
        void Mostrar();
        void CargarMonto(int tipodocumento, TDate fecha, double monto);
        void DescargarMonto(int tipodocumento, TDate fecha, double monto);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormRegistroVentasDiario *FormRegistroVentasDiario;
//---------------------------------------------------------------------------
#endif
