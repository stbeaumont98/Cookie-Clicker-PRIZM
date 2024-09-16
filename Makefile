PREFIX=../../
CC=$(PREFIX)/bin/sh3eb-elf-gcc.exe
MKG3A=$(PREFIX)/bin/mkg3a.exe
RM=del
CFLAGS=-m3 -mb -O3 -mhitachi -Wall -nostdlib -I$(PREFIX)/include -lfxcg -lm -lc -lg -lgcc -L$(PREFIX)/lib -std=c99
MKG3AFLAGS=-i uns:Icon_U.bmp -i sel:Icon_S.bmp -n en:CookieClicker
LDFLAGS=$(CFLAGS) -T../common/prizm.ld -Wl,-static
CSOURCES=main.c
OBJECTS=$(CRT0:.s=.o) $(CSOURCES:.c=.o)
BIN=Cookies.bin
ADDIN=$(BIN:.bin=.g3a)

all: $(ADDIN)

$(BIN): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(ADDIN): $(BIN)
	$(MKG3A) $(MKG3AFLAGS) $< $@

.s.o:
	$(CC) -c $(CFLAGS) $< -o $@

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS) $(BIN) $(ADDIN)


