#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <map>
#include <memory>
#include <cstdint>

using namespace std;

// Correct ELF64 type definitions
typedef uint64_t Elf64_Addr;
typedef uint64_t Elf64_Off;
typedef uint16_t Elf64_Half;
typedef uint32_t Elf64_Word;
typedef int32_t  Elf64_Sword;
typedef uint64_t Elf64_Xword;
typedef int64_t  Elf64_Sxword;  // Changed from int32_t to int64_t

#define EI_NIDENT 16

// ELF64 Header - corrected structure
struct Elf64_Ehdr {
    unsigned char e_ident[EI_NIDENT];
    Elf64_Half    e_type;
    Elf64_Half    e_machine;
    Elf64_Word    e_version;
    Elf64_Addr    e_entry;
    Elf64_Off     e_phoff;
    Elf64_Off     e_shoff;
    Elf64_Word    e_flags;
    Elf64_Half    e_ehsize;
    Elf64_Half    e_phentsize;
    Elf64_Half    e_phnum;
    Elf64_Half    e_shentsize;
    Elf64_Half    e_shnum;
    Elf64_Half    e_shstrndx;
};

// ELF64 program header
struct Elf64_Phdr {
    Elf64_Word    p_type;
    Elf64_Word    p_flags;
    Elf64_Off     p_offset;
    Elf64_Addr    p_vaddr;
    Elf64_Addr    p_paddr;
    Elf64_Xword   p_filesz;
    Elf64_Xword   p_memsz;
    Elf64_Xword   p_align;
};

// ELF64 dynamic entry - corrected
struct Elf64_Dyn {
    Elf64_Sxword d_tag;      // This should be 64-bit on ELF64
    union {
        Elf64_Xword d_val;
        Elf64_Addr d_ptr;
    } d_un;
};

// ELF64 section header (for completeness)
struct Elf64_Shdr {
    Elf64_Word    sh_name;
    Elf64_Word    sh_type;
    Elf64_Xword   sh_flags;
    Elf64_Addr    sh_addr;
    Elf64_Off     sh_offset;
    Elf64_Xword   sh_size;
    Elf64_Word    sh_link;
    Elf64_Word    sh_info;
    Elf64_Xword   sh_addralign;
    Elf64_Xword   sh_entsize;
};

// ELF type constants
#define ET_NONE   0
#define ET_REL    1
#define ET_EXEC   2
#define ET_DYN    3
#define ET_CORE   4

// Program header types
// Program header flags
#define PF_X 0x1                // Execute
#define PF_W 0x2                // Write
#define PF_R 0x4                // Read
#define PF_MASKOS 0x0ff00000    // OS-specific
#define PF_MASKPROC 0xf0000000  // Processor-specific
#define PT_NULL    0
#define PT_LOAD    1
#define PT_DYNAMIC 2
#define PT_INTERP  3
#define PT_NOTE    4
#define PT_SHLIB   5
#define PT_PHDR    6
#define PT_TLS     7
#define PT_GNU_EH_FRAME 0x6474e550
#define PT_GNU_STACK    0x6474e551
#define PT_GNU_RELRO    0x6474e552
#define PT_GNU_PROPERTY 0x6474e553

// Dynamic tags
#define DT_NULL     0
#define DT_NEEDED   1
#define DT_PLTRELSZ 2
#define DT_PLTGOT   3
#define DT_HASH     4
#define DT_STRTAB   5
#define DT_SYMTAB   6
#define DT_RELA     7
#define DT_RELASZ   8
#define DT_RELAENT  9
#define DT_STRSZ    10
#define DT_SYMENT   11
#define DT_INIT     12
#define DT_FINI     13
#define DT_SONAME   14
#define DT_RPATH    15
#define DT_SYMBOLIC 16
#define DT_REL      17
#define DT_RELSZ    18
#define DT_RELENT   19
#define DT_PLTREL   20
#define DT_DEBUG    21
#define DT_TEXTREL  22
#define DT_JMPREL   23
#define DT_BIND_NOW 24
#define DT_INIT_ARRAY 25
#define DT_FINI_ARRAY 26
#define DT_INIT_ARRAYSZ 27
#define DT_FINI_ARRAYSZ 28
#define DT_RUNPATH  29
#define DT_FLAGS    30
#define DT_FLAGS_1  0x6ffffffb
#define DT_VERNEEDED 0x6ffffffe
#define DT_VERSYM   0x6fffffff

// Flag constants
#define DF_1_NOW    0x00000001
#define DF_1_PIE    0x08000000

// Machine types
#define EM_X86_64   62
#define EM_386      3
#define EM_ARM      40
#define EM_AARCH64  183

class BinaryProtectionScanner {
private:
    string filename;
    ifstream file;
    Elf64_Ehdr ehdr;
    vector<Elf64_Phdr> phdrs;
    vector<Elf64_Dyn> dyn_entries;
    
    bool pie = false;
    bool canary = false;
    bool nx = false;
    bool relro = false;
    bool partial_relro = false;
    string arch;
    string endian;
    bool is_elf = false;
    
    void read_header() {
        file.seekg(0);
        file.read(reinterpret_cast<char*>(&ehdr), sizeof(ehdr));
        
        // Check ELF magic
        if (file.gcount() == sizeof(ehdr) &&
            ehdr.e_ident[0] == 0x7f && 
            ehdr.e_ident[1] == 'E' && 
            ehdr.e_ident[2] == 'L' && 
            ehdr.e_ident[3] == 'F') {
            is_elf = true;
        }
    }
    
    void read_program_headers() {
        if (!is_elf || ehdr.e_phnum == 0) return;
        
        file.seekg(ehdr.e_phoff);
        phdrs.resize(ehdr.e_phnum);
        file.read(reinterpret_cast<char*>(phdrs.data()), ehdr.e_phnum * sizeof(Elf64_Phdr));
    }
    
    void read_dynamic_entries() {
        for (const auto& phdr : phdrs) {
            if (phdr.p_type == PT_DYNAMIC) {
                file.seekg(phdr.p_offset);
                size_t entry_count = phdr.p_filesz / sizeof(Elf64_Dyn);
                if (entry_count > 0) {
                    dyn_entries.resize(entry_count);
                    file.read(reinterpret_cast<char*>(dyn_entries.data()), phdr.p_filesz);
                }
                break;
            }
        }
    }
    
    void check_architecture() {
        if (!is_elf) {
            arch = "Not an ELF file";
            return;
        }
        
        // Check architecture
        switch (ehdr.e_machine) {
            case EM_X86_64: arch = "x86-64"; break;
            case EM_386: arch = "x86"; break;
            case EM_ARM: arch = "ARM"; break;
            case EM_AARCH64: arch = "AArch64"; break;
            default: arch = "Unknown (" + to_string(ehdr.e_machine) + ")";
        }
        
        // Check endianness
        if (ehdr.e_ident[5] == 1) endian = "Little-endian";
        else if (ehdr.e_ident[5] == 2) endian = "Big-endian";
        else endian = "Unknown";
    }
    
    void check_pie() {
        // Check if it's a DYN (shared object/PIE executable)
        if (ehdr.e_type == ET_DYN) {
            pie = true;
        }
        
        // Also check for PIE flag in dynamic section
        for (const auto& dyn : dyn_entries) {
            if (dyn.d_tag == DT_FLAGS_1 && (dyn.d_un.d_val & DF_1_PIE)) {
                pie = true;
                break;
            }
        }
    }
    
    void check_nx() {
        bool found_stack = false;
        for (const auto& phdr : phdrs) {
            if (phdr.p_type == PT_GNU_STACK) {
                // If stack is executable (PF_X set), NX is disabled
                nx = !(phdr.p_flags & PF_X);
                found_stack = true;
                break;
            }
        }
        
        if (!found_stack) {
            // Default: assume NX is enabled if no PT_GNU_STACK
            nx = true;
        }
    }
    
    void check_relro() {
        bool has_relro = false;
        
        for (const auto& phdr : phdrs) {
            if (phdr.p_type == PT_GNU_RELRO) {
                has_relro = true;
                break;
            }
        }
        
        if (!has_relro) {
            relro = false;
            partial_relro = false;
            return;
        }
        
        // Check for BIND_NOW in dynamic entries
        bool bind_now = false;
        for (const auto& dyn : dyn_entries) {
            if (dyn.d_tag == DT_BIND_NOW) {
                bind_now = true;
                break;
            }
            if (dyn.d_tag == DT_FLAGS_1 && (dyn.d_un.d_val & DF_1_NOW)) {
                bind_now = true;
                break;
            }
        }
        
        if (bind_now) {
            relro = true;
            partial_relro = false;
        } else {
            relro = false;
            partial_relro = true;
        }
    }
    
    void check_canary() {
        // Look for canary symbols using readelf
        // This is a simplified check
        string cmd = "readelf -s " + filename + " 2>/dev/null | grep -q -E '(__stack_chk_fail|__intel_security_cookie|__security_cookie|__stack_chk_guard)'";
        int result = system(cmd.c_str());
        canary = (result == 0);
        
        // Also check for canary in .eh_frame or .rodata as fallback
        if (!canary) {
            cmd = "strings " + filename + " 2>/dev/null | grep -q -E 'stack_chk_fail|Stack protector|SSP'";
            result = system(cmd.c_str());
            canary = (result == 0);
        }
    }
    
    string get_protection_color(bool enabled) {
        return enabled ? "\033[32mYes\033[0m" : "\033[31mNo\033[0m";
    }
    
    string get_relro_status() {
        if (relro) return "\033[32mFull RELRO\033[0m";
        if (partial_relro) return "\033[33mPartial RELRO\033[0m";
        return "\033[31mNo RELRO\033[0m";
    }
    
    vector<string> suggest_exploitation_path() {
        vector<string> suggestions;
        
        if (!nx) {
            suggestions.push_back("• NX disabled: Can use shellcode on stack (ret2shellcode)");
        }
        
        if (!canary) {
            suggestions.push_back("• No stack canary: Buffer overflows possible (ret2libc, ROP)");
        }
        
        if (!pie && !nx) {
            suggestions.push_back("• No PIE + NX disabled: Easy ret2shellcode with fixed addresses");
        }
        
        if (!pie && nx && canary) {
            suggestions.push_back("• No PIE but NX+Canary: Consider information leak first, then ROP");
        }
        
        if (pie && !canary && nx) {
            suggestions.push_back("• PIE enabled but no canary: Need info leak for bypass, then ROP");
        }
        
        if (!relro && !pie) {
            suggestions.push_back("• No RELRO: GOT overwrite possible");
        }
        
        if (partial_relro && !pie) {
            suggestions.push_back("• Partial RELRO: Can overwrite non-PLT GOT entries after leak");
        }
        
        if (relro) {
            suggestions.push_back("• Full RELRO: GOT overwrite not possible - use other techniques (hooks, vtables, etc.)");
        }
        
        if (suggestions.empty()) {
            suggestions.push_back("• All protections enabled: Consider advanced techniques (JOP, COOP, ret2dlresolve, etc.)");
        }
        
        return suggestions;
    }
    
public:
    BinaryProtectionScanner(const string& fname) : filename(fname) {
        file.open(filename, ios::binary);
        if (!file.is_open()) {
            throw runtime_error("Cannot open file: " + filename);
        }
    }
    
    void scan() {
        try {
            read_header();
            
            if (!is_elf) {
                return;
            }
            
            read_program_headers();
            read_dynamic_entries();
            
            check_architecture();
            check_pie();
            check_nx();
            check_relro();
            check_canary();
            
        } catch (const exception& e) {
            cerr << "Error during scan: " << e.what() << endl;
        }
    }
    
    void print_results() {
        if (!is_elf) {
            cout << "\n[!] " << filename << " is not a valid ELF file!" << endl;
            return;
        }
        
        cout << "\n╔════════════════════════════════════╗" << endl;
        cout << "║    Binary Protection Scanner       ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;
        cout << "\n[*] File: " << filename << endl;
        cout << "[*] Architecture: " << arch << " (" << endian << ")\n" << endl;
        
        cout << left << setw(20) << "Protection" << " | Status" << endl;
        cout << string(40, '-') << endl;
        
        cout << left << setw(20) << "PIE" << " | " << get_protection_color(pie) << endl;
        cout << left << setw(20) << "Stack Canary" << " | " << get_protection_color(canary) << endl;
        cout << left << setw(20) << "NX" << " | " << get_protection_color(nx) << endl;
        cout << left << setw(20) << "RELRO" << " | " << get_relro_status() << endl;
        
        cout << "\n[*] Protection Summary:" << endl;
        cout << "    - " << (pie ? "PIE enabled" : "No PIE (ASLR bypass possible with info leak)") << endl;
        cout << "    - " << (canary ? "Stack canary present" : "No stack canary") << endl;
        cout << "    - " << (nx ? "NX enabled" : "NX disabled (executable stack)") << endl;
        
        cout << "\n[*] Suggested Exploitation Paths:" << endl;
        auto suggestions = suggest_exploitation_path();
        for (const auto& suggestion : suggestions) {
            cout << suggestion << endl;
        }
        
        // Additional notes
        cout << "\n[*] Additional Notes:" << endl;
        if (pie) {
            cout << "    • PIE enabled: Addresses will change with ASLR" << endl;
            cout << "    • Need information leak to bypass" << endl;
        } else {
            cout << "    • No PIE: Addresses are predictable (good for ROP)" << endl;
        }
        
        if (canary) {
            cout << "    • Stack canary present: Need leak or brute force (if fork)" << endl;
        } else {
            cout << "    • No stack canary: Direct buffer overflow possible" << endl;
        }
        
        if (nx) {
            cout << "    • NX enabled: Cannot execute shellcode on stack" << endl;
            cout << "    • Use ROP/ret2libc instead" << endl;
        } else {
            cout << "    • NX disabled: Shellcode execution possible" << endl;
        }
        
        cout << endl;
    }
    
    ~BinaryProtectionScanner() {
        if (file.is_open()) {
            file.close();
        }
    }
};

void print_usage(const char* progname) {
    cout << "Usage: " << progname << " <binary-file>" << endl;
    cout << "Example: " << progname << " /bin/ls" << endl;
    cout << "\nScans ELF binaries for security protections and suggests exploitation paths." << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    try {
        BinaryProtectionScanner scanner(argv[1]);
        scanner.scan();
        scanner.print_results();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}