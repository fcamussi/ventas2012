//---------------------------------------------------------------------------

#ifndef mensajeH
#define mensajeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormMensaje : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label;
        TImageList *ImageList;
        TImage *Image;
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormMensaje(TComponent* Owner);
};

class Mensaje
{
        public:
        Mensaje(AnsiString texto);
        void Mostrar();
        void Cerrar();
};

//---------------------------------------------------------------------------
extern PACKAGE TFormMensaje *FormMensaje;
//---------------------------------------------------------------------------
#endif
