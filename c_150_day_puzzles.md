# 150 Days of C: Low-Level Puzzles for a Python Programmer

One puzzle a day, covering language-level C, systems concepts, and capstone projects.

## How to use this

- **Compile strictly:** `gcc -std=c11 -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined file.c -o file`
- **Also try:** `valgrind --leak-check=full ./file`, and `-O0` vs `-O2` to see behavior change.
- **Difficulty:** ★ warm-up, ★★ standard, ★★★ challenging.
- Each puzzle has a **Problem**, a **Starter**, and **Think about** questions. Write the answers to the questions down in comments; that is where the low-level knowledge sticks.
- Don't use libraries that hide the point of the puzzle (e.g. `memcpy` in the byte-swapper). Each puzzle names its restrictions.
- Puzzles marked **(Python contrast)** compare against what Python does invisibly.

## Roadmap

| Days | Topic |
|---|---|
| 1-12 | Pointers & addresses |
| 13-24 | Manual memory management |
| 25-34 | Bitwise operations |
| 35-44 | Structs, unions & memory layout |
| 45-53 | Strings without stdlib |
| 54-65 | Arrays & data structures |
| 66-73 | Number representation |
| 74-79 | Recursion & the call stack |
| 80-87 | Debugging & undefined behavior |
| 88-96 | Process & memory model |
| 97-108 | Syscalls, file I/O & IPC |
| 109-117 | Concurrency & synchronization |
| 118-123 | Signals |
| 124-130 | Compilation & linking |
| 131-135 | Timing & performance |
| 136-150 | Capstones (VM, hash table, malloc, shell, TCP server) |

---

# Part A: Language-level C

## 1. Pointers & addresses

### Day 1: The Byte Swapper & Memory Layout ★★
**Concepts:** `void *`, pointer casting, endianness, alignment

**Context:** In Python, integers have arbitrary precision and byte conversions happen under the hood with `int.to_bytes()` or `struct.pack()`. In C, everything sits at concrete addresses in virtual memory.

**Problem:** Write `void reverse_bytes(void *ptr, size_t size)` that reverses the raw bytes of any data type in place, with no `malloc`/`free` and no `memcpy`/`memmove`. Test it on a `uint32_t` (`0xAABBCCDD`), a `double`, and a small struct.

**Starter:**
```c
#include <stdio.h>
#include <stdint.h>

void reverse_bytes(void *ptr, size_t size) {
    // TODO: byte-level reversal using raw pointer manipulation
}

int main(void) {
    uint32_t val = 0xAABBCCDD;
    printf("Original: 0x%08X\n", val);
    reverse_bytes(&val, sizeof(val));
    printf("Reversed: 0x%08X\n", val);   // little-endian: 0xDDCCBBAA
    return 0;
}
```

**Think about:**
- Why must you cast `void *` before doing pointer arithmetic?
- What happens to endianness when you view multi-byte words vs. individual byte addresses?
- How does alignment affect casting pointers on x86 vs. strict-alignment ARM?

### Day 2: Sum Without Brackets ★
**Concepts:** pointer arithmetic, `ptrdiff_t`

**Problem:** Write `long sum(const int *begin, const int *end)` that sums the half-open range `[begin, end)` without using `[]` anywhere. Then write `const int *find_max(const int *begin, const int *end)` returning a pointer to the largest element (not its value). Print the *index* of the max using pointer subtraction.

**Starter:**
```c
long sum(const int *begin, const int *end);
const int *find_max(const int *begin, const int *end);
// main: int a[] = {4, 9, -2, 7, 9, 1};
```

**Think about:**
- What type does `end - begin` have, and why isn't it `int`?
- Is it legal to compute `a + 6` for a 6-element array? To dereference it? What about `a + 7`?
- What does `p + 1` really add in bytes if `p` is `double *`?

### Day 3: Walking `argv` ★
**Concepts:** `char **`, pointer to pointer, NULL-terminated arrays

**Problem:** Print every command-line argument in reverse order, then print each argument reversed character-wise. Do it using only `char **` walking (no `argv[i]` indexing). Finally, compute the total number of bytes across all arguments, including NULLs.

**Starter:**
```c
int main(int argc, char **argv) {
    char **p = argv;
    // TODO: use p and pointer arithmetic only
}
```

**Think about:**
- `argv[argc]` is guaranteed to be what? Use that to iterate without `argc`.
- Are the strings in `argv` modifiable? Are they contiguous in memory? Print addresses to check.
- What does Python's `sys.argv` do for you that C does not?

### Day 4: Swap Pointers, Not Values ★★
**Concepts:** pointer to pointer, output parameters

**Problem:** Implement `void swap_ptrs(char **a, char **b)`. Then implement `int split_in_place(char *s, char sep, char **out, int max)` that replaces each `sep` in `s` with `'\0'` and stores pointers to each piece in `out`. Return the piece count.

**Starter:**
```c
char *x = "left", *y = "right";
swap_ptrs(&x, &y);

char line[] = "a,bb,ccc,,d";
char *parts[8];
int n = split_in_place(line, ',', parts, 8);
```

**Think about:**
- Why does `split_in_place` need a writable array while `x` and `y` can be string literals?
- What happens to the original `line` after splitting? What does `printf("%s", line)` print now?
- How would you handle empty fields such as `,,`?

### Day 5: Function Pointer Dispatch Table ★★
**Concepts:** function pointers, arrays of function pointers, `typedef`

**Problem:** Build a tiny calculator that reads lines like `add 3 4`, `mul 6 7`, `neg 5` and dispatches through a table `{ "add", fn }`. No `if/else` or `switch` chain on the command name; use a table lookup. Support unary and binary ops by giving the table a `nargs` field.

**Starter:**
```c
typedef int (*binop)(int, int);
typedef int (*unop)(int);
struct entry { const char *name; int nargs; void *fn; };  // can you do better than void*?
```

**Think about:**
- Is casting between `void *` and a function pointer legal in ISO C?
- How would you avoid the `void *` by using a union?
- What does `int (*(*f)(int))(double)` declare? Decode it.

### Day 6: `map` and `filter` in C ★★
**Concepts:** callbacks, `void *user_data`

**Problem:** Implement `void map_int(int *a, size_t n, int (*f)(int, void *), void *ctx)` and `size_t filter_int(const int *in, size_t n, int *out, int (*pred)(int, void *), void *ctx)`. Use them to (a) add a runtime offset to every element and (b) keep only multiples of a runtime `k`, where the offset and `k` are passed via `ctx`.

**Starter:**
```c
static int add_offset(int x, void *ctx) { return x + *(int *)ctx; }
```

**Think about:**
- C has no closures. How does `ctx` emulate a captured variable?
- Compare with Python's `map(lambda x: x + k, a)`. What does the lambda's cell object hold?
- Why is the `void *ctx` pattern so common in C libraries (pthreads, signal APIs, GUI toolkits)?

### Day 7: Generic Swap and Max ★★
**Concepts:** `void *`, `size_t`, byte-wise copying

**Problem:** Write `void swap(void *a, void *b, size_t size)` using a byte loop (no `memcpy`, no VLA on the stack larger than a small chunk, no malloc). Then write `void *max_of(void *base, size_t n, size_t size, int (*cmp)(const void *, const void *))`. Test on `int`, `double`, and `char *`.

**Starter:**
```c
void swap(void *a, void *b, size_t size);
void *max_of(void *base, size_t n, size_t size, int (*cmp)(const void *, const void *));
```

**Think about:**
- Why can't you write `*a = *b` with `void *`?
- What happens if `a == b`? What if they overlap partially?
- For `char *` arrays, what exactly is the comparator's `const void *` pointing at?

### Day 8: Write Your Own `qsort` ★★★
**Concepts:** generic code, comparators, pointer arithmetic on `char *`

**Problem:** Implement `void my_sort(void *base, size_t n, size_t size, int (*cmp)(const void *, const void *))` (any algorithm; insertion sort or heapsort is fine). Reuse your Day 7 `swap`. Test by sorting ints ascending, doubles descending, and an array of `struct person` by name then age.

**Starter:**
```c
struct person { char name[16]; int age; };
int by_name_then_age(const void *a, const void *b);
```

**Think about:**
- Why is `return x - y;` in an int comparator dangerous?
- Is `qsort` guaranteed stable? Is your implementation?
- How do you get from `base` to element `i` when you don't know the type?

### Day 9: The Dangling Pointer Trilogy ★★
**Concepts:** lifetime, stack vs heap vs static, AddressSanitizer

**Problem:** This function is broken:
```c
char *make_greeting(const char *name) {
    char buf[64];
    snprintf(buf, sizeof buf, "Hello, %s!", name);
    return buf;
}
```
Fix it three different ways (caller-provided buffer, `malloc`, `static`), and list the trade-offs of each. Run the original under ASan and read the report.

**Think about:**
- Why might the broken version "work" at `-O0` and fail at `-O2`?
- What is the thread-safety problem with the `static` version?
- Who owns and frees the memory in each design?

### Day 10: Use-After-Free Hunt ★★
**Concepts:** use-after-free, poisoning, defensive macros

**Problem:** Write a `FREE(p)` macro that frees `p` and sets it to `NULL`. Then write a program with a deliberate use-after-free and a double-free. Show how ASan reports each. Finally show a case where the `FREE` macro does *not* save you (hint: aliasing).

**Starter:**
```c
#define FREE(p) do { free(p); (p) = NULL; } while (0)
```

**Think about:**
- Why is the `do { } while (0)` wrapper needed?
- If `q = p; FREE(p); *q = 1;` is the bug, what could a smarter tool do?
- Does `free(NULL)` do anything? Does Python have an equivalent hazard?

### Day 11: 2D Arrays: Three Ways ★★
**Concepts:** `int **` vs `int (*)[N]` vs flat array

**Problem:** Implement a matrix transpose for an `R x C` matrix in three representations: (a) `int **` (array of row pointers), (b) `int (*m)[C]` (pointer to array), (c) flat `int *` with manual indexing `m[r*C + c]`. Print `sizeof` and the addresses of successive rows for each to see the layout.

**Think about:**
- Why can't you pass `int a[3][4]` to a function taking `int **`?
- Which representation has the best cache behavior? Which allows ragged rows?
- What does `int (*p)[4]` mean and what is `p + 1` in bytes?

### Day 12: Shapes with a Hand-Built vtable ★★★
**Concepts:** function pointers in structs, polymorphism, struct embedding

**Problem:** Implement `struct Shape { const struct ShapeOps *ops; }` and `struct ShapeOps { double (*area)(const struct Shape *); void (*print)(const struct Shape *); void (*destroy)(struct Shape *); }`. Create `Circle` and `Rect` that embed `Shape` as their *first member*. Store a mix in an array of `Shape *` and call through the vtable.

**Starter:**
```c
struct Circle { struct Shape base; double r; };
```

**Think about:**
- Why must `base` be the first member for the upcast to be safe?
- How does this map onto Python's method resolution and C++'s vtable?
- How would you add a `perimeter` op without breaking existing shapes?

---

## 2. Manual memory management

### Day 13: `malloc`, `calloc`, and Checking Failure ★
**Concepts:** `malloc`/`calloc`/`free`, error handling

**Problem:** Read `n` from `argv[1]`, allocate an `int` array of that size with `malloc`, fill with squares, print. Repeat with `calloc` and print *before* filling to show zeros. Handle `malloc` returning `NULL` and overflow in `n * sizeof(int)`.

**Think about:**
- Why does `calloc(n, size)` guard against overflow in a way `malloc(n * size)` doesn't?
- Is reading `malloc`'d memory before writing defined behavior?
- On Linux, why does `malloc` rarely return `NULL` even for huge sizes (overcommit)?

### Day 14: Your Own Dynamic Array ★★
**Concepts:** amortized growth, `realloc`, opaque structs

**Problem:** Implement `struct IntVec { int *data; size_t len, cap; }` with `iv_init`, `iv_push`, `iv_pop`, `iv_get`, `iv_free`. Grow capacity geometrically. Push 1,000,000 elements and count how many reallocs happened.

**Starter:**
```c
int iv_push(struct IntVec *v, int x);   // returns 0 on success
```

**Think about:**
- Why double instead of adding a constant? What does that do to the total cost?
- After `realloc`, why must you not keep old pointers into `data`?
- What is Python's `list` growth pattern, roughly?

### Day 15: The Safe `realloc` Pattern ★★
**Concepts:** `realloc` failure, leaks, `realloc(NULL, n)`, `realloc(p, 0)`

**Problem:** Show that `p = realloc(p, n);` leaks on failure. Write the safe pattern with a temporary. Then demonstrate what `realloc(NULL, 10)` and `realloc(p, 0)` do on your platform, and why the latter is implementation-defined territory.

**Think about:**
- Does `realloc` always move the block? How can you observe this with pointer prints?
- If it grows in place, is the old pointer still "valid"?
- How would you simulate failure for testing? (Try a wrapper with a counter.)

### Day 16: Leak Hunt with Valgrind ★★
**Concepts:** leaks, ownership, `valgrind`

**Problem:** Write a 60-line program that reads lines into a linked list of heap-allocated strings and then prints them. Deliberately introduce 4 leak types: never freed, freed only the node not the string, early return skipping cleanup, and overwritten pointer. Run valgrind, classify "definitely / indirectly / possibly / still reachable", then fix all four.

**Think about:**
- What is the difference between *definitely lost* and *still reachable*?
- Is a leak at program exit actually harmful? When is it catastrophic?
- Which of your leaks would ASan's LeakSanitizer also catch?

### Day 17: Fixed-Size Memory Pool ★★★
**Concepts:** free list, O(1) alloc/free, intrusive lists

**Problem:** Implement a pool of `N` blocks of `BLOCK_SIZE` bytes carved from one static buffer. `pool_alloc()` and `pool_free(void *)` must be O(1) using an *intrusive free list* (store the next pointer inside the free block itself). No `malloc` at all.

**Starter:**
```c
#define BLOCK_SIZE 32
#define N_BLOCKS 128
static _Alignas(max_align_t) unsigned char arena[BLOCK_SIZE * N_BLOCKS];
void *pool_alloc(void);
void pool_free(void *p);
```

**Think about:**
- Why can the free list be stored *inside* the free blocks?
- How could you detect a `pool_free` of a pointer that didn't come from the pool?
- What are the fragmentation properties of a fixed-block pool compared to `malloc`?

### Day 18: Double-Free Detector ★★★
**Concepts:** allocation tracking, wrappers, `__FILE__`/`__LINE__`

**Problem:** Wrap `malloc`/`free` with macros `MALLOC(n)` and `FREE(p)` that record every live allocation (pointer, size, file, line) in a table. `FREE` must report "double free" or "free of unknown pointer" with location. At exit, print leaks with the line that allocated them.

**Starter:**
```c
#define MALLOC(n) dbg_malloc((n), __FILE__, __LINE__)
#define FREE(p)   dbg_free((p), __FILE__, __LINE__)
```

**Think about:**
- What data structure gives fast lookup by pointer? (Try a small hash table.)
- How is this different from what ASan does at the allocator level?
- How could you use `atexit` to print the leak report?

### Day 19: Buffer Overflow Detection with Canaries ★★★
**Concepts:** guard bytes, heap corruption, red zones

**Problem:** Extend Day 18: allocate `n + 2*G` bytes and place a known pattern (e.g. `0xDEADBEEF...`) in `G` guard bytes before and after the user region. On `FREE`, verify both guards and report which side was overwritten. Write a test that overruns by 1 byte and one that underruns.

**Think about:**
- Why does an off-by-one write often not crash immediately?
- What can't guard bytes catch? (Hint: reads, or writes that skip the guard.)
- How do stack canaries (`-fstack-protector`) work conceptually?

### Day 20: Bump/Arena Allocator ★★
**Concepts:** arenas, alignment, bulk free

**Problem:** Build `struct Arena` over a caller-supplied buffer with `arena_alloc(a, size, align)` and `arena_reset(a)`. Use it to build a 1000-node binary tree, then free everything with a single `arena_reset`. Handle alignment correctly for `double`.

**Think about:**
- How do you round an offset up to a power-of-two alignment using bit tricks?
- What are the use cases where arenas beat `malloc`/`free`? (Parsers, per-request memory.)
- Why can't you free a single object?

### Day 21: Growing String Builder ★★
**Concepts:** `realloc`, `va_list`, formatted append

**Problem:** Implement `struct SB { char *buf; size_t len, cap; }` with `sb_appendf(struct SB *, const char *fmt, ...)` using `vsnprintf` twice (once to measure, once to write). Always keep a trailing NUL. Build a 100 KB string by repeatedly appending.

**Think about:**
- Why call `vsnprintf` twice? What must you do to the `va_list` between calls (`va_copy`)?
- Compare with Python's `str +=` in a loop vs `''.join`.
- How do you avoid O(n^2) behavior?

### Day 22: Leak Tracker with `atexit` ★★
**Concepts:** `atexit`, linked list bookkeeping, macros overriding `malloc`

**Problem:** Using `#define malloc(n) tracked_malloc(...)` in a header, make an existing small program report leaks automatically with no other source changes. Print total bytes leaked and per-site counts.

**Think about:**
- What goes wrong if the macro is defined before `#include <stdlib.h>`?
- Why doesn't this work for libraries compiled without your header? (Compare with `LD_PRELOAD`.)
- What is `__attribute__((malloc))` for?

### Day 23: Generic Vector of Anything ★★★
**Concepts:** `void *`, `elem_size`, byte arithmetic

**Problem:** Generalize Day 14 to `struct Vec { void *data; size_t elem_size, len, cap; }` with `vec_push(v, const void *elem)`, `vec_at(v, i)` returning `void *`, and an optional per-element destructor callback. Test with `int`, `struct point`, and `char *` (strings that must be freed).

**Think about:**
- Why is `vec_at` returning a pointer into the buffer dangerous across a push?
- How could macros give you type safety (`VEC(int)`)?
- Where does alignment matter when `elem_size` is odd?

### Day 24: `aligned_malloc` from `malloc` ★★★
**Concepts:** alignment, hidden headers, pointer/integer casts

**Problem:** Implement `void *aligned_malloc(size_t size, size_t align)` and `aligned_free(void *)` using only `malloc`/`free`. Over-allocate, round the address up to `align`, and stash the original pointer just before the returned address. Verify with `((uintptr_t)p % align) == 0` for align = 16, 64, 4096.

**Think about:**
- Why `uintptr_t` and not `long`?
- How does `free` itself know how big a block is? (Look at what's before the pointer.)
- Compare with `posix_memalign` and C11 `aligned_alloc`.

---

## 3. Bitwise operations

### Day 25: Bit Twiddling Toolkit ★
**Concepts:** set/clear/toggle/test, macros vs inline functions

**Problem:** Write `SET_BIT`, `CLEAR_BIT`, `TOGGLE_BIT`, `TEST_BIT` as macros, then again as `static inline` functions on `uint32_t`. Write a printer that shows a `uint32_t` in binary grouped by 8 bits. Exercise on bit 0, bit 31, and (carefully) shifting by 32.

**Think about:**
- Why should the constant be `1u << n` rather than `1 << n`?
- What does `1 << 31` do for a signed int?
- Why is shifting by >= the type width undefined?

### Day 26: Unix Permission Bits ★★
**Concepts:** bitmasks, flags, enums

**Problem:** Define flags `R=4, W=2, X=1` and pack owner/group/other into a 9-bit mode. Write `void print_mode(unsigned m)` producing `rwxr-xr--`, and `unsigned parse_mode(const char *s)` for the reverse. Support octal input like `0754`. Implement `chmod`-style `mode |= S_IXUSR` operations.

**Think about:**
- Why do flag values need to be distinct powers of two?
- What is the difference between `&` and `&&`, and `|` and `||`, in a flag check?
- How do setuid/setgid/sticky bits fit in?

### Day 27: Counting Set Bits Three Ways ★★
**Concepts:** Kernighan's algorithm, lookup tables, builtins

**Problem:** Implement popcount by (a) shifting all 32 bits, (b) Kernighan (`x &= x - 1`), (c) a 256-entry lookup table built at startup. Compare with `__builtin_popcount`. Benchmark each on 100M random values.

**Think about:**
- Why does `x & (x - 1)` clear the lowest set bit?
- On x86, what instruction does `__builtin_popcount` compile to with `-mpopcnt`?
- Which approach wins for mostly-zero inputs?

### Day 28: XOR Swap and Its Traps ★★
**Concepts:** XOR identities, aliasing

**Problem:** Implement `swap_xor(int *a, int *b)`. Show it fails when `a == b`. Fix it. Then use XOR to find the single non-duplicated element in an array where all others appear twice. Finally, compare the generated assembly of XOR-swap vs temp-swap at `-O2`.

**Think about:**
- Why is the temp-variable swap usually as fast or faster?
- What identities make `a ^ a = 0` and `a ^ 0 = a` useful?
- Does `restrict` change this discussion?

### Day 29: Endianness ★★
**Concepts:** byte order, unions, `htonl`/`ntohl`

**Problem:** Write `int is_little_endian(void)` in two ways (via char pointer, via union). Write `swap32` and `swap64` with shifts and masks only. Then serialize a `uint32_t` into a `uint8_t[4]` in big-endian *without* relying on host order, and read it back.

**Think about:**
- Why is the shift-based serialization endian-independent while a pointer cast isn't?
- When is byte order a concern (network, file formats, hardware registers)?
- What does Python's `int.from_bytes(b, "big")` hide?

### Day 30: Reverse Bits ★★
**Concepts:** shifts, masks, divide-and-conquer

**Problem:** Reverse the bits of a `uint8_t`, then a `uint32_t`, using (a) a loop, (b) the parallel swap method (swap adjacent bits, then pairs, then nibbles, then bytes, then halves). Verify against each other on random inputs.

**Starter:**
```c
x = ((x >> 1) & 0x55555555u) | ((x & 0x55555555u) << 1);
```

**Think about:**
- How many operations does the parallel version use vs. the loop?
- Where would bit-reversal appear in real code (FFT, CRC, bit-banged protocols)?
- What are the magic masks `0x55…`, `0x33…`, `0x0F…` selecting?

### Day 31: Power-of-Two Tricks ★★
**Concepts:** `x & (x-1)`, `x & -x`, rounding

**Problem:** Implement `is_pow2`, `next_pow2`, `round_up(x, align)` for power-of-two `align`, `lowest_set_bit(x)` (isolate with `x & -x`), and `log2_floor`. Test edge cases: 0, 1, `UINT32_MAX`, and 2^31.

**Think about:**
- Why does `x & -x` work in two's complement?
- Why is `round_up` with modulo slower than the mask version?
- What does `next_pow2(0)` mean, and what does your function return?

### Day 32: Bit Array ★★
**Concepts:** packed bitsets, index math

**Problem:** Implement `struct Bitset { uint64_t *w; size_t nbits; }` with `bs_set`, `bs_clear`, `bs_test`, `bs_count`, `bs_first_zero`. Use it for a Sieve of Eratosthenes up to 10 million and compare memory with an `unsigned char[]` sieve.

**Think about:**
- How do you turn a bit index into (word, bit)? Why do `>> 6` and `& 63` beat `/` and `%` at `-O0`?
- What is the memory ratio, and what does it do to cache misses?
- How is this related to Python's `int` as a bitset?

### Day 33: Pack and Unpack Pixels ★★
**Concepts:** masks, shifts, field extraction

**Problem:** Pack an RGB triple into RGB565 (16 bits) and into ARGB8888 (32 bits). Write `unpack` for both, and observe the precision loss in the 565 round trip. Write generic `extract(x, pos, width)` and `insert(x, pos, width, val)` helpers.

**Think about:**
- How do you build a mask of `width` ones without overflow when `width == 32`?
- How does `insert` avoid corrupting neighboring fields?
- Why is masking before shifting different from shifting before masking?

### Day 34: Gray Code, Parity, and Friends ★★
**Concepts:** XOR tricks, folding

**Problem:** Implement `to_gray(n) = n ^ (n >> 1)` and `from_gray`. Print the 4-bit Gray sequence and verify only one bit changes each step. Implement parity of a 32-bit word by folding (`x ^= x >> 16; x ^= x >> 8; ...`). Verify against popcount parity.

**Think about:**
- Why is Gray code used in rotary encoders?
- Why is right shift on a signed negative integer implementation-defined?
- How would you invert Gray code without a loop?

---

## 4. Structs, unions & memory layout

### Day 35: `sizeof` Surprises ★★
**Concepts:** padding, alignment, `offsetof`

**Problem:** Predict `sizeof` and `offsetof` for each member of these, *then* verify:
```c
struct A { char c; int i; char d; };
struct B { int i; char c; char d; };
struct C { char c; double d; char e; };
struct D { char c[3]; short s; long l; };
```
Write a helper that dumps a struct's bytes in hex so you can see the padding. Fill the struct with `memset(0xFF)` first.

**Think about:**
- What determines the alignment of a struct as a whole?
- Why does trailing padding exist? (Think arrays of structs.)
- Is comparing structs with `memcmp` safe?

### Day 36: Shrink the Struct ★★
**Concepts:** member ordering, `#pragma pack`, `__attribute__((packed))`

**Problem:** Take a 12-field struct (mixed `char`, `short`, `int`, `double`, pointers) and (a) reorder to minimize size, (b) pack it, (c) time a loop that sums a field across 10M elements for all three. Then read a packed `int` member via a pointer and discuss what can go wrong.

**Think about:**
- Why can packed structs be slower or even crash on some architectures?
- Why can't you take a normal `int *` to a packed member safely?
- When do you *need* packing (wire formats, file headers)?

### Day 37: Float Bits via Union ★★
**Concepts:** unions, type punning, IEEE 754

**Problem:** Use a `union { float f; uint32_t u; }` to print sign, exponent, and mantissa of a float. Test `1.0f`, `-0.0f`, `0.1f`, infinity, NaN, and a denormal. Then implement `float` to `uint32_t` punning a second way with `memcpy` and a third with pointer cast; explain which is legal.

**Think about:**
- Why is `*(uint32_t *)&f` a strict-aliasing violation?
- Is union punning defined in C? In C++?
- What does Python's `struct.pack('<f', x)` correspond to?

### Day 38: Bit Fields ★★
**Concepts:** bit fields, portability

**Problem:** Define a status register with bit fields: `ready:1, error:1, mode:3, count:11`. Print `sizeof`, set fields, then view the raw bytes via a union. Repeat the same thing with manual mask/shift on a `uint16_t`. Compare the resulting bit layouts.

**Think about:**
- Is the bit order within a byte specified by the standard?
- Why do people avoid bit fields for hardware registers and network protocols?
- What happens when you store 9 in a 3-bit field?

### Day 39: `container_of` ★★★
**Concepts:** `offsetof`, intrusive data structures, pointer casts

**Problem:** Implement `#define container_of(ptr, type, member)`. Use it to build an intrusive doubly-linked list where `struct list_node` is embedded inside `struct task`. Iterate the list and recover the enclosing `struct task *` from each node pointer.

**Starter:**
```c
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))
```

**Think about:**
- Why do intrusive lists avoid a separate allocation per node?
- What breaks if the same node is inserted into two lists?
- This trick is everywhere in the Linux kernel. Why?

### Day 40: Tagged Unions ★★
**Concepts:** variant types, `enum` + `union`

**Problem:** Implement a `Value` type: `NIL, BOOL, INT, DOUBLE, STRING (heap), LIST (array of Value)`. Write constructors, `value_print`, `value_free` (recursive), and `value_equal`. Build `[1, "hi", [2.5, true]]` and print it.

**Think about:**
- What does `sizeof(Value)` equal, and why?
- How does this compare with a Python object header (type pointer + refcount)?
- Who owns a string inside a `Value` when you copy the `Value`?

### Day 41: Manual Serialization ★★
**Concepts:** wire formats, byte order, padding-free layout

**Problem:** Define `struct Msg { uint8_t type; uint16_t len; uint32_t id; char payload[16]; }`. Write `size_t msg_encode(const struct Msg *, uint8_t *buf)` and `int msg_decode(const uint8_t *buf, size_t n, struct Msg *)` using big-endian fields and explicit offsets. Never write the struct directly.

**Think about:**
- Why is `fwrite(&msg, sizeof msg, 1, f)` non-portable?
- How do you defend `msg_decode` against a truncated or hostile buffer?
- Compare with `struct.pack('>BHI16s', ...)` in Python.

### Day 42: Flexible Array Member ★★
**Concepts:** variable-length structs, single allocation

**Problem:** Implement `struct Str { size_t len; char data[]; }` with `Str *str_new(const char *s)`, `str_concat(a, b)`, and `str_free`. Allocate header and data in one `malloc`. Print `sizeof(struct Str)` and explain why it excludes `data`.

**Think about:**
- What is the advantage over `char *data` (one allocation, one free, better locality)?
- Why can't such a struct be an array element or nested in another struct?
- What was the pre-C99 `data[1]` hack, and why is it UB-ish?

### Day 43: Pass by Value vs. by Pointer ★★
**Concepts:** struct copies, ABI, `const`

**Problem:** Create a 4 KB struct. Write `sum_by_value(struct Big b)` and `sum_by_ptr(const struct Big *b)`. Call each 1M times and time them. Look at the `-O0` assembly to see the copy (`objdump -d` or `gcc -S`). Also return a small struct (two `int`s) by value and see whether it fits in registers.

**Think about:**
- How does the System V ABI decide what goes in registers vs. memory?
- When is passing small structs by value actually better?
- Why can `const` help both readability and the optimizer?

### Day 44: Expression Tree Evaluator ★★★
**Concepts:** tagged union, recursion, pointers to structs

**Problem:** Define `struct Expr` as a tagged union: `NUM`, `ADD`, `MUL`, `NEG`, each child being `Expr *`. Build `-(2 + 3 * 4)` by hand, write `eval`, `print_infix`, and `free_expr`. Then add a `VAR` node and an `eval` that takes a lookup callback.

**Think about:**
- What does a `switch` on the tag give you that virtual dispatch doesn't (and vice versa)?
- How do you avoid leaking on partially built trees?
- How would `-Wswitch` help when you add a new tag?

---

## 5. Strings without stdlib

### Day 45: `strlen`, `strcpy`, `strcmp` ★
**Concepts:** NUL-terminated strings, pointer walking

**Problem:** Implement `my_strlen`, `my_strcpy`, `my_strcmp`, each in a single `while` loop using pointer increments. Compare results against libc on random strings, including empty strings.

**Think about:**
- What must `strcmp` return, and why compare as `unsigned char`?
- What happens with `my_strcpy(dst, src)` when `dst` is too small?
- Why is `char s[] = "abc"` different from `char *s = "abc"`?

### Day 46: Safe Concatenation ★★
**Concepts:** bounds, `strncat` pitfalls, truncation

**Problem:** Implement `my_strcat`, then `size_t my_strlcpy(char *dst, const char *src, size_t size)` and `my_strlcat` following the BSD semantics (always NUL-terminate, return the length it *tried* to create). Write a test with truncation and check the return value.

**Think about:**
- Why is `strncpy` considered unsafe despite its name?
- What is the size argument of `strncat` measuring?
- How does the return value help detect truncation?

### Day 47: `strstr` ★★
**Concepts:** substring search, nested loops

**Problem:** Implement `my_strstr(hay, needle)` naively, then implement a Boyer-Moore-Horspool version using a 256-entry skip table. Test on tricky inputs: empty needle, needle longer than haystack, repeated patterns like `"aaaaab"` in `"aaaa…"`.

**Think about:**
- What is the worst-case of the naive algorithm?
- What should `strstr(hay, "")` return?
- Why is the skip table indexed by `unsigned char`?

### Day 48: In-Place Reverse ★
**Concepts:** two-pointer technique

**Problem:** Reverse a string in place with two pointers. Then reverse the *words* in `"the sky is blue"` in place (reverse whole string, then each word). No extra buffer.

**Think about:**
- Why does reversing whole-then-words work?
- Does your code handle multiple spaces? Leading/trailing spaces?
- What about UTF-8 strings? (Reversing bytes breaks multi-byte characters.)

### Day 49: Trim in Place ★★
**Concepts:** modifying vs. returning pointers

**Problem:** Write `char *trim(char *s)` that strips leading and trailing whitespace *in place* and returns a pointer to the first non-space (which may be inside the original buffer). Then write `void trim_shift(char *s)` which shifts the content to the start of the buffer.

**Think about:**
- Why can't you `free` the pointer returned by `trim`?
- Why must `isspace` receive an `unsigned char` cast?
- How do these compare with Python's immutable `s.strip()` (which returns a new string)?

### Day 50: `strtok_r` Clone ★★★
**Concepts:** state, re-entrancy, static buffers

**Problem:** Implement `char *my_strtok_r(char *s, const char *delims, char **save)`. Tokenize `"  a, b;;c  "` with delimiters `" ,;"`. Then show why `strtok` (with static state) breaks when two loops tokenize simultaneously.

**Think about:**
- Why is `strtok` not thread-safe?
- What does the token function do to the input string?
- How does the `save` pointer replace hidden static state?

### Day 51: `sprintf`-lite ★★★
**Concepts:** varargs, formatting, parsing

**Problem:** Implement `int my_snprintf(char *buf, size_t n, const char *fmt, ...)` supporting `%d`, `%u`, `%x`, `%c`, `%s`, `%%`, plus an optional width and `0` flag (e.g. `%05d`). Never write past `n`. Return the would-be length.

**Think about:**
- How does `va_arg` know the type? (It doesn't. Who's responsible?)
- What happens on `%s` with a NULL pointer, and what happens with a mismatched specifier?
- Why is `printf(user_input)` a security bug (format string attack)?

### Day 52: Palindromes and Anagrams ★★
**Concepts:** frequency tables, char classification

**Problem:** Write `is_palindrome(const char *s)` ignoring case and non-alphanumerics using two pointers. Write `is_anagram(a, b)` using a `int count[256]` table. Extend to Unicode-unaware ASCII only and document the limits.

**Think about:**
- Why is a `char` table index of `s[i]` a bug for negative chars?
- What does `tolower` do outside ASCII in the "C" locale?
- What's the complexity compared to sorting both strings?

### Day 53: Run-Length Encoding ★★
**Concepts:** buffers, in-place vs. out-of-place, sizing

**Problem:** Implement `size_t rle_encode(const char *in, char *out, size_t out_cap)` producing `"aaabcc"` → `"a3b1c2"`, and `rle_decode`. Deal with runs longer than 9, and with digits in the input. Decide on an unambiguous format (e.g. count bytes) and document it.

**Think about:**
- What's the worst-case output size relative to input?
- How do you ensure the decoder can't overflow its output?
- When does RLE make data *bigger*?

---

## 6. Arrays & data structures

### Day 54: Stack and Balanced Brackets ★★
**Concepts:** array-backed stack, overflow

**Problem:** Implement a fixed-capacity stack of `char` with `push`, `pop`, `peek`, `is_empty`, returning error codes rather than crashing. Use it to check that `"{[()]}"` is balanced and `"([)]"` is not.

**Think about:**
- Where does the stack pointer live (index vs pointer)?
- What happens on push-when-full? Design error handling.
- How does the call stack use the same idea?

### Day 55: Queue on a Raw Array ★★
**Concepts:** head/tail indices, wraparound

**Problem:** Implement a FIFO queue of `int` with capacity 8 using `head`, `tail`, and a `count`. Show that a naive "shift left on dequeue" is O(n) and the ring version is O(1). Interleave 1M enqueue/dequeue pairs.

**Think about:**
- Why keep `count` instead of inferring empty/full from `head == tail`?
- How do you make wraparound cheap? (Power-of-two capacity and masking.)
- What does Python's `collections.deque` do differently?

### Day 56: Ring Buffer with Overwrite ★★★
**Concepts:** circular buffers, single-producer/single-consumer

**Problem:** Implement a byte ring buffer with `rb_write(buf, data, n)`, `rb_read(buf, out, n)`, and an *overwrite-oldest* mode for logging. Support wraparound copies in two segments. Test with sizes that straddle the end.

**Think about:**
- Why do free-running `head`/`tail` counters with a power-of-two size make the arithmetic easy?
- How can SPSC ring buffers be lock-free (with the right memory ordering)?
- How would you expose contiguous readable regions to avoid copying?

### Day 57: Singly Linked List: Insert, Delete ★★
**Concepts:** pointers to pointers, list surgery

**Problem:** Implement `push_front`, `push_back`, `insert_sorted`, and `delete_value` where `delete_value` uses a `struct Node **` "pointer to link" so there is no special case for the head node. Free everything at the end.

**Starter:**
```c
struct Node { int val; struct Node *next; };
void delete_value(struct Node **head, int v);
```

**Think about:**
- How does the `**` version remove the `if (head->val == v)` special case?
- What's the cost of `push_back` without a tail pointer?
- What happens if you free a node and then read `node->next`?

### Day 58: Reverse a Linked List ★★
**Concepts:** three-pointer technique, recursion

**Problem:** Reverse a singly linked list (a) iteratively with `prev/cur/next`, (b) recursively. Then reverse only nodes `m..n`. Test on lists of length 0, 1, 2, and 1000.

**Think about:**
- What is the stack depth of the recursive version on a million nodes?
- Which pointer is lost if you forget to save `next`?
- Can you do it with one extra pointer only?

### Day 59: Floyd's Cycle Detection ★★★
**Concepts:** tortoise and hare, cycle entry

**Problem:** Build a list with a cycle (tail points to node k). Implement `has_cycle` with slow/fast pointers, then `cycle_start` (reset one pointer to head, move both one step at a time), and compute the cycle length.

**Think about:**
- Why must the two pointers meet inside the cycle?
- Prove (informally) why the second phase finds the start.
- How would you free such a list safely?

### Day 60: Doubly Linked List with Sentinel ★★★
**Concepts:** sentinel nodes, circular lists, invariants

**Problem:** Implement a circular doubly linked list with a sentinel head (`head->next` and `head->prev` point to itself when empty). Provide `insert_after`, `remove`, and `move_to_front`. Use it to build a tiny LRU cache of size 3 (with linear lookup).

**Think about:**
- How does the sentinel remove NULL checks?
- What invariant checks (`assert(n->next->prev == n)`) would catch bugs?
- What do you need to make LRU O(1)? (A hash table.)

### Day 61: Hash Table from Scratch ★★★
**Concepts:** hashing, chaining, collisions

**Problem:** Implement a `string -> int` hash table with fixed 64 buckets using separate chaining. Implement `ht_put`, `ht_get`, `ht_del`. Use djb2 (`h = h * 33 + c`). Insert 10k words and print the longest chain and load factor.

**Think about:**
- What makes a good hash function? What does a bad one do to chain lengths?
- Who owns the key strings, and who frees them?
- How does Python's `dict` differ (open addressing, insertion order, resizing)?

### Day 62: Binary Search by Pointers ★★
**Concepts:** `lower_bound`, off-by-one, overflow

**Problem:** Implement `const int *lower_bound(const int *lo, const int *hi, int key)` returning the first element >= key (or `hi`). Never compute `(lo + hi) / 2`; use `lo + (hi - lo) / 2`, and explain why. Then implement `upper_bound` and use both to count occurrences of a key.

**Think about:**
- Why does the naive midpoint overflow (the famous decades-old bug)?
- What invariant does `[lo, hi)` maintain?
- How does the generic `bsearch` differ?

### Day 63: Quicksort and Mergesort ★★★
**Concepts:** partitioning, temp buffers, pointer ranges

**Problem:** Implement quicksort (Hoare or Lomuto partition, median-of-three pivot) and mergesort (with a single temp buffer) on `int *` ranges. Sort 1M random ints with each and compare with `qsort`. Test on already-sorted, reverse-sorted, and all-equal arrays.

**Think about:**
- What input makes naive quicksort O(n²)?
- Why does mergesort need O(n) space, and can quicksort recurse deep?
- Which is stable? Why does that matter?

### Day 64: Binary Search Tree ★★★
**Concepts:** recursion, pointers to pointers, traversal

**Problem:** Implement BST `insert`, `find`, `delete` (all three cases), `inorder`, `height`, and `free_tree` (post-order). Insert sorted keys and observe degenerate height, then randomize and compare.

**Think about:**
- Why does deletion of a node with two children use the successor?
- How would an iterative inorder traversal look with an explicit stack?
- What extra bookkeeping do AVL/red-black trees add?

### Day 65: Min-Heap Priority Queue ★★★
**Concepts:** implicit tree in an array, sift up/down

**Problem:** Implement a binary min-heap in an `int` array with `heap_push`, `heap_pop`, `heap_peek`, and `heapify` (O(n) build). Use it to heap-sort an array and to merge `k` sorted arrays.

**Think about:**
- How do you compute the parent and children from an index?
- Why is `heapify` O(n) rather than O(n log n)?
- How is this the structure behind Python's `heapq`?

---

## 7. Number representation

### Day 66: Subtract Using Only Add and Bit Flips ★★
**Concepts:** two's complement

**Problem:** Implement `int32_t sub(int32_t a, int32_t b)` using only `~` and `+` (no `-` operator). Implement `negate(x)` as `~x + 1`. Print the 8-bit binary for `5`, `-5`, `127`, `-128` by casting to `uint8_t`. Then implement `add` using only bitwise ops (XOR for sum, AND+shift for carry, in a loop).

**Think about:**
- Why is `-INT_MIN` a problem?
- Why does one negative value have no positive twin?
- How does a hardware adder work, and how is your loop like it?

### Day 67: Overflow: Signed vs. Unsigned ★★
**Concepts:** wraparound, UB, safe arithmetic

**Problem:** Show `UINT_MAX + 1 == 0` (defined) and `INT_MAX + 1` (undefined). Compile the latter at `-O0` and `-O2` and observe that `if (x + 1 < x)` may be optimized away. Write `int safe_add(int a, int b, int *out)` without overflowing, then use `__builtin_add_overflow` and compare.

**Think about:**
- Why does the compiler treat signed overflow as impossible?
- What does `-fwrapv` do, and what does `-ftrapv` do?
- Why did Python avoid this whole class of bugs?

### Day 68: `itoa` in Any Base ★★
**Concepts:** digit extraction, buffer sizing, negatives

**Problem:** Write `char *my_itoa(long long n, char *buf, int base)` for base 2 to 36. Handle 0, negatives (decimal only), and `LLONG_MIN` without overflow. Build digits backwards then reverse.

**Think about:**
- How do you negate `LLONG_MIN` safely? (Use an unsigned type.)
- What size buffer is guaranteed sufficient for base 2?
- How would you write into the buffer from the end to avoid reversing?

### Day 69: `atoi` with Error Handling ★★
**Concepts:** parsing, overflow, `errno`

**Problem:** Implement `int my_strtol(const char *s, long *out, int base)` returning 0 on success, with detection of: leading spaces, sign, no digits, trailing garbage, and overflow past `LONG_MAX/LONG_MIN`. Design the error contract, then compare with libc `strtol`.

**Think about:**
- Why is `atoi` unsafe (no way to distinguish `"0"` from `"abc"`)?
- How do you check `acc * 10 + d` for overflow *before* doing it?
- Which whitespace does `isspace` skip?

### Day 70: Fixed-Point Arithmetic ★★★
**Concepts:** Q16.16, scaling, precision

**Problem:** Implement Q16.16 fixed point in `int32_t`: `from_double`, `to_double`, `fx_add`, `fx_mul` (use a 64-bit intermediate), `fx_div`. Compute a sine table for 256 angles and approximate `sin(x)` by lookup + linear interpolation. Report the max error.

**Think about:**
- Why is multiplication `(a * b) >> 16` and not just `a * b`?
- Where does fixed point still matter (microcontrollers, DSP, games)?
- How does overflow behave, and how can you saturate?

### Day 71: Sign Extension & Integer Promotions ★★
**Concepts:** implicit conversions, `char` signedness

**Problem:** Predict the output of each, then run:
```c
signed char c = -1; unsigned u = c; printf("%u\n", u);
unsigned char b = 200; printf("%d\n", b + b);
if (-1 < 1u) puts("yes"); else puts("no");
uint8_t x = 0xFF; printf("%d\n", (int8_t)x);
size_t n = 3; int i = -1; printf("%d\n", i < n);
```
Explain each in terms of promotion rules.

**Think about:**
- What are the "usual arithmetic conversions"?
- Why is `for (size_t i = n - 1; i >= 0; i--)` an infinite loop?
- Is plain `char` signed? (It depends on the platform.)

### Day 72: Bignum Addition and Multiplication ★★★
**Concepts:** carry propagation, arrays of digits

**Problem:** Write `add_big(const char *a, const char *b, char *out)` for decimal strings and `mul_big` (schoolbook). Compute `2^1000` and `50!` and print all the digits. Try to store digits as base 10^9 in `uint32_t` limbs for a 9x speedup.

**Think about:**
- What is the maximum length of the result?
- How does Python's `int` implement arbitrary precision under the hood (30-bit digits)?
- Why use `uint64_t` for intermediate products?

### Day 73: Floating-Point Pitfalls ★★
**Concepts:** rounding, epsilon, ULPs

**Problem:** Print `0.1 + 0.2` with `%.20f`. Implement `almost_equal(a, b)` with a relative epsilon, then an ULP-based version using integer reinterpretation (`memcpy` to `int64_t`). Sum `0.1` ten million times in `float` and `double` and compare, then try Kahan summation.

**Think about:**
- Why does `0.1` not have an exact binary representation?
- Why doesn't a fixed absolute epsilon work for both tiny and huge values?
- What is `-ffast-math` allowed to break?

---

## 8. Recursion & the call stack

### Day 74: Watch the Stack Grow ★★
**Concepts:** stack frames, addresses, growth direction

**Problem:** Write `void f(int depth)` that prints the address of a local variable at each level (5 levels). Determine the growth direction, the frame size (difference between successive addresses), and see how compilers at `-O0` vs `-O2` change that.

**Think about:**
- What's in a stack frame? (Return address, saved registers, locals, spills.)
- Why is comparing addresses of unrelated locals technically UB, and how do you do it safely (`uintptr_t`)?
- What does the frame pointer register do?

### Day 75: Recursion Flavors ★★
**Concepts:** tail calls, accumulators, optimization

**Problem:** Implement factorial three ways: plain recursive, tail-recursive with an accumulator, and iterative. Compile with `-O0` and `-O2 -S` and inspect the assembly to see whether the tail call became a jump. Do the same for naive `fib(40)` vs. an iterative version.

**Think about:**
- Why can a tail call reuse the current frame?
- Why does Python not do tail-call optimization, and C compilers may?
- Why is naive `fib` exponential, and how do you memoize in C?

### Day 76: Deliberate Stack Overflow ★★
**Concepts:** stack limits, `ulimit`, guard pages

**Problem:** Write an unbounded recursion and find the depth at which it crashes by counting in a `static` variable and printing it in a `SIGSEGV` handler on an alternate stack (`sigaltstack`). Run with `ulimit -s 1024` and `ulimit -s 8192` and compare. Then do it again with big local arrays per frame.

**Think about:**
- How does the OS detect stack overflow (guard page)?
- Why must the handler use an alternate stack?
- What does Python report at recursion depth ~1000, and why does C not have that check?

### Day 77: Backtracking: Permutations and Hanoi ★★
**Concepts:** recursion, in-place swaps, state

**Problem:** Print all permutations of `"abcd"` by swapping in place and backtracking. Solve Towers of Hanoi for `n = 4` printing moves and count total moves. Then generate all subsets of `{1,2,3,4}` with a bitmask loop.

**Think about:**
- What is the recursion depth and what is the number of calls?
- Why must you swap back after the recursive call?
- How do bitmask subsets avoid recursion altogether?

### Day 78: Ackermann and Depth ★★★
**Concepts:** deep recursion, stack budgeting

**Problem:** Implement Ackermann `A(m, n)`. Compute `A(2, 3)` and `A(3, 3)` and track the maximum recursion depth with a global counter. Determine the largest `m, n` that runs without overflowing the default 8 MB stack, and estimate the frame size.

**Think about:**
- Why does depth grow so fast even though values are small?
- How could you convert it to iteration with an explicit stack?
- What does this teach you about worst-case stack usage in embedded code?

### Day 79: Recursion to Iteration ★★★
**Concepts:** explicit stacks, DFS, flood fill

**Problem:** Implement flood fill on a 2D grid (ASCII picture) recursively, then rewrite it with an explicit stack of `(x, y)` pairs stored in a heap array. Demonstrate that the recursive version overflows on a 4000x4000 blank grid while the iterative one doesn't.

**Think about:**
- Why is the explicit stack safer? Where does its memory live?
- How does BFS with a queue differ from DFS here?
- What is the size of the worst-case explicit stack?

---

## 9. Debugging & undefined behavior

### Day 80: Spot the Bug: Uninitialized ★★
**Concepts:** uninitialized reads, indeterminate values

**Problem:** This program "usually works":
```c
int find_first_negative(int *a, int n) {
    int idx;
    for (int i = 0; i < n; i++)
        if (a[i] < 0) { idx = i; break; }
    return idx;
}
```
Find the bug, trigger it, and catch it with `-Wall -Wextra -O2`, MSan (clang), or Valgrind. Then write two more examples of uninitialized bugs (struct padding leaked to a file; an uninitialized pointer).

**Think about:**
- Why do results often *look* deterministic at `-O0`?
- What is "indeterminate value", and why is it worse than "random"?
- What information leaks can padding cause?

### Day 81: Off-by-One Museum ★★
**Concepts:** fencepost errors, bounds, NUL terminators

**Problem:** Find and fix the off-by-one in each of six snippets: `for (i = 0; i <= n; i++)`, `char buf[5] = "hello"`, `malloc(strlen(s))` when copying, `memcpy(dst, src, n + 1)` into `n`, `while (i < n - 1)` with unsigned `n == 0`, and an inclusive/exclusive range mix in binary search. Reproduce each with ASan.

**Think about:**
- Which of these are compile-time detectable? Runtime?
- How do half-open ranges `[begin, end)` reduce fencepost errors?
- Why do off-by-ones often not crash?

### Day 82: Integer Overflow in Size Calculations ★★★
**Concepts:** allocation overflow, security

**Problem:** Write `struct Item *read_items(uint32_t count)` doing `malloc(count * sizeof(struct Item))` where `count = 0x40000001`. Show that the multiplication wraps, the allocation is tiny, and a loop writes far past it. Fix with `calloc`, a checked multiply, or `reallocarray`.

**Think about:**
- Why is this class of bug behind many real CVEs?
- Where does external input enter the size calculation?
- Which size type should you use, and why is `int` wrong?

### Day 83: What Undefined Behavior Really Means ★★★
**Concepts:** UB, optimizer assumptions, "nasal demons"

**Problem:** Write and run these at `-O0` and `-O2`, and read the assembly:
1. `int f(int x) { return x + 1 > x; }`
2. A loop with a signed counter that "overflows" and is optimized into an infinite loop
3. A null-check *after* a dereference being deleted
4. `int a[4]; a[4] = 0` being "optimized" away
5. Reading through a `float *` cast of an `int`

Explain what assumption the optimizer made in each.

**Think about:**
- UB means "the standard imposes no requirements", not "it crashes". What does that allow?
- What is the difference between unspecified, implementation-defined, and undefined?
- Why do tools like UBSan matter more than "it ran fine on my machine"?

### Day 84: Strict Aliasing and Alignment ★★★
**Concepts:** aliasing rules, `restrict`, unaligned access

**Problem:** Show a function `void inc(int *a, float *b)` that the optimizer may reorder because it assumes `a` and `b` don't alias. Compare with `-fno-strict-aliasing`. Then read a `uint32_t` from an odd address in a `char` buffer using a cast (UBSan will complain) and fix with `memcpy`.

**Think about:**
- Which types may legally alias anything? (`char`, `unsigned char`)
- What does `restrict` promise the compiler, and what happens if you lie?
- Why is `memcpy` optimized to a single load on x86?

### Day 85: Sequence Points ★★
**Concepts:** evaluation order, unsequenced modifications

**Problem:** Predict the output of `i = i++ + ++i;`, `a[i] = i++;`, and `printf("%d %d", i++, i++);`. Run under GCC and Clang at `-O0` and `-O2`, and with `-Wsequence-point`. Then rewrite each into well-defined statements.

**Think about:**
- Which operators do guarantee order (`&&`, `||`, `,`, `?:`)?
- Why is the order of function argument evaluation unspecified?
- Why is "it works on my compiler" insufficient?

### Day 86: Sanitizer Bake-Off ★★
**Concepts:** ASan, UBSan, MSan/TSan, Valgrind

**Problem:** Write ONE program with five bugs: heap overflow, stack overflow, use-after-free, signed overflow, and a data race between two threads. Determine which of `-fsanitize=address`, `undefined`, `thread`, and Valgrind detects each one. Fill in a table of tool vs. bug.

**Think about:**
- Why can't ASan and TSan be used together?
- What is the runtime and memory overhead of each?
- Which bugs are invisible to all of them?

### Day 87: Find the Five Bugs ★★★
**Concepts:** code review, mixed defects

**Problem:** Write a 60-line singly linked list program (push, find, remove, print, free) that *looks* correct. Have a friend (or ask Claude) plant five subtle bugs: a leak, a use-after-free, an off-by-one in a loop, an unchecked `malloc`, and a missing `NULL` check. Find all five using only tools and reading. Log how each was detected.

**Think about:**
- Which bug would you have missed without a tool?
- What coding habits (initialize everything, check every return value, own/borrow conventions) prevent each?
- How does a debugger (`gdb`) watchpoint help find who corrupted memory?

---

# Part B: Systems concepts

## 10. Process & memory model

### Day 88: Map the Address Space ★★
**Concepts:** text/data/BSS/heap/stack/mmap

**Problem:** Print addresses of: a function (`main`), a string literal, an initialized global, an uninitialized global, a `static` local, a `malloc`'d block, a huge `malloc` (1 MB+), a local variable, and `environ`. Sort by address and label each segment. Cross-check with `/proc/self/maps` (print it at the end) and `size ./a.out`.

**Think about:**
- Why does a large `malloc` land in a different region than a small one? (mmap threshold.)
- Why do addresses change between runs? (ASLR; try `setarch -R`.)
- Where do string literals live, and why is writing to them a crash?

### Day 89: Stack vs. Heap Trade-offs ★★
**Concepts:** allocation cost, lifetimes, VLAs, `alloca`

**Problem:** Benchmark 10 million allocations of a 64-byte object: stack local, `malloc`/`free`, and pool (Day 17). Then compare a VLA vs `malloc` for a runtime-sized array, and find the size at which the VLA crashes.

**Think about:**
- Why is stack allocation nearly free?
- When does the heap win (size, lifetime, sharing)?
- Why do many coding standards ban VLAs and `alloca`?

### Day 90: Write `getopt` ★★
**Concepts:** `argc/argv`, parsing, state

**Problem:** Write a tiny option parser handling `-v`, `-n 5`, `-n5`, `--name=foo`, and `--` to end options. Support combined short flags (`-abc`). Print errors for unknown options and missing arguments. Compare behavior with the libc `getopt`.

**Think about:**
- What global state does libc `getopt` keep (`optind`, `optarg`), and why is that awkward?
- How do you permute non-option arguments?
- Compare with Python's `argparse` and what it generates for you.

### Day 91: The Environment ★★
**Concepts:** `environ`, `getenv`, `setenv`, inheritance

**Problem:** Print all environment variables by walking `extern char **environ`. Implement your own `my_getenv`. Use `setenv` to add a variable, `fork`/`exec` a child that prints it (`sh -c 'echo $FOO'`), and show that a child can't change the parent's environment.

**Think about:**
- Where in memory does `environ` live? (Just above the stack.)
- Why is `getenv`'s return value not safe to modify?
- What is the security concern with `PATH` and `LD_PRELOAD`?

### Day 92: `fork` and Copy-on-Write ★★
**Concepts:** `fork`, PIDs, memory duplication

**Problem:** Call `fork()` and print PID/PPID in both branches. Have both modify a global and a heap variable and show they don't see each other's changes though the addresses printed look identical. Fork 3 times in a row and predict how many processes exist. Verify by counting lines.

**Think about:**
- Why do parent and child show the same *virtual* address for a variable but different values?
- What is copy-on-write and why does it make `fork` cheap?
- What happens to buffered `printf` output across `fork`? (Try `| cat` vs terminal.)

### Day 93: `fork` + `exec` + `wait` ★★
**Concepts:** process creation, exit codes

**Problem:** Write `int run(char *const argv[])` that forks, `exec`s `argv[0]` with `execvp`, waits, and returns the child's exit code, or `128 + signal` if killed by one. Test with `ls`, a program returning 3, `false`, a nonexistent command (child must `_exit(127)`), and a child that crashes with `SIGSEGV`.

**Think about:**
- Why use `_exit` in the child after a failed `exec`?
- What's the difference among `WIFEXITED`, `WEXITSTATUS`, `WIFSIGNALED`, `WTERMSIG`?
- How is this what `subprocess.run` does?

### Day 94: Zombies ★★
**Concepts:** zombie processes, reaping

**Problem:** Create a child that exits immediately while the parent sleeps 30 seconds. In another terminal, observe `Z` state in `ps aux`. Then fix by calling `wait`. Write a variant that creates 5 zombies and a fix using a `SIGCHLD` handler with `waitpid(-1, ..., WNOHANG)` in a loop.

**Think about:**
- What's a zombie holding onto? (The exit status/process table entry.)
- Why loop `waitpid` in the `SIGCHLD` handler instead of calling it once?
- What does `signal(SIGCHLD, SIG_IGN)` do?

### Day 95: Parallel Sleep Sort with `waitpid` ★★★
**Concepts:** multiple children, ordering

**Problem:** For each number `n` in `argv`, fork a child that sleeps `n` tenths of a second then prints `n`. The parent waits for all with `waitpid`. The output should come out sorted. Then collect exit codes of children (children return `n`, mod 256) in completion order.

**Think about:**
- Why is this a bad sorting algorithm but a good demonstration of scheduling?
- How does the parent know *which* child finished?
- What if there are 10,000 children? (Resource limits.)

### Day 96: Orphans and Daemonization ★★★
**Concepts:** reparenting, `setsid`, double fork

**Problem:** Make a parent exit while its child is still running, and show the child's new `PPID` (1 or a subreaper). Then implement classic daemonization: `fork`, `setsid`, `fork` again, `chdir("/")`, `umask(0)`, close stdio, redirect to `/dev/null`. Have the daemon write a heartbeat to a file.

**Think about:**
- Why fork twice? (So the daemon can't reacquire a controlling terminal.)
- What is a session, a process group, and a controlling terminal?
- Why do modern systems prefer `systemd` services over hand-rolled daemons?

---

## 11. Syscalls, file I/O & IPC

### Day 97: Raw `cat` with `read`/`write` ★★
**Concepts:** file descriptors, partial writes, `errno`

**Problem:** Implement `cat` using only `open`, `read`, `write`, `close`. Handle files given in `argv`, `-` or no args for stdin, and *partial writes* (loop until all bytes are written). Handle `EINTR`. Print `strerror(errno)` for failures.

**Think about:**
- Why can `write` return less than requested?
- What are fds 0, 1, 2? What's the lowest fd `open` returns?
- What does buffered `fread` add on top of `read`?

### Day 98: `cp` and Buffer Size ★★
**Concepts:** syscall overhead, buffering

**Problem:** Write `cp src dst` using `read`/`write` with buffer sizes 1, 64, 4096, 65536, and 1 MB on a 100 MB file. Time each with `clock_gettime`. Redo with `fread`/`fwrite`, and count syscalls with `strace -c`.

**Think about:**
- Why is a 1-byte buffer so slow? What is a syscall's cost?
- Does `fread` with 1-byte reads actually make 1-byte syscalls?
- What do `O_DIRECT` and the page cache have to do with your timings?

### Day 99: Parse a Binary Header ★★★
**Concepts:** binary formats, endianness, `fread`

**Problem:** Write a program that opens a BMP (or ELF) file and parses its header using `fread` into a struct or by manual byte offsets: print signature, width, height, bits per pixel (BMP) or class, endianness, and machine type (ELF). Validate the magic number and every length field.

**Think about:**
- Why is reading directly into a struct fragile (padding, endianness)?
- How do you avoid trusting sizes read from the file?
- What did you do to handle short reads?

### Day 100: Record File with Random Access ★★
**Concepts:** `fseek`/`lseek`, fixed records, in-place update

**Problem:** Store `struct Rec { int32_t id; char name[28]; double score; }` records in a binary file. Implement `add`, `get(index)`, `update(index)`, and `count` using `fseek`/`ftell` (and again using `lseek`/`pread`/`pwrite`). Show the file with `xxd`.

**Think about:**
- Why is a fixed record size handy for random access?
- What happens to data in the padding bytes that gets written to the file?
- Why are `pread`/`pwrite` friendlier to threads?

### Day 101: `dup2` Redirection ★★
**Concepts:** file descriptor table, `dup`, `dup2`

**Problem:** Redirect `stdout` to a file with `open` + `dup2(fd, 1)`, print with `printf`, then restore the original stdout using a saved `dup(1)`. Show what fflush does. Then implement `run_with_stdout_to(file, argv)` that redirects only in the child before `exec`.

**Think about:**
- Why does `printf` output go to the file *after* `dup2` even though your code never changed?
- Why must you `fflush` before switching descriptors?
- What is the difference between an fd and an open file description (shared offsets across `dup`)?

### Day 102: Parent-Child Pipe ★★
**Concepts:** `pipe`, blocking I/O, EOF

**Problem:** Create a pipe, fork, have the child write 5 messages and the parent read and print them. Close unused ends in *both* processes. Demonstrate what happens if the parent forgets to close its write end (hangs). Print the pipe capacity by writing until it blocks (use `O_NONBLOCK`).

**Think about:**
- When does `read` on a pipe return 0?
- What is `SIGPIPE` and when is it raised?
- What's `PIPE_BUF` and why does it matter for atomic writes?

### Day 103: Implement `ls | wc -l` ★★★
**Concepts:** `pipe`, `dup2`, `exec`, closing fds

**Problem:** Without `system()`, construct the pipeline `ls | wc -l` via two children, connected by a pipe with `dup2`. Wait for both. Generalize to `run_pipeline(char ***cmds, int n)` for arbitrary length.

**Think about:**
- Which fds must be closed in each child, and what goes wrong otherwise?
- Which process's exit status is the pipeline's status in a shell?
- How many pipes for N commands?

### Day 104: `mmap` a File ★★
**Concepts:** memory-mapped files, page cache

**Problem:** `mmap` a large text file read-only and count newlines with a simple loop over the mapped memory. Compare time against `read` into a 64 KB buffer. Then `mmap` with `MAP_SHARED` and `PROT_WRITE` and uppercase the whole file in place; check with `cat`.

**Think about:**
- Why is `mmap` not always faster than `read`?
- What happens when you access beyond the file size (SIGBUS)?
- How does the OS load pages lazily, and what does `msync` do?

### Day 105: Shared Memory Between Processes ★★★
**Concepts:** `mmap(MAP_ANONYMOUS | MAP_SHARED)`, fork, synchronization

**Problem:** Map an anonymous shared region containing a counter, fork 4 children, and have each increment the counter 100,000 times. Show lost updates without synchronization. Fix with a process-shared mutex (`PTHREAD_PROCESS_SHARED`) or atomics.

**Think about:**
- Why is `MAP_PRIVATE` useless here?
- Why does an ordinary pthread mutex in shared memory need special attributes?
- Compare with Python's `multiprocessing.Value`/`shared_memory`.

### Day 106: TCP Echo Server ★★★
**Concepts:** sockets, `bind/listen/accept`, byte order

**Problem:** Write a TCP server on port 9000: `socket`, `setsockopt(SO_REUSEADDR)`, `bind`, `listen`, `accept`, then echo bytes back until the client closes. Handle one client at a time. Print the client's IP and port (`inet_ntop`, `ntohs`). Test with `nc localhost 9000`.

**Think about:**
- Why do you need `htons` for the port?
- What does `SO_REUSEADDR` fix?
- What does a `read` returning 0 mean on a socket, and how is that different from -1?

### Day 107: TCP Echo Client ★★
**Concepts:** `connect`, `getaddrinfo`, stream semantics

**Problem:** Write a client that connects via `getaddrinfo`, sends each line from stdin, and prints the echoed reply. Send a 1 MB blob and verify that the same bytes come back, taking care that TCP has no message boundaries: loop on `send` and `recv`.

**Think about:**
- Why can one `send` become several `recv`s (and vice versa)?
- How would you frame messages? (Length prefix vs delimiter.)
- What happens on connecting to a closed port?

### Day 108: Multi-Client Echo with `poll` ★★★
**Concepts:** I/O multiplexing, non-blocking sockets

**Problem:** Rewrite the Day 106 server to handle many clients in one thread using `poll()` on an array of `struct pollfd`. Add new clients on the listening socket's readiness, remove them on close. Test with 100 parallel `nc` sessions.

**Think about:**
- How does `poll` scale compared with `epoll`?
- What if a `write` would block? Do you need per-client output buffers?
- How is this the same event-loop idea behind Python's `asyncio`?

---

## 12. Concurrency & synchronization

### Day 109: Hello, Threads ★★
**Concepts:** `pthread_create/join`, arguments, return values

**Problem:** Spawn 4 threads, each receiving a distinct `struct Arg { int id; int n; }` and returning a heap-allocated result via `pthread_join`. Demonstrate the classic bug of passing `&i` of the loop variable to all threads, then fix it.

**Think about:**
- Why is passing `&i` a race?
- Who frees the return value?
- What is the lifetime of a stack variable vs. a detached thread?

### Day 110: Race Conditions on Purpose ★★
**Concepts:** data races, lost updates

**Problem:** Two threads increment a global `long counter` 1,000,000 times each. Print the total across 10 runs (it will vary). Look at the `counter++` assembly (`load / add / store`). Run with `-fsanitize=thread` and read the report.

**Think about:**
- Why is `counter++` not atomic?
- Why might the bug disappear at `-O2` (register promotion) or with a single core?
- Why does Python's GIL hide many of these bugs?

### Day 111: Mutex vs. Atomic ★★
**Concepts:** `pthread_mutex_t`, C11 atomics, cost

**Problem:** Fix Day 110 (a) with a mutex, (b) with `_Atomic long` and `atomic_fetch_add`, (c) with per-thread counters combined at the end. Time all three with 1, 2, 4, 8 threads.

**Think about:**
- Why is (c) fastest, and what is the cost of sharing a cache line?
- What memory ordering does `atomic_fetch_add` use by default?
- When is a mutex the only right answer?

### Day 112: Bounded Producer/Consumer ★★★
**Concepts:** condition variables, spurious wakeups

**Problem:** Implement a bounded queue (capacity 8) with `pthread_mutex_t`, and two condition variables `not_full` and `not_empty`. Run 2 producers and 3 consumers, transferring 100,000 items with a checksum. Add a clean shutdown protocol (poison pills or a `closed` flag).

**Think about:**
- Why must `pthread_cond_wait` be in a `while` loop?
- Why does the mutex have to be held when calling wait, and what does wait do with it?
- How do you shut down consumers blocked in wait?

### Day 113: Semaphores and Ping-Pong ★★
**Concepts:** `sem_t`, ordering

**Problem:** Two threads print `ping` and `pong` alternately 10 times using two semaphores (each initialized so `ping` goes first). Then implement a counting-semaphore-based limiter allowing at most 3 threads inside a "critical zone" out of 10.

**Think about:**
- How does a semaphore differ from a mutex? (No ownership; can be posted by another thread.)
- What's a binary semaphore vs. a mutex when priority inversion matters?
- What breaks if you initialize both to 1?

### Day 114: Build and Fix a Deadlock ★★★
**Concepts:** lock ordering, `trylock`, `gdb`

**Problem:** Two threads and two mutexes: thread A locks `m1` then `m2`; thread B locks `m2` then `m1`, with a `usleep` in between to make it reliable. Confirm the hang and attach `gdb` (`thread apply all bt`). Fix by (a) global lock ordering, (b) `pthread_mutex_trylock` with backoff.

**Think about:**
- What are the four Coffman conditions and which does each fix break?
- Why is address-ordering a neat way to impose a lock order?
- How does `-fsanitize=thread` report potential lock-order inversions?

### Day 115: Dining Philosophers and RW Locks ★★★
**Concepts:** starvation, `pthread_rwlock_t`

**Problem:** Implement the dining philosophers with 5 threads, first naively (deadlocks), then with an ordering fix or a waiter semaphore (`N-1` seats). Then build a shared table (array + `rwlock`) with many readers and one writer, and measure the read throughput gain vs a plain mutex.

**Think about:**
- Which fix trades off throughput for correctness?
- Can readers starve writers, and vice versa?
- When is an RW lock slower than a mutex?

### Day 116: Minimal Thread Pool ★★★
**Concepts:** work queues, worker lifecycle

**Problem:** Implement a pool of N worker threads pulling `struct Task { void (*fn)(void *); void *arg; }` off a linked-list queue guarded by a mutex + condvar. Provide `pool_submit`, `pool_wait` (until the queue is empty and no tasks are running), and `pool_destroy`. Run 1000 tasks that each compute a prime count.

**Think about:**
- How do you track "in flight" tasks for `pool_wait`?
- What happens to tasks submitted during shutdown?
- Compare with `concurrent.futures.ThreadPoolExecutor`.

### Day 117: Parallel Sum and False Sharing ★★★
**Concepts:** data partitioning, cache lines

**Problem:** Sum a 100M-element array with T threads, each summing a slice into `partial[t]`. First put `partial` in a plain `long[]` (adjacent), then pad each to 64 bytes. Time both with 8 threads and explain the difference.

**Think about:**
- Why do adjacent counters on one cache line slow each other down?
- How would you choose the slice sizes for uneven divisions?
- Why is this not visible in CPython threads?

---

## 13. Signals

### Day 118: Catch `SIGINT` Gracefully ★★
**Concepts:** `sigaction`, `volatile sig_atomic_t`

**Problem:** Run a loop that does work until Ctrl-C. Install a handler with `sigaction` (not `signal`) that only sets a `volatile sig_atomic_t flag`. On exit, print how many iterations ran. Make a second Ctrl-C exit immediately.

**Think about:**
- Why should handlers do as little as possible?
- What's the difference between `signal()` and `sigaction()` regarding portability and `SA_RESTART`?
- Why must the flag be `volatile sig_atomic_t`?

### Day 119: `SIGTERM` Cleanup and `atexit` ★★
**Concepts:** termination, cleanup, `kill`

**Problem:** Write a program that creates a temp file and removes it on normal exit, `SIGINT`, and `SIGTERM`. Test with `kill -TERM`, Ctrl-C, and `kill -KILL`. Explain what can and can't be caught.

**Think about:**
- Why can `SIGKILL` and `SIGSTOP` not be caught?
- What runs on `exit()` vs. `_exit()` vs. a signal death?
- How do you make cleanup robust against crashes (e.g. write to `/tmp` and use `O_TMPFILE` or `unlink` after open)?

### Day 120: Recover from `SIGSEGV` ★★★
**Concepts:** `sigsetjmp/siglongjmp`, faulting instructions

**Problem:** Write `int safe_read(const void *addr, int *out)` that reads from an arbitrary address and returns -1 instead of crashing, by handling `SIGSEGV` and jumping back with `siglongjmp`. Probe `NULL`, a freed page, a valid address, and a `PROT_NONE` mmap page.

**Think about:**
- Why does returning from a `SIGSEGV` handler normally re-fault?
- Is this technique safe in general? (Only for controlled probing.)
- How do GC runtimes and JITs use this trick legitimately?

### Day 121: Blocking and Pending Signals ★★★
**Concepts:** `sigprocmask`, `sigpending`, critical sections

**Problem:** Block `SIGINT` around a critical section with `sigprocmask`. Send yourself `SIGINT` (`raise`) inside it, check `sigpending`, then unblock and see the handler run. Show that multiple pending instances of a standard signal collapse into one.

**Think about:**
- What does the mask look like across `fork` and `exec`?
- How do standard signals differ from real-time signals (queuing)?
- Use `sigsuspend` to avoid the "check flag then sleep" race. Why is that a race?

### Day 122: Async-Signal-Safety ★★★
**Concepts:** reentrancy, `write` vs. `printf`

**Problem:** Write a handler that calls `printf` and `malloc`, and a main loop that does too (heavy). Run for 10 seconds with a `SIGALRM` interval timer every 1 ms and demonstrate deadlocks or corruption. Then fix the handler using only `write(2, ...)` and a self-pipe trick to notify the main loop.

**Think about:**
- Why isn't `printf` async-signal-safe?
- What functions *are* safe (see `man 7 signal-safety`)?
- How does the self-pipe (or `signalfd`) turn a signal into a readable event?

### Day 123: `SIGCHLD`, `alarm`, and Timeouts ★★★
**Concepts:** timers, reaping, running child with timeout

**Problem:** Implement `run_with_timeout(argv, seconds)`: fork/exec the command; if it hasn't finished before the deadline, send `SIGTERM`, wait 1 s, then `SIGKILL`. Use `SIGALRM`/`setitimer` or `sigtimedwait`. Return its status. Test with `sleep 10` and timeout 2.

**Think about:**
- How do you avoid the race between `waitpid` returning and the alarm firing?
- Why kill the process *group* (`kill(-pgid, ...)`) for a shell command?
- How does Python's `subprocess.run(timeout=...)` implement this?

---

## 14. Compilation & linking

### Day 124: Break a Multi-File Project on Purpose ★★
**Concepts:** compile vs. link, undefined/multiple definition

**Problem:** Create `main.c`, `math.c`, `math.h`. Build with `gcc -c` for each, then link. Then deliberately cause: (1) an *undefined reference* (forget to link `math.o`), (2) a *multiple definition* (define a global in the header), (3) a *compile-time* error from a missing prototype, (4) a *type mismatch* between declaration and definition that compiles but crashes. Record the exact error text of each and which stage produced it.

**Think about:**
- What does the preprocessor, the compiler, the assembler, and the linker each do?
- Why can (4) slip through? (C linkage has no type info.)
- Why does putting `int x;` in a header cause trouble, and how do `extern` and `static` change it?

### Day 125: Build a Static Library ★★
**Concepts:** `ar`, object files, link order

**Problem:** Compile `vec.c` and `strutil.c` into `libmini.a` with `ar rcs`. Link a program using `-L. -lmini`. Show that link order matters (`-lmini` *before* the object that needs it fails on some toolchains). Use `nm libmini.a` to see the symbols.

**Think about:**
- How does the linker choose which `.o` from an archive to pull in?
- What does the resulting executable contain compared to using a shared library?
- Why is `-static` binary huge relative to a dynamic one?

### Day 126: Shared Libraries and `dlopen` ★★★
**Concepts:** `-fPIC`, `-shared`, `LD_LIBRARY_PATH`, `dlopen`/`dlsym`

**Problem:** Build `libgreet.so` (`-fPIC -shared`). Link normally and run with `LD_LIBRARY_PATH=.` (and see the "cannot open shared object file" error without it; fix with `-Wl,-rpath,'$ORIGIN'`). Then write a program that loads it at runtime with `dlopen`, `dlsym`, and calls a function pointer. Use `ldd` and `LD_DEBUG=libs`.

**Think about:**
- What is position-independent code and why do shared libs need it?
- What do the PLT and GOT do at the first call to a library function?
- How is `dlopen` how plugins (and Python's C extensions) load?

### Day 127: Header Guards and Include Hell ★★
**Concepts:** include guards, `#pragma once`, forward declarations

**Problem:** Make two headers that include each other (`a.h` needs `struct B`, `b.h` needs `struct A`). Show the "redefinition" error without guards, then the "incomplete type" error with guards. Fix with forward declarations and pointers. Inspect the fully expanded output with `gcc -E`.

**Think about:**
- Why can pointers to incomplete types be used but not values?
- What are the arguments for and against `#pragma once`?
- What is the "include what you use" principle?

### Day 128: Macro Pitfalls ★★
**Concepts:** preprocessor, multiple evaluation, hygiene

**Problem:** Predict and test:
```c
#define SQUARE(x) x * x
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SWAP(a, b) { int t = a; a = b; b = t; }
```
Show `SQUARE(1+2)`, `MAX(i++, j++)`, and `if (c) SWAP(x, y); else ...`. Fix with parentheses, `do { } while (0)`, statement expressions, or `static inline`. Then use `#x` and `##` to write a `TEST_EQ(a, b)` macro that prints expressions and values.

**Think about:**
- What is "double evaluation" and why can it be a security bug?
- Why prefer `static inline` and `const` over macros where possible?
- What does `__VA_ARGS__` allow?

### Day 129: Inspect a Binary ★★
**Concepts:** `nm`, `objdump`, `readelf`, `strings`

**Problem:** Compile a small program with a global, a static, a function, and a string literal. Use `nm` (symbol types T/D/B/R/U), `objdump -d -M intel`, `readelf -S` (sections `.text/.data/.bss/.rodata`), `readelf -h` (entry point), `strings`, and `size`. Map each of your variables to a section. Strip it (`strip`) and see what disappears.

**Think about:**
- What is in `.bss` vs `.data` and why isn't `.bss` stored in the file?
- What does `-g` add? What does `-O2` do to your symbols?
- How does the loader use program headers (`readelf -l`)?

### Day 130: Linkage: `static`, `extern`, `inline` ★★★
**Concepts:** internal/external linkage, visibility, ODR-like rules

**Problem:** Write two `.c` files each defining `static int helper()` and `int shared_counter`. Show the two `helper`s don't collide. Then explore `inline` functions in headers: `inline` (C99 semantics), `static inline`, and `extern inline`, seeing which produce link errors and why. Use `-fvisibility=hidden` and `__attribute__((visibility("default")))` in a shared lib.

**Think about:**
- What is the difference between a declaration and a definition?
- Why does a plain `inline` function in a header need exactly one `extern` definition somewhere?
- Why hide symbols in libraries?

---

## 15. Timing & performance

### Day 131: Which Clock? ★★
**Concepts:** `clock`, `gettimeofday`, `clock_gettime`

**Problem:** Measure the same busy loop with `clock()`, `gettimeofday()`, `clock_gettime(CLOCK_MONOTONIC)`, and `CLOCK_PROCESS_CPUTIME_ID`. Run once with `sleep(1)` in the middle and see which clocks count the sleep. Write `static inline double now(void)` returning seconds as `double`. Estimate the resolution of each.

**Think about:**
- Why is `gettimeofday` not suitable for benchmarks? (It can jump.)
- CPU time vs. wall time: when do they differ?
- Compare with Python's `time.perf_counter()` vs. `time.process_time()`.

### Day 132: Row-Major vs. Column-Major ★★
**Concepts:** cache locality, stride

**Problem:** Sum a 4096x4096 `int` matrix by rows and by columns. Time both, then compute the ratio. Vary the size (256, 1024, 4096) and see where the gap emerges. Use `perf stat -e cache-misses` if available.

**Think about:**
- How is a 2D array laid out in memory in C? (Row-major.)
- Why does stride matter: cache lines (64 B) and prefetching?
- Why does NumPy documentation talk about C-order vs F-order?

### Day 133: `volatile` and the Optimizer ★★★
**Concepts:** dead code elimination, `volatile`, benchmarking traps

**Problem:** Write a benchmark loop whose result is never used and see the compiler delete it at `-O2` (time reads ~0). Prevent it with `volatile`, with an asm barrier (`asm volatile("" : : "r"(x) : "memory")`), and by printing the result. Then write a `while (!flag)` loop with a non-volatile `flag` set by a signal handler and show it hang at `-O2`.

**Think about:**
- What does `volatile` guarantee, and what does it *not* (no atomicity, no ordering across threads)?
- Why is `volatile` the wrong tool for thread communication?
- How do you write reliable microbenchmarks?

### Day 134: Cache-Line and Stride Experiment ★★★
**Concepts:** memory hierarchy, working set size

**Problem:** Allocate a 256 MB array. For strides of 1, 2, 4, ..., 1024 elements, read every stride-th element and measure the time *per access*. Plot (or tabulate) the result and see the jump at 16 ints (64 B) and beyond. Then do a pointer-chasing benchmark over working sets of 4 KB to 512 MB to find your L1/L2/L3 sizes.

**Think about:**
- Why does time per access flatten after the cache line size?
- How does the pointer-chase defeat the hardware prefetcher?
- What do you infer about your CPU's cache sizes?

### Day 135: Branch Prediction and `memcpy` ★★★
**Concepts:** branch misprediction, vectorization, libc tuning

**Problem:** Sum elements >= 128 in an array of 32,768 random bytes, first unsorted then sorted; time both. Rewrite the loop branchlessly (`sum += (x >= 128) * x`) and see the unsorted time fall. Then time a hand-written byte-copy loop vs. an `int64` copy loop vs. `memcpy` for 100 MB.

**Think about:**
- Why does sorting make the loop faster even though it does the same work?
- What does the compiler do at `-O3` (auto-vectorization)? Check with `-fopt-info-vec`.
- Why is libc `memcpy` so much faster than your loop?

---

# Part C: Capstones

Each capstone spans several consecutive days. Keep the same source tree across the days and add tests as you go. Commit after each day.

## Capstone 1: Tiny Bytecode VM / Stack Machine (Days 136-138)

### Day 136: VM Part 1, Instruction Set and Decoder ★★★
**Concepts:** enums, bytecode encoding, `switch` dispatch, `uint8_t` buffers

**Problem:** Design a stack-machine ISA with opcodes `PUSH imm32, POP, ADD, SUB, MUL, DIV, PRINT, HALT`. Encode instructions as a byte array (opcode byte + little-endian operand). Write `struct VM { uint8_t *code; size_t pc; int32_t stack[256]; int sp; }` and a `vm_run` loop with a `switch`. Run `PUSH 2, PUSH 3, ADD, PRINT, HALT`. Add a disassembler that prints one instruction per line.

**Starter:**
```c
enum Op { OP_HALT, OP_PUSH, OP_POP, OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_PRINT };
int vm_run(struct VM *vm);   // returns 0 on success, error code otherwise
```

**Think about:**
- What errors must the VM catch (stack underflow/overflow, division by zero, bad opcode, `pc` out of range)?
- How does this compare with CPython's `dis` output and evaluation loop?
- What is "computed goto" dispatch (`&&label`) and why might it be faster?

### Day 137: VM Part 2, Memory, Comparisons, and Jumps ★★★
**Concepts:** control flow, labels, two-pass assembly

**Problem:** Add `DUP, SWAP, LOAD addr, STORE addr` (a 256-cell data memory), `EQ, LT, GT`, `JMP addr`, `JZ addr`. Write a tiny text assembler (two passes: collect labels, then emit) that turns `loop: ... JZ end ... JMP loop` into bytecode. Write programs: count from 10 down to 1, and sum 1..100.

**Think about:**
- Why does the assembler need two passes (forward references)?
- What must `LOAD`/`STORE` validate to prevent the guest from escaping the VM's memory?
- How could you verify bytecode before running it?

### Day 138: VM Part 3, Calls, Recursion, and a Benchmark ★★★
**Concepts:** call stack, return addresses, performance

**Problem:** Add `CALL addr` and `RET` with a separate return-address stack, and local access relative to a frame base (`LOADL n`, `STOREL n`). Write recursive `fact(10)` and iterative/recursive `fib(30)` in your assembly. Benchmark instructions per second, then try computed-goto dispatch and report the change.

**Think about:**
- Why a separate return stack vs. pushing return addresses on the data stack?
- How would you detect infinite recursion in the guest?
- What optimizations (superinstructions, register VM) reduce dispatch overhead?

---

## Capstone 2: Hash Table with Resizing (Days 139-140)

### Day 139: Open-Addressing Hash Table ★★★
**Concepts:** probing, tombstones, load factor, generic keys

**Problem:** Implement a `char *` to `void *` hash map with open addressing (linear probing). Support `put`, `get`, `del` (with tombstones), `len`, and iteration. Use FNV-1a. Keys are copied (`strdup`-style) and owned by the table. Add statistics: probes per lookup and max probe length.

**Think about:**
- What goes wrong in probing when you delete without a tombstone?
- Why do tombstones eventually require a rehash?
- What is the trade-off between chaining and open addressing regarding cache behavior?

### Day 140: Resizing, Iteration Safety, and Fuzzing ★★★
**Concepts:** rehash, amortized cost, differential testing

**Problem:** Grow to 2x when the load factor exceeds 0.7 (and rehash all live entries, dropping tombstones). Optionally shrink at < 0.15. Add an iterator and decide the semantics for modification during iteration. Write a randomized test that performs 1M random put/get/del operations against a simple reference (linear array) and asserts identical results. Run under ASan/UBSan.

**Think about:**
- Why does resizing keep `put` amortized O(1)?
- Which pointers become invalid after a resize (values? keys? iterators)?
- How does Python's `dict` preserve insertion order?

---

## Capstone 3: Custom `malloc` (Days 141-143)

### Day 141: Allocator Part 1, First-Fit Free List ★★★
**Concepts:** block headers, `sbrk`/`mmap`, alignment

**Problem:** Implement `my_malloc` and `my_free` on top of a big static (or `mmap`'d) arena. Each block has a header `{ size_t size; int free; struct hdr *next; }`. Allocation walks the list for the first free block that fits, or carves new space from the arena. Payloads must be 16-byte aligned. Write a heap dumper that prints every block.

**Think about:**
- Why must the header size preserve alignment?
- What does the dumper reveal about fragmentation after a mixed workload?
- How could `free` verify a pointer is valid?

### Day 142: Allocator Part 2, Splitting and Coalescing ★★★
**Concepts:** block splitting, boundary tags, fragmentation

**Problem:** Split large free blocks when serving a small request (if the remainder can hold a header + minimum payload). On `free`, coalesce with the next block, and (using a footer or a `prev` pointer) with the previous block. Write a stress test that does 100k random alloc/free operations and confirms that after freeing everything the heap is a single free block again.

**Think about:**
- What are internal vs. external fragmentation?
- How do boundary tags allow O(1) coalescing in both directions?
- How do first-fit, best-fit, and next-fit differ in behavior?

### Day 143: Allocator Part 3, `calloc`, `realloc`, and Testing ★★★
**Concepts:** API completeness, in-place growth, differential testing

**Problem:** Add `my_calloc` (with overflow check) and `my_realloc` (grow in place if the next block is free and large enough, else allocate/copy/free; shrink by splitting). Fill every allocation with a pattern and verify it never changes under random operations. Optionally add size-class bins for speed, thread safety with a global mutex, and preload it as the system `malloc` with `LD_PRELOAD` on a small program.

**Think about:**
- What are the semantics of `realloc(NULL, n)` and `realloc(p, 0)`?
- How does glibc's ptmalloc mitigate contention (per-thread arenas)?
- What breaks if your allocator calls `printf` (which calls `malloc`)?

---

## Capstone 4: Mini Shell (Days 144-146)

### Day 144: Shell Part 1, Read, Parse, Execute ★★★
**Concepts:** tokenizing, `fork/exec/wait`, built-ins

**Problem:** Write a REPL that prints a prompt, reads a line (`getline`), tokenizes it respecting single and double quotes, and runs the command with `fork`/`execvp`/`waitpid`. Implement built-ins `cd`, `exit`, and `pwd` (they must run in the shell process itself). Print the exit status of the last command (`$?`-like).

**Think about:**
- Why can't `cd` be an external program?
- How do you handle EOF (Ctrl-D) and empty lines?
- What should happen when `execvp` fails in the child?

### Day 145: Shell Part 2, Redirection and Pipelines ★★★
**Concepts:** `dup2`, pipes, multiple children

**Problem:** Support `<`, `>`, `>>`, `2>`, and pipelines `a | b | c`. Parse into `struct Command { char **argv; char *in, *out; int append; }` and `struct Pipeline { Command *cmds; int n; }`. Wire up pipes with `dup2`, close every unused fd, and wait for all children. Test with `ls -l | grep c | wc -l > out.txt`.

**Think about:**
- What's the fd-leak symptom when a pipe write end stays open (the reader never sees EOF)?
- In what order are redirections applied vs. pipe setup?
- How would you handle a syntax error like `| ls` or `ls >`?

### Day 146: Shell Part 3, Signals and Background Jobs ★★★
**Concepts:** process groups, `SIGINT` handling, `SIGCHLD`, `&`

**Problem:** The shell must survive Ctrl-C (ignore `SIGINT`) while foreground children die from it. Support `cmd &` background jobs, reap them via a `SIGCHLD` handler and print `[1]+ Done`. Put each pipeline in its own process group (`setpgid`) and give it the terminal (`tcsetpgrp`). Add a `jobs` built-in.

**Think about:**
- Why must both parent and child call `setpgid` (race)?
- What does the terminal do with Ctrl-C and to which process group?
- How would you implement `fg`, `bg`, and Ctrl-Z (`SIGTSTP`)?

---

## Capstone 5: Multi-Threaded TCP Echo Server (Days 147-150)

### Day 147: Echo Server Part 1, Thread per Connection ★★★
**Concepts:** `accept` loop, detached threads, per-connection state

**Problem:** Build on Day 106: for each `accept`, allocate a `struct Conn { int fd; struct sockaddr_in peer; }` on the heap, spawn a detached thread that echoes until EOF, then closes the fd and frees the struct. Log connects/disconnects with timestamps. Test with 50 parallel `nc` clients.

**Think about:**
- Who owns the `Conn` struct, and when is it freed?
- What happens to `SIGPIPE` when a client disconnects mid-write? (`MSG_NOSIGNAL` or ignore it.)
- What resource limits (threads, fds) will you hit first?

### Day 148: Echo Server Part 2, Thread Pool and Backpressure ★★★
**Concepts:** bounded queues, connection limits

**Problem:** Replace thread-per-connection with a fixed pool of 8 workers fed by a bounded queue of accepted fds (reuse Day 112/116). When the queue is full, either block the acceptor or reject with a "server busy" message and close. Add an idle timeout (`SO_RCVTIMEO` or `poll` with timeout).

**Think about:**
- Which is better under overload: rejecting or queueing? Why?
- What happens to a worker blocked on one slow client, and how could `poll` per worker help?
- How does this differ from an event-loop design (Day 108)?

### Day 149: Echo Server Part 3, Graceful Shutdown ★★★
**Concepts:** signal + threads, `pthread_sigmask`, draining

**Problem:** On `SIGINT`/`SIGTERM`, stop accepting, let active connections finish (up to 5 seconds), then exit cleanly with all threads joined and no leaks (check with ASan/Valgrind). Block signals in workers and handle them in one thread (or use `signalfd`/self-pipe) so the acceptor's `accept` wakes up reliably.

**Think about:**
- Which thread receives a process-directed signal?
- How do you wake threads blocked in `accept`/`read` (`shutdown(fd, SHUT_RDWR)`, closing, or a self-pipe)?
- What's the "close-while-another-thread-uses-the-fd" hazard?

### Day 150: Echo Server Part 4, Metrics, Stress, and Review ★★★
**Concepts:** atomics, load testing, retrospective

**Problem:** Add `_Atomic` counters (connections, bytes in/out, active) and a `SIGUSR1` handler (via the self-pipe) that prints them. Write a stress client that opens 500 connections and sends random data with checksums to verify byte-for-byte echo. Run under TSan and ASan, fix what they find, and measure throughput with 1, 4, and 8 workers. Finally, write a one-page retrospective: which of the 150 puzzles taught you the most, and which topics do you want to redo?

**Think about:**
- Which counters need atomics vs. which can be per-thread and summed?
- Where are your remaining races and leaks, and what would find them?
- What would you change to scale to 10,000 connections? (`epoll`, non-blocking I/O, sharded accept.)

---

## Suggested Review Schedule

- **Every 10th day:** redo one earlier puzzle from memory without looking at your solution.
- **Every 30th day:** re-read your notes on "Think about" questions and try answering out loud.
- **Keep a bug log:** every crash, sanitizer report, or surprising output goes in a file with cause and fix. It's the most valuable output of this whole exercise.

## Handy Reference

| Need | Tool |
|---|---|
| Memory errors | `-fsanitize=address`, `valgrind` |
| UB detection | `-fsanitize=undefined` |
| Data races | `-fsanitize=thread` |
| Syscall tracing | `strace -f -tt`, `strace -c` |
| Library calls | `ltrace` |
| Debugging | `gdb ./a.out` (`bt`, `watch`, `x/16xb`, `info proc mappings`) |
| Assembly | `gcc -S -O2`, `objdump -d -M intel` |
| Symbols/sections | `nm`, `readelf -a`, `size` |
| Perf counters | `perf stat`, `perf record` |
| Network | `nc`, `ss -tnp`, `tcpdump` |
