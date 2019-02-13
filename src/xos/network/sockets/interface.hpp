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
#ifndef _XOS_NETWORK_SOCKETS_INTERFACE_HPP
#define _XOS_NETWORK_SOCKETS_INTERFACE_HPP

#include "xos/network/sockets/address.hpp"
#include "xos/network/sockets/transport.hpp"
#include "xos/network/sockets/endpoint.hpp"
#include "xos/network/interface.hpp"

namespace xos {
namespace network {
namespace sockets {

typedef int backlog_t;
enum {
    backlog_none = 0,
    backlog_default = SOMAXCONN
};

typedef int send_flags_t;
enum {
    send_flags_default = 0
};
typedef int recv_flags_t;
enum {
    recv_flags_default = 0
};

typedef int opt_level_t;
typedef int opt_name_t;
typedef int linger_seconds_t;
enum {
    linger_seconds_none = 0,
    linger_seconds_default = 10
};
typedef int shutdown_how_t;
enum {
    shutdown_none = 0,
    shutdown_read = 1,
    shutdown_write = 2,
    shutdown_both = (shutdown_read | shutdown_write)
};

typedef address_family_t domain_t;
typedef transport_type_t type_t;
typedef transport_protocol_t protocol_t;

class _EXPORT_CLASS interface;
class _EXPORT_CLASS interface_implemented;
///////////////////////////////////////////////////////////////////////
///  Class: interfacet
///////////////////////////////////////////////////////////////////////
template <class TImplements = network::interface>
class _EXPORT_CLASS interfacet: virtual public TImplements {
public:
    typedef TImplements implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool open(const transport& tp) {
        domain_t domain = tp.domain();
        type_t type = tp.type();
        protocol_t protocol = tp.protocol();
        
        IS_LOGGED_DEBUG("this->open(domain = " << domain << ", type = " << type << ", protocol = " << protocol << ")...");
        if ((this->open(domain, type, protocol))) {
            return true;
        } else {
            IS_LOGGED_ERROR("...failed on this->open(domain = " << domain << ", type = " << type << ", protocol = " << protocol << ")");
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool connect(const endpoint& ep) {
        sockaddr_t* addr = 0;
        socklen_t addrlen = 0;
        if ((addr = ep.socket_address(addrlen))) {
            if ((this->connect(addr, addrlen))) {
                return true;
            }
        }
        return false;
    }
    virtual bool bind(const endpoint& ep) {
        sockaddr_t* addr = 0;
        socklen_t addrlen = 0;
        if ((addr = ep.socket_address(addrlen))) {
            if ((this->bind(addr, addrlen))) {
                return true;
            }
        }
        return false;
    }
    virtual bool listen(const endpoint& ep) {
        sockaddr_t* addr = 0;
        socklen_t addrlen = 0;
        if ((addr = ep.socket_address(addrlen))) {
            if ((this->bind(addr, addrlen))) {
                if ((this->listen())) {
                    return true;
                }
            }
        }
        return false;
    }
    virtual bool accept(interface_implemented& sk, const endpoint& ep) {
        sockaddr_t* addr = 0;
        socklen_t addrlen = 0;
        if ((addr = ep.socket_address(addrlen))) {
            if ((this->accept(sk, addr, addrlen))) {
                return true;
            }
        }
        return false; 
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool open(domain_t domain, type_t type, protocol_t protocol) {
        return false;
    }
    virtual bool close() {
        return false;
    }
    virtual bool shutdown(shutdown_how_t how) {
        return false;
    }
    virtual bool shutdown() {
        shutdown_how_t how = shutdown_both;
        return this->shutdown(how);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool connect(const sockaddr_t* addr, socklen_t addrlen) {
        return false; 
    }
    virtual bool bind(const sockaddr_t* addr, socklen_t addrlen) {
        return false; 
    }
    virtual bool accept
    (interface_implemented& sock, sockaddr_t* addr, socklen_t& addrlen) {
        return false; 
    }
    virtual bool listen(backlog_t backlog) { 
        return false; 
    }
    virtual bool listen() {
        backlog_t backlog = this->default_backlog();
        return this->listen(backlog);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual backlog_t default_backlog() const {
        return backlog_default;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual interface_implemented* implemented() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef interfacet<> interface_implement;

///////////////////////////////////////////////////////////////////////
///  Class: interface
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS interface: virtual public interface_implement {
public:
    typedef interface_implement implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using implements::accept;
    virtual bool accept
    (interface& sock, sockaddr_t* addr, socklen_t& addrlen) {
        interface_implemented* implemented = 0;
        if ((implemented = sock.implemented())) {
            return accept(*implemented, addr, addrlen);
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual interface* sockets_interface() const {
        return (interface*)this;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

namespace opened {

typedef int socket_attached_t;
typedef int socket_unattached_t;
enum { socket_unattached = 0 };

typedef implement_base interfacet_implements;
typedef base interfacet_extends;
///////////////////////////////////////////////////////////////////////
///  Class: interfacet
///////////////////////////////////////////////////////////////////////
template 
<typename TAttachedTo = socket_attached_t, 
 typename TUnattached = socket_unattached_t,
 TUnattached VUnattached = socket_unattached, 

 class TInterface = sockets::interface,

 class TAttacher = attachert
 <TAttachedTo, TUnattached, VUnattached, TInterface>,

 class TBase = network::extended::interfacet
 <TAttachedTo, TUnattached, VUnattached, TAttacher, base>,

 class TAttached = attachedt
 <TAttachedTo, TUnattached, VUnattached, TInterface, TBase, TAttacher>,

 class TOpened = openedt
 <TAttachedTo, TUnattached, VUnattached, TInterface, TBase, TAttacher, TAttached>,

 class TImplements = TAttacher, class TExtends = TOpened>

class _EXPORT_CLASS interfacet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;

    typedef TAttachedTo attached_t;
    typedef TUnattached unattached_t;
    enum { unattached = VUnattached };

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
    using implements::open;
    virtual bool open(domain_t domain, type_t type, protocol_t protocol) {
        attached_t detached = ((attached_t)unattached);
        if (((attached_t)unattached) != (detached = this->open_attached(domain, type, protocol))) {
            this->set_is_open();
            return true;
        }
        return false;
    }
    virtual bool close() {
        attached_t detached = ((attached_t)unattached);
        if (((attached_t)unattached) != (detached = this->detach())) {
            if ((this->close_detached(detached))) {
                this->set_is_open(false);
                return true;
            }
        }
        return false;
    }
    using implements::shutdown;
    virtual bool shutdown(shutdown_how_t how) {
        attached_t detached = ((attached_t)unattached);
        if (((attached_t)unattached) != (detached = this->attached_to())) {
            if ((this->shutdown_detached(detached, how))) {
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using implements::connect;
    virtual bool connect(const sockaddr_t* addr, socklen_t addrlen) {
        attached_t detached = ((attached_t)unattached);
        if (((attached_t)unattached) != (detached = this->attached_to())) {
            if ((connect_detached(detached, addr, addrlen))) {
                return true;
            }
        }
        return false; 
    }
    using implements::bind;
    virtual bool bind(const sockaddr_t* addr, socklen_t addrlen) {
        attached_t detached = ((attached_t)unattached);
        if (((attached_t)unattached) != (detached = this->attached_to())) {
            if ((bind_detached(detached, addr, addrlen))) {
                return true;
            }
        }
        return false; 
    }
    using implements::accept;
    virtual bool accept
    (interface_implemented& sock, sockaddr_t* addr, socklen_t& addrlen) {
        attached_t detached = ((attached_t)unattached);
        if (((attached_t)unattached) != (detached = this->attached_to())) {
            if ((accept_detached(detached, sock, addr, addrlen))) {
                return true;
            }
        }
        return false; 
    }
    using implements::listen;
    virtual bool listen(backlog_t backlog) { 
        attached_t detached = ((attached_t)unattached);
        if (((attached_t)unattached) != (detached = this->attached_to())) {
            if ((listen_detached(detached, backlog))) {
                return true;
            }
        }
        return false; 
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    //using implements::send;
    virtual ssize_t send(const void* buf, size_t len, send_flags_t flags) {
        attached_t detached = ((attached_t)unattached);
        if (((attached_t)unattached) != (detached = this->attached_to())) {
            ssize_t count = this->send_detached(detached, buf, len, flags);
            return count;
        }
        return -1;
    }
    //using implements::recv;
    virtual ssize_t recv(void* buf, size_t len, recv_flags_t flags) {
        attached_t detached = ((attached_t)unattached);
        if (((attached_t)unattached) != (detached = this->attached_to())) {
            ssize_t count = this->recv_detached(detached, buf, len, flags);
            return count;
        }
        return -1;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t open_attached(domain_t domain, type_t type, protocol_t protocol) {
        attached_t detached = ((attached_t)unattached);
        if ((this->closed())) {
            if (((attached_t)unattached) != (detached = open_detached(domain, type, protocol))) {
                this->attach(detached);
            }
        }
        return detached;
    }
    virtual attached_t open_detached(domain_t domain, type_t type, protocol_t protocol) const {
        attached_t detached = ((attached_t)unattached);
        return detached;
    }
    virtual bool close_detached(attached_t detached) const {
        if (((attached_t)unattached) != (detached)) {
        }
        return false;
    }
    virtual bool shutdown_detached(attached_t detached, shutdown_how_t how) const {
        if (((attached_t)unattached) != (detached)) {
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool connect_detached
    (attached_t detached, const sockaddr_t* addr, socklen_t addrlen) const {
        if (((attached_t)unattached) != (detached)) {
        }
        return false;
    }
    virtual bool bind_detached
    (attached_t detached, const sockaddr_t* addr, socklen_t addrlen) const {
        if (((attached_t)unattached) != (detached)) {
        }
        return false; 
    }
    virtual bool accept_detached
    (attached_t detached, interface_implemented& sock, sockaddr_t* addr, socklen_t& addrlen) const {
        if (((attached_t)unattached) != (detached)) {
        }
        return false; 
    }
    virtual bool listen_detached(attached_t detached, backlog_t backlog) const { 
        if (((attached_t)unattached) != (detached)) {
        }
        return false; 
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t send_detached
    (attached_t detached, const void* buf, size_t len, send_flags_t flags) const {
        if (((attached_t)unattached) != (detached)) {
        }
        return -1;
    }
    virtual ssize_t recv_detached
    (attached_t detached, void* buf, size_t len, recv_flags_t flags) const {
        if (((attached_t)unattached) != (detached)) {
        }
        return -1;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS interfacet
typedef interfacet<> interface;

} /// namespace opened

} /// namespace sockets
} /// namespace network
} /// namespace xos

#endif /// _XOS_NETWORK_SOCKETS_INTERFACE_HPP 
