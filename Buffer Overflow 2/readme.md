# buffer overflow 3

**Platform:** picoCTF  
**Technique:** 32-bit ret2win with Arguments  
**Difficulty:** Easy-Medium  

## Challenge Description

A 32-bit buffer overflow where the win function requires two specific arguments. Unlike 64-bit where arguments are passed in registers, 32-bit programs expect arguments on the stack **after** the return address. For buffer overflow challenges, especially when Partial RELRO is enabled, I always use ```nm <binary> | grep <function>``` to quickly find function addresses. It's fast, simple, and gives you exactly what you need without opening Ghidra or GDB. For example, ```nm ./vuln | grep win``` returns something like 08049296 T win, which you can directly use in your exploit. This works perfectly for non-PIE binaries where addresses are static, just grab the address, calculate your offset, and overwrite the return address. It's become my go-to method because it saves time and keeps the focus on exploitation rather than tooling.



## Vulnerability

The program uses an unsafe read into a buffer without bounds checking, allowing us to overwrite the return address and control the stack layout.

## Exploitation

### Step 1: Find the Win Address

Using `nm` or `readelf` on the binary:

```bash
$ nm ./vuln | grep win
08049296 T win
```
The win function is at 0x08049296.

Step 2: Identify Required Arguments
From the source or reverse engineering, the win function expects:

First argument: 0xCAFEF00D

Second argument: 0xF00DF00D

Step 3: Determine the Offset
Through fuzzing with cyclic patterns, I found that 112 bytes of padding reach the return address.

Step 4: Understand 32-bit Stack Layout
In 32-bit x86 architecture:

Arguments are pushed to the stack before the function call

The call instruction pushes the return address

The called function finds its arguments at [ebp+8], [ebp+12], etc.

When we overwrite the return address, we must also provide the arguments after it in the correct positions.
