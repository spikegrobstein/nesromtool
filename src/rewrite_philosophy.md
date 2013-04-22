# rewrite philosophy

speed things up by reading more and passing full objects around
read header in to simplify working
can also read values directly

## reading a CHR/PRG bank:

`nes_read_chr_bank_from_file` -- given a file and a bank index, it must first seek to
the bank location. optionally give it a header. without the header, it'll read the
bank counts directly

## error detection

do minimal error checking. if someone tries to read the 100th PRG bank and there's
only 2, error out normaly. don't detect that shit

## base functionality:

read header -- into `struct`
read entire file -- into `struct`
write entire file -- from `struct`
write bank to file -- from `char *`
read bank -- into `char*`
read title -- into `char*`
set title -- from string into file
get bank offset in file -- given a header if `header` is `NULL`, then figure it out yourself.
read tile -- from `char*`
read tile range -- from `char*` returning `GSList`
write tile -- to `char*`
decompile -- from `char*`

## to compile:

    clang -o nestest nesromtool/util.c nesromtool.c -Wall -O0 -g -I. `pkg-config --libs --cflags glib-2.0`

