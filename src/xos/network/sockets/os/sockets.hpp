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
#ifndef _XOS_NETWORK_SOCKETS_OS_SOCKETS_HPP
#define _XOS_NETWORK_SOCKETS_OS_SOCKETS_HPP

#include "xos/network/sockets/os/os.hpp"

#if defined(WINDOWS)
#include "xos/network/sockets/microsoft/windows/sockets.hpp"
#elif defined(MACOSX)
#include "xos/network/sockets/apple/osx/sockets.hpp"
#elif defined(APPIOS)
#include "xos/network/sockets/apple/ios/sockets.hpp"
#elif defined(LINUX)
#include "xos/network/sockets/linux/sockets.hpp"
#else /// defined(WINDOWS)
#include "xos/network/sockets/posix/sockets.hpp"
#endif /// defined(WINDOWS)

namespace xos {
namespace network {
namespace sockets {
namespace os {

typedef os::sockets sockets;

} /// namespace os
} /// namespace sockets
} /// namespace network
} /// namespace xos

#endif /// _XOS_NETWORK_SOCKETS_OS_SOCKETS_HPP 
