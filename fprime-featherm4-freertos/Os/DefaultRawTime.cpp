// ======================================================================
// \title DefaultRawTime.cpp
// \brief sets default Os::RawTime to FeatherM4 implementation via linker
// ======================================================================
#include "fprime-featherm4-freertos/Os/RawTime.hpp"
#include "Os/Delegate.hpp"

namespace Os {

//! \brief get a delegate for RawTimeInterface that intercepts calls for stub RawTime usage
//! \param aligned_new_memory: aligned memory to fill
//! \param to_copy: pointer to copy-constructor input
//! \return: pointer to delegate
RawTimeInterface *RawTimeInterface::getDelegate(RawTimeHandleStorage& aligned_placement_new_memory, const RawTimeInterface* to_copy) {
    return Os::Delegate::makeDelegate<RawTimeInterface, Os::FeatherM4::FeatherM4RawTime, RawTimeHandleStorage>(
            aligned_placement_new_memory, to_copy
    );
}

} // namespace Os