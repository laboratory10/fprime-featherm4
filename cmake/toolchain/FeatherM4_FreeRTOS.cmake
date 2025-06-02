####
# FeatherM4_FreeRTOS.cmake:
#
#
####

set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_PLATFORM "FeatherM4_FreeRTOS")
set(FPRIME_USE_BAREMETAL_SCHEDULER OFF)
set(ARDUINO_BUILD_PROPERTIES)

set(ARDUINO_FQBN "adafruit:samd:adafruit_feather_m4")
add_compile_options(-D_BOARD_FEATHERM4 -DUSE_BASIC_TIMER)
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/featherm4-support.cmake")
