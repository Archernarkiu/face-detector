SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
find_package(OpenCV REQUIRED core highgui imgproc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../src)

add_executable(mtcnn mtcnn.cpp mtcnnMain.cpp)
target_link_libraries(mtcnn ncnn ${OpenCV_LIBS})
