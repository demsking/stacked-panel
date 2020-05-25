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

find_program(STYLUS_BIN NAMES stylus)
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

#
## CMake Modules
include("cmake/InstallModule.cmake")

load_cmake_module("StableCoder")
load_cmake_module("CompilerInfo")
load_cmake_module("ProcessorInfo")
load_cmake_module("ConfigureInstaller")
load_cmake_module("CPPLINT")

install_stablecoder_script("tools")
install_stablecoder_script("c++-standards")
install_stablecoder_script("compiler-options")
install_stablecoder_script("sanitizers")

cxx_14()

cppcheck(
  --quiet --force --verbose
  --enable=warning,performance,portability,information,missingInclude
  --suppress=missingIncludeSystem
)

clang_tidy(
  -format-style=file
  -checks=*
  -warnings-as-errors=*
  -header-filter='${CMAKE_SOURCE_DIR}/src/*'
)

compiler_info()
processor_info()
configure_install()
add_cpplint(${TARGET} --counting=detailed)

# Install library
install(TARGETS ${TARGET} DESTINATION lib)

# Install headers
file(GLOB_RECURSE HEADERS
  src/global.h
  src/components/StackedPanel.h
  src/components/StackedPanelToolbox.h
  src/components/StackedPanelWidget.h
  src/components/StackedPanelFrame.h
  src/components/StackedPanelBar.h
  src/components/LandingWidget.h
  src/models/StackedPanelItem.h
  src/models/StackedPanelModel.h
)

install(FILES ${HEADERS} DESTINATION include/hpx-stacked-panel)

# Package
install(FILES HPXStackedPanelConfig.cmake DESTINATION lib/HPXStackedPanel)

# Theme task
set(THEME_DIR "${CMAKE_BINARY_DIR}/themes")

file(GLOB_RECURSE THEME_IMAGES src/*.svg)

if(CMAKE_BUILD_TYPE MATCHES "Release")
  set(STYLUS_ARGS --compress --sourcemap)
endif()

add_custom_target(themes
  COMMAND ${CMAKE_COMMAND} -E make_directory ${THEME_DIR}
  COMMAND ${STYLUS_BIN} ${STYLUS_ARGS} src/themes -o ${THEME_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy ${THEME_IMAGES} ${THEME_DIR}
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "Generating themes"
  VERBATIM
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
