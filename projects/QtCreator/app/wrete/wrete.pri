########################################################################
# Copyright (c) 1988-2019 $organization$
#
# This software is provided by the author and contributors ``as is''
# and any express or implied warranties, including, but not limited to,
# the implied warranties of merchantability and fitness for a particular
# purpose are disclaimed. In no event shall the author or contributors
# be liable for any direct, indirect, incidental, special, exemplary,
# or consequential damages (including, but not limited to, procurement
# of substitute goods or services; loss of use, data, or profits; or
# business interruption) however caused and on any theory of liability,
# whether in contract, strict liability, or tort (including negligence
# or otherwise) arising in any way out of the use of this software,
# even if advised of the possibility of such damage.
#
#   File: wrete.pri
#
# Author: $author$
#   Date: 2/13/2019
#
# QtCreator .pri file for rete executable wrete
########################################################################

########################################################################
# wrete

# wrete TARGET
#
wrete_TARGET = wrete

# wrete INCLUDEPATH
#
wrete_INCLUDEPATH += \
$${rete_INCLUDEPATH} \

# wrete DEFINES
#
wrete_DEFINES += \
$${rete_DEFINES} \

########################################################################
# wrete OBJECTIVE_HEADERS
#
#wrete_OBJECTIVE_HEADERS += \
#$${RETE_SRC}/rete/base/Base.hh \

# wrete OBJECTIVE_SOURCES
#
#wrete_OBJECTIVE_SOURCES += \
#$${RETE_SRC}/rete/base/Base.mm \

########################################################################
# wrete HEADERS
#
wrete_HEADERS += \
$${RETE_SRC}/xos/network/sockets/microsoft/windows/os.hpp \
$${RETE_SRC}/xos/network/sockets/microsoft/windows/interface.hpp \
$${RETE_SRC}/xos/network/sockets/microsoft/windows/main.hpp \

# wrete SOURCES
#
wrete_SOURCES += \
$${RETE_SRC}/xos/network/sockets/microsoft/windows/os.cpp \
$${RETE_SRC}/xos/network/sockets/microsoft/windows/interface.cpp \
$${RETE_SRC}/xos/network/sockets/microsoft/windows/main.cpp \

########################################################################
# wrete FRAMEWORKS
#
wrete_FRAMEWORKS += \
$${rete_FRAMEWORKS} \

# wrete LIBS
#
wrete_LIBS += \
$${rete_LIBS} \


