// ======================================================================
// \title RawTime.hpp
// \brief FeatherM4 definitions for Os::RawTime. Heavily based on 
//        the fprime-arduino library.
// ======================================================================
#ifndef FEATHERM4_SVC_FEATHERM4TIME_HPP
#define FEATHERM4_SVC_FEATHERM4TIME_HPP

#include <fprime-featherm4-freertos/Svc/FeatherM4Time/FeatherM4TimeComponentAc.hpp>

namespace FeatherM4 {

class FeatherM4Time : public FeatherM4TimeComponentBase {
  public:
    FeatherM4Time(const char* compName);
    virtual ~FeatherM4Time();

    //! \brief set time for the arduino subsystem
    //!
    void setTime(
        U32 year,             //!< The current year
        U8 month,             //!< The current month (1-12)
        U8 day,               //!< The current day (1-31)
        U8 hour,              //!< The current hour (0-23)
        U8 minute,            //!< The current minute (0-59)
        U8 second             //!< The current second (0-59)
    );

  protected:
    void getTime_handler(FwIndexType portNum, /*!< The port number*/
                         Fw::Time& time       /*!< The time argument to fill*/
    );

    //! Handler implementation for setTime
    //!
    //! Port to set the time
    void setTime_handler(FwIndexType portNum,  //!< The port number
                         U32 year,             //!< The current year
                         U8 month,             //!< The current month (1-12)
                         U8 day,               //!< The current day (1-31)
                         U8 hour,              //!< The current hour (0-23)
                         U8 minute,            //!< The current minute (0-59)
                         U8 second             //!< The current second (0-59)
                         ) override;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command SET_TIME
    //!
    //! Command to set the time
    void SET_TIME_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                        U32 cmdSeq,           //!< The command sequence number
                        U32 year,             //!< The current year
                        U8 month,             //!< The current month (1-12)
                        U8 day,               //!< The current day (1-31)
                        U8 hour,              //!< The current hour (0-23)
                        U8 minute,            //!< The current minute (0-59)
                        U8 second             //!< The current second (0-59)
                        ) override;
};

}  // namespace FeatherM4

#endif // FEATHERM4_SVC_FEATHERM4TIME_HPP
