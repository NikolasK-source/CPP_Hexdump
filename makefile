all: static_lib
static_lib: libhexdump.a

libhexdump.a: hexdump.o
	ar rcs $@ $^

hexdump.o: hexdump.cpp
	g++ -std=c++11 -O2 -c $< -o $@

clean:
	rm -f *.o *.a
