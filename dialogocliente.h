//---------------------------------------------------------------------------

#ifndef dialogoclienteH
#define dialogoclienteH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------


enum {
        DLG_CTE_AGREGAR,
        DLG_CTE_EDITAR,
        DLG_CTE_N
};



class TFormDialogoCliente : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl;
        TPanel *Panel1;
        TPanel *Panel2;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TDBEdit *DBEditNumero;
        TLabel *Label1;
        TLabel *Label2;
        TDBEdit *DBEditFecha;
        TBitBtn *BitBtnAceptar;
        TBitBtn *BitBtnCancelar;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TDBEdit *DBEditNombreCliente;
        TDBEdit *DBEditDireccion;
        TDBLookupComboBox *DBLookupComboBoxLocalidad;
        TDBLookupComboBox *DBLookupComboBoxProvincia;
        TDBEdit *DBEditTelefono1;
        TDBEdit *DBEditTelefono2;
        TLabel *Label11;
        TDBEdit *DBEditFax;
        TDBEdit *DBEditMovil;
        TDBEdit *DBEditEmail;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TLabel *Label18;
        TDBEdit *DBEditNombreNegocio;
        TDBLookupComboBox *DBLookupComboBoxTipo;
        TDBEdit *DBEditCUIT;
        TDBEdit *DBEditDescuento;
        TLabel *Label19;
        TDBComboBox *DBComboBoxPosicionIVA;
        TBitBtn *BitBtnProvincias;
        TBitBtn *BitBtnTiposNegocios;
        TDBComboBox *DBComboBoxNombreFactura;
        TDBComboBox *DBComboBoxFormaPago;
        void __fastcall BitBtnAceptarClick(TObject *Sender);
        void __fastcall BitBtnCancelarClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtnLocalidadesClick(TObject *Sender);
        void __fastcall DBEditDescuentoKeyPress(TObject *Sender,
          char &Key);
        void __fastcall DBEditNombreNegocioExit(TObject *Sender);
        void __fastcall DBEditNombreClienteExit(TObject *Sender);
private:	// User declarations

        /* Mis declaraciones */
        void ActualizarNombresFactura();

public:		// User declarations
        __fastcall TFormDialogoCliente(TComponent* Owner);

        /* Mis declaraciones */
        TModalResult Mostrar(int);
};

//---------------------------------------------------------------------------
extern PACKAGE TFormDialogoCliente *FormDialogoCliente;
//---------------------------------------------------------------------------
#endif
