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
///   File: writer.hpp
///
/// Author: $author$
///   Date: 8/31/2019
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_IO_NETWORK_SOCKETS_INTERFACE_WRITER_HPP
#define _XOS_IO_NETWORK_SOCKETS_INTERFACE_WRITER_HPP

#include "xos/network/sockets/interface.hpp"
#include "xos/io/writer.hpp"
#include "xos/io/logger.hpp"

namespace xos {
namespace io {
namespace network {
namespace sockets {
namespace interface {

///////////////////////////////////////////////////////////////////////
///  Class: writert
///////////////////////////////////////////////////////////////////////
template <class TImplements = io::writer, class TExtends = base>
class _EXPORT_CLASS writert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;

    typedef implements reader_t;
    typedef typename reader_t::what_t what_t;
    typedef typename reader_t::sized_t sized_t;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    writert(const writert &copy): sock_(copy.sock_) {
    }
    writert(::xos::network::sockets::interface& sock): sock_(sock) {
    }
    virtual ~writert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t write(const what_t* what, size_t size) {
        ssize_t count = 0;
        if (1 < (sizeof(sized_t))) {
            LOG_ERROR("...failed unsupported sizeof(sized_t) = " << sizeof(sized_t));
            return -1;
        }
        count = send(this->sock(), what, size);
        return count;
    }
    virtual ssize_t send(::xos::network::sockets::interface& sock, const void* what, size_t size) {
        ssize_t count = 0;
        if ((what) && (size)) {
            count = sock.send(what, size, 0);
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
}; /// class _EXPORT_CLASS writert

typedef writert<> writer;
typedef writert<io::char_writer> char_writer;

} /// namespace interface
} /// namespace sockets
} /// namespace network
} /// namespace io
} /// namespace xos

#endif /// _XOS_IO_NETWORK_SOCKETS_INTERFACE_WRITER_HPP 
