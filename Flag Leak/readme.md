# Format String Leak — Automated Pipeline

**Platform:** picoCTF  
**Technique:** Format String Leak + Custom Hex Decoder  
**Difficulty:** Medium  

## Challenge Description

A format string vulnerability where the flag is stored on the stack in hex format. We leak stack values and decode them using a custom C++ hex decoder.

## Vulnerability

The program uses `printf` directly on user input, allowing us to read arbitrary stack values with format specifiers like `%p`.

## Exploitation

### Step 1: Leak Stack Values

We send a payload with direct parameter access specifiers:

```python
payload = b"%36$p|%37$p|...|%45$p"
```
These leak stack positions 36 through 45, which contain the flag in hex.

Step 2: Capture Hex Output
The server returns hex values like:

```text
0x6f636970 0x7b465443 0x306c5f49 ...
```
Step 3: Feed to Custom Hex Decoder
The hex values are piped to my C++ hex decoder, which:

Extracts each hex value

Converts to little-endian ASCII

Outputs a clean table

Step 4: Reconstruct Flag
The decoder output is parsed and assembled into the flag.
