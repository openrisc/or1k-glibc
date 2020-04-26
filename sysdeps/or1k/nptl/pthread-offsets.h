/* OpenRISC pthread offsets
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

/* Offsets generated with:

   #include <stdio.h>
   #include <unistd.h>
   #include <pthread.h>
   #include <stddef.h>

   int main (int argc, char **argv)
   {
       printf ("#define __PTHREAD_MUTEX_NUSERS_OFFSET  %d\n", offsetof (pthread_mutex_t, __data.__nusers));
       printf ("#define __PTHREAD_MUTEX_KIND_OFFSET    %d\n", offsetof (pthread_mutex_t, __data.__kind));
       printf ("#define __PTHREAD_MUTEX_SPINS_OFFSET   %d\n", offsetof (pthread_mutex_t, __data.__spins));
#if __PTHREAD_MUTEX_LOCK_ELISION
       printf ("#define __PTHREAD_MUTEX_ELISION_OFFSET %d\n", offsetof (pthread_mutex_t, __data.__elision));
#endif
       printf ("#define __PTHREAD_MUTEX_LIST_OFFSET    %d\n", offsetof (pthread_mutex_t, __data.__list));
   }
 */

#define __PTHREAD_MUTEX_NUSERS_OFFSET   12
#define __PTHREAD_MUTEX_KIND_OFFSET     16
#define __PTHREAD_MUTEX_SPINS_OFFSET    20
#define __PTHREAD_MUTEX_LIST_OFFSET     24
