# Tiktok: stat program running time in kernel

## usage

```
# compiler tiktok
gcc -c /path/to/foo.c -o /path/to/foo.o
objcopy --redefine-sym main=target_main /path/to/foo.o fs/tiktok/target.o_shipped
make M=fs/tiktok

# run
echo 0 > /proc/tiktoc/perf

# check stat
dmesg
```
