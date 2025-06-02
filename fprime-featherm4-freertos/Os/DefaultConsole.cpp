// ======================================================================
// \title DefaultConsole.cpp
// \brief sets default Os::Console to FeatherM4 implementation via linker
// ======================================================================
#include "Os/Console.hpp"
#include "fprime-featherm4-freertos/Os/Console.hpp"
#include "Os/Delegate.hpp"

namespace Os {
ConsoleInterface* ConsoleInterface::getDelegate(ConsoleHandleStorage& aligned_new_memory, const ConsoleInterface* to_copy) {
    return Os::Delegate::makeDelegate<ConsoleInterface, Os::FeatherM4::StreamConsole>(aligned_new_memory, to_copy);
}
}