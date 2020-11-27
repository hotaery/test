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
        pthread
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

FILE(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
INCLUDE_DIRECTORIES(/usr/local/include)
INCLUDE_DIRECTORIES(/Users/daliang/github/incubator-brpc/bld/output/include)
INCLUDE_DIRECTORIES(${CMAKE_INSTALL_PREFIX}/include)
LINK_DIRECTORIES(${CMAKE_INSTALL_PREFIX}/lib /usr/local/lib)
SET(BRPC_LIB /Users/daliang/github/incubator-brpc/bld/output/lib/libbrpc.a)
SET(LIBS gflags protobuf ssl crypto leveldb)
ADD_EXECUTABLE(test ${SOURCES})
ADD_DEPENDENCIES(test data_structure utils proto)
TARGET_LINK_LIBRARIES(test data_structure.a utils.a proto.a ${BRPC_LIB} ${LIBS} ${DYNAMIC_LIB})
INSTALL(TARGETS test RUNTIME DESTINATION ../)

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