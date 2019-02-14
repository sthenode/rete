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
///   File: os.hpp
///
/// Author: $author$
///   Date: 2/13/2019
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_SOCKETS_MICROSOFT_WINDOWS_OS_HPP
#define _XOS_NETWORK_SOCKETS_MICROSOFT_WINDOWS_OS_HPP

#include "xos/platform/platform.hpp"

#if !defined(WINDOWS)
#include <sys/socket.h>
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef int SOCKET;
enum { SOCKET_ERROR = -1 };
enum { INVALID_SOCKET = -1 };
enum {
    SD_RECEIVE = SHUT_RD,
    SD_SEND    = SHUT_WR,
    SD_BOTH    = SHUT_RDWR
};
enum {
    DELAY_OPT_OFF = 1,
    DELAY_OPT_ON  = 0
};
enum {
    WSADESCRIPTION_LEN = 128,
    WSASYS_STATUS_LEN  = WSADESCRIPTION_LEN
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef struct WSAData {
  WORD           wVersion;
  WORD           wHighVersion;
  char           szDescription[WSADESCRIPTION_LEN+1];
  char           szSystemStatus[WSASYS_STATUS_LEN+1];
  unsigned short iMaxSockets;
  unsigned short iMaxUdpDg;
  char FAR       *lpVendorInfo;
} WSADATA, *LPWSADATA;

extern "C" {
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int closesocket(
  _In_ SOCKET s
);

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int WSAStartup(
  _In_  WORD      wVersionRequested,
  _Out_ LPWSADATA lpWSAData
);
int WSACleanup(void);
int WSAGetLastError(void);
} /// extern "C"

#else /// !defined(WINDOWS)
enum {
    DELAY_OPT_OFF = 0, /// Note opposite of posix
    DELAY_OPT_ON  = 1  /// Note opposite of posix
};
#endif /// !defined(WINDOWS)

namespace xos {
namespace network {
namespace sockets {
namespace microsoft {
namespace windows {

} /// namespace windows
} /// namespace microsoft
} /// namespace sockets
} /// namespace network
} /// namespace xos

#endif /// _XOS_NETWORK_SOCKETS_MICROSOFT_WINDOWS_OS_HPP 
