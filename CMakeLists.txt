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
#LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/nsis")


INCLUDE(ExternalProject)

# Includ external project wxWidgets
ExternalProject_Add(
  wxWidgets
  GIT_REPOSITORY         https://github.com/wxWidgets/wxWidgets.git
  GIT_TAG                v3.1.4
# GIT_SUBMODULES_RECURSE TRUE
  GIT_SHALLOW            TRUE
  GIT_PROGRESS           FALSE
  CMAKE_ARGS             -DCMAKE_SH="CMAKE_SH-NOTFOUND"  -DwxBUILD_SHARED=NO -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
  INSTALL_COMMAND        ""
)

# Includ external project wxWidgets
string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_LOWER)
ExternalProject_Add(
  Boost
  URL                    https://dl.bintray.com/boostorg/release/1.74.0/source/boost_1_74_0.7z
  URL_HASH               SHA256=903fd40074de8dc733d2f0b6b0642e43b714653eaeb79289b12161b9567fae97
#  GIT_REPOSITORY         https://github.com/boostorg/boost.git
#  GIT_TAG                boost-1.74.0
#  GIT_SUBMODULES_RECURSE TRUE
#  GIT_SHALLOW            TRUE
#  GIT_PROGRESS           FALSE
  BUILD_IN_SOURCE 1
  CONFIGURE_COMMAND      bootstrap.bat gcc
  BUILD_COMMAND          b2 toolset=gcc variant=${CMAKE_BUILD_TYPE_LOWER} link=static address-model=64 --with-filesystem --with-date_time --with-test
  INSTALL_COMMAND        ""
)