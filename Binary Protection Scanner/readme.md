# Binary Protection Scanner

A C++ tool that scans ELF binaries and displays security protections (PIE, canary, NX, RELRO) with exploitation path suggestions. It's just a tool, I made it cuz I was learning the behavior of elf, and trying to understand better. My way of understanding complex things is by doing projects in it, and it's one of that. I made this just to learn binaries and how to play with them. It's completely optional. The only best thing which it gives is: It doesn't just gives the checksec, it also suggests some methods to get flag and that. It's good for beginners, but once you are beyone the beginner line, use 'checksec' and find the type of attack on your own. Cuz we grow like that.

## Features

- **ELF parsing** — reads headers, program headers, dynamic section
- **Protection detection**:
  - PIE (Position Independent Executable)
  - Stack canary
  - NX (No-eXecute)
  - RELRO (Full/Partial/None)
- **Architecture detection** — x86-64, x86, ARM, AArch64
- **Exploitation suggestions** — recommends attack paths based on protections
- **Color-coded output** — green for enabled, red for disabled

## Compilation

```bash
g++ -o scanner scanner.cpp
```
Usage
```bash
./scanner <binary-file>
```
Example
```bash
./scanner ./vuln
```
Output
```text
╔════════════════════════════════════╗
║    Binary Protection Scanner       ║
╚════════════════════════════════════╝

[*] File: ./vuln
[*] Architecture: x86-64 (Little-endian)

Protection          | Status
----------------------------------------
PIE                 | Yes
Stack Canary        | Yes
NX                  | Yes
RELRO               | Full RELRO

[*] Protection Summary:
    - PIE enabled
    - Stack canary present
    - NX enabled

[*] Suggested Exploitation Paths:
    • Full RELRO: GOT overwrite not possible - use other techniques (hooks, vtables, etc.)

[*] Additional Notes:
    • PIE enabled: Addresses will change with ASLR
    • Need information leak to bypass
    • Stack canary present: Need leak or brute force (if fork)
    • NX enabled: Cannot execute shellcode on stack
    • Use ROP/ret2libc instead
```
Code Structure
Elf64_Ehdr — ELF header structure

Elf64_Phdr — program header structure

Elf64_Dyn — dynamic entry structure


BinaryProtectionScanner — main scanning class

How It Works
Read ELF header — validates magic bytes, gets architecture, type

Read program headers — finds PT_DYNAMIC, PT_GNU_STACK, PT_GNU_RELRO

Parse dynamic entries — checks for PIE flag, BIND_NOW

Check canary — scans symbol table for stack protector symbols

Suggest exploitation paths — based on enabled protections

Limitations
64-bit only (ELF64)

Canary detection uses readelf/strings (requires external tools)

No 32-bit support (planned)

Why Build This?
Most people use `checksec`. I built my own to understand ELF structure, program headers, and how protections are detected. It's not meant to replace checksec, but to learn.
