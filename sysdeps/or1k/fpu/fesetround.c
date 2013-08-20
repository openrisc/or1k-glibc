/* Set current rounding direction.  OpenRISC version.
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

#include <fenv.h>
#include <fpu_control.h>

int
__fesetround (int round)
{
  fpu_control_t cw;

  switch (round)
    {
    case FE_TONEAREST:
    case FE_TOWARDZERO:
    case FE_DOWNWARD:
    case FE_UPWARD:
      _FPU_GETCW (cw);
      cw &= ~(0x3 << 1);
      cw |= round;
      _FPU_SETCW (cw);
      return 0;
    default:
      return round; /* A nonzero value.  */
    }
}
libm_hidden_def (__fesetround)
weak_alias (__fesetround, fesetround)
libm_hidden_weak (fesetround)
