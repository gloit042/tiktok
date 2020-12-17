obj-m += tiktok.o
tiktok-objs := procfs.o tiktok_target.o
CFLAGS_tiktok_target.o := -O0 -x ir

all:
	./prebuild.sh
	make CC=/home/cp/llvm-install/bin/clang -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
	rm tiktok_target.c
