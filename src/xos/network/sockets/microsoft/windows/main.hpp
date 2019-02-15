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
///   Date: 2/13/2019
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_NETWORK_SOCKETS_MICROSOFT_WINDOWS_MAIN_HPP
#define _XOS_NETWORK_SOCKETS_MICROSOFT_WINDOWS_MAIN_HPP

#include "xos/mt/std/queue.hpp"
#include "xos/network/sockets/ip/tcp/transport.hpp"
#include "xos/network/sockets/ip/v4/endpoint.hpp"
#include "xos/network/sockets/microsoft/windows/interface.hpp"
#include "xos/network/sockets/microsoft/windows/sockets.hpp"
#include "xos/console/getopt/main.hpp"

namespace xos {
namespace network {
namespace sockets {
namespace microsoft {
namespace windows {

typedef xos::console::getopt::main::implements main_implements;
typedef xos::console::getopt::main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main: virtual public main_implements, public main_extends {
public:
    typedef main_implements implements;
    typedef main_extends extends;
    typedef maint derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main()
    : run_(0),
      client_message_("GET / HTTP/1.0\r\n\r\n"), 
      server_message_("HTTP/1.0 200 OK\r\n\r\nOK\r\n") {
    }
    virtual ~main() {
    }
private:
    main(const main &copy) {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int (derives::*run_)(int argc, char_t** argv, char_t** env);
    virtual int run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        network::sockets::microsoft::windows::sockets sks;

        if ((sks.startup())){
            if ((run_)) {
                err = (this->*run_)(argc, argv, env);
            }
            err = server_run(argc, argv, env);
            sks.cleanup();
        }
        return err;
    }
    virtual int server_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        network::sockets::ip::v4::endpoint ep(8080);
        network::sockets::ip::tcp::transport tp;
        network::sockets::microsoft::windows::interface sk;

        if ((sk.open(tp))) {

            if ((sk.bind(ep))) {
                
                if ((sk.listen())) {
                    network::sockets::microsoft::windows::interface cn;
                    
                    if ((sk.accept(cn, ep))) {
                        ssize_t count = 0;
                        
                        if (0 < (count = recv_message(message_, cn))) {
                            this->out(message_.chars());                            
                            count = cn.send(server_message_.chars(), server_message_.length(), 0);
                        }
                        cn.close();
                    }
                }
            }
            sk.close();
        }
        return err;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t recv_message
    (char_string& message, network::sockets::interface& sk) {
        enum { start, cr, crlf, crlfcr } state = start;
        ssize_t amount = 0, count = 0;
        char_t c = 0;

        message.clear();
        do {
            if (0 < (amount = sk.recv(&c, 1, 0))) {
                message.append(&c, 1);
                count += 1;
                if ('\r' == c) {
                    switch (state) {
                    case start: state = cr; break;
                    case cr: break;
                    case crlf: state = crlfcr; break;
                    case crlfcr: state = cr; break;
                    }
                } else {
                    if ('\n' == c) {
                        switch (state) {
                        case start: state = start; break;
                        case cr: state = crlf; break;
                        case crlf: state = start; break;
                        case crlfcr: return count; break;
                        }
                    } else {
                        state = start;
                    }
                }
            }
        } while (0 < (amount));
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    char_string client_message_, server_message_, message_;
}; /// class _EXPORT_CLASS main

} /// namespace windows
} /// namespace microsoft
} /// namespace sockets
} /// namespace network
} /// namespace xos

#endif /// _XOS_NETWORK_SOCKETS_MICROSOFT_WINDOWS_MAIN_HPP 
