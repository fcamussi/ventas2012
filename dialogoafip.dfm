object FormDialogoAFIP: TFormDialogoAFIP
  Left = 301
  Top = 270
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'AFIP: Observaciones y eventos'
  ClientHeight = 391
  ClientWidth = 561
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel2: TPanel
    Left = 0
    Top = 317
    Width = 561
    Height = 74
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    object ButtonLeido: TButton
      Left = 256
      Top = 24
      Width = 75
      Height = 28
      ModalResult = 1
      TabOrder = 0
    end
  end
  object Memo: TMemo
    Left = 0
    Top = 0
    Width = 561
    Height = 317
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 1
  end
  object Timer: TTimer
    Enabled = False
    OnTimer = TimerTimer
    Left = 272
    Top = 200
  end
end
