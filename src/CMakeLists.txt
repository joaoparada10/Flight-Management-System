set(SOURCE_FILES
        Airline.cpp
        Airport.cpp
        FileReader.cpp
        FMSGraph.cpp
        Flight.cpp
        Menu.cpp
        main.cpp)

set(HEADER_FILES
        Airline.h
        Airport.h
        Flight.h
        FileReader.h
        FMSGraph.h
        Menu.h
        Graph.h)

add_executable(AEDProject2 ${SOURCE_FILES} ${HEADER_FILES})