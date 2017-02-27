cmake_minimum_required(VERSION 2.6)
project(pam_auth)

add_executable(pam_auth main.cpp)

install(TARGETS pam_auth RUNTIME DESTINATION bin)
