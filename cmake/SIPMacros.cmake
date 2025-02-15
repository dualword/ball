# Macros for SIP
# ~~~~~~~~~~~~~~
# Copyright (c) 2007, Simon Edwards <simon@simonzone.com>
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#
# SIP website: http://www.riverbankcomputing.co.uk/sip/index.php
#
# This file defines the following macros:
#
# ADD_SIP_PYTHON_MODULE (MODULE_NAME MODULE_SIP [library1, libaray2, ...])
#     Specifies a SIP file to be built into a Python module and installed.
#     MODULE_NAME is the name of Python module including any path name. (e.g.
#     os.sys, Foo.bar etc). MODULE_SIP the path and filename of the .sip file
#     to process and compile. OUTPUT_BASENAME is the basename of the library to be generated,
#			and libraryN are libraries that the Python module,
#     which is typically a shared library, should be linked to. The built
#     module will also be install into Python's site-packages directory.
#
# The behaviour of the ADD_SIP_PYTHON_MODULE macro can be controlled by a
# number of variables:
#
# SIP_INCLUDES - List of directories which SIP will scan through when looking
#     for included .sip files. (Corresponds to the -I option for SIP.)
#
# SIP_TAGS - List of tags to define when running SIP. (Corresponds to the -t
#     option for SIP.)
#
# SIP_CONCAT_PARTS - An integer which defines the number of parts the C++ code
#     of each module should be split into. Defaults to 8. (Corresponds to the
#     -j option for SIP.)
#
# SIP_DISABLE_FEATURES - List of feature names which should be disabled
#     running SIP. (Corresponds to the -x option for SIP.)
#
# SIP_EXTRA_OPTIONS - Extra command line options which should be passed on to
#     SIP.

SET(SIP_INCLUDES)
SET(SIP_TAGS)
SET(SIP_CONCAT_PARTS 8)
SET(SIP_DISABLE_FEATURES)
SET(SIP_EXTRA_OPTIONS)

MACRO(ADD_SIP_PYTHON_MODULE MODULE_NAME OUTPUT_BASENAME MODULE_SIP)

    SET(EXTRA_LINK_LIBRARIES ${ARGN})

    STRING(REPLACE "." "/" _x ${MODULE_NAME})
    GET_FILENAME_COMPONENT(_parent_module_path ${_x} PATH)
    GET_FILENAME_COMPONENT(_child_module_name  ${_x} NAME)

    GET_FILENAME_COMPONENT(_module_path    ${MODULE_SIP} PATH)
    GET_FILENAME_COMPONENT(_abs_module_sip ${MODULE_SIP} ABSOLUTE)

    SET(SIP_MODULE_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/${OUTPUT_BASENAME})    # Output goes in this dir.
    FILE(MAKE_DIRECTORY ${SIP_MODULE_BINARY_DIR})

    SET(_sip_includes)
    FOREACH (_inc ${SIP_INCLUDES})
        GET_FILENAME_COMPONENT(_abs_inc ${_inc} ABSOLUTE)
        LIST(APPEND _sip_includes -I ${_abs_inc})
    ENDFOREACH (_inc )

    SET(_sip_tags)
    FOREACH (_tag ${SIP_TAGS})
        LIST(APPEND _sip_tags -t ${_tag})
    ENDFOREACH (_tag)

    SET(_sip_x)
    FOREACH (_x ${SIP_DISABLE_FEATURES})
        LIST(APPEND _sip_x -x ${_x})
    ENDFOREACH (_x ${SIP_DISABLE_FEATURES})

    SET(_message "-DMESSAGE=Generating CPP code for module ${MODULE_NAME}")
    SET(_sip_output_files)
    FOREACH(CONCAT_NUM RANGE 0 ${SIP_CONCAT_PARTS} )
        IF( ${CONCAT_NUM} LESS ${SIP_CONCAT_PARTS} )
            SET(_sip_output_files ${_sip_output_files} ${SIP_MODULE_BINARY_DIR}/sip${MODULE_NAME}part${CONCAT_NUM}.cpp )
        ENDIF( ${CONCAT_NUM} LESS ${SIP_CONCAT_PARTS} )
    ENDFOREACH(CONCAT_NUM RANGE 0 ${SIP_CONCAT_PARTS} )

    IF(NOT WIN32)
        SET(TOUCH_COMMAND touch)
    ELSE(NOT WIN32)
        SET(TOUCH_COMMAND echo)
        # instead of a touch command, give out the name and append to the files
        # this is basically what the touch command does.
        FOREACH(filename ${_sip_output_files})
            FILE(APPEND filename "")
        ENDFOREACH(filename ${_sip_output_files})
    ENDIF(NOT WIN32)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${_sip_output_files} 
        COMMAND ${CMAKE_COMMAND} -E echo ${message}
        COMMAND ${TOUCH_COMMAND} ${_sip_output_files} 
        COMMAND ${SIP_EXECUTABLE} ${_sip_tags} ${_sip_x} ${SIP_EXTRA_OPTIONS} -j ${SIP_CONCAT_PARTS} -c ${SIP_MODULE_BINARY_DIR} ${_sip_includes} ${_abs_module_sip}
        DEPENDS ${_abs_module_sip} ${SIP_EXTRA_FILES_DEPEND}
    )
    
    ADD_LIBRARY(${OUTPUT_BASENAME} SHARED ${_sip_output_files} ${SIP_EXTRA_SOURCES})
    TARGET_LINK_LIBRARIES(${OUTPUT_BASENAME} ${PYTHON_LIBRARY})
    TARGET_LINK_LIBRARIES(${OUTPUT_BASENAME} ${EXTRA_LINK_LIBRARIES})
    SET_TARGET_PROPERTIES(${OUTPUT_BASENAME} PROPERTIES PREFIX "" OUTPUT_NAME ${MODULE_NAME})
    SET_TARGET_PROPERTIES(${OUTPUT_BASENAME} PROPERTIES IMPORT_PREFIX "pythonModule_")
    INCLUDE_DIRECTORIES(${SIP_MODULE_BINARY_DIR})

    IF (WIN32)
    	SET_TARGET_PROPERTIES(${OUTPUT_BASENAME} PROPERTIES SUFFIX .pyd)
    ELSEIF (APPLE)
	SET_TARGET_PROPERTIES(${OUTPUT_BASENAME} PROPERTIES SUFFIX .so)
    ENDIF()
#    INSTALL(TARGETS ${_logical_name} DESTINATION "${PYTHON_SITE_PACKAGES_DIR}/${_parent_module_path}")

ENDMACRO(ADD_SIP_PYTHON_MODULE)
