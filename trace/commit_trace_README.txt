- Cài đặt syscall trace:

1) Makefile:
- thêm  $U/_trace (dòng 197)

2) kernel/syscall.h:
- thêm #define SYS_trace 22

3) kernel/proc.h:
struct proc {
  - thêm int tracemask (dòng 107);
}

4) kernel/sysproc.c:
- thêm hàm sys_trace(). (dòng 95 - 103)

5) kernel/syscall.c:
- thêm extern uint64 sys_trace(void) (dòng 104)
- trong static uint 64:
	+ thêm [SYS_trace]  sys_trace (dòng 129)
- dòng 132 - 155: thêm mảng gọi lệnh
- thêm điều kiện check  (dòng 169 -> 171)

6) kernel/proc.c: 
- thêm np->tracemask = p->tracemask; (dòng 300).

7) user/usys.pl:
thêm entry("trace") (dòng 39)

8) user/user.h:

//system calls
- thêm int trace(int mask) (dòng 25).

9) user/trace.c:
thêm hàm trace.
