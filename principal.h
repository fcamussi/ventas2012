//---------------------------------------------------------------------------

#ifndef principalH
#define principalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <AppEvnts.hpp>
//---------------------------------------------------------------------------
class TFormPrincipal : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu;
        TMenuItem *MenuItemArchivos;
        TMenuItem *MenuItemClientes;
        TMenuItem *MenuItemProductos;
        TMenuItem *MenuItemHerramientas;
        TMenuItem *MenuItemRegistros;
        TMenuItem *MenuItemVentasDiario;
        TMenuItem *MenuItemVentasMensual;
        TMenuItem *MenuItemVentasAnual;
        TMenuItem *MenuItemDocumentos;
        TMenuItem *MenuItemConfiguracion;
        TMenuItem *MenuItemCopiaSeguridad;
        TMenuItem *MenuItemFacturacion;
        TMenuItem *MenuItemTradicional;
        TMenuItem *MenuItemRemito;
        TMenuItem *MenuItemCuentas;
        TMenuItem *MenuItemCuentasCorrientes;
        TImageList *ImageList;
        TToolBar *ToolBar;
        TToolButton *ToolButtonPedido;
        TMenuItem *MenuItemSaldos;
        TApplicationEvents *ApplicationEvents;
        TToolButton *ToolButtonRemito;
        TToolButton *ToolButtonFacturaElectronica;
        TToolButton *ToolButtonCuentasCorrientes;
        TToolButton *ToolButton5;
        TToolButton *ToolButton6;
        TToolButton *ToolButtonRegistroDocumentos;
        TToolButton *ToolButtonRegistroVentasDiario;
        TToolButton *ToolButtonSaldos;
        TMenuItem *MenuItemRegistroVentas;
        TMenuItem *MenuItemRegistroProductos;
        TMenuItem *MenuItemProductosDiario;
        TMenuItem *MenuItemProductosMensual;
        TMenuItem *MenuItemProductosAnual;
        TMenuItem *MenuItemCreditoRemito;
        TMenuItem *MenuItemCreditoTradicional;
        TMenuItem *MenuItemStock;
        TMenuItem *MenuItemFacturaTradicional;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *MenuItemFacturaElectronica;
        TMenuItem *MenuItemCreditoElectronica;
        TMenuItem *MenuItemDebitoElectronica;
        TMenuItem *RegistroKilogramos;
        TMenuItem *MenuItemGramosMensual;
        TMenuItem *MenuItemPedido;
        TMenuItem *N3;
        void __fastcall MenuItemConfiguracionClick(TObject *Sender);
        void __fastcall MenuItemCuentasCorrientesClick(TObject *Sender);
        void __fastcall MenuItemRemitoClick(TObject *Sender);
        void __fastcall MenuItemDocumentosClick(TObject *Sender);
        void __fastcall MenuItemSaldosClick(TObject *Sender);
        void __fastcall ApplicationEventsMessage(tagMSG &Msg,
          bool &Handled);
        void __fastcall MenuItemVentasDiarioClick(TObject *Sender);
        void __fastcall MenuItemVentasMensualClick(TObject *Sender);
        void __fastcall MenuItemVentasAnualClick(TObject *Sender);
        void __fastcall MenuItemCopiaSeguridadClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ToolButtonRemitoClick(TObject *Sender);
        void __fastcall ToolButtonFacturaElectronicaClick(TObject *Sender);
        void __fastcall ToolButtonCuentasCorrientesClick(TObject *Sender);
        void __fastcall ToolButtonSaldosClick(TObject *Sender);
        void __fastcall ToolButtonRegistroDocumentosClick(TObject *Sender);
        void __fastcall ToolButtonRegistroVentasDiarioClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall MenuItemProductosDiarioClick(TObject *Sender);
        void __fastcall MenuItemProductosMensualClick(TObject *Sender);
        void __fastcall MenuItemProductosAnualClick(TObject *Sender);
        void __fastcall MenuItemCreditoRemitoClick(TObject *Sender);
        void __fastcall MenuItemCreditoTradicionalClick(TObject *Sender);
        void __fastcall MenuItemStockClick(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall MenuItemFacturaTradicionalClick(TObject *Sender);
        void __fastcall MenuItemFacturaElectronicaClick(TObject *Sender);
        void __fastcall MenuItemCreditoElectronicaClick(TObject *Sender);
        void __fastcall MenuItemDebitoElectronicaClick(TObject *Sender);
        void __fastcall MenuItemGramosMensualClick(TObject *Sender);
        void __fastcall ToolButtonPedidoClick(TObject *Sender);
        void __fastcall MenuItemPedidoClick(TObject *Sender);
        void __fastcall MenuItemClientesClick(TObject *Sender);
        void __fastcall MenuItemProductosClick(TObject *Sender);
private:	// User declarations

        /* Mis declaraciones */
        void HacerCopiaSeguridad();
        void HacerCompactacion();
        void Inicializar();
        void Cerrar();

public:		// User declarations
        __fastcall TFormPrincipal(TComponent* Owner);

};

//---------------------------------------------------------------------------
extern PACKAGE TFormPrincipal *FormPrincipal;
//---------------------------------------------------------------------------
#endif
