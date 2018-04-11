object ConnectionForm: TConnectionForm
  Left = 456
  Top = 233
  Width = 654
  Height = 477
  Caption = 'New Game: Connection'
  Color = clBtnShadow
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PortLabel: TLabel
    Left = 104
    Top = 200
    Width = 59
    Height = 37
    Caption = 'Port'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label1: TLabel
    Left = 96
    Top = 24
    Width = 424
    Height = 74
    Caption = 'CHESS GAME'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -64
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 24
    Top = 112
    Width = 258
    Height = 74
    Caption = 'SERVER'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -64
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 376
    Top = 112
    Width = 228
    Height = 74
    Caption = 'CLIENT'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -64
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 448
    Top = 264
    Width = 59
    Height = 37
    Caption = 'Port'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 408
    Top = 192
    Width = 156
    Height = 37
    Caption = 'IP Address'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object ServerBtn: TButton
    Left = 72
    Top = 288
    Width = 137
    Height = 33
    Caption = 'CREATE GAME ROOM'
    TabOrder = 0
    OnClick = ServerBtnClick
  end
  object ServerPortEdit: TEdit
    Left = 56
    Top = 240
    Width = 169
    Height = 21
    TabOrder = 1
    Text = '2000'
  end
  object ClientPortEdit: TEdit
    Left = 400
    Top = 304
    Width = 169
    Height = 21
    TabOrder = 2
    Text = '2000'
  end
  object ClientAddressEdit: TEdit
    Left = 400
    Top = 232
    Width = 169
    Height = 21
    TabOrder = 3
    Text = '127.0.0.1'
  end
  object ClientBtn: TButton
    Left = 424
    Top = 360
    Width = 129
    Height = 33
    Caption = 'CONNECT TO GAME'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNone
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = ClientBtnClick
  end
end
