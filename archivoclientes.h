//---------------------------------------------------------------------------

#ifndef archivoclientesH
#define archivoclientesH
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

#define FICHCLIENTES GetCurrentDir() + "\\clientes"

//---------------------------------------------------------------------------
class TFormArchivoClientes : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu;
        TMenuItem *MenuItemArchivo;
        TMenuItem *MenuItemCerrar;
        TMenuItem *MenuItemCliente;
        TMenuItem *MenuItemAgregar;
        TMenuItem *MenuItemEditar;
        TMenuItem *MenuItemEliminar;
        TMenuItem *MenuItemVer;
        TDBGrid *DBGrid;
        TMenuItem *MenuItemOrdenar;
        TMenuItem *MenuItemBuscar;
        TImageList *ImageList;
        TToolBar *ToolBar;
        TToolButton *ToolButtonAgregar;
        TToolButton *ToolButtonEliminar;
        TToolButton *ToolButtonEditar;
        TToolButton *ToolButton4;
        TToolButton *ToolButtonBuscar;
        TPopupMenu *PopupMenu;
        TMenuItem *MenuItemAgregar2;
        TMenuItem *MenuItemEditar2;
        TMenuItem *MenuItemEliminar2;
        void __fastcall MenuItemAgregarClick(TObject *Sender);
        void __fastcall MenuItemEditarClick(TObject *Sender);
        void __fastcall MenuItemEliminarClick(TObject *Sender);
        void __fastcall MenuItemCerrarClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall MenuItemBuscarClick(TObject *Sender);
        void __fastcall DBGridKeyPress(TObject *Sender, char &Key);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations

        /* Mis declaraciones */
        void __fastcall MenuItemOrdCol(TObject *Sender);

        bool HayClientes();
        void AgregarCliente();
        void EditarCliente();
        void EliminarCliente();
        bool ConfirmarEliminacion();

public:		// User declarations
        __fastcall TFormArchivoClientes(TComponent* Owner);

        /* Mis declaraciones */
        void Mostrar();
};

//---------------------------------------------------------------------------
extern PACKAGE TFormArchivoClientes *FormArchivoClientes;
//---------------------------------------------------------------------------
#endif
