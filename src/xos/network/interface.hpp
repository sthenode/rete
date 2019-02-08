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
///   File: interface.hpp
///
/// Author: $author$
///   Date: 2/7/2019
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_INTERFACE_HPP
#define _XOS_NETWORK_INTERFACE_HPP

#include "xos/base/opened.hpp"
#include "xos/base/logged.hpp"
#include "xos/network/transport.hpp"

namespace xos {
namespace network {

namespace sockets {
class _EXPORT_CLASS interface;
} /// namespace sockets

typedef loggedt<opener> interfacet_implements;
///////////////////////////////////////////////////////////////////////
///  Class: interfacet
///////////////////////////////////////////////////////////////////////
template <class TImplements = interfacet_implements>
class _EXPORT_CLASS interfacet: virtual public TImplements {
public:
    typedef TImplements implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool open(const transport& tp) {
        return false;
    }
    virtual bool close() {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const sockets::interface* const_sockets_interface() const {
        return this->sockets_interface();
    }
    virtual sockets::interface* sockets_interface() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS interfacet
typedef interfacet<> interface;

namespace extended {

///////////////////////////////////////////////////////////////////////
///  Class: interfacet
///////////////////////////////////////////////////////////////////////
template 
<typename TAttached = pointer_t, 
 typename TUnattached = int, TUnattached VUnattached = 0,
 class TImplements = interface, class TExtends = openedt
 <TAttached, TUnattached, VUnattached, TImplements, base> >

class _EXPORT_CLASS interfacet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    interfacet(const interfacet &copy): extends(copy) {
    }
    interfacet() {
    }
    virtual ~interfacet() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS interfacet
typedef interfacet<> interface;

} /// namespace extended

} /// namespace network
} /// namespace xos

#endif /// _XOS_NETWORK_INTERFACE_HPP 
