//---------------------------------------------------------------------------

#ifndef registroventasmensualH
#define registroventasmensualH
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
class TFormRegistroVentasMensual : public TForm
{
__published:	// IDE-managed Components
        TDBGrid *DBGrid;
        TMainMenu *MainMenu;
        TMenuItem *MenuItemArchivo;
        TMenuItem *MenuItemCerrar;
        TMenuItem *MenuItemVer;
        TMenuItem *MenuItemOrdenar;
        void __fastcall MenuItemCerrarClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
        void __fastcall MenuItemOrdCol(TObject *Sender);
public:		// User declarations
        __fastcall TFormRegistroVentasMensual(TComponent* Owner);
        void Mostrar();
        void CargarMonto(int tipodocumento, int mes, int ano, double monto);
        void DescargarMonto(int tipodocumento, int mes, int ano, double monto);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormRegistroVentasMensual *FormRegistroVentasMensual;
//---------------------------------------------------------------------------
#endif
