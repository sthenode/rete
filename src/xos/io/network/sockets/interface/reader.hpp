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
///   File: reader.hpp
///
/// Author: $author$
///   Date: 8/31/2019
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_NETWORK_SOCKETS_INTERFACE_READER_HPP
#define _XOS_IO_NETWORK_SOCKETS_INTERFACE_READER_HPP

#include "xos/io/reader.hpp"
#include "xos/network/sockets/interface.hpp"

namespace xos {
namespace io {
namespace network {
namespace sockets {
namespace interface {

///////////////////////////////////////////////////////////////////////
///  Class: readert
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = io::reader, class TExtends = base>

class _EXPORT_CLASS readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;

    typedef implements reader_t;
    typedef typename reader_t::what_t what_t;
    typedef typename reader_t::sized_t sized_t;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    readert(const readert &copy): sock_(copy.sock_) {
    }
    readert(::xos::network::sockets::interface& sock): sock_(sock) {
    }
    virtual ~readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(what_t* what, size_t size) {
        ssize_t count = recv(this->sock(), what, size*sizeof(sized_t));
        return count;
    }
    virtual ssize_t recv(::xos::network::sockets::interface& sock, void* what, size_t size) {
        ssize_t count = 0;
        if ((what) && (size)) {
            count = sock.recv(what, size, 0);
        }
        return count;
    }
    virtual ::xos::network::sockets::interface& sock() const {
        return (::xos::network::sockets::interface&)sock_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ::xos::network::sockets::interface& sock_;
}; /// class _EXPORT_CLASS readert

typedef readert<> reader;
typedef readert<io::char_reader> char_reader;

} /// namespace interface
} /// namespace sockets
} /// namespace network
} /// namespace io
} /// namespace xos

#endif /// _XOS_IO_NETWORK_SOCKETS_INTERFACE_READER_HPP 
