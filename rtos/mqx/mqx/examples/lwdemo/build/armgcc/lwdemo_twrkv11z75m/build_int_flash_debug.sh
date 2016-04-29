#!/usr/bin/env bash
(cd  ../../../../../build/armgcc/mqx_twrkv11z75m && source build_debug.sh nopause) 
(cd  ../../../../../../mqx_stdlib/build/armgcc/mqx_stdlib_twrkv11z75m && source build_debug.sh nopause) 
(cd  ../../../../../../../../lib/ksdk_mqx_lib/armgcc/KV11Z7 && source build_debug.sh nopause) 
cmake -DCMAKE_TOOLCHAIN_FILE=armgcc.cmake -DCMAKE_BUILD_TYPE="int flash debug" -G "Unix Makefiles" 
make all 
if [ "${1}" != "nopause" ]; then
read -p "Press any key to continue... " -n1 -s
fi
