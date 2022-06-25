//---------------------------------------------------------------------------

#ifndef dialogoproductoH
#define dialogoproductoH
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
        DLG_PTO_AGREGAR,
        DLG_PTO_EDITAR,
        DLG_PTO_N
};



class TFormDialogoProducto : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TPanel *Panel3;
        TDBEdit *DBEditCodigo;
        TLabel *Label1;
        TLabel *Label2;
        TDBEdit *DBEditFecha;
        TBitBtn *BitBtnAceptar;
        TBitBtn *BitBtnCancelar;
        TPanel *Panel2;
        TLabel *Label12;
        TDBEdit *DBEditDescripcion;
        TLabel *Label13;
        TDBLookupComboBox *DBLookupComboBoxFamilia;
        TBitBtn *BitBtnFamilias;
        TLabel *Label17;
        TDBLookupComboBox *DBLookupComboBoxUnidad;
        TBitBtn *BitBtnUnidades;
        TLabel *LabelPrecio1;
        TDBEdit *DBEditPrecio1;
        TLabel *LabelPrecio2;
        TDBEdit *DBEditPrecio2;
        TLabel *LabelPrecio3;
        TDBEdit *DBEditPrecio3;
        TLabel *Label3;
        TDBEdit *DBEditGramos;
        void __fastcall BitBtnAceptarClick(TObject *Sender);
        void __fastcall BitBtnCancelarClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtnFamiliasClick(TObject *Sender);
        void __fastcall DBEditPrecio1KeyPress(TObject *Sender, char &Key);
        void __fastcall DBEditCodigoKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
        __fastcall TFormDialogoProducto(TComponent* Owner);

        /* Mis declaraciones */
        TModalResult Mostrar(int);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDialogoProducto *FormDialogoProducto;
//---------------------------------------------------------------------------
#endif
