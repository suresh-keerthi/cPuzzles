# 150 Days of Low-Level C

A daily puzzle series to keep your systems knowledge sharp while you live in Python.

Python hides the machine from you: garbage collection, arbitrary-precision ints,
`bytes`/`struct` for binary data, GIL-protected threads, no visible stack/heap.
These puzzles drag all of that back into the open.

## How to use this

- One puzzle per day. Don't skip the **Think about** questions — they are the real content.
- Recommended toolchain: `gcc -Wall -Wextra -Wpedantic -std=c11 -g -O2`.
- Debug harness: `-fsanitize=address,undefined` (ASan/UBSan). Use it *before* you claim a bug is fixed.
- On Linux, keep `valgrind`, `strace`, `perf`, `objdump`, `nm`, `readelf` nearby.
- The goal is not "make it compile". The goal is to *predict* the machine's behavior, then confirm it.

## Rules of engagement

1. **No `#include <string.h>`** unless a puzzle explicitly allows it.
2. Pointer arithmetic and raw bytes are the default; indexing is a luxury.
3. Every memory bug you are asked to "find" must be confirmed with ASan or Valgrind.
4. Write down your *prediction* of addresses, sizes, and output before you run.
5. A puzzle is "done" when you can explain why a wrong answer is wrong.

---

# Part A — Language-Level C

## 1. Pointers & Addresses

---

### Day 1: The Byte Swapper & Memory Layout

**Concepts:** `void *`, pointer arithmetic, endianness, strict aliasing.

**Context:** In Python, `int.to_bytes(4, 'little')` or `struct.pack` handles byte order for you and ints are arbitrary precision. In C, a `uint32_t` is 4 concrete bytes at a concrete address, and which byte is "first" is an architectural fact.

**Problem:** Write `void reverse_bytes(void *ptr, size_t size)` that reverses the raw bytes of any object in place, using no heap allocation and no library string functions.

Exercise it on:
- a `uint32_t` = `0xAABBCCDD`
- a `double`
- a small struct

```c
#include <stdio.h>
#include <stdint.h>

void reverse_bytes(void *ptr, size_t size) {
    /* TODO: operate on unsigned char * , swap from both ends */
}

int main(void) {
    uint32_t val = 0xAABBCCDD;
    printf("Original: 0x%08X\n", val);
    reverse_bytes(&val, sizeof val);
    printf("Reversed: 0x%08X\n", val);
    /* little-endian expected: 0xDDCCBBAA */
    return 0;
}
```

**Think about:**
- Why must you cast `void *` before pointer arithmetic in standard C? (GNU allows `void*+1`; ISO does not.)
- Why is `unsigned char *` the correct type for viewing object representation — not `char`, not `int8_t`?
- Would this swap produce the same numeric result on a big-endian machine? What does "reversed" mean there?

---

### Day 2: No Brackets Allowed

**Concepts:** pointer arithmetic, array decay, `sizeof` traps.

**Context:** In Python a list knows its length. A C array passed to a function decays to a pointer and forgets it. `a[i]` is literally `*(a + i)`.

**Problem:** Implement these with **zero** `[]` operators:
```c
int   nth(const int *a, size_t n, size_t i);     /* return a[i] */
void  set_nth(int *a, size_t n, size_t i, int v);
int   sum(const int *a, size_t n);
int  *find(const int *a, size_t n, int needle);  /* pointer to element or NULL */
```
Then write `last(const int *a, size_t n)` returning a pointer to the last element, and explain what `&a[5]` on a 5-element array actually means (one-past-the-end is legal to *form*, illegal to *dereference*).

**Think about:**
- Why does `sizeof(arr)/sizeof(arr[0])` work in `main` but silently lie inside a function?
- Is `a[-1]` defined if `a` is not the start of its object? When is forming `p-1` UB?

---

### Day 3: Command-Line Surgery (`char **argv`)

**Concepts:** pointers to pointers, `argc`/`argv`, in-place mutation, `NULL` termination.

**Context:** `sys.argv` is a mutable Python list. `argv` is an array of `char *` terminated by a `NULL` pointer; `argv[argc]` is guaranteed `NULL`.

**Problem:** Write a program that, without allocating new strings (you may permute pointers):
1. Reverses the argument order (keep `argv[0]` first).
2. Removes every argument starting with `-`.
3. Prints the result using `char **` walking, never `argv[i]`.

Then add `char **find_flag(char **argv, const char *name)` returning a pointer into the array.

**Think about:**
- Why is the type `char **argv`, not `char *argv[]`? Is there a difference in a parameter?
- Can you modify the *characters* of `argv` strings? (Technically modifying the strings is UB by the standard; explain why POSIX-first, but be honest about it.)

---

### Day 4: Function Pointers & the Dispatch Table

**Concepts:** function pointers, callbacks, vtable-style dispatch.

**Context:** Python has first-class functions and dict dispatch. C gives you a pointer to code.

**Problem:** Build a tiny calculator:
```c
typedef int (*binop)(int, int);
struct entry { const char *name; binop fn; };
typedef struct entry table[];
```
Register `+ - * /` with wrappers that handle division by zero (return a sentinel). Write `binop lookup(const table *t, size_t n, const char *name)`. Dispatch from user input.

**Follow-up:** implement `map(int *a, size_t n, int (*f)(int))` and `reduce(int *a, size_t n, int (*f)(int,int), int init)`.

**Think about:**
- What is the difference between `int (*f)(int)` and `int *f(int)`?
- Why can't you portably cast a function pointer to `void *` and back? (POSIX says you can for `dlsym`; ISO C says function and object pointers may differ.)

---

### Day 5: Generic Swap and Generic Reverse (`void *`)

**Concepts:** `void *`, `memcpy` semantics hand-rolled, size-aware algorithms.

**Context:** Python's generic code is duck-typed. C's is byte-addressed with an explicit element size.

**Problem:** Implement, with no `<string.h>`:
```c
void gswap(void *a, void *b, size_t size);
void greverse(void *base, size_t count, size_t elem_size);
void gcopy(void *dst, const void *src, size_t nbytes); /* your own memcpy */
int  gcmp(const void *a, const void *b, size_t nbytes);/* your own memcmp */
```
`gswap` must work for sizes not divisible by the natural word size (e.g. `elem_size = 3`).

**Think about:**
- Why can't you `*a = *b` on `void *`? What does `*a` mean for an unknown type?
- Why does `memcpy` forbid overlapping regions while `memmove` allows them? Implement a safe overlap-aware copy.

---

### Day 6: `qsort` From Scratch

**Concepts:** function pointers, `void *` arithmetic, callbacks, instability.

**Context:** `sorted(key=...)` in Python. In C you pass a comparator and an element size.

**Problem:** Implement `my_qsort(void *base, size_t n, size_t size, int (*cmp)(const void*, const void*))` using Lomuto or Hoare partitioning. It must sort an array of `int` and an array of `struct { char name[16]; int age; }`.

Then implement `bsearch_generic` on top of it and prove a 3-element search using only `cmp`.

**Think about:**
- Is `qsort` stable? Does that matter for your struct sort? How would you make it stable?
- Why does the comparator return `int`, not `bool`? What do negative/zero/positive encode?

---

### Day 7: The Dangling Pointer Lab

**Concepts:** lifetime, use-after-free, stack vs heap validity.

**Context:** Python's GC keeps objects alive while referenced. In C, nothing does.

**Problem:** Given the buggy code below, predict the output *before* running, then run under ASan (or Valgrind). Explain each bug:

```c
#include <stdio.h>
#include <stdlib.h>
int *make_array(size_t n) {
    int local[10];
    for (size_t i = 0; i < n; i++) local[i] = (int)i;
    return local;               /* bug 1 */
}
int main(void) {
    int *p = make_array(10);
    printf("%d\n", p[0]);
    int *q = malloc(sizeof(int));
    *q = 42;
    free(q);
    printf("%d\n", *q);         /* bug 2 */
    free(q);                    /* bug 3 */
    return 0;
}
```

**Fix it** two ways: returning a `malloc` buffer, and taking an output parameter.

**Think about:**
- Why might bug 1 "work" anyway? Why is "it printed the right answer" not evidence?
- What does ASan report that `printf` never will?

---

### Day 8: A Tour of an Object's Bytes

**Concepts:** object representation, pointer casts, inspection.

**Context:** `pahole`/`objdump` in Python-land is a mystery; here you do it by hand.

**Problem:** Write `void dump(const void *p, size_t n)` printing bytes as `xx xx xx ...` and printable ASCII. Then dump:
- an `int`, a `double`, a `char[8]`
- a struct with mixed field types
- the bytes of a function pointer

Use a `union { struct; unsigned char raw[sizeof(struct)]; }` to inspect without violating strict aliasing.

**Think about:**
- Which bytes of a little-endian `int` hold the least significant part?
- Why is poking a struct through a `char[16]` union legal, but through an `int *` often UB?

---

### Day 9: The `const` Matrix

**Concepts:** const-correctness, top-level vs pointed-to const.

**Context:** Python has no compile-time mutability contract; C's `const` is a real part of the type.

**Problem:** Fill in a table: for each declaration, say whether the *pointer* is mutable, the *pointee* is mutable, and assign valid/invalid examples.

```c
const int *p;          /* ? */
int * const p;         /* ? */
const int * const p;   /* ? */
int const * p;         /* ? */
```
Then write a function `size_t count_if(const int *a, size_t n, int (*pred)(int))` and explain why the array parameter must be `const int *` to accept both mutable and const arrays.

**Think about:**
- Can you pass `char *` to a function taking `const char *`? Can you do the reverse without a cast warning?
- What is "const poisoning" and how does it propagate through a call graph?

---

### Day 10: `offsetof` and `container_of`

**Concepts:** member offsets, pointer subtraction, intrusive data structures.

**Context:** The Linux kernel's `container_of` recovers a struct from a pointer to one of its members. This is how intrusive linked lists avoid a separate node allocation.

**Problem:** Implement:
```c
#define my_offsetof(type, member) ((size_t)&((type *)0)->member)
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - my_offsetof(type, member)))
```
Build a struct with 3+ members, take a pointer to the middle one, and recover the whole struct. Verify with `printf` that the recovered pointer equals the original.

**Think about:**
- Is taking `&((type*)0)->member` technically UB? Why do compilers still make it work? (C23/C++ allow it.)
- Why do you subtract from a `char *` rather than the member pointer type?

---

## 2. Manual Memory Management

---

### Day 11: Your Own Dynamic Array (`int_vector`)

**Concepts:** `malloc`/`realloc`/`free`, amortized growth, capacity vs size.

**Context:** Python lists grow automatically. Here you own the growth policy.

**Problem:** Implement:
```c
typedef struct { int *data; size_t size, cap; } ivec;
int  ivec_init(ivec *v, size_t cap);
int  ivec_push(ivec *v, int x);      /* grow x2, return 0/-1 */
int  ivec_pop(ivec *v, int *out);
void ivec_free(ivec *v);
int  ivec_reserve(ivec *v, size_t need);
```
Make `push` return failure on allocation error without corrupting state. Prove no leaks with ASan/Valgrind across 1,000,000 pushes.

**Think about:**
- Why geometric (×2) growth, not +1? What is the amortized cost per push?
- What happens to `v->data` if `realloc` fails? Why is `v->data = realloc(v->data, ...)` a classic leak?

---

### Day 12: Growable String Builder

**Concepts:** capacity management, `%` formatting by hand, null termination.

**Context:** Python's `''.join(...)` is O(n). Naive `strcat` in a loop is O(n²).

**Problem:** Build `sbuf` with `append`, `appendc`, `append_int`, `cstr()` and `free()`. Test appending 100k chars and compare total bytes written vs a naive `strcat` loop. Then make it so `cstr()` never reallocates (returns a stable buffer).

**Think about:**
- Where exactly does the O(n²) come from in repeated `strcat`?
- Who owns the returned `cstr()` buffer? How do you make the ownership obvious in the API?

---

### Day 13: Find the Leaks

**Concepts:** leak detection, ownership, error paths.

**Context:** Python frees for you. Here, every early return is a potential leak.

**Problem:** The following parses a config, but leaks on several paths. Find them all, then rewrite with a single cleanup label (`goto cleanup`):

```c
#define LINES 4
char **load(void) {
    char **lines = malloc(LINES * sizeof *lines);
    for (int i = 0; i < LINES; i++) {
        lines[i] = malloc(128);
        if (!lines[i]) return NULL;          /* leak A */
        if (i == 2) return NULL;             /* leak B */
    }
    return lines;
}
```
Then free everything correctly. Confirm with Valgrind `--leak-check=full --show-leak-kinds=all`.

**Think about:**
- Why is the `goto cleanup` pattern preferred over nested `if`s in kernel-style C?
- What is the difference between "definitely lost", "indirectly lost", and "still reachable" in Valgrind?

---

### Day 14: Fixed-Size Memory Pool

**Concepts:** bump allocator, free list, O(1) alloc/free, locality.

**Context:** Python allocates per-object. Games/kernels pre-allocate a pool to avoid fragmentation and allocator overhead.

**Problem:** Implement a pool of N fixed-size blocks:
```c
typedef struct pool pool;
pool *pool_create(size_t block_size, size_t nblocks);
void *pool_alloc(pool *p);      /* O(1) */
void  pool_free(pool *p, void *b);
void  pool_destroy(pool *p);
```
Use a free list threaded through the free blocks themselves (no extra metadata array). Verify no double-free when ASan is enabled by refusing to hand out an already-free block.

**Think about:**
- Why can free blocks store the `next` pointer inside themselves?
- What is external vs internal fragmentation? Does a pool reduce or increase each?

---

### Day 15: A Tiny `malloc` (Free-List Allocator)

**Concepts:** headers, splitting, coalescing, alignment.

**Context:** This is how `malloc` actually works under the hood.

**Problem:** Implement `xmalloc`/`xfree` over one big `mmap`'d or `malloc`'d arena. Each block carries a header `{size_t size; int free; struct block *next;}`. Support:
- first-fit search
- splitting oversized blocks
- coalescing adjacent free blocks on free
- 16-byte alignment of returned pointers

Track fragmentation statistics.

**Think about:**
- Why must returned pointers be aligned? What breaks on ARM if they aren't?
- Why is coalescing easier with a doubly-linked free list (or boundary tags)?

---

### Day 16: Double-Free Detector

**Concepts:** canaries, free-list membership, defensive checks.

**Context:** Double free is one of the most exploited C bugs (`tcache` poisoning). Python's GC makes it impossible from user code.

**Problem:** Extend Day 15's allocator (or wrap the system one) so that:
- `xfree(NULL)` is a no-op (required by the standard)
- freeing an unknown pointer is detected
- double free is detected and reported, not silently corrupting

Add a magic word written into the header on allocation and poisoned on free.

**Think about:**
- Why does `free(NULL)` being legal matter in cleanup code?
- What is a use-after-free that *passes* a naive canary check?

---

### Day 17: Buffer Overflow Canary Lab

**Concepts:** stack smashing, canaries, `-fstack-protector`.

**Context:** `-fstack-protector` inserts a canary between locals and the saved return address.

**Problem:** Write a function with a `char buf[8]` filled by an unchecked copy. Call it with 4, 8, 12, 16 bytes. Observe when the canary trips (`*** stack smashing detected ***`). Then:
1. Inspect the disassembly with `objdump -d` and find the canary load/compare.
2. Fix the code with `snprintf` / bounded copy.
3. Repeat with `-fno-stack-protector` and explain the difference.

**Think about:**
- Why is a canary placed *between* locals and the return address?
- Why is a canary a mitigation, not a fix?

---

### Day 18: Arena / Region Allocator

**Concepts:** bulk allocation, bulk free, lifetime scopes.

**Context:** Compilers and interpreters allocate a whole phase's data in one arena and free it all at once — far faster than per-object `free`.

**Problem:** Implement an arena that hands out pointers via bump allocation, supports `arena_reset()` (free everything, keep capacity), and takes optional destructor callbacks for non-trivial objects. Build a tiny AST (binary expression tree) entirely from the arena, evaluate it, then reset.

**Think about:**
- Why is an arena a bad fit for long-lived, individually freed objects?
- What is the alignment requirement of a bump pointer, and how do you enforce it?

---

### Day 19: Reference Counting Smart Pointer

**Concepts:** ownership, `shared_ptr`-style semantics, cycles.

**Context:** CPython uses refcounting plus a cycle collector because refcounting alone leaks cycles.

**Problem:** Implement:
```c
typedef struct rc { void *obj; int count; void (*dtor)(void *); } rc;
rc  *rc_new(void *obj, void (*dtor)(void *));
void rc_retain(rc *r);
void rc_release(rc *r);   /* free obj when count hits 0 */
```
Use it to manage a shared buffer. Then construct a *cycle* (A holds B, B holds A) and demonstrate the leak. Propose a fix.

**Think about:**
- Why is refcounting not thread-safe by default? (Non-atomic increment races.)
- Why can't plain refcounting collect cycles?

---

### Day 20: `realloc` Semantics Deep Dive

**Concepts:** realloc failure, in-place vs move, aliasing.

**Context:** `realloc` may return the same pointer or a new one, and may fail leaving the original intact.

**Problem:** Write `grow_and_report(int *p, size_t newsize)` that prints whether the pointer moved. Loop growing from 1 to 100MB and record moves. Then implement a safe wrapper:
```c
void *xrealloc(void *p, size_t n); /* preserves p on failure */
```
Explain why the naive `p = realloc(p, n)` loses the old block on failure.

**Think about:**
- Under what conditions can `realloc` extend in place?
- What does `realloc(p, 0)` do per the standard vs common libc behavior?

---

### Day 21: 2D Matrices — Two Layouts

**Concepts:** contiguous vs array-of-pointers, cache behavior, cleanup.

**Context:** NumPy arrays are contiguous (C-order by default). Python lists-of-lists are arrays of pointers.

**Problem:** Implement both:
```c
/* A: contiguous row-major */
double *mat_flat(size_t r, size_t c);
#define AT(m, c, i, j) ((m)[(i)*(c) + (j)])

/* B: pointer array */
double **mat_rows(size_t r, size_t c);
```
Fill both with the same data and benchmark multiplication by a vector. Explain the cache difference. Free both correctly.

**Think about:**
- How many `free` calls does each layout need?
- Which layout lets you pass the whole matrix to a BLAS-like function as one pointer?

---

### Day 22: Aligned Allocations

**Concepts:** alignment, `aligned_alloc`/`posix_memalign`, SIMD.

**Context:** SSE/AVX loads may require 16/32-byte alignment. A misaligned pointer can crash or slow down.

**Problem:** Implement `void *aligned_xalloc(size_t align, size_t size)` without `aligned_alloc` (round up, stash the original pointer just before the aligned address, return aligned). Implement matching free. Test with alignment 1, 8, 16, 32, 64 and verify `(uintptr_t)p % align == 0`.

**Think about:**
- Why must `align` be a power of two?
- Where do you store the original pointer without wasting a full header per allocation?

---

## 3. Bitwise Operations

---

### Day 23: The Four Basic Bit Ops

**Concepts:** masks, shifts, in-place mutation.

**Context:** Python ints are arbitrary precision and bit ops just work; C fixes the width and makes overflow/UB your problem.

**Problem:** Implement:
```c
void set_bit(uint32_t *w, unsigned b);
void clear_bit(uint32_t *w, unsigned b);
void toggle_bit(uint32_t *w, unsigned b);
int  test_bit(uint32_t w, unsigned b);
```
Then extend to a 64-bit word and an arbitrary-length bit array (`unsigned char *bits, size_t nbits`).

**Think about:**
- Why is `1 << 31` UB-ish for signed `int`? What is `1u << 31`?
- Why `x & (1u << b)` and not `x & 1 << b`?

---

### Day 24: Hardware-Style Flag Register

**Concepts:** bitmasks, multi-bit fields, decoding.

**Context:** CPU status registers pack many independent flags into one word. Device registers too.

**Problem:** Model a 32-bit register:
- bit 0 = CARRY, bit 1 = ZERO, bit 2 = SIGN, bit 3 = OVERFLOW
- bits 8–11 = a 4-bit mode (0–15)
- bits 16–23 = an 8-bit opcode

Write `set_flag`, `get_mode`, `set_opcode` (masking), `decode` (print all fields). Then implement an ALU that computes `add` and sets C/Z/S/V correctly for signed and unsigned 8-bit addition.

**Think about:**
- How do you update a multi-bit field without clobbering neighbors? (clear-mask then OR.)
- Signed overflow vs unsigned carry — how do they differ?

---

### Day 25: Swap Without a Temp / XOR Tricks

**Concepts:** XOR properties, sequence-point pitfalls.

**Context:** A classic interview trick that is now discouraged.

**Problem:** Implement `swap_xor(int *a, int *b)` without a temporary. Prove it works with a loop of random pairs. Then explain:
- what happens if `a == b`
- what happens if `*a` and `*b` are the *same object*
- why the XOR trick is worse than a temp on modern CPUs

**Think about:**
- Why is `self ^= self` zero, and why does that break the in-place swap?
- Does the compiler already optimize a temp swap away anyway?

---

### Day 26: Population Count — Three Ways

**Concepts:** bit tricks, Kernighan, SWAR, lookup tables.

**Context:** `int.bit_count()` in Python 3.10+ is one call. Here you build it.

**Problem:** Implement three popcounts for `uint64_t`:
1. naive shift-and-test
2. Kernighan (`x &= x-1`)
3. SWAR / parallel bit count with masks

Benchmark all three over 100M random values. Then add a 256-entry lookup table version.

**Think about:**
- How many iterations does Kernighan run for `x=0xF0F0`?
- Why does `x & (x-1)` clear the lowest set bit?
- Why is `__builtin_popcountll` usually fastest?

---

### Day 27: Endianness Detection & Conversion

**Concepts:** byte order, `htonl`/`ntohl`, union inspection.

**Context:** Python's `sys.byteorder` and `int.to_bytes`. Network protocols demand a fixed order.

**Problem:** Detect endianness **at runtime** without `<endian.h>` (use a union or a `uint16_t` trick). Then implement `uint32_t bswap32(uint32_t)` and `uint64_t bswap64(uint64_t)` with shifts/masks, and portability wrappers `to_be`/`from_be` that are correct on both little- and big-endian hosts.

Test by round-tripping values and by comparing against `__builtin_bswap32`.

**Think about:**
- Why is network byte order big-endian?
- Why can you not just `memcpy` a `float` and call it a network float?

---

### Day 28: Reverse the Bits

**Concepts:** bit reversal, masks, divide-and-conquer.

**Context:** FFT bit-reversal permutation, CRC reflections.

**Problem:** Implement `uint32_t reverse_bits(uint32_t)` two ways: naive loop and the SWAR 5-step mask method. Verify against a brute-force reference on random inputs.

**Think about:**
- Why does reversing bits also reverse endianness *for a value*, but not for memory?
- How many log₂ steps does the SWAR method need for a 64-bit word?

---

### Day 29: Lowest Set Bit and Powers of Two

**Concepts:** `x & -x`, two's complement, de Bruijn sequences.

**Context:** Used in schedulers (find next free slot), memory allocators (size classes).

**Problem:** Implement:
```c
uint64_t lowest_bit(uint64_t x);   /* x & -x */
int      is_pow2(uint64_t x);      /* x && !(x & (x-1)) */
int      next_pow2(uint64_t x);    /* round up */
unsigned bit_index(uint64_t x);    /* index of lowest set bit, no loops */
```
For `bit_index`, use a de Bruijn multiply-and-lookup table.

**Think about:**
- Why does `x & -x` isolate the lowest set bit on two's-complement machines?
- How does the de Bruijn table turn a bit pattern into an index in O(1)?

---

### Day 30: Rotations and Circular Shifts

**Concepts:** rotate vs shift, UB when shifting by width.

**Context:** Hash functions and ciphers (e.g. `rotl32` in ChaCha) rely on rotations.

**Problem:** Implement `rotl32`, `rotr32`, `rotl64`, `rotr64`. Handle `n == 0` and `n %= 32/64`. Then implement a small toy cipher that uses rotations, XOR, and addition (an ARX design) and prove `decrypt(encrypt(x)) == x`.

**Think about:**
- Why is `x << 32` UB for a 32-bit `x`? How do you avoid it in a generic rotate?
- Why do ARX ciphers avoid lookup tables (think constant-time / cache attacks)?

---

### Day 31: Manual Bit Packing vs Bit Fields

**Concepts:** bit fields, packing, portability, `#pragma pack`.

**Context:** Wire formats pack many small fields into one byte. C bit fields *look* convenient but their layout is implementation-defined.

**Problem:** Define a 24-bit color as:
1. bit fields `struct { unsigned r:8, g:8, b:8; }`
2. manual `uint32_t` with shifts

Serialize both to 3 bytes little- and big-endian. Compare byte output; explain any mismatch. Then pack a struct of `uint8_t`s into one `uint32_t` via shifts and unpack it.

**Think about:**
- Why is bit-field bit order implementation-defined?
- When is manual packing the only portable choice?

---

### Day 32: N-Queens with Bitmasks

**Concepts:** bitmasks as sets, recursion, constraint propagation.

**Context:** Python's `set` is easy; a 64-bit integer can represent a whole board's constraints.

**Problem:** Solve N-Queens (N ≤ 16) using three `uint32_t` masks for columns, diagonals (`<<`), and anti-diagonals (`>>`). Count solutions. Compare runtime against a naive array-backed backtracker at N=12.

**Think about:**
- How does `col | diag | anti` let you compute available squares in one expression?
- Why do diagonal masks shift on every recursion level?

---

## 4. Structs, Unions & Memory Layout

---

### Day 33: `sizeof` Surprises

**Concepts:** padding, alignment, field ordering.

**Context:** Python objects have a `__dict__` and refcount; C structs are just laid out bytes with holes.

**Problem:** For each struct below, predict `sizeof` and each member offset **before** running. Then print with `offsetof`. Reorder members to minimize size and state the savings.

```c
struct A { char a; int b; char c; };
struct B { char a; char c; int b; };
struct C { double d; char c; int i; short s; };
struct D { char x; struct { int a; char b; } inner; char y; };
```

**Think about:**
- Where exactly do padding holes appear, and why can't the compiler just "pack" by default?
- Does trailing padding exist? Why must it for arrays?

---

### Day 34: The Alignment Optimizer

**Concepts:** padding minimization, sorting by alignment.

**Context:** Large structs in arrays pay for every padding byte. Reducing size improves cache hits.

**Problem:** Write a tool that, given a list of `(name, size, align)` fields, computes a minimal-padding ordering (sort by descending alignment). Emulate a struct of `char, int, char, double, short, char` and compute size before/after. Then verify by declaring the real reordered struct and printing `sizeof`.

**Think about:**
- Why does descending alignment order minimize padding in practice?
- Are there cases where reordering changes semantics? (Bit fields, unions, ABI stability.)

---

### Day 35: Type Punning with Unions

**Concepts:** unions, `memcpy` punning, strict aliasing.

**Context:** Python uses `struct.unpack` to reinterpret bits. C's blessed way is `memcpy` or a union (implementation-defined).

**Problem:** Implement:
```c
float  u32_as_float(uint32_t bits);
uint32_t float_as_u32(float f);
```
via a union. Then inspect the fields of a `float`: sign, exponent (8 bits), mantissa (23 bits). Print them for `1.0f`, `-0.0f`, `0.5f`, `NaN`, `+inf`. Verify against `memcpy`-based punning.

**Think about:**
- Why is union punning implementation-defined but `memcpy` punning well-defined?
- How do you detect `NaN` using only bits (exponent all 1s, mantissa nonzero)?

---

### Day 36: Tagged Union (Variant Type)

**Concepts:** tagged unions, discriminants, safe accessors.

**Context:** Python's dynamic typing is a tagged union under the hood. Rust's `enum` is a type-safe tagged union.

**Problem:** Build a `Value` type:
```c
enum Tag { VAL_INT, VAL_DOUBLE, VAL_STR, VAL_NONE };
struct Value {
    enum Tag tag;
    union { long i; double d; char *s; } as;
};
```
Write `Value make_int(...)`, `make_double`, `make_str`, `make_none`, a safe `print_value`, and a `Value add(Value, Value)` with numeric promotion. Handle mismatched tags gracefully.

**Think about:**
- Why is reading the wrong union member UB but reading `.tag` always safe?
- How much memory does this use vs the largest member plus the tag? Why?

---

### Day 37: Nested Structs & Interior Pointers

**Concepts:** composition, pointer members, ownership.

**Context:** Python object graphs. In C, ownership of pointed-to memory must be explicit.

**Problem:** Model a `Person` that has a `Name { char first[16]; char last[16]; }` and a pointer to an `Address` it *does not own*. Write constructors/destructors and a function that prints the person without freeing the borrowed address. Then add an owned `char *nickname` and free it in the destructor.

**Think about:**
- How do you document "borrowed" vs "owned" pointers? (Naming, comments, `const`.)
- What happens on shallow copy of this struct? Why is that a double-free waiting to happen?

---

### Day 38: Serialize a Struct to Bytes

**Concepts:** layout, endianness, portability, versioning.

**Context:** Python's `struct.pack('<IHH', ...)`. C tells you exactly where fields are.

**Problem:** Define a packet `{ uint32_t id; uint16_t flags; uint16_t len; char payload[8]; }`. Write `pack`/`unpack` into a `uint8_t buf[]` using explicit big-endian field writes. Then add a version byte and a checksum. Prove `unpack(pack(x)) == x` for random inputs.

**Think about:**
- Why must you NOT just `memcpy` the struct to the wire?
- How would you evolve the format while remaining backward compatible?

---

### Day 39: Flexible Array Members

**Concepts:** struct hack, trailing arrays, one allocation.

**Context:** Python `array`/`bytes` are length-prefixed. C can put a variable-length payload at the end of a struct.

**Problem:** Implement:
```c
struct msg { size_t len; char data[]; };
struct msg *msg_new(const char *s, size_t n);
```
Allocate `sizeof(struct msg) + n` in one `malloc`. Write accessors and a destructor. Compare the pointer layout with the old `char data[1]` hack.

**Think about:**
- Why can't a flexible array member be the first or only member?
- Why is this one `malloc` better than a separate payload allocation?

---

### Day 40: Struct Embedding / Fake Inheritance

**Concepts:** struct embedding, upcasting via container_of, vtable.

**Context:** Linux kernel and GLib emulate OOP with C. Rust/C++ do inheritance natively.

**Problem:** Create `struct Shape { const struct ShapeVtbl *v; }`, `struct Circle { struct Shape base; double r; }`, `struct Rect { struct Shape base; double w, h; }`. Build a vtable with `area`, `name`, `destroy`. Write a `Shape *` array and dispatch virtually. Recover the derived type with `container_of`.

**Think about:**
- Why must the base struct be the *first* member for a plain cast to work?
- How does this compare to C++ virtual dispatch (vptr as a hidden first member)?

---

## 5. Strings Without stdlib

---

### Day 41: Reimplement `strlen`

**Concepts:** null termination, pointer walking, edge cases.

**Context:** Python strings carry a length. C strings are null-terminated, which the caller must respect.

**Problem:** Implement `my_strlen`, `my_strnlen` (bounded). Then implement a word-at-a-time strlen that reads 8 bytes at once using the "has zero byte" trick (`(x - 0x0101..) & ~x & 0x8080..`). Careful: it may read past the terminator — explain why that's technically UB but widely accepted.

**Think about:**
- Why is the word-at-a-time read potentially reading beyond the allocation?
- What is the difference between `strlen` and `strnlen` in terms of safety?

---

### Day 42: `strcpy` / `strncpy` / `strcpy_s`-ish

**Concepts:** bounded copy, truncation semantics, return values.

**Context:** `strncpy` does **not** always null-terminate — a classic source of bugs.

**Problem:** Implement:
- `my_strcpy(dst, src)` — copies including terminator
- `my_strncpy(dst, src, n)` — replicate the weird C semantics exactly
- `safe_copy(dst, cap, src)` — always null-terminates, returns bytes written

Then write a test that shows `strncpy` failing to terminate when `n <= strlen(src)`.

**Think about:**
- Why does `strncpy` zero-fill the rest, and why is that often wasteful?
- Why is `snprintf(dst, cap, "%s", src)` a common safe idiom?

---

### Day 43: `strcmp` / `strncmp` / Collation

**Concepts:** lexicographic compare, return sign, `unsigned char` casts.

**Context:** Python compares strings by Unicode code point. C compares bytes as `unsigned char`.

**Problem:** Implement `my_strcmp`, `my_strncmp`, `my_strcasecmp`. Then discuss: why must you cast to `unsigned char` before comparing? Write a test with bytes ≥ 0x80 to demonstrate the signed-char bug.

**Think about:**
- Why does `strcmp` return `int` and not the difference necessarily? Can it overflow?
- How does locale affect comparison, and why is that a security concern?

---

### Day 44: `strcat` / Safe Concatenation

**Concepts:** repeated scans, buffer bounds, O(n²).

**Context:** `strcat` rescans the destination every call.

**Problem:** Implement `my_strcat`, `my_strncat`, and `my_strlcat` (BSD-style, returns total length it tried to create, always terminates). Join an array of N strings into one buffer and show `strlcat` is safe while naive `strcat` overflows for large N.

**Think about:**
- Why is `strncat`'s `n` the *max bytes to append*, not the total buffer size? Why is that easy to misuse?
- How does tracking a running length avoid the repeated scan?

---

### Day 45: `strstr` / Substring Search

**Concepts:** naive search, KMP, Boyer–Moore intuition.

**Context:** Python's `in`/`.find()` is optimized in C. Build your own.

**Problem:** Implement naive `my_strstr`, then KMP with a failure table, then (stretch) Boyer–Moore–Horspool. Benchmark all three on a long haystack. Return a pointer to the first occurrence or `NULL`.

**Think about:**
- Why is the naive algorithm O(n·m) and KMP O(n+m)?
- How does KMP's failure function encode "what prefix of the pattern is also a suffix"?

---

### Day 46: In-Place Reverse, Trim, and Case

**Concepts:** two-pointer, whitespace semantics, in-place mutation.

**Context:** Python returns new strings; C mutates byte buffers.

**Problem:** Implement in place:
- `reverse(char *s)` and `reverse_range(s, i, j)`
- `trim(char *s)` (returns pointer to new start, moves content)
- `to_upper`, `to_lower` using only arithmetic (no `<ctype.h>`)
- `is_palindrome(const char *s)` ignoring case and non-alphanumerics

**Think about:**
- Why does `trim` returning a new start pointer sometimes not need to move memory?
- Why must `to_upper` guard against signed `char` (negative values to `toupper`)?

---

### Day 47: Tokenizer Without `strtok`

**Concepts:** state machines, thread safety, reentrancy.

**Context:** `strtok` uses hidden static state (not reentrant). Python's `str.split` returns fresh objects.

**Problem:** Implement a reentrant tokenizer:
```c
char *next_token(char **cursor, const char *delims);
```
It takes a `char **` so state lives with the caller. Tokenize a CSV-like line, handling empty fields. Then compare with `strtok_r`.

**Think about:**
- Why is `strtok` not thread-safe or reentrant?
- How do you represent "empty field" vs "no more tokens" in the return value?

---

### Day 48: `sprintf`-Lite

**Concepts:** varargs, format parsing, manual itoa.

**Context:** Python f-strings call into C formatting. Now you write one.

**Problem:** Implement `int my_snprintf(char *buf, size_t cap, const char *fmt, ...)` supporting `%d`, `%u`, `%x`, `%s`, `%c`, `%%`. Use `<stdarg.h>` (`va_start`/`va_arg`/`va_end`) and your own integer-to-string. Never write out of bounds.

**Think about:**
- Why is `va_arg` type-unsafe? What blows up if the caller passes `%d` but you read `va_arg(ap, double)`?
- Why must `va_end` always be called?

---

### Day 49: Base Conversion & `printf("%b")`

**Concepts:** itoa, buffer sizing, negative numbers.

**Context:** Python's `format(x, 'b')`. C has no `%b` (until C23 `printf`).

**Problem:** Implement `char *itoa_base(long long v, char *buf, int base)` for bases 2..36, handling negatives and `LLONG_MIN` correctly (the negation trap). Then a `print_bits(int)` that prints a 32-bit binary representation.

**Think about:**
- Why does `-x` overflow for `x = LLONG_MIN`? How do you handle it using `unsigned`?
- What is the maximum buffer length needed for base 2 of a 64-bit number?

---

### Day 50: Mini `sed`-Like Line Replacer

**Concepts:** file I/O preview, search/replace, dynamic strings.

**Context:** Python's `str.replace`. Here you stream lines and rebuild them.

**Problem:** Read a text file line by line (`fgets` or `getline`), replace all occurrences of a token with another, and write to stdout. Use your Day 12 string builder or in-place replacement. Handle lines longer than your buffer.

**Think about:**
- Why is `getline` (POSIX) easier than `fgets` for arbitrary line lengths?
- What happens to the file if you read and write to the *same* file in place?

---

## 6. Arrays & Data Structures

---

### Day 51: Stack via Raw Array

**Concepts:** LIFO, bounds checking, `push`/`pop`.

**Context:** The call stack itself is a stack; here you build one explicitly.

**Problem:** Implement an `int` stack with fixed capacity: `push`, `pop`, `peek`, `is_empty`, `is_full`, `size`. Then use it to:
1. reverse a string's words
2. check balanced parentheses (`()[]{}`)
3. evaluate a postfix expression

**Think about:**
- Why does an underflow check matter as much as an overflow check?
- How would you make it growable without changing the API?

---

### Day 52: Queue via Raw Array (and Why It's Bad)

**Concepts:** FIFO, head/tail indices, wasted space.

**Context:** A naive queue on a linear array wastes space unless you shift or wrap.

**Problem:** Implement a linear-array queue that shifts elements on dequeue, measure the O(n) cost, then replace it with a circular buffer (Day 53) and compare.

**Think about:**
- What is the space/time trade-off between shifting and wrapping?
- How do you distinguish "empty" from "full" in a circular buffer? (count, or sacrifice one slot.)

---

### Day 53: Circular Buffer

**Concepts:** modular arithmetic, wrap-around, overwrite policy.

**Context:** Audio ring buffers, logging, kernel event queues.

**Problem:** Implement a ring buffer for bytes with 2 modes: overwrite-oldest and drop-newest. Support `push`, `pop`, `peek`, `len`, `is_full`. Make capacity a power of two and use `& (cap-1)` instead of `%`.

**Think about:**
- Where does the boundary condition break if you use `size == cap` for full with head==tail?
- Why is power-of-two masking faster than modulo?

---

### Day 54: Singly Linked List

**Concepts:** pointer chasing, `malloc` per node, insertion/deletion.

**Context:** Python lists are arrays of pointers. Linked lists trade locality for O(1) splice.

**Problem:** Implement a singly linked list with `push_front`, `push_back` (with tail pointer), `insert_after`, `remove_value`, `find`, `free_all`. Then remove the head repeatedly while freeing and prove no leaks.

**Think about:**
- Why do you need `Node **` (pointer to pointer) for deletion from a list head?
- Why is a linked list cache-unfriendly compared to a dynamic array?

---

### Day 55: Reverse a Linked List

**Concepts:** three-pointer reversal, in-place mutation.

**Context:** A classic interview problem; also shows pointer discipline.

**Problem:** Reverse a singly linked list iteratively (three pointers: prev/cur/next) and recursively. Then reverse only nodes `[m, n]`. Test on sizes 0, 1, 2, 10 and print before/after.

**Think about:**
- Why does the recursive version use O(n) stack space?
- What is the last thing you must set to avoid a cycle?

---

### Day 56: Floyd's Cycle Detection

**Concepts:** tortoise & hare, cycle entry point, O(1) space.

**Context:** JSON serializers, GC (mark-sweep), and "does this list loop" need cycle detection.

**Problem:** Build a list with an intentional cycle. Implement `has_cycle` (fast/slow) and `find_cycle_start` (reset one pointer after meeting). Prove it with a reference that uses a hash set.

**Think about:**
- Why do the two pointers always meet if a cycle exists?
- Why does resetting to the head after the meeting find the cycle start?

---

### Day 57: Merge Two Sorted Lists

**Concepts:** merge, dummy head, recursion vs iteration.

**Context:** Merge sort's core operation; also database merge joins.

**Problem:** Implement iterative and recursive merge of two sorted singly linked lists into a new list (reusing nodes). Then merge k lists (stretch: via a min-heap or pairwise).

**Think about:**
- Why does the recursive version consume stack proportional to list length?
- Does reusing nodes vs copying them change complexity?

---

### Day 58: Doubly Linked List + LRU List

**Concepts:** prev/next, O(1) unlink, sentinel nodes.

**Context:** LRU caches (CPython's `OrderedDict` uses a doubly linked list).

**Problem:** Implement a DLL with sentinel head/tail. Support `push_front`, `unlink(node)`, `move_to_front(node)`, `pop_back`. Then implement a fixed-capacity LRU: on access, move to front; on insert when full, evict back. Use a hash map from key to node for O(1).

**Think about:**
- Why do sentinels remove almost all edge cases?
- Why must you save `node->next` before `unlink(node)` in a single-threaded loop?

---

### Day 59: Hash Table with Chaining

**Concepts:** hashing, buckets, collisions, load factor.

**Context:** Python `dict`. Here you implement the machinery.

**Problem:** Implement a string-keyed hash table with separate chaining:
```c
struct entry { char *key; int val; struct entry *next; };
```
`put` (replace existing key), `get`, `del`, `free_all`. Use a simple FNV-1a hash. Track load factor and print bucket length distribution.

**Think about:**
- Why must `put` free the old key or value on replacement?
- Why is a good hash function critical for worst-case behavior?

---

### Day 60: Hash Table with Open Addressing + Resize

**Concepts:** probing, tombstones, rehashing, load factor.

**Context:** CPython's dict uses open addressing (perturbed probing) to be cache-friendly.

**Problem:** Implement an open-addressing table with linear or quadratic probing. Support `put`, `get`, `del` (tombstones), and automatic resize at load factor 0.7. Benchmark lookups vs Day 59's chained table.

**Think about:**
- Why do tombstones accumulate, and when do you need to rehash?
- Why is open addressing more cache-friendly than chaining?

---

### Day 61: Binary Search Without `[]`

**Concepts:** `lo`/`hi` invariant, mid overflow, first/last occurrence.

**Context:** Python's `bisect`. Bugs like `(lo+hi)/2` overflow are famous.

**Problem:** Implement:
```c
const int *bsearch_raw(const int *a, size_t n, int key);
const int *lower_bound(const int *a, size_t n, int key);
const int *upper_bound(const int *a, size_t n, int key);
```
All via pointer arithmetic. Compare with Day 6's generic `bsearch`. Explain why `mid = lo + (hi-lo)/2` beats `(lo+hi)/2`.

**Think about:**
- What loop invariant makes `lower_bound` return the first element ≥ key?
- How many comparisons does a search of 1,000,000 elements need?

---

### Day 62: Sort an Array of Pointers by Pointer Arithmetic

**Concepts:** sorting, comparator, pointer vs element swap.

**Context:** Python sorts objects by key. Here you sort `char *` strings by length then lexicographically.

**Problem:** Implement `sort_strings(char **arr, size_t n)` sorting by (length, then `strcmp`) using your Day 6 `my_qsort`. Then implement merge sort and insertion sort on `int` arrays via pointer arithmetic, and benchmark.

**Think about:**
- Why is insertion sort fast on nearly-sorted data?
- Why is merge sort preferred for linked lists but quicksort for arrays?

---

## 7. Number Representation

---

### Day 63: `itoa` From Scratch

**Concepts:** division/remainder, digit extraction, buffer reversal.

**Context:** Python's `str(int)` is a C call. Write the C call.

**Problem:** Implement `char *itoa(int v, char *buf)` for negatives and `INT_MIN`. Then a fast version that fills the buffer backwards (avoiding a reverse pass). Compare both with `snprintf`.

**Think about:**
- Why does the "fill backwards" trick avoid a reversal?
- Why does the standard not require `itoa`? (Not in ISO C; it's a common extension.)

---

### Day 64: `atoi` From Scratch (and `strtol`)

**Concepts:** parsing, overflow detection, whitespace/sign.

**Context:** Python's `int("...")` handles overflow by promoting to bignum. C just overflows.

**Problem:** Implement `my_atoi`, then `my_strtol(const char *s, char **end, int base)` that:
- skips leading whitespace
- handles `+`/`-`
- handles base 0 (0x/0 prefixes), 8, 10, 16
- detects overflow and returns `LONG_MAX`/`LONG_MIN` with `errno = ERANGE`
- sets `end`

**Think about:**
- Why is `atoi` unable to report errors while `strtol` can?
- How do you detect overflow without using a wider type? (Compare against `LONG_MAX/10` before multiply.)

---

### Day 65: Subtraction via Addition and Bit Flips

**Concepts:** two's complement, `~x + 1`, half-adder.

**Context:** Hardware has no subtractor — it adds the two's complement. Python hides this.

**Problem:** Implement `int my_sub(int a, int b)` using only `+`, `~`, `&`, `|`, `^`, `<<`, `>>` (no `-`). Then implement `add` using only bitwise ops (carry loop). Build a 4-bit ALU simulator: add, sub, and, or, xor, not, and compute flags.

**Think about:**
- Why does `~b + 1` equal `-b` in two's complement?
- What happens for `INT_MIN` negation, and why is it special?

---

### Day 66: Signed vs Unsigned Overflow

**Concepts:** modular arithmetic, UB, `-fwrapv`, `-ftrapv`.

**Context:** Python never overflows. C: unsigned wraps, signed is UB.

**Problem:** Write tests that demonstrate:
- unsigned overflow wraps modulo 2ⁿ
- signed overflow is UB (observe with `-O2` vs `-O0` and with UBSan)
- a loop `for (int i; i < n; i++)` optimization difference with `-fwrapv`

Use `-fsanitize=undefined` to catch it.

**Think about:**
- Why is signed overflow UB instead of defined wrap? (Optimization freedom.)
- Why is `size_t` unsigned a common source of underflow bugs?

---

### Day 67: Fixed-Point Arithmetic

**Concepts:** Q-format, scaling, rounding, overflow.

**Context:** Embedded/DSP avoids floats. Python has `decimal`/`fractions`; C gives you fixed-point by hand.

**Problem:** Implement Q16.16 fixed-point: `int32_t` with 16 fractional bits. Support `add`, `sub`, `mul` (with a 64-bit intermediate and rounding), `div`, `from_float`, `to_float`, and `sqrt` via Newton's method. Test precision against `double`.

**Think about:**
- Why must `mul` use a 64-bit intermediate?
- How does rounding (`+ (1<<15)`) before shifting reduce bias?

---

### Day 68: IEEE-754 Float Inspector

**Concepts:** bit fields of floats, normalization, special values.

**Context:** Python floats are doubles; understanding them prevents NaN surprises.

**Problem:** Write `void inspect_float(float f)` that prints sign, biased exponent, mantissa, whether it's normalized/denormal/zero/inf/NaN, and the value. Handle subnormals. Then compare `-0.0f == 0.0f` (true) with their bit patterns (different).

**Think about:**
- Why is `NaN != NaN`? Which bits encode NaN?
- Why can't you compare floats with `==` for exact decimal values?

---

## 8. Recursion & the Call Stack

---

### Day 69: Visualize the Stack

**Concepts:** stack frames, addresses, growth direction.

**Context:** Python has a call stack too, but its frames are heap objects. C frames live on the machine stack.

**Problem:** Write a recursive function that prints the address of a local variable at each depth. Show the stack grows *down* on x86-64. Print `&local` and the frame gap between levels. Then print the difference between a frame from `main` and one deep in recursion.

**Think about:**
- Why is the stack pointer decremented on function entry?
- Why is a frame's exact size not something you should rely on?

---

### Day 70: Tail vs Regular Recursion

**Concepts:** TCO, accumulator, stack usage.

**Context:** Python has no TCO. C compilers may do it at `-O2`.

**Problem:** Implement factorial and sum recursively (non-tail) and with an accumulator (tail). Compile at `-O0` and `-O2`, disassemble with `objdump`, and see whether the tail version becomes a loop (look for `jmp` back with no `call`). Find factorial(100000) crashing vs surviving with TCO.

**Think about:**
- Why is TCO guaranteed in Scheme but only opportunistic in C?
- What does `-foptimize-sibling-calls` do?

---

### Day 71: Deliberately Overflow the Stack

**Concepts:** stack limits, `SIGSEGV`, `ulimit`, frame size.

**Context:** Python raises `RecursionError`; C just segfaults.

**Problem:** Write infinite recursion with a large local array to consume 1 MB per frame. Catch the crash. On Linux, inspect `ulimit -s`. Then:
- reduce frame size and recurse deeper
- install a `SIGSEGV`/`SIGALTSTACK` handler to print a friendly message (preview of signals)

**Think about:**
- Why does a large local array cause a crash with far fewer frames?
- Why do you need `sigaltstack` to handle stack-overflow `SIGSEGV`?

---

### Day 72: Convert Recursion to Iteration

**Concepts:** explicit stack, recurrences, memory trade-offs.

**Context:** Python hits recursion limits; iterative code scales.

**Problem:** Take recursive implementations of:
1. Fibonacci (memoized)
2. Towers of Hanoi
3. N-Queens

and convert at least one to an explicit stack/iteration. Compare stack memory and runtime. Then implement Ackermann and note why it can't be flattened easily.

**Think about:**
- When does an explicit stack beat the call stack?
- Why is naive Fibonacci recursion exponential, and how much does memoization save?

---

## 9. Debugging & Undefined Behavior

---

### Day 73: Spot the Bug — Uninitialized

**Concepts:** indeterminate values, `-Wuninitialized`, MSan.

**Context:** Python zero-initializes/references; C locals are garbage.

**Problem:** Find every uninitialized read:
```c
int main(void) {
    int x;
    int arr[5];
    int *p;
    if (x > 0) puts("pos");
    arr[3] = arr[1] + 2;
    printf("%d\n", *p);
    return 0;
}
```
Predict output, run with `-Wall -Wextra -Wmaybe-uninitialized`, then with Valgrind/MSan.

**Think about:**
- Why is an uninitialized read UB, not "just garbage"?
- Why might it "work" in a debug build but not with `-O2`?

---

### Day 74: Spot the Bug — Off-by-One

**Concepts:** `<=` vs `<`, one-past-the-end, loop bounds.

**Context:** `for i in range(n)` in Python is forgiving; C loops are not.

**Problem:** Fix the off-by-ones:
```c
void fill(int *a, size_t n) { for (size_t i = 0; i <= n; i++) a[i] = 0; }
void copy(char *dst, const char *src, size_t n) {
    for (size_t i = 0; i < n; i++) dst[i] = src[i];   /* forgets terminator */
}
void print(const int *a, size_t n) { for (size_t i = n; i >= 0; i--) printf("%d", a[i]); }
```
The last one is extra nasty: `size_t` is unsigned. Explain the infinite loop.

**Think about:**
- Why does `i >= 0` never fail when `i` is unsigned?
- How does ASan catch the first bug immediately?

---

### Day 75: Spot the Bug — Dangling Pointer

**Concepts:** returning stack addresses, use-after-free, realloc invalidation.

**Context:** Python holds references; C pointers don't extend lifetimes.

**Problem:** Given three functions (return `local` array, return `&local_var`, keep pointer into a `realloc`ed buffer), classify each as stack-dangling, heap-UAF, or invalidated-by-realloc. Fix each.

**Think about:**
- Why can a `realloc` invalidate pointers even if it returns the same address?
- What is pointer provenance and how do modern compilers track it?

---

### Day 76: Integer Overflow in Real Code

**Concepts:** overflow, allocation size multiplication, TOCTOU.

**Context:** `malloc(n * sizeof(T))` can overflow to a small number, then you write out of bounds.

**Problem:** Analyze:
```c
size_t n = user_count;               /* attacker-controlled */
int *a = malloc(n * sizeof(int));    /* if n*4 overflows... */
for (size_t i = 0; i < n; i++) a[i] = i;
```
Write a safe `xcalloc(n, size)` that checks `n > SIZE_MAX / size`. Then discuss C23's `[[nodiscard]]` and `reallocarray`.

**Think about:**
- How does overflow in the size computation become a heap overflow?
- Why does `calloc` avoid this internally?

---

### Day 77: Sequence Points and `i = i++`

**Concepts:** sequencing, UB expressions, clang/gcc divergence.

**Context:** Python evaluates statements predictably. C leaves many orders unspecified or UB.

**Problem:** For each expression, predict the result or say "UB", then test on gcc and clang:
```c
int i = 0; i = i++;
int a = 1; a = a++ + ++a;
int x[2] = {0}; int k = 0; x[k] = k++;
f(i++, i++);
```
Explain why compilers disagree.

**Think about:**
- What is a sequence point and where are the modern C11 ones?
- Why is `f(i++, i++)` unspecified rather than UB (or is it UB)?

---

### Day 78: Strict Aliasing Violation

**Concepts:** effective type, `-fstrict-aliasing`, type punning.

**Context:** Reading an `int` through a `float *` is UB and can be miscompiled.

**Problem:** Write a function that reinterprets a `float` through an `int *`; test at `-O0` and `-O2` and observe miscompilation. Then fix it with a union or `memcpy`. Explain the "effective type" rule.

**Think about:**
- Why is `char *` (and `unsigned char *`) exempt from aliasing?
- When is `-fno-strict-aliasing` necessary (e.g. old code, network stacks)?

---

### Day 79: UB Enables "Impossible" Optimizations

**Concepts:** UB, compiler reasoning, `-fsanitize=undefined`.

**Context:** UB means the compiler assumes it never happens, so it can delete "dead" checks.

**Problem:** Compile the classic:
```c
int foo(int x) { return x + 1 > x; }          /* compiler may return 1 always */
int bar(int *p) { return p + 1 > p; }          /* and assume p != NULL */
```
Disassemble and show the check vanishes. Add `-fwrapv` and show it returns correctly.

**Think about:**
- Why can the compiler assume `x + 1 > x` without knowing `x`?
- What is a "signed overflow" dependent security bug (e.g. `if (len + 1 < len)` checks)?

---

### Day 80: Sanitizer Lab

**Concepts:** ASan, UBSan, MSan, TSan, coverage.

**Context:** Python's own C runtime uses these. You should too.

**Problem:** Write one program with (separately toggleable) `#ifdef`s for:
- heap-buffer-overflow
- use-after-free
- signed overflow
- data race (LSan/TSan)

Compile with `-fsanitize=address,undefined` and `-fsanitize=thread`, capture reports, and rewrite each to be clean. Record the exact report wording.

**Think about:**
- Why can't ASan and TSan be combined in one binary?
- What overhead does ASan add, and why is that fine at test time?

---

# Part B — Systems Concepts

## 10. Process & Memory Model

---

### Day 81: Program Layout Tour

**Concepts:** text/data/bss/heap/stack, addresses.

**Context:** Python's runtime hides segments. Here you print their addresses and see the map.

**Problem:** Write a program that prints the address of:
- a function (text)
- a global initialized variable (data)
- a global uninitialized variable (bss)
- a `malloc`'d block (heap)
- a local variable (stack)

Sort them by address and explain the order. On Linux, cross-check with `/proc/self/maps`.

**Think about:**
- Why are the heap and stack on opposite ends, growing toward each other?
- What is ASLR and how does it change these addresses run to run?

---

### Day 82: Stack vs Heap Allocation Patterns

**Concepts:** lifetime, size limits, allocation cost.

**Context:** Python objects live on the heap. C lets you choose.

**Problem:** Benchmark allocating 1M ints:
1. as one stack/VLA array (careful with limits)
2. as one `malloc`
3. as 1M separate `malloc`s

Time each. Then discuss when stack allocation is wrong (returning it, huge sizes).

**Think about:**
- Why is per-object `malloc` so much slower than one block?
- What is the maximum safe stack allocation? (Depends on `ulimit`.)

---

### Day 83: `argc`/`argv`/`environ`

**Concepts:** process arguments, environment array, `NULL` termination.

**Context:** `sys.argv` and `os.environ`.

**Problem:** Print all args and all environment variables by walking `environ` as a `NULL`-terminated `char **`. Implement a mini `--name=value` CLI parser into a small map. Run under `env -i` to see empty environment.

**Think about:**
- Why is `argv[argc] == NULL` guaranteed?
- Why is `environ` not declared in `<stdio.h>` but via `extern char **environ;`?

---

### Day 84: `getenv`/`setenv`/`unsetenv` and Inheritance

**Concepts:** environment manipulation, `putenv` lifetime, exec inheritance.

**Context:** `os.environ` writes back to the C environment.

**Problem:** Read, set, unset env vars; then `fork`+`exec` a child (e.g. `/usr/bin/env`) and show inherited values. Demonstrate the `putenv` vs `setenv` dangling-string bug.

**Think about:**
- Why does `putenv` require the string to outlive the call, while `setenv` copies it?
- Are environment changes visible to processes already running?

---

### Day 85: `fork` Basics

**Concepts:** process duplication, return values, copy-on-write.

**Context:** Python's `multiprocessing` uses fork/spawn underneath.

**Problem:** Call `fork` and print `getpid`, `getppid` in parent and child. Show that the child gets a *copy* of variables, not shared memory (modify and reprint). Then demonstrate copy-on-write by touching a big array in the child.

**Think about:**
- Why does `fork` return 0 in the child and the child's PID in the parent? What on error?
- Why is `fork` cheap until you write to memory?

---

### Day 86: Zombies and Reaping

**Concepts:** `wait`/`waitpid`, zombie state, `SIGCHLD`.

**Context:** Unreaped children become zombies until the parent waits.

**Problem:** Fork a child that exits immediately; don't wait; run `ps` and find the `<defunct>` zombie. Then reap with `waitpid`, and also test `WNOHANG`. Finally use a `SIGCHLD` handler to reap automatically.

**Think about:**
- What are the two ways a zombie is cleaned up?
- Why does `wait` return -1 with `ECHILD` when there are no children?

---

### Day 87: The `exec` Family

**Concepts:** `execve`, replacing address space, `PATH` search.

**Context:** Python's `os.exec*`; shells call these constantly.

**Problem:** Use `execlp`, `execvp`, and `execve` (with a custom env) to run `/bin/echo`, `ls -l`, and a script. Show that code after a successful `exec` never runs. Handle `exec` failure explicitly.

**Think about:**
- Why is there no "exec returns success" path to code after it?
- Difference between `execv`/`execvp`/`execve`/`execlp`?

---

### Day 88: Mini Command Runner (fork/exec/wait)

**Concepts:** combining process primitives.

**Context:** `subprocess.run`.

**Problem:** Implement `int run(char *const argv[])` that forks, execs, and waits, returning the child's exit status decoded by `WIFEXITED`/`WEXITSTATUS`. Run `true`, `false`, and a nonexistent command (report 127). Then support background execution.

**Think about:**
- How do you distinguish "exited with code 5" from "killed by signal 9"?
- Why must you use `_exit` (not `exit`) in the child after a failed exec?

---

### Day 89: Orphans and Daemonization

**Concepts:** parent death, `setsid`, reparenting to init.

**Context:** Daemons detach from the terminal. Python's `daemon` libs do this.

**Problem:** Fork a child, have the parent exit immediately, then show the child's `getppid()` becomes 1 (or a subreaper). Then build a minimal daemon: `fork`, `setsid`, `chdir("/")`, redirect std fds to `/dev/null`.

**Think about:**
- What does `setsid` detach you from?
- Why redirect stdin/stdout/stderr in a daemon?

---

### Day 90: `/proc/self/maps` Parser

**Concepts:** virtual memory regions, permissions, file-backed vs anonymous.

**Context:** Python's `psutil` reads this. Parse it yourself.

**Problem:** Read `/proc/self/maps`, parse each line into `(start, end, perms, offset, pathname)`, and classify regions: text, heap (`[heap]`), stack (`[stack]`), libraries, anonymous. Print a summary and total mapped bytes.

**Think about:**
- What do `r-xp` vs `rw-p` permissions mean?
- Why is `[heap]` sometimes multiple non-contiguous regions?

---

### Day 91: Growth of the Heap (`brk` vs `mmap`)

**Concepts:** allocator behavior, `sbrk`, `mmap`, large allocations.

**Context:** glibc `malloc` uses `brk` for small allocations and `mmap` for large ones.

**Problem:** Allocate many small blocks and watch `[heap]` grow. Allocate one huge block and find a new anonymous mapping in `/proc/self/maps`. Find the `M_MMAP_THRESHOLD` (often 128 KiB) empirically.

**Think about:**
- Why does glibc switch to `mmap` for large allocations?
- What is `MADV_DONTNEED`/`MADV_FREE` and why does `free` sometimes not return memory to the OS?

---

### Day 92: Memory Layout of Threads

**Concepts:** thread stacks, guard pages, TLS.

**Context:** Each pthread gets its own stack, usually via `mmap`.

**Problem:** Create 3 threads, each printing its stack-local address and `pthread_self()`. Compare distances between thread stacks (look for `mmap` regions in `/proc/self/maps`). Explain guard pages.

**Think about:**
- Why is thread stack size finite and configurable?
- What is thread-local storage (`__thread`) and where does it live?

---

## 11. Syscalls, File I/O & IPC

---

### Day 93: Raw `read`/`write` vs `fread`/`fwrite`

**Concepts:** buffering, syscall overhead, partial reads.

**Context:** Python's file objects are buffered. The C `FILE *` layer is too.

**Problem:** Copy a large file (a) with `read`/`write` in a loop, (b) with `fread`/`fwrite`, (c) with byte-at-a-time `read`. Time them. Then demonstrate a partial read with `read` on a pipe/socket.

**Think about:**
- Why is byte-at-a-time `read` catastrophically slow?
- Why can `read` return fewer bytes than requested? (This is why `fread` exists.)

---

### Day 94: Binary File Parsing with `fread`/`fwrite`

**Concepts:** binary formats, endianness, struct serialization.

**Context:** Python `struct` + `open('rb')`. Do it in C.

**Problem:** Write a tiny record file format: a header (magic, version, count) followed by records. Write 5 records, then read them back, validating magic and count. Then corrupt a byte and detect it via checksum.

**Think about:**
- Why should you never trust fields read from a file without validation?
- Why does `fwrite` return a count of *items*, and why check it?

---

### Day 95: File Descriptors and `dup`/`dup2`

**Concepts:** fd table, redirection, close-on-exec.

**Context:** Shell redirection is `dup2`. Python's `subprocess` uses it.

**Problem:** Open a file, `dup` the fd, write via both, and show they share the file offset. Then use `dup2` to redirect stdout to a file and print. Restore stdout. Discuss `FD_CLOEXEC`.

**Think about:**
- Why do duplicated fds share offset but have separate descriptors?
- Why set `FD_CLOEXEC` to prevent fd leaks into children?

---

### Day 96: Pipes

**Concepts:** unidirectional IPC, blocking, EOF on close.

**Context:** `subprocess` pipes are `pipe()` fds.

**Problem:** Create a pipe, fork, have the child write lines and the parent read until EOF. Then reverse the direction. Show that if the writer doesn't close the write end, the reader never sees EOF.

**Think about:**
- Why must *all* write ends be closed for the reader to get EOF?
- What is the pipe buffer size and what happens when a writer fills it?

---

### Day 97: Two-Process Pipeline

**Concepts:** pipe + fork + exec + wait.

**Context:** `ls | grep foo` in a shell.

**Problem:** Implement `run_pipeline("cat file", "grep abc", "wc -l")` for two or three stages using pipes, forks, `dup2`, and `execvp`. Close unused ends in every child. Wait for all.

**Think about:**
- Why must each child close the pipe ends it doesn't use?
- In which order do you wait, and does it matter?

---

### Day 98: `mmap` a File

**Concepts:** memory-mapped files, page cache, `msync`.

**Context:** Python `mmap` module. Here you use the syscall.

**Problem:** `mmap` a file read-only, scan for a byte pattern, then map read-write and modify bytes in place; `msync` and verify the file changed. Compare performance with `read` on a large file.

**Think about:**
- Why is mmap often faster for random access but not always for sequential?
- What happens if the file is truncated while mapped? (SIGBUS.)

---

### Day 99: Shared Memory IPC with `mmap`

**Concepts:** `MAP_SHARED|MAP_ANONYMOUS`, producer/consumer without pipes.

**Context:** Python `multiprocessing.shared_memory`.

**Problem:** `mmap` an anonymous shared region before `fork`; parent writes a message + a sequence counter, child polls and reads it; use a shared `volatile` flag and `__sync_synchronize()` for ordering.

**Think about:**
- Why is shared memory faster than pipes for large payloads?
- Why do you still need synchronization even with shared memory?

---

### Day 100: TCP Echo Client

**Concepts:** sockets, `connect`, `send`/`recv`, partial writes.

**Context:** Python `socket`. The C API is lower-level.

**Problem:** Write a client that connects to `127.0.0.1:9000`, sends a line, and prints the echo. Handle partial sends with a `send_all` loop and `recv` returning 0 (peer closed).

**Think about:**
- Why can `send` deliver fewer bytes than requested?
- Why does `recv` returning 0 mean EOF, not an error?

---

### Day 101: TCP Echo Server

**Concepts:** `socket`/`bind`/`listen`/`accept`, `SO_REUSEADDR`.

**Context:** The basis of every network service.

**Problem:** Build a single-client echo server. Handle `EINTR` from `accept`. Set `SO_REUSEADDR` and explain why (TIME_WAIT). Then make it handle clients sequentially in a loop.

**Think about:**
- Why does bind fail without `SO_REUSEADDR` after a restart?
- Why does `accept` return a *new* fd?

---

### Day 102: Multiplexing with `select`/`poll`

**Concepts:** I/O multiplexing, readiness, fd sets.

**Context:** Python `selectors`. Build the loop yourself.

**Problem:** Extend the echo server to handle N clients with `select` (or `poll`). Maintain a client array; add on `accept`, remove on EOF/error. Then compare with a thread-per-client server.

**Think about:**
- What does "readable" guarantee? That `recv` won't block?
- Why does `select` have an FD_SETSIZE limit and `poll` doesn't (as much)?

---

### Day 103: Non-Blocking I/O

**Concepts:** `O_NONBLOCK`, `EAGAIN`/`EWOULDBLOCK`, event loops.

**Context:** `asyncio` is built on non-blocking fds.

**Problem:** Set a socket non-blocking with `fcntl`. Loop calling `recv`; handle `EAGAIN` by doing other work. Demonstrate a connect-in-progress returning `EINPROGRESS`.

**Think about:**
- Why does a non-blocking `recv` return -1 with `EAGAIN` instead of blocking?
- Why is busy-polling on `EAGAIN` bad, and what replaces it?

---

### Day 104: File Locking

**Concepts:** `flock`/`fcntl` locks, advisory vs mandatory, concurrency.

**Context:** Python `fcntl.flock`. Prevent multiple processes corrupting a file.

**Problem:** Build two processes writing to one log file, guarded by `flock` (exclusive) so lines don't interleave. Then compare with lock-free writing to show interleaving/corruption.

**Think about:**
- Why are POSIX locks advisory?
- What happens to a lock when the process dies?

---

### Day 105: Named Pipes (FIFOs)

**Concepts:** `mkfifo`, unrelated-process IPC.

**Context:** Anonymous pipes only connect related processes; FIFOs have a filesystem name.

**Problem:** Create a FIFO with `mkfifo`, write from one program and read from another. Show that `open` for read blocks until a writer appears (and vice versa).

**Think about:**
- How does a FIFO differ from `pipe()` beyond the name?
- Why does opening a FIFO for write block until a reader opens it?

---

### Day 106: Shared Memory + Semaphore Under the Hood

**Concepts:** System V / POSIX shared memory, semaphores, process sync.

**Context:** Python `multiprocessing.Semaphore`. Implement the primitives.

**Problem:** Use POSIX `shm_open` + `mmap` + `sem_open` to implement a single-slot producer/consumer across two unrelated processes. Clean up with `shm_unlink`/`sem_unlink`.

**Think about:**
- Why must the semaphore be in shared/system memory, not a stack variable?
- What is the difference between a named and unnamed semaphore?

---

## 12. Concurrency & Synchronization

---

### Day 107: `pthread_create` / `pthread_join`

**Concepts:** thread lifecycle, `void *` thread argument, return values.

**Context:** Python threads share the GIL; C threads truly run in parallel.

**Problem:** Create 4 threads each summing a slice of an array, join, combine results. Pass a struct per thread; return a value via the `void *` return or an out-param. Compare runtime to single-threaded.

**Think about:**
- Why is `pthread_join` needed (resources aren't freed otherwise)?
- Why does the `void *` argument force casts, and what breaks if it points to a loop variable?

---

### Day 108: Race Condition Demo

**Concepts:** data races, lost updates, non-atomic `++`.

**Context:** The GIL masks some races in Python; C has none to save you.

**Problem:** Have 8 threads increment a shared `long` 1,000,000 times each. Observe the result is less than 8,000,000. Run with TSan to see the race report. Explain the read-modify-write window.

**Think about:**
- Why does `counter++` compile to load/add/store, and where's the race?
- Does declaring it `volatile` fix it? (No — explain why.)

---

### Day 109: Fixing the Race with a Mutex

**Concepts:** `pthread_mutex_t`, critical sections, contention.

**Context:** Python's `threading.Lock`.

**Problem:** Fix Day 108 with a mutex. Measure runtime vs the racy and vs a per-thread-local accumulation. Then reduce contention by giving each thread a local counter and combining at the end.

**Think about:**
- Why is a lock around the whole loop slower than per-thread locals?
- What is lock contention and how does it limit scaling?

---

### Day 110: Atomic Operations

**Concepts:** `_Atomic`, `__atomic_*`, lock-free counters.

**Context:** C11 atomics map to CPU instructions instead of locks.

**Problem:** Implement the counter with `atomic_fetch_add` and with `__sync_fetch_and_add`. Benchmark vs mutex. Then implement a lock-free "increment and get max" using CAS (`compare_exchange`).

**Think about:**
- Why is an atomic increment faster than a mutex for a single counter?
- What is the ABA problem in CAS-based algorithms?

---

### Day 111: Condition Variables

**Concepts:** `pthread_cond_t`, wait/signal, predicate loops.

**Context:** Python `threading.Condition`. The loop-around-wait rule is critical.

**Problem:** Implement a bounded buffer where a producer waits when full and a consumer waits when empty. Use `pthread_cond_wait` in a `while` loop, not an `if`. Demonstrate a spurious wakeup handling.

**Think about:**
- Why must you re-check the predicate after waking?
- Why must the mutex be held while signaling (or why is it optional but careful)?

---

### Day 112: Semaphores

**Concepts:** `sem_t`, counting vs binary, `sem_wait`/`sem_post`.

**Context:** Python `threading.Semaphore`.

**Problem:** Implement a connection-pool limiter with a counting semaphore (e.g. max 3 concurrent workers among 10). Then implement a rendezvous between two threads using two binary semaphores.

**Think about:**
- How does a semaphore differ from a mutex (ownership)?
- Why can `sem_wait` be interrupted and what do you do?

---

### Day 113: Producer–Consumer with a Bounded Buffer

**Concepts:** combining mutex + condvars, backpressure.

**Context:** `queue.Queue` in Python. Build it in C.

**Problem:** Implement a thread-safe ring buffer with `put` (blocks when full) and `get` (blocks when empty). Use one mutex and two condition variables (`not_full`, `not_empty`). Stress with 4 producers and 4 consumers; verify total counts and no data loss.

**Think about:**
- Why two condition variables instead of one?
- Why does `pthread_cond_signal` wake one waiter but `broadcast` wake all?

---

### Day 114: Reader–Writer Lock

**Concepts:** shared/exclusive access, writer starvation.

**Context:** Databases and `pthread_rwlock_t`.

**Problem:** Implement an RW lock with a mutex + counters + condvar(s). Readers can hold simultaneously; writers are exclusive. Then add writer preference to avoid writer starvation. Test with many readers and a few writers.

**Think about:**
- Why can naive reader-preference starve writers?
- Why might Python's GIL make this moot but C's threads not?

---

### Day 115: Thread Pool

**Concepts:** worker threads, task queue, shutdown.

**Context:** Python `concurrent.futures.ThreadPoolExecutor`.

**Problem:** Implement a fixed-size thread pool: a task queue (function pointer + arg), workers pulling tasks, and a graceful shutdown (no new tasks, drain, join). Submit 100 tasks across 4 workers.

**Think about:**
- How do you signal "no more work" to all workers (sentinel tasks vs flag + broadcast)?
- What happens if a task calls `pthread_exit` unexpectedly?

---

### Day 116: Create a Deadlock

**Concepts:** lock ordering, circular wait, Coffman conditions.

**Context:** Python's GIL hides many deadlocks; C deadlocks are real.

**Problem:** Write two threads that each `lock(A)` then `lock(B)`, but in opposite orders, and reliably deadlock. Demonstrate the four Coffman conditions. Use `gdb`/`pstack` to inspect the stuck threads.

**Think about:**
- Which Coffman condition does lock ordering break?
- Why is a deadlock hard to reproduce deterministically?

---

### Day 117: Resolve the Deadlock

**Concepts:** global lock ordering, `trylock`+backoff, `pthread_mutex_timedlock`.

**Context:** `threading` best practices.

**Problem:** Fix Day 116 three ways:
1. establish a global lock order
2. use `pthread_mutex_trylock` and back off
3. acquire all locks upfront or use a single coarser lock

Compare throughput.

**Think about:**
- What is lock convoying?
- When is a single coarse lock actually the right choice?

---

### Day 118: Barriers

**Concepts:** `pthread_barrier_t`, phased computation.

**Context:** `threading.Barrier`. Used in iterative solvers.

**Problem:** Implement a parallel "game of life" step where all threads must finish reading the old grid before any writes to the new grid. Use a barrier between phases. Compare double-buffering with a barrier vs locking.

**Think about:**
- Why does a barrier need a generation counter internally?
- Why is a barrier not a substitute for a mutex?

---

### Day 119: False Sharing

**Concepts:** cache lines, padding, performance.

**Context:** Two Python threads don't share CPU caches like this; C threads do.

**Problem:** Have 4 threads each increment their own `long` in an array (no logical sharing). Show it's much slower when the longs share a cache line. Fix with `alignas(64)` padding. Measure the speedup.

**Think about:**
- Why does writing to independent variables in one cache line cause traffic?
- What size is a cache line on your CPU? (Check `/sys/.../cache/`.)

---

### Day 120: Spinlock with Atomics

**Concepts:** busy-wait, `compare_exchange`, backoff.

**Context:** Useful for very short critical sections; kernels use them.

**Problem:** Implement a spinlock using `atomic_flag_test_and_set` / `atomic_compare_exchange_weak`. Add a `pause`/`__builtin_ia32_pause` and exponential backoff. Compare with a mutex for short vs long critical sections.

**Think about:**
- When is spinning better than blocking?
- Why is a spinlock dangerous on a uniprocessor?

---

### Day 121: Parallel Merge Sort

**Concepts:** divide-and-conquer + threads, task granularity.

**Context:** Python's GIL makes CPU-bound threads useless; C scales.

**Problem:** Implement parallel merge sort: spawn threads for subarrays above a threshold (e.g. 100k), otherwise sort serially. Measure speedup vs serial on 4 cores. Tune the threshold.

**Think about:**
- Why does spawning a thread per element destroy performance?
- What is the difference between concurrency and parallelism here?

---

### Day 122: Thread Cancellation & Cleanup

**Concepts:** cancellation points, cleanup handlers, resource leaks.

**Context:** Cancelling a thread mid-`malloc` can leak; Python wraps this with exceptions.

**Problem:** Start a worker in a loop that allocates and frees. Cancel it with `pthread_cancel`. Observe where it stops and whether resources leak. Add `pthread_cleanup_push`/`pop` to free safely. Compare deferred vs asynchronous cancellation.

**Think about:**
- Why is asynchronous cancellation (the default is deferred) dangerous?
- What is a cancellation point?

---

## 13. Signals

---

### Day 123: Handling `SIGINT`

**Concepts:** signal handlers, `sig_atomic_t`, graceful interrupt.

**Context:** Python raises `KeyboardInterrupt`. C runs your handler in an unexpected context.

**Problem:** Install a `SIGINT` handler that sets a `volatile sig_atomic_t` flag; a main loop checks the flag and exits cleanly. Show that `Ctrl-C` doesn't corrupt the loop. Compare with doing work directly in the handler.

**Think about:**
- Why must the flag be `volatile sig_atomic_t`?
- Why is `printf` inside a signal handler unsafe?

---

### Day 124: `SIGTERM` Graceful Shutdown

**Concepts:** termination signals, cleanup, idempotency.

**Context:** `systemd`/Docker send `SIGTERM` and expect clean shutdown.

**Problem:** Build a server that on `SIGTERM` sets a shutdown flag, stops accepting, drains clients, frees resources, then exits 0. Make the handler idempotent (multiple signals).

**Think about:**
- Why does the default `SIGTERM` action not run `atexit`/destructors?
- Why should a handler do as little as possible?

---

### Day 125: `SIGSEGV` Handler

**Concepts:** fault handling, `sigaction`, `si_addr`, `sigaltstack`.

**Context:** Segfault handlers power crash reporters.

**Problem:** Install a `SIGSEGV` handler using `sigaction` that prints the faulting address from `siginfo_t`. Trigger a NULL deref and a wild-pointer write. Use `sigaltstack` so a stack-overflow `SIGSEGV` is still catchable.

**Think about:**
- Why can't a normal `SIGSEGV` handler run when the stack is exhausted?
- Why is it dangerous to "recover" from `SIGSEGV` and continue?

---

### Day 126: Blocking and Unblocking Signals

**Concepts:** signal masks, `sigprocmask`, deferred delivery.

**Context:** Python's signal handling runs in the main thread at safe points.

**Problem:** Block `SIGINT` with `sigprocmask`, do a critical section, then unblock and show the pending signal is delivered immediately. Then demonstrate protecting a non-reentrant operation.

**Think about:**
- Why might a signal be delivered multiple times if unblocked during a storm?
- Why does `sigprocmask` only affect the calling thread?

---

### Day 127: `signal` vs `sigaction`

**Concepts:** semantics, `SA_RESTART`, `SA_SIGINFO`, portability.

**Context:** `signal()` has historically inconsistent semantics; `sigaction` is the real API.

**Problem:** Install a handler with `signal()` and with `sigaction()`. Test `SA_RESTART`: a blocking `read` interrupted by a signal returns `EINTR` without it, and resumes with it. Show the difference.

**Think about:**
- Why is `SA_RESTART` desirable for some code and harmful for others?
- Why can `signal()` reset the handler on some systems?

---

### Day 128: Async-Signal-Safety

**Concepts:** reentrancy, the async-signal-safe list, self-pipe trick.

**Context:** Python queues signals and handles them in the main loop.

**Problem:** Write a handler that (unsafely) calls `printf`/`malloc`, provoke a deadlock (signal during `malloc`), then fix it with the self-pipe trick: handler writes one byte to a pipe; main loop reads it and does the real work.

**Think about:**
- Why is `malloc` not async-signal-safe?
- How does the self-pipe trick move work out of the handler context?

---

### Day 129: Reaping with `SIGCHLD`

**Concepts:** child-exit notification, non-reentrant `wait`, `SA_NOCLDSTOP`.

**Context:** Python's `signal.SIGCHLD` plus `os.waitpid`.

**Problem:** Install a `SIGCHLD` handler that reaps children in a loop with `waitpid(-1, ..., WNOHANG)` until it returns 0. Spawn several short-lived children and verify no zombies remain.

**Think about:**
- Why must the reap loop call `waitpid` repeatedly?
- Why is `WNOHANG` necessary inside the handler?

---

### Day 130: Timeouts with `timer`/`SIGALRM`

**Concepts:** `alarm`/`setitimer`, interrupting slow operations.

**Context:** Python `signal.alarm`. Useful to bound blocking calls.

**Problem:** Set a one-second `SIGALRM`; in the handler set a flag or `longjmp` out of a slow loop. Implement a `with_timeout(seconds, fn)` helper. Demonstrate interrupting a blocking `read`.

**Think about:**
- Why is `siglongjmp` out of a signal handler fraught with danger (async-signal-safety again)?
- How does `SA_RESTART` interact with alarm-based timeouts?

---

## 14. Compilation & Linking

---

### Day 131: Break a Multi-File Project on Purpose

**Concepts:** declarations vs definitions, `extern`, link errors.

**Context:** Python's imports resolve at runtime; C resolves symbols at link time.

**Problem:** Split code into `util.h`, `util.c`, `main.c`. Then cause each error deliberately:
- missing include → implicit declaration
- missing definition → undefined reference
- duplicate definition → multiple definition
- missing header guard → redefinition

Write down the exact compiler/linker message for each.

**Think about:**
- Why is `int x;` a definition in C (tentative) but `extern int x;` a declaration?
- What does the linker actually do with `.o` symbol tables?

---

### Day 132: Static Library

**Concepts:** `ar`, `.a`, symbol resolution, dead code elimination.

**Context:** Python C extensions are often linked against static libs.

**Problem:** Build `libmath.a` from two `.o` files. Link a program against it with `-L. -lmath`. Add a symbol collision and observe the error. Use `nm libmath.a` to inspect.

**Think about:**
- Why is a static library just an archive of object files?
- Why does link order matter (`-lfoo` before `-lbar`)?

---

### Day 133: Dynamic Library and `dlopen`

**Concepts:** shared objects, PIC, runtime loading, `dlsym`.

**Context:** Python's `ctypes`/`cffi` do exactly this.

**Problem:** Build `libplugin.so` with `-fPIC -shared`. Load it with `dlopen`, resolve a `compute` symbol with `dlsym`, and call it. Build two plugins and dispatch by name. Handle `dlerror` and `dlclose`.

**Think about:**
- Why must shared-library code be compiled with `-fPIC`?
- What does `dlsym` return for a function pointer, and why is casting it legal in POSIX?

---

### Day 134: Header Guards and the ODR-ish

**Concepts:** include guards, `#pragma once`, tentative definitions.

**Context:** Python modules import once; C headers are textually included everywhere.

**Problem:** Create a header with a struct and a global. Include it from two `.c` files. Without a guard, get redefinition errors within one TU; with tentative definitions, get a multiple-definition link error. Fix with guards + `extern` + one definition.

**Think about:**
- Why does `#pragma once` not solve the multiple-definition problem?
- What is an "inline function" in a header and how does C99 handle it?

---

### Day 135: Macro Pitfalls

**Concepts:** text substitution, side effects, `do{}while(0)`, parenthesization.

**Context:** Python functions evaluate arguments once; macros don't evaluate at all — they paste text.

**Problem:** Explain and fix:
```c
#define SQUARE(x) x*x
#define MAX(a,b) ((a)>(b)?(a):(b))
#define LOG(x) printf("log"); 
#define SWAP(a,b) { int t=a; a=b; b=t; }
```
Show `SQUARE(n++)`, `MAX(i++, j++)`, `if (c) LOG(x); else ...`, and `SWAP(a,b);` misuse. Fix with parentheses, `do{}while(0)`, and `({...})` (GNU) or inline functions.

**Think about:**
- Why is an inline function often better than a function-like macro?
- What is the comma operator's role in macros?

---

### Day 136: Inspect a Binary

**Concepts:** sections, symbols, relocations.

**Context:** Python bytecode is inspectable with `dis`; native code with `objdump`.

**Problem:** For a compiled program, use:
- `file` (type/arch)
- `nm` (symbols, `T`/`U`/`B`)
- `readelf -S` (sections), `-l` (segments)
- `objdump -d` (disassembly), `-r` (relocations)

Identify the `main` symbol, `.text`, `.data`, `.bss`, and the dynamic symbols. Disassemble a simple function and annotate it.

**Think about:**
- What's the difference between `.data` and `.bss` in the file vs in memory?
- Why does `objdump` show relocations in an unlinked `.o` but not in an executable?

---

### Day 137: Weak and Hidden Symbols

**Concepts:** weak symbols, symbol interposition, visibility.

**Context:** Used for default implementations and overrides (like malloc hooks).

**Problem:** Declare a `__attribute__((weak))` function and override it in another TU. Then mark a symbol `-fvisibility=hidden` in a shared lib and show it's absent from `nm -D`. Implement a weak default `log` that can be replaced.

**Think about:**
- How does weak linking let a library provide a fallback?
- Why do shared libraries use `-fvisibility=hidden` for performance and safety?

---

### Day 138: Write a Makefile

**Concepts:** build rules, dependencies, incremental builds, flags.

**Context:** Python has `setup.py`/`pyproject`; C uses make/ninja.

**Problem:** Write a `Makefile` that:
- compiles all `.c` to `.o` with `-MMD` dependency generation
- links the program
- has `debug`, `release`, `asan`, and `clean` targets
- only rebuilds what changed (prove by touching one header)

**Think about:**
- Why do header dependencies need `-MMD`/`.d` files?
- What does `.PHONY` protect against?

---

## 15. Timing & Performance

---

### Day 139: Benchmarking with `clock_gettime`

**Concepts:** monotonic clocks, measurement overhead, warmup.

**Context:** Python `time.perf_counter`. Choose the right clock in C.

**Problem:** Write a timing harness using `CLOCK_MONOTONIC`. Benchmark three ways to compute the sum of an array (naive, unrolled, SIMD-intrinsics if available). Warm up, take medians, and report ns/element.

**Think about:**
- Why is `CLOCK_MONOTONIC` better than `CLOCK_REALTIME` for timing?
- Why should you warm up caches and the branch predictor before measuring?

---

### Day 140: Cache-Friendly vs Unfriendly Access

**Concepts:** row-major vs column-major, cache misses, locality.

**Context:** NumPy's C-order vs Fortran-order is this exact trade-off.

**Problem:** Sum a 4096×4096 matrix row-major vs column-major. Time both. Then transpose in place (cache-blocked). Measure the 10×+ gap and explain it with cache lines and prefetching.

**Think about:**
- Why is column-major traversal slow even though it does the same arithmetic?
- How does loop tiling (blocking) improve the transpose?

---

### Day 141: `volatile` and Optimization

**Concepts:** `volatile`, `-O0` vs `-O2`, memory-mapped registers.

**Context:** `volatile` is *not* the same as atomic. It tells the compiler "don't optimize these accesses away".

**Problem:** Write a busy-wait on a `volatile int flag` set by a signal/thread. Show that with `volatile` the loop keeps re-reading; without it, `-O2` hoists the load and loops forever. Then show `volatile` does NOT fix race conditions or ordering.

**Think about:**
- Why is `volatile` needed for MMIO but not for thread synchronization?
- What does `volatile` guarantee and what does it not?

---

### Day 142: Branch Prediction Lab

**Concepts:** predictable vs unpredictable branches, sorted vs random data.

**Context:** This is why sorting data can make code *faster* despite the work.

**Problem:** Sum elements of an array below a threshold. Run with random data, then sorted data. Time the difference (the classic "why is processing a sorted array faster"). Then rewrite branchlessly with a conditional move/ternary and compare.

**Think about:**
- Why does sorted data make the branch predictable?
- How does `perf stat` report branch misses?

---

### Day 143: Memory Bandwidth Benchmark

**Concepts:** bandwidth vs latency, streaming, working set.

**Context:** Distinguishes memory-bound from compute-bound code.

**Problem:** `memcpy` large buffers of increasing size; plot (mentally) throughput vs size. Find where it drops as the working set leaves L1/L2/L3. Compare with a compute-bound sum.

**Think about:**
- What is the memory hierarchy latency for L1/L2/DRAM?
- Why does streaming beat random access even at the same byte count?

---

### Day 144: Optimize a Hot Loop

**Concepts:** profiling, algorithmic vs micro optimization.

**Context:** Python's C extensions are optimized this way. Measure first.

**Problem:** Take a deliberately slow function (e.g. counting primes by trial division) and:
1. profile with `perf`/`gprof` or manual timers
2. improve the algorithm (sieve, √n bound)
3. micro-optimize (branch reduction, loop unrolling)
4. try `-O3 -march=native`

Report speedup at each step.

**Think about:**
- Why does algorithmic improvement almost always beat micro-optimization?
- Why can `-march=native` be dangerous for distributable binaries?

---

# Part C — Multi-Day Capstones

---

### Day 145: Tiny Bytecode VM / Stack Machine

**Concepts:** dispatch loop, operand stack, function pointers, bytecode encoding, GC preview.

**Context:** This is how CPython's `ceval.c` works: a loop over opcodes manipulating a value stack.

**Problem:** Design a bytecode format and a VM with:
- `PUSH`, `ADD`, `SUB`, `MUL`, `DIV`, `LOAD`, `STORE`, `JMP`, `JZ`, `CALL`, `RET`, `PRINT`, `HALT`
- a value stack and a locals frame
- a computed-goto or switch dispatch
- a tiny assembler (or hand-encoded program) computing Fibonacci / factorial

Stretch: add an object heap and a mark-sweep GC.

**Think about:**
- Why is switch dispatch slower than computed goto? (Look at the disassembly.)
- How would you add dynamic typing (tagged values from Day 36)?

---

### Day 146: Hash Table with Resizing (Capstone)

**Concepts:** all of Day 59/60 plus rehashing, iterators, memory.

**Context:** A production `dict`.

**Problem:** Build a robust string→value hash table with:
- separate chaining *and* open addressing variants behind one API
- automatic resize (grow/shrink) with a good load-factor policy
- an iterator that survives... or explicitly documents invalidation
- statistics (collisions, max chain, resizes)
- full ASan/Valgrind-clean teardown

Benchmark against the libc-free reference and explain your choice.

**Think about:**
- What load factor balances memory and speed?
- Why is shrink-on-delete often omitted in practice?

---

### Day 147: Custom `malloc` Allocator (Capstone)

**Concepts:** Day 15/16/18 combined, thread safety, performance.

**Context:** jemalloc/tcmalloc exist because glibc's malloc isn't always best.

**Problem:** Write a full allocator with:
- size classes (small/large)
- free lists per class
- coalescing and splitting
- mmap-backed arenas
- alignment and thread-local caches (or a global mutex first)
- a `LD_PRELOAD`-able `malloc`/`free`/`realloc`/`calloc` shim

Validate by running a real program under your allocator and checking it doesn't crash.

**Think about:**
- Why do real allocators use thread-local caches?
- How do you detect heap corruption caused by a buggy caller?

---

### Day 148: Mini Shell (Capstone)

**Concepts:** fork/exec/wait, pipes, redirection, job control, signals.

**Context:** `bash` distilled to its essence.

**Problem:** Build a shell that supports:
- command execution with args
- pipelines (`a | b | c`)
- input/output redirection (`<`, `>`)
- builtins: `cd`, `exit`, `jobs`
- `&` background jobs and `fg`/`bg` (stretch: process groups, `tcsetpgrp`)
- `SIGINT` handling for `Ctrl-C`

**Think about:**
- Why does the shell fork before exec instead of exec directly?
- Why do background jobs need `setpgid` to avoid receiving terminal signals?

---

### Day 149: Multi-Threaded TCP Echo Server (Capstone)

**Concepts:** threads, sockets, synchronization, graceful shutdown, resource limits.

**Context:** A real network service skeleton.

**Problem:** Build a server that:
- accepts connections in a loop
- spawns a thread per client (or a thread pool from Day 115)
- echoes lines, tracks connected-client count with a mutex
- handles `SIGTERM` for graceful shutdown (drain, join, close)
- limits max clients (semaphore)
- logs with timestamps

Stress it with many concurrent clients (`nc`, a Python load script, or `ab`).

**Think about:**
- When does thread-per-client stop scaling, and what replaces it?
- How do you avoid joining on a thread that's blocked forever?

---

### Day 150: Choose Your Own Capstone

**Concepts:** everything.

**Context:** Consolidate 149 days into one artifact you're proud of.

**Problem:** Pick one and go deep over several days:
- a Lisp/Forth interpreter with a GC
- a tiny HTTP/1.1 server (static files, `GET`/`HEAD`)
- a `git`-like content-addressed store (hashing, zlib, index)
- a `make`-like build tool with dependency graph + parallel jobs
- a debugger using `ptrace` (`PEEKDATA`/`POKEDATA`, breakpoints)
- a binary format parser with a fuzzing harness (AFL/libFuzzer)
- a lock-free MPMC queue with hazard pointers

Document design decisions, benchmarks, and the bugs you hit. Then write a short "what I'd do differently" — the sign of a real systems engineer.

**Think about:**
- Which two earlier puzzles does your capstone depend on most?
- What surprised you about the machine that Python never showed you?

---

## Appendix A: Suggested Weekly Rhythm

| Day of week | Focus |
|---|---|
| Mon | Pointers / memory (Part A §1–2) |
| Tue | Bits / layout (Part A §3–4) |
| Wed | Strings / data structures (Part A §5–6) |
| Thu | Process / I/O / IPC (Part B §10–11) |
| Fri | Threads / signals (Part B §12–13) |
| Sat | Tooling / performance (Part B §14–15) |
| Sun | Review, capstone progress, or a "spot the bug" |

## Appendix B: Toolchain Cheat Sheet

```sh
gcc -Wall -Wextra -Wpedantic -Wconversion -std=c11 -g -O2 file.c -o file
gcc -fsanitize=address,undefined -fno-omit-frame-pointer ...
gcc -fsanitize=thread ...            # cannot combine with asan
valgrind --leak-check=full --show-leak-kinds=all ./prog
clang-tidy file.c -- -std=c11
objdump -d -Mintel ./prog | less
nm -C ./prog
readelf -S -l -s ./prog
strace -f ./prog
perf stat -e branches,branch-misses,cache-misses ./prog
```

## Appendix C: Rules for Predicting, Not Guessing

1. Write the expected `sizeof`/address/output *before* compiling.
2. If it surprises you, disassemble and read the instructions.
3. If it's UB, prove it with a sanitizer, then explain *why* it's UB.
4. If it's a race, prove it with TSan, then explain the interleaving.
5. "It works on my machine" is the punchline of a bug report, not a result.

Happy hacking. The machine is more honest than any abstraction — and far more instructive.
```
