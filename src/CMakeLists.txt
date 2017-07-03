# driver source files
SET(sources robohead.cpp mechanical.cpp visual_analysis.cpp face.cpp)

# application header files
SET(headers robohead.h mechanical.h visual_analysis.h face.h)

# locate the necessary dependencies
FIND_PACKAGE(dynamixel_pan_tilt REQUIRED)
ADD_DEFINITIONS(-D_HAVE_XSD)
FIND_PACKAGE(OpenCV REQUIRED)

# add the necessary include directories
INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(${dynamixel_pan_tilt_INCLUDE_DIR})

# create the shared library
ADD_LIBRARY(robohead SHARED ${sources})

# link necessary libraries
TARGET_LINK_LIBRARIES(robohead ${dynamixel_pan_tilt_LIBRARY})
TARGET_LINK_LIBRARIES(robohead ${OpenCV_LIBS})

INSTALL(TARGETS robohead
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib/iridrivers
        ARCHIVE DESTINATION lib/iridrivers)
INSTALL(FILES ${headers} DESTINATION include/iridrivers)
INSTALL(FILES ../Findrobohead.cmake DESTINATION ${CMAKE_ROOT}/Modules/)
ADD_SUBDIRECTORY(examples)
