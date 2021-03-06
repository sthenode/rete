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
///   File: address.hpp
///
/// Author: $author$
///   Date: 2/6/2019
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_SOCKETS_IP_V6_ADDRESS_HPP
#define _XOS_NETWORK_SOCKETS_IP_V6_ADDRESS_HPP

#include "xos/network/sockets/ip/address.hpp"

namespace xos {
namespace network {
namespace sockets {
namespace ip {
namespace v6 {

typedef network::sockets::ip::address::implements addresst_implements;
typedef network::sockets::ip::address addresst_extends;
///////////////////////////////////////////////////////////////////////
///  Class: addresst
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = addresst_implements, class TExtends = addresst_extends>

class _EXPORT_CLASS addresst: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;

    typedef typename implements::family_t family_t;
    typedef typename implements::version_t version_t;

    static const family_t family_unspec = implements::family_unspec;
    static const version_t version_unspec = implements::version_unspec;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    addresst(const addresst &copy) {
    }
    addresst() {
    }
    virtual ~addresst() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual family_t family() const {
        return AF_INET6;
    }
    virtual version_t version() const {
        return 6;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS addresst
typedef addresst<> address;

} /// namespace v6
} /// namespace ip
} /// namespace sockets
} /// namespace network
} /// namespace xos

#endif /// _XOS_NETWORK_SOCKETS_IP_V6_ADDRESS_HPP 
