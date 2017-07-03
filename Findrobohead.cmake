#edit the following line to add the librarie's header files
FIND_PATH(robohead_INCLUDE_DIR robohead.h /usr/include/iridrivers /usr/local/include/iridrivers)

FIND_LIBRARY(robohead_LIBRARY
    NAMES robohead
    PATHS /usr/lib /usr/local/lib /usr/local/lib/iridrivers) 

IF (robohead_INCLUDE_DIR AND robohead_LIBRARY)
   SET(robohead_FOUND TRUE)
ENDIF (robohead_INCLUDE_DIR AND robohead_LIBRARY)

IF (robohead_FOUND)
   IF (NOT robohead_FIND_QUIETLY)
      MESSAGE(STATUS "Found robohead: ${robohead_LIBRARY}")
   ENDIF (NOT robohead_FIND_QUIETLY)
ELSE (robohead_FOUND)
   IF (robohead_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find robohead")
   ENDIF (robohead_FIND_REQUIRED)
ENDIF (robohead_FOUND)

