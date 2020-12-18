# Tiktok: stat program running time in Linux kernel

Tiktok (comes from `tic`, `toc` and `K`ernel) is a tool to stat program running time in kernel.
The original idea comes from the requirement to measure the efficiency of different 
compiler backend optimization algorithms more accurately.

## How to use

### 1. Build Kernel

If you have similar requirements to measure LLVM IR, you need to build your kernel with `clang`.
Otherwise, use whatever you have.

### 2. Choose Target Source

#### example.c

There is a `example.c` under `src`, it makes some useless computation.
You can leave it unchanged, or, you can write your own codes.

If you are using `gcc`, you need to comment `./prebuild.sh` and `-x ir` in Makefile, and copy `example.c` as `tiktok_target.c`

#### LLVM IR

Comment first twos line in `prebuild.sh`, and change the filename of your IR output to `tiktok_target.c`.

Notice: You need to add attributes to functions, which can be found in `tiktok_target.c` when you build `example.c`.

### 3. Build and Install

```sh
# build
cd src && sudo make
# install
insmod tiktok.ko
```

### 4. Run

```
echo 0 > /proc/tiktoc/bench
# check stat
dmesg
```
micro-benchmark results can be found under `bench/`

## Limitations

* Current implementation cannot use most functions from standard libraries. (We can write a runtime library to support some key functions)
* Kernel forbid FP usage, so does Tiktok

