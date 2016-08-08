CFLAGS=-g -O2 -Wall -Wextra -Isrc -fPIC -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%.test,$(TEST_SRC))

TARGET=build/libfusion_keys.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

POC_SRC=examples/main.c
POC=build/main

VALGRIND=


all: $(TARGET) $(SO_TARGET) $(POC) tests

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

#$(TARGET): CFLAGS +=fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

%.test: %.c
	$(CC) -o $@ $< -Lbuild -lfusion_keys

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: tests run
#tests: CFLAGS += #$(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true

$(POC): $(TARGET) $(POC_SRC)
	@LD_LIBRARY_PATH=build $(CC) $(POC_SRC) -o $(POC) -Lbuild -lfusion_keys

run: $(POC)
	@echo "------ Next is the running program ------"
	@LD_LIBRARY_PATH=build ${VALGRIND} ./build/main
