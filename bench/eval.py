#!/usr/bin/env python3
import os
import time
import subprocess
if __name__ == "__main__":
    # COMMAND = os.getcwd() + "/a.out"
    COMMAND = "taskset -c 0 " + os.getcwd() + "/a.out"
    times = []
    # Warmup phase
    for i in range(3):
        subprocess.run(COMMAND, shell=True, timeout=10)
    for i in range(100):
        start = time.time()
        subprocess.run(COMMAND, shell=True, timeout=10)
        end = time.time()
        times.append(end - start)
    print(times)
    print(sum(times)/100)

