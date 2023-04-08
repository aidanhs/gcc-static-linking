#!/usr/bin/env bash
set -o pipefail
set -o nounset
set -o errexit

if ! command -v bison >/dev/null 2>&1; then
    echo 'need bison'
fi

glibc=glibc-2.37
tar=$glibc.tar.gz
wget http://ftp.gnu.org/gnu/glibc/$tar
tar xf $tar
sed -i 's/# *ifdef USE_NSCD/#if defined USE_NSCD \&\& (!defined DO_STATIC_NSS || defined SHARED)/g' $glibc/nss/nss_module.c
mkdir build
cd build
    ../$glibc/configure --prefix=$(pwd)/../prefix --enable-static-nss
    make -j8
    make install
    cd ..
./gcc.sh
