# ROP to Win

**Platform:** picoCTF  
**Technique:** Buffer Overflow + ROP Gadget  
**Difficulty:** Easy-Medium  

## Challenge Description

A buffer overflow challenge where calling the win function directly would cause a crash due to stack alignment issues. A single ROP gadget (`ret`) is used to align the stack before jumping to the win function.

## Vulnerability

The program uses an unsafe read into a buffer, allowing us to overwrite the return address. However, on 64-bit systems, the stack must be 16-byte aligned when calling functions. Directly jumping to `win` may cause a crash if the stack is misaligned.

## Exploitation

### Step 1: Find the Offset

Through fuzzing, I found that **40 bytes** of padding reach the return address.

### Step 2: Find a `ret` Gadget

Using `ROP(elf).find_gadget(['ret'])`, I located a single `ret` instruction in the binary.

```python
ret = rop.find_gadget(['ret'])[0]
```
This gadget does nothing but pop the next value off the stack and jump to it — perfect for alignment.

Step 3: Find the Win Address
```python
win_addr = elf.symbols['win']
```
Step 4: Craft the Payload
Instead of jumping directly to win, we chain:

ret gadget → aligns the stack

win_addr → the actual win function
