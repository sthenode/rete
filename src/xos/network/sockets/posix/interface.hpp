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
#ifndef _XOS_NETWORK_SOCKETS_POSIX_INTERFACE_HPP
#define _XOS_NETWORK_SOCKETS_POSIX_INTERFACE_HPP

#include "xos/network/sockets/interface.hpp"

namespace xos {
namespace network {
namespace sockets {
namespace posix {

typedef int socket_attached_t;
typedef int socket_unattached_t;
enum { socket_unattached = 0 };

typedef sockets::opened::interfacet
<socket_attached_t, socket_unattached_t, socket_unattached> interfacet_extends;
typedef interfacet_extends::implements interfacet_implements;
///////////////////////////////////////////////////////////////////////
///  Class: interfacet
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = interfacet_implements, class TExtends = interfacet_extends>

class _EXPORT_CLASS interfacet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;

    typedef socket_attached_t attached_t;
    typedef socket_unattached_t unattached_t;
    enum { unattached = socket_unattached };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    interfacet(const interfacet &copy): extends(copy.attached_to()) {
    }
    interfacet() {
    }
    virtual ~interfacet() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t open_detached(domain_t domain, type_t type, protocol_t protocol) const {
        attached_t detached = ((attached_t)unattached);
        IS_LOGGED_DEBUG("::socket(domain = " << domain << ", type = " << type << ", protocol = " << protocol << ")...");
        if (0 <= (detached = ::socket(domain, type, protocol))) {
            IS_LOGGED_DEBUG("..." << detached << " = ::socket(domain = " << domain << ", type = " << type << ", protocol = " << protocol << ")");
        } else {
            IS_LOGGED_ERROR("failed errno = " << errno << " on ::socket(domain = " << domain << ", type = " << type << ", protocol = " << protocol << ")");
        }
        return detached;
    }
    virtual bool close_detached(attached_t detached) const {
        if (((attached_t)unattached) != (detached)) {
            int err = 0;
            IS_LOGGED_DEBUG("::close(" << detached << ")...");
            if (!(err = ::close(detached))) {
                IS_LOGGED_DEBUG("...::close(" << detached << ")");
                return true;
            } else {
                IS_LOGGED_ERROR("failed errno = " << errno << " on ::close(" << detached << ")");
            }
        }
        return false;
    }
    virtual bool shutdown_detached(attached_t detached, shutdown_how_t how) const {
        if (((attached_t)unattached) != (detached)) {
            int sd_how = ((how == shutdown_read)?(SHUT_RD)
                          :((how == shutdown_write)?(SHUT_WR)
                          :((how == shutdown_both)?(SHUT_RDWR):(0))));
            int err = 0;
            IS_LOGGED_DEBUG("::shutdown(detached, sd_how)...");
            if (!(err = ::shutdown(detached, sd_how))) {
                IS_LOGGED_DEBUG("...::shutdown(detached, sd_how)");
                return true;
            } else {
                IS_LOGGED_ERROR("...failed " << errno << " on shutdown(detached, sd_how)");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool connect_detached
    (attached_t detached, const sockaddr_t* addr, socklen_t addrlen) const {
        if (((attached_t)unattached) != (detached)) {
            int err = 0;
            IS_LOGGED_DEBUG("::connect(..., addrlen = " << addrlen << ")...");
            if (!(err = ::connect(detached, addr, addrlen))) {
                IS_LOGGED_DEBUG("...::connect(..., addrlen = " << addrlen << ")...");
                return true;
            } else {
                IS_LOGGED_ERROR("...failed errno = " << errno << " on ::connect(..., addrlen = " << addrlen << ")");
            }
        }
        return false;
    }
    virtual bool bind_detached
    (attached_t detached, const sockaddr_t* addr, socklen_t addrlen) const {
        if (((attached_t)unattached) != (detached)) {
            int err = 0;
            IS_LOGGED_DEBUG("::bind(..., addrlen = " << addrlen << ")...");
            if (!(err = ::bind(detached, addr, addrlen))) {
                IS_LOGGED_DEBUG("...::bind(..., addrlen = " << addrlen << ")...");
                return true;
            } else {
                IS_LOGGED_ERROR("...failed errno = " << errno << " on ::bind(..., addrlen = " << addrlen << ")");
            }
        }
        return false; 
    }
    virtual bool accept_detached
    (attached_t detached, interface_implemented& sock, sockaddr_t* addr, socklen_t& addrlen) const {
        if (((attached_t)unattached) != (detached)) {
            int err = 0;
            attached_t accepted = ((attached_t)unattached);
            IS_LOGGED_DEBUG("::accept(..., addrlen = " << addrlen << ")...");
            if (0 <= (accepted = ::accept(detached, addr, &addrlen))) {
                IS_LOGGED_DEBUG("...::accept(..., addrlen = " << addrlen << ")...");
                if ((accepted_detached(accepted, sock, addr, addrlen))) {
                    return true;
                }
                IS_LOGGED_DEBUG("::close(accepted = " << accepted << ")...");
                if ((err = ::close(accepted))) {
                    IS_LOGGED_ERROR("...failed errno = " << errno << " on ::aclose(accepted = " << accepted << ")");
                }
            } else {
                IS_LOGGED_ERROR("...failed errno = " << errno << " on ::accept(..., addrlen = " << addrlen << ")");
            }
        }
        return false; 
    }
    virtual bool accepted_detached
    (attached_t detached, interface_implemented& sock, sockaddr_t* addr, socklen_t& addrlen) const {
        if (((attached_t)unattached) != (detached)) {
        }
        return false; 
    }
    virtual bool listen_detached(attached_t detached, backlog_t backlog) const { 
        if (((attached_t)unattached) != (detached)) {
            int err = 0;
            IS_LOGGED_DEBUG("::listen(..., backlog = " << backlog << ")...");
            if (!(err = ::listen(detached, backlog))) {
                IS_LOGGED_DEBUG("...::listen(..., backlog = " << backlog << ")...");
                return true;
            } else {
                IS_LOGGED_ERROR("...failed errno = " << errno << " on ::listen(..., backlog = " << backlog << ")");
            }
        }
        return false; 
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t send_detached
    (attached_t detached, const void* buf, size_t len, send_flags_t flags) const {
        if (((attached_t)unattached) != (detached)) {
            ssize_t count = 0;
            IS_LOGGED_DEBUG("::send(..., len = " << len << ", flags = " << flags << ")...");
            if (0 <= (count = ::send(detached, buf, len, flags))) {
                IS_LOGGED_DEBUG("..." << count << " = ::send(..., len = " << len << ", flags = " << flags << ")...");
                return count;
            } else {
                IS_LOGGED_ERROR("...failed errno = " << errno << " on ::end(..., len = " << len << ", flags = " << flags << ")");
            }
        }
        return -1;
    }
    virtual ssize_t recv_detached
    (attached_t detached, void* buf, size_t len, recv_flags_t flags) const {
        if (((attached_t)unattached) != (detached)) {
            ssize_t count = 0;
            IS_LOGGED_DEBUG("::recv(..., len = " << len << ", flags = " << flags << ")...");
            if (0 <= (count = ::recv(detached, buf, len, flags))) {
                IS_LOGGED_DEBUG("..." << count << " = ::recv(..., len = " << len << ", flags = " << flags << ")...");
                return count;
            } else {
                IS_LOGGED_ERROR("...failed errno = " << errno << " on ::recv(..., len = " << len << ", flags = " << flags << ")");
            }
        }
        return -1;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS interfacet
typedef interfacet<> interface_extend;

} /// namespace posix

typedef posix::interfacet_implements interface_implemented_implements;
typedef posix::interface_extend interface_implemented_extends;
///////////////////////////////////////////////////////////////////////
///  Class: interface_implemented
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS interface_implemented
: virtual public interface_implemented_implements, public interface_implemented_extends {
public:
    typedef interface_implemented_implements implements;
    typedef interface_implemented_extends extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    interface_implemented(const interface_implemented &copy) {
    }
    interface_implemented() {
    }
    virtual ~interface_implemented() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool accepted_detached
    (attached_t detached, interface_implemented& sock, sockaddr_t* addr, socklen_t& addrlen) const {
        if ((sock.closed())) {
            if (((attached_t)unattached) != (detached)) {
                sock.attach_opened(detached);
                return true;
            }
        }
        return false; 
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS interface_implemented

namespace posix {

typedef interface_implemented_implements interface_implements;
typedef interface_implemented interface_extends;
///////////////////////////////////////////////////////////////////////
///  Class: interface
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS interface: virtual public interface_implements, public interface_extends {
public:
    typedef interface_implements implements;
    typedef interface_extends extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    interface(const interface &copy) {
    }
    interface() {
    }
    virtual ~interface() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS interface

} /// namespace posix
} /// namespace sockets
} /// namespace network
} /// namespace xos

#endif /// _XOS_NETWORK_SOCKETS_POSIX_INTERFACE_HPP 
