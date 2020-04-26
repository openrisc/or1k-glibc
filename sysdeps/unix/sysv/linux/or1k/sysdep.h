/* Copyright (C) 2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#include <asm/unistd.h>
#include <sysdeps/or1k/sysdep.h>
#include <sysdeps/unix/sysv/linux/generic/sysdep.h>
#include <sys/syscall.h>

#undef SYS_ify
#define SYS_ify(syscall_name)   (__NR_##syscall_name)

/* Linux uses a negative return value to indicate syscall errors,
   unlike most Unices, which use the condition codes' carry flag.

   Since version 2.1 the return value of a system call might be
   negative even if the call succeeded.  E.g., the `lseek' system call
   might return a large offset.  Therefore we must not anymore test
   for < 0, but test for a real error by making sure the value in R0
   is a real error number.  Linus said he will make sure the no syscall
   returns a value in -1 .. -4095 as a valid result so we can safely
   test with -4095.  */

#ifdef __ASSEMBLER__

/* Macros used in syscall-template.S */
#define ret          l.jr r9; l.nop
#define ret_NOERRNO  l.jr r9; l.nop

#undef	DO_CALL
#define DO_CALL(syscall_name) \
  l.addi r11, r0, SYS_ify (syscall_name); \
  l.sys 1; \
   l.nop

#undef	PSEUDO
#define PSEUDO(name, syscall_name, args) \
  ENTRY (name); \
  DO_CALL(syscall_name); \
  /* if -4096 < ret < 0 holds, it's an error */ \
  l.sfgeui r11, 0xf001; \
  l.bf L(pseudo_end); \
   l.nop

#undef	PSEUDO_NOERRNO
#define PSEUDO_NOERRNO(name, syscall_name, args)  \
  ENTRY (name);           \
  DO_CALL(syscall_name)

#undef	PSEUDO_END
#define PSEUDO_END(name) \
L(pseudo_end): \
  l.j SYSCALL_ERROR_NAME; \
  l.ori r3,r11,0; \
  END (name)

#undef	PSEUDO_END_NOERRNO
#define PSEUDO_END_NOERRNO(name) \
  END (name)

#ifndef PIC
/* For static code, on error jump to __syscall_error directly. */
# define SYSCALL_ERROR_NAME __syscall_error
#elif !IS_IN (libc)
/* Use the internal name for libc/libpthread shared objects. */
# define SYSCALL_ERROR_NAME __GI___syscall_error
#else
/* Otherwise, on error do a full PLT jump. */
# define SYSCALL_ERROR_NAME plt(__syscall_error)
#endif

#else /* not __ASSEMBLER__ */

#include <errno.h>

extern long int __syscall_error (long int neg_errno);

/* Pointer mangling is not yet supported for or1k.
 * TODO: Implement pointer guards */
#define PTR_MANGLE(var) (void) (var)
#define PTR_DEMANGLE(var) (void) (var)

#undef INLINE_SYSCALL
#define INLINE_SYSCALL(name, nr, args...) \
        ({                                                                     \
         unsigned int resultvar = INTERNAL_SYSCALL (name, , nr, args);         \
         if (__builtin_expect (INTERNAL_SYSCALL_ERROR_P (resultvar, ), 0))     \
           {                                                                   \
             __set_errno (INTERNAL_SYSCALL_ERRNO (resultvar, ));               \
             resultvar = 0xffffffff;                                           \
           }                                                                   \
         (int) resultvar; })

#undef INTERNAL_SYSCALL
#define INTERNAL_SYSCALL(name, err, nr, args...) \
	INTERNAL_SYSCALL_NCS (SYS_ify (name), err, nr, args)

/* The _NCS variant allows non-constant syscall numbers.  */
#undef INTERNAL_SYSCALL_NCS
#define INTERNAL_SYSCALL_NCS(number, err, nr, args...) \
        ({ unsigned long __sys_result;                                         \
          {                                                                    \
            long _sc_ret = (long) number;                                      \
            LOAD_ARGS_##nr (args)                                              \
            register long __sc_ret __asm__ ("r11") = _sc_ret;                  \
            __asm__ __volatile__ ("l.sys 1\n\t"                                \
				  " l.nop\n\t"                                 \
                                  : "+r" (__sc_ret)                            \
                                  : ASM_ARGS_##nr                              \
                                  : ASM_CLOBBERS_##nr                          \
                                    "r12", "r13", "r15", "r17", "r19",         \
                                    "r21", "r23", "r25", "r27", "r29",         \
                                    "r31", "memory");                          \
            __sys_result = __sc_ret;                                           \
          }                                                                    \
          (long) __sys_result; })

/* INTERNAL_SYSCALL_DECL - Allows us to setup some function static
   value to use within the context of the syscall.

   We do not use it */
#undef INTERNAL_SYSCALL_DECL
#define INTERNAL_SYSCALL_DECL(err) do { } while (0)

/* INTERNAL_SYSCALL_ERROR_P - Returns 0 if it wasn't an error, 1 otherwise
   You are allowed to use the syscall result (val) and the DECL error
   variable to determine what went wrong. */
#undef INTERNAL_SYSCALL_ERROR_P
#define INTERNAL_SYSCALL_ERROR_P(val, err) \
    ((unsigned int) (val) >= 0xfffff001u)


/* INTERLAL_SYSCALL_ERRNO - Munges the val/err pair into the error number.
   In our case we just flip the sign. */
#undef INTERNAL_SYSCALL_ERRNO
#define INTERNAL_SYSCALL_ERRNO(val, err)        (-(val))

/* From here on we have nested macros that generate code for
 * storing arguments to the syscall */

#define LOAD_ARGS_0()

#define ASM_ARGS_0
#define ASM_CLOBBERS_0  "r3", ASM_CLOBBERS_1

#define LOAD_ARGS_1(a) \
  long _a = (long)(a);                                      \
  register long __a __asm__ ("r3") = _a;
#define ASM_ARGS_1 "r" (__a)
#define ASM_CLOBBERS_1  "r4", ASM_CLOBBERS_2

#define LOAD_ARGS_2(a, b) \
  long _b = (long)(b);                                     \
  LOAD_ARGS_1 (a)                                          \
  register long __b __asm__ ("r4") = _b;
#define ASM_ARGS_2 ASM_ARGS_1, "r" (__b)
#define ASM_CLOBBERS_2  "r5", ASM_CLOBBERS_3

#define LOAD_ARGS_3(a, b, c) \
  long _c = (long)(c);                                     \
  LOAD_ARGS_2 (a, b)                                       \
  register long __c __asm__ ("r5") = _c;
#define ASM_ARGS_3 ASM_ARGS_2, "r" (__c)
#define ASM_CLOBBERS_3  "r6", ASM_CLOBBERS_4

#define LOAD_ARGS_4(a, b, c, d) \
    LOAD_ARGS_3 (a, b, c)                                  \
  long _d = (long)(d);                                     \
  register long __d __asm__ ("r6") = _d;
#define ASM_ARGS_4 ASM_ARGS_3, "r" (__d)
#define ASM_CLOBBERS_4  "r7", ASM_CLOBBERS_5

#define LOAD_ARGS_5(a, b, c, d, e) \
  long _e = (long)(e);                                     \
  LOAD_ARGS_4 (a, b, c, d)                                 \
  register long __e __asm__ ("r7") = _e;
#define ASM_ARGS_5 ASM_ARGS_4, "r" (__e)
#define ASM_CLOBBERS_5  "r8", ASM_CLOBBERS_6

#define LOAD_ARGS_6(a, b, c, d, e, f) \
  long _f = (long)(f);                                     \
  LOAD_ARGS_5 (a, b, c, d, e)                              \
  register long __f __asm__ ("r8") = _f;
#define ASM_ARGS_6 ASM_ARGS_5, "r" (__f)
#define ASM_CLOBBERS_6

#endif
