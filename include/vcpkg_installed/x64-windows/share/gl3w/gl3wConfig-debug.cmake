#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "unofficial::gl3w::gl3w" for configuration "Debug"
set_property(TARGET unofficial::gl3w::gl3w APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(unofficial::gl3w::gl3w PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/gl3w.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/gl3w.dll"
  )

list(APPEND _cmake_import_check_targets unofficial::gl3w::gl3w )
list(APPEND _cmake_import_check_files_for_unofficial::gl3w::gl3w "${_IMPORT_PREFIX}/debug/lib/gl3w.lib" "${_IMPORT_PREFIX}/debug/bin/gl3w.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
