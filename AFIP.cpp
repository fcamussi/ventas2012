//---------------------------------------------------------------------------

#pragma hdrstop

#include "AFIP.h"
#include "auxiliar.h"

#define HOMO
//---------------------------------------------------------------------------

#pragma package(smart_init)

#ifdef HOMO
AnsiString URL_WSAA = "https://wsaahomo.afip.gov.ar/ws/services/LoginCms?wsdl";
AnsiString URL_WSFEv1 = "https://wswhomo.afip.gov.ar/wsfev1/service.asmx?WSDL";
AnsiString URL_WSSrPadronA5 = "https://awshomo.afip.gov.ar/sr-padron/webservices/personaServicioA5?wsdl";
#else
AnsiString URL_WSAA = "https://wsaa.afip.gov.ar/ws/services/LoginCms?wsdl";
AnsiString URL_WSFEv1 = "https://servicios1.afip.gov.ar/wsfev1/service.asmx?WSDL";
AnsiString URL_WSSrPadronA5 = "https://aws.afip.gov.ar/sr-padron/webservices/personaServiceA5?wsdl";
#endif
//---------------------------------------------------------------------------

static inline Variant VWS(AnsiString s)
{
        return Variant(WideString(s));
}
//---------------------------------------------------------------------------

static inline Variant VWS(int s)
{
        return Variant(WideString(s));
}
//---------------------------------------------------------------------------

static inline Variant VWS(double s)
{
        return Variant(WideString(s));
}
//---------------------------------------------------------------------------

Item::Item(int qty, AnsiString ds, double precio, double importe)
{
        Item::qty = qty;
        Item::ds = ds;
        Item::precio = precio;
        Item::importe = importe;
}
//---------------------------------------------------------------------------

AFIP::AFIP(AnsiString fichcert, AnsiString fichclave)
{
        AnsiString error = "No se puede conectar con el componente ";

        try
        {
                // Crear objeto interface Web Service Autenticación y Autorización
                WSAA = Variant::CreateObject("WSAA");
        }
        catch (...)
        {
                throw EAFIP(error + "WSAA");
        }

        try
        {
                // Crear objeto interface Web Service de Factura Electrónica de Mercado Interno
                WSFEv1 = Variant::CreateObject("WSFEv1");
        }
        catch (...)
        {
                throw EAFIP(error + "WSFEv1");
        }

        try
        {
                // Crear objeto interface para generación de F.E. en PDF
                PyFEPDF = Variant::CreateObject("PyFEPDF");
        }
        catch (...)
        {
                throw EAFIP(error + "PyFEPDF");
        }

        try
        {
                // Crear objeto interface para Padron AFIP
                WSSrPadronA5 = Variant::CreateObject("WSSrPadronA5");
        }
        catch (...)
        {
                throw EAFIP(error + "WSSrPadronA5");
        }

        // Deshabilito excepciones para WSAA y WSFEv1
        WSAA.OlePropertySet("LanzarExcepciones", false);
        WSFEv1.OlePropertySet("LanzarExcepciones", false);
        WSSrPadronA5.OlePropertySet("LanzarExcepciones", false);

        AFIP::fichcert = fichcert;
        AFIP::fichclave = fichclave;
}
//---------------------------------------------------------------------------

void AFIP::AutorizarComprobante(FE &fe)
{
        AnsiString excepcion;
        AnsiString cae_comp;
        Variant eventos;

        // Llamo al web service para autenticar
        WSAA.OleFunction("Autenticar",
                         VWS("wsfe"), // servicio a acceder
                         VWS(fichcert), // certificado firmado por la afip
                         VWS(fichclave), // clave privada usada para crear el certificado
                         VWS(URL_WSAA)); // url WSAA

        excepcion = WSAA.OlePropertyGet("Excepcion");
        if (! excepcion.IsEmpty())
        {
                throw EAFIP("Autentificar:\n" + excepcion);
        }

        // Seteo token y sing de autorización
        WSFEv1.OlePropertySet("Token", WSAA.OlePropertyGet("Token"));
        WSFEv1.OlePropertySet("Sign", WSAA.OlePropertyGet("Sign"));

        // Seteo CUIT del emisor
        WSFEv1.OlePropertySet("Cuit", VWS(SinGuiones(cuit)));

        // Conecto al Servicio Web de Facturación
        WSFEv1.OleFunction("Conectar",
                           VWS(""), // cache
                           VWS(URL_WSFEv1)); // url WSFEv1
        excepcion = WSFEv1.OlePropertyGet("Excepcion");
        if (! excepcion.IsEmpty())
        {
                throw EAFIP("Conectar:\n" + excepcion);
        }

        // Verifico el estado de los servidores
        WSFEv1.OleFunction("Dummy");
        if (WSFEv1.OlePropertyGet("AppServerStatus") != VWS("OK") ||
            WSFEv1.OlePropertyGet("DbServerStatus") != VWS("OK") ||
            WSFEv1.OlePropertyGet("AuthServerStatus") != VWS("OK"))
        {
                throw EAFIP("Aparentemente uno de los servidores está fuera de servicio");
        }

        // Obtengo el número del último comprobante
        fe.cbte_nro = WSFEv1.OleFunction("CompUltimoAutorizado",
                                         fe.tipo_cbte,
                                         punto_vta);
        excepcion = WSFEv1.OlePropertyGet("Excepcion");
        if (! excepcion.IsEmpty())
        {
                throw EAFIP("CompUltimoAutorizado:\n" + excepcion);
        }

        // Número del próximo comprobante
        fe.cbte_nro++;

        // Establezco los valores de la factura
        WSFEv1.OleFunction("CrearFactura",
                           VWS(1), // concepto (1: Producto)
                           VWS(80), // tipo_doc (80: CUIT)
                           VWS(SinGuiones(fe.nro_doc)), // nro_doc
                           VWS(fe.tipo_cbte), // tipo_cbte
                           VWS(punto_vta), // punto_vta
                           VWS(fe.cbte_nro), // cbt_desde
                           VWS(fe.cbte_nro), // cbt_hasta
                           VWS(fe.imp_total), // imp_total
                           VWS("0.00"), // imp_tot_conc
                           VWS(fe.imp_neto), // imp_neto
                           VWS(fe.imp_iva), // imp_iva
                           VWS("0.00"), // imp_trib
                           VWS("0.00"), // imp_op_ex
                           VWS(fe.fecha_cbte.FormatString("yyyymmdd")), // fecha_cbte
                           VWS(""), // fecha_venc_pago
                           VWS(""), // fecha_serv_desde
                           VWS(""), // fecha_serv_hasta
                           VWS("PES"), // moneda_id
                           VWS("1.000")); // moneda_ctz

        // Agrego tasa de IVA
        WSFEv1.OleFunction("AgregarIva",
                           VWS(5), // iva_id (5: 21%)
                           VWS(fe.imp_neto), // base_imp
                           VWS(fe.imp_iva)); // importe

        // Si es NC o ND agrego comprobante asociado
        if (fe.tipo_cbte == 2 ||
            fe.tipo_cbte == 3 ||
            fe.tipo_cbte == 7 ||
            fe.tipo_cbte == 8)
        {
                WSFEv1.OleFunction("AgregarCmpAsoc",
                                   VWS(fe.tipo_cbte_asoc),
                                   VWS(punto_vta),
                                   VWS(fe.cbte_nro_asoc));
        }

        // Solicito CAE, y guardo pedido y respuesta XML
        WSFEv1.OleFunction("CAESolicitar");
        excepcion = WSFEv1.OlePropertyGet("Excepcion");
        fichlog.open("AFIP_XML.log", ofstream::out | ofstream::app);
        fichlog << "***** " << Date().FormatString("dd/mm/yyyy").c_str()
                << " - " << Time().FormatString("hh:nn").c_str() << " *****"
                << endl << endl << "XmlRequest:" << endl
                << AnsiString(WSFEv1.OlePropertyGet("XmlRequest")).c_str()
                << endl << endl << "XmlResponse:" << endl
                << AnsiString(WSFEv1.OlePropertyGet("XmlResponse")).c_str()
                << endl << endl << endl;
        fichlog.close();
        if (! excepcion.IsEmpty())
        {
                throw EAFIP("CAESolicitar: " + excepcion);
        }
        fe.cae = WSFEv1.OlePropertyGet("cae");
        fe.obs_afip = WSFEv1.OlePropertyGet("obs");
        if (fe.cae == "" || WSFEv1.OlePropertyGet("Resultado") != VWS("A"))
        {
                throw EAFIP("*** LA OPERACIÓN NO FUE APROBADA ***\n\n" + fe.obs_afip);
        }

        fe.vto_cae = StringToDate(WSFEv1.OlePropertyGet("Vencimiento"));

        // Guardo los eventos (mantenimiento programados y otros mensajes de la AFIP)
        eventos = WSFEv1.OlePropertyGet("eventos");
        fe.eventos.clear();
        for (int c = eventos.ArrayLowBound(); c <= eventos.ArrayHighBound(); c++)
        {
                ficheventos.open("AFIP_eventos.log", ofstream::out | ofstream::app);
                ficheventos << "[" << Date().FormatString("dd/mm/yyyy").c_str()
                            << " - " << Time().FormatString("hh:nn").c_str()
                            << "] " << AnsiString(eventos.GetElement(c)).c_str()
                            << endl;
                ficheventos.close();
                fe.eventos.push_back(AnsiString(eventos.GetElement(c)));
        }

        // Realizo comprobaciones adicionales
        cae_comp = WSFEv1.OleFunction("CompConsultar", fe.tipo_cbte, punto_vta, fe.cbte_nro);
        excepcion = WSFEv1.OlePropertyGet("Excepcion");
        if (! excepcion.IsEmpty())
        {
                throw EAFIPAdv("El comprobante fue autorizado pero no pudo ser recuperado. "
                               "Si este problema se vuelve a repetir por favor informarlo "
                               "al programador.");
        }

        if (fe.cae != cae_comp)
        {
                throw EAFIPAdv("El comprobante fue autorizado pero se encontró una inconsistencia. "
                               "Si este problema se vuelve a repetir por favor informarlo "
                               "al programador.");
        }
}
//---------------------------------------------------------------------------

void AFIP::GenerarPDF(FE &fe, AnsiString fichpdf)
{
        AnsiString excepcion;

        // CUIT del emisor (necesario para el código de barras)
        PyFEPDF.OlePropertySet("CUIT", VWS(SinGuiones(cuit)));

        // Establezco formatos (cantidad de decimales)
        PyFEPDF.OlePropertySet("FmtCantidad", VWS("0.0"));
        PyFEPDF.OlePropertySet("FmtPrecio", VWS("0.2"));

        // Creo la factura (internamente en la interfaz)
        PyFEPDF.OleFunction("CrearFactura",
                            VWS(1), // concepto (1: Producto)
                            VWS(80), // tipo_doc (80: CUIT)
                            VWS(SinGuiones(fe.nro_doc)), // nro_doc
                            VWS(fe.tipo_cbte), // tipo_cbte
                            VWS(punto_vta), // punto_vta
                            VWS(fe.cbte_nro), // cbte_nro
                            VWS(fe.imp_total), // imp_total
                            VWS("0.00"), // imp_tot_conc
                            VWS(fe.imp_neto), // imp_neto
                            VWS(fe.imp_iva), // imp_iva
                            VWS("0.00"), // imp_trib
                            VWS("0.00"), // imp_op_ex
                            VWS(fe.fecha_cbte.FormatString("yyyymmdd")), // fecha_cbte
                            VWS(""), // fecha_venc_pago
                            VWS(""), // fecha_serv_desde
                            VWS(""), // fecha_serv_hasta
                            VWS("PES"), // moneda_id
                            VWS("1.000"), // moneda_ctz
                            VWS(fe.cae), // cae
                            VWS(fe.vto_cae.FormatString("yyyymmdd")), // fecha_vto_cae
                            VWS(fe.id_impositivo), // id_impositivo
                            VWS(fe.nombre_cliente), // nombre_cliente
                            VWS(fe.domicilio_cliente), // domicilio_cliente
                            VWS(""), // pais_dst_cmp
                            VWS(""), // obs_comerciales
                            VWS(fe.obs_generales), // obs_generales
                            VWS("Contado"), // forma_pago
                            VWS(""), // incoterms
                            VWS(""), // idioma_cbte
                            VWS(fe.obs_afip)); // motivos_obs

        // Datos de la empresa
        PyFEPDF.OleFunction("AgregarDato",
                            VWS("logo"),
                            VWS(GetCurrentDir() + "\\plantillas\\logo.png"));
        PyFEPDF.OleFunction("AgregarDato",
                            VWS("MEMBRETE2"),
                            VWS("742 de Evergreen Terrace"));
        PyFEPDF.OleFunction("AgregarDato",
                            VWS("MEMBRETE3"),
                            VWS("Springfield"));
        PyFEPDF.OleFunction("AgregarDato",
                            VWS("IVA"),
                            VWS("IVA Responsable Inscripto"));
        PyFEPDF.OleFunction("AgregarDato",
                            VWS("CUIT"),
                            VWS("CUIT: " + cuit));
        PyFEPDF.OleFunction("AgregarDato",
                            VWS("IIBB"),
                            VWS("Ing. Brutos: 123-456789-0"));
        PyFEPDF.OleFunction("AgregarDato",
                            VWS("Inicio"),
                            VWS("Inicio de Actividad: 01/09/2012"));

        // Más datos del cliente
        PyFEPDF.OleFunction("EstablecerParametro",
                            VWS("localidad_cliente"),
                            VWS(fe.localidad_cliente));
        PyFEPDF.OleFunction("EstablecerParametro",
                            VWS("provincia_cliente"),
                            VWS(fe.provincia_cliente));

        // Blanqueo elementos que no quiero que se vean
        vector<AnsiString> items;
        vector<AnsiString>::const_iterator it;
        items.push_back("Pedido.L");
        items.push_back("Remito.L");
        items.push_back("VencimientoL");
        items.push_back("Item.Codigo");
        items.push_back("Item.Bonificacion");
        items.push_back("Item.AlicuotaIVA");
        items.push_back("descuento.L");
        items.push_back("descuento");
        items.push_back("NGRA.L");
        items.push_back("imp_tot_conc");
        items.push_back("EXENTO.L");
        items.push_back("imp_op_ex");
        items.push_back("custom-tit-transporte");
        //items.push_back("NETO.L");
        //items.push_back("NETO");

        for (it = items.begin(); it != items.end(); it++)
        {
                PyFEPDF.OleFunction("EstablecerParametro",
                                    VWS(*it),
                                    VWS(""));
        }

        // Numero de control
        PyFEPDF.OleFunction("EstablecerParametro",
                            VWS("Pagina"),
                            VWS(AnsiString("Nro Ctrl: ") + fe.nro_ctrl));

        // Items de la factura
        for (unsigned c = 0; c < fe.items.size(); c++)
        {
                PyFEPDF.OleFunction("AgregarDetalleItem",
                                    VWS(""), // u_mtx
                                    VWS(""), // cod_mtx
                                    VWS(""), // codigo
                                    VWS(fe.items[c].ds), // ds
                                    VWS(fe.items[c].qty), // qty
                                    VWS(7), // umed (7: unidades)
                                    VWS(fe.items[c].precio), // precio
                                    VWS(""), // bonif
                                    VWS(1), // iva_id (1: No gravado)
                                    VWS(""), // imp_iva
                                    VWS(fe.items[c].importe), // importe
                                    VWS("")); // despacho
        }

        // Descuento
        if (fe.desc > 0)
        {
                AnsiString ds = "Descuento: " + AnsiString(fe.desc) + "%";
                PyFEPDF.OleFunction("AgregarDetalleItem",
                                    VWS(""), // u_mtx
                                    VWS(""), // cod_mtx
                                    VWS(""), // codigo
                                    VWS(ds), // ds
                                    VWS(""), // qty
                                    VWS(0), // umed (0: sin unidad)
                                    VWS(""), // precio
                                    VWS(""), // bonif
                                    VWS(1), // iva_id (1: No gravado)
                                    VWS(""), // imp_iva
                                    VWS(- fe.imp_desc), // importe
                                    VWS("")); // despacho
        }

        // IVA
        if (fe.imp_iva != 0)
        {
                PyFEPDF.OleFunction("AgregarIva",
                                    VWS(5), // iva_id (5: 21%)
                                    VWS(fe.imp_neto), // base_imp
                                    VWS(fe.imp_iva)); // importe
        }

        // Cargo el formato desde el archivo CSV
        PyFEPDF.OleFunction("CargarFormato",
                            VWS(GetCurrentDir() + "\\plantillas\\factura.csv"));

        // Creo plantilla para esta factura (papel A4 vertical)
        PyFEPDF.OleFunction("CrearPlantilla",
                            VWS("A4"), // papel (A4, letter o legal)
                            VWS("portrait")); // orientacion (portrait o landscape)

        // Proceso la plantilla
        PyFEPDF.OleFunction("ProcesarPlantilla",
                            VWS(2), // num_copias
                            VWS(24), // lineas_max
                            VWS("izq")); // qty_pos

        // Genero el PDF
        PyFEPDF.OleFunction("GenerarPDF", VWS(fichpdf));
}
//---------------------------------------------------------------------------

AnsiString AFIP::ObtenerDenominacion(AnsiString cuit)
{
        AnsiString excepcion;
        Variant ta;
        AnsiString denominacion;

        // Llamo al web service para autenticar
        ta = WSAA.OleFunction("Autenticar",
                              VWS("ws_sr_padron_a5"), // servicio a acceder
                              VWS(fichcert), // certificado firmado por la afip
                              VWS(fichclave), // clave privada usada para crear el certificado
                              VWS(URL_WSAA)); // url WSAA
        excepcion = WSAA.OlePropertyGet("Excepcion");
        if (! excepcion.IsEmpty())
        {
                throw EAFIP("WSSrPadronA5.Autentificar:\n" + excepcion);
        }

        // Seteo ticket acceso
        WSSrPadronA5.OleFunction("SetTicketAcceso", ta);

        // Seteo CUIT del consultor
        WSSrPadronA5.OlePropertySet("Cuit", VWS(SinGuiones(AFIP::cuit)));

        // Conecto al Servicio Web de Padrón A5
        WSSrPadronA5.OleFunction("Conectar",
                                 VWS(""), // cache
                                 VWS(URL_WSSrPadronA5)); // url WSSrPadronA5
        excepcion = WSSrPadronA5.OlePropertyGet("Excepcion");
        if (! excepcion.IsEmpty())
        {
                throw EAFIP("WSSrPadronA5.Conectar:\n" + excepcion);
        }

        // Obtengo la denominación del CUIT
        WSSrPadronA5.OleFunction("Consultar", VWS(SinGuiones(cuit)));
        excepcion = WSSrPadronA5.OlePropertyGet("Excepcion");
        if (! excepcion.IsEmpty())
        {
                throw EAFIP("WSSrPadronA5.Consultar:\n" + excepcion);
        }

        denominacion = WSSrPadronA5.OlePropertyGet("denominacion");

        if (denominacion.IsEmpty()) { // por si retorna una cadena vacía
                throw EAFIP("Error al consultar el CUIT en el padrón de la AFIP");
        }

        return denominacion;
}
//---------------------------------------------------------------------------

