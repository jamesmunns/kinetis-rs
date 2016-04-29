#!/usr/bin/env bash
(./build_int_flash_max_release.sh nopause) 
(./build_int_flash_typical_release.sh nopause) 
(./build_int_flash_small_release.sh nopause) 
(./build_int_flash_tiniest_release.sh nopause) 
if [ "${1}" != "nopause" ]; then
read -p "Press any key to continue... " -n1 -s
fi
