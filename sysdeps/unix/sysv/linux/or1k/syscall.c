/* System call interface.  OpenRISC version.
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
   <https://www.gnu.org/licenses/>.  */

#include <sysdep.h>
#include <stdarg.h>

long int
syscall (long int syscall_number, ...)
{
  unsigned long arg1, arg2, arg3, arg4, arg5, arg6;
  va_list arg;
  long int ret;

  va_start (arg, syscall_number);
  arg1 = va_arg (arg, unsigned long);
  arg2 = va_arg (arg, unsigned long);
  arg3 = va_arg (arg, unsigned long);
  arg4 = va_arg (arg, unsigned long);
  arg5 = va_arg (arg, unsigned long);
  arg6 = va_arg (arg, unsigned long);
  va_end (arg);

  ret = INTERNAL_SYSCALL_NCS (syscall_number, 6, arg1, arg2, arg3, arg4,
			      arg5, arg6);

  if (INTERNAL_SYSCALL_ERROR_P (ret))
    return __syscall_error (ret);

  return ret;
}
