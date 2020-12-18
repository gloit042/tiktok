#!/usr/bin/env python3
import os
import subprocess
import sys

"""
Some efforts to compile tiktok with gcc-built kernel but failed
"""

DEFAULT_CC='gcc'

FILE_PATH = os.path.dirname(os.path.abspath(__file__))

CLANG_FILTER = ['-fmerge-constants', '-falign-jumps=1', '-falign-loops=1', '-mindirect-branch=thunk-extern', 
        '-mindirect-branch-register', '-mrecord-mcount', '-fconserve-stack', '-mskip-rax-setup',
        '-mno-fp-ret-in-387','-fno-var-tracking-assignments', '-flive-patching=inline-clone']


def run(argv):
    use_clang = False
    for arg in argv:
        if arg == FILE_PATH + '/tiktok_target.c':
            use_clang = True
            break

    new_argv = []
    if use_clang:
        new_argv.append(os.getenv('CLANG'))
        new_argv.append('-mretpoline-external-thunk')
        new_argv.append('-mfentry')
        new_argv.append('-fstack-protector-strong')
        for arg in argv:
            if arg == '-mpreferred-stack-boundary=2':
                new_argv.append('-mstack-alignment=4')
            elif arg == '-mpreferred-stack-boundary=3':
                new_argv.append('-mstack-alignment=8')
            elif arg not in CLANG_FILTER:
                new_argv.append(arg)
    else:
        new_argv = [DEFAULT_CC]
        new_argv.extend(argv)

    ret = subprocess.call(new_argv, timeout=1)
    return ret

if __name__ == '__main__':
    argv = sys.argv[1:]
    exit(run(argv))

