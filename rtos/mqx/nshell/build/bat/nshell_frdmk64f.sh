#!/usr/bin/env bash

# expect forward slash paths
ROOTDIR="${1}"
OUTPUTDIR="${2}"
TOOL="${3}"

if [ "${TOOL}" = "armgcc" ]; then
mkdir -p "${OUTPUTDIR}"
mkdir -p "${OUTPUTDIR}/."
cp -f "${ROOTDIR}/nshell/source/include/shell.h" "${OUTPUTDIR}/shell.h"
cp -f "${ROOTDIR}/nshell/source/include/sh_rtcs.h" "${OUTPUTDIR}/sh_rtcs.h"
cp -f "${ROOTDIR}/nshell/source/include/sh_enet.h" "${OUTPUTDIR}/sh_enet.h"
:
fi


if [ "${TOOL}" = "kds" ]; then
mkdir -p "${OUTPUTDIR}"
mkdir -p "${OUTPUTDIR}/."
cp -f "${ROOTDIR}/nshell/source/include/shell.h" "${OUTPUTDIR}/shell.h"
cp -f "${ROOTDIR}/nshell/source/include/sh_rtcs.h" "${OUTPUTDIR}/sh_rtcs.h"
cp -f "${ROOTDIR}/nshell/source/include/sh_enet.h" "${OUTPUTDIR}/sh_enet.h"
:
fi




