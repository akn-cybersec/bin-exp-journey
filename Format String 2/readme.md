
# Format String 2

**Platform:** picoCTF  
**Technique:** Format String Write  
**Difficulty:** Medium  

## Challenge Description

A format string vulnerability where we need to write a specific value (`0x67616c66`) to a target address (`0x404060`) to get the flag. The program uses `printf` directly on user input.

## Vulnerability

The program uses `printf` on user input without a format specifier, allowing arbitrary memory writes using `%n` format specifiers. `%n` writes the number of bytes printed so far to a specified address.

## Exploitation

### Step 1: Finding the Offset

Before writing, I needed to know where my input lands on the stack. The commented function `get_remote_offset()` does this:

```python
def get_remote_offset():
    p = remote(HOST, PORT)
    p.sendlineafter(b"say?\n", b"ABCDEFGH" + b".%p"*30)
    response = p.recvall().decode()
    p.close()
    
    leaks = response.split('.')
    for i, leak in enumerate(leaks):
        if "4847464544434241" in leak:  # "ABCDEFGH" in hex
            print(f"Found offset at index: {i}")
            return i
    return None
```
This confirmed the offset was 14 — meaning my input appears as the 14th argument to printf.

Step 2: The Target
Address: 0x404060 (sus_addr)

Value to write: 0x67616c66 ("flag" in ASCII)

Step 3: Using fmtstr_payload
Instead of manually crafting a complex format string, I used pwntools' fmtstr_payload:

python
target_val = 0x67616c66
sus_addr = 0x404060
offset = 14

payload = fmtstr_payload(offset, {sus_addr: target_val}, write_size='byte')
This automatically generates a format string that:

Writes 0x66 (first byte) to 0x404060

Writes 0x6c (second byte) to 0x404061

Writes 0x61 (third byte) to 0x404062

Writes 0x67 (fourth byte) to 0x404063

Using multiple %n writes with appropriate padding.

Step 4: Why write_size='byte' Matters
Writing a 4-byte value (0x67616c66) in one %n would require printing 0x67616c66 bytes — impossible. Instead, write_size='byte' writes one byte at a time using %hhn (write byte), which only requires printing up to 255 bytes per write.

