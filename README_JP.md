# UE5 Ollama Local LLM Roleplay

Unreal Engine 5 から [Ollama](https://ollama.com/) を介して、ローカルで動作する大規模言語モデル（LLM）と通信する技術検証プロジェクトです。

本プロジェクトは、**Unreal Engine 5 とローカル LLM の連携、および LLM を利用した AI キャラクター・ロールプレイシステムの基本的な実装を検証すること**を目的としています。

UE5 から Ollama API を通じて、キャラクター設定、シーン情報、会話コンテキストなどの構造化データをローカル LLM に送信し、生成されたキャラクターの応答を UE5 側で受け取ります。

## Project Status

**Prototype / Technical Experiment**

現在、以下の主要な技術検証を完了しています。

* UE5 と Ollama 間の HTTP 通信
* ローカル LLM による推論
* JSON ベースのデータ通信
* AI キャラクター・ロールプレイ
* キャラクターおよびシーン情報の構造化
* 会話履歴・コンテキストの管理

本プロジェクトは技術検証・研究を目的としたプロトタイプであり、完成した商用ゲームや一般ユーザー向けの完成済みツールではありません。

---

## Features

* Unreal Engine 5 と Ollama の連携
* ローカル LLM による推論
* UE5 と Ollama 間の HTTP 通信
* AI キャラクターによるロールプレイ
* 構造化されたキャラクターデータ
* キャラクターの性格・背景設定
* キャラクター同士の関係性
* 世界観・シーン情報
* 会話履歴
* ロールプレイ用コンテキスト・メモリ
* JSON ベースのデータ通信
* Ollama に対応したモデルの利用

---

# 使用モデル

現在の開発環境では以下のモデルを使用しています。

```text
nemotron-mini:4b
```

本プロジェクトはこのモデルだけに限定されていません。

Ollama にインストールされている別のモデルに変更して使用することもできます。

---

# 必要な環境

本プロジェクトを使用する前に、以下をインストールしてください。

* Unreal Engine 5
* Ollama
* `nemotron-mini:4b`

> **重要:** LLM 本体は本プロジェクトには含まれていません。使用する前に Ollama と必要なモデルを別途インストールしてください。

---

# 1. Ollama のインストール

Ollama は、本プロジェクトで使用するローカル LLM 実行環境です。

公式サイトから Ollama をダウンロードしてください。

[Ollama Download](https://ollama.com/download)

### Windows

Windows 版 Ollama をインストールしてください。

インストール後、PowerShell で以下を実行して正常にインストールされていることを確認できます。

```powershell
ollama --version
```

Ollama のローカル API は通常、以下のアドレスで動作します。

```text
http://localhost:11434
```

本プロジェクトでは、このローカル API を使用して Ollama と通信します。

---

# 2. LLM モデルのインストール

以下のコマンドを実行してモデルをインストールします。

```powershell
ollama pull nemotron-mini:4b
```

インストール済みのモデルは以下で確認できます。

```powershell
ollama list
```

以下のモデルが表示されればインストール完了です。

```text
nemotron-mini:4b
```

---

# 3. モデルの動作確認

UE5 プロジェクトを起動する前に、モデルが正常に動作することを確認することをおすすめします。

```powershell
ollama run nemotron-mini:4b
```

例えば、以下のように入力します。

```text
Hello
```

モデルから正常に応答が返ってくれば、Ollama とモデルの準備は完了です。

終了する場合：

```text
/bye
```

---

# 4. Unreal Engine プロジェクトの起動

Ollama とモデルの準備が完了したら、以下の手順でプロジェクトを起動します。

1. Ollama を起動します。
2. Unreal Engine 5 で本プロジェクトを開きます。
3. 使用するモデルが `nemotron-mini:4b` に設定されていることを確認します。
4. 必要に応じてプロジェクトをビルドします。
5. プロジェクトを実行します。

基本的な通信の流れは以下の通りです。

```text
┌──────────────────────┐
│    Unreal Engine 5   │
│                      │
│   Roleplay System    │
│   Character Data     │
│   Conversation Data  │
└──────────┬───────────┘
           │
           │ HTTP / JSON
           ▼
┌──────────────────────┐
│        Ollama        │
│                      │
│    Local LLM API     │
└──────────┬───────────┘
           │
           ▼
┌──────────────────────┐
│   Local LLM Model    │
│                      │
│  Roleplay Generation │
└──────────┬───────────┘
           │
           │ 生成された応答
           ▼
┌──────────────────────┐
│    Unreal Engine 5   │
└──────────────────────┘
```

---

# 5. モデル設定

Unreal Engine から Ollama に送信するリクエストには、使用するモデル名が含まれています。

例えば：

```cpp
JsonObject->SetStringField(
    TEXT("model"),
    TEXT("nemotron-mini:4b")
);
```

別のモデルを使用する場合は、モデル名を変更することができます。

```cpp
JsonObject->SetStringField(
    TEXT("model"),
    TEXT("your-model-name")
);
```

Ollama にインストールされているモデルは、以下で確認できます。

```powershell
ollama list
```

---

# 6. ロールプレイデータ

本プロジェクトでは、LLM にロールプレイに必要な情報を提供するため、構造化されたデータを使用しています。

ロールプレイ用のコンテキストには、例えば以下の情報が含まれます。

* AI キャラクター情報
* ユーザー側キャラクター情報
* 性格
* 背景
* キャラクター同士の関係性
* 世界観
* 現在のシーン
* 会話メモリ
* 会話履歴
* ロールプレイ用ルール

また、UE5 内部で使用するデータ構造と、LLM に送信するデータ構造を分離しています。

これにより、LLM 向けのデータ形式を調整する際に、ゲーム側の内部データ構造を直接変更する必要がありません。

---

# 7. 会話履歴とコンテキスト

本プロジェクトでは、LLM に必要な会話コンテキストを提供するため、以下の情報を利用します。

* 最近の会話履歴
* 過去の会話の要約
* キャラクター情報
* 現在のシーン情報
* キャラクター同士の関係性

また、会話履歴が長くなった場合に、過去の会話を要約してコンテキスト量を抑える処理についても検証しています。

---

# 8. ローカル LLM を使用した構成

本プロジェクトは、ローカル環境で LLM を実行する構成を基本としています。

```text
Unreal Engine 5
       │
       │ HTTP / JSON
       ▼
    Ollama
       │
       ▼
   Local LLM
       │
       │ 生成されたテキスト
       ▼
    Ollama
       │
       ▼
Unreal Engine 5
```

現在の開発モデル：

```text
nemotron-mini:4b
```

ローカル推論を使用するため、外部のクラウド AI API は必要ありません。

---

# 9. ハードウェアとパフォーマンス

ローカル LLM の性能は、以下の要素によって大きく変化します。

* GPU VRAM
* システム RAM
* CPU 性能
* モデルサイズ
* 量子化方式
* Context Length

現在の開発環境：

```text
CPU: Intel Core i5-13600K
GPU: NVIDIA GeForce RTX 4060 Ti 8GB
RAM: 32GB
```

現在は `nemotron-mini:4b` を Ollama 経由でローカル実行しています。

実際の推論速度や生成品質は、使用するハードウェア、モデル、コンテキストサイズなどによって変化します。

---

# 10. ロールプレイにおける制限

ロールプレイの品質は、使用する LLM に大きく依存します。

モデルやコンテキストの長さによって、以下のような問題が発生する場合があります。

* キャラクターの名前や身份を混同する
* ユーザー側キャラクターの発言や行動を勝手に生成する
* キャラクター設定を無視する
* 過去の出来事を忘れる
* キャラクターを維持できなくなる
* ロールプレイではなく設定やルールの説明を始める

特に、小規模なモデルや非常に長く複雑なコンテキストでは、このような問題が発生しやすくなります。

Ollama に対応している別のモデルに変更して比較することもできます。

---

# Troubleshooting

### Ollama が応答しない場合

Ollama がインストールされているか確認します。

```powershell
ollama --version
```

インストール済みのモデルを確認します。

```powershell
ollama list
```

モデルを直接実行して確認することもできます。

```powershell
ollama run nemotron-mini:4b
```

### モデルが見つからない場合

以下を実行してモデルをインストールしてください。

```powershell
ollama pull nemotron-mini:4b
```

また、UE5 プロジェクトで指定しているモデル名が以下と完全に一致していることを確認してください。

```text
nemotron-mini:4b
```

---

# License

現在、プロジェクトのライセンスは設定されていません。

---

# Acknowledgements

* Unreal Engine — Epic Games
* Ollama
* NVIDIA Nemotron — NVIDIA
