#!/usr/bin/env bash
set -o pipefail
set -o nounset
set -o errexit

# https://stackoverflow.com/a/10772056
LDFLAGS="-nostdlib -nostartfiles -static"
GLIBCDIR=$(pwd)/prefix/lib
STARTFILES="$GLIBCDIR/crt1.o $GLIBCDIR/crti.o `gcc --print-file-name=crtbegin.o`"
ENDFILES="`gcc --print-file-name=crtend.o` $GLIBCDIR/crtn.o"
LIBGROUP="-Wl,--start-group $GLIBCDIR/libc.a -lgcc -lgcc_eh -Wl,--end-group"
gcc $LDFLAGS $STARTFILES test.c $LIBGROUP $ENDFILES
