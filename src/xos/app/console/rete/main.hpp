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
#include "xos/network/sockets/ip/v4/tcp/transport.hpp"
#include "xos/network/sockets/ip/v4/udp/transport.hpp"
#include "xos/network/sockets/ip/v6/tcp/transport.hpp"
#include "xos/network/sockets/ip/v6/udp/transport.hpp"
#include "xos/network/endpoint.hpp"
#include "xos/network/sockets/endpoint.hpp"
#include "xos/network/sockets/ip/endpoint.hpp"
#include "xos/network/sockets/ip/v4/endpoint.hpp"
#include "xos/network/sockets/ip/v6/endpoint.hpp"
#include "xos/network/interface.hpp"
#include "xos/network/sockets/interface.hpp"
#include "xos/network/sockets/os/interface.hpp"
#include "xos/network/sockets/os/sockets.hpp"
#include "xos/io/network/sockets/interface/reader.hpp"
#include "xos/io/network/sockets/interface/writer.hpp"
#include "xos/app/console/rete/main_opt.hpp"

namespace xos {
namespace app {
namespace console {
namespace rete {

///////////////////////////////////////////////////////////////////////
///  Class: maint
///////////////////////////////////////////////////////////////////////
template 
<class TVersion = xos::lib::rete::version,
 class TExtends = main_optt<TVersion>, 
 class TImplements = typename TExtends::implements>

class _EXPORT_CLASS maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef maint derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    maint()
    : run_(0), sockets_run_(0), 
      sockets_client_run_(0), sockets_server_run_(0),
      client_port_(80), server_port_(8080),
      client_host_("localhost"), server_host_(""),
      client_message_("GET / HTTP/1.0\r\n\r\n"), 
      server_message_("HTTP/1.0 200 OK\r\n\r\nOK\r\n"),
      message_(0), ip_transport_(0), 
      ip_tcp_transport_(0), ip_udp_transport_(0), 
      ip_endpoint_(0) {
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
    virtual int default_run(int argc, char_t** argv, char_t** env) {
        return extends::run(argc, argv, env);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int (derives::*sockets_run_)(int argc, char_t** argv, char_t** env);
    virtual int sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        network::sockets::os::sockets sks;

        if ((sks.startup())) {
            if ((sockets_run_)) {
                err = (this->*sockets_run_)(argc, argv, env);
            } else {
                err = default_sockets_run(argc, argv, env);
            }
            sks.cleanup();
        }
        return err;
    }
    virtual int default_sockets_run(int argc, char_t** argv, char_t** env) {
        return sockets_client_run(argc, argv, env);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int (derives::*sockets_client_run_)(int argc, char_t** argv, char_t** env);
    virtual int sockets_client_run(int argc, char_t** argv, char_t** env) {
        if ((sockets_client_run_)) {
            return (this->*sockets_client_run_)(argc, argv, env);
        }
        return default_sockets_client_run(argc, argv, env);
    }
    virtual int default_sockets_client_run(int argc, char_t** argv, char_t** env) {
        return tcp_client_run(argc, argv, env);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int (derives::*sockets_server_run_)(int argc, char_t** argv, char_t** env);
    virtual int sockets_server_run(int argc, char_t** argv, char_t** env) {
        if ((sockets_server_run_)) {
            return (this->*sockets_server_run_)(argc, argv, env);
        }
        return default_sockets_server_run(argc, argv, env);
    }
    virtual int default_sockets_server_run(int argc, char_t** argv, char_t** env) {
        return tcp_server_run(argc, argv, env);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int tcp_client_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        network::sockets::ip::endpoint& ep = this->ip_endpoint();
        network::sockets::ip::transport& tp = this->tcp_transport();
        network::sockets::os::interface sk;

        if ((ep.attach(client_host_, client_port_))) {

            if ((sk.open(tp))) {
    
                if ((sk.connect(ep))) {
                    ssize_t count = 0;
    
                    if (0 < (count = tcp_send_request_message(client_message_, sk))) {
                        if (0 < (count = tcp_recv_response_message(recved_message_, sk))) {
                            on_tcp_recv_response_message(recved_message_, sk);
                        }
                    }
                    sk.shutdown();
                }
                sk.close();
            }
            ep.detach();
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int udp_client_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        network::sockets::ip::endpoint& ep = this->ip_endpoint();
        network::sockets::ip::transport& tp = this->udp_transport();
        network::sockets::os::interface sk;

        if ((ep.attach(client_host_, client_port_))) {

            if ((sk.open(tp))) {
                const char_t* chars = client_message_.chars();
                ssize_t size = client_message_.length();
                ssize_t count = 0;
    
                do {
                    if (0 < (count = sk.sendto(chars, size, 0, ep))) {
                        this->out(chars, count);
                        this->out_flush();
                        chars += count;
                        size -= count;
                    }
                } while ((0 < count) && (0 < size));
                sk.close();
            }
            ep.detach();
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int tcp_server_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        network::sockets::ip::endpoint& ep = this->ip_endpoint();
        network::sockets::ip::transport& tp = this->tcp_transport();
        network::sockets::os::interface sk;

        if ((ep.attach(server_host_, server_port_))) {

            if ((sk.open(tp))) {
    
                if ((sk.bind(ep))) {
                    
                    if ((sk.listen())) {
                        network::sockets::os::interface cn;
                        
                        if ((sk.accept(cn, ep))) {
                            ssize_t count = 0;
                            
                            if (0 < (count = tcp_recv_request_message(recved_message_, cn))) {
                                on_tcp_recv_request_message(recved_message_, cn);                      
                                count = tcp_send_response_message(server_message_, cn); 
                            }
                            cn.close();
                        }
                    }
                }
                sk.close();
            }
            ep.detach();
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int udp_server_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        network::sockets::ip::endpoint& ep = this->ip_endpoint();
        network::sockets::ip::transport& tp = this->udp_transport();
        network::sockets::os::interface sk;

        if ((ep.attach(server_host_, server_port_))) {

            if ((sk.open(tp))) {
    
                if ((sk.bind(ep))) {
                    char_t* chars = chars_;
                    size_t size = sizeof(chars_);
                    ssize_t count = 0;
                    
                    do {
                        if (0 < (count = sk.recvfrom(chars, size, 0, ep))) {
                            this->out(chars_, count);
                            this->out_flush();
                        }
                    } while (size <= (count));
                }
                sk.close();
            }
            ep.detach();
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t tcp_send_request_message
    (char_string& message, network::sockets::interface& sk) {
        io::network::sockets::interface::char_writer writer(sk);
        return tcp_write_request_message(message, writer);
    }
    virtual ssize_t tcp_write_request_message
    (char_string& message, io::char_writer& writer) {
        return tcp_write_message(message, writer);
    }
    virtual ssize_t tcp_send_response_message
    (char_string& message, network::sockets::interface& sk) {
        io::network::sockets::interface::char_writer writer(sk);
        return tcp_write_response_message(message, writer);
    }
    virtual ssize_t tcp_write_response_message
    (char_string& message, io::char_writer& writer) {
        return tcp_write_message(message, writer);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void on_tcp_recv_request_message
    (char_string& message, network::sockets::interface& sk) {
        io::network::sockets::interface::char_reader reader(sk);
        on_tcp_read_request_message(message, reader);
    }
    virtual void on_tcp_read_request_message
    (char_string& message, io::char_reader& reader) {
        this->out(message.chars());
    }
    virtual ssize_t tcp_recv_request_message
    (char_string& message, network::sockets::interface& sk) {
        io::network::sockets::interface::char_reader reader(sk);
        return tcp_read_request_message(message, reader);
    }
    virtual ssize_t tcp_read_request_message
    (char_string& message, io::char_reader& reader) {
        return tcp_read_message(message, reader);
    }
    virtual void on_tcp_recv_response_message
    (char_string& message, network::sockets::interface& sk) {
        io::network::sockets::interface::char_reader reader(sk);
        on_tcp_read_response_message(message, reader);
    }
    virtual void on_tcp_read_response_message
    (char_string& message, io::char_reader& reader) {
        this->out(message.chars());
    }
    virtual ssize_t tcp_recv_response_message
    (char_string& message, network::sockets::interface& sk) {
        io::network::sockets::interface::char_reader reader(sk);
        return tcp_read_request_message(message, reader);
    }
    virtual ssize_t tcp_read_response_message
    (char_string& message, io::char_reader& reader) {
        return tcp_read_message(message, reader);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t tcp_send_message
    (char_string& message, network::sockets::interface& sk) {
        io::network::sockets::interface::char_writer writer(sk);
        return tcp_write_message(message, writer);
    }
    virtual ssize_t tcp_write_message
    (char_string& message, io::char_writer& writer) {
        const char* chars = 0;
        size_t length = 0;
        ssize_t count = 0;
        if ((chars = message.has_chars(length))) {
            count = writer.write(chars, length);
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t tcp_recv_message
    (char_string& message, network::sockets::interface& sk) {
        io::network::sockets::interface::char_reader reader(sk);
        return tcp_read_message(message, reader);
    }
    virtual ssize_t tcp_read_message
    (char_string& message, io::char_reader& reader) {
        enum { start, cr, crlf, crlfcr } state = start;
        ssize_t amount = 0, count = 0;
        char_t c = 0;

        message.clear();
        do {
            if (0 < (amount = reader.read(&c, 1))) {
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
    unsigned& (derives::*port_)() const;
    virtual unsigned& port() const {
        if ((port_)) {
            return (this->*port_)();
        }
        return default_port();
    }
    virtual unsigned& client_port() const {
        return (unsigned&)client_port_;
    }
    virtual unsigned& server_port() const {
        return (unsigned&)server_port_;
    }
    virtual unsigned& default_port() const {
        return client_port();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    char_string& (derives::*host_)() const;
    virtual char_string& host() const {
        if ((host_)) {
            return (this->*host_)();
        }
        return default_host();
    }
    virtual char_string& client_host() const {
        return (char_string&)client_host_;
    }
    virtual char_string& server_host() const {
        return (char_string&)server_host_;
    }
    virtual char_string& default_host() const {
        return client_host();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    char_string& (derives::*message_)() const;
    virtual char_string& message() const {
        if ((message_)) {
            return (this->*message_)();
        }
        return default_message();
    }
    virtual char_string& client_message() const {
        return (char_string&)client_message_;
    }
    virtual char_string& server_message() const {
        return (char_string&)server_message_;
    }
    virtual char_string& default_message() const {
        return client_message();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    network::sockets::ip::transport& (derives::*ip_transport_)() const;
    virtual network::sockets::ip::transport& ip_transport() const {
        if ((ip_transport_)) {
            return (this->*ip_transport_)();
        }
        return default_ip_transport();
    }
    virtual network::sockets::ip::transport& default_ip_transport() const {
        return tcp_transport();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    network::sockets::ip::transport& (derives::*ip_tcp_transport_)() const;
    virtual network::sockets::ip::transport& tcp_transport() const {
        if ((ip_tcp_transport_)) {
            return (this->*ip_tcp_transport_)();
        }
        return (network::sockets::ip::transport&)tcp_;
    }
    virtual network::sockets::ip::transport& ipv4_tcp_transport() const {
        return (network::sockets::ip::transport&)ipv4_tcp_;
    }
    virtual network::sockets::ip::transport& ipv6_tcp_transport() const {
        return (network::sockets::ip::transport&)ipv6_tcp_;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    network::sockets::ip::transport& (derives::*ip_udp_transport_)() const;
    virtual network::sockets::ip::transport& udp_transport() const {
        if ((ip_udp_transport_)) {
            return (this->*ip_udp_transport_)();
        }
        return (network::sockets::ip::transport&)udp_;
    }
    virtual network::sockets::ip::transport& ipv4_udp_transport() const {
        return (network::sockets::ip::transport&)ipv4_udp_;
    }
    virtual network::sockets::ip::transport& ipv6_udp_transport() const {
        return (network::sockets::ip::transport&)ipv6_udp_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void set_transport_tcp() {
        sockets_client_run_ = &derives::tcp_client_run;
        sockets_server_run_ = &derives::tcp_server_run;
        ip_transport_ = &derives::tcp_transport;
    }
    virtual void set_transport_udp() {
        sockets_client_run_ = &derives::udp_client_run;
        sockets_server_run_ = &derives::udp_server_run;
        ip_transport_ = &derives::udp_transport;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    network::sockets::ip::endpoint& (derives::*ip_endpoint_)() const;
    virtual network::sockets::ip::endpoint& ip_endpoint() const {
        if ((ip_endpoint_)) {
            return (this->*ip_endpoint_)();
        }
        return default_ip_endpoint();
    }
    virtual network::sockets::ip::endpoint& ipv4_endpoint() const {
        return (network::sockets::ip::endpoint&)ipv4_;
    }
    virtual network::sockets::ip::endpoint& ipv6_endpoint() const {
        return (network::sockets::ip::endpoint&)ipv6_;
    }
    virtual network::sockets::ip::endpoint& default_ip_endpoint() const {
        return ipv4_endpoint();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void set_family_ipv4() {
        ip_tcp_transport_ = &derives::ipv4_tcp_transport;
        ip_udp_transport_ = &derives::ipv4_udp_transport;
        ip_endpoint_ = &derives::ipv4_endpoint;
    }
    virtual void set_family_ipv6() {
        ip_tcp_transport_ = &derives::ipv6_tcp_transport;
        ip_udp_transport_ = &derives::ipv6_udp_transport;
        ip_endpoint_ = &derives::ipv6_endpoint;
    }
    virtual void set_family_local() {
        ip_endpoint_ = 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_client_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        run_ = &derives::sockets_run;
        sockets_run_ = &derives::sockets_client_run;
        port_ = &derives::client_port;
        host_ = &derives::client_host;
        message_ = &derives::client_message;
        return err;
    }
    virtual int on_server_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        run_ = &derives::sockets_run;
        sockets_run_ = &derives::sockets_server_run;
        port_ = &derives::server_port;
        host_ = &derives::server_host;
        message_ = &derives::server_message;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_host_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            char_string& host = this->host();
            host.assign(optarg);
        }
        return err;
    }
    virtual int on_port_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            unsigned portno = chars_t::to_unsigned(optarg);
            if ((portno)) {
                unsigned& port = this->port();
                port = portno;
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_family_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            if (!((optarg[1]) || (XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_IPV4[3] != optarg[0]))
                || !(chars_t::compare(XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_IPV4, optarg))) {
                set_family_ipv4();
            } else {
                if (!((optarg[1]) || (XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_IPV6[3] != optarg[0]))
                    || !(chars_t::compare(XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_IPV6, optarg))) {
                    set_family_ipv6();
                } else {
                    if (!((optarg[1]) || (XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_LOCAL[0] != optarg[0]))
                        || !(chars_t::compare(XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_LOCAL, optarg))) {
                        set_family_local();
                    } else {
                    }
                }
            }
        }
        return err;
    }
    virtual int on_transport_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            if (!((optarg[1]) || (XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_TCP[0] != optarg[0]))
                || !(chars_t::compare(XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_TCP, optarg))) {
                set_transport_tcp();
            } else {
                if (!((optarg[1]) || (XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_UDP[0] != optarg[0]))
                    || !(chars_t::compare(XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_UDP, optarg))) {
                    set_transport_udp();
                } else {
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    unsigned client_port_, server_port_;
    char_string client_host_, server_host_;
    char_string client_message_, server_message_, recved_message_;
    network::sockets::ip::tcp::transport tcp_;
    network::sockets::ip::udp::transport udp_;
    network::sockets::ip::v4::endpoint ipv4_;
    network::sockets::ip::v4::tcp::transport ipv4_tcp_;
    network::sockets::ip::v4::udp::transport ipv4_udp_;
    network::sockets::ip::v6::endpoint ipv6_;
    network::sockets::ip::v6::tcp::transport ipv6_tcp_;
    network::sockets::ip::v6::udp::transport ipv6_udp_;
    char_t chars_[4096];
}; /// class _EXPORT_CLASS maint
typedef maint<> main;

} /// namespace rete
} /// namespace console
} /// namespace app
} /// namespace xos

#endif /// _XOS_APP_CONSOLE_RETE_MAIN_HPP 
