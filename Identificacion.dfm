object FormIdentificacion: TFormIdentificacion
  Left = 416
  Top = 405
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  ClientHeight = 68
  ClientWidth = 348
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object EditClave: TEdit
    Left = 53
    Top = 24
    Width = 153
    Height = 21
    Ctl3D = True
    MaxLength = 20
    ParentCtl3D = False
    PasswordChar = '*'
    TabOrder = 0
  end
  object ButtonEntrar: TButton
    Left = 221
    Top = 22
    Width = 75
    Height = 25
    Caption = 'Entrar'
    Default = True
    TabOrder = 1
    OnClick = ButtonEntrarClick
  end
end
