# Copyright (c) <2017> <Alexander Basov>

set (PAM_LIB_SRC config.cpp
                 pam.cpp
                 usb_device.cpp)

set (PAM_LIB_HDRS config.h
                  device.h
                  usb_device.h)

add_library(pam_usb_auth SHARED ${PAM_LIB_GDRS} ${PAM_LIB_SRC})
target_link_libraries(pam_usb_auth ${LIBUSB_LIBRARIES})

SET_TARGET_PROPERTIES(pam_usb_auth PROPERTIES PREFIX "")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/pam_usb.conf.in ${CMAKE_CURRENT_BINARY_DIR}/pam_usb.conf)

install(TARGETS pam_usb_auth LIBRARY DESTINATION /lib/security)
install(FILES pam_usb.conf.in LIBRARY DESTINATION /etc/)
