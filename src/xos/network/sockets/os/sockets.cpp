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
///   File: sockets.cpp
///
/// Author: $author$
///   Date: 2/14/2019
///////////////////////////////////////////////////////////////////////
#include "xos/network/sockets/os/sockets.hpp"

#if defined(WINDOWS)
#include "xos/network/sockets/microsoft/windows/sockets.cpp"
#elif defined(MACOSX)
#include "xos/network/sockets/apple/osx/sockets.cpp"
#elif defined(APPIOS)
#include "xos/network/sockets/apple/ios/sockets.cpp"
#elif defined(LINUX)
#include "xos/network/sockets/linux/sockets.cpp"
#else /// defined(WINDOWS)
#include "xos/network/sockets/posix/sockets.cpp"
#endif /// defined(WINDOWS)

namespace xos {
namespace network {
namespace sockets {
namespace os {

} /// namespace os
} /// namespace sockets
} /// namespace network
} /// namespace xos

