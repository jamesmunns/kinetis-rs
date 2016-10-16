#!/bin/bash

set -eu

cd rust-bindgen/
cargo build --release
cd ../

# TODO: figure out why "-target thumbv7em-none-eabi" causes these errors:
#     ERROR:bindgen: /usr/include/sys/cdefs.h:707:2: error: Unsupported architecture
#     ERROR:bindgen: /usr/include/machine/_types.h:34:2: error: architecture not supported
#     ERROR:bindgen: /usr/include/sys/_types.h:55:9: error: unknown type name '__int64_t'
#     ERROR:bindgen: /usr/include/sys/_types.h:56:9: error: unknown type name '__int32_t'
#     ERROR:bindgen: /usr/include/sys/_types.h:57:9: error: unknown type name '__int32_t'
#     ERROR:bindgen: /usr/include/sys/_types.h:60:9: error: unknown type name '__uint32_t'
#     ERROR:bindgen: /usr/include/sys/_types.h:61:9: error: unknown type name '__uint32_t'
#     ERROR:bindgen: /usr/include/sys/_types.h:62:9: error: unknown type name '__uint64_t'
#     ERROR:bindgen: /usr/include/sys/_types.h:68:9: error: unknown type name '__darwin_natural_t'
#     ERROR:bindgen: /usr/include/sys/_types.h:70:9: error: unknown type name '__uint16_t'
#     ERROR:bindgen: /usr/include/sys/_types.h:71:9: error: unknown type name '__int64_t'
#     ERROR:bindgen: /usr/include/sys/_types.h:72:9: error: unknown type name '__int32_t'
#     ERROR:bindgen: /usr/include/sys/_types.h:73:9: error: unknown type name '__uint32_t'
#     ERROR:bindgen: /usr/include/sys/_types.h:74:9: error: unknown type name '__int32_t'
#     ERROR:bindgen: /usr/include/sys/_types.h:75:9: error: unknown type name '__uint32_t'
#     ERROR:bindgen: /usr/include/sys/_types.h:76:9: error: unknown type name '__uint32_t'
#     ERROR:bindgen: /usr/include/sys/_types/_intptr_t.h:30:9: error: unknown type name '__darwin_intptr_t'
#     WARN:bindgen: ../platform/CMSIS/Include/core_cm0plus.h:123:6: warning: "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)" [-W#warnings]
#     ERROR:bindgen: /usr/include/machine/signal.h:34:2: error: architecture not supported
#     ERROR:bindgen: /usr/include/machine/_mcontext.h:31:2: error: architecture not supported
#     ERROR:bindgen: fatal error: too many errors emitted, stopping now [-ferror-limit=]

rust-bindgen/target/release/bindgen \
    --convert-macros \
    ../platform/hal/inc/fsl_gpio_hal.h \
\
\
    -- \
    -DCPU_MKL27Z64VLH4 \
\
\
    -I../platform/CMSIS/Include \
    -I../platform/composite/inc \
    -I../platform/devices/MK02F12810/include \
    -I../platform/devices/MK02F12810/startup \
    -I../platform/devices/MK10D10/include \
    -I../platform/devices/MK10D10/startup \
    -I../platform/devices/MK11DA5/include \
    -I../platform/devices/MK11DA5/startup \
    -I../platform/devices/MK20D10/include \
    -I../platform/devices/MK20D10/startup \
    -I../platform/devices/MK21DA5/include \
    -I../platform/devices/MK21DA5/startup \
    -I../platform/devices/MK21FA12/include \
    -I../platform/devices/MK21FA12/startup \
    -I../platform/devices/MK22F12810/include \
    -I../platform/devices/MK22F12810/startup \
    -I../platform/devices/MK22F25612/include \
    -I../platform/devices/MK22F25612/startup \
    -I../platform/devices/MK22F51212/include \
    -I../platform/devices/MK22F51212/startup \
    -I../platform/devices/MK22FA12/include \
    -I../platform/devices/MK22FA12/startup \
    -I../platform/devices/MK24F12/include \
    -I../platform/devices/MK24F12/startup \
    -I../platform/devices/MK24F25612/include \
    -I../platform/devices/MK24F25612/startup \
    -I../platform/devices/MK26F18/include \
    -I../platform/devices/MK26F18/startup \
    -I../platform/devices/MK30D10/include \
    -I../platform/devices/MK30D10/startup \
    -I../platform/devices/MK40D10/include \
    -I../platform/devices/MK40D10/startup \
    -I../platform/devices/MK50D10/include \
    -I../platform/devices/MK50D10/startup \
    -I../platform/devices/MK51D10/include \
    -I../platform/devices/MK51D10/startup \
    -I../platform/devices/MK52D10/include \
    -I../platform/devices/MK52D10/startup \
    -I../platform/devices/MK53D10/include \
    -I../platform/devices/MK53D10/startup \
    -I../platform/devices/MK60D10/include \
    -I../platform/devices/MK60D10/startup \
    -I../platform/devices/MK63F12/include \
    -I../platform/devices/MK63F12/startup \
    -I../platform/devices/MK64F12/include \
    -I../platform/devices/MK64F12/startup \
    -I../platform/devices/MK65F18/include \
    -I../platform/devices/MK65F18/startup \
    -I../platform/devices/MK66F18/include \
    -I../platform/devices/MK66F18/startup \
    -I../platform/devices/MK80F25615/include \
    -I../platform/devices/MK80F25615/startup \
    -I../platform/devices/MKL02Z4/include \
    -I../platform/devices/MKL02Z4/startup \
    -I../platform/devices/MKL03Z4/include \
    -I../platform/devices/MKL03Z4/startup \
    -I../platform/devices/MKL13Z644/include \
    -I../platform/devices/MKL13Z644/startup \
    -I../platform/devices/MKL14Z4/include \
    -I../platform/devices/MKL14Z4/startup \
    -I../platform/devices/MKL15Z4/include \
    -I../platform/devices/MKL15Z4/startup \
    -I../platform/devices/MKL16Z4/include \
    -I../platform/devices/MKL16Z4/startup \
    -I../platform/devices/MKL17Z4/include \
    -I../platform/devices/MKL17Z4/startup \
    -I../platform/devices/MKL17Z644/include \
    -I../platform/devices/MKL17Z644/startup \
    -I../platform/devices/MKL24Z4/include \
    -I../platform/devices/MKL24Z4/startup \
    -I../platform/devices/MKL25Z4/include \
    -I../platform/devices/MKL25Z4/startup \
    -I../platform/devices/MKL26Z4/include \
    -I../platform/devices/MKL26Z4/startup \
    -I../platform/devices/MKL27Z4/include \
    -I../platform/devices/MKL27Z4/startup \
    -I../platform/devices/MKL27Z644/include \
    -I../platform/devices/MKL27Z644/startup \
    -I../platform/devices/MKL33Z4/include \
    -I../platform/devices/MKL33Z4/startup \
    -I../platform/devices/MKL33Z644/include \
    -I../platform/devices/MKL33Z644/startup \
    -I../platform/devices/MKL34Z4/include \
    -I../platform/devices/MKL34Z4/startup \
    -I../platform/devices/MKL36Z4/include \
    -I../platform/devices/MKL36Z4/startup \
    -I../platform/devices/MKL43Z4/include \
    -I../platform/devices/MKL43Z4/startup \
    -I../platform/devices/MKL46Z4/include \
    -I../platform/devices/MKL46Z4/startup \
    -I../platform/devices/MKM34Z7/include \
    -I../platform/devices/MKM34Z7/startup \
    -I../platform/devices/MKV10Z1287/include \
    -I../platform/devices/MKV10Z1287/startup \
    -I../platform/devices/MKV10Z7/include \
    -I../platform/devices/MKV10Z7/startup \
    -I../platform/devices/MKV11Z7/include \
    -I../platform/devices/MKV11Z7/startup \
    -I../platform/devices/MKV30F12810/include \
    -I../platform/devices/MKV30F12810/startup \
    -I../platform/devices/MKV31F12810/include \
    -I../platform/devices/MKV31F12810/startup \
    -I../platform/devices/MKV31F25612/include \
    -I../platform/devices/MKV31F25612/startup \
    -I../platform/devices/MKV31F51212/include \
    -I../platform/devices/MKV31F51212/startup \
    -I../platform/devices/MKW01Z4/include \
    -I../platform/devices/MKW01Z4/startup \
    -I../platform/devices/MKW20Z4/include \
    -I../platform/devices/MKW20Z4/startup \
    -I../platform/devices/MKW21D5/include \
    -I../platform/devices/MKW21D5/startup \
    -I../platform/devices/MKW22D5/include \
    -I../platform/devices/MKW22D5/startup \
    -I../platform/devices/MKW24D5/include \
    -I../platform/devices/MKW24D5/startup \
    -I../platform/devices/MKW30Z4/include \
    -I../platform/devices/MKW30Z4/startup \
    -I../platform/devices/MKW40Z4/include \
    -I../platform/devices/MKW40Z4/startup \
    -I../platform/devices \
    -I../platform/drivers/inc \
    -I../platform/drivers/src/flash/C90TFS/drvsrc/include \
    -I../platform/drivers/src/mmcau/asm-cm0p \
    -I../platform/drivers/src/mmcau/asm-cm4 \
    -I../platform/drivers/src/smartcard/interface \
    -I../platform/hal/inc \
    -I../platform/hal/src/sim/MK02F12810 \
    -I../platform/hal/src/sim/MK10D10 \
    -I../platform/hal/src/sim/MK11DA5 \
    -I../platform/hal/src/sim/MK20D10 \
    -I../platform/hal/src/sim/MK21DA5 \
    -I../platform/hal/src/sim/MK21FA12 \
    -I../platform/hal/src/sim/MK22F12810 \
    -I../platform/hal/src/sim/MK22F25612 \
    -I../platform/hal/src/sim/MK22F51212 \
    -I../platform/hal/src/sim/MK22FA12 \
    -I../platform/hal/src/sim/MK24F12 \
    -I../platform/hal/src/sim/MK24F25612 \
    -I../platform/hal/src/sim/MK26F18 \
    -I../platform/hal/src/sim/MK30D10 \
    -I../platform/hal/src/sim/MK40D10 \
    -I../platform/hal/src/sim/MK50D10 \
    -I../platform/hal/src/sim/MK51D10 \
    -I../platform/hal/src/sim/MK52D10 \
    -I../platform/hal/src/sim/MK53D10 \
    -I../platform/hal/src/sim/MK60D10 \
    -I../platform/hal/src/sim/MK63F12 \
    -I../platform/hal/src/sim/MK64F12 \
    -I../platform/hal/src/sim/MK65F18 \
    -I../platform/hal/src/sim/MK66F18 \
    -I../platform/hal/src/sim/MK80F25615 \
    -I../platform/hal/src/sim/MKL02Z4 \
    -I../platform/hal/src/sim/MKL03Z4 \
    -I../platform/hal/src/sim/MKL13Z644 \
    -I../platform/hal/src/sim/MKL14Z4 \
    -I../platform/hal/src/sim/MKL15Z4 \
    -I../platform/hal/src/sim/MKL16Z4 \
    -I../platform/hal/src/sim/MKL17Z4 \
    -I../platform/hal/src/sim/MKL17Z644 \
    -I../platform/hal/src/sim/MKL24Z4 \
    -I../platform/hal/src/sim/MKL25Z4 \
    -I../platform/hal/src/sim/MKL26Z4 \
    -I../platform/hal/src/sim/MKL27Z4 \
    -I../platform/hal/src/sim/MKL27Z644 \
    -I../platform/hal/src/sim/MKL33Z4 \
    -I../platform/hal/src/sim/MKL33Z644 \
    -I../platform/hal/src/sim/MKL34Z4 \
    -I../platform/hal/src/sim/MKL36Z4 \
    -I../platform/hal/src/sim/MKL43Z4 \
    -I../platform/hal/src/sim/MKL46Z4 \
    -I../platform/hal/src/sim/MKM34Z7 \
    -I../platform/hal/src/sim/MKV10Z1287 \
    -I../platform/hal/src/sim/MKV10Z7 \
    -I../platform/hal/src/sim/MKV11Z7 \
    -I../platform/hal/src/sim/MKV30F12810 \
    -I../platform/hal/src/sim/MKV31F12810 \
    -I../platform/hal/src/sim/MKV31F25612 \
    -I../platform/hal/src/sim/MKV31F51212 \
    -I../platform/hal/src/sim/MKW01Z4 \
    -I../platform/hal/src/sim/MKW20Z4 \
    -I../platform/hal/src/sim/MKW21D5 \
    -I../platform/hal/src/sim/MKW22D5 \
    -I../platform/hal/src/sim/MKW24D5 \
    -I../platform/hal/src/sim/MKW30Z4 \
    -I../platform/hal/src/sim/MKW40Z4 \
    -I../platform/osa/inc \
    -I../platform \
    -I../platform/system/inc \
    -I../platform/system/src/clock/MK02F12810 \
    -I../platform/system/src/clock/MK10D10 \
    -I../platform/system/src/clock/MK11DA5 \
    -I../platform/system/src/clock/MK20D10 \
    -I../platform/system/src/clock/MK21DA5 \
    -I../platform/system/src/clock/MK21FA12 \
    -I../platform/system/src/clock/MK22F12810 \
    -I../platform/system/src/clock/MK22F25612 \
    -I../platform/system/src/clock/MK22F51212 \
    -I../platform/system/src/clock/MK22FA12 \
    -I../platform/system/src/clock/MK24F12 \
    -I../platform/system/src/clock/MK24F25612 \
    -I../platform/system/src/clock/MK26F18 \
    -I../platform/system/src/clock/MK30D10 \
    -I../platform/system/src/clock/MK40D10 \
    -I../platform/system/src/clock/MK50D10 \
    -I../platform/system/src/clock/MK51D10 \
    -I../platform/system/src/clock/MK52D10 \
    -I../platform/system/src/clock/MK53D10 \
    -I../platform/system/src/clock/MK60D10 \
    -I../platform/system/src/clock/MK63F12 \
    -I../platform/system/src/clock/MK64F12 \
    -I../platform/system/src/clock/MK65F18 \
    -I../platform/system/src/clock/MK66F18 \
    -I../platform/system/src/clock/MK80F25615 \
    -I../platform/system/src/clock/MKL02Z4 \
    -I../platform/system/src/clock/MKL03Z4 \
    -I../platform/system/src/clock/MKL13Z644 \
    -I../platform/system/src/clock/MKL14Z4 \
    -I../platform/system/src/clock/MKL15Z4 \
    -I../platform/system/src/clock/MKL16Z4 \
    -I../platform/system/src/clock/MKL17Z4 \
    -I../platform/system/src/clock/MKL17Z644 \
    -I../platform/system/src/clock/MKL24Z4 \
    -I../platform/system/src/clock/MKL25Z4 \
    -I../platform/system/src/clock/MKL26Z4 \
    -I../platform/system/src/clock/MKL27Z4 \
    -I../platform/system/src/clock/MKL27Z644 \
    -I../platform/system/src/clock/MKL33Z4 \
    -I../platform/system/src/clock/MKL33Z644 \
    -I../platform/system/src/clock/MKL34Z4 \
    -I../platform/system/src/clock/MKL36Z4 \
    -I../platform/system/src/clock/MKL43Z4 \
    -I../platform/system/src/clock/MKL46Z4 \
    -I../platform/system/src/clock/MKM34Z7 \
    -I../platform/system/src/clock/MKV10Z1287 \
    -I../platform/system/src/clock/MKV10Z7 \
    -I../platform/system/src/clock/MKV11Z7 \
    -I../platform/system/src/clock/MKV30F12810 \
    -I../platform/system/src/clock/MKV31F12810 \
    -I../platform/system/src/clock/MKV31F25612 \
    -I../platform/system/src/clock/MKV31F51212 \
    -I../platform/system/src/clock/MKW01Z4 \
    -I../platform/system/src/clock/MKW20Z4 \
    -I../platform/system/src/clock/MKW21D5 \
    -I../platform/system/src/clock/MKW22D5 \
    -I../platform/system/src/clock/MKW24D5 \
    -I../platform/system/src/clock/MKW30Z4 \
    -I../platform/system/src/clock/MKW40Z4 \
    -I../platform/system/src/power \
    -I../platform/utilities/inc \
    -I../platform/utilities/inc/virtual_com \
    -I../platform/utilities/src \
        > bindings.rs

exit 0
