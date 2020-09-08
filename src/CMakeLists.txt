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
FILE(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
INCLUDE_DIRECTORIES(/home/arma/project/incubator-brpc/bld/output/include)
INCLUDE_DIRECTORIES(${CMAKE_INSTALL_PREFIX}/include)
LINK_DIRECTORIES(${CMAKE_INSTALL_PREFIX}/lib)
SET(BRPC_LIB /home/arma/project/incubator-brpc/bld/output/lib/libbrpc.a)
SET(LIBS pthread gflags protobuf ssl crypto)
ADD_EXECUTABLE(test ${SOURCES})
ADD_DEPENDENCIES(test data_structure utils)
TARGET_LINK_LIBRARIES(test ${BRPC_LIB} ${LIBS} data_structure.a utils.a)
INSTALL(TARGETS test RUNTIME DESTINATION ../)
