## for each executable we want to build we need an
## add_executable and a target_link_libraries line
message("Building executable: version")

add_executable(version version.cpp)
target_link_libraries(version LINK_PUBLIC OpenType)

## executables created to test certain features
add_executable(test_endian test_endian.cpp)
add_executable(test_ids test_ids.cpp)
target_link_libraries(test_ids LINK_PUBLIC OpenType)

#add_executable(drawfont drawfont.cpp)
#target_link_libraries(drawfont LINK_PUBLIC OpenType glfw  GLEW GL)
