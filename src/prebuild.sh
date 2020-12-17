$CC -O0 -fstack-protector-strong -fno-omit-frame-pointer -mfentry -mno-red-zone -fno-asynchronous-unwind-tables -S -emit-llvm example.c -o tiktok_target.c
sed -i 's/main()/target_main()/' tiktok_target.c
cp tiktok_target_dep .tiktok_target.o.d
