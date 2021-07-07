#!/bin/sh

find . -name "*.c" -o -name "*.h" | sed 's| |\\ |g' | xargs clang-format -i
