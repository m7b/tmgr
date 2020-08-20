CMAKE_MINIMUM_REQUIRED( VERSION 3.9.6 )

PROJECT(tmgr VERSION 2.2.0)
SET(VERSION_DEV_STAGE "\" (Pre-alpha)\"")
#SET(VERSION_DEV_STAGE "\" (Alpha)\"")
#SET(VERSION_DEV_STAGE "\" (Beta)\"")
#SET(VERSION_DEV_STAGE "")

CONFIGURE_FILE(
  ${PROJECT_SOURCE_DIR}/inc/version.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/version.h
)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/nsis")

ADD_SUBDIRECTORY(doc)

## wxWidgets
SET(wxWidgets_ROOT_DIR "W:/wxWidgets-3.0.5.1")
SET(wxWidgets_LIB_DIR "W:/wxWidgets-3.0.5.1/lib/gcc_lib")
SET(wxWidgets_CONFIGURATION mswu)
FIND_PACKAGE(wxWidgets 3.0.5 REQUIRED ribbon aui propgrid richtext adv html core xml base)
INCLUDE("${wxWidgets_USE_FILE}")


## Boost
#SET(Boost_DEBUG ON)
#SET(Boost_COMPILER "-mgw92")
SET(Boost_ARCHITECTURE "-x64")
SET(BOOST_ROOT "W:/boost_1_73_0")
SET(BOOST_INCLUDEDIR "W:/boost_1_73_0")
SET(BOOST_LIBRARYDIR "W:/boost_1_73_0/stage/lib")
SET(Boost_USE_STATIC_LIBS        ON)
SET(Boost_USE_MULTITHREADED      ON)
SET(Boost_USE_STATIC_RUNTIME    OFF)
FIND_PACKAGE(Boost 1.73.0 REQUIRED filesystem date_time)



SET( SQLITE_INC     "W:/sqlite-amalgamation-3320300")
SET( SPDLOG_INC     "W:/spdlog-1.6.1/include")


# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${CMAKE_CURRENT_BINARY_DIR}"
                    "${PROJECT_SOURCE_DIR}/inc"
                    "${PROJECT_SOURCE_DIR}/wxfb"
                    "${Boost_INCLUDE_DIRS}"
                    "${SQLITE_INC}"
                    "${SPDLOG_INC}"
)


add_library(
    sqlite
    ${SQLITE_INC}/sqlite3.c
)
#set_source_files_properties(${SQLITE_INC}/sqlite3.c PROPERTIES COMPILE_FLAGS "-O3 -Wno-unused-but-set-variable -DSQLITE_DQS=0")


# add the executable
add_executable(
    ${CMAKE_PROJECT_NAME}
    WIN32
    src/C_DbHandle.cpp
    src/C_OsmDownloader.cpp
    src/C_Report.cpp
    src/C_ReportAssignementDuration.cpp
    src/C_ReportAssignements.cpp
    src/C_ReportMapCreator.cpp
    src/C_ReportMapCreatorAll.cpp
    src/C_ReportMapInlet.cpp
    src/C_ReportNotAssigned.cpp
    src/C_ReportNoVisits.cpp
    src/C_ReportOverview.cpp
    src/C_Settings.cpp
    src/C_wxDataListPanel_NoVisits.cpp
    src/C_wxDataListPanel_Tips.cpp
    src/C_wxDecorator.cpp
    src/C_wxDlgInfo.cpp
    src/C_wxImagePanel.cpp
    src/C_wxLCtrlExtended.cpp
    src/C_wxPanelActions.cpp
    src/C_wxPanelProperties.cpp
    src/C_wxPanelTerritoryProperties.cpp
    src/C_wxPopupMenu.cpp
    src/C_wxScrolledImageComponent.cpp
    src/C_wxScrolledWindowCat.cpp
    src/C_wxTmgrMainFrame.cpp
    src/C_wxTmgrMainFrameManager.cpp
    src/helpers.cpp
    src/logger.cpp
    src/safe_wx_str.cpp
    src/TerritoryMgrApp.cpp
    src/wxIconBundleResLoader.cpp
    wxfb/C_wxActions.cpp
    wxfb/C_wxInfoDialog.cpp
    wxfb/C_wxListPanel.cpp
    wxfb/C_wxProperties.cpp
    wxfb/C_wxTerritoryProperties.cpp
    wxfb/C_wxTmgr.cpp
    res/resource.rc
#   res/svn.rc
)



# target compile options
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:-g>)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:-O0>)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC $<$<CONFIG:Release>:-Ofast>)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -funroll-loops)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -mthreads)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -pipe)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -Wall)


# target compile definitions
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC -DEXE_NAME=${CMAKE_PROJECT_NAME})
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC -D__GNUWIN32__)
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC -D__WXMSW__)
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC -D_WIN32_WINNT=0x0601)
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC -DwxUSE_UNICODE)
#target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC -DwxNO_UNSAFE_WXSTRING_CONV)
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC $<$<CONFIG:Release>:wxDEBUG_LEVEL=0>)
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:wxDEBUG_LEVEL=1>)


# a custom target that is always built
SET(SVN_HEADER_TMPL ${PROJECT_SOURCE_DIR}/inc/svn_version.tmpl)
SET(SVN_HEADER_H    ${CMAKE_CURRENT_BINARY_DIR}/svn_version.h)
ADD_CUSTOM_TARGET(
    svnheader
    ALL
    COMMAND cmake -E copy ${SVN_HEADER_TMPL} ${SVN_HEADER_H}
    COMMENT "Write subversion information in header file: ${SVN_HEADER_H}"
)


# generate CHANGELOG from *.md to *.html (on change)
FIND_PROGRAM(PANDOC_EXECUTABLE V:/pandoc-2.6-windows-x86_64/pandoc.exe)
SET(CHANGELOG_MD   ${PROJECT_SOURCE_DIR}/CHANGELOG.md)
SET(CHANGELOG_HTML ${CMAKE_CURRENT_BINARY_DIR}/CHANGELOG.html)
ADD_CUSTOM_COMMAND(
    OUTPUT ${CHANGELOG_HTML}
    COMMAND ${PANDOC_EXECUTABLE} ${CHANGELOG_MD} -o ${CHANGELOG_HTML}
    DEPENDS ${CHANGELOG_MD}
)
ADD_CUSTOM_TARGET(
    changelog
    DEPENDS ${CHANGELOG_HTML}
    COMMENT "Create changelog file (md to html)"
)
SET_PROPERTY(SOURCE res/resource.rc APPEND PROPERTY OBJECT_DEPENDS ${CHANGELOG_HTML})


# generate TOOLCHAIN from *.md to *.html (on change)
SET(TOOLCHAIN_MD   ${PROJECT_SOURCE_DIR}/TOOLCHAIN.md)
SET(TOOLCHAIN_HTML ${CMAKE_CURRENT_BINARY_DIR}/TOOLCHAIN.html)
ADD_CUSTOM_COMMAND(
    OUTPUT ${TOOLCHAIN_HTML}
    COMMAND ${PANDOC_EXECUTABLE} ${TOOLCHAIN_MD} -o ${TOOLCHAIN_HTML}
    DEPENDS ${TOOLCHAIN_MD}
)
ADD_CUSTOM_TARGET(
    toolchain
    DEPENDS ${TOOLCHAIN_HTML}
    COMMENT "Create toolchain file (md to html)"
)
SET_PROPERTY(SOURCE res/resource.rc APPEND PROPERTY OBJECT_DEPENDS ${TOOLCHAIN_HTML})


# # generate SVNLog (always)
# FIND_PROGRAM(SVN_EXECUTABLE svn)
# SET(SVNLOG_NEW ${CMAKE_CURRENT_BINARY_DIR}/svnlog_new.txt)
# SET(SVNLOG     ${CMAKE_CURRENT_BINARY_DIR}/svnlog.txt)
# ADD_CUSTOM_TARGET(
    # svnlog
	# ALL
    # COMMAND ${SVN_EXECUTABLE} log ${PROJECT_SOURCE_DIR} -l 20 -r HEAD:1 > ${SVNLOG_NEW}
    # COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SVNLOG_NEW} ${SVNLOG}
    # COMMENT "Create SVN-log file"
# )
# SET_PROPERTY(SOURCE res/svn.rc APPEND PROPERTY OBJECT_DEPENDS ${SVNLOG})



if(CMAKE_BUILD_TYPE STREQUAL Release)
    MESSAGE(STATUS "Do minimal size release stuff")
    FIND_PROGRAM(UPX_EXECUTABLE V:/upx-3.96-win64/upx.exe)
    ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${UPX_EXECUTABLE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
    COMMENT "Running UPX packer ..."
    )
endif()



# link libraries
target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    ${wxWidgets_LIBRARIES}
    ${Boost_LIBRARIES}
    sqlite
    shlwapi
    version
    oleacc
    -static
    -static-libgcc
    -static-libstdc++
    $<$<CONFIG:Release>:-s>
)


ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(nsis)


#VERA Code Checker Variante A ##################################################
#find_package(vera++)
#include(${VERA++_USE_FILE})
#get_filename_component(VERA++_ROOT ${VERA++_USE_FILE} PATH)
#add_vera_targets(
#    *.h *.cpp
#    RECURSE
#    ROOT "${VERA++_ROOT}"
#)
#MESSAGE("VERA++_USE_FILE ${VERA++_USE_FILE}")
#MESSAGE("VERA++ Executable ${VERA++_EXECUTABLE}")
#MESSAGE("VERA++ Root ${VERA++_ROOT}")


#VERA Code Checker Variante B ##################################################
#enable_testing()
#file(GLOB_RECURSE srcs
#  ${CMAKE_SOURCE_DIR}/src/*.cpp
#  ${CMAKE_SOURCE_DIR}/inc/*.h)
#add_test(NAME VeraStyle
#  COMMAND vera++
#  --show-rule
##  --error
#  -P max-line-length=120
#  -R L001
#  -R L002
#  -R L003
## -R L004 #Line cannot be too long
#  -R L005
#  -R L006
#  -R T001
#  -R T002
#  -R T003
#  -R T004
#  -R T005
#  -R T006
#  -R T007
## -R T008 #Keywords catch, for, if, switch and while should be followed by a single space
## -R T009 #Comma should not be preceded by whitespace, but should be followed by one
## -R T010 #Identifiers should not be composed of 'l' and 'O' characters only
#  -R T011
## -R T012 #Negation operator should not be used in its short form
## -R T013 #Source files should contain the copyright notice
## -R T014 #Source files should refer the Boost Software License
#  -R T015
#  -R T016
#  -R T017
#  -R T018
#  -R T019
#  ${srcs})