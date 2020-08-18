set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})

#set(CPACK_PACKAGE_VENDOR "CMake.org")
#set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "MyLib - CPack Component Installation Example")
#set(CPACK_PACKAGE_VERSION "1.0.0")
#set(CPACK_PACKAGE_VERSION_MAJOR "1")
#set(CPACK_PACKAGE_VERSION_MINOR "2")
#set(CPACK_PACKAGE_VERSION_PATCH "0")
#set(CPACK_PACKAGE_INSTALL_DIRECTORY "CPack Component Example")

set(CPACK_PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(CPACK_CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(CPACK_PROJECT_BINARY_DIR ${tmgr_BINARY_DIR})

# Load packaging facilities.
include(CPack)

# Configure file with custom definitions for NSIS.
#configure_file(
#  ${PROJECT_SOURCE_DIR}/nsis/installer.nsi.in
#  ${CMAKE_CURRENT_BINARY_DIR}/installer.nsi
#)