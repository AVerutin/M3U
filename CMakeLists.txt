cmake_minimum_required(VERSION 3.20)
project(m3u)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(SKIP_BUILD_TEST on)

find_package(Boost COMPONENTS regex REQUIRED)
IF(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    # message(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")
endif()


#add_compile_options(-l sqlite3)
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -lpthread -lsqlite3")

include_directories(src/includes/sqlite3pp)
include_directories(src/models)
include_directories(src/forms)
include_directories(src/source)

set(SOURCE src/main.cpp
        src/models/DbItem.cpp
        src/models/DbItem.h
        src/source/DbConnection.cpp
        src/source/DbConnection.h
        src/source/Logger.cpp
        src/source/Logger.h
        src/source/M3UParser.cpp
        src/source/M3UParser.h
        src/source/datatype.h
        src/models/Channel.cpp
        src/models/Channel.h
        src/models/Playlist.cpp
        src/models/Playlist.h
        )

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC sqlite3 ${Boost_LIBRARIES}) # ${SQLITE3_LIBRARY_DIRS}
