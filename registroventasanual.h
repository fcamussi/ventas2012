//---------------------------------------------------------------------------

#ifndef registroventasanualH
#define registroventasanualH
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
class TFormRegistroVentasAnual : public TForm
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
        __fastcall TFormRegistroVentasAnual(TComponent* Owner);
        void Mostrar();
        void CargarMonto(int tipodocumento, int ano, double monto);
        void DescargarMonto(int tipodocumento, int ano, double monto);

};
//---------------------------------------------------------------------------
extern PACKAGE TFormRegistroVentasAnual *FormRegistroVentasAnual;
//---------------------------------------------------------------------------
#endif
