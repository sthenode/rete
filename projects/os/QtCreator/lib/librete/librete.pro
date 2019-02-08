########################################################################
# Copyright (c) 1988-2018 $organization$
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
#   File: librete.pro
#
# Author: $author$
#   Date: 5/30/2018
#
# QtCreator .pro file for rete library librete
########################################################################
include(../../../../../build/QtCreator/rete.pri)
include(../../../../QtCreator/rete.pri)
include(../../rete.pri)
include(../../../../QtCreator/lib/librete/librete.pri)

TARGET = $${librete_TARGET}
TEMPLATE = $${librete_TEMPLATE}
CONFIG += $${librete_CONFIG}

########################################################################
# INCLUDEPATH
#
INCLUDEPATH += \
$${librete_INCLUDEPATH} \

# DEFINES
# 
DEFINES += \
$${librete_DEFINES} \

# OBJECTIVE_SOURCES
#
OBJECTIVE_SOURCES += \
$${librete_OBJECTIVE_SOURCES} \

########################################################################
# HEADERS
#
HEADERS += \
$${librete_HEADERS} \
$${OBJECTIVE_HEADERS} \

# SOURCES
#
SOURCES += \
$${librete_SOURCES} \

########################################################################


