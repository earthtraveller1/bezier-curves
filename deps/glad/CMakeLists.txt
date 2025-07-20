add_library(glad src/glad.c include/glad/glad.h include/KHR/khrplatform.h)

target_include_directories(glad SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/deps/glad/include)
