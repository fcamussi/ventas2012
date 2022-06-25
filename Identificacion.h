//---------------------------------------------------------------------------

#ifndef IdentificacionH
#define IdentificacionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormIdentificacion : public TForm
{
__published:	// IDE-managed Components
        TEdit *EditClave;
        TButton *ButtonEntrar;
        void __fastcall ButtonEntrarClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormIdentificacion(TComponent* Owner);

        /* Mis declaraciones */
        int Mostrar();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormIdentificacion *FormIdentificacion;
//---------------------------------------------------------------------------
#endif
