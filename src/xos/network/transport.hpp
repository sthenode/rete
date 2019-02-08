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
#ifndef _XOS_NETWORK_TRANSPORT_HPP
#define _XOS_NETWORK_TRANSPORT_HPP

#include "xos/base/base.hpp"

#include <sys/socket.h>

namespace xos {
namespace network {

typedef int transport_domain_t;
typedef int transport_type_t;
typedef int transport_protocol_t;

enum { transport_domain_unspec = 0 };
enum { transport_type_unspec = 0 };
enum { transport_protocol_unspec = 0 };

typedef implement_base transportt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: transportt
///////////////////////////////////////////////////////////////////////
template 
<typename TDomain = transport_domain_t,
 typename TType = transport_type_t,
 typename TProtocol = transport_protocol_t,
 class TImplements = transportt_implements>

class _EXPORT_CLASS transportt: virtual public TImplements {
public:
    typedef TImplements implements;

    typedef TDomain domain_t;
    typedef TType type_t;
    typedef TProtocol protocol_t;

    static const domain_t domain_unspec = transport_domain_unspec;
    static const type_t type_unspec = transport_type_unspec;
    static const protocol_t protocol_unspec = transport_protocol_unspec;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual domain_t domain() const {
        return domain_unspec;
    }
    virtual type_t type() const {
        return type_unspec;
    }
    virtual protocol_t protocol() const {
        return protocol_unspec;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS transportt
typedef transportt<> transport;

namespace extended {

typedef network::transport transportt_implements;
typedef base transportt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: transportt
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = transportt_implements, class TExtends = transportt_extends>

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
}; /// class _EXPORT_CLASS transportt
typedef transportt<> transport;

} /// namespace extended

} /// namespace network
} /// namespace xos

#endif /// _XOS_NETWORK_TRANSPORT_HPP 
