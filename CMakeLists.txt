cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

set(TARGET HPXStackedPanel)
set(VERSION 1.0.0)
set(AUTHOR "Sébastien Demanou")
set(EMAIL "demsking@gmail.com")
set(WEBSITE "https://gitlab.com/demsking/stacked-panel")
set(BUG_ADDRESS "https://gitlab.com/demsking/stacked-panel/issues")

project(${TARGET})

set(QT_MIN_VERSION "5.9.0")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

set(DIST_DIR ${PROJECT_SOURCE_DIR}/dist)

add_definitions(-DHPX_LIBRARY)

find_program(MAKE NAMES make)
find_package(ECM 1.3.0 REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
  Core
  Widgets
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(packagekitqt5 REQUIRED)

#
## TARGET
file(GLOB_RECURSE SOURCES
  src/*.h
  src/*.cpp
)

include_directories(src)

link_directories(${CMAKE_BINARY_DIR}/lib)

add_library(${TARGET} SHARED ${SOURCES})
target_include_directories (${TARGET} PUBLIC include)

target_link_libraries(${TARGET}
  Qt5::Core
  Qt5::Widgets
)

# Install library
install(TARGETS ${TARGET} DESTINATION lib)

# Install headers
file(GLOB_RECURSE HEADERS
  src/global.h
  src/components/StackedPanel.h
  src/components/StackedPanelToolbox.h
  src/components/StackedPanelWidget.h
  src/components/StackedPanelFrame.h
  src/models/StackedPanelItem.h
  src/models/StackedPanelModel.h
)

install(FILES ${HEADERS} DESTINATION include/hpx-stacked-panel)

# Package
install(FILES HPXStackedPanelConfig.cmake DESTINATION lib/HPXStackedPanel)

# Theme task
if(CMAKE_BUILD_TYPE)
  string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
endif()

add_custom_target(themes
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/themes
  COMMAND ${MAKE} -C ${PROJECT_SOURCE_DIR} themes ENV=${BUILD_TYPE}
)

add_dependencies(${TARGET} themes)

# Packaging task
add_custom_target(pack
  DEPENDS ${CMAKE_BINARY_DIR}/${TARGET}

  COMMAND ${CMAKE_COMMAND} -E remove_directory ${DIST_DIR}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${DIST_DIR} ${DIST_DIR}/lib ${DIST_DIR}/include
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/themes ${DIST_DIR}/themes
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/*.so ${DIST_DIR}/lib
  COMMAND ${CMAKE_COMMAND} -E copy ${HEADERS} ${DIST_DIR}/include
  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/LICENSE ${DIST_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/AUTHORS ${DIST_DIR}
  COMMAND cd ${DIST_DIR} && ${CMAKE_COMMAND} -E tar -zcf ${PROJECT_SOURCE_DIR}/${TARGET}.tar.gz .
)

add_dependencies(pack themes ${TARGET})

install(TARGETS ${TARGET} ${INSTALL_TARGETS_DEFAULT_ARGS})
