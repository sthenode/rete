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
///   File: transport.hpp
///
/// Author: $author$
///   Date: 8/11/2019
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_SOCKETS_IP_V4_UDP_TRANSPORT_HPP
#define _XOS_NETWORK_SOCKETS_IP_V4_UDP_TRANSPORT_HPP

#include "xos/network/sockets/ip/v4/transport.hpp"
#include "xos/network/sockets/ip/udp/transport.hpp"

namespace xos {
namespace network {
namespace sockets {
namespace ip {
namespace v4 {
namespace udp {

typedef ip::udp::transportt<ip::v4::transport> transport;

} /// namespace udp
} /// namespace v4
} /// namespace ip
} /// namespace sockets
} /// namespace network
} /// namespace xos

#endif /// _XOS_NETWORK_SOCKETS_IP_V4_UDP_TRANSPORT_HPP 
