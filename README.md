# Tiktok: stat program running time in Linux kernel

The initial idea of this project is to measure the efficiency of compiler backend optimization algorithms
more accurately. I implement it to compile LLVM IR, however, normal C file works as well.

## compile

1. Build your Linux kernel using clang
2. Change `src/example.c`, if you like
3. `cd src && sudo make`
4. `insmod tiktok.ko`

## run

```
# run
echo 0 > /proc/tiktoc/perf

# check stat
dmesg
```

micro-benchmark results can be found under `bench/`
