cmake_minimum_required(VERSION 3.10)  
project(image_cleander)

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
add_executable(image_cleaner src/main.c src/filelist.c src/list_diff.c src/curl_list.c src/remove_file.c )

# Link libraries
target_link_libraries(image_cleaner
  CURL::libcurl
  jansson
)
