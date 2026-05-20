cmake_minimum_required(VERSION 3.10)  
project(file_remover)

# Find the curl library
find_package(CURL REQUIRED)


# Find the jansson library
#find_package(Jansson REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JANSSON REQUIRED jansson)

if(JANSSON_FOUND)
    include_directories(${JANSSON_INCLUDE_DIRS})
    link_directories(${JANSSON_LIBRARY_DIRS})
    #add_executable(translate translate.c)
    #target_link_libraries(translate ${JANSSON_LIBRARIES})
else()
    message(FATAL_ERROR "Jansson library not found!")
endif()
  


# Add executable
add_executable(file_remover src/main.c src/filelist.c src/list_diff.c src/curl_list.c src/remove_file.c )

# Link libraries
target_link_libraries(file_remover 
  CURL::libcurl
  jansson
)
