/* FPU control word bits.  OpenRISC version.
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
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _FPU_CONTROL_H
#define _FPU_CONTROL_H

#if !defined(__or1k_hard_float__)

# define _FPU_RESERVED 0xffffffff
# define _FPU_DEFAULT  0x00000000
typedef unsigned int fpu_control_t;
# define _FPU_GETCW(cw) (cw) = 0
# define _FPU_SETCW(cw) (void) (cw)
extern fpu_control_t __fpu_control;

#else /* __or1k_hard_float__ */

# define _FPU_RESERVED 0xfffff000
# define _FPU_DEFAULT  0
# define _FPU_IEEE     1          /* FPU traps enabled.  */

/* Type of the control word.  */
typedef unsigned int fpu_control_t;

/* Macros for accessing the hardware control word.  */
# define _FPU_GETCW(cw) __asm__ volatile ("l.mfspr %0,r0,20" : "=r" (cw))
# define _FPU_SETCW(cw) __asm__ volatile ("l.mtspr r0,%0,20" : : "r" (cw))

/* Default control word set at startup.  */
extern fpu_control_t __fpu_control;

#endif

#endif	/* fpu_control.h */
