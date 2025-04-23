# CS5963-fuzzing-libxmp

## Setup
The fuzzing campaigns with this harness were performed using performed [AFL++](https://github.com/AFLplusplus/AFLplusplus). Please view their [documentation](https://github.com/AFLplusplus/AFLplusplus) to install and build AFL++. Do the same to build [libXMP](https://github.com/libxmp/libxmp/tree/master).

After building these libraries, we compiled our harness using clang and cmplog:\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`AFL_LLVM_CMPLOG=1 afl-clang-fast -o harness2cmplog harness_2.c -g -fsanitize-coverage=trace-cmp $(INCLUDE) $(LIBS) -lm`\
We then began our fuzzing campaigns:\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`afl-fuzz -i in -o out -t 100 -c ./harness2cmplog -m none -- ./harness2 @@`
