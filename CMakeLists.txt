cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

project(HPXStackedPanel VERSION 1.0.0
                        DESCRIPTION "A fully stylized StackedWidget implementation"
                        LANGUAGES CXX)

set(AUTHOR "Sébastien Demanou")
set(EMAIL "demsking@gmail.com")
set(WEBSITE "https://gitlab.com/demsking/stacked-panel")
set(BUG_ADDRESS "https://gitlab.com/demsking/stacked-panel/issues")

set(ECM_VERSION 1.3.0)
set(QT_MIN_VERSION 5.9.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

set(DIST_DIR ${PROJECT_SOURCE_DIR}/dist)
set(INSTALL_INCLUDE_DIR "include/hpx/stacked-panel")

find_program(STYLUS_BIN NAMES stylus)

find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Widgets)
find_package(packagekitqt5 REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)

#
## Target
add_definitions(-DHPX_LIBRARY)

file(GLOB_RECURSE SOURCES src/*.h src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "src")
target_include_directories(${PROJECT_NAME} PUBLIC "include")

target_link_directories(${PROJECT_NAME} PUBLIC "${CMAKE_BINARY_DIR}/lib")
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)

# Export vars
if(PARENT_DIRECTORY)
  set(HPX_STACKEDPANEL_INCLUDE_PATH ${INSTALL_INCLUDE_DIR} PARENT_SCOPE)
  set(HPX_STACKEDPANEL_LIB_NAME ${PROJECT_NAME} PARENT_SCOPE)
endif()

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
compiler_info()
processor_info()
configure_install()

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

add_cpplint(${PROJECT_NAME} --counting=detailed)

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib)

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

install(FILES ${HEADERS} DESTINATION ${INSTALL_INCLUDE_DIR})

# Package
install(FILES HPXStackedPanelConfig.cmake DESTINATION lib/HPXStackedPanel)

# Theme task
set(THEME_DIR "${CMAKE_BINARY_DIR}/themes")

file(GLOB_RECURSE THEME_IMAGES src/*.svg)
file(GLOB_RECURSE THEME_STYLES src/*.styl)
list(REMOVE_ITEM THEME_STYLES "${PROJECT_SOURCE_DIR}/src/themes/mixins.styl")

if(CMAKE_BUILD_TYPE MATCHES "Release")
  set(STYLUS_ARGS --compress --sourcemap)
endif()

add_custom_target(themes
  COMMENT "Generating themes"
  COMMAND ${CMAKE_COMMAND} -E make_directory ${THEME_DIR}
  COMMAND ${STYLUS_BIN} ${STYLUS_ARGS} ${THEME_STYLES} -o ${THEME_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy ${THEME_IMAGES} ${THEME_DIR}
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  VERBATIM
)

add_dependencies(${PROJECT_NAME} themes)

# Packaging task
add_custom_target(pack
  COMMENT "Packaging"
  DEPENDS ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${DIST_DIR}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${DIST_DIR} ${DIST_DIR}/lib ${DIST_DIR}/include
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/themes ${DIST_DIR}/themes
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/*.so ${DIST_DIR}/lib
  COMMAND ${CMAKE_COMMAND} -E copy ${HEADERS} ${DIST_DIR}/include
  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/LICENSE ${DIST_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/AUTHORS ${DIST_DIR}
  COMMAND cd ${DIST_DIR} && ${CMAKE_COMMAND} -E tar -zcf ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}.tar.gz .
)

add_dependencies(pack themes ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} ${INSTALL_TARGETS_DEFAULT_ARGS})
