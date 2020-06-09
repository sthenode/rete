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
///   File: endpoint.hpp
///
/// Author: $author$
///   Date: 2/7/2019
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_SOCKETS_ENDPOINT_HPP
#define _XOS_NETWORK_SOCKETS_ENDPOINT_HPP

#include "xos/network/sockets/address.hpp"
#include "xos/network/endpoint.hpp"
#include "xos/base/attached.hpp"
#include "xos/io/logger.hpp"

namespace xos {
namespace network {
namespace sockets {

typedef sockaddr_t* sockaddr_attached_t;
typedef int sockaddr_unattached_t;
enum { sockaddr_unattached = 0 };

///////////////////////////////////////////////////////////////////////
///  Class: endpointt
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = attachert
 <sockaddr_attached_t, sockaddr_unattached_t, 
  sockaddr_unattached, network::endpoint> >

class _EXPORT_CLASS endpointt: virtual public TImplements {
public:
    typedef TImplements implements;
    
    typedef typename implements::attached_t attached_t;
    typedef typename implements::unattached_t unattached_t;
    enum { unattached = implements::unattached };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using implements::attach;
    virtual sockaddr_attached_t attach_first(const char_string& host, sockport_t port) {
        const char* chars = host.has_chars();
        if ((chars)) { return this->attach_first(chars, port); }
        return this->attach(port);
    }
    virtual sockaddr_attached_t attach_last(const char_string& host, sockport_t port) {
        const char* chars = host.has_chars();
        if ((chars)) { return this->attach_last(chars, port); }
        return this->attach(port);
    }
    virtual sockaddr_attached_t attach(const char_string& host, sockport_t port) {
        const char* chars = host.has_chars();
        if ((chars)) { return this->attach(chars, port); }
        return this->attach(port);
    }
    virtual sockaddr_attached_t attach_first(const char* host, sockport_t port) {
        if ((host) && (host[0]) && (('*' != host[0]) || (0 != host[1]))) {
            return this->attach(host, first_addrindex, port); }
        return this->attach(port);
    }
    virtual sockaddr_attached_t attach_last(const char* host, sockport_t port) {
        if ((host) && (host[0]) && (('*' != host[0]) || (0 != host[1]))) {
            return this->attach(host, last_addrindex, port); }
        return this->attach(port);
    }
    virtual sockaddr_attached_t attach(const char* host, sockport_t port) {
        if ((host) && (host[0]) && (('*' != host[0]) || (0 != host[1]))) {
            return this->attach(host, first_addrindex, port); }
        return this->attach(port);
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual sockaddr_attached_t attach
    (const char_t* host, addrindex_t index, sockport_t port) {
        sockaddr_attached_t saddr = 0;
        struct addrinfo* addrs = 0;
        int err = 0;

        IS_LOGGED_DEBUG("getaddrinfo(\"" << host << "\",...)...");
        if (!(err = getaddrinfo(host, 0, 0, &addrs))) {
            const address_family_t family = this->family();
            struct addrinfo* addr = 0;
            addrindex_t addr_i = 0;

            IS_LOGGED_DEBUG("...getaddrinfo(\"" << host << "\",...) family = " << family);
            for (addr_i = 0, addr = addrs; addr; addr = addr->ai_next) {
                const address_family_t addrfamily = addr->ai_family;
                /*char addrhost[NI_MAXHOST];

                IS_LOGGED_DEBUG("getnameinfo(...)... family = " << addrfamily);
                if (!(err = getnameinfo
                    (addr->ai_addr, addr->ai_addrlen, addrhost, sizeof(addrhost)-1, 0, 0, 0))) {

                    addrhost[sizeof(addrhost)-1] = 0;
                    IS_LOGGED_DEBUG("...getnameinfo(..., addrhost = \"" << addrhost << "\",...)");
                } else {
                    IS_LOGGED_ERROR("...failed " << this->last_error() << " on getnameinfo(...)");
                }*/
                if (family == (addrfamily)) {
                    if ((addr_i == index) || ((last_addrindex == index) && !(addr->ai_next))) {
                        IS_LOGGED_DEBUG("...found family " << family << " address[" << addr_i << "]");
                        saddr = this->attach(addr->ai_addr, addr->ai_addrlen, port);
                        break;
                    } else {
                        ++addr_i;
                    }
                }
            }
            freeaddrinfo(addrs);
        } else {
            IS_LOGGED_ERROR("...failed " << this->last_error() << " on getaddrinfo(\"" << host << "\",...)");
        }
        return saddr;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual sockaddr_attached_t attach
    (const sockaddr_attached_t socket_address, socklen_t socket_addresslen, sockport_t port) {
        return 0;
    }
    virtual sockaddr_attached_t attach(sockport_t port) {
        return 0;
    }
    virtual sockaddr_attached_t attach(const char* path) {
        return 0;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* host_name(char* addrhost, socklen_t addrhostlen) const {
        if ((addrhost) && (1 < addrhostlen)) {
            attached_t saddr = 0; socklen_t saddrlen = 0;

            if ((saddr = socket_address(saddrlen)) && (0 < saddrlen)) {
                int err = 0;

                IS_LOGGED_DEBUG("getnameinfo(...)...");
                if (!(err = getnameinfo(saddr, saddrlen, addrhost, addrhostlen-1, 0, 0, 0))) {
                    addrhost[addrhostlen-1] = 0;
                    IS_LOGGED_DEBUG("...getnameinfo(..., addrhost = \"" << addrhost << "\",...)");
                    return addrhost;
                } else {
                    IS_LOGGED_ERROR("...failed " << this->last_error() << " on getnameinfo(...)");
                }
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual sockaddr_attached_t recv_socket_address(socklen_t& len) const {
        len = this->socket_address_len();
        return 0;
    }
    virtual sockaddr_attached_t socket_address(socklen_t& len) const {
        len = this->socket_address_len();
        return this->attached_to();
    }
    virtual sockaddr_attached_t socket_address() const {
        return this->attached_to();
    }
    virtual socklen_t socket_address_len() const {
        return 0;
    }
    virtual operator sockaddr_attached_t () const {
        return this->socket_address();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int last_error() const {
        return errno;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS endpointt
typedef endpointt<> endpoint;

namespace extended {

///////////////////////////////////////////////////////////////////////
///  Class: endpointt
///////////////////////////////////////////////////////////////////////
template 
<class TAddress = network::extended::address,
 class TImplements = sockets::endpoint, 
 class TExtends = attachedt
 <sockaddr_attached_t, sockaddr_unattached_t, 
  sockaddr_unattached, network::endpoint, 
  network::extended::endpointt
  <sockets::endpoint, TAddress>, sockets::endpoint> >

class _EXPORT_CLASS endpointt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;

    typedef typename extends::attached_t attached_t;
    typedef typename extends::unattached_t unattached_t;
    enum { unattached = extends::unattached };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    endpointt(const char* host, sockport_t port)
    : socket_address_port_(0), socket_address_len_(0) {
        if (!(this->attach(host, port))) {
            attach_exception e(attach_failed);
            IS_LOGGED_ERROR("...throwing attach_exception e(attach_failed)...");
            throw (e);
        }
    }
    endpointt(sockport_t port)
    : socket_address_port_(0), socket_address_len_(0) {
        if (!(this->attach(port))) {
            attach_exception e(attach_failed);
            IS_LOGGED_ERROR("...throwing attach_exception e(attach_failed)...");
            throw (e);
        }
    }
    endpointt(const endpointt &copy)
    : extends(copy), socket_address_port_(0), socket_address_len_(0) {
    }
    endpointt()
    : socket_address_port_(0), socket_address_len_(0) {
    }
    virtual ~endpointt() {
        if ((this->attached_to())) {
            if (!(this->detach())) {
                attach_exception e(detach_failed);
                IS_LOGGED_ERROR("...throwing attach_exception e(detach_failed)...");
                throw (e);
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using implements::attach;
    virtual attached_t attach(attached_t detached) {
        return extends::attach(detached);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    sockport_t socket_address_port_;
    socklen_t socket_address_len_;
}; /// class _EXPORT_CLASS endpointt
typedef endpointt<> endpoint;

} /// namespace extended

} /// namespace sockets
} /// namespace network
} /// namespace xos

#endif /// _XOS_NETWORK_SOCKETS_ENDPOINT_HPP 
