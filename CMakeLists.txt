cmake_minimum_required(VERSION 3.5)

project(smo LANGUAGES C)


set(HEADERS
    include/core/smoinfo.h
    include/def/defs.h
    include/def/strutil.h
    include/io/input.h
    include/test/test.h
    include/util/datetime.h
    include/util/log.h
    include/util/thread.h)

set(SOURCES
    src/def/strutil.c
    src/io/input.c
    src/test/testlog.c
    src/test/teststrutil.c
    src/test/main_test.c
    src/util/datetime.c
    src/util/log.c
    src/util/thread.c
    src/main.c)


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC include)
