# 🧨 Binary Exploitation Journey

> One locked year. Infinite growth.

> Welcome to my personal journey through the world of binary exploitation.  
This repository documents every challenge I solve, every technique I learn, and every mistake I make along the way. I don't just post the flashy solves, but also the easy ones, cuz, not gonna lie, there was a time, when easy today felt impossible. There are days when I can't solve any, when I'm stuck on one challenge for hours, but it doesn't mean, I can't solve. Learning is a continuous, and we can't learn until we are humbled, such days humble me and make me learn more.
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
| 3 | 2026-03-11 | 3 | Format String, offset calculation |
| 4 | 2026-03-12 | 2 | Format string leaks, PIE bypass, stack analysis, custom tooling |
| 5 | 2026-03-13 | 2 | Input Injection, Buffer Overflow, username to shell |
| 6 | 2026-03-14 | 1 | Format String, ret2libc |
| 7 | 2026-03-15 | 2 | Buffer overflow |
| 8 | 2026-03-16 | 0 | Worked on echo valley, tried to solve it, but kept failing |
| 9 | 2026-03-17 | 0 | Worked on echo valley and failed again, went back to basic lectures of assembly and python for better understanding and will be back to it tomorrow |
| 10 | 2026-03-18 | 1 | 32-bit vs 64-bit calling conventions, stack argument placement, and precise offset control for ret2win with multiple arguments |
| 11 | 2026-03-19 | 2 | Format string multi-stage exploitation with PIE and stack leaks, return address overwrite using short writes, and integer overflow via signed wraparound with max value + 1. |
| 12 | 2026-03-20 | 2 | Restricted shell escape via Python, system binary location discovery with find, and PATH hijacking to replace md5sum with a custom script |
| 13 | 2026-03-21 | 3 | ret2win with stack alignment using a single `ret` ROP gadget to fix 64-bit calling convention requirements |
| 14 | 2026-03-22 | 3 | Format string leak + custom C++ generator/decoder, logic exploit with strstr, direct ret2win, and expanding my reusable toolkit |
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
- Discord: kaizen_drag0n

---

**365 days. One commit at a time.**

---

## 🏆 Current Streak

🔥 **Day 14** – March 22, 2026

> "Trust The Process!" – My Princess

> Author: kaizen_dragon
