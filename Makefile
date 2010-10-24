CC=cc
CFLAGS=-O3 -Wall -static
LD=cc
LDFLAGS=-O3 -Wall -static

H=\
	types.h\
	util.h\

all: sha256 sha512

sha256: sha256.o sha2.o util.o $(H) sha2.h
	$(LD) $(LDFLAGS) -o $@ sha256.o sha2.o util.o

sha512: sha512.o sha2.o util.o $(H) sha2.h
	$(LD) $(LDFLAGS) -o $@ sha512.o sha2.o util.o

test:
	./test.py './sha256 -o' < SHA224LongMsg.txt
	./test.py './sha256 -o' < SHA224ShortMsg.txt
	./test.py './sha256' < SHA256LongMsg.txt
	./test.py './sha256' < SHA256ShortMsg.txt
	./test.py './sha512 -o' < SHA384LongMsg.txt
	./test.py './sha512 -o' < SHA384ShortMsg.txt
	./test.py './sha512' < SHA512LongMsg.txt
	./test.py './sha512' < SHA512ShortMsg.txt

clean:
	- rm -f *.o sha256 sha512
