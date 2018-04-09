cmake_minimum_required(VERSION 2.6)

set(CMAKE_INSTALL_PREFIX / opt/trochilus-0.0.1)

project(trochilus-0.0.1)

set(SRC_FILES
        trls_queue.h
        trls_queue.c)

add_library(trochilus SHARED ${SRC_FILES})

install(FILES
        trls_base.h
        trls_queue.h
        trls_config.h
        DESTINATION include)

install(TARGETS
        trochilus
        LIBRARY DESTINATION lib64)

include_directories(.)
