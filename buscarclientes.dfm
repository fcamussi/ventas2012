object FormBuscarClientes: TFormBuscarClientes
  Left = 244
  Top = 132
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Buscar clientes'
  ClientHeight = 366
  ClientWidth = 666
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 256
    Width = 666
    Height = 110
    Align = alBottom
    TabOrder = 0
    object Label1: TLabel
      Left = 340
      Top = 22
      Width = 69
      Height = 13
      Caption = 'en la columna:'
    end
    object Label2: TLabel
      Left = 28
      Top = 22
      Width = 36
      Height = 13
      Caption = 'Buscar:'
    end
    object BitBtnBuscar: TBitBtn
      Left = 149
      Top = 70
      Width = 80
      Height = 28
      Caption = 'Buscar'
      Default = True
      TabOrder = 2
      OnClick = BitBtnBuscarClick
    end
    object EditTexto: TEdit
      Left = 80
      Top = 18
      Width = 215
      Height = 21
      TabOrder = 0
    end
    object ComboBoxColumna: TComboBox
      Left = 424
      Top = 18
      Width = 215
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 1
    end
    object BitBtnCerrar: TBitBtn
      Left = 437
      Top = 70
      Width = 80
      Height = 28
      Cancel = True
      Caption = 'Cerrar'
      TabOrder = 4
      OnClick = BitBtnCerrarClick
    end
    object BitBtnSeleccionar: TBitBtn
      Left = 293
      Top = 70
      Width = 80
      Height = 28
      Caption = 'Seleccionar'
      TabOrder = 3
      OnClick = BitBtnSeleccionarClick
    end
  end
  object DBGrid: TDBGrid
    Left = 0
    Top = 0
    Width = 666
    Height = 256
    Align = alClient
    Options = [dgTitles, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgAlwaysShowSelection, dgCancelOnExit]
    ReadOnly = True
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnDblClick = DBGridDblClick
    Columns = <
      item
        Expanded = False
        FieldName = 'NumeroCliente'
        Title.Caption = 'N'#250'mero cliente'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Fecha'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'NombreCliente'
        Title.Caption = 'Nombre cliente'
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Direccion'
        Title.Caption = 'Direcci'#243'n'
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Localidad'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Provincia'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Telefono1'
        Title.Caption = 'Tel'#233'fono N'#186' 1'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Telefono2'
        Title.Caption = 'Tel'#233'fono N'#186' 2'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Fax'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Movil'
        Title.Caption = 'M'#243'vil'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'E-mail'
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'NombreNegocio'
        Title.Caption = 'Nombre negocio'
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'TipoNegocio'
        Title.Caption = 'Tipo negocio'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'NombreFactura'
        Title.Caption = 'Nombre factura'
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'PosicionIVA'
        Title.Caption = 'Posici'#243'n IVA'
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'CUIT'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'FormaPago'
        Title.Caption = 'Forma de pago'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Descuento'
        Title.Caption = 'Descuento %'
        Width = 100
        Visible = True
      end>
  end
  object TableClientes: TTable
    DatabaseName = 'bd2'
    OnFilterRecord = TableClientesFilterRecord
    ReadOnly = True
    TableName = 'clientes.DB'
    Left = 16
    Top = 173
  end
  object DataSourceClientes: TDataSource
    DataSet = TableClientes
    Left = 56
    Top = 173
  end
end
