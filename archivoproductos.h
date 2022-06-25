//---------------------------------------------------------------------------

#ifndef archivoproductosH
#define archivoproductosH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormArchivoProductos : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu;
        TMenuItem *MenuItemArchivo;
        TMenuItem *MenuItemCerrar;
        TMenuItem *MenuItemProducto;
        TMenuItem *MenuItemAgregar;
        TMenuItem *MenuItemEditar;
        TMenuItem *MenuItemEliminar;
        TMenuItem *MenuItemVer;
        TDBGrid *DBGrid;
        TMenuItem *MenuItemOrdenar;
        TMenuItem *MenuItemBuscar;
        TImageList *ImageList;
        TToolBar *ToolBar;
        TToolButton *ToolButtonEliminar;
        TToolButton *ToolButtonEditar;
        TToolButton *ToolButtonBuscar;
        TPopupMenu *PopupMenu;
        TMenuItem *MenuItemAgregar2;
        TMenuItem *MenuItemEditar2;
        TMenuItem *MenuItemEliminar2;
        TMenuItem *MenuItemIncrementarPrecios;
        TMenuItem *MenuItemImprimir;
        TMenuItem *MenuItemDecrementarPrecios;
        TToolButton *ToolButton1;
        TToolButton *ToolButtonImprimir;
        TToolButton *ToolButtonAgregar;
        TToolButton *ToolButton5;
        TMenuItem *MenuItemVisualizar;
        TMenuItem *MenuItemHerramientas;
        TMenuItem *ExportarListaPrecios;
        TSaveDialog *SaveDialog;
        void __fastcall MenuItemAgregarClick(TObject *Sender);
        void __fastcall MenuItemEditarClick(TObject *Sender);
        void __fastcall MenuItemEliminarClick(TObject *Sender);
        void __fastcall MenuItemCerrarClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall MenuItemBuscarClick(TObject *Sender);
        void __fastcall DBGridKeyPress(TObject *Sender, char &Key);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall MenuItemIncrementarPreciosClick(TObject *Sender);
        void __fastcall MenuItemDecrementarPreciosClick(TObject *Sender);
        void __fastcall MenuItemImprimirClick(TObject *Sender);
        void __fastcall ToolButtonImprimirClick(TObject *Sender);
        void __fastcall ToolButtonAgregarClick(TObject *Sender);
        void __fastcall MenuItemVisualizarClick(TObject *Sender);
        void __fastcall ExportarListaPreciosClick(TObject *Sender);
private:	// User declarations

        /* Mis declaraciones */
        void __fastcall MenuItemVerCol(TObject *Sender);
        void __fastcall MenuItemOrdCol(TObject *Sender);
        bool HayProductos();
        AnsiString CodigoProducto();
        void CodigoProducto(AnsiString);
        AnsiString DescripcionProducto();
        void AgregarProducto();
        void EditarProducto();
        void EliminarProducto();
        bool ConfirmarEliminacion();
        void ModificarPrecios(double porcentaje);

public:		// User declarations
        __fastcall TFormArchivoProductos(TComponent* Owner);

        /* Mis declaraciones */
        void Mostrar();
};

//---------------------------------------------------------------------------
extern PACKAGE TFormArchivoProductos *FormArchivoProductos;
//---------------------------------------------------------------------------
#endif
