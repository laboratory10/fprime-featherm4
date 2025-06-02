// ======================================================================
// \title StreamDriver.cpp
// \brief Implementations for StreamDriver component. Heavily based on 
//        the fprime-arduino library.
// ======================================================================

#include <fprime-featherm4-freertos/Drv/StreamDriver/StreamDriver.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace FeatherM4 {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

StreamDriver ::StreamDriver(const char* compName)
    : StreamDriverComponentBase(compName),
      m_port_number(0),
      m_port_pointer(static_cast<POINTER_CAST>(NULL)) {}

StreamDriver ::~StreamDriver(void) {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

Drv::SendStatus StreamDriver ::send_handler(const NATIVE_INT_TYPE portNum, Fw::Buffer& fwBuffer) {
    write_data(fwBuffer);
    deallocate_out(0, fwBuffer);
    return Drv::SendStatus::SEND_OK;
}

void StreamDriver ::schedIn_handler(const NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    if (not reinterpret_cast<Stream*>(m_port_pointer)->available()) {
        return;
    }
    
    Fw::Buffer recv_buffer = this->allocate_out(0, SERIAL_BUFFER_SIZE);
    read_data(recv_buffer);
    recv_out(0, recv_buffer, Drv::RecvStatus::RECV_OK);
}

void StreamDriver::configure(Stream* streamDriver) {
    FW_ASSERT(streamDriver != nullptr);
    m_port_pointer = streamDriver;
    if (this->isConnected_ready_OutputPort(0)) {
        this->ready_out(0);
    }
}

void StreamDriver ::write_data(Fw::Buffer& fwBuffer) {
    FW_ASSERT(m_port_pointer != 0);
    reinterpret_cast<Stream*>(m_port_pointer)
        ->write(reinterpret_cast<U8*>(fwBuffer.getData()), fwBuffer.getSize());
}

void StreamDriver ::read_data(Fw::Buffer& fwBuffer) {
    Stream* stream_ptr = reinterpret_cast<Stream*>(m_port_pointer);
    int byte = 0;
    NATIVE_UINT_TYPE count = 0;
    U8* raw_data = reinterpret_cast<U8*>(fwBuffer.getData());
    while ((stream_ptr->available() > 0) && (count < fwBuffer.getSize()) && ((byte = stream_ptr->read()) != -1)) {
        *(raw_data + count) = static_cast<U8>(byte);
        count++;
    }
    fwBuffer.setSize(count);
}

}  // namespace FeatherM4
