#!/usr/bin/env bash

# expect forward slash paths
ROOTDIR="${1}"
OUTPUTDIR="${2}"
TOOL="${3}"

if [ "${TOOL}" = "armgcc" ]; then
mkdir -p "${OUTPUTDIR}"
mkdir -p "${OUTPUTDIR}/."
cp -f "${ROOTDIR}/mqx_stdlib/source/include/std_prv.h" "${OUTPUTDIR}/std_prv.h"
cp -f "${ROOTDIR}/mqx_stdlib/source/include/stdio.h" "${OUTPUTDIR}/stdio.h"
cp -f "${ROOTDIR}/mqx_stdlib/source/include/strings.h" "${OUTPUTDIR}/strings.h"
:
fi


if [ "${TOOL}" = "kds" ]; then
mkdir -p "${OUTPUTDIR}"
mkdir -p "${OUTPUTDIR}/."
cp -f "${ROOTDIR}/mqx_stdlib/source/include/std_prv.h" "${OUTPUTDIR}/std_prv.h"
cp -f "${ROOTDIR}/mqx_stdlib/source/include/stdio.h" "${OUTPUTDIR}/stdio.h"
cp -f "${ROOTDIR}/mqx_stdlib/source/include/strings.h" "${OUTPUTDIR}/strings.h"
:
fi




