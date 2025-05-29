restrict_platforms(ArduinoFw)

# TEMPORARY FIX: Add ASSERT_RELATIVE_PATH definition for FW_ASSERT_LEVEL = FW_RELATIVE_PATH_ASSERT
if(NOT DEFINED ASSERT_RELATIVE_PATH)
    add_definitions(-DASSERT_RELATIVE_PATH="${FPRIME_PROJECT_ROOT}")
endif()

# Include subdirectories
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/fprime-featherm4-freertos/Drv/HardwareRateDriver")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/fprime-featherm4-freertos/Drv/StreamDriver")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/fprime-featherm4-freertos/Os")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/fprime-featherm4-freertos/Svc/ArduinoTime")