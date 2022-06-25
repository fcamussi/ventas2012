object FormDialogoCliente: TFormDialogoCliente
  Left = 210
  Top = 148
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  ClientHeight = 503
  ClientWidth = 610
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl: TPageControl
    Left = 0
    Top = 54
    Width = 610
    Height = 375
    ActivePage = TabSheet2
    Align = alClient
    TabIndex = 1
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'Datos del cliente'
      object Label3: TLabel
        Left = 24
        Top = 40
        Width = 91
        Height = 13
        Caption = 'Nombre del cliente:'
      end
      object Label4: TLabel
        Left = 24
        Top = 83
        Width = 48
        Height = 13
        Caption = 'Direcci'#243'n:'
      end
      object Label5: TLabel
        Left = 24
        Top = 165
        Width = 49
        Height = 13
        Caption = 'Localidad:'
      end
      object Label6: TLabel
        Left = 24
        Top = 122
        Width = 47
        Height = 13
        Caption = 'Provincia:'
      end
      object Label7: TLabel
        Left = 24
        Top = 212
        Width = 69
        Height = 13
        Caption = 'Tel'#233'fono N'#186' 1:'
      end
      object Label8: TLabel
        Left = 24
        Top = 255
        Width = 20
        Height = 13
        Caption = 'Fax:'
      end
      object Label9: TLabel
        Left = 344
        Top = 255
        Width = 28
        Height = 13
        Caption = 'M'#243'vil:'
      end
      object Label10: TLabel
        Left = 24
        Top = 298
        Width = 31
        Height = 13
        Caption = 'E-mail:'
      end
      object Label11: TLabel
        Left = 344
        Top = 212
        Width = 24
        Height = 13
        Caption = 'N'#186' 2:'
      end
      object DBEditNombreCliente: TDBEdit
        Left = 136
        Top = 36
        Width = 425
        Height = 21
        DataField = 'NombreCliente'
        DataSource = BD.DataSourceClientes
        TabOrder = 0
        OnExit = DBEditNombreClienteExit
      end
      object DBEditDireccion: TDBEdit
        Left = 136
        Top = 79
        Width = 425
        Height = 21
        DataField = 'Direccion'
        DataSource = BD.DataSourceClientes
        TabOrder = 1
      end
      object DBLookupComboBoxLocalidad: TDBLookupComboBox
        Left = 136
        Top = 165
        Width = 170
        Height = 21
        DataField = 'Localidad'
        DataSource = BD.DataSourceClientes
        KeyField = 'Localidad'
        ListField = 'Localidad'
        ListSource = BD.DataSourceLocalidades
        TabOrder = 2
      end
      object DBLookupComboBoxProvincia: TDBLookupComboBox
        Left = 136
        Top = 122
        Width = 170
        Height = 21
        DataField = 'Provincia'
        DataSource = BD.DataSourceClientes
        KeyField = 'Provincia'
        ListField = 'Provincia'
        ListSource = BD.DataSourceProvincias
        TabOrder = 3
      end
      object DBEditTelefono1: TDBEdit
        Left = 136
        Top = 208
        Width = 170
        Height = 21
        DataField = 'Telefono1'
        DataSource = BD.DataSourceClientes
        TabOrder = 5
      end
      object DBEditTelefono2: TDBEdit
        Left = 391
        Top = 208
        Width = 170
        Height = 21
        DataField = 'Telefono2'
        DataSource = BD.DataSourceClientes
        TabOrder = 6
      end
      object DBEditFax: TDBEdit
        Left = 136
        Top = 251
        Width = 170
        Height = 21
        DataField = 'Fax'
        DataSource = BD.DataSourceClientes
        TabOrder = 7
      end
      object DBEditMovil: TDBEdit
        Left = 391
        Top = 251
        Width = 170
        Height = 21
        DataField = 'Movil'
        DataSource = BD.DataSourceClientes
        TabOrder = 8
      end
      object DBEditEmail: TDBEdit
        Left = 136
        Top = 294
        Width = 425
        Height = 21
        DataField = 'E-mail'
        DataSource = BD.DataSourceClientes
        TabOrder = 9
      end
      object BitBtnProvincias: TBitBtn
        Left = 312
        Top = 163
        Width = 24
        Height = 24
        TabOrder = 4
        OnClick = BitBtnLocalidadesClick
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000120B0000120B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00500000000055
          555557777777775F55550FFFFFFFFF0555557F5555555F7FFF5F0FEEEEEE0000
          05007F555555777775770FFFFFF0BFBFB00E7F5F5557FFF557770F0EEEE000FB
          FB0E7F75FF57775555770FF00F0FBFBFBF0E7F57757FFFF555770FE0B00000FB
          FB0E7F575777775555770FFF0FBFBFBFBF0E7F5575FFFFFFF5770FEEE0000000
          FB0E7F555777777755770FFFFF0B00BFB0007F55557577FFF7770FEEEEE0B000
          05557F555557577775550FFFFFFF0B0555557FF5F5F57575F55500F0F0F0F0B0
          555577F7F7F7F7F75F5550707070700B055557F7F7F7F7757FF5507070707050
          9055575757575757775505050505055505557575757575557555}
        NumGlyphs = 2
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Datos administrativos'
      ImageIndex = 1
      object Label12: TLabel
        Left = 24
        Top = 40
        Width = 98
        Height = 13
        Caption = 'Nombre del negocio:'
      end
      object Label13: TLabel
        Left = 24
        Top = 83
        Width = 80
        Height = 13
        Caption = 'Tipo de negocio:'
      end
      object Label14: TLabel
        Left = 24
        Top = 126
        Width = 91
        Height = 13
        Caption = 'Nombre en factura:'
      end
      object Label15: TLabel
        Left = 24
        Top = 169
        Width = 63
        Height = 13
        Caption = 'Posici'#243'n IVA:'
      end
      object Label16: TLabel
        Left = 24
        Top = 212
        Width = 28
        Height = 13
        Caption = 'CUIT:'
      end
      object Label17: TLabel
        Left = 24
        Top = 255
        Width = 74
        Height = 13
        Caption = 'Forma de pago:'
      end
      object Label18: TLabel
        Left = 24
        Top = 298
        Width = 55
        Height = 13
        Caption = 'Descuento:'
      end
      object Label19: TLabel
        Left = 198
        Top = 298
        Width = 8
        Height = 13
        Caption = '%'
      end
      object DBEditNombreNegocio: TDBEdit
        Left = 136
        Top = 36
        Width = 425
        Height = 21
        DataField = 'NombreNegocio'
        DataSource = BD.DataSourceClientes
        TabOrder = 0
        OnExit = DBEditNombreNegocioExit
      end
      object DBLookupComboBoxTipo: TDBLookupComboBox
        Left = 136
        Top = 79
        Width = 170
        Height = 21
        DataField = 'TipoNegocio'
        DataSource = BD.DataSourceClientes
        KeyField = 'TipoNegocio'
        ListField = 'TipoNegocio'
        ListSource = BD.DataSourceTiposNegocios
        TabOrder = 1
      end
      object DBEditCUIT: TDBEdit
        Left = 136
        Top = 208
        Width = 170
        Height = 21
        DataField = 'CUIT'
        DataSource = BD.DataSourceClientes
        TabOrder = 4
      end
      object DBEditDescuento: TDBEdit
        Left = 136
        Top = 294
        Width = 57
        Height = 21
        DataField = 'Descuento'
        DataSource = BD.DataSourceClientes
        TabOrder = 5
        OnKeyPress = DBEditDescuentoKeyPress
      end
      object DBComboBoxPosicionIVA: TDBComboBox
        Left = 136
        Top = 165
        Width = 170
        Height = 21
        Style = csDropDownList
        DataField = 'PosicionIVA'
        DataSource = BD.DataSourceClientes
        ItemHeight = 13
        Items.Strings = (
          'Responsable inscripto'
          'Responsable monotributo'
          'Consumidor final')
        TabOrder = 3
      end
      object BitBtnTiposNegocios: TBitBtn
        Tag = 1
        Left = 312
        Top = 77
        Width = 24
        Height = 24
        TabOrder = 2
        OnClick = BitBtnLocalidadesClick
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000120B0000120B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00500000000055
          555557777777775F55550FFFFFFFFF0555557F5555555F7FFF5F0FEEEEEE0000
          05007F555555777775770FFFFFF0BFBFB00E7F5F5557FFF557770F0EEEE000FB
          FB0E7F75FF57775555770FF00F0FBFBFBF0E7F57757FFFF555770FE0B00000FB
          FB0E7F575777775555770FFF0FBFBFBFBF0E7F5575FFFFFFF5770FEEE0000000
          FB0E7F555777777755770FFFFF0B00BFB0007F55557577FFF7770FEEEEE0B000
          05557F555557577775550FFFFFFF0B0555557FF5F5F57575F55500F0F0F0F0B0
          555577F7F7F7F7F75F5550707070700B055557F7F7F7F7757FF5507070707050
          9055575757575757775505050505055505557575757575557555}
        NumGlyphs = 2
      end
      object DBComboBoxNombreFactura: TDBComboBox
        Left = 136
        Top = 122
        Width = 425
        Height = 21
        Style = csDropDownList
        DataField = 'NombreFactura'
        DataSource = BD.DataSourceClientes
        ItemHeight = 13
        TabOrder = 6
      end
      object DBComboBoxFormaPago: TDBComboBox
        Left = 136
        Top = 251
        Width = 170
        Height = 21
        Style = csDropDownList
        DataField = 'FormaPago'
        DataSource = BD.DataSourceClientes
        ItemHeight = 13
        Items.Strings = (
          'Contado'
          'Cuenta corriente')
        TabOrder = 7
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 610
    Height = 54
    Align = alTop
    BevelOuter = bvNone
    Ctl3D = True
    ParentCtl3D = False
    TabOrder = 0
    object Label1: TLabel
      Left = 32
      Top = 20
      Width = 40
      Height = 13
      Caption = 'N'#250'mero:'
    end
    object Label2: TLabel
      Left = 416
      Top = 20
      Width = 68
      Height = 13
      Caption = 'Fecha de alta:'
    end
    object DBEditNumero: TDBEdit
      Left = 80
      Top = 16
      Width = 70
      Height = 21
      DataField = 'NumeroCliente'
      DataSource = BD.DataSourceClientes
      ReadOnly = True
      TabOrder = 0
    end
    object DBEditFecha: TDBEdit
      Left = 496
      Top = 16
      Width = 80
      Height = 21
      DataField = 'Fecha'
      DataSource = BD.DataSourceClientes
      ReadOnly = True
      TabOrder = 1
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 429
    Width = 610
    Height = 74
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 2
    object BitBtnAceptar: TBitBtn
      Left = 163
      Top = 24
      Width = 80
      Height = 28
      Caption = 'Aceptar'
      Default = True
      TabOrder = 0
      OnClick = BitBtnAceptarClick
    end
    object BitBtnCancelar: TBitBtn
      Left = 367
      Top = 24
      Width = 80
      Height = 28
      Cancel = True
      Caption = 'Cancelar'
      TabOrder = 1
      OnClick = BitBtnCancelarClick
    end
  end
end
