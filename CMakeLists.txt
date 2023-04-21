cmake_minimum_required( VERSION 3.16 )

project( uganet VERSION 0.0.1 )

option( CMAKE_EXPORT_COMPILE_COMMANDS ON )

add_compile_options( -Wall -Wextra -pedantic -O0 )
#add_compile_options( -Wall -Wextra -pedantic -Werror -O0 )

add_library( uganetlib STATIC   src/uga_err.c
                                src/uga_fs.c
                                src/uga_net.c
                                src/uga_read.c
                                src/uga_write.c
)
target_include_directories( uganetlib PUBLIC include )

add_executable( ugatest main.c )

target_link_libraries( ugatest uganetlib )

target_include_directories( ugatest PUBLIC include )
