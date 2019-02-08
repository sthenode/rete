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
#ifndef _XOS_NETWORK_SOCKETS_ADDRESS_HPP
#define _XOS_NETWORK_SOCKETS_ADDRESS_HPP

#include "xos/network/address.hpp"
#include "xos/network/sockets.hpp"

#include <sys/socket.h>
#include <netdb.h>

namespace xos {
namespace network {
namespace sockets {

typedef network::address addresst_implements;
///////////////////////////////////////////////////////////////////////
///  Class: addresst
///////////////////////////////////////////////////////////////////////
template <class TImplements = addresst_implements>
class _EXPORT_CLASS addresst: virtual public TImplements {
public:
    typedef TImplements implements;

    typedef typename implements::family_t family_t;
    typedef typename implements::version_t version_t;

    static const family_t family_unspec = AF_UNSPEC;
    static const version_t version_unspec = 0;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual family_t family() const {
        return family_unspec;
    }
    virtual version_t version() const {
        return version_unspec;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS addresst
typedef addresst<> address;

namespace extended {

typedef sockets::address addresst_implements;
typedef network::extended::address addresst_extends;
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
}; /// class _EXPORT_CLASS addresst
typedef addresst<> address;

} /// namespace extended

} /// namespace sockets
} /// namespace network
} /// namespace xos

#endif /// _XOS_NETWORK_SOCKETS_ADDRESS_HPP 
