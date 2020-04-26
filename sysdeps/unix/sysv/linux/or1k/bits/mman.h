/* Copyright (C) 2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Christian Svensson <blue@cmd.nu>

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

#ifndef _SYS_MMAN_H
# error "Never use <bits/mman.h> directly; include <sys/mman.h> instead."
#endif

/* The following definitions basically come from the kernel headers.
   But the kernel header is not namespace clean.  */

#ifdef __USE_MISC
# define MAP_GROWSDOWN  0x0100          /* stack-like segment */
# define MAP_DENYWRITE  0x0800          /* ETXTBSY */
# define MAP_EXECUTABLE 0x1000          /* mark it as an executable */
# define MAP_LOCKED     0x2000          /* pages are locked */
# define MAP_NORESERVE  0x4000          /* don't check for reservations */
# define MAP_POPULATE   0x8000          /* populate (prefault) pagetables */
# define MAP_NONBLOCK   0x10000         /* do not block on IO */
# define MAP_STACK      0x20000         /* give out an address that is best suited for process/thread stacks */
# define MAP_HUGETLB    0x40000         /* create a huge page mapping */
#endif

/* Bits [26:31] are reserved, see mman-common.h for MAP_HUGETLB usage */

#define MCL_CURRENT     1               /* lock all current mappings */
#define MCL_FUTURE      2               /* lock all future mappings */

/* Include generic Linux declarations.  */
#include <bits/mman-linux.h>
