cmake_minimum_required(VERSION 3.5)

project(smo LANGUAGES C)


set(HEADERS
    include/core/smoinfo.h
    include/core/smorhs.h
    include/core/solve.h
    include/def/defs.h
    include/def/strutil.h
    include/io/input.h
    include/io/output.h
    include/math/mathdef.h
    include/math/rk.h
    include/math/rk_three_eighth.h
    include/test/test.h
    include/util/datetime.h
    include/util/log.h
    include/util/thread.h)

set(SOURCES
    src/core/smorhs.c
    src/core/solve.c
    src/def/strutil.c
    src/io/input.c
    src/io/output.c
    src/math/mathdef.c
    src/math/rk.c
    src/math/rk_three_eighth.c
    src/test/main_test.c
    src/test/testio.c
    src/test/testlog.c
    src/test/testrk.c
    src/test/teststrutil.c
    src/util/datetime.c
    src/util/log.c
    src/util/thread.c
    src/main.c)


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC include)
