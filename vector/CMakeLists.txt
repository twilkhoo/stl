add_library(vector vector.cc)

target_include_directories(vector
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
