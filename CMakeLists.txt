project(fis)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(EXTERNAL_LIBS "")
set(EXTRA_DEPS "")
set(CMAKE_BUILD_TYPE "Release")

find_package(Threads REQUIRED)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
set(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${PYTHON_LIBRARIES})

find_package( LIBIGL REQUIRED )
include_directories(${LIBIGL_INCLUDE_DIRS})
set(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${LIBIGL_LIBRARIES})

find_package( CGAL REQUIRED )
include_directories(${CGAL_INCLUDE_DIRS})
set(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${CGAL_LIBRARIES})

# Suppress Eigen's warning by adding it to the system's library
#find_package(Eigen3 REQUIRED)
#include_directories("${EIGEN_INCLUDE_DIR}")
#set(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${Eigen3_LIBRARIES})

#find_package(libnabo REQUIRED PATHS ${LIBNABO_INSTALL_DIR})
#include(libnaboConfig)
#include_directories(${libnabo_INCLUDE_DIRS})
#set(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${libnabo_LIBRARIES})
#message(STATUS "libnabo found, version ${libnabo_VERSION} (include=${libnabo_INCLUDE_DIRS} libs=${libnabo_LIBRARIES})")

find_path(EIGEN_INCLUDE_DIR Eigen/Core
	/usr/local/include/eigen3
	/usr/include/eigen3
)

# Suppress Eigen's warning by adding it to the system's library
include_directories(SYSTEM "${EIGEN_INCLUDE_DIR}")


find_package(Boost COMPONENTS thread filesystem system program_options date_time REQUIRED)

#message(${Boost_INCLUDE_DIRS})
#if (Boost_MINOR_VERSION GREATER 47)
#    find_package(Boost COMPONENTS thread filesystem system program_options date_time chrono REQUIRED)
#endif (Boost_MINOR_VERSION GREATER 47)
include_directories(${Boost_INCLUDE_DIRS})
set(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${Boost_LIBRARIES})


add_executable(test_eigen ./src/test_eigen.cpp)
target_link_libraries(test_eigen ${EXTERNAL_LIBS} CGAL::CGAL)
