//---------------------------------------------------------------------------

#ifndef configuracionH
#define configuracionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <inifiles.hpp>
#include <ComCtrls.hpp>

#define FICHCONFIG GetCurrentDir() + "\\" + Application->Title + ".ini"

//---------------------------------------------------------------------------
class TFormConfiguracion : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TBitBtn *BitBtnAceptar;
        TBitBtn *BitBtnCancelar;
        TPageControl *PageControl;
        TTabSheet *TabSheet2;
        TLabel *Label7;
        TEdit *EditCantidadImprimirCC;
        TTabSheet *TabSheet4;
        TTabSheet *TabSheet5;
        TTabSheet *TabSheet6;
        TLabel *Label8;
        TEdit *EditEjecucionesCompactar;
        TButton *ButtonItemsClientes;
        TButton *ButtonItemsProductos;
        TTabSheet *TabSheet7;
        TBitBtn *BitBtnDirectorioCopia;
        TEdit *EditCopiaDirectorio;
        TLabel *Label6;
        TCheckBox *CheckBoxCopiaSalir;
        TGroupBox *GroupBox1;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TComboBox *ComboBoxImpresoraRemito;
        TComboBox *ComboBoxImpresoraFactura;
        TComboBox *ComboBoxImpresoraCuentaCorriente;
        TComboBox *ComboBoxImpresoraSaldos;
        TComboBox *ComboBoxImpresoraProductos;
        TComboBox *ComboBoxImpresoraRegistros;
        TCheckBox *CheckBoxRAWRemito;
        TCheckBox *CheckBoxRAWFactura;
        TCheckBox *CheckBoxRAWCuentaCorriente;
        TCheckBox *CheckBoxRAWSaldos;
        TCheckBox *CheckBoxRAWProductos;
        TCheckBox *CheckBoxRAWRegistros;
        TLabel *Label20;
        TEdit *EditBackupsConservar;
        TTabSheet *TabSheet8;
        TLabel *Label21;
        TEdit *EditClaveIdentificacion;
        TGroupBox *GroupBox3;
        TLabel *Label15;
        TLabel *Label17;
        TLabel *Label16;
        TLabel *Label18;
        TEdit *EditEspaciosPosteriorRD;
        TEdit *EditEspaciosPosteriorFO;
        TEdit *EditEspaciosPosteriorRO;
        TEdit *EditEspaciosPosteriorFD;
        TLabel *Label22;
        TEdit *EditEspaciosPosteriorCC;
        TGroupBox *GroupBox2;
        TCheckBox *CheckBoxImprimirDuplicadoRemito;
        TLabel *Label23;
        TLabel *Label1;
        TEdit *EditEspaciosPosteriorPedido;
        TLabel *Label2;
        TComboBox *ComboBoxImpresoraPedido;
        TCheckBox *CheckBoxRAWPedido;
        TGroupBox *GroupBox4;
        TButton *ButtonPadronCache;
        void __fastcall BitBtnAceptarClick(TObject *Sender);
        void __fastcall BitBtnCancelarClick(TObject *Sender);
        void __fastcall ButtonItemsClientesClick(TObject *Sender);
        void __fastcall ButtonItemsProductosClick(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BitBtnDirectorioCopiaClick(TObject *Sender);
        void __fastcall ButtonPadronCacheClick(TObject *Sender);
private:	// User declarations

        /* Mis declaraciones */
        void CargarConfiguracion();
        void GuardarConfiguracion();
        void CargarImpresoras();

public:		// User declarations
        __fastcall TFormConfiguracion(TComponent* Owner);

        /* Mis declaraciones */
        void Mostrar();
        double ValorIVA();
        int NumeroRenglones(int tipodocumento);
        int CantidadImprimirCC();
        void Comunicado(AnsiString);
        AnsiString Comunicado();
        AnsiString CopiaDirectorio();
        int BackupsConservar();
        bool CopiaSalir();
        int EjecucionesCompactar();
        AnsiString Impresora(int tipoimpresion);
        bool ModoRAW(int tipoimpresion);
        void EjecucionesSinCompactar(int cantidad);
        int EjecucionesSinCompactar();
        int EspaciosPosteriorRO();
        int EspaciosPosteriorRD();
        int EspaciosPosteriorFO();
        int EspaciosPosteriorFD();
        int EspaciosPosteriorCC();
        int EspaciosPosteriorPedido();
        AnsiString ClaveIdentificacion();
        bool ImprimirDuplicadoRemito();
        void CargarEstadoVentanas();
        void GuardarEstadoVentanas();
        AnsiString CUIT();
        int PuntoVenta();
        AnsiString Certificado();
        AnsiString ClavePrivada();
};

enum {
        IMP_REMITO,
        IMP_FACTURA,
        IMP_CUENTA,
        IMP_SALDOS,
        IMP_PRODUCTOS,
        IMP_REGISTROS,
        IMP_PEDIDO,
        IMP_N
};

//---------------------------------------------------------------------------
extern PACKAGE TFormConfiguracion *FormConfiguracion;
//---------------------------------------------------------------------------
#endif
