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
///   Date: 2/6/2019
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_SOCKETS_IP_TCP_TRANSPORT_HPP
#define _XOS_NETWORK_SOCKETS_IP_TCP_TRANSPORT_HPP

#include "xos/network/sockets/ip/transport.hpp"

namespace xos {
namespace network {
namespace sockets {
namespace ip {
namespace tcp {

typedef ip::transport::implements transportt_implements;
typedef ip::extended::transport transportt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: transportt
///////////////////////////////////////////////////////////////////////
template <class TImplements = transportt_implements, class TExtends = transportt_extends>
class _EXPORT_CLASS transportt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;

    typedef typename implements::domain_t domain_t;
    typedef typename implements::type_t type_t;
    typedef typename implements::protocol_t protocol_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    transportt(const transportt &copy) {
    }
    transportt() {
    }
    virtual ~transportt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual type_t type() const {
        return SOCK_STREAM;
    }
    virtual protocol_t protocol() const {
        return IPPROTO_TCP;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS transportt
typedef transportt<> transport;

} /// namespace tcp
} /// namespace ip
} /// namespace sockets
} /// namespace network
} /// namespace xos

#endif /// _XOS_NETWORK_SOCKETS_IP_TCP_TRANSPORT_HPP 
