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
///   Date: 2/13/2019
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_SOCKETS_MICROSOFT_WINDOWS_INTERFACE_HPP
#define _XOS_NETWORK_SOCKETS_MICROSOFT_WINDOWS_INTERFACE_HPP

#include "xos/network/sockets/microsoft/windows/os.hpp"
#include "xos/network/sockets/interface.hpp"

namespace xos {
namespace network {
namespace sockets {
namespace microsoft {
namespace windows {

typedef SOCKET socket_attached_t;
typedef SOCKET socket_unattached_t;
enum { socket_unattached = INVALID_SOCKET };

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
    virtual bool set_reuseaddr_opt(bool on = true) {
        int value = (on)?(1):(0);
        IS_LOGGED_DEBUG("set_opt(SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value))...");
        if ((this->set_opt(SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)))) {
            return true;
        }
        return false;
    }
    virtual bool set_noreuseaddr_opt(bool on = true) {
        int value = (on)?(0):(1);
        IS_LOGGED_DEBUG("set_opt(SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value))...");
        if ((this->set_opt(SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)))) {
            return true;
        }
        return false;
    }
    virtual bool get_reuseaddr_opt(bool &on) const {
        int value = 0;
        socklen_t length = sizeof(value);
        IS_LOGGED_DEBUG("get_opt(SOL_SOCKET, SO_REUSEADDR, &value, length)...");
        if ((this->get_opt(SOL_SOCKET, SO_REUSEADDR, &value, length))) {
            on = (value != 0);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_delay_opt(bool on = true) {
        int value = (on)?(DELAY_OPT_ON):(DELAY_OPT_OFF); /// Note opposite of posix
        IS_LOGGED_DEBUG("set_opt(IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value))...");
        if ((this->set_opt(IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value)))) {
            return true;
        }
        return false;
    }
    virtual bool set_nodelay_opt(bool on = true) {
        int value = (on)?(DELAY_OPT_OFF):(DELAY_OPT_ON); /// Note opposite of posix
        IS_LOGGED_DEBUG("set_opt(IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value))...");
        if ((this->set_opt(IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value)))) {
            return true;
        }
        return false;
    }
    virtual bool get_delay_opt(bool &on) const {
        int value = 0;
        socklen_t length = sizeof(value);
        IS_LOGGED_DEBUG("get_opt(IPPROTO_TCP, TCP_NODELAY, &value, length))...");
        if ((this->get_opt(IPPROTO_TCP, TCP_NODELAY, &value, length))) {
            on = (value == 0);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_linger_opt
    (bool on = true, linger_seconds_t linger_seconds = -1) {
        struct linger value;
        value.l_onoff = (on)?(1):(0);
        value.l_linger = (0>linger_seconds)?(this->default_linger_seconds()):(linger_seconds);
        IS_LOGGED_DEBUG("set_opt(SOL_SOCKET, SO_LINGER, &value, sizeof(value))...");
        if ((this->set_opt(SOL_SOCKET, SO_LINGER, &value, sizeof(value)))) {
            return true;
        }
        return false;
    }
    virtual bool set_dont_linger_opt
    (bool on = true, linger_seconds_t linger_seconds = -1) {
        struct linger value;
        value.l_onoff = (on)?(0):(1);
        value.l_linger = (0>linger_seconds)?(this->default_linger_seconds()):(linger_seconds);
        IS_LOGGED_DEBUG("set_opt(SOL_SOCKET, SO_LINGER, &value, sizeof(value))...");
        if ((this->set_opt(SOL_SOCKET, SO_LINGER, &value, sizeof(value)))) {
            return true;
        }
        return false;
    }
    virtual bool get_linger_opt(bool &on, linger_seconds_t &linger_seconds) const {
        struct linger value = {0, 0};
        socklen_t length = sizeof(value);
        IS_LOGGED_DEBUG("get_opt(SOL_SOCKET, SO_LINGER, &value, length)...");
        if ((this->get_opt(SOL_SOCKET, SO_LINGER, &value, length))) {
            on = (value.l_onoff == 0);
            linger_seconds = (value.l_linger);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t open_detached(domain_t domain, type_t type, protocol_t protocol) const {
        attached_t detached = ((attached_t)unattached);
        IS_LOGGED_DEBUG("::socket(domain = " << domain << ", type = " << type << ", protocol = " << protocol << ")...");
        if (0 <= (detached = ::socket(domain, type, protocol))) {
            IS_LOGGED_DEBUG("..." << detached << " = ::socket(domain = " << domain << ", type = " << type << ", protocol = " << protocol << ")");
        } else {
            int error = WSAGetLastError();
            IS_LOGGED_ERROR("failed error = " << error << " on socket(domain = " << domain << ", type = " << type << ", protocol = " << protocol << ")");
        }
        return detached;
    }
    virtual bool close_detached(attached_t detached) const {
        if (((attached_t)unattached) != (detached)) {
            int err = 0;
            IS_LOGGED_DEBUG("::closesocket(" << detached << ")...");
            if (!(err = ::closesocket(detached))) {
                IS_LOGGED_DEBUG("...::closesocket(" << detached << ")");
                return true;
            } else {
                int error = WSAGetLastError();
                IS_LOGGED_ERROR("failed error = " << error << " on ::closesocket(" << detached << ")");
            }
        }
        return false;
    }
    virtual bool shutdown_detached(attached_t detached, shutdown_how_t how) const {
        if (((attached_t)unattached) != (detached)) {
            int sd_how = ((how == shutdown_read)?(SD_RECEIVE)
                          :((how == shutdown_write)?(SD_SEND)
                          :((how == shutdown_both)?(SD_BOTH):(0))));
            int err = 0;
            IS_LOGGED_DEBUG("::shutdown(detached = " << detached << ", sd_how = " << sd_how << ")...");
            if (!(err = ::shutdown(detached, sd_how))) {
                IS_LOGGED_DEBUG("...::shutdown(detached = " << detached << ", sd_how = " << sd_how << ")");
                return true;
            } else {
                int error = WSAGetLastError();
                IS_LOGGED_ERROR("...failed error = " << error << " on shutdown(detached = " << detached << ", sd_how = " << sd_how << ")");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool connect_detached
    (attached_t detached, const sockaddr_t* addr, socklen_t addrlen) const {
        if ((((attached_t)unattached) != (detached)) && (addr) && (0 < addrlen)) {
            int err = 0;
            IS_LOGGED_DEBUG("::connect(..., addrlen = " << addrlen << ")...");
            if (!(err = ::connect(detached, addr, addrlen))) {
                IS_LOGGED_DEBUG("...::connect(..., addrlen = " << addrlen << ")...");
                return true;
            } else {
                int error = WSAGetLastError();
                IS_LOGGED_ERROR("...failed error = " << error << " on ::connect(..., addrlen = " << addrlen << ")");
            }
        }
        return false;
    }
    virtual bool bind_detached
    (attached_t detached, const sockaddr_t* addr, socklen_t addrlen) const {
        if ((((attached_t)unattached) != (detached)) && (addr) && (0 < addrlen)) {
            int err = 0;
            IS_LOGGED_DEBUG("::bind(..., addrlen = " << addrlen << ")...");
            if (!(err = ::bind(detached, addr, addrlen))) {
                IS_LOGGED_DEBUG("...::bind(..., addrlen = " << addrlen << ")...");
                return true;
            } else {
                int error = WSAGetLastError();
                IS_LOGGED_ERROR("...failed error = " << error << " on ::bind(..., addrlen = " << addrlen << ")");
            }
        }
        return false; 
    }
    virtual bool accept_detached
    (attached_t detached, interface_implemented& sock, sockaddr_t* addr, socklen_t& addrlen) const {
        if ((((attached_t)unattached) != (detached)) && (addr)) {
            attached_t accepted = ((attached_t)unattached);
            int err = 0;
            IS_LOGGED_DEBUG("::accept(..., addrlen = " << addrlen << ")...");
            if (0 <= (accepted = ::accept(detached, addr, &addrlen))) {
                IS_LOGGED_DEBUG("..." << accepted << " = ::accept(..., addrlen = " << addrlen << ")...");
                if ((accepted_detached(accepted, sock, addr, addrlen))) {
                    return true;
                }
                IS_LOGGED_DEBUG("::closesocket(" << accepted << ")...");
                if (!(err = ::closesocket(accepted))) {
                    IS_LOGGED_DEBUG("...::closesocket(" << accepted << ")");
                } else {
                    int error = WSAGetLastError();
                    IS_LOGGED_ERROR("failed error = " << error << " on ::closesocket(" << accepted << ")");
                }
            } else {
                int error = WSAGetLastError();
                IS_LOGGED_ERROR("...failed error = " << error << " on accept(..., addrlen = " << addrlen << ")");
            }
        }
        return false; 
    }
    virtual bool accepted_detached
    (attached_t detached, interface_implemented& sock, sockaddr_t* addr, socklen_t& addrlen) const {
        if ((((attached_t)unattached) != (detached)) && (addr)) {
        }
        return false; 
    }
    virtual bool listen_detached(attached_t detached, backlog_t backlog) const { 
        if (((attached_t)unattached) != (detached)) {
            int err = 0;
            IS_LOGGED_DEBUG("::listen(..., backlog = " << backlog << ")...");
            if (!(err = ::listen(detached, backlog))) {
                IS_LOGGED_DEBUG("...listen(..., backlog = " << backlog << ")...");
                return true;
            } else {
                int error = WSAGetLastError();
                IS_LOGGED_ERROR("...failed error = " << error << " on ::listen(..., backlog = " << backlog << ")");
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
            if (0 <= (count = ::send(detached, (const char*)buf, len, flags))) {
                IS_LOGGED_DEBUG("..." << count << " = ::send(..., len = " << len << ", flags = " << flags << ")...");
                return count;
            } else {
                int error = WSAGetLastError();
                IS_LOGGED_ERROR("...failed error = " << error << " on ::send(..., len = " << len << ", flags = " << flags << ")");
            }
        }
        return -1;
    }
    virtual ssize_t recv_detached
    (attached_t detached, void* buf, size_t len, recv_flags_t flags) const {
        if (((attached_t)unattached) != (detached)) {
            ssize_t count = 0;
            IS_LOGGED_DEBUG("::recv(..., len = " << len << ", flags = " << flags << ")...");
            if (0 <= (count = ::recv(detached, (char*)buf, len, flags))) {
                IS_LOGGED_DEBUG("..." << count << " = recv(..., len = " << len << ", flags = " << flags << ")...");
                return count;
            } else {
                int error = WSAGetLastError();
                IS_LOGGED_ERROR("...failed error = " << error << " on ::recv(..., len = " << len << ", flags = " << flags << ")");
            }
        }
        return -1;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_opt_detached
    (attached_t detached, opt_level_t level, opt_name_t name, const void* value, socklen_t length) {
        if ((((attached_t)unattached) != (detached)) && (value) && (0 < length)) {
            int err = 0;
            IS_LOGGED_DEBUG("::setsockopt(..., level = " << level << ", name = " << name << ", ..., length)...");
            if (!(err = ::setsockopt(detached, level, name, (const char*)value, length))) {
                IS_LOGGED_DEBUG("...setsockopt(..., level = " << level << ", name = " << name << ", ..., length)...");
                return true;
            } else {
                int error = WSAGetLastError();
                IS_LOGGED_ERROR("...failed error = " << error << " on ::setsockopt(..., level = " << level << ", name = " << name << ", ..., length)");
            }
        }
        return false;
    }
    virtual bool get_opt_detached
    (attached_t detached, opt_level_t level, opt_name_t name, void* value, socklen_t &length) const {
        if ((((attached_t)unattached) != (detached)) && (value)) {
            int err = 0;
            IS_LOGGED_DEBUG("::getsockopt(..., level = " << level << ", name = " << name << ", ..., length)...");
            if (!(err = ::getsockopt(detached, level, name, (char*)value, &length))) {
                IS_LOGGED_DEBUG("...::getsockopt(..., level = " << level << ", name = " << name << ", ..., length)...");
                return true;
            } else {
                int error = WSAGetLastError();
                IS_LOGGED_ERROR("...failed error = " << error << " on ::getsockopt(..., level = " << level << ", name = " << name << ", ..., length)");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS interfacet
typedef interfacet<> interface_extend;

} /// namespace windows
} /// namespace microsoft

typedef microsoft::windows::interfacet_implements interface_implemented_implements;
typedef microsoft::windows::interface_extend interface_implemented_extends;
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

namespace microsoft {
namespace windows {

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

} /// namespace windows
} /// namespace microsoft
} /// namespace sockets
} /// namespace network
} /// namespace xos

#endif /// _XOS_NETWORK_SOCKETS_MICROSOFT_WINDOWS_INTERFACE_HPP 
