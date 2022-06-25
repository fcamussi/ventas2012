//---------------------------------------------------------------------------

#ifndef seleccionarproductoH
#define seleccionarproductoH
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
class TFormSeleccionarProducto : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TLabel *Label2;
        TEdit *EditTexto;
        TDBGrid *DBGrid;
        TBitBtn *BitBtnCerrar;
        TBitBtn *BitBtnSeleccionar;
        TTable *TableProductos;
        TDataSource *DataSourceProductos;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtnCerrarClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtnSeleccionarClick(TObject *Sender);
        void __fastcall DBGridDblClick(TObject *Sender);
        void __fastcall EditTextoChange(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall TableProductosFilterRecord(TDataSet *DataSet,
          bool &Accept);
private:	// User declarations
public:		// User declarations
        __fastcall TFormSeleccionarProducto(TComponent* Owner);

        /* Mis declaraciones */
        AnsiString Mostrar(AnsiString);
};

//---------------------------------------------------------------------------
extern PACKAGE TFormSeleccionarProducto *FormSeleccionarProducto;
//---------------------------------------------------------------------------
#endif
