# Null Write + Partial Overwrite — `binary-exploitation-null-write-w`

**Challenge:** `binary-exploitation-null-write-w`  
**Techniques:** Partial overwrite, null byte injection, stack leak, ret2win  
**Difficulty:** Medium  

---

## Overview

This challenge requires bypassing **PIE** and **ASLR** using a **partial overwrite** of a saved return address, combined with a **stack leak** to get the runtime base. Unlike the previous PIE challenge, here we have a stack leak (from a format string or `printf` of a stack address) — but we still use partial overwrite to avoid needing a full `p64()` address.

The twist: the binary has a **null byte restriction** (it stops reading at `\x00`), so we can't send a full `p64()` address if it contains null bytes. Instead, we calculate the offset and overwrite only the low 16 bits (`p16`).

---

## Vulnerability

The binary contains a buffer overflow vulnerability. It also prints a stack address (the saved return address) before reading input, giving us a **stack leak** (no format string needed — it's printed directly). However, the binary stops reading input at a null byte (`\x00`), so we cannot use a full 64‑bit address if it contains a null byte.

**Protections enabled:**
- PIE (Position Independent Executable)
- ASLR (Address Space Layout Randomization)
- NX (Non‑Executable stack)
- No stack canary

---

## The Exploit

### Step 1: Parse the stack leak

The binary prints the saved return address in a known format. We extract it using `re.findall()`:

```python
data = io.recvuntil(b"Send your payload", timeout=10)
addrs = re.findall(rb"\|\s(0x[0-9a-f]{16})\s\|", data)
saved_ret = int(addrs[-1], 16)
```
This gives us the runtime address of the saved return address — we don't need to guess PIE base.

Step 2: Calculate the partial overwrite
We want to jump to win (or win_authed). We know the offset of win from the binary base (RET_TO_WIN = 0x8B5). Instead of writing the full address, we calculate the difference:

```python
p16val = (saved_ret - RET_TO_WIN) & 0xFFFF
```
This gives us the low 16 bits we need to write. The high bits remain the same — they already point to somewhere in the binary, and we're just adjusting the low 16 bits to point to win.

Step 3: Build the payload with null byte handling
The binary stops reading at \x00. To work around this:

We send 117 As, then a \x00 to satisfy the null byte requirement

Then we send Bs to reach the return address offset (0xA8)

Finally, we send the p16 partial overwrite (no null bytes, since it's only 2 bytes)

```python
def build_payload(saved_ret: int) -> bytes:
    p16val = (saved_ret - RET_TO_WIN) & 0xFFFF
    payload = b"A" * 117
    payload += b"\x00"
    payload += b"B" * (OFFSET - len(payload))
    payload += p16(p16val)
    return payload
```
Step 4: Send and get the flag
```python
io.send(build_payload(saved_ret))
io.recvall()
```
