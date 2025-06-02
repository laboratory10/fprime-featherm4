// ======================================================================
// \title RawTime.cpp
// \brief FeatherM4 implementation for Os::RawTime. Heavily based on 
//        the fprime-arduino library.
// ======================================================================
#include "fprime-featherm4-freertos/Os/RawTime.hpp"
#include "FprimeFeatherM4.hpp"
namespace Os {
namespace FeatherM4 {

//! \brief check is a is newer than b
bool isNewer(const FeatherM4RawTimeHandle& a, const FeatherM4RawTimeHandle& b) {
    return ((a.m_seconds > b.m_seconds) ||
           ((a.m_seconds == b.m_seconds) && (a.m_micros >= b.m_seconds)));
}

RawTimeHandle* FeatherM4RawTime::getHandle() {
    return &this->m_handle;
}

RawTime::Status FeatherM4RawTime::now() {
    U32 milliseconds_now = millis();
    U32 microseconds_now = micros() % 1000000;
    U32 milliseconds_no_seconds = milliseconds_now % 1000;
    // Microsecond portion and millisecond portion don't agree, assume roll-over and ask for milliseconds again
    if (milliseconds_no_seconds != (microseconds_now/1000)) {
        microseconds_now = millis();
    }
    this->m_handle.m_micros = microseconds_now % 1000000;
    this->m_handle.m_seconds = milliseconds_now / 1000;
    return Status::OP_OK;
}

RawTime::Status FeatherM4RawTime::getTimeInterval(const Os::RawTime& other, Fw::TimeInterval& interval) const {
    interval.set(0, 0);
    const FeatherM4RawTimeHandle& my_handle = this->m_handle;
    const FeatherM4RawTimeHandle& other_handle = static_cast<const FeatherM4RawTimeHandle&>(*const_cast<Os::RawTime&>(other).getHandle());

    const FeatherM4RawTimeHandle& newer = isNewer(my_handle, other_handle) ? my_handle : other_handle;
    const FeatherM4RawTimeHandle& older = isNewer(my_handle, other_handle) ? other_handle : my_handle;

    if (newer.m_micros < older.m_micros) {
        interval.set(newer.m_seconds - older.m_seconds - 1, 1000000 + newer.m_micros - older.m_micros);
    } else {
        interval.set(newer.m_seconds - older.m_seconds, newer.m_micros - older.m_micros);
    }

    return Status::OP_OK;
}

Fw::SerializeStatus FeatherM4RawTime::serialize(Fw::SerializeBufferBase& buffer) const {
    Fw::SerializeStatus status = Fw::SerializeStatus::FW_SERIALIZE_OK;
    status = buffer.serialize(this->m_handle.m_seconds);
    if (status == Fw::FW_SERIALIZE_OK) {
        status = buffer.serialize(this->m_handle.m_micros);
    }
    return status;
}

Fw::SerializeStatus FeatherM4RawTime::deserialize(Fw::SerializeBufferBase& buffer) {
    Fw::SerializeStatus status = Fw::SerializeStatus::FW_SERIALIZE_OK;
    status = buffer.deserialize(this->m_handle.m_seconds);
    if (status == Fw::FW_SERIALIZE_OK) {
        status = buffer.deserialize(this->m_handle.m_micros);
    }
    return status;
}
}  // namespace FeatherM4
}  // namespace Os