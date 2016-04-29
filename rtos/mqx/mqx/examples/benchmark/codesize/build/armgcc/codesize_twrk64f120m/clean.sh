#!/usr/bin/env bash
rm -rf CMakeFiles Makefile cmake_install.cmake CMakeCache.txt *.map
rm -rf "int flash max release" 
rm -rf "int flash typical release" 
rm -rf "int flash small release" 
rm -rf "int flash tiniest release" 
if [ "${1}" != "nopause" ]; then
read -p "Press any key to continue... " -n1 -s
fi
