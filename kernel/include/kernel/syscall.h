#ifndef _KERNEL_SYSCALL_H
#define _KERNEL_SYSCALL_H

#include <vga/vga.h>

#define DECLARE_SYSCALL0(fn) int syscall_##fn();
#define DECLARE_SYSCALL1(fn, p1) int syscall_##fn(p1);
#define DECLARE_SYSCALL2(fn, p1, p2) int syscall_##fn(p1, p2);
#define DECLARE_SYSCALL3(fn, p1, p2, p3) int syscall_##fn(p1, p2, p3);
#define DECLARE_SYSCALL4(fn, p1, p2, p3, p4) int syscall_##fn(p1, p2, p3, p4);
#define DECLARE_SYSCALL5(fn, p1, p2, p3, p4, p5)                               \
  int syscall_##fn(p1, p2, p3, p4, p5);

#define DEFINE_SYSCALL0(fn, num)                                               \
  int syscall_##fn() {                                                         \
    int a;                                                                     \
    asm volatile("int $0x80" : "=a"(a) : "0"(num));                            \
    return a;                                                                  \
  }

#define DEFINE_SYSCALL1(fn, num, P1)                                           \
  int syscall_##fn(P1 p1) {                                                    \
    int a;                                                                     \
    asm volatile("int $0x80" : "=a"(a) : "0"(num), "b"((int)p1));              \
    return a;                                                                  \
  }

#define DEFINE_SYSCALL2(fn, num, P1, P2)                                       \
  int syscall_##fn(P1 p1, P2 p2) {                                             \
    int a;                                                                     \
    asm volatile("int $0x80"                                                   \
                 : "=a"(a)                                                     \
                 : "0"(num), "b"((int)p1), "c"((int)p2));                      \
    return a;                                                                  \
  }

#define DEFINE_SYSCALL3(fn, num, P1, P2, P3)                                   \
  int syscall_##fn(P1 p1, P2 p2, P3 p3) {                                      \
    int a;                                                                     \
    asm volatile("int $0x80"                                                   \
                 : "=a"(a)                                                     \
                 : "0"(num), "b"((int)p1), "c"((int)p2), "d"((int)p3));        \
    return a;                                                                  \
  }

#define DEFINE_SYSCALL4(fn, num, P1, P2, P3, P4)                               \
  int syscall_##fn(P1 p1, P2 p2, P3 p3, P4 p4) {                               \
    int a;                                                                     \
    asm volatile("int $0x80"                                                   \
                 : "=a"(a)                                                     \
                 : "0"(num), "b"((int)p1), "c"((int)p2), "d"((int)p3),         \
                   "S"((int)p4));                                              \
    return a;                                                                  \
  }

#define DEFINE_SYSCALL5(fn, num)                                               \
  int syscall_##fn(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) {                        \
    int a;                                                                     \
    asm volatile("int $0x80"                                                   \
                 : "=a"(a)                                                     \
                 : "0"(num), "b"((int)p1), "c"((int)p2), "d"((int)p3),         \
                   "S"((int)p4), "D"((int)p5));                                \
    return a;                                                                  \
  }

DECLARE_SYSCALL1(writestr, const char *)
DECLARE_SYSCALL1(writehex, const char *)
DECLARE_SYSCALL1(writeint, const char *)

void init_syscalls();

#endif //_KERNEL_SYSCALL_H
