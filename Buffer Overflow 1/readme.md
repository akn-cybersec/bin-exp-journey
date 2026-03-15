# Buffer Overflow 1

**Platform:** picoCTF  
**Technique:** Buffer Overflow / ret2win  
**Difficulty:** Easy  

## Challenge Description

A simple 32-bit buffer overflow where we need to overwrite the return address to call a win function. The program reads input into a vulnerable buffer without bounds checking.

## Vulnerability

The program uses an unsafe function like `gets()` to read input into a fixed-size buffer. By writing beyond the buffer, we can overwrite the return address on the stack and redirect execution.

## Exploitation

### Step 1: Find the Win Address

Using `nm` or `readelf` on the binary:

```bash
$ nm ./vuln | grep win
080491f6 T win
```
The win function is at 0x080491f6.

Step 2: Determine the Offset
Through fuzzing with cyclic patterns, I found that 44 bytes of padding reach the return address. This was confirmed by:

Sending a unique pattern

Checking where the crash occurred

Calculating the exact offset

Step 3: Craft the Payload
```python
payload = b"A" * 44 + p32(win_addr)
```
`b"A" * 44` – padding to reach the return address

`p32(win_addr)` – win function address packed for 32-bit little-endian

Step 4: Trigger the Overflow
Send the payload when prompted. The function returns to win() instead of its normal flow, printing the flag.
