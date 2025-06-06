####
# featherm4-warpper.cmake:
#
# Support for the FeatherM4 board using the arduino-cli utility.
# Based heavily on the fprime-arduino library
####

####
# Function `run_arduino_wrapper`:
#
# Runs `arduino-cli` and forwards all supplied arguments to it. Output text will be set into the variable
# `WRAPPER_OUTPUT` for use in the larger program.
#
# Args:
#   *: forwarded as CLI arguments to `arduino-cli`
#
# Returns: WRAPPER_OUTPUT containing standard-output of the `arduino-cli` run.
####
function(run_arduino_wrapper)
    find_program(ARDUINO_WRAPPER NAMES arduino-cli-wrapper)
    if (NOT ARDUINO_WRAPPER)
        message(FATAL_ERROR "arduino-cli-wrapper is required to be on PATH for arduino-support toolchain")
    elseif (NOT DEFINED ARDUINO_FQBN)
        message(FATAL_ERROR "Variable ARDUINO_FQDN must be set to use arduino-support")
    endif()
    set(EXECUTE_ARGS
            "${ARDUINO_WRAPPER}"
            ${ARGN}
            --includes
            --detect-settings
            --post-link
            -o
            "${CMAKE_BINARY_DIR}/arduino-cli-sketch"
            )
    if (CMAKE_DEBUG_OUTPUT)
        list(APPEND EXECUTE_ARGS --debug)
        string(REPLACE ";" " " INVOCATION "${EXECUTE_ARGS}")
        message(STATUS "[arduino-cli] Invocation: ${INVOCATION}")
    endif()

    # Execute the python wrapper
    execute_process(COMMAND
            ${EXECUTE_ARGS}
            OUTPUT_VARIABLE WRAPPER_OUTPUT
            RESULT_VARIABLE RET_CODE
            )
    if (NOT RET_CODE EQUAL 0)
        message(FATAL_ERROR "Could not run 'arduino-cli' please install 'arduino-cli' and board '${ARDUINO_FQBN}'.")
    endif()
    set(WRAPPER_OUTPUT "${WRAPPER_OUTPUT}" PARENT_SCOPE)
endfunction(run_arduino_wrapper)

###
# Function `read_json`:
#
# A wrapper to help read JSON data as native-cmake types.
#
# Args:
#  VARIABLE_NAME: variable to set
#  JSON_DATA: data to mine
#  *: field list (e.g. a.b.c[0] -> a b c 0)
###
function(read_json VARIABLE_NAME JSON_DATA)
    string(JSON FIELD_TYPE TYPE "${JSON_DATA}" ${ARGN})

    # Handle lists
    if (FIELD_TYPE STREQUAL ARRAY)
        set(READ_DATA)
        string(JSON FIELD_LENGTH LENGTH "${JSON_DATA}" ${ARGN})
        math(EXPR FIELD_LENGTH "${FIELD_LENGTH} - 1")
        if (FIELD_LENGTH LESS 0)
            set(READ_DATA "")
        else()
            foreach(INDEX RANGE ${FIELD_LENGTH})
                string(JSON TEMP_DATA GET "${JSON_DATA}" ${ARGN} ${INDEX})
                list(APPEND READ_DATA "${TEMP_DATA}")
            endforeach()
        endif()
    # Standard read
    else()
        string(JSON READ_DATA GET "${JSON_DATA}" ${ARGN} ${INDEX})
    endif()
    set(${VARIABLE_NAME} "${READ_DATA}" PARENT_SCOPE)
endfunction()
