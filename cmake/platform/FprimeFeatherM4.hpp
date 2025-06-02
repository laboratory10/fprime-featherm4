// ======================================================================
// \title FprimeFeatherM4.hpp
// \brief Compatability header to include Arduino.h in fprime-featherm4.
//        Heavily based on fprime-arduino library.
// ======================================================================
#ifndef FPRIMEFEATHERM4_HPP
#define FPRIMEFEATHERM4_HPP
#undef DEPRECATED // Undefine in preparation for arduino's definition
#include <Arduino.h>
#undef DEPRECATED // Undefine arduino's definitions
#define DEPRECATED(X,Y)

/**
 * Arduino.h often uses #define constants to setup values like HIGH and LOW. This means that other tokens that contain
 * these #define constants get clobbered by the preprocessor. This remap pulls these tokens into enumeration constants,
 * where possible, to side-step this issue.
 *
 * Examples:
 *   HIGH -> Arduino::DEF_HIGH
 *   LOW -> Arduino::DEF_LOW
 *
 */
namespace FeatherM4 {
    enum ARDUINO_DEFINITION_REMAP {
        DEF_HIGH = HIGH,
        DEF_LOW = LOW,
        DEF_INPUT = INPUT,
        DEF_OUTPUT = OUTPUT,
        DEF_INPUT_PULLUP = INPUT_PULLUP,
        #ifdef LED_BUILTIN
            DEF_LED_BUILTIN = LED_BUILTIN
        #else
            DEF_LED_BUILTIN = -1
        #endif //LED_BUILTIN
    }; 
}; // namespace FeatherM4
#undef INPUT
#undef OUTPUT
#undef INPUT_PULLUP
#undef HIGH
#undef LOW
#undef LED_BUILTIN
#undef SERIAL_BUFFER_SIZE
#undef DEFAULT
#undef DISABLED

#endif  // FPRIMEFEATHERM4_HPP
