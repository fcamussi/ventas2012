//---------------------------------------------------------------------------

#ifndef AFIPH
#define AFIPH

#include <vcl.h>
#include <fstream>
#include <vector>
//---------------------------------------------------------------------------

using namespace std;
//---------------------------------------------------------------------------

class Item
{
    public:
        Item(int qty, AnsiString ds, double precio, double importe);
        int qty;
        AnsiString ds;
        double precio;
        double importe;
};
//---------------------------------------------------------------------------

class FE
{
    public:
        // entrada
        AnsiString nro_doc;
        int tipo_cbte;
        TDate fecha_cbte;
        double imp_neto;
        double imp_iva;
        double imp_total;
        AnsiString id_impositivo;
        AnsiString nombre_cliente;
        AnsiString domicilio_cliente;
        AnsiString localidad_cliente;
        AnsiString provincia_cliente;
        vector<Item> items;
        double desc;
        double imp_desc;
        int nro_ctrl;
        AnsiString obs_generales;
        int tipo_cbte_asoc;
        int cbte_nro_asoc;
        // salida
        int cbte_nro;
        AnsiString cae;
        TDate vto_cae;
        vector<AnsiString> eventos;
        AnsiString obs_afip;
};
//---------------------------------------------------------------------------

class AFIP
{
    public:
        AFIP(AnsiString fichcert, AnsiString fichclave);
        void AutorizarComprobante(FE &fe);
        void GenerarPDF(FE &fe, AnsiString fichpdf);
        AnsiString ObtenerDenominacion(AnsiString cuit);
        AnsiString cuit;
        int punto_vta;
    private:
        AnsiString fichcert;
        AnsiString fichclave;
        Variant WSAA;
        Variant WSFEv1;
        Variant PyFEPDF;
        Variant WSSrPadronA5;
        ofstream fichlog;
        ofstream ficheventos;
};
//---------------------------------------------------------------------------

class EAFIP : public Exception
{
        public:
        __fastcall EAFIP(const AnsiString Msg) : Exception(Msg) {};
};
//---------------------------------------------------------------------------

class EAFIPAdv : public Exception
{
        public:
        __fastcall EAFIPAdv(const AnsiString Msg) : Exception(Msg) {};
};
//---------------------------------------------------------------------------

static inline Variant VWS(AnsiString s);
//---------------------------------------------------------------------------

#endif
