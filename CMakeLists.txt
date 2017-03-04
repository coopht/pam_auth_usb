# Copyright (c) <2017> <Alexander Basov>

cmake_minimum_required(VERSION 3.2)
project(pam_usb_auth)

find_package(PkgConfig)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

if (NOT LIBUSB_FOUND)
    message(FATAL_ERROR "libusb not found")
endif(NOT LIBUSB_FOUND)

set (CMAKE_CXX_FLAGS "-std=c++0x -Wall -O2")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")

    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Werror")

endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

add_subdirectory(src)
