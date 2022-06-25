object FormConfiguracion: TFormConfiguracion
  Left = 205
  Top = 136
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Configuraci'#243'n'
  ClientHeight = 603
  ClientWidth = 636
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 536
    Width = 636
    Height = 67
    Align = alBottom
    TabOrder = 0
    object BitBtnAceptar: TBitBtn
      Left = 182
      Top = 21
      Width = 80
      Height = 28
      Caption = 'Aceptar'
      Default = True
      TabOrder = 0
      OnClick = BitBtnAceptarClick
    end
    object BitBtnCancelar: TBitBtn
      Left = 374
      Top = 21
      Width = 80
      Height = 28
      Cancel = True
      Caption = 'Cancelar'
      TabOrder = 1
      OnClick = BitBtnCancelarClick
    end
  end
  object PageControl: TPageControl
    Left = 0
    Top = 0
    Width = 636
    Height = 536
    ActivePage = TabSheet5
    Align = alClient
    TabIndex = 2
    TabOrder = 1
    object TabSheet2: TTabSheet
      Caption = 'Cuentas corrientes'
      ImageIndex = 1
      object Label7: TLabel
        Left = 16
        Top = 32
        Width = 93
        Height = 13
        Caption = 'Registros a imprimir:'
      end
      object EditCantidadImprimirCC: TEdit
        Left = 136
        Top = 28
        Width = 57
        Height = 21
        TabOrder = 0
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Impresi'#243'n'
      ImageIndex = 3
      object GroupBox1: TGroupBox
        Left = 16
        Top = 16
        Width = 529
        Height = 257
        Caption = 'Impresoras'
        TabOrder = 0
        object Label9: TLabel
          Left = 16
          Top = 32
          Width = 124
          Height = 13
          Caption = 'Remito (y nota de cr'#233'dito):'
        end
        object Label10: TLabel
          Left = 16
          Top = 64
          Width = 127
          Height = 13
          Caption = 'Factura (y nota de cr'#233'dito):'
        end
        object Label11: TLabel
          Left = 16
          Top = 128
          Width = 35
          Height = 13
          Caption = 'Saldos:'
        end
        object Label12: TLabel
          Left = 16
          Top = 160
          Width = 51
          Height = 13
          Caption = 'Productos:'
        end
        object Label13: TLabel
          Left = 16
          Top = 96
          Width = 81
          Height = 13
          Caption = 'Cuenta corriente:'
        end
        object Label14: TLabel
          Left = 16
          Top = 192
          Width = 47
          Height = 13
          Caption = 'Registros:'
        end
        object Label2: TLabel
          Left = 16
          Top = 224
          Width = 36
          Height = 13
          Caption = 'Pedido:'
        end
        object ComboBoxImpresoraRemito: TComboBox
          Left = 152
          Top = 28
          Width = 160
          Height = 21
          ItemHeight = 13
          TabOrder = 0
        end
        object ComboBoxImpresoraFactura: TComboBox
          Left = 152
          Top = 60
          Width = 160
          Height = 21
          ItemHeight = 13
          TabOrder = 1
        end
        object ComboBoxImpresoraCuentaCorriente: TComboBox
          Left = 152
          Top = 92
          Width = 160
          Height = 21
          ItemHeight = 13
          TabOrder = 2
        end
        object ComboBoxImpresoraSaldos: TComboBox
          Left = 152
          Top = 124
          Width = 160
          Height = 21
          ItemHeight = 13
          TabOrder = 3
        end
        object ComboBoxImpresoraProductos: TComboBox
          Left = 152
          Top = 156
          Width = 160
          Height = 21
          ItemHeight = 13
          TabOrder = 4
        end
        object ComboBoxImpresoraRegistros: TComboBox
          Left = 152
          Top = 188
          Width = 160
          Height = 21
          ItemHeight = 13
          TabOrder = 5
        end
        object CheckBoxRAWRemito: TCheckBox
          Left = 336
          Top = 30
          Width = 89
          Height = 17
          Caption = 'Modo RAW'
          TabOrder = 6
        end
        object CheckBoxRAWFactura: TCheckBox
          Left = 336
          Top = 62
          Width = 89
          Height = 17
          Caption = 'Modo RAW'
          TabOrder = 7
        end
        object CheckBoxRAWCuentaCorriente: TCheckBox
          Left = 336
          Top = 94
          Width = 89
          Height = 17
          Caption = 'Modo RAW'
          TabOrder = 8
        end
        object CheckBoxRAWSaldos: TCheckBox
          Left = 336
          Top = 126
          Width = 89
          Height = 17
          Caption = 'Modo RAW'
          TabOrder = 9
        end
        object CheckBoxRAWProductos: TCheckBox
          Left = 336
          Top = 158
          Width = 89
          Height = 17
          Caption = 'Modo RAW'
          TabOrder = 10
        end
        object CheckBoxRAWRegistros: TCheckBox
          Left = 336
          Top = 190
          Width = 89
          Height = 17
          Caption = 'Modo RAW'
          TabOrder = 11
        end
        object ComboBoxImpresoraPedido: TComboBox
          Left = 152
          Top = 220
          Width = 160
          Height = 21
          ItemHeight = 13
          TabOrder = 12
        end
        object CheckBoxRAWPedido: TCheckBox
          Left = 336
          Top = 222
          Width = 89
          Height = 17
          Caption = 'Modo RAW'
          TabOrder = 13
        end
      end
      object GroupBox3: TGroupBox
        Left = 16
        Top = 280
        Width = 345
        Height = 217
        Caption = 'Espacios'
        TabOrder = 1
        object Label15: TLabel
          Left = 16
          Top = 56
          Width = 230
          Height = 13
          Caption = 'Posterior a remito (y a nota de cr'#233'dito) duplicado:'
        end
        object Label17: TLabel
          Left = 16
          Top = 24
          Width = 217
          Height = 13
          Caption = 'Posterior a remito (y a nota de cr'#233'dito) original:'
        end
        object Label16: TLabel
          Left = 16
          Top = 88
          Width = 222
          Height = 13
          Caption = 'Posterior a factura (y a nota de cr'#233'dito) original:'
        end
        object Label18: TLabel
          Left = 16
          Top = 120
          Width = 235
          Height = 13
          Caption = 'Posterior a factura (y a nota de cr'#233'dito) duplicado:'
        end
        object Label22: TLabel
          Left = 16
          Top = 152
          Width = 133
          Height = 13
          Caption = 'Posterior a cuenta corriente:'
        end
        object Label1: TLabel
          Left = 16
          Top = 184
          Width = 79
          Height = 13
          Caption = 'Posterior pedido:'
        end
        object EditEspaciosPosteriorRD: TEdit
          Left = 264
          Top = 52
          Width = 57
          Height = 21
          TabOrder = 1
        end
        object EditEspaciosPosteriorFO: TEdit
          Left = 264
          Top = 84
          Width = 57
          Height = 21
          TabOrder = 2
        end
        object EditEspaciosPosteriorRO: TEdit
          Left = 264
          Top = 20
          Width = 57
          Height = 21
          TabOrder = 0
        end
        object EditEspaciosPosteriorFD: TEdit
          Left = 264
          Top = 116
          Width = 57
          Height = 21
          TabOrder = 3
        end
        object EditEspaciosPosteriorCC: TEdit
          Left = 264
          Top = 148
          Width = 57
          Height = 21
          TabOrder = 4
        end
        object EditEspaciosPosteriorPedido: TEdit
          Left = 264
          Top = 180
          Width = 57
          Height = 21
          TabOrder = 5
        end
      end
      object GroupBox2: TGroupBox
        Left = 376
        Top = 280
        Width = 169
        Height = 185
        Caption = 'Duplicado'
        TabOrder = 2
        object Label23: TLabel
          Left = 32
          Top = 40
          Width = 119
          Height = 13
          Caption = ' remito (y nota de cr'#233'dito)'
        end
        object CheckBoxImprimirDuplicadoRemito: TCheckBox
          Left = 16
          Top = 24
          Width = 113
          Height = 17
          Caption = 'Imprimir duplicado'
          TabOrder = 0
        end
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'Base de datos'
      ImageIndex = 4
      object Label8: TLabel
        Left = 16
        Top = 32
        Width = 158
        Height = 13
        Caption = 'Ejecuciones antes de compactar:'
      end
      object EditEjecucionesCompactar: TEdit
        Left = 192
        Top = 28
        Width = 57
        Height = 21
        TabOrder = 0
      end
      object GroupBox4: TGroupBox
        Left = 16
        Top = 80
        Width = 185
        Height = 105
        Caption = 'Padr'#243'n AFIP'
        TabOrder = 1
        object ButtonPadronCache: TButton
          Left = 16
          Top = 32
          Width = 153
          Height = 25
          Caption = 'Borrar cache (CUIDADO!!!)'
          TabOrder = 0
          OnClick = ButtonPadronCacheClick
        end
      end
    end
    object TabSheet6: TTabSheet
      Caption = 'Configurar items'
      ImageIndex = 5
      object ButtonItemsClientes: TButton
        Left = 24
        Top = 32
        Width = 81
        Height = 25
        Caption = 'De clientes'
        TabOrder = 0
        OnClick = ButtonItemsClientesClick
      end
      object ButtonItemsProductos: TButton
        Left = 24
        Top = 80
        Width = 81
        Height = 25
        Caption = 'De productos'
        TabOrder = 1
        OnClick = ButtonItemsProductosClick
      end
    end
    object TabSheet7: TTabSheet
      Caption = 'Copia de seguridad'
      ImageIndex = 6
      object Label6: TLabel
        Left = 16
        Top = 32
        Width = 211
        Height = 13
        Caption = 'Directorio para saldos y copias de seguridad:'
      end
      object Label20: TLabel
        Left = 16
        Top = 112
        Width = 163
        Height = 13
        Caption = 'Cantidad de backups a conservar:'
      end
      object BitBtnDirectorioCopia: TBitBtn
        Left = 464
        Top = 26
        Width = 25
        Height = 25
        TabOrder = 1
        OnClick = BitBtnDirectorioCopiaClick
        Glyph.Data = {
          26050000424D26050000000000003604000028000000100000000F0000000100
          080000000000F000000000000000000000000001000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000C0DCC000F0C8
          A400000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          000000000000000000000000000000000000F0FBFF00A4A0A000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00070707070707
          0707070707070707070700000000000000000000000707070707000003030303
          0303030303000707070700FB000303030303030303030007070700FFFB000303
          0303030303030300070700FBFFFB00030303030303030303000700FFFBFFFB00
          0000000000000000000000FBFFFBFFFBFFFBFFFB00070707070700FFFBFFFBFF
          FBFFFBFF00070707070700FBFFFB000000000000000707070707070000000707
          0707070707070000000707070707070707070707070707000007070707070707
          0707000707070007000707070707070707070700000007070707070707070707
          07070707070707070707}
      end
      object EditCopiaDirectorio: TEdit
        Left = 232
        Top = 28
        Width = 217
        Height = 21
        ReadOnly = True
        TabOrder = 0
      end
      object CheckBoxCopiaSalir: TCheckBox
        Left = 16
        Top = 72
        Width = 193
        Height = 17
        Caption = 'Hacer copia de seguridad al salir'
        TabOrder = 2
      end
      object EditBackupsConservar: TEdit
        Left = 192
        Top = 108
        Width = 57
        Height = 21
        TabOrder = 3
      end
    end
    object TabSheet8: TTabSheet
      Caption = 'Identificaci'#243'n'
      ImageIndex = 7
      object Label21: TLabel
        Left = 16
        Top = 32
        Width = 30
        Height = 13
        Caption = 'Clave:'
      end
      object EditClaveIdentificacion: TEdit
        Left = 56
        Top = 28
        Width = 161
        Height = 21
        PasswordChar = '*'
        TabOrder = 0
      end
    end
  end
end
