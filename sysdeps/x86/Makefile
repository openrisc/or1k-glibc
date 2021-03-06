ifeq ($(subdir),csu)
gen-as-const-headers += cpu-features-offsets.sym
endif

ifeq ($(subdir),elf)
sysdep-dl-routines += dl-get-cpu-features

tests += tst-get-cpu-features tst-get-cpu-features-static
tests-static += tst-get-cpu-features-static
endif

ifeq ($(subdir),setjmp)
gen-as-const-headers += jmp_buf-ssp.sym
sysdep_routines += __longjmp_cancel
endif

ifeq ($(enable-cet),yes)
ifeq ($(subdir),elf)
sysdep-dl-routines += dl-cet

tests += tst-cet-legacy-1 tst-cet-legacy-1a tst-cet-legacy-2 \
	 tst-cet-legacy-2a tst-cet-legacy-3 tst-cet-legacy-4 \
	 tst-cet-legacy-5a tst-cet-legacy-6a tst-cet-legacy-7 \
	 tst-cet-legacy-8
tst-cet-legacy-1a-ARGS = -- $(host-test-program-cmd)
ifneq (no,$(have-tunables))
tests += tst-cet-legacy-4a tst-cet-legacy-4b tst-cet-legacy-4c \
	 tst-cet-legacy-5b tst-cet-legacy-6b
endif
modules-names += tst-cet-legacy-mod-1 tst-cet-legacy-mod-2 \
		 tst-cet-legacy-mod-4 tst-cet-legacy-mod-5a \
		 tst-cet-legacy-mod-5b tst-cet-legacy-mod-5c \
		 tst-cet-legacy-mod-6a tst-cet-legacy-mod-6b \
		 tst-cet-legacy-mod-6c

CFLAGS-tst-cet-legacy-2.c += -fcf-protection=branch
CFLAGS-tst-cet-legacy-2a.c += -fcf-protection
CFLAGS-tst-cet-legacy-mod-1.c += -fcf-protection=none
CFLAGS-tst-cet-legacy-mod-2.c += -fcf-protection=none
CFLAGS-tst-cet-legacy-3.c += -fcf-protection=none
CFLAGS-tst-cet-legacy-4.c += -fcf-protection=branch
CFLAGS-tst-cet-legacy-4a.c += -fcf-protection
CFLAGS-tst-cet-legacy-4b.c += -fcf-protection
CFLAGS-tst-cet-legacy-mod-4.c += -fcf-protection=none
CFLAGS-tst-cet-legacy-5a.c += -fcf-protection
CFLAGS-tst-cet-legacy-5b.c += -fcf-protection
CFLAGS-tst-cet-legacy-mod-5a.c += -fcf-protection=branch
CFLAGS-tst-cet-legacy-mod-5b.c += -fcf-protection
CFLAGS-tst-cet-legacy-mod-5c.c += -fcf-protection
CFLAGS-tst-cet-legacy-6a.c += -fcf-protection
CFLAGS-tst-cet-legacy-6b.c += -fcf-protection
CFLAGS-tst-cet-legacy-mod-6a.c += -fcf-protection=branch
CFLAGS-tst-cet-legacy-mod-6b.c += -fcf-protection
CFLAGS-tst-cet-legacy-mod-6c.c += -fcf-protection
CFLAGS-tst-cet-legacy-7.c += -fcf-protection=none
CFLAGS-tst-cet-legacy-8.c += -mshstk

$(objpfx)tst-cet-legacy-1: $(objpfx)tst-cet-legacy-mod-1.so \
		       $(objpfx)tst-cet-legacy-mod-2.so
$(objpfx)tst-cet-legacy-1a: $(objpfx)tst-cet-legacy-mod-1.so \
		       $(objpfx)tst-cet-legacy-mod-2.so
$(objpfx)tst-cet-legacy-2: $(objpfx)tst-cet-legacy-mod-2.so $(libdl)
$(objpfx)tst-cet-legacy-2.out: $(objpfx)tst-cet-legacy-mod-1.so
$(objpfx)tst-cet-legacy-2a: $(objpfx)tst-cet-legacy-mod-2.so $(libdl)
$(objpfx)tst-cet-legacy-2a.out: $(objpfx)tst-cet-legacy-mod-1.so
$(objpfx)tst-cet-legacy-4: $(libdl)
$(objpfx)tst-cet-legacy-4.out: $(objpfx)tst-cet-legacy-mod-4.so
$(objpfx)tst-cet-legacy-5a: $(libdl)
$(objpfx)tst-cet-legacy-5a.out: $(objpfx)tst-cet-legacy-mod-5a.so \
				$(objpfx)tst-cet-legacy-mod-5b.so
$(objpfx)tst-cet-legacy-mod-5a.so: $(objpfx)tst-cet-legacy-mod-5c.so
$(objpfx)tst-cet-legacy-mod-5b.so: $(objpfx)tst-cet-legacy-mod-5c.so
$(objpfx)tst-cet-legacy-6a: $(libdl)
$(objpfx)tst-cet-legacy-6a.out: $(objpfx)tst-cet-legacy-mod-6a.so \
				$(objpfx)tst-cet-legacy-mod-6b.so
$(objpfx)tst-cet-legacy-mod-6a.so: $(objpfx)tst-cet-legacy-mod-6c.so
$(objpfx)tst-cet-legacy-mod-6b.so: $(objpfx)tst-cet-legacy-mod-6c.so
LDFLAGS-tst-cet-legacy-mod-6c.so = -Wl,--enable-new-dtags,-z,nodelete
ifneq (no,$(have-tunables))
$(objpfx)tst-cet-legacy-4a: $(libdl)
$(objpfx)tst-cet-legacy-4a.out: $(objpfx)tst-cet-legacy-mod-4.so
tst-cet-legacy-4a-ENV = GLIBC_TUNABLES=glibc.cpu.x86_shstk=permissive
$(objpfx)tst-cet-legacy-4b: $(libdl)
$(objpfx)tst-cet-legacy-4b.out: $(objpfx)tst-cet-legacy-mod-4.so
tst-cet-legacy-4b-ENV = GLIBC_TUNABLES=glibc.cpu.x86_shstk=on
$(objpfx)tst-cet-legacy-4c: $(libdl)
$(objpfx)tst-cet-legacy-4c.out: $(objpfx)tst-cet-legacy-mod-4.so
tst-cet-legacy-4c-ENV = GLIBC_TUNABLES=glibc.cpu.x86_shstk=off
$(objpfx)tst-cet-legacy-5b: $(libdl)
$(objpfx)tst-cet-legacy-5b.out: $(objpfx)tst-cet-legacy-mod-5a.so \
				$(objpfx)tst-cet-legacy-mod-5b.so
tst-cet-legacy-5b-ENV = GLIBC_TUNABLES=glibc.cpu.hwcaps=-IBT,-SHSTK
$(objpfx)tst-cet-legacy-6b: $(libdl)
$(objpfx)tst-cet-legacy-6b.out: $(objpfx)tst-cet-legacy-mod-6a.so \
				$(objpfx)tst-cet-legacy-mod-6b.so
tst-cet-legacy-6b-ENV = GLIBC_TUNABLES=glibc.cpu.hwcaps=-IBT,-SHSTK
endif
endif

# Add -fcf-protection to CFLAGS when CET is enabled.
CFLAGS-.o += -fcf-protection
CFLAGS-.os += -fcf-protection
CFLAGS-.op += -fcf-protection
CFLAGS-.oS += -fcf-protection

# Compile assembly codes with <cet.h> when CET is enabled.
asm-CPPFLAGS += -fcf-protection -include cet.h

ifeq ($(subdir),elf)
ifeq (yes,$(build-shared))
tests-special += $(objpfx)check-cet.out
endif

# FIXME: Can't use all-built-dso in elf/Makefile since this file is
# processed before elf/Makefile.  Duplicate it here.
cet-built-dso := $(common-objpfx)elf/ld.so $(common-objpfx)libc.so \
		 $(filter-out $(common-objpfx)linkobj/libc.so, \
			      $(sort $(wildcard $(addprefix $(common-objpfx), \
							    */lib*.so \
							    iconvdata/*.so))))

$(cet-built-dso:=.note): %.note: %
	@rm -f $@T
	LC_ALL=C $(READELF) -n $< > $@T
	test -s $@T
	mv -f $@T $@
common-generated += $(cet-built-dso:$(common-objpfx)%=%.note)

$(objpfx)check-cet.out: $(..)sysdeps/x86/check-cet.awk \
			$(cet-built-dso:=.note)
	LC_ALL=C $(AWK) -f $^ > $@; \
	$(evaluate-test)
generated += check-cet.out
endif
endif
