# UE5 Ollama Local LLM Roleplay

A Unreal Engine 5 project that communicates with a locally running Large Language Model (LLM) through [Ollama](https://ollama.com/).

This project is an experimental implementation of **local AI-powered character roleplay in Unreal Engine 5**. UE5 sends structured roleplay data and conversation history to a local LLM through Ollama and receives the generated character response.

## Features

* Unreal Engine 5 + Ollama integration
* Local LLM inference
* HTTP communication between UE5 and Ollama
* AI character roleplay
* Structured character data
* Character personality and background
* Relationship and world information
* Current scene information
* Conversation history
* Roleplay memory
* JSON-based communication
* Support for different Ollama models

## Current Model

The model currently used during development is:

```text
nemotron-mini:4b
```

The model is provided and executed through Ollama.

The project is not limited to this model. Other models available through Ollama can also be used by changing the model name in the request.

---

# Requirements

Before using this project, install:

* Unreal Engine 5
* Ollama
* `nemotron-mini:4b`

> **Important:** The LLM model is not included in this project. Ollama and the required model must be installed separately before running the project.

---

# 1. Install Ollama

Ollama is used as the local LLM runtime for this project.

Download Ollama from the official website:

[Ollama Download](https://ollama.com/download)

### Windows

Download and install the Windows version of Ollama.

After installation, verify that Ollama is available:

```powershell
ollama --version
```

If the installation was successful, Ollama should display its version information.

Ollama provides a local API that normally runs at:

```text
http://localhost:11434
```

The Unreal Engine project communicates with Ollama through this local API.

---

# 2. Install the LLM Model

After installing Ollama, download the model used by this project.

Run:

```powershell
ollama pull nemotron-mini:4b
```

The model will be downloaded and installed locally.

You can check the installed models with:

```powershell
ollama list
```

You should see:

```text
nemotron-mini:4b
```

---

# 3. Test the Model

Before running the Unreal Engine project, it is recommended to verify that the model works correctly.

Run:

```powershell
ollama run nemotron-mini:4b
```

Then enter a simple message:

```text
Hello
```

If the model returns a response, the Ollama environment is ready.

To exit the interactive session:

```text
/bye
```

---

# 4. Run the Unreal Engine Project

After installing Ollama and the model:

1. Start Ollama.
2. Open the project in Unreal Engine 5.
3. Make sure the configured model name is `nemotron-mini:4b`.
4. Build the project if necessary.
5. Run the project.

The basic communication flow is:

```text
┌──────────────────────┐
│    Unreal Engine 5  │
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
│   nemotron-mini:4b   │
│                      │
│  Roleplay Generation │
└──────────┬───────────┘
           │
           │ Generated Response
           ▼
┌──────────────────────┐
│    Unreal Engine 5  │
└──────────────────────┘
```

---

# 5. Model Configuration

The model name is included in the Ollama request sent by Unreal Engine.

For example:

```cpp
JsonObject->SetStringField(
    TEXT("model"),
    TEXT("nemotron-mini:4b")
);
```

If another model has been installed through Ollama, the model name can be changed accordingly.

For example:

```cpp
JsonObject->SetStringField(
    TEXT("model"),
    TEXT("your-model-name")
);
```

You can check available models with:

```powershell
ollama list
```

---

# 6. Roleplay Data

The project uses structured data to provide the LLM with the information required for roleplay.

The roleplay context can contain:

* AI character information
* User-controlled character information
* Personality
* Background
* Character relationships
* World information
* Current scene
* Conversation memory
* Conversation history
* Roleplay rules

The project separates the **internal Unreal Engine data structures** from the **data structure sent to the LLM**.

This allows the LLM prompt structure to be modified without requiring the internal game data structure to follow the same format.

---

# 7. Conversation and Memory

The project maintains conversation history and provides previous conversation information to the LLM.

The roleplay system can use:

* Recent conversation history
* Previous conversation summaries
* Character information
* Current scene information
* Relationship information

This allows the LLM to maintain context during longer roleplay sessions.

The project is also designed to experiment with conversation summarization when the conversation history becomes too large.

---

# 8. Local LLM Architecture

The project is designed around local LLM inference.

The general architecture is:

```text
Unreal Engine 5
       │
       │ HTTP
       ▼
    Ollama
       │
       ▼
Local LLM
       │
       │ Generated Text
       ▼
    Ollama
       │
       ▼
Unreal Engine 5
```

The default development model is:

```text
nemotron-mini:4b
```

No external AI API is required for the local inference workflow.

---

# 9. Hardware and Performance

Local LLM performance depends on several factors:

* GPU VRAM
* System RAM
* CPU performance
* Model size
* Model quantization
* Context length

Larger models generally require more system resources.

The current development environment uses a local NVIDIA GPU and runs `nemotron-mini:4b` through Ollama.

Different models may provide significantly different results, even when used with the same roleplay prompt.

---

# 10. Roleplay Limitations

The quality of roleplay depends heavily on the selected LLM.

A model may sometimes:

* Confuse character identities
* Speak or act for the user-controlled character
* Ignore parts of the character settings
* Forget previous events
* Break character
* Explain the roleplay instructions instead of responding naturally

These behaviors are particularly noticeable with smaller models and long or complex contexts.

The current project uses `nemotron-mini:4b` as the development model. Other Ollama-compatible models can be tested by changing the model name.

---

# Troubleshooting

### Ollama is not responding

Make sure Ollama is installed and running.

Check:

```powershell
ollama --version
```

Then verify that the required model is installed:

```powershell
ollama list
```

You can also test the model directly:

```powershell
ollama run nemotron-mini:4b
```

### Model not found

If the project reports that the model cannot be found, install it with:

```powershell
ollama pull nemotron-mini:4b
```

Also make sure that the model name in the UE5 project exactly matches:

```text
nemotron-mini:4b
```

---

# License

Add the project's license information here.

# Acknowledgements

* Unreal Engine — Epic Games
* Ollama — Ollama
* NVIDIA Nemotron — NVIDIA
