object FormSeleccionarPeriodo: TFormSeleccionarPeriodo
  Left = 351
  Top = 296
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Seleccionar periodo'
  ClientHeight = 216
  ClientWidth = 335
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 64
    Top = 48
    Width = 34
    Height = 13
    Caption = 'Desde:'
  end
  object Label2: TLabel
    Left = 64
    Top = 88
    Width = 31
    Height = 13
    Caption = 'Hasta:'
  end
  object DateTimePickerDesde: TDateTimePicker
    Left = 176
    Top = 44
    Width = 97
    Height = 21
    CalAlignment = dtaLeft
    Date = 41138.7523184722
    Time = 41138.7523184722
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 0
  end
  object DateTimePickerHasta: TDateTimePicker
    Left = 176
    Top = 84
    Width = 97
    Height = 21
    CalAlignment = dtaLeft
    Date = 41138.7524076157
    Time = 41138.7524076157
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 1
  end
  object ButtonAceptar: TButton
    Left = 67
    Top = 160
    Width = 75
    Height = 25
    Caption = 'Aceptar'
    Default = True
    TabOrder = 2
    OnClick = ButtonAceptarClick
  end
  object ButtonCancelar: TButton
    Left = 195
    Top = 160
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancelar'
    TabOrder = 3
    OnClick = ButtonCancelarClick
  end
end
