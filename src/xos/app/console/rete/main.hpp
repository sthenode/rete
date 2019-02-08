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
///   File: main.hpp
///
/// Author: $author$
///   Date: 2/6/2019
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_CONSOLE_RETE_MAIN_HPP
#define _XOS_APP_CONSOLE_RETE_MAIN_HPP

#include "xos/mt/os/mutex.hpp"
#include "xos/mt/os/semaphore.hpp"
#include "xos/mt/std/queue.hpp"
#include "xos/network/address.hpp"
#include "xos/network/sockets/address.hpp"
#include "xos/network/sockets/ip/address.hpp"
#include "xos/network/sockets/ip/v4/address.hpp"
#include "xos/network/sockets/ip/v6/address.hpp"
#include "xos/network/transport.hpp"
#include "xos/network/sockets/transport.hpp"
#include "xos/network/sockets/ip/transport.hpp"
#include "xos/network/sockets/ip/tcp/transport.hpp"
#include "xos/network/sockets/ip/udp/transport.hpp"
#include "xos/network/endpoint.hpp"
#include "xos/network/sockets/endpoint.hpp"
#include "xos/network/sockets/ip/endpoint.hpp"
#include "xos/network/sockets/ip/v4/endpoint.hpp"
#include "xos/network/sockets/ip/v6/endpoint.hpp"
#include "xos/network/interface.hpp"
#include "xos/network/sockets/interface.hpp"
#include "xos/network/sockets/posix/interface.hpp"
#include "xos/network/sockets/os/interface.hpp"
#include "xos/console/lib/version/main.hpp"
#include "xos/lib/rete/version.hpp"

namespace xos {
namespace app {
namespace console {
namespace rete {

typedef xos::console::lib::version::maint_implements maint_implements;
typedef xos::console::lib::version::maint<xos::lib::rete::version> maint_extends;
///////////////////////////////////////////////////////////////////////
///  Class: maint
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = maint_implements, class TExtends = maint_extends>
class _EXPORT_CLASS maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef maint derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    maint() {
    }
    virtual ~maint() {
    }
private:
    maint(const maint &copy) {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int (derives::*run_)(int argc, char_t** argv, char_t** env);
    virtual int run(int argc, char_t** argv, char_t** env) {
        if ((run_)) {
            return (this->*run_)(argc, argv, env);
        }
        return default_run(argc, argv, env);
    }
    virtual int client_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        network::sockets::ip::v4::endpoint ep("localhost", 80);
        network::sockets::ip::tcp::transport tp;
        network::sockets::os::interface sk;

        if ((sk.open(tp))) {

            if ((sk.connect(ep))) {
                char_string message("GET / HTTP/1.0\r\n\r\n");
                ssize_t count = 0;

                if (0 < (count = sk.send(message.chars(), message.length(), 0))) {
                    char_t c = 0;

                    do {
                        if (0 < (count = sk.recv(&c, 1, 0))) {
                            this->out(&c, 1);
                        }
                    } while (0 < (count));
                }
                sk.shutdown();
            }
            sk.close();
        }
        return err;
    }
    virtual int default_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = extends::run(argc, argv, env))) {
            client_run(argc, argv, env);
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual network::transport& transport() const {
        return default_transport();
    }
    virtual network::transport& tcp_transport() const {
        return (network::transport&)tcp_;
    }
    virtual network::transport& udp_transport() const {
        return (network::transport&)udp_;
    }
    virtual network::transport& default_transport() const {
        return tcp_transport();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    network::sockets::ip::tcp::transport tcp_;
    network::sockets::ip::udp::transport udp_;

}; /// class _EXPORT_CLASS maint
typedef maint<> main;

} /// namespace rete
} /// namespace console
} /// namespace app
} /// namespace xos

#endif /// _XOS_APP_CONSOLE_RETE_MAIN_HPP 
