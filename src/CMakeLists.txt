CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
INCLUDE(ExternalProject)
ExternalProject_Add(
    data_structure 
    URL ${CMAKE_CURRENT_SOURCE_DIR}/data_structure/
    DOWNLOAD_NO_EXTRACT 1
    CONFIGURE_COMMAND cmake -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} .
    BUILD_COMMAND make 
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND make install
)

ExternalProject_Add(
    utils
    URL ${CMAKE_CURRENT_SOURCE_DIR}/utils/
    DOWNLOAD_NO_EXTRACT 1
    CONFIGURE_COMMAND cmake -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} .
    BUILD_COMMAND make 
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND make install
)

ExternalProject_Add(
    proto
    URL ${CMAKE_CURRENT_SOURCE_DIR}/proto/
    DOWNLOAD_NO_EXTRACT 1
    CONFIGURE_COMMAND cmake -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} .
    BUILD_COMMAND make 
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND make install
)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(DYNAMIC_LIB ${DYNAMIC_LIB}
        "-framework CoreFoundation"
        "-framework CoreGraphics"
        "-framework CoreData"
        "-framework CoreText"
        "-framework Security"
        "-framework Foundation"
        "-Wl,-U,_MallocExtension_ReleaseFreeMemory"
        "-Wl,-U,_ProfilerStart"
        "-Wl,-U,_ProfilerStop")
endif()

SET(BRPC_PREFIX /home/daliang/github)
FILE(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
INCLUDE_DIRECTORIES(
    /usr/include 
    ${BRPC_PREFIX}/incubator-brpc/bld/output/include 
    ${CMAKE_INSTALL_PREFIX}/include
)
LINK_DIRECTORIES(${CMAKE_INSTALL_PREFIX}/lib /usr/lib/x86_64-linux-gnu)
SET(BRPC_LIB ${BRPC_PREFIX}/incubator-brpc/bld/output/lib/libbrpc.a)
message(STATUS "wangziliang ${BRPC_LIB}")
SET(LIBS pthread gflags protobuf ssl crypto leveldb dl)
ADD_EXECUTABLE(main ${SOURCES})
ADD_DEPENDENCIES(main data_structure utils proto)
TARGET_LINK_LIBRARIES(main data_structure.a utils.a proto.a ${BRPC_LIB} ${LIBS} ${DYNAMIC_LIB})
INSTALL(TARGETS main RUNTIME DESTINATION ../)

FILE(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/server.cpp)
ADD_EXECUTABLE(server ${SOURCES})
ADD_DEPENDENCIES(server data_structure utils proto)
TARGET_LINK_LIBRARIES(server data_structure.a utils.a proto.a ${BRPC_LIB} ${LIBS} ${DYNAMIC_LIB})
INSTALL(TARGETS server RUNTIME DESTINATION ../)

FILE(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/client.cpp)
ADD_EXECUTABLE(client ${SOURCES})
ADD_DEPENDENCIES(client data_structure utils proto)
TARGET_LINK_LIBRARIES(client data_structure.a utils.a proto.a ${BRPC_LIB} ${LIBS} ${DYNAMIC_LIB})
INSTALL(TARGETS client RUNTIME DESTINATION ../)