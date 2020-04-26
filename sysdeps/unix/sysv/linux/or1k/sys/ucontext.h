/* ucontext_t definition, OpenRISC version.
   Copyright (C) 2020 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/* System V/OpenRISC compliant context switching support.  */

#ifndef _SYS_UCONTEXT_H
#define _SYS_UCONTEXT_H	1

#include <features.h>

#include <bits/types/sigset_t.h>
#include <bits/types/stack_t.h>


/* Context to describe whole processor state.  */
typedef struct
  {
    unsigned long __gprs[32];
  } mcontext_t;

/* Userlevel context.  */
typedef struct ucontext_t
  {
    unsigned long __uc_flags;    /* getcontext() 1, ... */
    struct ucontext_t *uc_link;  /* user setup before makecontext () */
    stack_t uc_stack;            /* user setup before make context() */
    mcontext_t uc_mcontext;      /* getcontext() regs, v2    : makecontext() func, sp, RA=__startcontext, args injected */
    sigset_t uc_sigmask;         /* getcontext() sigprocmask : */
  } ucontext_t;

#endif /* sys/ucontext.h */
