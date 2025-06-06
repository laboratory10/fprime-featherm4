// ======================================================================
// \title FeatherM4Time.cpp
// \brief FeatherM4 implementation for FeatherM4Time. Heavily based on 
//        the fprime-arduino library. The time format is 
//        (U32 seconds, U32 microseconds) and must be mapped to the 
//        Arduino supplied "millis()" and "micros()" functions. Heavily 
//        based on the fprime-arduino library.
// ======================================================================

#include <fprime-featherm4-freertos/Svc/FeatherM4Time/FeatherM4Time.hpp>
#include <TimeLib.h>
#include <FprimeFeatherM4.hpp>

namespace FeatherM4 {

constexpr FwSizeType TIME_ROLLOVER_RETRIES = 3;
constexpr  U32 MICROSECONDS_PER_SECOND = 1000000;

FeatherM4Time::FeatherM4Time(const char* name) : FeatherM4TimeComponentBase(name) {}
FeatherM4Time::~FeatherM4Time() {}

void FeatherM4Time::getTime_handler(NATIVE_INT_TYPE portNum, /*!< The port number*/
                                      Fw::Time& time           /*!< The time to set */
) {
    time_t time_seconds = 0;
    U32 time_microseconds = 0;
    for (FwSizeType i = 0; i < TIME_ROLLOVER_RETRIES; i++) {
        U32 time_microseconds_rollover = ::micros() % MICROSECONDS_PER_SECOND;
        time_seconds = ::now();
        time_microseconds = ::micros() % MICROSECONDS_PER_SECOND;
        // No rollover exit the loop without further retries
        if (time_microseconds > time_microseconds_rollover) {
            break;
        }
    }
    TimeBase base = (::timeStatus() == timeStatus_t::timeNeedsSync) ? TimeBase::TB_PROC_TIME : TimeBase::TB_WORKSTATION_TIME;
    // Look for seconds overflow
    FW_ASSERT(time_seconds < std::numeric_limits<U32>::max());
    time.set(base, static_cast<U32>(time_seconds), time_microseconds);
}

void FeatherM4Time ::setTime(U32 year, U8 month, U8 day, U8 hour, U8 minute, U8 second) {
    year = (year > std::numeric_limits<int>::max()) ? std::numeric_limits<int>::max() : year;
    Fw::Time before_set = this->getTime();
    ::setTime(hour, minute, second, day, month, year);
    Fw::Time after_set = this->getTime();
    this->log_ACTIVITY_HI_TimeUpdate(before_set.getSeconds(), before_set.getUSeconds(), before_set.getTimeBase(),
                                  after_set.getSeconds(), after_set.getUSeconds(), after_set.getTimeBase());
}

void FeatherM4Time ::setTime_handler(FwIndexType portNum, U32 year, U8 month, U8 day, U8 hour, U8 minute, U8 second) {
    this->setTime(year, month, day, hour, minute, second);
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void FeatherM4Time ::SET_TIME_cmdHandler(FwOpcodeType opCode,
                                       U32 cmdSeq,
                                       U32 year,
                                       U8 month,
                                       U8 day,
                                       U8 hour,
                                       U8 minute,
                                       U8 second) {
    this->setTime(year, month, day, hour, minute, second);
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}
}  // namespace FeatherM4
