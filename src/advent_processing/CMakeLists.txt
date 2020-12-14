set(HEADERS
day.h
day1.h
day2.h
# day3.h
# day4.h
# day5.h
# day6.h
)

set(SOURCES
day1.cpp
day2.cpp
# day3.cpp
# day4.cpp
# day5.cpp
# day6.cpp
)
set(ADVENT_OF_CODE_HEADERS ${HEADERS} PARENT_SCOPE)

# prepend the current directory to the sources
foreach(file ${SOURCES})
    set(SOURCES_WITH_DIR ${SOURCES_WITH_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${file})
endforeach(file)
set(ADVENT_OF_CODE_SOURCES ${SOURCES_WITH_DIR} PARENT_SCOPE)

foreach(file ${HEADERS})
    set(HEADERS_WITH_DIR ${HEADERS_WITH_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${file})
endforeach(file)
set(ADVENT_OF_CODE_HEADERS ${HEADERS_WITH_DIR} PARENT_SCOPE)

# Everything was initially just cpp, these are 
# leftover executables
# add_executable(day1 day1.cpp day1.h day.h)
# add_executable(day2 day2.cpp day2.h day.h)
# add_executable(day3 day3.cpp day3.h day.h)
# add_executable(day4 day4.cpp day4.h day.h)
# add_executable(day5 day5.cpp day5.h day.h)
# add_executable(day6 day6.cpp day6.h day.h)