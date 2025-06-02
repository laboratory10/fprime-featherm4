####
# FeatherM4_FreeRTOS.cmake:
#
#
####
if(NOT DEFINED ARDUINO_FQBN)
    message(FATAL_ERROR "Must defined arduino FQBN")
endif()
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
    set(ARDUINO_TYPES_DIR "${CMAKE_CURRENT_LIST_DIR}/types/arm")
else()
    message(FATAL_ERROR "System processor type unsupported")
endif()
set(ARDUINO_PLATFORM_DIR "${CMAKE_CURRENT_LIST_DIR}")

set(CMAKE_EXECUTABLE_SUFFIX "${FPRIME_ARDUINO_EXECUTABLE_SUFFIX}" CACHE INTERNAL "" FORCE)

# Add FPrime OSAL Implementations
choose_fprime_implementation(Os/File Os_File_Stub)
choose_fprime_implementation(Os/Queue Os_Generic_PriorityQueue)
choose_fprime_implementation(Os/Cpu Os/Cpu/Stub)
choose_fprime_implementation(Os/Memory Os/Memory/Stub)

# Add fprime-freertos OSAL Implementations
choose_fprime_implementation(Os/Task Os_Task_FreeRTOS)
choose_fprime_implementation(Os/Mutex Os_Mutex_FreeRTOS)
choose_fprime_implementation(Os/ConditionVariable Os_ConditionVariable_FreeRTOS)


# Add FeatherM4 OSAL Implementations
choose_fprime_implementation(Os/Console Os_Console_FeatherM4)
choose_fprime_implementation(Os/RawTime Os_RawTime_FeatherM4)

include_directories("${ARDUINO_TYPES_DIR}" "${ARDUINO_PLATFORM_DIR}")

