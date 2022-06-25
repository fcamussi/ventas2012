//---------------------------------------------------------------------------

#ifndef cuentacorrienteH
#define cuentacorrienteH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormCuentaCorriente : public TForm
{
__published:	// IDE-managed Components
        TDBGrid *DBGrid;
        TMainMenu *MainMenu;
        TMenuItem *MenuItemArchivo;
        TMenuItem *MenuItemCerrar;
        TMenuItem *MenuItemRegistro;
        TMenuItem *MenuItemAgregar;
        TMenuItem *MenuItemEliminar;
        TMenuItem *MenuItemImprimir;
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TLabel *Label4;
        TLabel *Label5;
        TDBEdit *DBEditNombreCliente;
        TDBEdit *DBEditNumeroCliente;
        TLabel *Label1;
        TDBEdit *DBEditNombreNegocio;
        TLabel *Label2;
        TImageList *ImageList;
        TToolBar *ToolBar;
        TToolButton *ToolButtonAgregar;
        TToolButton *ToolButtonEliminar;
        TStaticText *StaticTextSaldo;
        TButton *Button1;
        TPopupMenu *PopupMenu;
        TMenuItem *MenuItemAgregar2;
        TMenuItem *MenuItemEliminar2;
        TMenuItem *MenuItemCambiarCliente;
        TMenuItem *MenuItemMostrar;
        TMenuItem *MenuItemMostrar2;
        TPanel *Panel2;
        TLabel *Label3;
        TLabel *LabelCantidadRegistros;
        TMenuItem *MenuItemImprimirDesde;
        TToolButton *ToolButton1;
        TToolButton *ToolButtonCambiarCliente;
        TToolButton *ToolButtonImprimir;
        TMenuItem *MenuItemVisualizar;
        TMenuItem *MenuItemVisualizarDesde;
        void __fastcall DBGridColExit(TObject *Sender);
        void __fastcall DBGridKeyPress(TObject *Sender, char &Key);
        void __fastcall DBGridExit(TObject *Sender);
        void __fastcall MenuItemCerrarClick(TObject *Sender);
        void __fastcall MenuItemEliminarClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall DBGridKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall MenuItemAgregarClick(TObject *Sender);
        void __fastcall MenuItemCambiarClienteClick(TObject *Sender);
        void __fastcall MenuItemMostrarClick(TObject *Sender);
        void __fastcall MenuItemRegistroClick(TObject *Sender);
        void __fastcall MenuItemImprimirDesdeClick(TObject *Sender);
        void __fastcall MenuItemImprimirClick(TObject *Sender);
        void __fastcall ToolButtonCambiarClienteClick(TObject *Sender);
        void __fastcall ToolButtonImprimirClick(TObject *Sender);
        void __fastcall MenuItemVisualizarClick(TObject *Sender);
        void __fastcall MenuItemVisualizarDesdeClick(TObject *Sender);
private:	// User declarations

        /* Mis declaraciones */
        bool HayRegistros();
        bool ConfirmarEliminacion();
        void EliminarRegistro();
        //void Reducir(int conservar);
        void ActualizarSaldoParcial();
        void ActualizarSaldoTotal();
        void Imprimir(bool vistaprevia);

public:		// User declarations
        __fastcall TFormCuentaCorriente(TComponent* Owner);

        /* Mis declaraciones */
        void Mostrar(int);
        void AgregarRegistro(AnsiString, AnsiString, double, double, int, double);
        void ActualizarSaldos();
        void ActualizarCantidadRegistros();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormCuentaCorriente *FormCuentaCorriente;
//---------------------------------------------------------------------------
#endif
