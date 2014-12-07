CC=g++
CFLAGS=-std=c++11 -Wall -O3
LDFLAGS=-s
GTESTLIBS=-lgtest -lpthread
SOURCES=main.cpp globex_fast_speed_test.cpp fix_compiler.cpp fast_compiler.cpp
EXECUTABLES=fixfast_test fast_fields_test globex_fast_speed_test globex_fast_test fix_compiler fast_compiler
TEMPLATES=templates.xml fast_test.xml FIX42.xml
HEADERS=optional.h fast_fields.h message.h utils.h
GENERATED_HEADERS=globex_fast.h fast_test.h fix42.h

all: $(SOURCES) $(HEADERS) $(TEMPLATES) $(EXECUTABLES)

clean:
	rm $(GENERATED_HEADERS) $(EXECUTABLES)

fixfast_test: main.cpp $(HEADERS) $(GENERATED_HEADERS)
	$(CC) $(CFLAGS) $(LDFLAGS) main.cpp $(GTESTLIBS) -o $@

fast_fields_test: fast_fields_test.cpp $(HEADERS) $(GENERATED_HEADERS)
	$(CC) $(CFLAGS) $(LDFLAGS) fast_fields_test.cpp -o $@

globex_fast_speed_test: globex_fast_speed_test.cpp $(HEADERS) $(GENERATED_HEADERS)
	$(CC) $(CFLAGS) $(LDFLAGS) globex_fast_speed_test.cpp -o $@

globex_fast_test: globex_fast_test.cpp $(HEADERS) $(GENERATED_HEADERS)
	$(CC) $(CFLAGS) $(LDFLAGS) globex_fast_test.cpp -o $@

fix_compiler: fix_compiler.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) fix_compiler.cpp -o $@

fast_compiler: fast_compiler.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) fast_compiler.cpp -o $@

globex_fast.h: templates.xml fast_compiler
	./fast_compiler templates.xml $@

fast_test.h: fast_test.xml fast_compiler
	./fast_compiler fast_test.xml $@

fix42.h: FIX42.xml fix_compiler
	./fix_compiler FIX42.xml $@