// ======================================================================
// \title StreamDriver.cpp
// \brief Definitions for StreamDriver component. Heavily based on 
//        the fprime-arduino library.
// ======================================================================

#ifndef FEATHERM4_DRV_STREAMDRIVER_HPP
#define FEATHERM4_DRV_STREAMDRIVER_HPP

#include <fprime-featherm4-freertos/Drv/StreamDriver/StreamDriverComponentAc.hpp>
#include "Os/Task.hpp"
#include <FprimeFeatherM4.hpp>

namespace FeatherM4 {
// Allow for setting serial ports on linux from the inputs
#ifndef ARDUINO
extern char** SERIAL_PORT;
#endif

class StreamDriver : public StreamDriverComponentBase {
  public:
    const static FwSizeType SERIAL_BUFFER_SIZE = 64;  // Maximum Arduino buffer size
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object StreamDriver
    //!
    StreamDriver(const char* compName /*!< The component name*/
    );

    //! Destroy object StreamDriver
    //!
    ~StreamDriver(void);

    //! Configure this port
    //!
    void configure(Stream* streamDriver);

  private:
    //! Read the actual data
    void read_data(Fw::Buffer& fwBuffer);
    //! Write the actual data
    void write_data(Fw::Buffer& fwBuffer);
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for send
    //!
    Drv::SendStatus send_handler(const NATIVE_INT_TYPE portNum, /*!< The port number*/
                                 Fw::Buffer& fwBuffer) override;

    //! Handler implementation for schedIn
    //!
    void schedIn_handler(const NATIVE_INT_TYPE portNum, /*!< The port number*/
                         NATIVE_UINT_TYPE context       /*!< The call order*/
    );

    //! Port number to open
    NATIVE_UINT_TYPE m_port_number;
    //! Stores the open stream port, POINTER_CAST so Linux and Ardunio may use different types
    void* m_port_pointer;
};

}  // namespace FeatherM4

#endif // FEATHERM4_DRV_STREAMDRIVER_HPP
