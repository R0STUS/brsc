#!/usr/bin/bash

SOURCES="src/main.c"
OUTPUT="brsc"
CONFIG="-D_POSIX_C_SOURCE=200112L -std=c90 -pedantic-errors -Wall -Wextra"

gcc $SOURCES $CONFIG -o $OUTPUT
