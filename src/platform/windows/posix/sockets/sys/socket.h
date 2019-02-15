/*/
///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
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
///   File: socket.h
///
/// Author: $author$
///   Date: 9/24/2018
///////////////////////////////////////////////////////////////////////
/*/
#ifndef _PLATFORM_WINDOWS_POSIX_SOCKETS_SYS_SOCKET_H
#define _PLATFORM_WINDOWS_POSIX_SOCKETS_SYS_SOCKET_H

#define SHUT_RD SD_RECEIVE
#define SHUT_WR SD_SEND
#define SHUT_RDWR SD_BOTH

#if defined(__cplusplus)
namespace platform {
namespace windows {
namespace posix {
namespace sockets {
namespace sys {
#endif /*/ defined(__cplusplus) /*/

#if defined(__cplusplus)
} /*/ namespace sys /*/
} /*/ namespace sockets /*/
} /*/ namespace posix /*/
} /*/ namespace windows /*/
} /*/ namespace platform /*/
#endif /*/ defined(__cplusplus) /*/

#endif /*/ _PLATFORM_WINDOWS_POSIX_SOCKETS_SYS_SOCKET_H /*/

