# Guessing Game 1 — Full ROP Chain with execve

**Platform:** picoCTF  
**Technique:** 64-bit ROP / Syscall  
**Difficulty:** Hard  

## Challenge Description

A 64-bit binary with a buffer overflow vulnerability. No win function. No libc leak. No easy path. We must build a full ROP chain to write `/bin/sh` into memory and call `execve` via syscall. It took one day to be solved, but I learnt an amazing thing from this one. So, the binary uses: rand() to generate the number which we have to guess, and rand() gives same sequence of numbers everytime. For example the guess#1 was 84 everytime, and similarly, I generated pattern upto 50 guesses by writing selfsolve.c.

## Vulnerability

The program uses `gets()` to read input, allowing a classic buffer overflow. The binary also uses `rand()` without `srand()`, making the "guessing game" predictable.

## Exploitation

### Step 1: Find the Guesses

Since `rand()` is used without `srand()`, the sequence is the same every time. I brute-forced the number once and found it's always `84`.

### Step 2: Find the Offset

Through fuzzing, I found the offset to the return address is **120 bytes**.

### Step 3: Find the Gadgets

Using `ROPgadget`, I found all the necessary gadgets:

| Gadget | Address | Purpose |
|--------|---------|---------|
| `pop rsi; ret` | `0x410b93` | Set destination address |
| `pop rax; ret` | `0x4005af` | Set value to write |
| `pop rdi; ret` | `0x4006a6` | Set first argument |
| `pop rdx; ret` | `0x410602` | Set third argument |
| `mov qword ptr [rsi], rax; ret` | `0x47ffe1` | Write to memory |
| `xor rax, rax; ret` | `0x445690` | Zero out register |
| `syscall` | `0x40138c` | Call kernel |

### Step 4: Find a Writable Location

The `.bss` section is writable. I chose `0x6ba0e0` as my data section.

### Step 5: Build the ROP Chain

1. **Write `/bin//sh`** to `data_section`
2. **Write null terminator** to `data_section + 8`
3. **Set up registers** for `execve`:
   - `rdi = data_section` (pointer to `/bin/sh`)
   - `rsi = 0` (argv = NULL)
   - `rdx = 0` (envp = NULL)
   - `rax = 59` (execve syscall number)
4. **Call syscall**

### Step 6: Send the Payload

```python
padding = b"A" * 120
payload = padding + rop_chain
```
