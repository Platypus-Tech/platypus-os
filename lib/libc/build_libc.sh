#!/bin/sh

if [ ! -d build ]; then
   mkdir build
fi

# Build ctype
cd ./ctype/
i686-elf-gcc -I../../../kernel/include/ -c isalnum.c
i686-elf-gcc -I../../../kernel/include/ -c isalpha.c
i686-elf-gcc -I../../../kernel/include/ -c isblank.c
i686-elf-gcc -I../../../kernel/include/ -c iscntrl.c
i686-elf-gcc -I../../../kernel/include/ -c isdigit.c
i686-elf-gcc -I../../../kernel/include/ -c isgraph.c
i686-elf-gcc -I../../../kernel/include/ -c islower.c
i686-elf-gcc -I../../../kernel/include/ -c isprint.c
i686-elf-gcc -I../../../kernel/include/ -c ispunct.c
i686-elf-gcc -I../../../kernel/include/ -c isspace.c
i686-elf-gcc -I../../../kernel/include/ -c isupper.c
i686-elf-gcc -I../../../kernel/include/ -c isxdigit.c
i686-elf-gcc -I../../../kernel/include/ -c tolower.c
i686-elf-gcc -I../../../kernel/include/ -c toupper.c

cp *.o ../build/
cd ..

# Build inttypes
cd ./inttypes/
i686-elf-gcc -I../../../kernel/include/ -c imaxabs.c
i686-elf-gcc -I../../../kernel/include/ -c imaxdiv.c
i686-elf-gcc -I../../../kernel/include/ -c strtoimax.c
i686-elf-gcc -I../../../kernel/include/ -c strtoumax.c

cp *.o ../build/
cd ..

# Build locale
cd ./locale/
i686-elf-gcc -I../../../kernel/include/ -c localeconv.c
i686-elf-gcc -I../../../kernel/include/ -c setlocale.c

cp *.o ../build/
cd ..

# Build stdio
cd ./stdio/
i686-elf-gcc -I../../../kernel/include/ -c clearerr.c
i686-elf-gcc -I../../../kernel/include/ -c fclose.c
i686-elf-gcc -I../../../kernel/include/ -c feof.c
i686-elf-gcc -I../../../kernel/include/ -c ferror.c
i686-elf-gcc -I../../../kernel/include/ -c fflush.c
i686-elf-gcc -I../../../kernel/include/ -c fgetc.c
i686-elf-gcc -I../../../kernel/include/ -c fgetpos.c
i686-elf-gcc -I../../../kernel/include/ -c fgets.c
i686-elf-gcc -I../../../kernel/include/ -c fopen.c
i686-elf-gcc -I../../../kernel/include/ -c fopen_s.c
i686-elf-gcc -I../../../kernel/include/ -c fprintf.c
i686-elf-gcc -I../../../kernel/include/ -c fputc.c
i686-elf-gcc -I../../../kernel/include/ -c fputs.c
i686-elf-gcc -I../../../kernel/include/ -c fread.c
i686-elf-gcc -I../../../kernel/include/ -c freopen.c
i686-elf-gcc -I../../../kernel/include/ -c freopen_s.c
i686-elf-gcc -I../../../kernel/include/ -c fscanf.c
i686-elf-gcc -I../../../kernel/include/ -c fseek.c
i686-elf-gcc -I../../../kernel/include/ -c fsetpos.c
i686-elf-gcc -I../../../kernel/include/ -c ftell.c
i686-elf-gcc -I../../../kernel/include/ -c fwrite.c
i686-elf-gcc -I../../../kernel/include/ -c getc.c
i686-elf-gcc -I../../../kernel/include/ -c getchar.c
i686-elf-gcc -I../../../kernel/include/ -c perror.c
i686-elf-gcc -I../../../kernel/include/ -c printf.c
i686-elf-gcc -I../../../kernel/include/ -c putc.c
i686-elf-gcc -I../../../kernel/include/ -c putchar.c
i686-elf-gcc -I../../../kernel/include/ -c puts.c
i686-elf-gcc -I../../../kernel/include/ -c remove.c
i686-elf-gcc -I../../../kernel/include/ -c rename.c
i686-elf-gcc -I../../../kernel/include/ -c rewind.c
i686-elf-gcc -I../../../kernel/include/ -c scanf.c
i686-elf-gcc -I../../../kernel/include/ -c setbuf.c
i686-elf-gcc -I../../../kernel/include/ -c setvbuf.c
i686-elf-gcc -I../../../kernel/include/ -c snprintf.c
i686-elf-gcc -I../../../kernel/include/ -c sprintf.c
i686-elf-gcc -I../../../kernel/include/ -c sscanf.c 
i686-elf-gcc -I../../../kernel/include/ -c tmpfile_s.c
i686-elf-gcc -I../../../kernel/include/ -c tmpnam.c
i686-elf-gcc -I../../../kernel/include/ -c ungetc.c
i686-elf-gcc -I../../../kernel/include/ -c vfprintf.c
i686-elf-gcc -I../../../kernel/include/ -c vfscanf.c
i686-elf-gcc -I../../../kernel/include/ -c vprintf.c
i686-elf-gcc -I../../../kernel/include/ -c vscanf.c
i686-elf-gcc -I../../../kernel/include/ -c vsnprintf.c
i686-elf-gcc -I../../../kernel/include/ -c vsprintf.c
i686-elf-gcc -I../../../kernel/include/ -c vsscanf.c

cp *.o ../build
cd ..

# Build stdlib
cd ./stdlib/
i686-elf-gcc -I../../../kernel/include/ -c abort.c
i686-elf-gcc -I../../../kernel/include/ -c abort_handler_s.c
i686-elf-gcc -I../../../kernel/include/ -c abs.c
i686-elf-gcc -I../../../kernel/include/ -c atexit.c
i686-elf-gcc -I../../../kernel/include/ -c atoi.c
i686-elf-gcc -I../../../kernel/include/ -c atol.c
i686-elf-gcc -I../../../kernel/include/ -c atoll.c
i686-elf-gcc -I../../../kernel/include/ -c at_quick_exit.c
i686-elf-gcc -I../../../kernel/include/ -c bsearch.c
i686-elf-gcc -I../../../kernel/include/ -c bsearch_s.c
i686-elf-gcc -I../../../kernel/include/ -c div.c
i686-elf-gcc -I../../../kernel/include/ -c exit.c
i686-elf-gcc -I../../../kernel/include/ -c _Exit.c
i686-elf-gcc -I../../../kernel/include/ -c ignore_handler_s.c
i686-elf-gcc -I../../../kernel/include/ -c labs.c
i686-elf-gcc -I../../../kernel/include/ -c ldiv.c
i686-elf-gcc -I../../../kernel/include/ -c llabs.c
i686-elf-gcc -I../../../kernel/include/ -c lldiv.c
i686-elf-gcc -I../../../kernel/include/ -c qsort.c
i686-elf-gcc -I../../../kernel/include/ -c qsort_s.c
i686-elf-gcc -I../../../kernel/include/ -c quick_exit.c
i686-elf-gcc -I../../../kernel/include/ -c rand.c
i686-elf-gcc -I../../../kernel/include/ -c set_constraint_handler_s.c
i686-elf-gcc -I../../../kernel/include/ -c srand.c
i686-elf-gcc -I../../../kernel/include/ -c strtol.c
i686-elf-gcc -I../../../kernel/include/ -c strtoll.c
i686-elf-gcc -I../../../kernel/include/ -c strtoul.c
i686-elf-gcc -I../../../kernel/include/ -c strtoull.c

cp *.o ../build/
cd ..

# Build string
cd ./string/
i686-elf-gcc -I../../../kernel/include/ -c memchr.c
i686-elf-gcc -I../../../kernel/include/ -c memcmp.c
i686-elf-gcc -I../../../kernel/include/ -c memcpy.c
i686-elf-gcc -I../../../kernel/include/ -c memcpy_s.c
i686-elf-gcc -I../../../kernel/include/ -c memmove.c
i686-elf-gcc -I../../../kernel/include/ -c memmove_s.c
i686-elf-gcc -I../../../kernel/include/ -c memset.c
i686-elf-gcc -I../../../kernel/include/ -c memset_s.c
i686-elf-gcc -I../../../kernel/include/ -c strcat.c
i686-elf-gcc -I../../../kernel/include/ -c strcat_s.c
i686-elf-gcc -I../../../kernel/include/ -c strchr.c
i686-elf-gcc -I../../../kernel/include/ -c strcmp.c
i686-elf-gcc -I../../../kernel/include/ -c strcoll.c
i686-elf-gcc -I../../../kernel/include/ -c strcpy.c
i686-elf-gcc -I../../../kernel/include/ -c strcpy_s.c
i686-elf-gcc -I../../../kernel/include/ -c strcspn.c
i686-elf-gcc -I../../../kernel/include/ -c strerror.c
i686-elf-gcc -I../../../kernel/include/ -c strerrorlen_s.c
i686-elf-gcc -I../../../kernel/include/ -c strerror_s.c
i686-elf-gcc -I../../../kernel/include/ -c strlen.c
i686-elf-gcc -I../../../kernel/include/ -c strncat.c
i686-elf-gcc -I../../../kernel/include/ -c strncat_s.c
i686-elf-gcc -I../../../kernel/include/ -c strncmp.c
i686-elf-gcc -I../../../kernel/include/ -c strncpy.c
i686-elf-gcc -I../../../kernel/include/ -c strncpy_s.c
i686-elf-gcc -I../../../kernel/include/ -c strpbrk.c
i686-elf-gcc -I../../../kernel/include/ -c strrchr.c
i686-elf-gcc -I../../../kernel/include/ -c strspn.c
i686-elf-gcc -I../../../kernel/include/ -c strstr.c
i686-elf-gcc -I../../../kernel/include/ -c strtok.c
i686-elf-gcc -I../../../kernel/include/ -c strtok_s.c
i686-elf-gcc -I../../../kernel/include/ -c strxfrm.c

cp *.o ../build/
cd ..

# Build time
cd ./time/
i686-elf-gcc -I../../../kernel/include/ -c asctime.c
i686-elf-gcc -I../../../kernel/include/ -c asctime_s.c
i686-elf-gcc -I../../../kernel/include/ -c ctime.c
i686-elf-gcc -I../../../kernel/include/ -c ctime_s.c
i686-elf-gcc -I../../../kernel/include/ -c difftime.c
i686-elf-gcc -I../../../kernel/include/ -c gmtime.c
i686-elf-gcc -I../../../kernel/include/ -c gmtime_s.c
i686-elf-gcc -I../../../kernel/include/ -c localtime.c
i686-elf-gcc -I../../../kernel/include/ -c localtime_s.c
i686-elf-gcc -I../../../kernel/include/ -c mktime.c
i686-elf-gcc -I../../../kernel/include/ -c strftime.c

cp *.o ../build/
cd ..

ar rcs libpdclib.a ./build/*.o
