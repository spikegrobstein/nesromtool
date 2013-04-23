sources = nesromtool/util.c nesromtool.c
program = nestest
CFLAGS = -Wall -O0 -g -I. `pkg-config --libs --cflags glib-2.0`

all:
	clang -o $(program) $(sources) $(CFLAGS)
