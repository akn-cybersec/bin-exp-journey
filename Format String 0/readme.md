# Format String 0

**Platform:** picoCTF  
**Technique:** Format String Vulnerability  
**Difficulty:** Easy  

## Challenge Description

A simple format string challenge where we need to input specific strings to get the flag. The program asks for two recommendations and prints them back using `printf` directly.

## Vulnerability

The program uses `printf` on user input without a format specifier, creating a classic format string vulnerability. This allows us to use `%x`, `%s`, `%n`, etc., to read from or write to the stack.

## Exploitation

### Step 1: First Input

```python
b"Gr%114d_Cheese"
```
This payload:

Gr – normal text

%114d – prints a decimal number padded to 114 characters

_Cheese – normal text

The %114d causes printf to read a value from the stack and print it as a decimal with width 114. This helps with stack alignment and may leak information.

Step 2: Second Input
python
b"Cla%sic_Che%s%steak"
This payload:

Cla – normal text

%sic – tries to read a string from the stack (%s) followed by "ic"

_Che – normal text

%s – reads another string from the stack

%steak – another %s followed by "teak"

The multiple %s specifiers cause printf to treat stack values as pointers and print the strings they point to. If any of these pointers point to the flag, it gets printed.
