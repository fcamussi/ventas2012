object FormRegistroVentasAnual: TFormRegistroVentasAnual
  Left = 232
  Top = 141
  Width = 800
  Height = 600
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = 'Registro anual de ventas'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object DBGrid: TDBGrid
    Left = 0
    Top = 0
    Width = 792
    Height = 547
    Align = alClient
    DataSource = BD.DataSourceVentasAnual
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgAlwaysShowSelection, dgCancelOnExit]
    ReadOnly = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'Ano'
        Title.Caption = 'A'#241'o'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'MontoRemitos'
        Title.Caption = 'Monto remitos'
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'MontoFacturas'
        Title.Caption = 'Monto facturas'
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'MontoTotal'
        Title.Caption = 'Monto total'
        Width = 200
        Visible = True
      end>
  end
  object MainMenu: TMainMenu
    Left = 360
    Top = 216
    object MenuItemArchivo: TMenuItem
      Caption = 'Archivo'
      object MenuItemCerrar: TMenuItem
        Caption = 'Cerrar'
        OnClick = MenuItemCerrarClick
      end
    end
    object MenuItemVer: TMenuItem
      Caption = 'Ver'
      object MenuItemOrdenar: TMenuItem
        Caption = 'Ordenar'
      end
    end
  end
end
