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
///   File: main_opt.hpp
///
/// Author: $author$
///   Date: 2/15/2019
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_CONSOLE_RETE_MAIN_OPT_HPP
#define _XOS_APP_CONSOLE_RETE_MAIN_OPT_HPP

#include "xos/console/lib/version/main.hpp"
#include "xos/lib/rete/version.hpp"

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPT "client"
#define XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPTARG ""
#define XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPTUSE "Run as client"
#define XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPTVAL_S "c"
#define XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPTVAL_C 'c'
#define XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPTION \
   {XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPT, \
    XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPTARG_RESULT, \
    XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPTVAL_C}, \

#define XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPT "server"
#define XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPTARG ""
#define XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPTUSE "Run as server"
#define XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPTVAL_S "s"
#define XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPTVAL_C 's'
#define XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPTION \
   {XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPT, \
    XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPTARG_RESULT, \
    XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPTVAL_C}, \

#define XOS_APP_CONSOLE_RETE_MAIN_HOST_OPT "host"
#define XOS_APP_CONSOLE_RETE_MAIN_HOST_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_APP_CONSOLE_RETE_MAIN_HOST_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_RETE_MAIN_HOST_OPTARG "string"
#define XOS_APP_CONSOLE_RETE_MAIN_HOST_OPTUSE "Host name or address"
#define XOS_APP_CONSOLE_RETE_MAIN_HOST_OPTVAL_S "o:"
#define XOS_APP_CONSOLE_RETE_MAIN_HOST_OPTVAL_C 'o'
#define XOS_APP_CONSOLE_RETE_MAIN_HOST_OPTION \
   {XOS_APP_CONSOLE_RETE_MAIN_HOST_OPT, \
    XOS_APP_CONSOLE_RETE_MAIN_HOST_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_RETE_MAIN_HOST_OPTARG_RESULT, \
    XOS_APP_CONSOLE_RETE_MAIN_HOST_OPTVAL_C}, \

#define XOS_APP_CONSOLE_RETE_MAIN_PORT_OPT "port"
#define XOS_APP_CONSOLE_RETE_MAIN_PORT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_APP_CONSOLE_RETE_MAIN_PORT_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_RETE_MAIN_PORT_OPTARG "number"
#define XOS_APP_CONSOLE_RETE_MAIN_PORT_OPTUSE "Port number"
#define XOS_APP_CONSOLE_RETE_MAIN_PORT_OPTVAL_S "p:"
#define XOS_APP_CONSOLE_RETE_MAIN_PORT_OPTVAL_C 'p'
#define XOS_APP_CONSOLE_RETE_MAIN_PORT_OPTION \
   {XOS_APP_CONSOLE_RETE_MAIN_PORT_OPT, \
    XOS_APP_CONSOLE_RETE_MAIN_PORT_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_RETE_MAIN_PORT_OPTARG_RESULT, \
    XOS_APP_CONSOLE_RETE_MAIN_PORT_OPTVAL_C}, \

#define XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPT "family"
#define XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_LOCAL_C "l"
#define XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_LOCAL "local"
#define XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_IPV4_C "4"
#define XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_IPV4 "ipv4"
#define XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_IPV6_C "6"
#define XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_IPV6 "ipv6"
#define XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG "{ "\
    "(" XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_LOCAL_C ")" \
    XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_LOCAL " | " \
    "(" XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_IPV4_C ")" \
    XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_IPV4 " | " \
    "(" XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_IPV6_C ")" \
    XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_IPV6 " }"
#define XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTUSE "Address family"
#define XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTVAL_S "f:"
#define XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTVAL_C 'f'
#define XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTION \
   {XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPT, \
    XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG_RESULT, \
    XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTVAL_C}, \

#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPT "transport"
#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_RAW_C "r"
#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_RAW "raw"
#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_STREAM_C "s"
#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_STREAM "stream"
#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_DGRAM_C "d"
#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_DGRAM "dgram"
#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_TCP_C "t"
#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_TCP "tcp"
#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_UDP_C "u"
#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_UDP "udp"
#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG "{ " \
    "(" XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_RAW_C ")" \
    XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_RAW " | " \
    "(" XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_STREAM_C ")" \
    XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_STREAM " | " \
    "(" XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_DGRAM_C ")" \
    XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_DGRAM " | " \
    "(" XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_TCP_C ")" \
    XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_TCP " | " \
    "(" XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_UDP_C ")" \
    XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_UDP " }"
#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTUSE "Transport type"
#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTVAL_S "t:"
#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTVAL_C 't'
#define XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTION \
   {XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPT, \
    XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG_RESULT, \
    XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTVAL_C}, \

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_RETE_MAIN_OPTIONS_CHARS \
   XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPTVAL_S \
   XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPTVAL_S \
   XOS_APP_CONSOLE_RETE_MAIN_HOST_OPTVAL_S \
   XOS_APP_CONSOLE_RETE_MAIN_PORT_OPTVAL_S \
   XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTVAL_S \
   XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTVAL_S \
   XOS_CONSOLE_MAIN_OPTIONS_CHARS

#define XOS_APP_CONSOLE_RETE_MAIN_OPTIONS_OPTIONS \
   XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPTION \
   XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPTION \
   XOS_APP_CONSOLE_RETE_MAIN_HOST_OPTION \
   XOS_APP_CONSOLE_RETE_MAIN_PORT_OPTION \
   XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTION \
   XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTION \
   XOS_CONSOLE_MAIN_OPTIONS_OPTIONS

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define XOS_APP_CONSOLE_RETE_MAIN_ARGS 0
#define XOS_APP_CONSOLE_RETE_MAIN_ARGV

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

namespace xos {
namespace app {
namespace console {
namespace rete {

typedef xos::console::lib::version::maint_implements main_opt_implements;
typedef xos::console::lib::version::maint<xos::lib::rete::version> main_opt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main_opt
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main_opt: virtual public main_opt_implements, public main_opt_extends {
public:
    typedef main_opt_implements implements;
    typedef main_opt_extends extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
private:
    main_opt(const main_opt &copy) {
    }
public:
    main_opt() {
    }
    virtual ~main_opt() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_client_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_server_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_host_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_port_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_family_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_transport_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {
        case XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPTVAL_C:
            err = on_client_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPTVAL_C:
            err = on_server_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_RETE_MAIN_HOST_OPTVAL_C:
            err = on_host_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_RETE_MAIN_PORT_OPTVAL_C:
            err = on_port_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTVAL_C:
            err = on_family_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTVAL_C:
            err = on_transport_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        default:
            err = extends::on_option
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* option_usage
    (const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {
        case XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPTVAL_C:
            optarg = XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPTARG;
            chars = XOS_APP_CONSOLE_RETE_MAIN_CLIENT_OPTUSE;
            break;
        case XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPTVAL_C:
            optarg = XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPTARG;
            chars = XOS_APP_CONSOLE_RETE_MAIN_SERVER_OPTUSE;
            break;
        case XOS_APP_CONSOLE_RETE_MAIN_HOST_OPTVAL_C:
            optarg = XOS_APP_CONSOLE_RETE_MAIN_HOST_OPTARG;
            chars = XOS_APP_CONSOLE_RETE_MAIN_HOST_OPTUSE;
            break;
        case XOS_APP_CONSOLE_RETE_MAIN_PORT_OPTVAL_C:
            optarg = XOS_APP_CONSOLE_RETE_MAIN_PORT_OPTARG;
            chars = XOS_APP_CONSOLE_RETE_MAIN_PORT_OPTUSE;
            break;
        case XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTVAL_C:
            optarg = XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTARG;
            chars = XOS_APP_CONSOLE_RETE_MAIN_FAMILY_OPTUSE;
            break;
        case XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTVAL_C:
            optarg = XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTARG;
            chars = XOS_APP_CONSOLE_RETE_MAIN_TRANSPORT_OPTUSE;
            break;
        default:
            chars = extends::option_usage(optarg, longopt);
        }
        return chars;
    }
    virtual const char_t* options(const struct option*& longopts) {
        int err = 0;
        static const char_t* chars = XOS_APP_CONSOLE_RETE_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_APP_CONSOLE_RETE_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
    virtual const char_t* arguments(const char_t**& argv) {
        static const char_t* _args = XOS_APP_CONSOLE_RETE_MAIN_ARGS;
        static const char_t* _argv[] = {
            XOS_APP_CONSOLE_RETE_MAIN_ARGV
            0};
        argv = _argv;
        return _args;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS main_opt

} /// namespace rete
} /// namespace console
} /// namespace app
} /// namespace xos

#endif /// _XOS_APP_CONSOLE_RETE_MAIN_OPT_HPP 
