TOOLS := can_log_raw isoblued
TEST := sc_mod_test can_stress isoblue_dummy
PREFIX := /usr
CFLAGS := -Wall -Wextra -O3 $(CFLAGS)

all : $(TOOLS) $(TEST)

include ../buildnum.mk

isoblued isoblue_dummy : LDLIBS += -lbluetooth
isoblued : ring_buf.o
storage : storage.o

ring_buf.o : ring_buf.c ring_buf.h
storage.o : storage.c

install : $(TOOLS:%=install_%)

install_% :
	install $* $(PREFIX)/bin/$*

clean ::
	-$(RM) $(TOOLS) $(TEST) *.o
