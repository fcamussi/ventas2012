//---------------------------------------------------------------------------

#ifndef buscarproductosH
#define buscarproductosH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormBuscarProductos : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *EditTexto;
        TComboBox *ComboBoxColumna;
        TTable *TableProductos;
        TDataSource *DataSourceProductos;
        TDBGrid *DBGrid;
        TBitBtn *BitBtnBuscar;
        TBitBtn *BitBtnCerrar;
        TBitBtn *BitBtnSeleccionar;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtnBuscarClick(TObject *Sender);
        void __fastcall BitBtnCerrarClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtnSeleccionarClick(TObject *Sender);
        void __fastcall DBGridDblClick(TObject *Sender);
        void __fastcall TableProductosFilterRecord(TDataSet *DataSet,
          bool &Accept);
private:	// User declarations

        /* Mis declaraciones */
        bool BusquedaValida();

public:		// User declarations
        __fastcall TFormBuscarProductos(TComponent* Owner);

        /* Mis declaraciones */
        AnsiString Mostrar();
};

//---------------------------------------------------------------------------
extern PACKAGE TFormBuscarProductos *FormBuscarProductos;
//---------------------------------------------------------------------------
#endif
