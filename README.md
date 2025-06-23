<!---
  SPDX-FileCopyrightText: 2024 Toki Makabe <s23c1130sm@s.chibakoudai.jp>
  SPDX-License-Identifier:BSD-3-Clause
--->

認識工学の課題：DPマッチング課題

# できること
## ookawa_dpmatching.c
1つの無知データと、100種類のデータをそれぞれ全てDPマッチング<BR>
もっとも、局所距離が少ないデータセットを出力する。<BR>
<BR>
もっとも局所距離が少ないDPマッチングデータをCSVとして出力。<BR>
新機能！！　もっとも局所距離が少なかったDPマッチングのルートも画像ファイルとして出力できるようになりました！<BR>
PPM形式で出力されます。GIMP等の対応ソフトで開いてください。<BR>

## ookawa_dpmatching_probability.c
データセット内のすべてのデータを一気にDPマッチングし、それらの正答率をまとめて出すプログラム。<BR>
例：1つ目の無知データ & 100種類のデータ　→　2つ目の無知データ & 100種類のデータ → ....<BR>

出力例
```bash
総数：100 正解数：33 不正解数:67
正解率：33.000000 %
```


## その他準備中...

# 共通
## ファイル配置
基本的には、同じディレクトリに city_mcepdataを入れればOKです。

ookawa_DP<BR>
├ city_mcepdata ディレクトリ（自分でご用意ください）<BR>
├ ookawa_dpmatching_probability.c<BR>
├ ookawa_dpmatching_probability (実行ファイル)<BR>
├ ookawa_dpmatching.c<BR>
├ ookawa_dpmatching (実行ファイル)<BR>
├ pic1.ppm (局所距離が最少時の画像ファイル)<BR>
└ save.csv (局所距離が最少時のDPマッチングデータ)<BR>

## ソースファイルの変更場所
各ソースファイルのdefineを変更します。
```diff
// 入力ファイル (city011_001.txtからcity011_002.txtに変更している様子)
-#define INPUT_FILE "city_mcepdata/city011/city011_001.txt"
+#define INPUT_FILE "city_mcepdata/city011/city011_002.txt"
//データセット（正解）のファイル（ディレクトリ）
#define DATASET_FILE "city_mcepdata/city021/city021_"
//画像を出力する際の出力名
#define PICTURE_PATH "pic1.ppm"
//データセットが何種類あるか
#define DATASET_NUM_MAX 100
//データセットの最大フレーム
#define DATASET_FRAME_MAX 200
//DIMENSIONの区切り個数
#define DATASET_DIMENSION_MAX 15
```

# 使うとき
- 一応BSD3ライセンスでの配布
