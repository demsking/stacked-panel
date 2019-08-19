cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

set(TARGET demo)

project(${TARGET})

set(QT_MIN_VERSION "5.11.0")
set(KF5_MIN_VERSION "5.46.0")
set(CMAKE_CXX_STANDARD 14)

find_program(MAKE NAMES make)
find_package(ECM 1.3.0 REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(ECMInstallIcons)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
  Core
  Widgets
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
  IconThemes
  Config
)

find_package(KF5Config REQUIRED)

#
## TARGET
file(GLOB_RECURSE SOURCES src/*.h src/*.cpp ../src/*.h ../src/*.cpp)

include_directories(src)

link_directories(${CMAKE_BINARY_DIR}/lib)

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} LINK_PUBLIC
  Qt5::Core
  Qt5::Widgets
  KF5::IconThemes
  KF5::ConfigCore
)
