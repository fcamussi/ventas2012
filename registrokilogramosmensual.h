//---------------------------------------------------------------------------

#ifndef registrokilogramosmensualH
#define registrokilogramosmensualH
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
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormRegistroKilogramosMensual : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu;
        TMenuItem *MenuItemArchivo;
        TMenuItem *MenuItemCerrar;
        TMenuItem *MenuItemVer;
        TMenuItem *MenuItemOrdenar;
        TDBGrid *DBGrid;
        void __fastcall MenuItemCerrarClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
        void __fastcall MenuItemOrdCol(TObject *Sender);
public:		// User declarations
        __fastcall TFormRegistroKilogramosMensual(TComponent* Owner);
        void Mostrar();
        void CargarCantidad(int tipodocumento, int mes, int ano, double cantidad);
        void DescargarCantidad(int tipodocumento, int mes, int ano, double cantidad);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormRegistroKilogramosMensual *FormRegistroKilogramosMensual;
//---------------------------------------------------------------------------
#endif
