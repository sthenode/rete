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
#   File: wrete.pro
#
# Author: $author$
#   Date: 2/13/2019
#
# QtCreator .pro file for rete executable wrete
########################################################################
include(../../../../../build/QtCreator/rete.pri)
include(../../../../QtCreator/rete.pri)
include(../../rete.pri)
include(../../../../QtCreator/app/wrete/wrete.pri)

TARGET = $${wrete_TARGET}

########################################################################
# INCLUDEPATH
#
INCLUDEPATH += \
$${wrete_INCLUDEPATH} \

# DEFINES
# 
DEFINES += \
$${wrete_DEFINES} \

########################################################################
# OBJECTIVE_HEADERS
#
OBJECTIVE_HEADERS += \
$${wrete_OBJECTIVE_HEADERS} \

# OBJECTIVE_SOURCES
#
OBJECTIVE_SOURCES += \
$${wrete_OBJECTIVE_SOURCES} \

########################################################################
# HEADERS
#
HEADERS += \
$${wrete_HEADERS} \
$${OBJECTIVE_HEADERS} \

# SOURCES
#
SOURCES += \
$${wrete_SOURCES} \

########################################################################
# FRAMEWORKS
#
FRAMEWORKS += \
$${wrete_FRAMEWORKS} \

# LIBS
#
LIBS += \
$${wrete_LIBS} \
$${FRAMEWORKS} \


