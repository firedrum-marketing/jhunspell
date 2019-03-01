#!/bin/bash

cd $(cygpath -C UTF8 "@jhunspellDir@") && autoreconf --force --install >/dev/null 2>&1 && (automake --add-missing >/dev/null 2>&1 || echo >/dev/null 2>&1) && chmod u+x ./configure && ./configure --host x86_64-w64-mingw32 --build x86_64-w64-mingw32 && make clean && make