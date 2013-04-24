# @configure_output@

# package-specific substitution variables
package = nesromtool
version = 2.0a
tarname = nesromtool
distdir = $(tarname)-$(version)

# Prefix-specific substitution variables
prefix = /usr/local
exec_prefix = ${prefix}
bindir = ${exec_prefix}/bin

sources = nesromtool/util.c nesromtool.c
program = nestest
CFLAGS = -Wall -O0 -g -I. `pkg-config --libs --cflags glib-2.0`

all: program

debug: program
	gdb ./$(program)

program:
	clang -o $(program) $(sources) $(CFLAGS)

clean:
	rm -f $(program)
