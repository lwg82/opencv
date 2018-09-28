# Define project name
project(traits_demo)


# Declare the executable target built from your sources
add_executable(${PROJECT_NAME} main.cpp)

# Link your application with OpenCV libraries
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
