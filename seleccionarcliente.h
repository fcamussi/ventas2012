//---------------------------------------------------------------------------

#ifndef seleccionarclienteH
#define seleccionarclienteH
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
class TFormSeleccionarCliente : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TLabel *Label2;
        TEdit *EditTexto;
        TDBGrid *DBGrid;
        TBitBtn *BitBtnCerrar;
        TBitBtn *BitBtnSeleccionar;
        TTable *TableClientes;
        TDataSource *DataSourceClientes;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtnCerrarClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtnSeleccionarClick(TObject *Sender);
        void __fastcall DBGridDblClick(TObject *Sender);
        void __fastcall EditTextoChange(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall TableClientesFilterRecord(TDataSet *DataSet,
          bool &Accept);
private:	// User declarations
public:		// User declarations
        __fastcall TFormSeleccionarCliente(TComponent* Owner);

        /* Mis declaraciones */
        int Mostrar(int defecto);
};

//---------------------------------------------------------------------------
extern PACKAGE TFormSeleccionarCliente *FormSeleccionarCliente;
//---------------------------------------------------------------------------
#endif
