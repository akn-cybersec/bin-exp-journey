# Format String to System

**Platform:** picoCTF  
**Technique:** Format String + ret2libc  
**Difficulty:** Medium  

## Challenge Description

A format string vulnerability where the program helpfully leaks a libc address (`setvbuf`) at the start. The goal is to overwrite the GOT entry of `puts` with the address of `system`, so that any subsequent call to `puts` actually executes `system`. I liked this one.

## Vulnerability

The program has a format string vulnerability that allows arbitrary writes using `%n`. Combined with the libc leak, we can redirect execution to `system()` and get a shell.

## Exploitation

### Step 1: Receive the Leak

The program prints:
libc: 0x7f...

text

This is the actual runtime address of `setvbuf` in libc.

### Step 2: Calculate libc Base and system Address

```python
libc.address = leak - libc.symbols['setvbuf']
system_addr = libc.symbols['system']
```
Once we have the base, all other libc addresses can be calculated using their known offsets.

Step 3: Choose the Target
puts@got at 0x404018 is a perfect target:

It's writable (GOT)

The program will call puts again

Overwriting it with system means puts becomes system

Step 4: Find the Format String Offset
Through fuzzing with AAAA%p.%p..., I found that the input lands at position 38. This is where our format string payload will write.

Step 5: Generate the Payload
python
payload = fmtstr_payload(offset, {puts_got: system_addr})
This automatically generates a format string that writes system_addr to puts_got using multiple %n writes with proper padding.

Step 6: Send and Win
When the program next calls puts, it actually calls system. By sending a dummy string afterward, we trigger system and get a shell.
