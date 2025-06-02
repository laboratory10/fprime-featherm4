// ======================================================================
// \title Console.hpp
// \brief FeatherM4 definitions for Os::Console. Heavily based on 
//        the fprime-arduino library.
// ======================================================================
#ifndef FEATHERM4_OS_CONSOLE_HPP
#define FEATHERM4_OS_CONSOLE_HPP
#include <Os/Console.hpp>
#include <FprimeFeatherM4.hpp>
namespace Os {
namespace FeatherM4 {

//! ConsoleHandle class definition for stub implementations.
//!
struct StreamConsoleHandle : public ConsoleHandle {
    Stream* m_stream = nullptr;
    //! \brief set the stream handler
    void setStreamHandler(Stream& stream);
};

//! \brief implementation of Os::Console that routes to an FeatherM4 stream
//!
class StreamConsole : public ConsoleInterface {
  public:
    //! \brief constructor
    //!
    StreamConsole() = default;

    //! \brief copy constructor
    StreamConsole(const StreamConsole& other) = default;

    //! \brief default copy assignment
    StreamConsole& operator=(const StreamConsole& other) = default;

    //! \brief destructor
    //!
    ~StreamConsole() override = default;

    // ------------------------------------
    // Functions overrides
    // ------------------------------------

    //! \brief write message to console
    //!
    //! Write a message to the console with a bounded size. This will use the active file descriptor as the output
    //! destination.
    //!
    //! \param message: raw message to write
    //! \param size: size of the message to write to the console
    void writeMessage(const CHAR *message, const FwSizeType size) override;

    //! \brief returns the raw console handle
    //!
    //! Gets the raw console handle from the implementation. Note: users must include the implementation specific
    //! header to make any real use of this handle. Otherwise it will be as an opaque type.
    //!
    //! \return raw console handle
    //!
    ConsoleHandle *getHandle() override;
  private:
    //! File handle for PosixFile
    StreamConsoleHandle m_handle;
};
} // namespace FeatherM4
} // namespace Os

#endif // FEATHERM4_OS_CONSOLE_HPP