# motorized-turntable

[English](./README.md)

M5Stack Roller485Liteを使用した自動回転式ターンテーブルプロジェクトです。  
3Dプリント部品と電子部品を組み合わせて、自作の回転台を作成できます。

**朗報!** Roller485にも対応しています（詳細は末尾に!!）。

## 概要

このプロジェクトは以下の2つの主要部分から構成されています

1. **M5Stack NanoC6用ファームウェア**: M5Stack Roller485Liteを制御して回転を管理します。
2. **3Dプリント用モデル**: ターンテーブルの筐体と機構部品を作成します。

## 必要な部品

- M5Stack NanoC6
- M5Stack Roller485Lite
- Groveケーブル（1本）（NanoC6とRoller485Liteを接続）
- 3Dプリンタ（STLファイル出力用）
- 固定用ネジx4 (M3x5 皿ネジ)
- 滑り止め用ゴム足x4
- トップカバー固定用両面テープまたは接着剤

## セットアップ方法

### ファームウェアのビルドとインストール

1. [PlatformIO](https://platformio.org/)をインストール
2. このリポジトリをクローン
3. PlatformIOでプロジェクトを開く
4. ビルドしてM5Stack NanoC6にアップロード

```bash
# PlatformIOコマンドラインの場合
platformio run -t upload
```

### 3Dモデルの生成と印刷

1. 必要なPythonパッケージをインストール

```bash
cd 3dmodel
pip install -r requirements.txt
```

2. モデルを生成（デフォルトの直径は100mm）

```bash
python turntable.py --diameter 100
```

3. 生成されたSTLファイル（`top.stl`、`bottom.stl`、`upper.stl`）を3Dプリンタで印刷

## 組み立て方法

1. 3Dプリントした部品を準備
2. M5Stack NanoC6とM5Stack Roller485Liteを底部に取り付け、Groveケーブルで接続
3. 上部と底部を組み合わせ、固定用ネジで固定
4. 滑り止め用ゴム足を各部品の下部に取り付ける
5. トップカバーを貼り付ける

## 使用方法

本体にはスイッチや操作パネルがなく、手で回すだけで操作できます。

1. M5Stack NanoC6に給電するため、USBケーブルでPCや電源アダプタに接続
2. ターンテーブルを手で回すと、その回転速度で自動的に回転を継続
3. 回転中でも手で回して速度を変更
4. 手で回転を止めると、モーター制御も停止

## おまけ：Roller485を使う場合

本プロジェクトのファームウェアは、Roller485LiteとRoller485のどちらでもそのまま使えます。  
3Dモデルの`upper.stl`だけRoller485用の`upper_nolite.stl`を利用してください。  
テーブル上に Grobeケーブルを通す穴が空いていますが、必要に応じて`turntable_nolite.py`を編集して3Dモデルを作成してください。

## ライセンス

本プロジェクトはMITライセンスの下で公開しています。詳細は[LICENSE](LICENSE)ファイルをご参照ください。

## 作った人

名称未設定ちゃん (misetteichan)

---
このドキュメントはAIアシスタントCascadeによって作成されました。
