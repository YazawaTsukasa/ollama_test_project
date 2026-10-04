# UE5 Ollama Local LLM Roleplay

A technical prototype for communicating with a locally running Large Language Model (LLM) from Unreal Engine 5 through [Ollama](https://ollama.com/).

The purpose of this project is to **experiment with the integration of Unreal Engine 5 and a local LLM, and to validate the basic implementation of an AI character roleplay system using an LLM**.

UE5 sends structured data such as character settings, scene information, and conversation context to a local LLM through the Ollama API, then receives the generated character response back in UE5.

## Project Status

**Prototype / Technical Experiment**

The following core technical aspects have been successfully verified:

* HTTP communication between UE5 and Ollama
* Local LLM inference
* JSON-based data communication
* AI character roleplay
* Structured character and scene information
* Conversation history and context management

This project is intended for technical experimentation and research. It is not a completed commercial game or a finished end-user tool.

---

## Features

* Unreal Engine 5 and Ollama integration
* Local LLM inference
* HTTP communication between UE5 and Ollama
* AI character roleplay
* Structured character data
* Character personality and background
* Character relationship information
* World and scene information
* Conversation history
* Roleplay context and memory
* JSON-based data communication
* Support for Ollama-compatible models

---

# Current Model

The current development environment uses:

```text
nemotron-mini:4b
```

The project is not limited to this model.

Any model installed in Ollama can be used by changing the model name sent in the API request.

---

# Requirements

Before running the project, install:

* Unreal Engine 5
* Ollama
* `nemotron-mini:4b`

> **Important:** The LLM itself is not included in this repository. Ollama and the required model must be installed separately.

---

# 1. Install Ollama

Ollama is used as the local LLM runtime for this project.

Download Ollama from the official website:

[Ollama Download](https://ollama.com/download)

### Windows

Install the Windows version of Ollama.

After installation, verify it using PowerShell:

```powershell
ollama --version
```

The Ollama local API normally runs at:

```text
http://localhost:11434
```

The project communicates with Ollama through this local API.

---

# 2. Install the LLM Model

Install the model used by the project:

```powershell
ollama pull nemotron-mini:4b
```

Installed models can be checked with:

```powershell
ollama list
```

The following model should be listed:

```text
nemotron-mini:4b
```

---

# 3. Test the Model

Before launching the UE5 project, it is recommended to verify that the model works correctly.

```powershell
ollama run nemotron-mini:4b
```

For example:

```text
Hello
```

If the model returns a response, Ollama and the model are ready.

Exit with:

```text
/bye
```

---

# 4. Run the Unreal Engine Project

After preparing Ollama and the model:

1. Start Ollama.
2. Open the project with Unreal Engine 5.
3. Make sure the configured model name is `nemotron-mini:4b`.
4. Build the project if necessary.
5. Run the project.

The basic communication flow is:

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
           │ Generated Response
           ▼
┌──────────────────────┐
│    Unreal Engine 5   │
└──────────────────────┘
```

---

# 5. Model Configuration

The model name is included in the request sent from Unreal Engine to Ollama.

For example:

```cpp
JsonObject->SetStringField(
    TEXT("model"),
    TEXT("nemotron-mini:4b")
);
```

To use another model, change the model name:

```cpp
JsonObject->SetStringField(
    TEXT("model"),
    TEXT("your-model-name")
);
```

Installed models can be checked with:

```powershell
ollama list
```

---

# 6. Roleplay Data

The project uses structured data to provide the LLM with the information required for roleplay.

The roleplay context can include:

* AI character information
* User character information
* Personality
* Background
* Character relationships
* World information
* Current scene
* Conversation memory
* Conversation history
* Roleplay rules

The project also separates UE5-side data structures from the data structures sent to the LLM.

This allows the LLM-facing data format to be adjusted without directly modifying the game's internal data structures.

---

# 7. Conversation History and Context

The project provides the LLM with relevant conversation context, including:

* Recent conversation history
* Previous conversation summaries
* Character information
* Current scene information
* Character relationships

The project also experiments with summarizing previous conversations when the conversation history becomes long, reducing the amount of context that needs to be sent to the model.

---

# 8. Local LLM Architecture

The project is designed around local LLM inference.

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
       │ Generated Text
       ▼
    Ollama
       │
       ▼
Unreal Engine 5
```

Current development model:

```text
nemotron-mini:4b
```

Because inference is performed locally, the project does not require an external cloud AI API.

---

# 9. Hardware and Performance

Local LLM performance depends on factors such as:

* GPU VRAM
* System RAM
* CPU performance
* Model size
* Quantization
* Context length

Current development environment:

```text
CPU: Intel Core i5-13600K
GPU: NVIDIA GeForce RTX 4060 Ti 8GB
RAM: 32GB
```

The project currently runs `nemotron-mini:4b` locally through Ollama.

Actual inference speed and generation quality may vary depending on the hardware, model, and context size.

---

# 10. Roleplay Limitations

Roleplay quality depends heavily on the selected LLM.

Depending on the model and context length, issues such as the following may occur:

* Confusing character identities
* Generating dialogue or actions for the user character
* Ignoring character settings
* Forgetting previous events
* Losing character consistency
* Responding with explanations instead of roleplay

These issues are particularly noticeable with smaller models or very long and complex contexts.

Different Ollama-compatible models can be tested by changing the configured model name.

---

# Troubleshooting

### Ollama does not respond

Check whether Ollama is installed:

```powershell
ollama --version
```

Check installed models:

```powershell
ollama list
```

You can also test the model directly:

```powershell
ollama run nemotron-mini:4b
```

### Model not found

Install the model:

```powershell
ollama pull nemotron-mini:4b
```

Also make sure that the model name configured in the UE5 project exactly matches:

```text
nemotron-mini:4b
```

---

# License

No license has currently been specified for this project.

---

# Acknowledgements

* Unreal Engine — Epic Games
* Ollama
* NVIDIA Nemotron — NVIDIA
