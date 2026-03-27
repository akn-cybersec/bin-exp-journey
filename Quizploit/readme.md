# Buffer Overflow Quiz

**Platform:** picoCTF  
**Technique:** ret2win + Binary Analysis  
**Difficulty:** Easy-Medium  

## Challenge Description

A unique challenge that combines a quiz about binary analysis with a buffer overflow. You must answer 13 questions about the binary correctly, then exploit the overflow to call the win function.

## Vulnerability

The program first asks a series of questions about its own structure (architecture, protection, etc.). After answering correctly, you get a buffer overflow vulnerability that allows you to overwrite the return address.

## Exploitation

### Step 1: Answer the Quiz

The binary asks 13 questions. All answers can be found using standard tools:

| Question | Answer | How to Find |
|----------|--------|-------------|
| Architecture | `64-bit` | `file` command |
| Linking | `dynamic` | `file` command |
| Stripped | `not stripped` | `file` command |
| Buffer size | `0x15` | Ghidra / GDB |
| Goal value | `0x90` | Ghidra / GDB |
| Vulnerability exists? | `yes` | Confirmed |
| Dangerous function | `fgets` | Ghidra / GDB |
| Target function | `win` | `nm` |
| Attack class | `buffer overflow` | Analysis |
| Overflow bytes | `0x7b` | Math: `0x90 - 0x15 = 0x7b` (123 bytes) |
| Mitigation | `NX` | `checksec` |
| Bypass technique | `ROP` | Required for NX |
| Win address | `0x401176` | `nm` / Ghidra |

### Step 2: Craft the Payload

After the quiz, the program asks for input. The buffer is 40 bytes to the return address:

```python
payload = b"A" * 40 + p64(win_addr)
