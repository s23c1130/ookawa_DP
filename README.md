認識工学の課題：DPマッチング課題

# できること
## ookawa_dpmatching.c
1つの無知データと、100種類のデータをそれぞれ全てDPマッチング
もっとも、局所距離が少ないデータセットを出力する。

もっとも局所距離が少ないDPマッチングデータをCSVとして出力。
新機能！！　もっとも局所距離が少なかったDPマッチングのルートも画像ファイルとして出力できるようになりました！
PPM形式で出力されます。GIMP等の対応ソフトで開いてください。

## ookawa_dpmatching_probability.c
データセット内のすべてのデータを一気にDPマッチングし、それらの正答率をまとめて出すプログラム。
例：1つ目の無知データ & 100種類のデータ　→　2つ目の無知データ & 100種類のデータ → ....

## その他準備中...

# 共通
## ファイル配置
基本的には、同じディレクトリに city_mcepdataを入れればOKです。

ookawa_DP
├ city_mcepdata ディレクトリ（自分でご用意ください）
├ ookawa_dpmatching_probability.c
├ ookawa_dpmatching_probability (実行ファイル)
├ ookawa_dpmatching.c
├ ookawa_dpmatching (実行ファイル)
├ pic1.ppm (局所距離が最少時の画像ファイル)
└ save.csv (局所距離が最少時のDPマッチングデータ)

## ソースファイルの変更場所


# 使うとき
- 一応BSD3ライセンスでの配布
- Starつけてくれるとめちゃうれしい
