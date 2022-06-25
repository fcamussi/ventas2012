object FormBuscarProductos: TFormBuscarProductos
  Left = 244
  Top = 132
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Buscar productos'
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
        FieldName = 'CodigoProducto'
        Title.Caption = 'C'#243'digo producto'
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
        FieldName = 'Descripcion'
        Title.Caption = 'Descripci'#243'n'
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Familia'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Unidad'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Precio1'
        Title.Caption = 'Precio 1'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Precio2'
        Title.Caption = 'Precio 2'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Precio3'
        Title.Caption = 'Precio 3'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Gramos'
        Width = 100
        Visible = True
      end>
  end
  object TableProductos: TTable
    DatabaseName = 'bd2'
    OnFilterRecord = TableProductosFilterRecord
    ReadOnly = True
    TableName = 'productos.DB'
    Left = 16
    Top = 157
  end
  object DataSourceProductos: TDataSource
    DataSet = TableProductos
    Left = 56
    Top = 157
  end
end
