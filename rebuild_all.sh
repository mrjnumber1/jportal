#!/usr/bin/env sh

command ./update_zproject.sh
command make clean
command ./autogen.sh
command ./configure
command make check
command make

exit 1
