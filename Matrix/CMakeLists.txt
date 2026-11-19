add_executable(matrix
    Matrix.cpp
    Matrix.h
    TestMatrix.cpp
)

# TestMatrix reads read.csv from the current directory
configure_file(read.csv ${CMAKE_CURRENT_BINARY_DIR}/read.csv COPYONLY)
