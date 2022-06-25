object FormDialogoProducto: TFormDialogoProducto
  Left = 208
  Top = 168
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
      Left = 16
      Top = 20
      Width = 81
      Height = 13
      Caption = 'C'#243'digo producto:'
    end
    object Label2: TLabel
      Left = 416
      Top = 20
      Width = 68
      Height = 13
      Caption = 'Fecha de alta:'
    end
    object DBEditCodigo: TDBEdit
      Left = 112
      Top = 16
      Width = 120
      Height = 21
      CharCase = ecUpperCase
      DataField = 'CodigoProducto'
      DataSource = BD.DataSourceProductos
      TabOrder = 0
      OnKeyPress = DBEditCodigoKeyPress
    end
    object DBEditFecha: TDBEdit
      Left = 496
      Top = 16
      Width = 80
      Height = 21
      DataField = 'Fecha'
      DataSource = BD.DataSourceProductos
      ReadOnly = True
      TabOrder = 1
    end
  end
  object Panel3: TPanel
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
  object Panel2: TPanel
    Left = 0
    Top = 54
    Width = 610
    Height = 375
    Align = alClient
    TabOrder = 1
    object Label12: TLabel
      Left = 24
      Top = 32
      Width = 59
      Height = 13
      Caption = 'Descripci'#243'n:'
    end
    object Label13: TLabel
      Left = 24
      Top = 81
      Width = 35
      Height = 13
      Caption = 'Familia:'
    end
    object Label17: TLabel
      Left = 24
      Top = 131
      Width = 37
      Height = 13
      Caption = 'Unidad:'
    end
    object LabelPrecio1: TLabel
      Left = 24
      Top = 180
      Width = 42
      Height = 13
      Caption = 'Precio 1:'
    end
    object LabelPrecio2: TLabel
      Left = 24
      Top = 230
      Width = 42
      Height = 13
      Caption = 'Precio 2:'
    end
    object LabelPrecio3: TLabel
      Left = 24
      Top = 280
      Width = 42
      Height = 13
      Caption = 'Precio 3:'
    end
    object Label3: TLabel
      Left = 24
      Top = 328
      Width = 39
      Height = 13
      Caption = 'Gramos:'
    end
    object DBEditDescripcion: TDBEdit
      Left = 136
      Top = 28
      Width = 425
      Height = 21
      DataField = 'Descripcion'
      DataSource = BD.DataSourceProductos
      TabOrder = 0
    end
    object DBLookupComboBoxFamilia: TDBLookupComboBox
      Left = 136
      Top = 77
      Width = 170
      Height = 21
      DataField = 'Familia'
      DataSource = BD.DataSourceProductos
      KeyField = 'Familia'
      ListField = 'Familia'
      ListSource = BD.DataSourceFamilias
      TabOrder = 1
    end
    object BitBtnFamilias: TBitBtn
      Left = 312
      Top = 75
      Width = 24
      Height = 24
      TabOrder = 2
      OnClick = BitBtnFamiliasClick
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
    object DBLookupComboBoxUnidad: TDBLookupComboBox
      Left = 136
      Top = 127
      Width = 170
      Height = 21
      DataField = 'Unidad'
      DataSource = BD.DataSourceProductos
      KeyField = 'Unidad'
      ListField = 'Unidad'
      ListSource = BD.DataSourceUnidades
      TabOrder = 3
    end
    object BitBtnUnidades: TBitBtn
      Tag = 1
      Left = 312
      Top = 125
      Width = 24
      Height = 24
      TabOrder = 4
      OnClick = BitBtnFamiliasClick
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
    object DBEditPrecio1: TDBEdit
      Left = 136
      Top = 176
      Width = 170
      Height = 21
      DataField = 'Precio1'
      DataSource = BD.DataSourceProductos
      TabOrder = 5
      OnKeyPress = DBEditPrecio1KeyPress
    end
    object DBEditPrecio2: TDBEdit
      Left = 136
      Top = 226
      Width = 170
      Height = 21
      DataField = 'Precio2'
      DataSource = BD.DataSourceProductos
      TabOrder = 6
      OnKeyPress = DBEditPrecio1KeyPress
    end
    object DBEditPrecio3: TDBEdit
      Left = 136
      Top = 276
      Width = 170
      Height = 21
      DataField = 'Precio3'
      DataSource = BD.DataSourceProductos
      TabOrder = 7
      OnKeyPress = DBEditPrecio1KeyPress
    end
    object DBEditGramos: TDBEdit
      Left = 136
      Top = 324
      Width = 170
      Height = 21
      DataField = 'Gramos'
      DataSource = BD.DataSourceProductos
      TabOrder = 8
    end
  end
end
