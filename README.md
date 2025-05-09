![image](https://github.com/R0STUS/bvm-compiler/BRASS.svg)

# LANGUAGE DOCUMENTATION, SOLDIER!

Now listen up, I’m gonna tell you everything there is about the language, SOLDIER:

## PHILOSOPHY

**"Code like a soldier!"**

This language is made for those who are TOO ABSTRACT to code in Assembly,  
but still find C UNFIT for the mission.

The language is NOT IMPERATIVE (yet) due to TEMPORARY RESTRICTIONS.

It's designed for LOW-LEVEL BYTE MANIPULATION — THAT'S WHY YOU WON’T FIND  
ANY `SIGNED` OR `UNSIGNED` HERE, SOLDIER!

**TYPING ENDS AT BYTE COUNT. NO STRONG TYPING!**  
I’M NOT YOUR DAMN BABYSITTER!

Name of this programming language: B.R.A.S.S.
It means **BATTLEFILED-REGULATED ASSEMBLY SUBTITUTE SYNTAX**.

---

## TECHNICALS

- Uses `nasm` in the Linux compiler version.
- The assembler compiler will be INTEGRATED later.
- The original compiler uses STATIC BUILD ONLY.

---

## SYNTAX RULES, SOLDIER

Lines beginning with `+` declare something.  
A line is EVERYTHING from one semicolon to the next!

Lines beginning with `-` operate on what’s already declared.

### Examples:

```

// Variable declaration — 4 bytes:
+var_name [{4}];

// Reference declaration — 4 bytes:
+var_name [{4}&];

// Pointer declaration — 4 bytes, pointer level 4:
+var_name [{4}*[4]];

// Array declaration — 4-byte elements, unknown count:
+var_name [{4}[]];

```

> DECLARATION AND ASSIGNMENT ARE DIFFERENT PROCESSES, SOLDIER!  
> THEY SHOULD NEVER CROSS PATHS!  
> WRONG: `+var_name [{1}] = 1;` — THIS IS ILLEGAL, SOLDIER!

---

### Assignment Examples:

```

// Assign var2 to var1
-var1 = -var2;

// Assign dereferenced pointer var2 to var1
-var1 = -*[0]var2;

// Assign address of var2 to var1
-var1 = -&var2;

````

---

## POINTER DEREFERENCING EXAMPLE

```bvm
#include <io> std;
#include <defined_calls> std;

+main() {
    +a [{4}]; -a = 0;
    +b [{4}*[0]]; -b = -&a;
    +c [{4}*[1]]; -c = -&b;
    -a = 10;
    -print("%d", {-*[1]c}); /* YES, THIS FUNCTION MIGHT NOT EVEN EXIST YET, OR MIGHT DO SOMETHING ELSE! LANGUAGE IS IN DEVELOPMENT, DON'T GET COCKY! */
    syscall(exit, 0);
}
````

---

## C++ EQUIVALENT

```cpp
#include <iostream>

int main() {
    int a = 0;
    int* b = &a;
    int** c = &b;
    a = 10;
    std::cout << **c;
    return 0;
}
```

---

## FINAL NOTE, SOLDIER

This language ain't for kids.
No sugar. No safety. No hand-holding.
This is **raw byte-level coding**.

You don’t ask questions — you read memory.
You don’t complain — you trace bugs.
You don’t type `std::` — YOU WRITE YOUR OWN DAMN I/O.

**LANGUAGE IN DEVELOPMENT — EXPECT NOTHING, FIX EVERYTHING.**
