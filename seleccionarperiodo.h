//---------------------------------------------------------------------------

#ifndef seleccionarperiodoH
#define seleccionarperiodoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormSeleccionarPeriodo : public TForm
{
__published:	// IDE-managed Components
        TDateTimePicker *DateTimePickerDesde;
        TDateTimePicker *DateTimePickerHasta;
        TLabel *Label1;
        TLabel *Label2;
        TButton *ButtonAceptar;
        TButton *ButtonCancelar;
        void __fastcall ButtonAceptarClick(TObject *Sender);
        void __fastcall ButtonCancelarClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormSeleccionarPeriodo(TComponent* Owner);

        /* Mis declaraciones */
        TModalResult Mostrar();
        void ObtenerPeriodo(TDate &desde, TDate &hasta);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSeleccionarPeriodo *FormSeleccionarPeriodo;
//---------------------------------------------------------------------------
#endif
