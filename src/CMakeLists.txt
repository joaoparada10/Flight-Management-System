set(SOURCE_FILES
        Airline.cpp
        Airport.cpp
        FileReader.cpp
        Flight.cpp
        FMSGraph.cpp
        main.cpp)

set(HEADER_FILES
        Airline.h
        Airport.h
        FileReader.h
        Flight.h
        FMSGraph.h
        Graph.h)

add_executable(AEDProject2 ${SOURCE_FILES} ${HEADER_FILES})