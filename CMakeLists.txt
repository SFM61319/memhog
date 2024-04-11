cmake_minimum_required(VERSION 3.22.1...3.25.1 FATAL_ERROR)
project("memhog"
  VERSION 0.1.0
  DESCRIPTION "A C program to hog given (or all) memory."
  HOMEPAGE_URL "https://github.com/SFM61319/memhog"
  LANGUAGES C)

if(PROJECT_IS_TOP_LEVEL)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  set(CPACK_PROJECT_NAME "${PROJECT_NAME}")
  set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
  include(CPack)

  set(CMAKE_C_STANDARD 17)
  set(CMAKE_C_STANDARD_REQUIRED ON)
  set(CMAKE_C_EXTENSIONS OFF)

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)

  if(MSVC)
    set(MEMHOG_COMPILER_WARNING_FLAGS
      "/Wall"
      "/WX")
  else()
    set(MEMHOG_COMPILER_WARNING_FLAGS
      "-Wall"
      "-Wextra"
      "-Wpedantic"
      "-Werror")
  endif()
endif()

set(MEMHOG_PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

set(MEMHOG_INCLUDE_DIR "${MEMHOG_PROJECT_ROOT}/include")
set(MEMHOG_SRC_DIR "${MEMHOG_PROJECT_ROOT}/src")

set(MEMHOG_PUBLIC_HEADERS_DIR "${MEMHOG_INCLUDE_DIR}")
set(MEMHOG_PRIVATE_SOURCES_DIR "${MEMHOG_SRC_DIR}")

set(MEMHOG_PUBLIC_HEADERS "${MEMHOG_PUBLIC_HEADERS_DIR}/${PROJECT_NAME}.h")
set(MEMHOG_PRIVATE_SOURCES
  "${MEMHOG_PRIVATE_SOURCES_DIR}/main.c"
  "${MEMHOG_PRIVATE_SOURCES_DIR}/${PROJECT_NAME}.c")

option(MEMHOG_INSTALL "Setup CMake install" ${PROJECT_IS_TOP_LEVEL})

add_executable("${PROJECT_NAME}")
target_compile_options("${PROJECT_NAME}"
  PRIVATE
    ${MEMHOG_COMPILER_WARNING_FLAGS})
target_include_directories("${PROJECT_NAME}"
  PUBLIC
    $<BUILD_INTERFACE:${MEMHOG_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_sources("${PROJECT_NAME}"
  PRIVATE
    ${MEMHOG_PRIVATE_SOURCES})

if(MEMHOG_INSTALL)
  include(GNUInstallDirs)
  include(CMakePackageConfigHelpers)

  if(DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX
      "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}"
      CACHE PATH "Where the library will be installed to" FORCE)
  endif()

  install(TARGETS "${PROJECT_NAME}"
    EXPORT "${PROJECT_NAME}Targets"
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

  install(EXPORT "${PROJECT_NAME}Targets"
    FILE "${PROJECT_NAME}Targets.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

  write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${VERSION}
    COMPATIBILITY AnyNewerVersion)

  configure_package_config_file("${MEMHOG_PROJECT_ROOT}/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

  install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

  export(EXPORT "${PROJECT_NAME}Targets"
    FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Targets.cmake")
endif()

# Ensure that the project is not being built in the project root or any directory with a CMakeLists.txt file.
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
  message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()
