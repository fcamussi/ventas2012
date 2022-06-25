//---------------------------------------------------------------------------

#ifndef basedatosH
#define basedatosH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include "AbBase.hpp"
#include "AbBrowse.hpp"
#include "AbZBrows.hpp"
#include "AbZipper.hpp"
#include "AbCabMak.hpp"
#include "AbCBrows.hpp"
//---------------------------------------------------------------------------
class TBD : public TDataModule
{
__published:	// IDE-managed Components
        TTable *TableClientes;
        TTable *TableProductos;
        TTable *TableDocumentos;
        TTable *TableDocumentosDetalles;
        TTable *TableVentasDiario;
        TTable *TableCuentasCorrientes;
        TTable *TableVentasAnual;
        TTable *TableVentasMensual;
        TTable *TableLocalidades;
        TTable *TableProvincias;
        TTable *TableTiposNegocios;
        TTable *TableFamilias;
        TTable *TableUnidades;
        TDataSource *DataSourceProductos;
        TDataSource *DataSourceClientes;
        TDataSource *DataSourceDocumentosDetalles;
        TDataSource *DataSourceDocumentos;
        TDataSource *DataSourceVentasDiario;
        TDataSource *DataSourceCuentasCorrientes;
        TDataSource *DataSourceVentasAnual;
        TDataSource *DataSourceVentasMensual;
        TDataSource *DataSourceProvincias;
        TDataSource *DataSourceLocalidades;
        TDataSource *DataSourceTiposNegocios;
        TDataSource *DataSourceFamilias;
        TDataSource *DataSourceUnidades;
        TSmallintField *TableCuentasCorrientesTipoDocumento;
        TIntegerField *TableCuentasCorrientesNumeroDocumento;
        TMemoField *TableCuentasCorrientesObservacion;
        TSmallintField *TableDocumentosTipoDocumento;
        TIntegerField *TableCuentasCorrientesNumeroCliente;
        TIntegerField *TableCuentasCorrientesNumeroRegistro;
        TDateField *TableCuentasCorrientesFecha;
        TCurrencyField *TableCuentasCorrientesDebe;
        TCurrencyField *TableCuentasCorrientesHaber;
        TCurrencyField *TableCuentasCorrientesSaldoParcial;
        TIntegerField *TableDocumentosNumeroDocumento;
        TIntegerField *TableDocumentosNumeroCliente;
        TDateField *TableDocumentosFecha;
        TStringField *TableDocumentosNombreFactura;
        TCurrencyField *TableDocumentosSubtotal;
        TFloatField *TableDocumentosDescuento;
        TCurrencyField *TableDocumentosDescuentoTotal;
        TCurrencyField *TableDocumentosSubtotal2;
        TFloatField *TableDocumentosIVA;
        TCurrencyField *TableDocumentosIVATotal;
        TCurrencyField *TableDocumentosTotal;
        TStringField *TableDocumentosDireccion;
        TStringField *TableDocumentosLocalidad;
        TStringField *TableDocumentosProvincia;
        TStringField *TableDocumentosPosicionIVA;
        TStringField *TableDocumentosCUIT;
        TMemoField *TableDocumentosComunicado;
        TTimeField *TableDocumentosHora;
        TTimeField *TableCuentasCorrientesHora;
        TSmallintField *TableDocumentosEstado;
        TSmallintField *TableVentasMensualAno;
        TSmallintField *TableVentasMensualMes;
        TCurrencyField *TableVentasMensualMontoRemitos;
        TCurrencyField *TableVentasMensualMontoFacturas;
        TCurrencyField *TableVentasMensualMontoTotal;
        TStringField *TableDocumentosFormaPago;
        TTable *TableProductosMensual;
        TTable *TableProductosDiario;
        TTable *TableProductosAnual;
        TDataSource *DataSourceProductosMensual;
        TDataSource *DataSourceProductosDiario;
        TDataSource *DataSourceProductosAnual;
        TIntegerField *TableClientesNumeroCliente;
        TDateField *TableClientesFecha;
        TStringField *TableClientesNombreCliente;
        TStringField *TableClientesDireccion;
        TStringField *TableClientesLocalidad;
        TStringField *TableClientesProvincia;
        TStringField *TableClientesTelefono1;
        TStringField *TableClientesTelefono2;
        TStringField *TableClientesFax;
        TStringField *TableClientesMovil;
        TStringField *TableClientesEmail;
        TStringField *TableClientesNombreNegocio;
        TStringField *TableClientesTipoNegocio;
        TStringField *TableClientesNombreFactura;
        TStringField *TableClientesPosicionIVA;
        TStringField *TableClientesCUIT;
        TStringField *TableClientesFormaPago;
        TFloatField *TableClientesDescuento;
        TIntegerField *TableClientesNumeroRegistrosCC;
        TCurrencyField *TableClientesSaldoCC;
        TStringField *TableProductosCodigoProducto;
        TDateField *TableProductosFecha;
        TStringField *TableProductosDescripcion;
        TStringField *TableProductosFamilia;
        TStringField *TableProductosUnidad;
        TCurrencyField *TableProductosPrecio1;
        TCurrencyField *TableProductosPrecio2;
        TCurrencyField *TableProductosPrecio3;
        TSmallintField *TableDocumentosDetallesTipoDocumento;
        TIntegerField *TableDocumentosDetallesNumeroDocumento;
        TIntegerField *TableDocumentosDetallesNumeroRenglon;
        TIntegerField *TableDocumentosDetallesCantidad;
        TStringField *TableDocumentosDetallesCodigoProducto;
        TStringField *TableDocumentosDetallesUnidad;
        TStringField *TableDocumentosDetallesDescripcion;
        TCurrencyField *TableDocumentosDetallesPrecio;
        TBooleanField *TableDocumentosDetallesSinCargo;
        TCurrencyField *TableDocumentosDetallesImporte;
        TDateField *TableVentasDiarioFecha;
        TCurrencyField *TableVentasDiarioMontoRemitos;
        TCurrencyField *TableVentasDiarioMontoFacturas;
        TCurrencyField *TableVentasDiarioMontoTotal;
        TSmallintField *TableVentasAnualAno;
        TCurrencyField *TableVentasAnualMontoRemitos;
        TCurrencyField *TableVentasAnualMontoFacturas;
        TCurrencyField *TableVentasAnualMontoTotal;
        TStringField *TableProvinciasProvincia;
        TStringField *TableTiposNegociosTipoNegocio;
        TStringField *TableUnidadesUnidad;
        TStringField *TableProductosDiarioCodigoProducto;
        TDateField *TableProductosDiarioFecha;
        TIntegerField *TableProductosDiarioCantidadRemito;
        TIntegerField *TableProductosDiarioCantidadFactura;
        TIntegerField *TableProductosDiarioCantidadTotal;
        TStringField *TableProductosMensualCodigoProducto;
        TSmallintField *TableProductosMensualMes;
        TSmallintField *TableProductosMensualAno;
        TIntegerField *TableProductosMensualCantidadRemito;
        TIntegerField *TableProductosMensualCantidadFactura;
        TIntegerField *TableProductosMensualCantidadTotal;
        TStringField *TableProductosAnualCodigoProducto;
        TSmallintField *TableProductosAnualAno;
        TIntegerField *TableProductosAnualCantidadRemito;
        TIntegerField *TableProductosAnualCantidadFactura;
        TIntegerField *TableProductosAnualCantidadTotal;
        TTable *TableNumeracion;
        TDataSource *DataSourceNumeracion;
        TStringField *TableLocalidadesProvincia;
        TStringField *TableLocalidadesLocalidad;
        TStringField *TableFamiliasFamilia;
        TStringField *TableProductosDiarioDescripcion;
        TStringField *TableProductosDiarioUnidad;
        TStringField *TableProductosMensualDescripcion;
        TStringField *TableProductosMensualUnidad;
        TStringField *TableProductosAnualDescripcion;
        TStringField *TableProductosAnualUnidad;
        TAbMakeCab *AbMakeCab;
        TDatabase *Database;
        TTable *TableFacturaElectronica;
        TDataSource *DataSourceFacturaElectronica;
        TSmallintField *TableFacturaElectronicaTipoDocumento;
        TIntegerField *TableFacturaElectronicaNumeroDocumento;
        TSmallintField *TableFacturaElectronicaTipo_cbte;
        TIntegerField *TableFacturaElectronicaCbte_nro;
        TStringField *TableFacturaElectronicaCae;
        TDateField *TableFacturaElectronicaVto_cae;
        TMemoField *TableFacturaElectronicaObs_afip;
        TStringField *TableFacturaElectronicaNombreAFIP;
        TTable *TablePadronAFIP;
        TDataSource *DataSourcePadronAFIP;
        TStringField *TablePadronAFIPCUIT;
        TStringField *TablePadronAFIPNombreAFIP;
        TTable *TableKilogramosMensual;
        TDataSource *DataSourceKilogramosMensual;
        TSmallintField *TableKilogramosMensualMes;
        TSmallintField *TableKilogramosMensualAno;
        TFloatField *TableKilogramosMensualCantidadRemito;
        TFloatField *TableKilogramosMensualCantidadFactura;
        TFloatField *TableKilogramosMensualCantidadTotal;
        TDataSource *DataSourceFacturaTradicional;
        TTable *TableFacturaTradicional;
        TSmallintField *TableFacturaTradicionalTipoDocumento;
        TIntegerField *TableFacturaTradicionalNumeroDocumento;
        TSmallintField *TableFacturaTradicionalTipo_cbte;
        TIntegerField *TableFacturaTradicionalCbte_nro;
        TIntegerField *TableProductosGramos;
        TIntegerField *TableProductosStock;
        TIntegerField *TableNumeracionNumeroCliente;
        TIntegerField *TableNumeracionNumeroRemito;
        TIntegerField *TableNumeracionNumeroFactura;
        TIntegerField *TableNumeracionNumeroCreditoRemito;
        TIntegerField *TableNumeracionNumeroCreditoFactura;
        TIntegerField *TableNumeracionNumeroFacturaElect;
        TIntegerField *TableNumeracionNumeroCreditoElect;
        TIntegerField *TableNumeracionNumeroDebitoElect;
        TIntegerField *TableNumeracionNumeroPedido;
        void __fastcall TableProductosPostError(TDataSet *DataSet,
          EDatabaseError *E, TDataAction &Action);
        void __fastcall TableCuentasCorrientesAfterPost(TDataSet *DataSet);
        void __fastcall TableCuentasCorrientesObservacionSetText(
          TField *Sender, const AnsiString Text);
        void __fastcall TableCuentasCorrientesObservacionGetText(
          TField *Sender, AnsiString &Text, bool DisplayText);
        void __fastcall TableCuentasCorrientesTipoDocumentoGetText(
          TField *Sender, AnsiString &Text, bool DisplayText);
        void __fastcall TableCuentasCorrientesNumeroDocumentoGetText(
          TField *Sender, AnsiString &Text, bool DisplayText);
        void __fastcall TableDocumentosTipoDocumentoGetText(TField *Sender,
          AnsiString &Text, bool DisplayText);
        void __fastcall TableCuentasCorrientesBeforeEdit(
          TDataSet *DataSet);
        void __fastcall TableCuentasCorrientesAfterDelete(
          TDataSet *DataSet);
        void __fastcall TableDocumentosEstadoGetText(TField *Sender,
          AnsiString &Text, bool DisplayText);
        void __fastcall TableVentasMensualMesGetText(TField *Sender,
          AnsiString &Text, bool DisplayText);
        void __fastcall TableProductosMensualMesGetText(TField *Sender,
          AnsiString &Text, bool DisplayText);
        void __fastcall TableProductosDescripcionGetText(
          TField *Sender, AnsiString &Text, bool DisplayText);
        void __fastcall TableProductosUnidadGetText(TField *Sender,
          AnsiString &Text, bool DisplayText);
        void __fastcall TableKilogramosMensualMesGetText(TField *Sender,
          AnsiString &Text, bool DisplayText);
        void __fastcall FlushDataSet(TDataSet *DataSet);

private:	// User declarations

        /* Mis declaraciones */
        int GetBDEError(EDatabaseError *);
        void PackParadox(const AnsiString ADatabase, const AnsiString ATable);

public:		// User declarations
        __fastcall TBD(TComponent* Owner);

        /* Mis declaraciones */
        void ActivarTableCuentasCorrientesAfterPost(bool);
        void ActivarTableCuentasCorrientesBeforeEdit(bool);
        bool ActivarBaseDatos(bool estado);
        void Compactar();
        bool CopiaSeguridad(AnsiString dirdest, AnsiString nombre);
        bool SetearAlias(AnsiString alias);
        void ReducirBackup(AnsiString dir, int conservar);
        bool GuardarSaldos();
        void RefrescarTablas();
        void CancelarTablas();
        void FlushTablas();
        void FlushEnabled(bool value);
};

//---------------------------------------------------------------------------
extern PACKAGE TBD *BD;
//---------------------------------------------------------------------------
#endif
