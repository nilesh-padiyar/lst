# lst

> A simple `ls` clone built from scratch to learn C and UNIX APIs.

`lst` is a small command-line utility that displays directory contents in a simple format directly in your terminal.

Built as a learning project, lst focuses on simplicity, readability, and understanding low-level filesystem traversal in C.

This project exists purely for learning. The goal is to understand how a command like `ls` works internally by building it from scratch using C and UNIX system APIs, rather than relying on existing implementations.

---

## Demo

![lst demo](assets/demo.gif)

---

## Project Structure

```text
lst
├── assets/
│   └── demo.gif
├── src/
│   └── main.c
├── LICENSE
├── Makefile
├── README.md
└── lst
```

---

## Installation

### Build from Source

#### Requirements

* GCC
* GNU Make

#### Clone the Repository

```bash
git clone https://github.com/nilesh-padiyar/lst.git
cd lst
```

#### 1. Build and Run

```bash
make
./lst
```

#### 2. Install System-Wide (Optional)

```bash
sudo make install
```

After installation:

```bash
lst
```

can be executed from anywhere.

Uninstall:

```bash
sudo make uninstall
```

> If you are using other compiler than `GCC` then change the C Compiler (`CC`) in `Makefile` to your preferred C compiler.

---


## Goals

* Learn directory traversal (`opendir()`, `readdir()`, `closedir()`)
* Understand file metadata (`stat()`)
* Practice writing command-line utilities in C
* Explore UNIX programming concepts and APIs

---

## Current Status

lst is currently in pre-release and under active development.

The project is functional but still evolving as new features and improvements are added.

---

## Author

**Nilesh Padiyar**

---
