object fMain: TfMain
  Left = 251
  Top = 125
  Width = 1096
  Height = 659
  Caption = 'Chess'
  Color = clScrollBar
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnClose = FormClose
  OnConstrainedResize = FormConstrainedResize
  PixelsPerInch = 96
  TextHeight = 13
  object MainMenu1: TMainMenu
    AutoLineReduction = maManual
    Left = 8
    Top = 8
    object hjuh1: TMenuItem
      Caption = 'Play'
      object NewGame1: TMenuItem
        Caption = 'New Game Round'
        OnClick = NewGame1Click
      end
      object Exit1: TMenuItem
        AutoLineReduction = maManual
        Caption = 'Exit Game'
        OnClick = Exit1Click
      end
    end
    object Resolution1: TMenuItem
      Caption = 'Window Size'
      object N800x6001: TMenuItem
        Caption = '800 x 600'
        OnClick = N800x6001Click
      end
      object N1024x6001: TMenuItem
        Caption = '1024 x 600'
        OnClick = N1024x6001Click
      end
      object N1280x8001: TMenuItem
        Caption = '1280 x 800'
        OnClick = N1280x8001Click
      end
    end
    object Colors1: TMenuItem
      Caption = 'Graphic Interface'
      object BackgroundColor1: TMenuItem
        Caption = 'Background Color'
        object Black1: TMenuItem
          Caption = 'Black'
          OnClick = Black1Click
        end
        object White1: TMenuItem
          Caption = 'White'
          OnClick = White1Click
        end
        object Grey1: TMenuItem
          Caption = 'Grey'
          OnClick = Grey1Click
        end
        object Blue1: TMenuItem
          Caption = 'Blue'
          OnClick = Blue1Click
        end
        object Teal1: TMenuItem
          Caption = 'Teal'
          OnClick = Teal1Click
        end
        object Maroon1: TMenuItem
          Caption = 'Maroon'
          OnClick = Maroon1Click
        end
      end
      object GamelogColor1: TMenuItem
        Caption = 'Gamelog Color'
        object Black2: TMenuItem
          Caption = 'Black'
          OnClick = Black2Click
        end
        object White2: TMenuItem
          Caption = 'White'
          OnClick = White2Click
        end
        object Grey2: TMenuItem
          Caption = 'Grey'
          OnClick = Grey2Click
        end
        object Blue2: TMenuItem
          Caption = 'Blue'
          OnClick = Blue2Click
        end
        object Teal2: TMenuItem
          Caption = 'Teal'
          OnClick = Teal2Click
        end
        object Maroon2: TMenuItem
          Caption = 'Maroon'
          OnClick = Maroon2Click
        end
      end
      object FontColor1: TMenuItem
        Caption = 'Gamelog Font Color'
        object Black3: TMenuItem
          Caption = 'Black'
          OnClick = Black3Click
        end
        object White3: TMenuItem
          Caption = 'White'
          OnClick = White3Click
        end
        object Grey3: TMenuItem
          Caption = 'Grey'
          OnClick = Grey3Click
        end
        object Blue3: TMenuItem
          Caption = 'Blue'
          OnClick = Blue3Click
        end
        object Teal3: TMenuItem
          Caption = 'Teal'
          OnClick = Teal3Click
        end
        object Maroon3: TMenuItem
          Caption = 'Maroon'
          OnClick = Maroon3Click
        end
      end
      object FontSize1: TMenuItem
        Caption = 'Gamelog Font Size'
        object N151: TMenuItem
          Caption = 'small'
          OnClick = N151Click
        end
        object N181: TMenuItem
          Caption = 'medium small'
          OnClick = N181Click
        end
        object N182: TMenuItem
          Caption = 'medium'
          OnClick = N182Click
        end
        object N241: TMenuItem
          Caption = 'medium big'
          OnClick = N241Click
        end
        object N301: TMenuItem
          Caption = 'big'
          OnClick = N301Click
        end
      end
    end
    object About1: TMenuItem
      Caption = 'Credits'
      OnClick = About1Click
    end
    object Help1: TMenuItem
      Caption = 'Help'
      OnClick = Help1Click
    end
  end
  object ClientSocket: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 0
    OnConnect = ClientSocketConnect
    OnRead = ClientSocketRead
    Left = 8
    Top = 40
  end
  object ServerSocket: TServerSocket
    Active = False
    Port = 0
    ServerType = stNonBlocking
    OnAccept = ServerSocketAccept
    OnClientRead = ServerSocketClientRead
    Left = 8
    Top = 72
  end
end
