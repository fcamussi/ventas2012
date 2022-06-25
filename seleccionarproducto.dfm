object FormSeleccionarProducto: TFormSeleccionarProducto
  Left = 302
  Top = 166
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Seleccionar producto'
  ClientHeight = 368
  ClientWidth = 432
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
    Top = 238
    Width = 432
    Height = 130
    Align = alBottom
    TabOrder = 0
    object Label2: TLabel
      Left = 79
      Top = 32
      Width = 28
      Height = 13
      Caption = 'Filtrar:'
    end
    object EditTexto: TEdit
      Left = 138
      Top = 28
      Width = 215
      Height = 21
      TabOrder = 0
      OnChange = EditTextoChange
    end
    object BitBtnCerrar: TBitBtn
      Left = 268
      Top = 78
      Width = 80
      Height = 28
      Cancel = True
      Caption = 'Cerrar'
      TabOrder = 2
      OnClick = BitBtnCerrarClick
    end
    object BitBtnSeleccionar: TBitBtn
      Left = 84
      Top = 78
      Width = 80
      Height = 28
      Caption = 'Seleccionar'
      Default = True
      TabOrder = 1
      OnClick = BitBtnSeleccionarClick
    end
  end
  object DBGrid: TDBGrid
    Left = 0
    Top = 0
    Width = 432
    Height = 238
    Align = alClient
    DataSource = DataSourceProductos
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
        Title.Caption = 'C'#243'digo'
        Width = 83
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Descripcion'
        Title.Caption = 'Descripci'#243'n'
        Width = 230
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Familia'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Unidad'
        Visible = True
      end>
  end
  object TableProductos: TTable
    DatabaseName = 'bd2'
    OnFilterRecord = TableProductosFilterRecord
    ReadOnly = True
    TableName = 'productos.DB'
    Left = 8
    Top = 317
  end
  object DataSourceProductos: TDataSource
    DataSet = TableProductos
    Left = 48
    Top = 317
  end
end
