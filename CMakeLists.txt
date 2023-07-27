cmake_minimum_required(VERSION 3.15)
project(eventi)

add_library(eventi)
target_sources(eventi PRIVATE
  src/Callback_ref.cpp
  src/Exceptions.cpp
  src/Scoped_callbacks.cpp
  src/Scoped_defer.cpp
  src/Scoped_disable.cpp)

include(GNUInstallDirs)

target_compile_features(eventi PUBLIC cxx_std_11)
set_target_properties(eventi PROPERTIES DEBUG_POSTFIX "d")

target_include_directories(eventi PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install(
  TARGETS eventi
  EXPORT eventi-config
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
  EXPORT eventi-config
  NAMESPACE eventi::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/eventi)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/eventi/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/eventi)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  # We're in the root, define additional targets for developers.
  option(BUILD_TESTS "Build tests" OFF)

  if(BUILD_TESTS)
    add_subdirectory(tests)
  endif()
endif()
