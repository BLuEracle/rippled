//
// Copyright (c) 2015-2016 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BEAST_CORE_FILE_WIN32_HPP
#define BEAST_CORE_FILE_WIN32_HPP

#include <boost/config.hpp>

#if ! defined(BEAST_USE_WIN32_FILE)
# ifdef BOOST_MSVC
#  define BEAST_USE_WIN32_FILE 1
# else
#  define BEAST_USE_WIN32_FILE 0
# endif
#endif

#if BEAST_USE_WIN32_FILE

#include <beast/core/error.hpp>
#include <beast/core/file_base.hpp>
#include <boost/detail/winapi/basic_types.hpp>
#include <boost/detail/winapi/handles.hpp>
#include <cstdio>
#include <cstdint>

namespace beast {

/** An implementation of File for Win32.

    This class implements a @b File using Win32 native interfaces.
*/
class file_win32
{
    boost::detail::winapi::HANDLE_ h_ =
        boost::detail::winapi::INVALID_HANDLE_VALUE_;

public:
    /** The type of the underlying file handle.

        This is platform-specific.
    */
#if BEAST_DOXYGEN
    using native_handle_type = HANDLE;
#else
    using native_handle_type = boost::detail::winapi::HANDLE_;
#endif

    /** Destructor

        If the file is open it is first closed.
    */
    ~file_win32();

    /** Constructor

        There is no open file initially.
    */
    file_win32() = default;

    /** Constructor

        The moved-from object behaves as if default constructed.
    */
    file_win32(file_win32&& other);

    /** Assignment

        The moved-from object behaves as if default constructed.
    */
    file_win32& operator=(file_win32&& other);

    /// Returns the native handle associated with the file.
    native_handle_type
    native_handle()
    {
        return h_;
    }

    /** Set the native handle associated with the file.

        If the file is open it is first closed.

        @param h The native file handle to assign.
    */
    void
    native_handle(native_handle_type h);

    /// Returns `true` if the file is open
    bool
    is_open() const
    {
        return h_ != boost::detail::winapi::INVALID_HANDLE_VALUE_;
    }

    /** Close the file if open

        @param ec Set to the error, if any occurred.
    */
    void
    close(error_code& ec);

    /** Open a file at the given path with the specified mode

        @param path The utf-8 encoded path to the file

        @param mode The file mode to use

        @param ec Set to the error, if any occurred
    */
    void
    open(char const* path, file_mode mode, error_code& ec);

    /** Return the size of the open file

        @param ec Set to the error, if any occurred

        @return The size in bytes
    */
    std::uint64_t
    size(error_code& ec) const;

    /** Return the current position in the open file

        @param ec Set to the error, if any occurred

        @return The offset in bytes from the beginning of the file
    */
    std::uint64_t
    pos(error_code& ec);

    /** Adjust the current position in the open file

        @param offset The offset in bytes from the beginning of the file

        @param ec Set to the error, if any occurred
    */
    void
    seek(std::uint64_t offset, error_code& ec);

    /** Read from the open file

        @param buffer The buffer for storing the result of the read

        @param n The number of bytes to read

        @param ec Set to the error, if any occurred
    */
    std::size_t
    read(void* buffer, std::size_t n, error_code& ec);

    /** Write to the open file

        @param buffer The buffer holding the data to write

        @param n The number of bytes to write

        @param ec Set to the error, if any occurred
    */
    std::size_t
    write(void const* buffer, std::size_t n, error_code& ec);
};

} // beast

#include <beast/core/impl/file_win32.ipp>

#endif

#endif