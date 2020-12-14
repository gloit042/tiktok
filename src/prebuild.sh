gcc -O0 -c example.c -o example.o
objcopy --redefine-sym main=target_main example.o target.o_shipped
