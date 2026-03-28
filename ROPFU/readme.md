# 32-bit ROP — execve via .bss

**Platform:** picoCTF  
**Technique:** ROP Chain / Syscall  
**Difficulty:** Hard  

## Challenge Description

A 32-bit binary with no win function, no libc leak, but a buffer overflow. We need to build a full ROP chain to write `/bin/sh` into memory and call `execve` via `int 0x80`. It was fun to do. I won't lie by saying: It was easy to do, it wasn't. 

## Vulnerability

The program uses an unsafe read into a buffer, allowing us to overwrite the return address and control execution flow.

## Exploitation

### Step 1: Find Gadgets

We need gadgets to:
- Write strings to memory
- Set registers for the syscall

Gadgets found:

| Gadget | Purpose |
|--------|---------|
| `pop edx; pop ebx; ret` | Set `edx` (destination address) and junk `ebx` |
| `pop eax; ret` | Set `eax` (value to write or syscall number) |
| `pop ecx; ret` | Set `ecx` (argv pointer) |
| `mov [edx], eax; ret` | Write `eax` to address in `edx` |
| `int 0x80` | Syscall |

### Step 2: Find Memory to Write

We use the `.bss` section + offset to avoid overwriting anything important.

```python
data_addr = elf.bss() + 0x100
```
Step 3: Build the Chain
Write /bin to data_addr

Write //sh to data_addr + 4

Set up registers for execve:

eax = 0xb (syscall number)

ebx = data_addr (pointer to /bin/sh)

ecx = 0 (argv = NULL)

edx = 0 (envp = NULL)

Call int 0x80 → shell

Step 4: Trigger
Send the payload. The program returns into our ROP chain, writes the string, sets up registers, and calls execve → shell.
