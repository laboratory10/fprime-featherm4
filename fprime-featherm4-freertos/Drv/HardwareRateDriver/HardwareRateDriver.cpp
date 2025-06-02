// ======================================================================
// \title HardwareRateDriver.cpp
// \brief Implementations for a rate group driver designed to work as a 
//        passive component with the FeatherM4 board. Heavily based on 
//        the fprime-arduino library.
// ======================================================================

#include <FpConfig.hpp>
#include <fprime-featherm4-freertos/Drv/HardwareRateDriver/HardwareRateDriver.hpp>
#include <Fw/Logger/Logger.hpp>
#include <FprimeFeatherM4.hpp>

namespace FeatherM4 {

static U32 last_us;
static U32 interval_us;

HardwareRateDriver* HardwareRateDriver::s_driver = NULL;

HardwareRateDriver::HardwareRateDriver(const char* compName)
    : HardwareRateDriverComponentBase(compName), m_interval(std::numeric_limits<U32>::max()) {
    s_driver = this;
}

HardwareRateDriver::~HardwareRateDriver(void) {}


void HardwareRateDriver::configure(U32 intervalMs) {
    m_interval = intervalMs;
}

void HardwareRateDriver::s_timer(void* comp) {
    Os::RawTime now;
    now.now();
    interrupts();  // Enable interrupts so UART RX interrupt handler can receive incoming bytes during remainder of this ISR
    HardwareRateDriver* driver = reinterpret_cast<HardwareRateDriver*>(comp);
    // Check if it is time to run the group
    if(driver->isConnected_CycleOut_OutputPort(0))
    {
        driver->CycleOut_out(0, now);
    }
    driver->m_last = now;
}

void HardwareRateDriver::start() {
    interval_us = m_interval * 1000;
    last_us = micros();
}

void HardwareRateDriver::cycle() {
    if((micros() - last_us) >= interval_us)
    {
        this->s_timerISR();
        last_us += interval_us;
    }
}

void HardwareRateDriver::stop() {
    
}

void HardwareRateDriver::s_timerISR() {    
    s_timer(s_driver);
}
}  // namespace FeatherM4
