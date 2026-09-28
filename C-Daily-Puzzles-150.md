meta

# 150 Daily C Low-Level Puzzles for a Python Dev

> Keep your pointers sharp while coding Python daily. Each puzzle is 20-45 min, no Python stdlib allowed. Focus: raw memory, syscalls, concurrency.

**How to use:** 1 per day. Compile with `gcc -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined`. Run Valgrind weekly. Keep a `puzzles/` folder.

## Table of Contents
- Day 2: Pointer Arithmetic Without [] [Pointers] ★☆☆
- Day 3: argv Unleashed - Double Pointers Deep Dive [Pointers to pointers, Process] ★☆☆
- Day 4: Callback Table & Op Dispatch [Function pointers] ★★☆
- Day 5: Generic Programming with void* [void*, Generic] ★★☆
- Day 6: Dangling Pointers & Use-After-Free [Dangling, Lifetime] ★★☆
- Day 7: Bump Allocator: Your First malloc [malloc/free] ★☆☆
- Day 8: Dynamic Array (Vector) from Scratch [Manual memory, realloc] ★★☆
- Day 9: Leak Hunting with Valgrind/ASAN [Leaks, Tools] ★☆☆
- Day 10: Fixed-Size Memory Pool Allocator [Memory pool] ★★☆
- Day 11: Double-Free & Buffer Overflow Guards [Security, allocator] ★★★
- Day 12: Bit Twiddling: Set/Clear/Toggle [Bitwise ops] ★☆☆
- Day 13: Bitmasks & Permission Flags [Bitmasks] ★☆☆
- Day 14: Swap Without Temp & XOR Pitfalls [Shift tricks, XOR swap] ★☆☆
- Day 15: Counting Bits: Kernighan vs Lookup [Counting bits] ★★☆
- Day 16: Endianness Detection & Conversion [Endianness] ★★☆
- Day 17: Padding & Alignment Surprises [Structs, Padding] ★★☆
- Day 18: Union Type-Punning & Strict Aliasing [Unions, UB] ★★☆
- Day 19: Bit-Fields for Hardware Registers [Bit fields] ★★☆
- Day 20: Tagged Union (Variant Type) [Tagged unions] ★★☆
- Day 21: Reimplement strlen/strcpy [Strings without stdlib] ★☆☆
- Day 22: Reimplement strcmp/strcat/strstr [Strings] ★★☆
- Day 23: In-Place String Reverse & Trim [Strings, In-place] ★★☆
- Day 24: Custom Tokenizer (strtok without stdlib) [Strings, Tokenize] ★★☆
- Day 25: Sprintf-lite: %d %x %s [Strings, Variadic] ★★★
- Day 26: Stack via Raw Array & Overflow Check [Arrays & DS, Stack] ★☆☆
- Day 27: Circular Buffer (Ring Buffer) [Circular buffer, Queue] ★★☆
- Day 28: Linked List: Insert/Delete/Reverse [Linked lists] ★★☆
- Day 29: Floyd's Cycle Detection [Linked list, Cycle] ★★☆
- Day 30: Hash Table From Scratch - Open Addressing [Hash table] ★★★
- Day 31: Binary Search via Pointer Arithmetic [Binary search, Pointers] ★★☆
- Day 32: Quicksort with Generic Comparator [Sorting, void*, Function ptr] ★★★
- Day 33: Two's Complement: Subtract via Add [Number rep, Two's complement] ★☆☆
- Day 34: Signed vs Unsigned Overflow Traps [Overflow, UB] ★★☆
- Day 35: Fixed-Point Arithmetic Q16.16 [Fixed-point] ★★★
- Day 36: Your Own atoi/itoa - Base Agnostic [itoa/atoi] ★★☆
- Day 37: Stack Frames Inspection [Recursion, Call stack] ★★☆
- Day 38: Tail Recursion vs Loop [Tail recursion] ★★☆
- Day 39: Deliberate Stack Overflow & Guard [Stack overflow] ★★☆
- Day 40: Spot-the-Bug: Uninitialized & Off-by-One [Debugging, UB] ★☆☆
- Day 41: What UB Really Means - Optimizer Breaks [UB, Compiler] ★★★
- Day 42: Program Layout: Text/Data/BSS/Heap/Stack [Process & memory model] ★★☆
- Day 43: Stack vs Heap Trade-offs & Escaping [Stack vs heap] ★★☆
- Day 44: Environ & getenv Without libc? [argc/argv, environ] ★★☆
- Day 45: fork() & The Copy-On-Write Illusion [fork()] ★★☆
- Day 46: exec Family & PATH Resolution [exec, Process] ★★☆
- Day 47: Zombies & waitpid() [wait, Zombies] ★★☆
- Day 48: Raw I/O: read/write vs fread/fwrite [Syscalls, File I/O] ★★☆
- Day 49: Binary File Parser & Struct Packing [Binary files, fread] ★★☆
- Day 50: File Descriptors & dup/dup2 Redirection [FD, dup] ★★☆
- Day 51: pipe() & One-Way IPC [pipe(), IPC] ★★☆
- Day 52: mmap() File & Anonymous Memory [mmap] ★★★
- Day 53: Minimal TCP Echo Server (Single Client) [TCP, Sockets] ★★★
- Day 54: Minimal TCP Client & Byte Order [TCP, htons] ★★☆
- Day 55: pthreads: Create/Join & Argument Lifetime [pthread] ★★☆
- Day 56: Race Condition: The Lost Update [Race, Concurrency] ★★☆
- Day 57: Mutex Fix & Deadly Patterns [Mutex] ★★☆
- Day 58: Condition Variables: The Right Way [Condvar] ★★★
- Day 59: Semaphores & Counting [Semaphores] ★★☆
- Day 60: Producer-Consumer with Ring Buffer [Prod-Cons, Concurrency] ★★★
- Day 61: Building & Resolving Deadlock [Deadlock] ★★★
- Day 62: Signal Handler for SIGINT (Graceful Exit) [Signals] ★★☆
- Day 63: SIGSEGV Handler & Backtrace [Signals, SIGSEGV] ★★★
- Day 64: Blocking/Unblocking Signals & sigprocmask [Signals, Mask] ★★☆
- Day 65: Reentrancy & async-signal-safety [Reentrancy, Signals] ★★★
- Day 66: Break The Build: Multi-File Link Error [Compilation & linking] ★☆☆
- Day 67: Static vs Dynamic Library [Static vs Dynamic] ★★☆
- Day 68: Header Guards & Macro Pitfalls [Preprocessor, Macros] ★★☆
- Day 69: Inspecting Binaries: objdump/nm/readelf [Binaries, Tools] ★★☆
- Day 70: Timing: clock() vs gettimeofday vs clock_gettime [Timing] ★★☆
- Day 71: Cache-Friendly Access: Row vs Column Major [Performance, Cache] ★★☆
- Day 72: volatile & Compiler Optimization Trap [volatile, Optimizer] ★★☆
- Day 73: CAPSTONE Day 1/3: Tiny Bytecode VM - Stack Machine Design [Capstone: VM] ★★★
- Day 74: CAPSTONE Day 2/3: Bytecode VM - Assembler & Execution [Capstone: VM] ★★★
- Day 75: CAPSTONE Day 3/3: VM Extensions - Calls & Memory [Capstone: VM] ★★★
- Day 76: Pointer to Pointers to Pointers - 3-Star Programmer [Pointers] ★★☆
- Day 77: Function Pointer State Machine [Function ptr, State machine] ★★★
- Day 78: Generic Vector with void* & Macros [Generic, Macro, malloc] ★★★
- Day 79: Custom realloc That Never Moves? [realloc, Memory] ★★☆
- Day 80: Arena Allocator & Lifetime [Allocator, Arena] ★★☆
- Day 81: Bitmask Allocator for 1024 Slots [Bitwise, Allocator] ★★★
- Day 82: Bit Tricks: Power-of-Two & Isolate LSB [Bitwise tricks] ★☆☆
- Day 83: Endianness-Safe Network Packet Parser [Endianness, Structs] ★★★
- Day 84: Struct Packing for Binary Protocol [Struct layout, Packing] ★★☆
- Day 85: Union for Float Bit Hacking [Union, Float] ★★☆
- Day 86: Tagged Union Expression Evaluator [Tagged union, Recursion] ★★★
- Day 87: strlen Using Word-Sized Reads (Fast) [Strings, Performance] ★★★
- Day 88: In-Place URL Decode [Strings, In-place] ★★☆
- Day 89: Circular Buffer with Overwrite Policy [Circular buffer] ★★☆
- Day 90: Intrusive Linked List (Linux Style) [Linked list, Intrusive] ★★★
- Day 91: Hash Table with Separate Chaining & Resize [Hash table, Resize] ★★★
- Day 92: Binary Search Tree Without Recursion [BST, Stack] ★★★
- Day 93: Fixed-Point PID Controller [Fixed-point, Embedded] ★★★
- Day 94: itoa Base 2-36 with Negative Handling [Number rep, itoa] ★★☆
- Day 95: Recursion to Iteration: Manual Stack [Recursion, Stack] ★★★
- Day 96: UB in Signed Overflow: Compiler Deletes Check? [UB, Overflow] ★★★
- Day 97: Where Are My Vars? Printing Addresses [Memory model, Addresses] ★☆☆
- Day 98: fork() Bomb & Limits [fork, Process] ★★☆
- Day 99: Mini Shell: fork/exec/wait (Part 1) [Capstone: Shell] ★★★
- Day 100: Mini Shell: Pipes & Redirection (Part 2) [Capstone: Shell] ★★★
- Day 101: Raw File Copy with read/write Loop [File I/O, Syscalls] ★☆☆
- Day 102: Atomic File Replace with rename() [File I/O, Atomicity] ★★☆
- Day 103: dup2 for Shell Redirection Simulation [dup2, Shell] ★★☆
- Day 104: pipe() + fork() Chat (Bidirectional) [pipe, fork] ★★★
- Day 105: mmap() Shared Counter Between Processes [mmap, IPC, fork] ★★★
- Day 106: TCP Echo Server with fork() Per Client [TCP, fork, Server] ★★★
- Day 107: Select() Based Multiplexed Echo Server [select, TCP, Multiplex] ★★★
- Day 108: Thread Pool From Scratch [Concurrency, Thread pool] ★★★
- Day 109: Lock-Free? Test-and-Set with __sync [Concurrency, Atomics] ★★★
- Day 110: Readers-Writers Problem [Concurrency, RW Lock] ★★★
- Day 111: Producer-Consumer with Semaphores [Semaphores, Prod-Cons] ★★☆
- Day 112: Deadlock by Lock Ordering [Deadlock, Mutex] ★★☆
- Day 113: Signal vs Thread: Handling SIGINT in MT [Signals, Threads] ★★★
- Day 114: Custom SIGCHLD Handler to Reap Zombies [Signals, SIGCHLD] ★★☆
- Day 115: Static Library: ar & ranlib Mystery [Static libs] ★★☆
- Day 116: Dynamic Library & LD_PRELOAD Hook [Dynamic libs, LD_PRELOAD] ★★★
- Day 117: Macro Black Magic: X-Macros [Macros, Preprocessor] ★★☆
- Day 118: Performance: False Sharing [Performance, Cache, Threads] ★★★
- Day 119: Cache Line & Struct Padding for Speed [Cache, Padding] ★★☆
- Day 120: CAPSTONE Day 1/4: Custom malloc (Free List) [Capstone: malloc] ★★★
- Day 121: CAPSTONE Day 2/4: malloc - Coalescing & Splitting [Capstone: malloc] ★★★
- Day 122: CAPSTONE Day 3/4: malloc - Realloc & Edge Cases [Capstone: malloc] ★★★
- Day 123: CAPSTONE Day 4/4: malloc - Thread-Safety & Test [Capstone: malloc] ★★★
- Day 124: String Intern Pool [Strings, Hash table, Pool] ★★★
- Day 125: Zero-Copy Slice Type (ptr+len) [Pointers, Slices] ★★☆
- Day 126: Manual VTable: OOP in C [Function ptr, OOP, Structs] ★★★
- Day 127: Bitfield vs Manual Masking [Bit fields, Bitwise] ★★☆
- Day 128: Endian-Aware Serializer [Endianness, Serialization] ★★★
- Day 129: Double Linked List with Sentinel [Linked list, Sentinel] ★★☆
- Day 130: LRU Cache with Hash + List [Hash, List, LRU] ★★★
- Day 131: Radix Sort with Bitwise Partition [Sorting, Bitwise] ★★☆
- Day 132: Varint Encoding (Protobuf Style) [Number rep, Encoding] ★★☆
- Day 133: Deep Recursion & Stack Size (getrlimit) [Recursion, Stack] ★★☆
- Day 134: Heap Spray Detection Simulation [Memory, Security] ★★☆
- Day 135: File Locking: flock vs fcntl [File I/O, Locking] ★★☆
- Day 136: mmap() as Allocator Backend [mmap, Allocator] ★★☆
- Day 137: TCP Half-Close & Shutdown [TCP, Sockets] ★★☆
- Day 138: pthread Cleanup Handlers [Threads, Cleanup] ★★☆
- Day 139: Condition Variable Spurious Wakeup Demo [Condvar, Threads] ★★☆
- Day 140: Barrier Implementation [Concurrency, Barrier] ★★☆
- Day 141: Signal Safe Logger [Signals, async-safe] ★★★
- Day 142: Mini Make: Dependency Graph [Compilation, Graph] ★★★
- Day 143: Inspect ELF: .text .rodata .bss [ELF, Binaries] ★★☆
- Day 144: Timing Attack Resistant memcmp [Timing, Security, volatile] ★★★
- Day 145: CAPSTONE Day 1/2: Multi-Threaded TCP Echo Server [Capstone: TCP MT] ★★★
- Day 146: CAPSTONE Day 2/2: MT Echo Server - Graceful Shutdown & Stats [Capstone: TCP MT] ★★★
- Day 147: Write Your Own assert() & Diagnostics [Macros, Debugging] ★☆☆
- Day 148: Const Correctness & Pointer to Const Hell [const, Pointers] ★★☆
- Day 149: Flexible Array Members & Struct Hack [Structs, Flexible array] ★★☆
- Day 150: The Ultimate: Python's list in C - PyObject-ish System [Grand Finale, All topics] ★★★

---

## Day 2: Pointer Arithmetic Without []
**Topics:** Pointers  
**Difficulty:** ★☆☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's `for x in arr` hides pointer math. In C, `a[i]` is syntactic sugar for `*(a+i)`. Interviewers love banning [].

**Problem:**  
1. Implement `int sum_range(int *start, int *end)` where `end` is one-past-last (like C++ iterators), using ONLY pointer arithmetic. No []
2. Implement `void reverse_ints(int *start, int *end)` in place using two pointers moving toward center.
3. Print addresses at each step to visualize stride = sizeof(int).

**Starter Code:**  
#include <stdio.h>
int sum_range(int *start, int *end) { /* TODO */ return 0; }
void reverse_ints(int *start, int *end) { /* TODO */ }
int main() {
    int a[] = {1,2,3,4,5};
    printf("%d\n", sum_range(a, a+5));
    reverse_ints(a, a+5);
    for(int *p=a; p<a+5; p++) printf("%d ", *p);
}


**Constraints & Follow-Up Questions to Think About:**  
- Why is `ptr+1` not `+1 byte` but `+sizeof(*ptr)`?
- What is the type of `a` vs `&a` vs `&a[0]`?
- What happens if you compare pointers from different arrays?

---

## Day 3: argv Unleashed - Double Pointers Deep Dive
**Topics:** Pointers to pointers, Process  
**Difficulty:** ★☆☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's sys.argv is a list of strings. In C it's a `char **` - pointer to array of pointers. You need to walk it manually.

**Problem:**  
Implement `char *get_arg_value(char **argv, char *flag)` that finds flag like `--out` and returns next arg, or NULL. Then implement `int count_args(char **argv)` without using any string.h. Handle `--` terminator.

**Starter Code:**  
#include <stdio.h>
int my_strlen(char *s){/*TODO*/ return 0;}
int my_strcmp(char *a, char *b){/*TODO*/ return 0;}
char *get_arg_value(char **argv, char *flag){/*TODO*/ return 0;}
int main(int argc, char **argv){
    char *out = get_arg_value(argv, "--out");
    if(out) printf("out=%s\n", out);
}


**Constraints & Follow-Up Questions to Think About:**  
- Draw memory layout: argv array, each char* pointing to char array.
- Why argv is NULL-terminated? How to detect end?
- Difference between `char **argv` and `char *argv[]` in parameter?

---

## Day 4: Callback Table & Op Dispatch
**Topics:** Function pointers  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
In Python you pass functions as first-class objects. In C you use function pointers for dispatch tables, state machines, drivers.

**Problem:**  
Define `typedef int (*binary_op)(int,int);` Implement add/sub/mul/div. Create `struct {char sym; binary_op fn;} table[]`. Write `binary_op lookup(char)` and evaluate expression like `3 + 4 * 2` left-to-right using dispatch. Handle div-by-zero via returning error code via out param.

**Starter Code:**  
#include <stdio.h>
typedef int (*binary_op)(int,int);
int add(int a,int b){return a+b;}
// TODO: sub,mul,div
struct Op { char sym; binary_op fn; };
binary_op lookup(char c){ /* TODO */ return 0; }
int main(){ /* TODO parse */ }


**Constraints & Follow-Up Questions to Think About:**  
- Syntax: how to declare array of function pointers? Why parentheses matter?
- How to store function pointers in struct?
- Performance vs switch-case?

---

## Day 5: Generic Programming with void*
**Topics:** void*, Generic  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's list.sort() works for any type. C's qsort does it with void* + size + comparator. Understand generic memory.

**Problem:**  
Implement `void generic_swap(void *a, void *b, size_t size)` using stack buffer (max 256) + byte loop if bigger. Then implement `void generic_bubble(void *base, size_t n, size_t sz, int (*cmp)(const void*,const void*))`. Test with int and struct {char name[16]; int age;}

**Starter Code:**  
#include <stdio.h>
#include <stddef.h>
void generic_swap(void *a, void *b, size_t sz){ /* TODO */ }
int int_cmp(const void *a,const void *b){ return *(int*)a - *(int*)b; }
void generic_bubble(void *base, size_t n, size_t sz, int (*cmp)(const void*,const void*)){ /* TODO */ }
int main(){ int arr[]={5,2,9,1}; generic_bubble(arr,4,sizeof(int),int_cmp); }


**Constraints & Follow-Up Questions to Think About:**  
- Why can't you dereference void*? Why cast to char*?
- What about alignment when swapping via char*?
- How does qsort know element size?

---

## Day 6: Dangling Pointers & Use-After-Free
**Topics:** Dangling, Lifetime  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python never gives you dangling refs. In C, returning &local is classic bug. Understand stack lifetime.

**Problem:**  
1. Write buggy `int *make_dangling()` returning pointer to local. Call it, print *ptr before and after calling another function to clobber stack.
2. Write 3 correct versions: static, malloc, out-param.
3. Create use-after-free: free then write. Detect with ASAN.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
int *make_dangling(){ int x=42; return &x; }
int main(){
    int *p = make_dangling();
    printf("%d\n", *p); // UB
}


**Constraints & Follow-Up Questions to Think About:**  
- Why does it sometimes 'work'?
- Stack vs heap lifetime.
- What does -fstack-protector do?

---

## Day 7: Bump Allocator: Your First malloc
**Topics:** malloc/free  
**Difficulty:** ★☆☆  
**Estimated Time:** 20-45 min

**Context:**  
Low-level memory management puzzle - Bump Allocator: Your First malloc. Python hides this with GC and reference counting.

**Problem:**  
Task related to Bump Allocator: Your First malloc: Implement core logic, handle edge cases (NULL, size 0, OOM), test with valgrind. Write small test harness printing PASS/FAIL.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// TODO: Implement Bump Allocator: Your First malloc
int main(){ /* test */ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- When to use calloc vs malloc+memset?
- What does free(NULL) do?
- How to handle realloc failure without leaking?

---

## Day 8: Dynamic Array (Vector) from Scratch
**Topics:** Manual memory, realloc  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Low-level memory management puzzle - Dynamic Array (Vector) from Scratch. Python hides this with GC and reference counting.

**Problem:**  
Task related to Dynamic Array (Vector) from Scratch: Implement core logic, handle edge cases (NULL, size 0, OOM), test with valgrind. Write small test harness printing PASS/FAIL.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// TODO: Implement Dynamic Array (Vector) from Scratch
int main(){ /* test */ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- When to use calloc vs malloc+memset?
- What does free(NULL) do?
- How to handle realloc failure without leaking?

---

## Day 9: Leak Hunting with Valgrind/ASAN
**Topics:** Leaks, Tools  
**Difficulty:** ★☆☆  
**Estimated Time:** 20-45 min

**Context:**  
Low-level memory management puzzle - Leak Hunting with Valgrind/ASAN. Python hides this with GC and reference counting.

**Problem:**  
Task related to Leak Hunting with Valgrind/ASAN: Implement core logic, handle edge cases (NULL, size 0, OOM), test with valgrind. Write small test harness printing PASS/FAIL.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// TODO: Implement Leak Hunting with Valgrind/ASAN
int main(){ /* test */ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- When to use calloc vs malloc+memset?
- What does free(NULL) do?
- How to handle realloc failure without leaking?

---

## Day 10: Fixed-Size Memory Pool Allocator
**Topics:** Memory pool  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Low-level memory management puzzle - Fixed-Size Memory Pool Allocator. Python hides this with GC and reference counting.

**Problem:**  
Task related to Fixed-Size Memory Pool Allocator: Implement core logic, handle edge cases (NULL, size 0, OOM), test with valgrind. Write small test harness printing PASS/FAIL.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// TODO: Implement Fixed-Size Memory Pool Allocator
int main(){ /* test */ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- When to use calloc vs malloc+memset?
- What does free(NULL) do?
- How to handle realloc failure without leaking?

---

## Day 11: Double-Free & Buffer Overflow Guards
**Topics:** Security, allocator  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Low-level memory management puzzle - Double-Free & Buffer Overflow Guards. Python hides this with GC and reference counting.

**Problem:**  
Task related to Double-Free & Buffer Overflow Guards: Implement core logic, handle edge cases (NULL, size 0, OOM), test with valgrind. Write small test harness printing PASS/FAIL.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// TODO: Implement Double-Free & Buffer Overflow Guards
int main(){ /* test */ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- When to use calloc vs malloc+memset?
- What does free(NULL) do?
- How to handle realloc failure without leaking?

---

## Day 12: Bit Twiddling: Set/Clear/Toggle
**Topics:** Bitwise ops  
**Difficulty:** ★☆☆  
**Estimated Time:** 20-45 min

**Context:**  
Python ints are arbitrary precision. In C you control bits directly - essential for flags, protocols, embedded.

**Problem:**  
For Bit Twiddling: Set/Clear/Toggle: Implement bit manipulation functions without branching where possible. Test all 32 bits. Example: `int get_bit(uint32_t x, int n)`, `uint32_t set_bit`, `clear`, `toggle`. Then extend to requested puzzle.

**Starter Code:**  
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
int get_bit(uint32_t x,int n){ return (x>>n)&1; }
uint32_t set_bit(uint32_t x,int n){ /*TODO*/ return x; }
int count_bits(uint32_t x){ /* TODO Kernighan */ return 0; }
int main(){ assert(get_bit(0b1010,1)==1); }


**Constraints & Follow-Up Questions to Think About:**  
- Difference between >> on signed vs unsigned?
- Why XOR swap fails when &a == &b?
- Endianness vs bit order?

---

## Day 13: Bitmasks & Permission Flags
**Topics:** Bitmasks  
**Difficulty:** ★☆☆  
**Estimated Time:** 20-45 min

**Context:**  
Python ints are arbitrary precision. In C you control bits directly - essential for flags, protocols, embedded.

**Problem:**  
For Bitmasks & Permission Flags: Implement bit manipulation functions without branching where possible. Test all 32 bits. Example: `int get_bit(uint32_t x, int n)`, `uint32_t set_bit`, `clear`, `toggle`. Then extend to requested puzzle.

**Starter Code:**  
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
int get_bit(uint32_t x,int n){ return (x>>n)&1; }
uint32_t set_bit(uint32_t x,int n){ /*TODO*/ return x; }
int count_bits(uint32_t x){ /* TODO Kernighan */ return 0; }
int main(){ assert(get_bit(0b1010,1)==1); }


**Constraints & Follow-Up Questions to Think About:**  
- Difference between >> on signed vs unsigned?
- Why XOR swap fails when &a == &b?
- Endianness vs bit order?

---

## Day 14: Swap Without Temp & XOR Pitfalls
**Topics:** Shift tricks, XOR swap  
**Difficulty:** ★☆☆  
**Estimated Time:** 20-45 min

**Context:**  
Python ints are arbitrary precision. In C you control bits directly - essential for flags, protocols, embedded.

**Problem:**  
For Swap Without Temp & XOR Pitfalls: Implement bit manipulation functions without branching where possible. Test all 32 bits. Example: `int get_bit(uint32_t x, int n)`, `uint32_t set_bit`, `clear`, `toggle`. Then extend to requested puzzle.

**Starter Code:**  
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
int get_bit(uint32_t x,int n){ return (x>>n)&1; }
uint32_t set_bit(uint32_t x,int n){ /*TODO*/ return x; }
int count_bits(uint32_t x){ /* TODO Kernighan */ return 0; }
int main(){ assert(get_bit(0b1010,1)==1); }


**Constraints & Follow-Up Questions to Think About:**  
- Difference between >> on signed vs unsigned?
- Why XOR swap fails when &a == &b?
- Endianness vs bit order?

---

## Day 15: Counting Bits: Kernighan vs Lookup
**Topics:** Counting bits  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python ints are arbitrary precision. In C you control bits directly - essential for flags, protocols, embedded.

**Problem:**  
For Counting Bits: Kernighan vs Lookup: Implement bit manipulation functions without branching where possible. Test all 32 bits. Example: `int get_bit(uint32_t x, int n)`, `uint32_t set_bit`, `clear`, `toggle`. Then extend to requested puzzle.

**Starter Code:**  
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
int get_bit(uint32_t x,int n){ return (x>>n)&1; }
uint32_t set_bit(uint32_t x,int n){ /*TODO*/ return x; }
int count_bits(uint32_t x){ /* TODO Kernighan */ return 0; }
int main(){ assert(get_bit(0b1010,1)==1); }


**Constraints & Follow-Up Questions to Think About:**  
- Difference between >> on signed vs unsigned?
- Why XOR swap fails when &a == &b?
- Endianness vs bit order?

---

## Day 16: Endianness Detection & Conversion
**Topics:** Endianness  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python ints are arbitrary precision. In C you control bits directly - essential for flags, protocols, embedded.

**Problem:**  
For Endianness Detection & Conversion: Implement bit manipulation functions without branching where possible. Test all 32 bits. Example: `int get_bit(uint32_t x, int n)`, `uint32_t set_bit`, `clear`, `toggle`. Then extend to requested puzzle.

**Starter Code:**  
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
int get_bit(uint32_t x,int n){ return (x>>n)&1; }
uint32_t set_bit(uint32_t x,int n){ /*TODO*/ return x; }
int count_bits(uint32_t x){ /* TODO Kernighan */ return 0; }
int main(){ assert(get_bit(0b1010,1)==1); }


**Constraints & Follow-Up Questions to Think About:**  
- Difference between >> on signed vs unsigned?
- Why XOR swap fails when &a == &b?
- Endianness vs bit order?

---

## Day 17: Padding & Alignment Surprises
**Topics:** Structs, Padding  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python classes abstract memory layout. In C, struct layout = padding + alignment + ABI. Unions allow type-punning (careful with strict aliasing).

**Problem:**  
Explore Padding & Alignment Surprises: Create structs and print `sizeof` and `offsetof` each field. Reorder to minimize padding. For unions, write type-punning to inspect float bits. For tagged union, implement `enum Type {INT,FLOAT,STR}; struct Value {Type t; union {int i; float f; char *s;};};` with print function.

**Starter Code:**  
#include <stdio.h>
#include <stddef.h>
struct A { char c; int i; char d; };
struct B { int i; char c; char d; };
union FloatPun { float f; uint32_t u; };
int main(){
    printf("sizeof A=%zu B=%zu\n", sizeof(struct A), sizeof(struct B));
    printf("offset c=%zu i=%zu\n", offsetof(struct A,c), offsetof(struct A,i));
}


**Constraints & Follow-Up Questions to Think About:**  
- Why does compiler pad? Alignment requirements.
- What is strict aliasing rule? When is union punning allowed in C vs C++?
- How does #pragma pack affect portability?

---

## Day 18: Union Type-Punning & Strict Aliasing
**Topics:** Unions, UB  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python classes abstract memory layout. In C, struct layout = padding + alignment + ABI. Unions allow type-punning (careful with strict aliasing).

**Problem:**  
Explore Union Type-Punning & Strict Aliasing: Create structs and print `sizeof` and `offsetof` each field. Reorder to minimize padding. For unions, write type-punning to inspect float bits. For tagged union, implement `enum Type {INT,FLOAT,STR}; struct Value {Type t; union {int i; float f; char *s;};};` with print function.

**Starter Code:**  
#include <stdio.h>
#include <stddef.h>
struct A { char c; int i; char d; };
struct B { int i; char c; char d; };
union FloatPun { float f; uint32_t u; };
int main(){
    printf("sizeof A=%zu B=%zu\n", sizeof(struct A), sizeof(struct B));
    printf("offset c=%zu i=%zu\n", offsetof(struct A,c), offsetof(struct A,i));
}


**Constraints & Follow-Up Questions to Think About:**  
- Why does compiler pad? Alignment requirements.
- What is strict aliasing rule? When is union punning allowed in C vs C++?
- How does #pragma pack affect portability?

---

## Day 19: Bit-Fields for Hardware Registers
**Topics:** Bit fields  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python classes abstract memory layout. In C, struct layout = padding + alignment + ABI. Unions allow type-punning (careful with strict aliasing).

**Problem:**  
Explore Bit-Fields for Hardware Registers: Create structs and print `sizeof` and `offsetof` each field. Reorder to minimize padding. For unions, write type-punning to inspect float bits. For tagged union, implement `enum Type {INT,FLOAT,STR}; struct Value {Type t; union {int i; float f; char *s;};};` with print function.

**Starter Code:**  
#include <stdio.h>
#include <stddef.h>
struct A { char c; int i; char d; };
struct B { int i; char c; char d; };
union FloatPun { float f; uint32_t u; };
int main(){
    printf("sizeof A=%zu B=%zu\n", sizeof(struct A), sizeof(struct B));
    printf("offset c=%zu i=%zu\n", offsetof(struct A,c), offsetof(struct A,i));
}


**Constraints & Follow-Up Questions to Think About:**  
- Why does compiler pad? Alignment requirements.
- What is strict aliasing rule? When is union punning allowed in C vs C++?
- How does #pragma pack affect portability?

---

## Day 20: Tagged Union (Variant Type)
**Topics:** Tagged unions  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python classes abstract memory layout. In C, struct layout = padding + alignment + ABI. Unions allow type-punning (careful with strict aliasing).

**Problem:**  
Explore Tagged Union (Variant Type): Create structs and print `sizeof` and `offsetof` each field. Reorder to minimize padding. For unions, write type-punning to inspect float bits. For tagged union, implement `enum Type {INT,FLOAT,STR}; struct Value {Type t; union {int i; float f; char *s;};};` with print function.

**Starter Code:**  
#include <stdio.h>
#include <stddef.h>
struct A { char c; int i; char d; };
struct B { int i; char c; char d; };
union FloatPun { float f; uint32_t u; };
int main(){
    printf("sizeof A=%zu B=%zu\n", sizeof(struct A), sizeof(struct B));
    printf("offset c=%zu i=%zu\n", offsetof(struct A,c), offsetof(struct A,i));
}


**Constraints & Follow-Up Questions to Think About:**  
- Why does compiler pad? Alignment requirements.
- What is strict aliasing rule? When is union punning allowed in C vs C++?
- How does #pragma pack affect portability?

---

## Day 21: Reimplement strlen/strcpy
**Topics:** Strings without stdlib  
**Difficulty:** ★☆☆  
**Estimated Time:** 20-45 min

**Context:**  
Python strings are immutable objects. In C they're just `char*` terminated by \0. You must implement everything yourself.

**Problem:**  
Task Reimplement strlen/strcpy: Reimplement without using <string.h>. Handle NULL, empty, overlapping. For sprintf-lite, support %%d %%x %%s %%c %%p with variadic args (stdarg.h allowed). Test with your own assert.

**Starter Code:**  
#include <stdio.h>
size_t my_strlen(const char *s){ size_t n=0; while(s && *s++){n++;} return n; }
// TODO: strcpy, strcmp, strcat, strstr, reverse, trim, strtok, sprintf_lite
int main(){ char buf[64]="  hello world  "; /* test */ }


**Constraints & Follow-Up Questions to Think About:**  
- Why is strncpy dangerous? What does it not do?
- In-place reverse: why need to handle odd length?
- Security implications of strcpy?

---

## Day 22: Reimplement strcmp/strcat/strstr
**Topics:** Strings  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python strings are immutable objects. In C they're just `char*` terminated by \0. You must implement everything yourself.

**Problem:**  
Task Reimplement strcmp/strcat/strstr: Reimplement without using <string.h>. Handle NULL, empty, overlapping. For sprintf-lite, support %%d %%x %%s %%c %%p with variadic args (stdarg.h allowed). Test with your own assert.

**Starter Code:**  
#include <stdio.h>
size_t my_strlen(const char *s){ size_t n=0; while(s && *s++){n++;} return n; }
// TODO: strcpy, strcmp, strcat, strstr, reverse, trim, strtok, sprintf_lite
int main(){ char buf[64]="  hello world  "; /* test */ }


**Constraints & Follow-Up Questions to Think About:**  
- Why is strncpy dangerous? What does it not do?
- In-place reverse: why need to handle odd length?
- Security implications of strcpy?

---

## Day 23: In-Place String Reverse & Trim
**Topics:** Strings, In-place  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python strings are immutable objects. In C they're just `char*` terminated by \0. You must implement everything yourself.

**Problem:**  
Task In-Place String Reverse & Trim: Reimplement without using <string.h>. Handle NULL, empty, overlapping. For sprintf-lite, support %%d %%x %%s %%c %%p with variadic args (stdarg.h allowed). Test with your own assert.

**Starter Code:**  
#include <stdio.h>
size_t my_strlen(const char *s){ size_t n=0; while(s && *s++){n++;} return n; }
// TODO: strcpy, strcmp, strcat, strstr, reverse, trim, strtok, sprintf_lite
int main(){ char buf[64]="  hello world  "; /* test */ }


**Constraints & Follow-Up Questions to Think About:**  
- Why is strncpy dangerous? What does it not do?
- In-place reverse: why need to handle odd length?
- Security implications of strcpy?

---

## Day 24: Custom Tokenizer (strtok without stdlib)
**Topics:** Strings, Tokenize  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python strings are immutable objects. In C they're just `char*` terminated by \0. You must implement everything yourself.

**Problem:**  
Task Custom Tokenizer (strtok without stdlib): Reimplement without using <string.h>. Handle NULL, empty, overlapping. For sprintf-lite, support %%d %%x %%s %%c %%p with variadic args (stdarg.h allowed). Test with your own assert.

**Starter Code:**  
#include <stdio.h>
size_t my_strlen(const char *s){ size_t n=0; while(s && *s++){n++;} return n; }
// TODO: strcpy, strcmp, strcat, strstr, reverse, trim, strtok, sprintf_lite
int main(){ char buf[64]="  hello world  "; /* test */ }


**Constraints & Follow-Up Questions to Think About:**  
- Why is strncpy dangerous? What does it not do?
- In-place reverse: why need to handle odd length?
- Security implications of strcpy?

---

## Day 25: Sprintf-lite: %d %x %s
**Topics:** Strings, Variadic  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Python strings are immutable objects. In C they're just `char*` terminated by \0. You must implement everything yourself.

**Problem:**  
Task Sprintf-lite: %d %x %s: Reimplement without using <string.h>. Handle NULL, empty, overlapping. For sprintf-lite, support %%d %%x %%s %%c %%p with variadic args (stdarg.h allowed). Test with your own assert.

**Starter Code:**  
#include <stdio.h>
size_t my_strlen(const char *s){ size_t n=0; while(s && *s++){n++;} return n; }
// TODO: strcpy, strcmp, strcat, strstr, reverse, trim, strtok, sprintf_lite
int main(){ char buf[64]="  hello world  "; /* test */ }


**Constraints & Follow-Up Questions to Think About:**  
- Why is strncpy dangerous? What does it not do?
- In-place reverse: why need to handle odd length?
- Security implications of strcpy?

---

## Day 26: Stack via Raw Array & Overflow Check
**Topics:** Arrays & DS, Stack  
**Difficulty:** ★☆☆  
**Estimated Time:** 20-45 min

**Context:**  
Python list/dict are highly optimized C structures. Build yours to understand tradeoffs.

**Problem:**  
Stack via Raw Array & Overflow Check: Build from scratch with raw arrays/malloc. For stack/queue, implement grow policy. For circular buffer, handle full vs empty. For linked list, implement without leaks. For hash table, handle collisions. No [] where noted.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// TODO: DS implementation
typedef struct Node { int val; struct Node *next; } Node;
Node* reverse(Node *head){ /* TODO */ return head; }
int has_cycle(Node *head){ /* TODO Floyd */ return 0; }
int main(){}


**Constraints & Follow-Up Questions to Think About:**  
- Array vs linked list cache locality?
- Why circular buffer uses (head+1)%cap?
- How to choose hash table load factor?

---

## Day 27: Circular Buffer (Ring Buffer)
**Topics:** Circular buffer, Queue  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python list/dict are highly optimized C structures. Build yours to understand tradeoffs.

**Problem:**  
Circular Buffer (Ring Buffer): Build from scratch with raw arrays/malloc. For stack/queue, implement grow policy. For circular buffer, handle full vs empty. For linked list, implement without leaks. For hash table, handle collisions. No [] where noted.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// TODO: DS implementation
typedef struct Node { int val; struct Node *next; } Node;
Node* reverse(Node *head){ /* TODO */ return head; }
int has_cycle(Node *head){ /* TODO Floyd */ return 0; }
int main(){}


**Constraints & Follow-Up Questions to Think About:**  
- Array vs linked list cache locality?
- Why circular buffer uses (head+1)%cap?
- How to choose hash table load factor?

---

## Day 28: Linked List: Insert/Delete/Reverse
**Topics:** Linked lists  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python list/dict are highly optimized C structures. Build yours to understand tradeoffs.

**Problem:**  
Linked List: Insert/Delete/Reverse: Build from scratch with raw arrays/malloc. For stack/queue, implement grow policy. For circular buffer, handle full vs empty. For linked list, implement without leaks. For hash table, handle collisions. No [] where noted.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// TODO: DS implementation
typedef struct Node { int val; struct Node *next; } Node;
Node* reverse(Node *head){ /* TODO */ return head; }
int has_cycle(Node *head){ /* TODO Floyd */ return 0; }
int main(){}


**Constraints & Follow-Up Questions to Think About:**  
- Array vs linked list cache locality?
- Why circular buffer uses (head+1)%cap?
- How to choose hash table load factor?

---

## Day 29: Floyd's Cycle Detection
**Topics:** Linked list, Cycle  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python list/dict are highly optimized C structures. Build yours to understand tradeoffs.

**Problem:**  
Floyd's Cycle Detection: Build from scratch with raw arrays/malloc. For stack/queue, implement grow policy. For circular buffer, handle full vs empty. For linked list, implement without leaks. For hash table, handle collisions. No [] where noted.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// TODO: DS implementation
typedef struct Node { int val; struct Node *next; } Node;
Node* reverse(Node *head){ /* TODO */ return head; }
int has_cycle(Node *head){ /* TODO Floyd */ return 0; }
int main(){}


**Constraints & Follow-Up Questions to Think About:**  
- Array vs linked list cache locality?
- Why circular buffer uses (head+1)%cap?
- How to choose hash table load factor?

---

## Day 30: Hash Table From Scratch - Open Addressing
**Topics:** Hash table  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Python list/dict are highly optimized C structures. Build yours to understand tradeoffs.

**Problem:**  
Hash Table From Scratch - Open Addressing: Build from scratch with raw arrays/malloc. For stack/queue, implement grow policy. For circular buffer, handle full vs empty. For linked list, implement without leaks. For hash table, handle collisions. No [] where noted.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// TODO: DS implementation
typedef struct Node { int val; struct Node *next; } Node;
Node* reverse(Node *head){ /* TODO */ return head; }
int has_cycle(Node *head){ /* TODO Floyd */ return 0; }
int main(){}


**Constraints & Follow-Up Questions to Think About:**  
- Array vs linked list cache locality?
- Why circular buffer uses (head+1)%cap?
- How to choose hash table load factor?

---

## Day 31: Binary Search via Pointer Arithmetic
**Topics:** Binary search, Pointers  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python list/dict are highly optimized C structures. Build yours to understand tradeoffs.

**Problem:**  
Binary Search via Pointer Arithmetic: Build from scratch with raw arrays/malloc. For stack/queue, implement grow policy. For circular buffer, handle full vs empty. For linked list, implement without leaks. For hash table, handle collisions. No [] where noted.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// TODO: DS implementation
typedef struct Node { int val; struct Node *next; } Node;
Node* reverse(Node *head){ /* TODO */ return head; }
int has_cycle(Node *head){ /* TODO Floyd */ return 0; }
int main(){}


**Constraints & Follow-Up Questions to Think About:**  
- Array vs linked list cache locality?
- Why circular buffer uses (head+1)%cap?
- How to choose hash table load factor?

---

## Day 32: Quicksort with Generic Comparator
**Topics:** Sorting, void*, Function ptr  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Python list/dict are highly optimized C structures. Build yours to understand tradeoffs.

**Problem:**  
Quicksort with Generic Comparator: Build from scratch with raw arrays/malloc. For stack/queue, implement grow policy. For circular buffer, handle full vs empty. For linked list, implement without leaks. For hash table, handle collisions. No [] where noted.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// TODO: DS implementation
typedef struct Node { int val; struct Node *next; } Node;
Node* reverse(Node *head){ /* TODO */ return head; }
int has_cycle(Node *head){ /* TODO Floyd */ return 0; }
int main(){}


**Constraints & Follow-Up Questions to Think About:**  
- Array vs linked list cache locality?
- Why circular buffer uses (head+1)%cap?
- How to choose hash table load factor?

---

## Day 33: Two's Complement: Subtract via Add
**Topics:** Number rep, Two's complement  
**Difficulty:** ★☆☆  
**Estimated Time:** 20-45 min

**Context:**  
Python hides two's complement, overflow, fixed-point. In embedded C you live there.

**Problem:**  
Two's Complement: Subtract via Add: Implement conversion without library. For two's complement, show subtraction via ~ +1. For overflow, detect signed overflow before it happens. For fixed-point Q16.16, implement mul/div with 64-bit intermediate. For atoi/itoa, handle bases 2-36, INT_MIN edge.

**Starter Code:**  
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
int add_overflow(int a,int b,int *res){ /* TODO detect */ return 0; }
int32_t fixed_mul(int32_t a,int32_t b){ /* Q16.16 */ return 0; }
int my_atoi(const char *s){ /* TODO */ return 0; }
int main(){}


**Constraints & Follow-Up Questions to Think About:**  
- Why is signed overflow UB but unsigned defined wrap?
- Two's complement of INT_MIN?
- Fixed-point vs float precision?

---

## Day 34: Signed vs Unsigned Overflow Traps
**Topics:** Overflow, UB  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python hides two's complement, overflow, fixed-point. In embedded C you live there.

**Problem:**  
Signed vs Unsigned Overflow Traps: Implement conversion without library. For two's complement, show subtraction via ~ +1. For overflow, detect signed overflow before it happens. For fixed-point Q16.16, implement mul/div with 64-bit intermediate. For atoi/itoa, handle bases 2-36, INT_MIN edge.

**Starter Code:**  
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
int add_overflow(int a,int b,int *res){ /* TODO detect */ return 0; }
int32_t fixed_mul(int32_t a,int32_t b){ /* Q16.16 */ return 0; }
int my_atoi(const char *s){ /* TODO */ return 0; }
int main(){}


**Constraints & Follow-Up Questions to Think About:**  
- Why is signed overflow UB but unsigned defined wrap?
- Two's complement of INT_MIN?
- Fixed-point vs float precision?

---

## Day 35: Fixed-Point Arithmetic Q16.16
**Topics:** Fixed-point  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Python hides two's complement, overflow, fixed-point. In embedded C you live there.

**Problem:**  
Fixed-Point Arithmetic Q16.16: Implement conversion without library. For two's complement, show subtraction via ~ +1. For overflow, detect signed overflow before it happens. For fixed-point Q16.16, implement mul/div with 64-bit intermediate. For atoi/itoa, handle bases 2-36, INT_MIN edge.

**Starter Code:**  
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
int add_overflow(int a,int b,int *res){ /* TODO detect */ return 0; }
int32_t fixed_mul(int32_t a,int32_t b){ /* Q16.16 */ return 0; }
int my_atoi(const char *s){ /* TODO */ return 0; }
int main(){}


**Constraints & Follow-Up Questions to Think About:**  
- Why is signed overflow UB but unsigned defined wrap?
- Two's complement of INT_MIN?
- Fixed-point vs float precision?

---

## Day 36: Your Own atoi/itoa - Base Agnostic
**Topics:** itoa/atoi  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python hides two's complement, overflow, fixed-point. In embedded C you live there.

**Problem:**  
Your Own atoi/itoa - Base Agnostic: Implement conversion without library. For two's complement, show subtraction via ~ +1. For overflow, detect signed overflow before it happens. For fixed-point Q16.16, implement mul/div with 64-bit intermediate. For atoi/itoa, handle bases 2-36, INT_MIN edge.

**Starter Code:**  
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
int add_overflow(int a,int b,int *res){ /* TODO detect */ return 0; }
int32_t fixed_mul(int32_t a,int32_t b){ /* Q16.16 */ return 0; }
int my_atoi(const char *s){ /* TODO */ return 0; }
int main(){}


**Constraints & Follow-Up Questions to Think About:**  
- Why is signed overflow UB but unsigned defined wrap?
- Two's complement of INT_MIN?
- Fixed-point vs float precision?

---

## Day 37: Stack Frames Inspection
**Topics:** Recursion, Call stack  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python recursion limit ~1000. C recursion limited by stack size (8MB). Understand frames.

**Problem:**  
Stack Frames Inspection: For stack frames, write recursive function printing &local to show stack growth direction. For tail recursion, compare factorial tail vs non-tail with -O2 assembly. For overflow, deliberately overflow with infinite recursion and catch with sigaltstack or getrlimit.

**Starter Code:**  
#include <stdio.h>
void show_frames(int depth){
    int local;
    printf("depth %d: local at %p\n", depth, (void*)&local);
    if(depth>0) show_frames(depth-1);
}
int main(){ show_frames(5); }


**Constraints & Follow-Up Questions to Think About:**  
- Stack grows up or down on x86_64?
- Why tail recursion optimization saves stack?
- How to increase stack with ulimit?

---

## Day 38: Tail Recursion vs Loop
**Topics:** Tail recursion  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python recursion limit ~1000. C recursion limited by stack size (8MB). Understand frames.

**Problem:**  
Tail Recursion vs Loop: For stack frames, write recursive function printing &local to show stack growth direction. For tail recursion, compare factorial tail vs non-tail with -O2 assembly. For overflow, deliberately overflow with infinite recursion and catch with sigaltstack or getrlimit.

**Starter Code:**  
#include <stdio.h>
void show_frames(int depth){
    int local;
    printf("depth %d: local at %p\n", depth, (void*)&local);
    if(depth>0) show_frames(depth-1);
}
int main(){ show_frames(5); }


**Constraints & Follow-Up Questions to Think About:**  
- Stack grows up or down on x86_64?
- Why tail recursion optimization saves stack?
- How to increase stack with ulimit?

---

## Day 39: Deliberate Stack Overflow & Guard
**Topics:** Stack overflow  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python recursion limit ~1000. C recursion limited by stack size (8MB). Understand frames.

**Problem:**  
Deliberate Stack Overflow & Guard: For stack frames, write recursive function printing &local to show stack growth direction. For tail recursion, compare factorial tail vs non-tail with -O2 assembly. For overflow, deliberately overflow with infinite recursion and catch with sigaltstack or getrlimit.

**Starter Code:**  
#include <stdio.h>
void show_frames(int depth){
    int local;
    printf("depth %d: local at %p\n", depth, (void*)&local);
    if(depth>0) show_frames(depth-1);
}
int main(){ show_frames(5); }


**Constraints & Follow-Up Questions to Think About:**  
- Stack grows up or down on x86_64?
- Why tail recursion optimization saves stack?
- How to increase stack with ulimit?

---

## Day 40: Spot-the-Bug: Uninitialized & Off-by-One
**Topics:** Debugging, UB  
**Difficulty:** ★☆☆  
**Estimated Time:** 20-45 min

**Context:**  
Python raises exceptions. C gives you UB that optimizers exploit to delete your safety checks.

**Problem:**  
Spot-the-Bug: Uninitialized & Off-by-One: Find bugs: uninit var, off-by-one, double free, signed overflow check `if (a+100 < a)`. Compile with -O2 -Wall -Wextra and see how optimizer removes UB checks. Fix with proper overflow check.

**Starter Code:**  
#include <stdio.h>
int main(){
    int a; printf("%d\n", a); // uninit
    int b=2147483647; if(b+1 < b) printf("overflow\n"); // UB removed at O2?
    char buf[4]; buf[4]='x'; // off-by-one
}


**Constraints & Follow-Up Questions to Think About:**  
- What does UB allow compiler to assume?
- Why does ASAN/UBSAN help?
- How to write overflow-safe check?

---

## Day 41: What UB Really Means - Optimizer Breaks
**Topics:** UB, Compiler  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Python raises exceptions. C gives you UB that optimizers exploit to delete your safety checks.

**Problem:**  
What UB Really Means - Optimizer Breaks: Find bugs: uninit var, off-by-one, double free, signed overflow check `if (a+100 < a)`. Compile with -O2 -Wall -Wextra and see how optimizer removes UB checks. Fix with proper overflow check.

**Starter Code:**  
#include <stdio.h>
int main(){
    int a; printf("%d\n", a); // uninit
    int b=2147483647; if(b+1 < b) printf("overflow\n"); // UB removed at O2?
    char buf[4]; buf[4]='x'; // off-by-one
}


**Constraints & Follow-Up Questions to Think About:**  
- What does UB allow compiler to assume?
- Why does ASAN/UBSAN help?
- How to write overflow-safe check?

---

## Day 42: Program Layout: Text/Data/BSS/Heap/Stack
**Topics:** Process & memory model  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's memory model is abstract. In C you can print addresses of stack/heap/BSS to see real layout.

**Problem:**  
Program Layout: Text/Data/BSS/Heap/Stack: Print addresses of: function (text), global initialized (data), global uninit (BSS), static, stack local, heap malloc, argv, env. Compare growth. For fork/exec, show COW by modifying variable after fork. For zombies, create zombie and fix with waitpid WNOHANG loop.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int g_init=42; int g_uninit;
int main(int argc,char **argv){
    int stack; int *heap=malloc(4);
    printf("text %p data %p bss %p stack %p heap %p\n", (void*)main, (void*)&g_init, (void*)&g_uninit, (void*)&stack, (void*)heap);
    pid_t pid=fork();
    // TODO fork/exec/zombie demo
}


**Constraints & Follow-Up Questions to Think About:**  
- What is ASLR? How to disable?
- Stack vs heap which is faster alloc?
- What happens to heap after fork?

---

## Day 43: Stack vs Heap Trade-offs & Escaping
**Topics:** Stack vs heap  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's memory model is abstract. In C you can print addresses of stack/heap/BSS to see real layout.

**Problem:**  
Stack vs Heap Trade-offs & Escaping: Print addresses of: function (text), global initialized (data), global uninit (BSS), static, stack local, heap malloc, argv, env. Compare growth. For fork/exec, show COW by modifying variable after fork. For zombies, create zombie and fix with waitpid WNOHANG loop.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int g_init=42; int g_uninit;
int main(int argc,char **argv){
    int stack; int *heap=malloc(4);
    printf("text %p data %p bss %p stack %p heap %p\n", (void*)main, (void*)&g_init, (void*)&g_uninit, (void*)&stack, (void*)heap);
    pid_t pid=fork();
    // TODO fork/exec/zombie demo
}


**Constraints & Follow-Up Questions to Think About:**  
- What is ASLR? How to disable?
- Stack vs heap which is faster alloc?
- What happens to heap after fork?

---

## Day 44: Environ & getenv Without libc?
**Topics:** argc/argv, environ  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's memory model is abstract. In C you can print addresses of stack/heap/BSS to see real layout.

**Problem:**  
Environ & getenv Without libc?: Print addresses of: function (text), global initialized (data), global uninit (BSS), static, stack local, heap malloc, argv, env. Compare growth. For fork/exec, show COW by modifying variable after fork. For zombies, create zombie and fix with waitpid WNOHANG loop.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int g_init=42; int g_uninit;
int main(int argc,char **argv){
    int stack; int *heap=malloc(4);
    printf("text %p data %p bss %p stack %p heap %p\n", (void*)main, (void*)&g_init, (void*)&g_uninit, (void*)&stack, (void*)heap);
    pid_t pid=fork();
    // TODO fork/exec/zombie demo
}


**Constraints & Follow-Up Questions to Think About:**  
- What is ASLR? How to disable?
- Stack vs heap which is faster alloc?
- What happens to heap after fork?

---

## Day 45: fork() & The Copy-On-Write Illusion
**Topics:** fork()  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's memory model is abstract. In C you can print addresses of stack/heap/BSS to see real layout.

**Problem:**  
fork() & The Copy-On-Write Illusion: Print addresses of: function (text), global initialized (data), global uninit (BSS), static, stack local, heap malloc, argv, env. Compare growth. For fork/exec, show COW by modifying variable after fork. For zombies, create zombie and fix with waitpid WNOHANG loop.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int g_init=42; int g_uninit;
int main(int argc,char **argv){
    int stack; int *heap=malloc(4);
    printf("text %p data %p bss %p stack %p heap %p\n", (void*)main, (void*)&g_init, (void*)&g_uninit, (void*)&stack, (void*)heap);
    pid_t pid=fork();
    // TODO fork/exec/zombie demo
}


**Constraints & Follow-Up Questions to Think About:**  
- What is ASLR? How to disable?
- Stack vs heap which is faster alloc?
- What happens to heap after fork?

---

## Day 46: exec Family & PATH Resolution
**Topics:** exec, Process  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's memory model is abstract. In C you can print addresses of stack/heap/BSS to see real layout.

**Problem:**  
exec Family & PATH Resolution: Print addresses of: function (text), global initialized (data), global uninit (BSS), static, stack local, heap malloc, argv, env. Compare growth. For fork/exec, show COW by modifying variable after fork. For zombies, create zombie and fix with waitpid WNOHANG loop.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int g_init=42; int g_uninit;
int main(int argc,char **argv){
    int stack; int *heap=malloc(4);
    printf("text %p data %p bss %p stack %p heap %p\n", (void*)main, (void*)&g_init, (void*)&g_uninit, (void*)&stack, (void*)heap);
    pid_t pid=fork();
    // TODO fork/exec/zombie demo
}


**Constraints & Follow-Up Questions to Think About:**  
- What is ASLR? How to disable?
- Stack vs heap which is faster alloc?
- What happens to heap after fork?

---

## Day 47: Zombies & waitpid()
**Topics:** wait, Zombies  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's memory model is abstract. In C you can print addresses of stack/heap/BSS to see real layout.

**Problem:**  
Zombies & waitpid(): Print addresses of: function (text), global initialized (data), global uninit (BSS), static, stack local, heap malloc, argv, env. Compare growth. For fork/exec, show COW by modifying variable after fork. For zombies, create zombie and fix with waitpid WNOHANG loop.

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int g_init=42; int g_uninit;
int main(int argc,char **argv){
    int stack; int *heap=malloc(4);
    printf("text %p data %p bss %p stack %p heap %p\n", (void*)main, (void*)&g_init, (void*)&g_uninit, (void*)&stack, (void*)heap);
    pid_t pid=fork();
    // TODO fork/exec/zombie demo
}


**Constraints & Follow-Up Questions to Think About:**  
- What is ASLR? How to disable?
- Stack vs heap which is faster alloc?
- What happens to heap after fork?

---

## Day 48: Raw I/O: read/write vs fread/fwrite
**Topics:** Syscalls, File I/O  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's open() uses buffered stdio. Raw syscalls (read/write) are unbuffered. File descriptors are the real kernel handle.

**Problem:**  
Raw I/O: read/write vs fread/fwrite: Implement file copy using only `open/read/write/close`. Then parse binary file: struct with packed ints. Use dup/dup2 to redirect stdout to file. Use pipe() to send data parent->child. Use mmap() to cat file without read(). Implement TCP echo server/client with socket(), bind(), listen(), accept(), htons/ntohs.

**Starter Code:**  
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(){
    // TODO: raw I/O, dup2, pipe, mmap, socket
}


**Constraints & Follow-Up Questions to Think About:**  
- Buffered vs unbuffered I/O tradeoffs?
- What is file descriptor 0,1,2?
- mmap MAP_PRIVATE vs MAP_SHARED?

---

## Day 49: Binary File Parser & Struct Packing
**Topics:** Binary files, fread  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's open() uses buffered stdio. Raw syscalls (read/write) are unbuffered. File descriptors are the real kernel handle.

**Problem:**  
Binary File Parser & Struct Packing: Implement file copy using only `open/read/write/close`. Then parse binary file: struct with packed ints. Use dup/dup2 to redirect stdout to file. Use pipe() to send data parent->child. Use mmap() to cat file without read(). Implement TCP echo server/client with socket(), bind(), listen(), accept(), htons/ntohs.

**Starter Code:**  
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(){
    // TODO: raw I/O, dup2, pipe, mmap, socket
}


**Constraints & Follow-Up Questions to Think About:**  
- Buffered vs unbuffered I/O tradeoffs?
- What is file descriptor 0,1,2?
- mmap MAP_PRIVATE vs MAP_SHARED?

---

## Day 50: File Descriptors & dup/dup2 Redirection
**Topics:** FD, dup  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's open() uses buffered stdio. Raw syscalls (read/write) are unbuffered. File descriptors are the real kernel handle.

**Problem:**  
File Descriptors & dup/dup2 Redirection: Implement file copy using only `open/read/write/close`. Then parse binary file: struct with packed ints. Use dup/dup2 to redirect stdout to file. Use pipe() to send data parent->child. Use mmap() to cat file without read(). Implement TCP echo server/client with socket(), bind(), listen(), accept(), htons/ntohs.

**Starter Code:**  
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(){
    // TODO: raw I/O, dup2, pipe, mmap, socket
}


**Constraints & Follow-Up Questions to Think About:**  
- Buffered vs unbuffered I/O tradeoffs?
- What is file descriptor 0,1,2?
- mmap MAP_PRIVATE vs MAP_SHARED?

---

## Day 51: pipe() & One-Way IPC
**Topics:** pipe(), IPC  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's open() uses buffered stdio. Raw syscalls (read/write) are unbuffered. File descriptors are the real kernel handle.

**Problem:**  
pipe() & One-Way IPC: Implement file copy using only `open/read/write/close`. Then parse binary file: struct with packed ints. Use dup/dup2 to redirect stdout to file. Use pipe() to send data parent->child. Use mmap() to cat file without read(). Implement TCP echo server/client with socket(), bind(), listen(), accept(), htons/ntohs.

**Starter Code:**  
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(){
    // TODO: raw I/O, dup2, pipe, mmap, socket
}


**Constraints & Follow-Up Questions to Think About:**  
- Buffered vs unbuffered I/O tradeoffs?
- What is file descriptor 0,1,2?
- mmap MAP_PRIVATE vs MAP_SHARED?

---

## Day 52: mmap() File & Anonymous Memory
**Topics:** mmap  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Python's open() uses buffered stdio. Raw syscalls (read/write) are unbuffered. File descriptors are the real kernel handle.

**Problem:**  
mmap() File & Anonymous Memory: Implement file copy using only `open/read/write/close`. Then parse binary file: struct with packed ints. Use dup/dup2 to redirect stdout to file. Use pipe() to send data parent->child. Use mmap() to cat file without read(). Implement TCP echo server/client with socket(), bind(), listen(), accept(), htons/ntohs.

**Starter Code:**  
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(){
    // TODO: raw I/O, dup2, pipe, mmap, socket
}


**Constraints & Follow-Up Questions to Think About:**  
- Buffered vs unbuffered I/O tradeoffs?
- What is file descriptor 0,1,2?
- mmap MAP_PRIVATE vs MAP_SHARED?

---

## Day 53: Minimal TCP Echo Server (Single Client)
**Topics:** TCP, Sockets  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Python's open() uses buffered stdio. Raw syscalls (read/write) are unbuffered. File descriptors are the real kernel handle.

**Problem:**  
Minimal TCP Echo Server (Single Client): Implement file copy using only `open/read/write/close`. Then parse binary file: struct with packed ints. Use dup/dup2 to redirect stdout to file. Use pipe() to send data parent->child. Use mmap() to cat file without read(). Implement TCP echo server/client with socket(), bind(), listen(), accept(), htons/ntohs.

**Starter Code:**  
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(){
    // TODO: raw I/O, dup2, pipe, mmap, socket
}


**Constraints & Follow-Up Questions to Think About:**  
- Buffered vs unbuffered I/O tradeoffs?
- What is file descriptor 0,1,2?
- mmap MAP_PRIVATE vs MAP_SHARED?

---

## Day 54: Minimal TCP Client & Byte Order
**Topics:** TCP, htons  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's open() uses buffered stdio. Raw syscalls (read/write) are unbuffered. File descriptors are the real kernel handle.

**Problem:**  
Minimal TCP Client & Byte Order: Implement file copy using only `open/read/write/close`. Then parse binary file: struct with packed ints. Use dup/dup2 to redirect stdout to file. Use pipe() to send data parent->child. Use mmap() to cat file without read(). Implement TCP echo server/client with socket(), bind(), listen(), accept(), htons/ntohs.

**Starter Code:**  
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(){
    // TODO: raw I/O, dup2, pipe, mmap, socket
}


**Constraints & Follow-Up Questions to Think About:**  
- Buffered vs unbuffered I/O tradeoffs?
- What is file descriptor 0,1,2?
- mmap MAP_PRIVATE vs MAP_SHARED?

---

## Day 55: pthreads: Create/Join & Argument Lifetime
**Topics:** pthread  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's threading has GIL. In C pthreads run truly parallel, so races are real.

**Problem:**  
pthreads: Create/Join & Argument Lifetime: Demonstrate race with 2 threads incrementing global 100k times without lock (lose counts). Fix with mutex. Show deadlock with 2 mutexes opposite order. For producer-consumer, implement bounded buffer with mutex+condvar or semaphore. Build thread pool.

**Starter Code:**  
#include <stdio.h>
#include <pthread.h>
int counter=0;
void *inc(void *arg){ for(int i=0;i<100000;i++) counter++; return NULL; }
int main(){
    pthread_t t1,t2;
    pthread_create(&t1,NULL,inc,NULL);
    pthread_create(&t2,NULL,inc,NULL);
    pthread_join(t1,NULL); pthread_join(t2,NULL);
    printf("counter=%d expected 200000\n", counter);
}


**Constraints & Follow-Up Questions to Think About:**  
- Why does race lose updates? (load-add-store not atomic)
- Mutex vs semaphore?
- Condition variable spurious wakeup - why while loop?

---

## Day 56: Race Condition: The Lost Update
**Topics:** Race, Concurrency  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's threading has GIL. In C pthreads run truly parallel, so races are real.

**Problem:**  
Race Condition: The Lost Update: Demonstrate race with 2 threads incrementing global 100k times without lock (lose counts). Fix with mutex. Show deadlock with 2 mutexes opposite order. For producer-consumer, implement bounded buffer with mutex+condvar or semaphore. Build thread pool.

**Starter Code:**  
#include <stdio.h>
#include <pthread.h>
int counter=0;
void *inc(void *arg){ for(int i=0;i<100000;i++) counter++; return NULL; }
int main(){
    pthread_t t1,t2;
    pthread_create(&t1,NULL,inc,NULL);
    pthread_create(&t2,NULL,inc,NULL);
    pthread_join(t1,NULL); pthread_join(t2,NULL);
    printf("counter=%d expected 200000\n", counter);
}


**Constraints & Follow-Up Questions to Think About:**  
- Why does race lose updates? (load-add-store not atomic)
- Mutex vs semaphore?
- Condition variable spurious wakeup - why while loop?

---

## Day 57: Mutex Fix & Deadly Patterns
**Topics:** Mutex  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's threading has GIL. In C pthreads run truly parallel, so races are real.

**Problem:**  
Mutex Fix & Deadly Patterns: Demonstrate race with 2 threads incrementing global 100k times without lock (lose counts). Fix with mutex. Show deadlock with 2 mutexes opposite order. For producer-consumer, implement bounded buffer with mutex+condvar or semaphore. Build thread pool.

**Starter Code:**  
#include <stdio.h>
#include <pthread.h>
int counter=0;
void *inc(void *arg){ for(int i=0;i<100000;i++) counter++; return NULL; }
int main(){
    pthread_t t1,t2;
    pthread_create(&t1,NULL,inc,NULL);
    pthread_create(&t2,NULL,inc,NULL);
    pthread_join(t1,NULL); pthread_join(t2,NULL);
    printf("counter=%d expected 200000\n", counter);
}


**Constraints & Follow-Up Questions to Think About:**  
- Why does race lose updates? (load-add-store not atomic)
- Mutex vs semaphore?
- Condition variable spurious wakeup - why while loop?

---

## Day 58: Condition Variables: The Right Way
**Topics:** Condvar  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Python's threading has GIL. In C pthreads run truly parallel, so races are real.

**Problem:**  
Condition Variables: The Right Way: Demonstrate race with 2 threads incrementing global 100k times without lock (lose counts). Fix with mutex. Show deadlock with 2 mutexes opposite order. For producer-consumer, implement bounded buffer with mutex+condvar or semaphore. Build thread pool.

**Starter Code:**  
#include <stdio.h>
#include <pthread.h>
int counter=0;
void *inc(void *arg){ for(int i=0;i<100000;i++) counter++; return NULL; }
int main(){
    pthread_t t1,t2;
    pthread_create(&t1,NULL,inc,NULL);
    pthread_create(&t2,NULL,inc,NULL);
    pthread_join(t1,NULL); pthread_join(t2,NULL);
    printf("counter=%d expected 200000\n", counter);
}


**Constraints & Follow-Up Questions to Think About:**  
- Why does race lose updates? (load-add-store not atomic)
- Mutex vs semaphore?
- Condition variable spurious wakeup - why while loop?

---

## Day 59: Semaphores & Counting
**Topics:** Semaphores  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's threading has GIL. In C pthreads run truly parallel, so races are real.

**Problem:**  
Semaphores & Counting: Demonstrate race with 2 threads incrementing global 100k times without lock (lose counts). Fix with mutex. Show deadlock with 2 mutexes opposite order. For producer-consumer, implement bounded buffer with mutex+condvar or semaphore. Build thread pool.

**Starter Code:**  
#include <stdio.h>
#include <pthread.h>
int counter=0;
void *inc(void *arg){ for(int i=0;i<100000;i++) counter++; return NULL; }
int main(){
    pthread_t t1,t2;
    pthread_create(&t1,NULL,inc,NULL);
    pthread_create(&t2,NULL,inc,NULL);
    pthread_join(t1,NULL); pthread_join(t2,NULL);
    printf("counter=%d expected 200000\n", counter);
}


**Constraints & Follow-Up Questions to Think About:**  
- Why does race lose updates? (load-add-store not atomic)
- Mutex vs semaphore?
- Condition variable spurious wakeup - why while loop?

---

## Day 60: Producer-Consumer with Ring Buffer
**Topics:** Prod-Cons, Concurrency  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Python's threading has GIL. In C pthreads run truly parallel, so races are real.

**Problem:**  
Producer-Consumer with Ring Buffer: Demonstrate race with 2 threads incrementing global 100k times without lock (lose counts). Fix with mutex. Show deadlock with 2 mutexes opposite order. For producer-consumer, implement bounded buffer with mutex+condvar or semaphore. Build thread pool.

**Starter Code:**  
#include <stdio.h>
#include <pthread.h>
int counter=0;
void *inc(void *arg){ for(int i=0;i<100000;i++) counter++; return NULL; }
int main(){
    pthread_t t1,t2;
    pthread_create(&t1,NULL,inc,NULL);
    pthread_create(&t2,NULL,inc,NULL);
    pthread_join(t1,NULL); pthread_join(t2,NULL);
    printf("counter=%d expected 200000\n", counter);
}


**Constraints & Follow-Up Questions to Think About:**  
- Why does race lose updates? (load-add-store not atomic)
- Mutex vs semaphore?
- Condition variable spurious wakeup - why while loop?

---

## Day 61: Building & Resolving Deadlock
**Topics:** Deadlock  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Python's threading has GIL. In C pthreads run truly parallel, so races are real.

**Problem:**  
Building & Resolving Deadlock: Demonstrate race with 2 threads incrementing global 100k times without lock (lose counts). Fix with mutex. Show deadlock with 2 mutexes opposite order. For producer-consumer, implement bounded buffer with mutex+condvar or semaphore. Build thread pool.

**Starter Code:**  
#include <stdio.h>
#include <pthread.h>
int counter=0;
void *inc(void *arg){ for(int i=0;i<100000;i++) counter++; return NULL; }
int main(){
    pthread_t t1,t2;
    pthread_create(&t1,NULL,inc,NULL);
    pthread_create(&t2,NULL,inc,NULL);
    pthread_join(t1,NULL); pthread_join(t2,NULL);
    printf("counter=%d expected 200000\n", counter);
}


**Constraints & Follow-Up Questions to Think About:**  
- Why does race lose updates? (load-add-store not atomic)
- Mutex vs semaphore?
- Condition variable spurious wakeup - why while loop?

---

## Day 62: Signal Handler for SIGINT (Graceful Exit)
**Topics:** Signals  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python signals are handled in interpreter. In C handlers are async, very limited what you can do safely.

**Problem:**  
Signal Handler for SIGINT (Graceful Exit): Install SIGINT handler that sets volatile sig_atomic_t flag. Show non-safe handler calling printf (unsafe). Block signals with sigprocmask around critical section. Handle SIGCHLD to reap zombies automatically. For SIGSEGV, print backtrace using backtrace().

**Starter Code:**  
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
volatile sig_atomic_t stop=0;
void handler(int sig){ stop=1; }
int main(){
    signal(SIGINT, handler);
    while(!stop){ pause(); }
    printf("Graceful exit\n");
}


**Constraints & Follow-Up Questions to Think About:**  
- What functions are async-signal-safe?
- Why volatile sig_atomic_t?
- Signal masking inheritance across fork/exec/pthreads?

---

## Day 63: SIGSEGV Handler & Backtrace
**Topics:** Signals, SIGSEGV  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Python signals are handled in interpreter. In C handlers are async, very limited what you can do safely.

**Problem:**  
SIGSEGV Handler & Backtrace: Install SIGINT handler that sets volatile sig_atomic_t flag. Show non-safe handler calling printf (unsafe). Block signals with sigprocmask around critical section. Handle SIGCHLD to reap zombies automatically. For SIGSEGV, print backtrace using backtrace().

**Starter Code:**  
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
volatile sig_atomic_t stop=0;
void handler(int sig){ stop=1; }
int main(){
    signal(SIGINT, handler);
    while(!stop){ pause(); }
    printf("Graceful exit\n");
}


**Constraints & Follow-Up Questions to Think About:**  
- What functions are async-signal-safe?
- Why volatile sig_atomic_t?
- Signal masking inheritance across fork/exec/pthreads?

---

## Day 64: Blocking/Unblocking Signals & sigprocmask
**Topics:** Signals, Mask  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python signals are handled in interpreter. In C handlers are async, very limited what you can do safely.

**Problem:**  
Blocking/Unblocking Signals & sigprocmask: Install SIGINT handler that sets volatile sig_atomic_t flag. Show non-safe handler calling printf (unsafe). Block signals with sigprocmask around critical section. Handle SIGCHLD to reap zombies automatically. For SIGSEGV, print backtrace using backtrace().

**Starter Code:**  
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
volatile sig_atomic_t stop=0;
void handler(int sig){ stop=1; }
int main(){
    signal(SIGINT, handler);
    while(!stop){ pause(); }
    printf("Graceful exit\n");
}


**Constraints & Follow-Up Questions to Think About:**  
- What functions are async-signal-safe?
- Why volatile sig_atomic_t?
- Signal masking inheritance across fork/exec/pthreads?

---

## Day 65: Reentrancy & async-signal-safety
**Topics:** Reentrancy, Signals  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Python signals are handled in interpreter. In C handlers are async, very limited what you can do safely.

**Problem:**  
Reentrancy & async-signal-safety: Install SIGINT handler that sets volatile sig_atomic_t flag. Show non-safe handler calling printf (unsafe). Block signals with sigprocmask around critical section. Handle SIGCHLD to reap zombies automatically. For SIGSEGV, print backtrace using backtrace().

**Starter Code:**  
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
volatile sig_atomic_t stop=0;
void handler(int sig){ stop=1; }
int main(){
    signal(SIGINT, handler);
    while(!stop){ pause(); }
    printf("Graceful exit\n");
}


**Constraints & Follow-Up Questions to Think About:**  
- What functions are async-signal-safe?
- Why volatile sig_atomic_t?
- Signal masking inheritance across fork/exec/pthreads?

---

## Day 66: Break The Build: Multi-File Link Error
**Topics:** Compilation & linking  
**Difficulty:** ★☆☆  
**Estimated Time:** 20-45 min

**Context:**  
Python hides compilation. In C you manage preprocessing, compiling, linking, libraries.

**Problem:**  
Break The Build: Multi-File Link Error: Create multi-file project that fails linking (duplicate symbol). Fix with header guards, extern. Build static lib with ar, dynamic with -fPIC -shared, observe size with nm, objdump -d, readelf -h. Hook malloc via LD_PRELOAD.

**Starter Code:**  
// file: main.c
// file: util.h, util.c
// gcc -c util.c; ar rcs libutil.a util.o; gcc main.c -L. -lutil
// gcc -fPIC -shared util.c -o libutil.so; gcc main.c -L. -lutil -Wl,-rpath,.
int main(){}


**Constraints & Follow-Up Questions to Think About:**  
- Compilation stages: preprocessing, compilation, assembly, linking.
- Static vs dynamic linking tradeoffs?
- What does -fPIC do?

---

## Day 67: Static vs Dynamic Library
**Topics:** Static vs Dynamic  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python hides compilation. In C you manage preprocessing, compiling, linking, libraries.

**Problem:**  
Static vs Dynamic Library: Create multi-file project that fails linking (duplicate symbol). Fix with header guards, extern. Build static lib with ar, dynamic with -fPIC -shared, observe size with nm, objdump -d, readelf -h. Hook malloc via LD_PRELOAD.

**Starter Code:**  
// file: main.c
// file: util.h, util.c
// gcc -c util.c; ar rcs libutil.a util.o; gcc main.c -L. -lutil
// gcc -fPIC -shared util.c -o libutil.so; gcc main.c -L. -lutil -Wl,-rpath,.
int main(){}


**Constraints & Follow-Up Questions to Think About:**  
- Compilation stages: preprocessing, compilation, assembly, linking.
- Static vs dynamic linking tradeoffs?
- What does -fPIC do?

---

## Day 68: Header Guards & Macro Pitfalls
**Topics:** Preprocessor, Macros  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python hides compilation. In C you manage preprocessing, compiling, linking, libraries.

**Problem:**  
Header Guards & Macro Pitfalls: Create multi-file project that fails linking (duplicate symbol). Fix with header guards, extern. Build static lib with ar, dynamic with -fPIC -shared, observe size with nm, objdump -d, readelf -h. Hook malloc via LD_PRELOAD.

**Starter Code:**  
// file: main.c
// file: util.h, util.c
// gcc -c util.c; ar rcs libutil.a util.o; gcc main.c -L. -lutil
// gcc -fPIC -shared util.c -o libutil.so; gcc main.c -L. -lutil -Wl,-rpath,.
int main(){}


**Constraints & Follow-Up Questions to Think About:**  
- Compilation stages: preprocessing, compilation, assembly, linking.
- Static vs dynamic linking tradeoffs?
- What does -fPIC do?

---

## Day 69: Inspecting Binaries: objdump/nm/readelf
**Topics:** Binaries, Tools  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python hides compilation. In C you manage preprocessing, compiling, linking, libraries.

**Problem:**  
Inspecting Binaries: objdump/nm/readelf: Create multi-file project that fails linking (duplicate symbol). Fix with header guards, extern. Build static lib with ar, dynamic with -fPIC -shared, observe size with nm, objdump -d, readelf -h. Hook malloc via LD_PRELOAD.

**Starter Code:**  
// file: main.c
// file: util.h, util.c
// gcc -c util.c; ar rcs libutil.a util.o; gcc main.c -L. -lutil
// gcc -fPIC -shared util.c -o libutil.so; gcc main.c -L. -lutil -Wl,-rpath,.
int main(){}


**Constraints & Follow-Up Questions to Think About:**  
- Compilation stages: preprocessing, compilation, assembly, linking.
- Static vs dynamic linking tradeoffs?
- What does -fPIC do?

---

## Day 70: Timing: clock() vs gettimeofday vs clock_gettime
**Topics:** Timing  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's time.time() is simple. In C you have clock(), gettimeofday(), clock_gettime() with monotonic vs realtime. Performance needs cache awareness.

**Problem:**  
Timing: clock() vs gettimeofday vs clock_gettime: Compare clock() vs CLOCK_MONOTONIC timing of sorting. Implement row-major vs column-major matrix sum to show cache miss difference (e.g., 4096x4096). Show volatile prevents optimization of busy loop. Measure.

**Starter Code:**  
#include <stdio.h>
#include <time.h>
#define N 4096
static int mat[N][N];
int main(){
    struct timespec s,e;
    clock_gettime(CLOCK_MONOTONIC,&s);
    // TODO: row vs col sum
    clock_gettime(CLOCK_MONOTONIC,&e);
}


**Constraints & Follow-Up Questions to Think About:**  
- Why CLOCK_MONOTONIC vs REALTIME?
- What is cache line? Why row-major faster in C?
- When is volatile actually needed (memory-mapped I/O)?

---

## Day 71: Cache-Friendly Access: Row vs Column Major
**Topics:** Performance, Cache  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's time.time() is simple. In C you have clock(), gettimeofday(), clock_gettime() with monotonic vs realtime. Performance needs cache awareness.

**Problem:**  
Cache-Friendly Access: Row vs Column Major: Compare clock() vs CLOCK_MONOTONIC timing of sorting. Implement row-major vs column-major matrix sum to show cache miss difference (e.g., 4096x4096). Show volatile prevents optimization of busy loop. Measure.

**Starter Code:**  
#include <stdio.h>
#include <time.h>
#define N 4096
static int mat[N][N];
int main(){
    struct timespec s,e;
    clock_gettime(CLOCK_MONOTONIC,&s);
    // TODO: row vs col sum
    clock_gettime(CLOCK_MONOTONIC,&e);
}


**Constraints & Follow-Up Questions to Think About:**  
- Why CLOCK_MONOTONIC vs REALTIME?
- What is cache line? Why row-major faster in C?
- When is volatile actually needed (memory-mapped I/O)?

---

## Day 72: volatile & Compiler Optimization Trap
**Topics:** volatile, Optimizer  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Python's time.time() is simple. In C you have clock(), gettimeofday(), clock_gettime() with monotonic vs realtime. Performance needs cache awareness.

**Problem:**  
volatile & Compiler Optimization Trap: Compare clock() vs CLOCK_MONOTONIC timing of sorting. Implement row-major vs column-major matrix sum to show cache miss difference (e.g., 4096x4096). Show volatile prevents optimization of busy loop. Measure.

**Starter Code:**  
#include <stdio.h>
#include <time.h>
#define N 4096
static int mat[N][N];
int main(){
    struct timespec s,e;
    clock_gettime(CLOCK_MONOTONIC,&s);
    // TODO: row vs col sum
    clock_gettime(CLOCK_MONOTONIC,&e);
}


**Constraints & Follow-Up Questions to Think About:**  
- Why CLOCK_MONOTONIC vs REALTIME?
- What is cache line? Why row-major faster in C?
- When is volatile actually needed (memory-mapped I/O)?

---

## Day 73: CAPSTONE Day 1/3: Tiny Bytecode VM - Stack Machine Design
**Topics:** Capstone: VM  
**Difficulty:** ★★★  
**Estimated Time:** 60-120 min

**Context:**  
Build a tiny virtual machine - like Python's own bytecode interpreter but minimal. This is how Python executes.

**Problem:**  
CAPSTONE Day 1/3: Tiny Bytecode VM - Stack Machine Design: Design bytecode: PUSH, ADD, SUB, MUL, DIV, PRINT, HALT, JMP, JZ, CALL/RET, LOAD/STORE. Day1 design stack machine struct with pc, sp, stack[], program[]. Day2 implement assembler parsing text -> bytecode. Day3 add calls and locals.

**Starter Code:**  
#include <stdio.h>
#include <stdint.h>
enum { OP_PUSH, OP_ADD, OP_SUB, OP_MUL, OP_PRINT, OP_HALT, OP_JMP, OP_JZ };
typedef struct { int stack[1024]; int sp; int pc; uint8_t *code; } VM;
void vm_run(VM *vm){ /* TODO */ }
int main(){ uint8_t prog[]={OP_PUSH,42, OP_PUSH,10, OP_ADD, OP_PRINT, OP_HALT}; VM vm={0}; vm.code=prog; vm_run(&vm); }


**Constraints & Follow-Up Questions to Think About:**  
- Stack machine vs register machine?
- How Python VM differs?
- How to handle overflow in VM stack?

---

## Day 74: CAPSTONE Day 2/3: Bytecode VM - Assembler & Execution
**Topics:** Capstone: VM  
**Difficulty:** ★★★  
**Estimated Time:** 60-120 min

**Context:**  
Build a tiny virtual machine - like Python's own bytecode interpreter but minimal. This is how Python executes.

**Problem:**  
CAPSTONE Day 2/3: Bytecode VM - Assembler & Execution: Design bytecode: PUSH, ADD, SUB, MUL, DIV, PRINT, HALT, JMP, JZ, CALL/RET, LOAD/STORE. Day1 design stack machine struct with pc, sp, stack[], program[]. Day2 implement assembler parsing text -> bytecode. Day3 add calls and locals.

**Starter Code:**  
#include <stdio.h>
#include <stdint.h>
enum { OP_PUSH, OP_ADD, OP_SUB, OP_MUL, OP_PRINT, OP_HALT, OP_JMP, OP_JZ };
typedef struct { int stack[1024]; int sp; int pc; uint8_t *code; } VM;
void vm_run(VM *vm){ /* TODO */ }
int main(){ uint8_t prog[]={OP_PUSH,42, OP_PUSH,10, OP_ADD, OP_PRINT, OP_HALT}; VM vm={0}; vm.code=prog; vm_run(&vm); }


**Constraints & Follow-Up Questions to Think About:**  
- Stack machine vs register machine?
- How Python VM differs?
- How to handle overflow in VM stack?

---

## Day 75: CAPSTONE Day 3/3: VM Extensions - Calls & Memory
**Topics:** Capstone: VM  
**Difficulty:** ★★★  
**Estimated Time:** 60-120 min

**Context:**  
Build a tiny virtual machine - like Python's own bytecode interpreter but minimal. This is how Python executes.

**Problem:**  
CAPSTONE Day 3/3: VM Extensions - Calls & Memory: Design bytecode: PUSH, ADD, SUB, MUL, DIV, PRINT, HALT, JMP, JZ, CALL/RET, LOAD/STORE. Day1 design stack machine struct with pc, sp, stack[], program[]. Day2 implement assembler parsing text -> bytecode. Day3 add calls and locals.

**Starter Code:**  
#include <stdio.h>
#include <stdint.h>
enum { OP_PUSH, OP_ADD, OP_SUB, OP_MUL, OP_PRINT, OP_HALT, OP_JMP, OP_JZ };
typedef struct { int stack[1024]; int sp; int pc; uint8_t *code; } VM;
void vm_run(VM *vm){ /* TODO */ }
int main(){ uint8_t prog[]={OP_PUSH,42, OP_PUSH,10, OP_ADD, OP_PRINT, OP_HALT}; VM vm={0}; vm.code=prog; vm_run(&vm); }


**Constraints & Follow-Up Questions to Think About:**  
- Stack machine vs register machine?
- How Python VM differs?
- How to handle overflow in VM stack?

---

## Day 76: Pointer to Pointers to Pointers - 3-Star Programmer
**Topics:** Pointers  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Pointer to Pointers to Pointers - 3-Star Programmer. Combines multiple concepts from your list.

**Problem:**  
Implement Pointer to Pointers to Pointers - 3-Star Programmer from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Pointer to Pointers to Pointers - 3-Star Programmer
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 77: Function Pointer State Machine
**Topics:** Function ptr, State machine  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Function Pointer State Machine. Combines multiple concepts from your list.

**Problem:**  
Implement Function Pointer State Machine from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Function Pointer State Machine
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 78: Generic Vector with void* & Macros
**Topics:** Generic, Macro, malloc  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Generic Vector with void* & Macros. Combines multiple concepts from your list.

**Problem:**  
Implement Generic Vector with void* & Macros from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Generic Vector with void* & Macros
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 79: Custom realloc That Never Moves?
**Topics:** realloc, Memory  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Custom realloc That Never Moves?. Combines multiple concepts from your list.

**Problem:**  
Implement Custom realloc That Never Moves? from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Custom realloc That Never Moves?
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 80: Arena Allocator & Lifetime
**Topics:** Allocator, Arena  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Arena Allocator & Lifetime. Combines multiple concepts from your list.

**Problem:**  
Implement Arena Allocator & Lifetime from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Arena Allocator & Lifetime
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 81: Bitmask Allocator for 1024 Slots
**Topics:** Bitwise, Allocator  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Bitmask Allocator for 1024 Slots. Combines multiple concepts from your list.

**Problem:**  
Implement Bitmask Allocator for 1024 Slots from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Bitmask Allocator for 1024 Slots
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 82: Bit Tricks: Power-of-Two & Isolate LSB
**Topics:** Bitwise tricks  
**Difficulty:** ★☆☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Bit Tricks: Power-of-Two & Isolate LSB. Combines multiple concepts from your list.

**Problem:**  
Implement Bit Tricks: Power-of-Two & Isolate LSB from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Bit Tricks: Power-of-Two & Isolate LSB
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 83: Endianness-Safe Network Packet Parser
**Topics:** Endianness, Structs  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Endianness-Safe Network Packet Parser. Combines multiple concepts from your list.

**Problem:**  
Implement Endianness-Safe Network Packet Parser from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Endianness-Safe Network Packet Parser
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 84: Struct Packing for Binary Protocol
**Topics:** Struct layout, Packing  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Struct Packing for Binary Protocol. Combines multiple concepts from your list.

**Problem:**  
Implement Struct Packing for Binary Protocol from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Struct Packing for Binary Protocol
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 85: Union for Float Bit Hacking
**Topics:** Union, Float  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Union for Float Bit Hacking. Combines multiple concepts from your list.

**Problem:**  
Implement Union for Float Bit Hacking from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Union for Float Bit Hacking
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 86: Tagged Union Expression Evaluator
**Topics:** Tagged union, Recursion  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Tagged Union Expression Evaluator. Combines multiple concepts from your list.

**Problem:**  
Implement Tagged Union Expression Evaluator from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Tagged Union Expression Evaluator
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 87: strlen Using Word-Sized Reads (Fast)
**Topics:** Strings, Performance  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - strlen Using Word-Sized Reads (Fast). Combines multiple concepts from your list.

**Problem:**  
Implement strlen Using Word-Sized Reads (Fast) from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: strlen Using Word-Sized Reads (Fast)
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 88: In-Place URL Decode
**Topics:** Strings, In-place  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - In-Place URL Decode. Combines multiple concepts from your list.

**Problem:**  
Implement In-Place URL Decode from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: In-Place URL Decode
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 89: Circular Buffer with Overwrite Policy
**Topics:** Circular buffer  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Circular Buffer with Overwrite Policy. Combines multiple concepts from your list.

**Problem:**  
Implement Circular Buffer with Overwrite Policy from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Circular Buffer with Overwrite Policy
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 90: Intrusive Linked List (Linux Style)
**Topics:** Linked list, Intrusive  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Intrusive Linked List (Linux Style). Combines multiple concepts from your list.

**Problem:**  
Implement Intrusive Linked List (Linux Style) from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Intrusive Linked List (Linux Style)
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 91: Hash Table with Separate Chaining & Resize
**Topics:** Hash table, Resize  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Hash Table with Separate Chaining & Resize. Combines multiple concepts from your list.

**Problem:**  
Implement Hash Table with Separate Chaining & Resize from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Hash Table with Separate Chaining & Resize
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 92: Binary Search Tree Without Recursion
**Topics:** BST, Stack  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Binary Search Tree Without Recursion. Combines multiple concepts from your list.

**Problem:**  
Implement Binary Search Tree Without Recursion from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Binary Search Tree Without Recursion
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 93: Fixed-Point PID Controller
**Topics:** Fixed-point, Embedded  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Fixed-Point PID Controller. Combines multiple concepts from your list.

**Problem:**  
Implement Fixed-Point PID Controller from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Fixed-Point PID Controller
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 94: itoa Base 2-36 with Negative Handling
**Topics:** Number rep, itoa  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - itoa Base 2-36 with Negative Handling. Combines multiple concepts from your list.

**Problem:**  
Implement itoa Base 2-36 with Negative Handling from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: itoa Base 2-36 with Negative Handling
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 95: Recursion to Iteration: Manual Stack
**Topics:** Recursion, Stack  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Recursion to Iteration: Manual Stack. Combines multiple concepts from your list.

**Problem:**  
Implement Recursion to Iteration: Manual Stack from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Recursion to Iteration: Manual Stack
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 96: UB in Signed Overflow: Compiler Deletes Check?
**Topics:** UB, Overflow  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - UB in Signed Overflow: Compiler Deletes Check?. Combines multiple concepts from your list.

**Problem:**  
Implement UB in Signed Overflow: Compiler Deletes Check? from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: UB in Signed Overflow: Compiler Deletes Check?
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 97: Where Are My Vars? Printing Addresses
**Topics:** Memory model, Addresses  
**Difficulty:** ★☆☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Where Are My Vars? Printing Addresses. Combines multiple concepts from your list.

**Problem:**  
Implement Where Are My Vars? Printing Addresses from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Where Are My Vars? Printing Addresses
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 98: fork() Bomb & Limits
**Topics:** fork, Process  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - fork() Bomb & Limits. Combines multiple concepts from your list.

**Problem:**  
Implement fork() Bomb & Limits from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: fork() Bomb & Limits
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 99: Mini Shell: fork/exec/wait (Part 1)
**Topics:** Capstone: Shell  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Building a mini-shell combines fork/exec/wait, pipes, dup2, signals - the Unix core. Like bash but tiny.

**Problem:**  
Mini Shell: fork/exec/wait (Part 1): Part1: loop read line, tokenize, fork/exec, waitpid, handle cd/exit builtins. Part2: handle `|`, `>`, `<`, `>>` using pipe() and dup2. Add SIGINT handling (Ctrl-C shouldn't kill shell).

**Starter Code:**  
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
int main(){
    char line[1024];
    while(1){ printf("$ "); fgets(line,sizeof(line),stdin); /* TODO parse & fork/exec */ }
}


**Constraints & Follow-Up Questions to Think About:**  
- Why shell must fork before exec?
- How pipe + dup2 chain works?
- How bash handles background &?

---

## Day 100: Mini Shell: Pipes & Redirection (Part 2)
**Topics:** Capstone: Shell  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Building a mini-shell combines fork/exec/wait, pipes, dup2, signals - the Unix core. Like bash but tiny.

**Problem:**  
Mini Shell: Pipes & Redirection (Part 2): Part1: loop read line, tokenize, fork/exec, waitpid, handle cd/exit builtins. Part2: handle `|`, `>`, `<`, `>>` using pipe() and dup2. Add SIGINT handling (Ctrl-C shouldn't kill shell).

**Starter Code:**  
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
int main(){
    char line[1024];
    while(1){ printf("$ "); fgets(line,sizeof(line),stdin); /* TODO parse & fork/exec */ }
}


**Constraints & Follow-Up Questions to Think About:**  
- Why shell must fork before exec?
- How pipe + dup2 chain works?
- How bash handles background &?

---

## Day 101: Raw File Copy with read/write Loop
**Topics:** File I/O, Syscalls  
**Difficulty:** ★☆☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Raw File Copy with read/write Loop. Combines multiple concepts from your list.

**Problem:**  
Implement Raw File Copy with read/write Loop from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Raw File Copy with read/write Loop
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 102: Atomic File Replace with rename()
**Topics:** File I/O, Atomicity  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Atomic File Replace with rename(). Combines multiple concepts from your list.

**Problem:**  
Implement Atomic File Replace with rename() from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Atomic File Replace with rename()
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 103: dup2 for Shell Redirection Simulation
**Topics:** dup2, Shell  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Building a mini-shell combines fork/exec/wait, pipes, dup2, signals - the Unix core. Like bash but tiny.

**Problem:**  
dup2 for Shell Redirection Simulation: Part1: loop read line, tokenize, fork/exec, waitpid, handle cd/exit builtins. Part2: handle `|`, `>`, `<`, `>>` using pipe() and dup2. Add SIGINT handling (Ctrl-C shouldn't kill shell).

**Starter Code:**  
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
int main(){
    char line[1024];
    while(1){ printf("$ "); fgets(line,sizeof(line),stdin); /* TODO parse & fork/exec */ }
}


**Constraints & Follow-Up Questions to Think About:**  
- Why shell must fork before exec?
- How pipe + dup2 chain works?
- How bash handles background &?

---

## Day 104: pipe() + fork() Chat (Bidirectional)
**Topics:** pipe, fork  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - pipe() + fork() Chat (Bidirectional). Combines multiple concepts from your list.

**Problem:**  
Implement pipe() + fork() Chat (Bidirectional) from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: pipe() + fork() Chat (Bidirectional)
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 105: mmap() Shared Counter Between Processes
**Topics:** mmap, IPC, fork  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - mmap() Shared Counter Between Processes. Combines multiple concepts from your list.

**Problem:**  
Implement mmap() Shared Counter Between Processes from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: mmap() Shared Counter Between Processes
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 106: TCP Echo Server with fork() Per Client
**Topics:** TCP, fork, Server  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Network servers need concurrency + robustness. Python's socketserver hides details. Build it in C.

**Problem:**  
TCP Echo Server with fork() Per Client: Build multi-threaded TCP echo server: accept loop, spawn pthread per client (or thread pool), handle partial read/write, graceful shutdown via signal, stats with atomic counter. Client: handle reconnection.

**Starter Code:**  
#include <pthread.h>
#include <netinet/in.h>
#include <unistd.h>
void *client_handler(void *fd_ptr){ int fd=*(int*)fd_ptr; char buf[1024]; /* echo */ return NULL; }
int main(){ int srv=socket(AF_INET,SOCK_STREAM,0); /* bind listen accept */ }


**Constraints & Follow-Up Questions to Think About:**  
- Thread-per-client vs thread pool vs epoll?
- What is TIME_WAIT? SO_REUSEADDR?
- How to handle slowloris?

---

## Day 107: Select() Based Multiplexed Echo Server
**Topics:** select, TCP, Multiplex  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Select() Based Multiplexed Echo Server. Combines multiple concepts from your list.

**Problem:**  
Implement Select() Based Multiplexed Echo Server from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Select() Based Multiplexed Echo Server
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 108: Thread Pool From Scratch
**Topics:** Concurrency, Thread pool  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Thread Pool From Scratch. Combines multiple concepts from your list.

**Problem:**  
Implement Thread Pool From Scratch from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Thread Pool From Scratch
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 109: Lock-Free? Test-and-Set with __sync
**Topics:** Concurrency, Atomics  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Lock-Free? Test-and-Set with __sync. Combines multiple concepts from your list.

**Problem:**  
Implement Lock-Free? Test-and-Set with __sync from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Lock-Free? Test-and-Set with __sync
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 110: Readers-Writers Problem
**Topics:** Concurrency, RW Lock  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Readers-Writers Problem. Combines multiple concepts from your list.

**Problem:**  
Implement Readers-Writers Problem from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Readers-Writers Problem
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 111: Producer-Consumer with Semaphores
**Topics:** Semaphores, Prod-Cons  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Producer-Consumer with Semaphores. Combines multiple concepts from your list.

**Problem:**  
Implement Producer-Consumer with Semaphores from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Producer-Consumer with Semaphores
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 112: Deadlock by Lock Ordering
**Topics:** Deadlock, Mutex  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Deadlock by Lock Ordering. Combines multiple concepts from your list.

**Problem:**  
Implement Deadlock by Lock Ordering from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Deadlock by Lock Ordering
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 113: Signal vs Thread: Handling SIGINT in MT
**Topics:** Signals, Threads  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Signal vs Thread: Handling SIGINT in MT. Combines multiple concepts from your list.

**Problem:**  
Implement Signal vs Thread: Handling SIGINT in MT from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Signal vs Thread: Handling SIGINT in MT
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 114: Custom SIGCHLD Handler to Reap Zombies
**Topics:** Signals, SIGCHLD  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Custom SIGCHLD Handler to Reap Zombies. Combines multiple concepts from your list.

**Problem:**  
Implement Custom SIGCHLD Handler to Reap Zombies from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Custom SIGCHLD Handler to Reap Zombies
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 115: Static Library: ar & ranlib Mystery
**Topics:** Static libs  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Static Library: ar & ranlib Mystery. Combines multiple concepts from your list.

**Problem:**  
Implement Static Library: ar & ranlib Mystery from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Static Library: ar & ranlib Mystery
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 116: Dynamic Library & LD_PRELOAD Hook
**Topics:** Dynamic libs, LD_PRELOAD  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Dynamic Library & LD_PRELOAD Hook. Combines multiple concepts from your list.

**Problem:**  
Implement Dynamic Library & LD_PRELOAD Hook from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Dynamic Library & LD_PRELOAD Hook
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 117: Macro Black Magic: X-Macros
**Topics:** Macros, Preprocessor  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Macro Black Magic: X-Macros. Combines multiple concepts from your list.

**Problem:**  
Implement Macro Black Magic: X-Macros from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Macro Black Magic: X-Macros
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 118: Performance: False Sharing
**Topics:** Performance, Cache, Threads  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Performance: False Sharing. Combines multiple concepts from your list.

**Problem:**  
Implement Performance: False Sharing from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Performance: False Sharing
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 119: Cache Line & Struct Padding for Speed
**Topics:** Cache, Padding  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Cache Line & Struct Padding for Speed. Combines multiple concepts from your list.

**Problem:**  
Implement Cache Line & Struct Padding for Speed from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Cache Line & Struct Padding for Speed
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 120: CAPSTONE Day 1/4: Custom malloc (Free List)
**Topics:** Capstone: malloc  
**Difficulty:** ★★★  
**Estimated Time:** 60-120 min

**Context:**  
Implementing malloc teaches you heap management. This is a classic systems project, like Python's pymalloc.

**Problem:**  
CAPSTONE Day 1/4: Custom malloc (Free List): Build custom malloc using free list. Implement: first-fit, split if large, coalesce on free, sbrk/mmap backend, realloc handling, thread-safety with mutex, tests for fragmentation.

**Starter Code:**  
#include <unistd.h>
#include <stddef.h>
typedef struct Block { size_t size; struct Block *next; int free; } Block;
static Block *head=NULL;
void *my_malloc(size_t sz){ /* TODO */ return NULL; }
void my_free(void *p){ /* TODO */ }
int main(){ void *a=my_malloc(32); my_free(a); }


**Constraints & Follow-Up Questions to Think About:**  
- Free list vs bump vs buddy allocator?
- Fragmentation internal vs external?
- How to align to 16 bytes?

---

## Day 121: CAPSTONE Day 2/4: malloc - Coalescing & Splitting
**Topics:** Capstone: malloc  
**Difficulty:** ★★★  
**Estimated Time:** 60-120 min

**Context:**  
Implementing malloc teaches you heap management. This is a classic systems project, like Python's pymalloc.

**Problem:**  
CAPSTONE Day 2/4: malloc - Coalescing & Splitting: Build custom malloc using free list. Implement: first-fit, split if large, coalesce on free, sbrk/mmap backend, realloc handling, thread-safety with mutex, tests for fragmentation.

**Starter Code:**  
#include <unistd.h>
#include <stddef.h>
typedef struct Block { size_t size; struct Block *next; int free; } Block;
static Block *head=NULL;
void *my_malloc(size_t sz){ /* TODO */ return NULL; }
void my_free(void *p){ /* TODO */ }
int main(){ void *a=my_malloc(32); my_free(a); }


**Constraints & Follow-Up Questions to Think About:**  
- Free list vs bump vs buddy allocator?
- Fragmentation internal vs external?
- How to align to 16 bytes?

---

## Day 122: CAPSTONE Day 3/4: malloc - Realloc & Edge Cases
**Topics:** Capstone: malloc  
**Difficulty:** ★★★  
**Estimated Time:** 60-120 min

**Context:**  
Implementing malloc teaches you heap management. This is a classic systems project, like Python's pymalloc.

**Problem:**  
CAPSTONE Day 3/4: malloc - Realloc & Edge Cases: Build custom malloc using free list. Implement: first-fit, split if large, coalesce on free, sbrk/mmap backend, realloc handling, thread-safety with mutex, tests for fragmentation.

**Starter Code:**  
#include <unistd.h>
#include <stddef.h>
typedef struct Block { size_t size; struct Block *next; int free; } Block;
static Block *head=NULL;
void *my_malloc(size_t sz){ /* TODO */ return NULL; }
void my_free(void *p){ /* TODO */ }
int main(){ void *a=my_malloc(32); my_free(a); }


**Constraints & Follow-Up Questions to Think About:**  
- Free list vs bump vs buddy allocator?
- Fragmentation internal vs external?
- How to align to 16 bytes?

---

## Day 123: CAPSTONE Day 4/4: malloc - Thread-Safety & Test
**Topics:** Capstone: malloc  
**Difficulty:** ★★★  
**Estimated Time:** 60-120 min

**Context:**  
Implementing malloc teaches you heap management. This is a classic systems project, like Python's pymalloc.

**Problem:**  
CAPSTONE Day 4/4: malloc - Thread-Safety & Test: Build custom malloc using free list. Implement: first-fit, split if large, coalesce on free, sbrk/mmap backend, realloc handling, thread-safety with mutex, tests for fragmentation.

**Starter Code:**  
#include <unistd.h>
#include <stddef.h>
typedef struct Block { size_t size; struct Block *next; int free; } Block;
static Block *head=NULL;
void *my_malloc(size_t sz){ /* TODO */ return NULL; }
void my_free(void *p){ /* TODO */ }
int main(){ void *a=my_malloc(32); my_free(a); }


**Constraints & Follow-Up Questions to Think About:**  
- Free list vs bump vs buddy allocator?
- Fragmentation internal vs external?
- How to align to 16 bytes?

---

## Day 124: String Intern Pool
**Topics:** Strings, Hash table, Pool  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - String Intern Pool. Combines multiple concepts from your list.

**Problem:**  
Implement String Intern Pool from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: String Intern Pool
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 125: Zero-Copy Slice Type (ptr+len)
**Topics:** Pointers, Slices  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Zero-Copy Slice Type (ptr+len). Combines multiple concepts from your list.

**Problem:**  
Implement Zero-Copy Slice Type (ptr+len) from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Zero-Copy Slice Type (ptr+len)
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 126: Manual VTable: OOP in C
**Topics:** Function ptr, OOP, Structs  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Manual VTable: OOP in C. Combines multiple concepts from your list.

**Problem:**  
Implement Manual VTable: OOP in C from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Manual VTable: OOP in C
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 127: Bitfield vs Manual Masking
**Topics:** Bit fields, Bitwise  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Bitfield vs Manual Masking. Combines multiple concepts from your list.

**Problem:**  
Implement Bitfield vs Manual Masking from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Bitfield vs Manual Masking
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 128: Endian-Aware Serializer
**Topics:** Endianness, Serialization  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Endian-Aware Serializer. Combines multiple concepts from your list.

**Problem:**  
Implement Endian-Aware Serializer from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Endian-Aware Serializer
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 129: Double Linked List with Sentinel
**Topics:** Linked list, Sentinel  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Double Linked List with Sentinel. Combines multiple concepts from your list.

**Problem:**  
Implement Double Linked List with Sentinel from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Double Linked List with Sentinel
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 130: LRU Cache with Hash + List
**Topics:** Hash, List, LRU  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - LRU Cache with Hash + List. Combines multiple concepts from your list.

**Problem:**  
Implement LRU Cache with Hash + List from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: LRU Cache with Hash + List
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 131: Radix Sort with Bitwise Partition
**Topics:** Sorting, Bitwise  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Radix Sort with Bitwise Partition. Combines multiple concepts from your list.

**Problem:**  
Implement Radix Sort with Bitwise Partition from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Radix Sort with Bitwise Partition
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 132: Varint Encoding (Protobuf Style)
**Topics:** Number rep, Encoding  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Varint Encoding (Protobuf Style). Combines multiple concepts from your list.

**Problem:**  
Implement Varint Encoding (Protobuf Style) from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Varint Encoding (Protobuf Style)
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 133: Deep Recursion & Stack Size (getrlimit)
**Topics:** Recursion, Stack  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Deep Recursion & Stack Size (getrlimit). Combines multiple concepts from your list.

**Problem:**  
Implement Deep Recursion & Stack Size (getrlimit) from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Deep Recursion & Stack Size (getrlimit)
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 134: Heap Spray Detection Simulation
**Topics:** Memory, Security  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Heap Spray Detection Simulation. Combines multiple concepts from your list.

**Problem:**  
Implement Heap Spray Detection Simulation from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Heap Spray Detection Simulation
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 135: File Locking: flock vs fcntl
**Topics:** File I/O, Locking  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - File Locking: flock vs fcntl. Combines multiple concepts from your list.

**Problem:**  
Implement File Locking: flock vs fcntl from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: File Locking: flock vs fcntl
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 136: mmap() as Allocator Backend
**Topics:** mmap, Allocator  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - mmap() as Allocator Backend. Combines multiple concepts from your list.

**Problem:**  
Implement mmap() as Allocator Backend from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: mmap() as Allocator Backend
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 137: TCP Half-Close & Shutdown
**Topics:** TCP, Sockets  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Network servers need concurrency + robustness. Python's socketserver hides details. Build it in C.

**Problem:**  
TCP Half-Close & Shutdown: Build multi-threaded TCP echo server: accept loop, spawn pthread per client (or thread pool), handle partial read/write, graceful shutdown via signal, stats with atomic counter. Client: handle reconnection.

**Starter Code:**  
#include <pthread.h>
#include <netinet/in.h>
#include <unistd.h>
void *client_handler(void *fd_ptr){ int fd=*(int*)fd_ptr; char buf[1024]; /* echo */ return NULL; }
int main(){ int srv=socket(AF_INET,SOCK_STREAM,0); /* bind listen accept */ }


**Constraints & Follow-Up Questions to Think About:**  
- Thread-per-client vs thread pool vs epoll?
- What is TIME_WAIT? SO_REUSEADDR?
- How to handle slowloris?

---

## Day 138: pthread Cleanup Handlers
**Topics:** Threads, Cleanup  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - pthread Cleanup Handlers. Combines multiple concepts from your list.

**Problem:**  
Implement pthread Cleanup Handlers from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: pthread Cleanup Handlers
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 139: Condition Variable Spurious Wakeup Demo
**Topics:** Condvar, Threads  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Condition Variable Spurious Wakeup Demo. Combines multiple concepts from your list.

**Problem:**  
Implement Condition Variable Spurious Wakeup Demo from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Condition Variable Spurious Wakeup Demo
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 140: Barrier Implementation
**Topics:** Concurrency, Barrier  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Barrier Implementation. Combines multiple concepts from your list.

**Problem:**  
Implement Barrier Implementation from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Barrier Implementation
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 141: Signal Safe Logger
**Topics:** Signals, async-safe  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Signal Safe Logger. Combines multiple concepts from your list.

**Problem:**  
Implement Signal Safe Logger from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Signal Safe Logger
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 142: Mini Make: Dependency Graph
**Topics:** Compilation, Graph  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Mini Make: Dependency Graph. Combines multiple concepts from your list.

**Problem:**  
Implement Mini Make: Dependency Graph from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Mini Make: Dependency Graph
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 143: Inspect ELF: .text .rodata .bss
**Topics:** ELF, Binaries  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Inspect ELF: .text .rodata .bss. Combines multiple concepts from your list.

**Problem:**  
Implement Inspect ELF: .text .rodata .bss from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Inspect ELF: .text .rodata .bss
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 144: Timing Attack Resistant memcmp
**Topics:** Timing, Security, volatile  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Timing Attack Resistant memcmp. Combines multiple concepts from your list.

**Problem:**  
Implement Timing Attack Resistant memcmp from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Timing Attack Resistant memcmp
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 145: CAPSTONE Day 1/2: Multi-Threaded TCP Echo Server
**Topics:** Capstone: TCP MT  
**Difficulty:** ★★★  
**Estimated Time:** 60-120 min

**Context:**  
Network servers need concurrency + robustness. Python's socketserver hides details. Build it in C.

**Problem:**  
CAPSTONE Day 1/2: Multi-Threaded TCP Echo Server: Build multi-threaded TCP echo server: accept loop, spawn pthread per client (or thread pool), handle partial read/write, graceful shutdown via signal, stats with atomic counter. Client: handle reconnection.

**Starter Code:**  
#include <pthread.h>
#include <netinet/in.h>
#include <unistd.h>
void *client_handler(void *fd_ptr){ int fd=*(int*)fd_ptr; char buf[1024]; /* echo */ return NULL; }
int main(){ int srv=socket(AF_INET,SOCK_STREAM,0); /* bind listen accept */ }


**Constraints & Follow-Up Questions to Think About:**  
- Thread-per-client vs thread pool vs epoll?
- What is TIME_WAIT? SO_REUSEADDR?
- How to handle slowloris?

---

## Day 146: CAPSTONE Day 2/2: MT Echo Server - Graceful Shutdown & Stats
**Topics:** Capstone: TCP MT  
**Difficulty:** ★★★  
**Estimated Time:** 60-120 min

**Context:**  
Advanced low-level puzzle - CAPSTONE Day 2/2: MT Echo Server - Graceful Shutdown & Stats. Combines multiple concepts from your list.

**Problem:**  
Implement CAPSTONE Day 2/2: MT Echo Server - Graceful Shutdown & Stats from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: CAPSTONE Day 2/2: MT Echo Server - Graceful Shutdown & Stats
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 147: Write Your Own assert() & Diagnostics
**Topics:** Macros, Debugging  
**Difficulty:** ★☆☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Write Your Own assert() & Diagnostics. Combines multiple concepts from your list.

**Problem:**  
Implement Write Your Own assert() & Diagnostics from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Write Your Own assert() & Diagnostics
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 148: Const Correctness & Pointer to Const Hell
**Topics:** const, Pointers  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Const Correctness & Pointer to Const Hell. Combines multiple concepts from your list.

**Problem:**  
Implement Const Correctness & Pointer to Const Hell from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Const Correctness & Pointer to Const Hell
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 149: Flexible Array Members & Struct Hack
**Topics:** Structs, Flexible array  
**Difficulty:** ★★☆  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - Flexible Array Members & Struct Hack. Combines multiple concepts from your list.

**Problem:**  
Implement Flexible Array Members & Struct Hack from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: Flexible Array Members & Struct Hack
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

## Day 150: The Ultimate: Python's list in C - PyObject-ish System
**Topics:** Grand Finale, All topics  
**Difficulty:** ★★★  
**Estimated Time:** 20-45 min

**Context:**  
Advanced low-level puzzle - The Ultimate: Python's list in C - PyObject-ish System. Combines multiple concepts from your list.

**Problem:**  
Implement The Ultimate: Python's list in C - PyObject-ish System from scratch, without stdlib helpers where noted. Write tests, measure performance, and document memory layout. Focus on correctness under edge cases (OOM, overflow, concurrency).

**Starter Code:**  
#include <stdio.h>
#include <stdlib.h>
// TODO: The Ultimate: Python's list in C - PyObject-ish System
int main(){ return 0; }


**Constraints & Follow-Up Questions to Think About:**  
- What tradeoffs did you make?
- How would you test with sanitizers?
- Python equivalent vs C complexity?

---

