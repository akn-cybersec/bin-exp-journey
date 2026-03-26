# ret2win with Stack Alignment

**Platform:** picoCTF  
**Technique:** ret2win + Stack Alignment  
**Difficulty:** Easy  

## Challenge Description

A simple 64-bit buffer overflow where we need to call the `flag` function. A direct jump may crash due to stack misalignment, so we use a `ret` gadget to align the stack before calling `flag`.

## Vulnerability

The program uses an unsafe read into a buffer, allowing us to overwrite the return address. On 64-bit systems, the stack must be 16-byte aligned when calling functions. A direct jump can crash if the alignment is off.

## Exploitation

### Step 1: Find the Offset

Through fuzzing, I found the offset to the return address is **72 bytes**.

### Step 2: Find a `ret` Gadget

```python
rop = ROP(elf)
ret_gadget = p64(rop.find_gadget(['ret'])[0])
```
A single ret instruction is enough to align the stack.

Step 3: Find the Flag Function
```python
flag_addr = p64(elf.symbols['flag'])
```
Step 4: Craft the Payload
python
```payload = b"A" * 72 + ret_gadget + flag_addr
```
b"A" * 72 — padding to return address

ret_gadget — aligns the stack

flag_addr — jumps to the flag function

Step 5: Trigger
Send the payload. The program returns to the ret gadget, which pops the flag address into rip with a properly aligned stack.
