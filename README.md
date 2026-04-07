# 🧨 Binary Exploitation Journey

>My strength doesn't come from anything but from "My Princess", who believes in me when I doubt myself, and never lets me doubt myself. To be honest I'm not good at binaries, I'm just good at making her proud of me, and binaries are just one way of doing that.

>One locked year. Infinite growth.

>This repository documents every challenge I solve, every technique I learn, and every mistake I make along the way.

I don't just post the flashy solves; I include the "easy" ones too. Not gonna lie, there was a time when what feels easy today felt impossible. There are days when I can't solve anything, when I'm stuck on a single challenge for hours, but that doesn't mean I can't solve it.
**My Philosophy:**

- **Continuous Learning:** We can't truly learn until we are humbled. Those "stuck" days humble me and push me to learn more.
- **Stay Humble:** Keep learning, and we'll end up where we want to be. Even if we don't, we'll at least have a great story to tell.
- **The Deep Dive:** With binaries, the deeper you go, the more fun they get. Don't just do this as a career skill, it's a legendary hobby to have. In the end, I'll say, don't just learn, just have fun and do what excites you.
- There's  time when quitting seems like the only option, when I'm stuck and just can't solve it, quitting feels like the only way out, but it's not. Quitting is just an illusion of win, while win is a win, win is doing what forces you to quit, win is doing what can't be done. Win is doing what feels impossible.

>If this journey helps you on your own CTF path, a ⭐ is much appreciated!
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
| 15 | 2026-03-23 | 3 | Command injection via environment variable chaining, local variable overwrite with GDB offset calculation, and 64-bit shellcode injection using leaked buffer address with NOP sled |
| 16 | 2026-03-24 | 2 | Canary brute force via byte-by-byte feedback loop and local variable overwrite with manual little-endian packing |
| 17 | 2026-03-25 | 1 | Built an ELF protection scanner in C++ and automated format string leaks with Python + hex decoder pipeline |
| 18 | 2026-03-26 | 3 | Python import hijacking for privilege escalation, stack alignment with a single ret gadget for 64-bit ret2win, and game exploitation via crafted movement sequences |
| 19 | 2026-03-27 | 1 | Binary analysis via file, nm, checksec, and Ghidra for protection detection, offset calculation from buffer size and target value (0x90 - 0x15 = 0x7b), and ret2win with 40-byte offset, and learnt some basics of `RUST` |
| 20 | 2026-03-28 | 1 | Full 32-bit ROP chain with manual gadget hunting, writing /bin/sh to .bss, setting registers for execve syscall, and calling int 0x80 |
| 21 | 2026-03-29 | 0 | Made a CTF challenge |
| 22 | 2026-03-30 | 0 | Developing CTFs/challenges for PWN (might post them later) |
| 23 | 2026-03-31 | 1 | 20-second timed 32-bit ret2win with offset calculation via GDB disassembly and one-liner payload delivery |
| 24 | 2026-04-01 | 3 | Heap overflow with GOT overwrite via safe_ptr manipulation, 20-byte offset calculation, and manual payload crafting using p32() for 32-bit addresses |
| 25 | 2026-04-02 | 0 | Solved a challenge from picoCTF, but couldn't just get the flag cuz I was hitting a wall. Will try to solve it again tomorrow |
| 26 | 2026-04-03 | 1 | 4-bit ROP chain with manual gadget hunting, writing /bin/sh to .bss using mov [rsi], rax, setting up execve syscall (rax=59, rdi, rsi, rdx), and calling syscall — all without libc |
| 27 | 2026-04-04 | 1 | TOCTOU race condition via symlink swapping between a user-owned fake file and root-owned flag file to bypass ownership check and read the flag |
| 28 | 2026-04-05 | 0 | Working on a new tool |
| 29 | 2026-04-06 | 0 | Writing a header to match the speed of C++, and syntax of python |
| 30 | 2026-04-07 | 1 | Fomrat sting+Stack overflow in one, with ASLR |
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
- Discord: [0xk41z3n](https://discord.com/users/0xk41z3n)

---

**365 days. One commit at a time.**

---

## 🏆 Current Streak

🔥 **Day 29** – April 06, 2026

> "Trust The Process!" – My Princess

> Author: kaizen_dragon
