<!---
  SPDX-FileCopyrightText: 2024 Toki Makabe <s23c1130sm@s.chibakoudai.jp>
  SPDX-License-Identifier:BSD-3-Clause
--->

認識工学の課題：DPマッチング課題

# できること
## ookawa_dpmatching.c
1つの無知データと、100種類のデータをそれぞれ全てDPマッチング<BR>
最も、累積距離が少ないデータセットを出力する。<BR>
<BR>
~~最も累積距離が少ないDPマッチングデータをCSVとして出力。~~<BR>
~~新機能！！　最も累積距離が少なかったDPマッチングのルートも画像ファイルとして出力できるようになりました！<BR>~~

累積距離等に関わらず、dp_outputディレクトリに、DPマッチング後のCSVファイルと、ルートと局所距離を記したPPM形式の画像ファイルを**全て**出力するように変更しました。

PPM形式で出力されます。GIMP等の対応ソフトで開いてください。<BR>

**動作させる前に、dp_outputディレクトリを作ってください**<BR>
例：```mkdir dp_output```



## ookawa_dpmatching_probability.c
データセット内のすべてのデータを一気にDPマッチングし、それらの正答率をまとめて出すプログラム。<BR>
例：1つ目の無知データ & 100種類のデータ　→　2つ目の無知データ & 100種類のデータ → ....<BR>

出力例
```bash
総数：100 正解数：89 不正解数:11
正解率：89.000000 %
処理時間:44.061238 [s]
```

## ookawa_dpmatching_fast.c
```ookawa_dpmatching_probability.c```の高速化バージョン。DPマッチングを行ごとに処理するが、行ごとの最小を出して、過去に最も最小だったデータセットと比較。最小だった時点でそのデータセットの計算を放棄する。

思ったよりも高速化できなかった。（速くなって2-3秒くらい）

## ookawa_dpmatching_window.c
```#define WINDOW 50```
により整合窓を設定できます。これにより対角線から離れたノードの計算を省略し、高速化を図ります。

# 共通
## ファイル配置
基本的には、同じディレクトリに city_mcepdataを入れればOKです。

```
ookawa_DP
├ city_mcepdata ディレクトリ（自分でご用意ください）
├ ookawa_dpmatching_probability.c
├ ookawa_dpmatching_probability (実行ファイル)
├ ookawa_dpmatching.c
├ ookawa_dpmatching (実行ファイル)
├ pic1.ppm (局所距離が最少時の画像ファイル)
└ save.csv (局所距離が最少時のDPマッチングデータ)
```

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
