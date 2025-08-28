+_start label;
    +str .data 1 = "Hello, World!\n";
    -rax = 1;
    -rdi = 1;
    -rsi = -str;
    -rdx = 15;
    syscall;
    -rax = 60;
    -rdi xor -rdi;
    syscall;

