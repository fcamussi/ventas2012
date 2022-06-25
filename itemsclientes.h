//---------------------------------------------------------------------------

#ifndef itemsclientesH
#define itemsclientesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFormItemsClientes : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl;
        TTabSheet *TabSheetLocalidades;
        TTabSheet *TabSheetTiposNegocios;
        TDBGrid *DBGridTiposNegocios;
        TDBGrid *DBGridLocalidades;
        TToolBar *ToolBar;
        TToolButton *ToolButtonAgregar;
        TToolButton *ToolButtonEliminar;
        TImageList *ImageList;
        TPopupMenu *PopupMenu;
        TMenuItem *MenuItemAgregar;
        TMenuItem *MenuItemEliminar;
        TDBGrid *DBGridProvincias;
        void __fastcall ToolButtonAgregarClick(TObject *Sender);
        void __fastcall ToolButtonEliminarClick(TObject *Sender);
        void __fastcall DBGridKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift);
        void __fastcall MenuItemAgregarClick(TObject *Sender);
        void __fastcall MenuItemEliminarClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormItemsClientes(TComponent* Owner);

        /* Mis definiciones */
        void Mostrar(int);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormItemsClientes *FormItemsClientes;
//---------------------------------------------------------------------------
#endif
