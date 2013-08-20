ifeq ($(subdir),misc)
  sysdep_routines += prctl or1k_clone
endif

ifeq ($(subdir),stdlib)
gen-as-const-headers += ucontext_i.sym
endif

# pull in __syscall_error routine
libpthread-routines += sysdep
librt-routines += sysdep

