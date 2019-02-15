///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2019 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: sockets.hpp
///
/// Author: $author$
///   Date: 2/14/2019
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_SOCKETS_MICROSOFT_WINDOWS_SOCKETS_HPP
#define _XOS_NETWORK_SOCKETS_MICROSOFT_WINDOWS_SOCKETS_HPP

#include "xos/network/sockets/microsoft/windows/os.hpp"
#include "xos/base/logged.hpp"
#include "xos/io/logger.hpp"

#if defined(WINSOCK_2)
#define WINSOCK_VERSION_MAJOR 2
#define WINSOCK_VERSION_MINOR 2
#else // defined(WINSOCK_2)
#define WINSOCK_VERSION_MAJOR 1
#define WINSOCK_VERSION_MINOR 1
#endif // defined(WINSOCK_2)

namespace xos {
namespace network {
namespace sockets {
namespace microsoft {
namespace windows {

///////////////////////////////////////////////////////////////////////
///  Class: sockets
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS sockets: public xos::extended::logged {
public:
    typedef xos::extended::logged extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    sockets(const sockets &copy) {
    }
    sockets() {
    }
    virtual ~sockets() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool startup() {
        size_t& startedup = this->startedup();
        if ((startedup++)) {
            return true;
        } else {
            BYTE wsaVersionMajor = WINSOCK_VERSION_MAJOR,
                 wsaVersionMinor = WINSOCK_VERSION_MINOR;
            WORD wsaVersion = MAKEWORD(wsaVersionMajor, wsaVersionMinor);
            WSADATA wsaData;

            IS_LOGGED_DEBUG("::memset(&wsaData, 0, sizeof(WSADATA))...");
            ::memset(&wsaData, 0, sizeof(WSADATA));

            IS_LOGGED_DEBUG("::WSAStartup(wsaVersion = " << wsaVersion << ",...)...");
            if (SOCKET_ERROR != (::WSAStartup(wsaVersion, &wsaData))) {
                IS_LOGGED_DEBUG("...::WSAStartup(wsaVersion = " << wsaVersion << ",...)");
                return true;
            } else {
                int error = ::WSAGetLastError();
                IS_LOGGED_ERROR("...failed error = " << error << " on ::WSAStartup(wsaVersion = " << wsaVersion << ",...)");
            }
            --startedup;
        }
        return false;
    }
    virtual bool cleanup() {
        size_t& startedup = this->startedup();
        if (0 < (startedup)) {
            if ((--startedup)) {
                return true;
            } else {
                IS_LOGGED_DEBUG("::WSACleanup()...");
                if (SOCKET_ERROR != (::WSACleanup())) {
                    IS_LOGGED_DEBUG("...::WSACleanup()");
                    return true;
                } else {
                    int error = ::WSAGetLastError();
                    IS_LOGGED_ERROR("...failed error = " << error << " on ::WSACleanup()");
                }
            }
        }
        return false;
    }
    virtual size_t& startedup() const {
        static size_t startedup = 0;
        return ((size_t&)startedup);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS sockets

} /// namespace windows
} /// namespace microsoft
} /// namespace sockets
} /// namespace network
} /// namespace xos

#endif /// _XOS_NETWORK_SOCKETS_MICROSOFT_WINDOWS_SOCKETS_HPP 
