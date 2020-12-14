# Tiktok: stat program running time in kernel

## compile

### Method 1

1. apply patch to linux kernel
2. run following commands in `/path/to/kernel/src`
```
# compile tiktok
gcc -c /path/to/foo.c -o /path/to/foo.o
objcopy --redefine-sym main=target_main /path/to/foo.o fs/tiktok/target.o_shipped
make M=fs/tiktok
insmod fs/tiktok.ko

```

### Method 2

1. install linux header files
2. `cd src && sudo make`
3. `insmod tiktok.ko`

## run

```
# run
echo 0 > /proc/tiktoc/perf

# check stat
dmesg
```
