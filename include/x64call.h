
/**
 * x64call c header
 * 
 * Copyright (c) 2021 github.com/System233
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
    /*
        Search the symbol in all loaded modules, same with x64call_dlsym(0,name);
        @param name: the symbol name
        @returns symbol address,may fail to 0
    */
    uint64_t x64call_dlwalk(char const*name);

    /*
        Search the symbol in specific module;
        @param handle: the module handle
        @param name: the symbol name
        @returns symbol address, may fail to 0
    */
    uint64_t x64call_dlsym(uint64_t handle,char const*name);

    /*
        @param num: number of vargs
        @param addr: address of 64bit function 
        @param ...: function arguments, type must be uint64_t
        @returns target function result
    */
    uint64_t x64call_exec(uint64_t num,uint64_t addr,...);
    
    /*
        @returns Whether current CPU is running in x86 mode;
    */
    int x64call_isin32();
    /*
        built-in strcmp for symbol search;
    */
    int x64call_strcmp(char const*,char const*);

#ifdef __cplusplus
};
#endif