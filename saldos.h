//---------------------------------------------------------------------------

#ifndef saldosH
#define saldosH
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
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormSaldos : public TForm
{
__published:	// IDE-managed Components
        TDBGrid *DBGrid;
        TMainMenu *MainMenu;
        TMenuItem *MenuItemArchivo;
        TMenuItem *MenuItemCerrar;
        TMenuItem *MenuItemVer;
        TMenuItem *MenuItemOrdenar;
        TMenuItem *MenuItemImprimir;
        TToolBar *ToolBar;
        TToolButton *ToolButtonImprimirDesde;
        TImageList *ImageList;
        TPanel *Panel1;
        TLabel *Label1;
        TStaticText *StaticTextSaldoTotal;
        TMenuItem *MenuItemVisualizar;
        void __fastcall DBGridDrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall MenuItemCerrarClick(TObject *Sender);
        void __fastcall MenuItemImprimirClick(TObject *Sender);
        void __fastcall ToolButtonImprimirDesdeClick(TObject *Sender);
        void __fastcall MenuItemVisualizarClick(TObject *Sender);
private:	// User declarations
        void __fastcall MenuItemOrdCol(TObject *Sender);
                /* Mis declaraciones */
        void CalcularSaldoTotal();

public:		// User declarations
        __fastcall TFormSaldos(TComponent* Owner);

        /* Mis declaraciones */
        void Mostrar();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSaldos *FormSaldos;
//---------------------------------------------------------------------------
#endif
