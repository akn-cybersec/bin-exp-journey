# 🧨 Binary Exploitation Journey

> One locked year. Infinite growth.

Welcome to my personal journey through the world of binary exploitation.  
This repository documents every challenge I solve, every technique I learn, and every mistake I make along the way.

---

## 📌 Table of Contents

- [🎯 Purpose](#-purpose)
- [🗂 Structure](#-structure)
- [📝 Writeup Format](#-writeup-format)
- [🛠 Tools I Use](#-tools-i-use)
- [📈 Progress](#-progress)
- [⚠️ Disclaimer](#️-disclaimer)
- [🤝 Connect](#-connect)

---

## 🎯 Purpose

This repo exists for three reasons:

1. **Accountability** – Public progress keeps me honest.
2. **Learning** – Teaching is the best way to truly understand.
3. **Proof** – A record of growth from "needs AI for everything" to real understanding.

---

## 🗂 Structure

Challenges are organized by:

- **Platform** – `picoCTF/`, `pwn.college/`, `HTB/`, etc.
- **Technique** – `heap/`, `stack/`, `rop/`, `format-string/`, etc.
- **Difficulty** – `easy/`, `medium/`, `hard/`

Each challenge folder contains:
📁 Platform/
📁 Technique/
📁 difficulty/
📄 challenge-name.md
📄 exploit.py
📄 README.md (if needed)



---

## 📝 Writeup Format

Every solved challenge follows this structure:


# Challenge Name

**Platform:** picoCTF  
**Technique:** Heap Overflow  
**Difficulty:** Easy  

## Vulnerability

Brief explanation of the bug. What went wrong in the code?

## Exploitation

Step-by-step breakdown of how I exploited it:
1. Finding the offset
2. Crafting the payload
3. Triggering the vulnerability
4. Getting the flag

## Script

```python
from pwn import *

# Exploit explanation in comments
HOST = "example.com"
PORT = 1234

p = remote(HOST, PORT)
offset = 32
payload = b"A" * offset + p64(0x401234)

p.sendlineafter(b"prompt:", payload)
p.interactive()
```

## Flag

`picoCTF{redacted_for_your_learning}`

## Lessons Learned

What this challenge taught me:
- New technique
- Mistake I made
- Something I'll do differently next time




---

## 🛠 Tools I Use

| Tool | Purpose |
|------|---------|
| [`pwntools`](https://github.com/Gallopsled/pwntools) | Exploit development |
| [`gdb`](https://www.sourceware.org/gdb/) + [`pwndbg`](https://github.com/pwndbg/pwndbg) | Runtime debugging |
| [`ghidra`](https://ghidra-sre.org/) | Static analysis / decompilation |
| [`radare2`](https://rada.re/n/) | Lightweight analysis |
| [`checksec`](https://github.com/slimm609/checksec.sh) | Binary security analysis |
| [`ropper`](https://github.com/sashs/Ropper) | ROP gadget finding |

---

## 📈 Progress

| Day | Date | Challenges Solved | Techniques Learned |
|-----|------|-------------------|---------------------|
| 1 | 2026-03-09 | 1 | Basic heap overflow |
| 2 | 2026-03-10 | 3 | Heap overflows, return address control |
| 3 | ... | ... | ... |

> Updated regularly as I solve more.

---

## ⚠️ Disclaimer

- All challenges solved here are from **public, educational platforms** (picoCTF, pwn.college, etc.)
- Flags are either **redacted** or posted **after** competitions end
- This repo is for **learning and documentation only**
- If you're stuck on a challenge, try solving it yourself before reading my writeup — the struggle is where growth happens

---

## 🤝 Connect

If you're also learning binary exploitation, feel free to reach out.  
We suffer together, we grow together.

- GitHub: [@akn-cybersec](https://github.com/akn-cybersec)
- Email: fict.0501@gmail.com
- LinkedIn: [Muhammad Abdullah Khan](https://www.linkedin.com/in/muhammad-abdullah-khan-841465384/)

---

**365 days. One commit at a time.**

---

## 🏆 Current Streak

🔥 **Day 2** – March 10, 2024

> "Easy wins or deserved wins." – My Princess

> Author: "kaizen_dragon"
