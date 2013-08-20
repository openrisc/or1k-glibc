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
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <stdarg.h>
#include <sysdep.h>

/* or1k ABI uses stack for varargs, syscall uses registers.
 * This function moves from varargs to regs. */
int
__prctl (int __option, ...)
{
  va_list ap;
  unsigned long arg2;
  unsigned long arg3;
  unsigned long arg4;
  unsigned long arg5;

  va_start (ap, __option);
  arg2 = va_arg (ap, unsigned long);
  arg3 = va_arg (ap, unsigned long);
  arg4 = va_arg (ap, unsigned long);
  arg5 = va_arg (ap, unsigned long);
  va_end (ap);

  return INLINE_SYSCALL (prctl, 5, __option, arg2, arg3, arg4, arg5);
}
weak_alias (__prctl, prctl)
