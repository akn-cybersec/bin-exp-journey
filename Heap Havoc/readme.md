**Platform:** picoCTF  
**Technique:** Heap Overflow / GOT Overwrite  
**Difficulty:** Hard  

## Challenge Description

A heap-based buffer overflow that allows us to overwrite a `safe_ptr` on the heap. By controlling this pointer, we can redirect the program to call the `winner` function instead of its intended target.

## Vulnerability

The program allocates a buffer on the heap and uses `gets()` to read input, allowing a heap overflow. Adjacent to the buffer is a `safe_ptr` that gets dereferenced later. By overflowing, we can overwrite this pointer with any address we want.

## Exploitation

### Step 1: Find the Offset

Through analysis, I found that the buffer is 20 bytes before the `safe_ptr`. So:

```python
padding = b'A' * 20
```
Step 2: Find the Safe Pointer Address
The safe_ptr is at 0x0804c060. This is where the pointer itself lives in memory.

```python
safe_ptr = p32(0x0804c060)
```
Step 3: Find the Winner Function
The winner function is at 0x080492b6. This is where we want to redirect execution.

```python
winner_addr = p32(0x080492b6)
```
Step 4: Craft the Payload
We need to:

Overflow the heap buffer (20 bytes of padding)

Overwrite the safe_ptr with the address of the pointer we want to change (0x0804c060)

Write the winner address at the location pointed to by that pointer

Add dummy data to trigger the write

```python
payload = padding + safe_ptr + winner_addr + b" dummy"
```
When the program dereferences the overwritten safe_ptr, it will now point to the winner function, which will be called.

Step 5: Trigger
Send the payload. The program reads it, overwrites the heap, and when it later uses safe_ptr, it jumps to winner and prints the flag.
