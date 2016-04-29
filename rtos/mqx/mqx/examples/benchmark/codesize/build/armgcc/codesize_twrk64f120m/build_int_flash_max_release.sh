#!/usr/bin/env bash
(cd  ../../../../../../build/armgcc/mqx_twrk64f120m && source build_release.sh nopause) 
(cd  ../../../../../../../mqx_stdlib/build/armgcc/mqx_stdlib_twrk64f120m && source build_release.sh nopause) 
(cd  ../../../../../../../../../lib/ksdk_mqx_lib/armgcc/K64F12 && source build_release.sh nopause) 
(cd  ../../../../../../../nshell/build/armgcc/nshell_twrk64f120m && source build_release.sh nopause) 
(cd  ../../../../../../../../../middleware/filesystem/mfs/build/armgcc/mfs_twrk64f120m && source build_release.sh nopause) 
(cd  ../../../../../../../../../middleware/tcpip/rtcs/build/armgcc/rtcs_twrk64f120m && source build_release.sh nopause) 
cmake -DCMAKE_TOOLCHAIN_FILE=armgcc.cmake -DCMAKE_BUILD_TYPE="int flash max release" -G "Unix Makefiles" 
make all 
if [ "${1}" != "nopause" ]; then
read -p "Press any key to continue... " -n1 -s
fi
