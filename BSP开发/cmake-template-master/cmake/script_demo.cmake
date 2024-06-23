#[[
Author: FarmerLi, 公众号: 很酷的程序员/RealCoolEngineer
Date: 2021-04-27
]]

# Option
option(TO_BE_COOL "Whether to a real cool engineer" ON)
message("Do you want to follow the author? ${TO_BE_COOL}")

# Set variable
set(AUTHOR_NAME Farmer)
set(AUTHOR "Farmer Li")
set(AUTHOR Farmer\ Li)

# Set list
set(SLOGAN_ARR To be)   # Saved as "To;be"
set(SLOGAN_ARR To;be)
set(SLOGAN_ARR "To;be")

set(NUM 30)   # Saved as string, but can compare with other number string
set(FLAG ON)  # Bool value
message("This is a cmake script demo writed by ${AUTHOR_NAME}")
message("This is a cmake script demo writed by ${AUTHOR}\n")

# Set cache variable
# set(<variable> <value>... CACHE <type> <docstring> [FORCE])
set(CACHE_VAR "Default cache value" CACHE STRING "A sample for cache variable")
# Lookup by $CACHE{<variable>}
message("Value of CACHE_VAR $CACHE{CACHE_VAR}\n")

# Set ENV variable
# set(ENV{<variable>} [<value>])
set(ENV{ENV_VAR} "$ENV{PATH}")
# Lookup by $ENV{<variable>}
message("Value of ENV_VAR: $ENV{ENV_VAR}\n")

# List operations
set(WECHAT_ID_ARR Real Cool Eengineer)
list(APPEND SLOGAN_ARR a)                # APPEND sub command
list(APPEND SLOGAN_ARR ${WECHAT_ID_ARR}) # Can append another list
list(LENGTH SLOGAN_ARR SLOGAN_ARR_LEN)   # LENGTH sub command
# Convert list "To;be;a;Real;Cool;Engineer"
# To string "To be a Real Cool Engineer"
list(JOIN SLOGAN_ARR " " SLOGEN_STR)

message("Slogen list length: ${SLOGAN_ARR_LEN}")
message("Slogen list: ${SLOGAN_ARR}")
message("Slogen list to string: ${SLOGEN_STR}\n")

message("Begin of If statements...")
set(EMPTY_STR "")
if (NOT EMPTY_STR AND FLAG AND NUM LESS 50 AND NOT NOT_DEFINE_VAR)
    message("The first if branch...")
elseif (EMPTY_STR)
    message("EMPTY_STR is not empty")
else ()
    message("All other case")
endif()
message("End of If statements...\n")

message("For loop demo: ")
foreach(arg
    NoSpace
    Escaped\ Space
    This;Divides;Into;Five;Arguments
    Escaped\;Semicolon
    )
  message("${arg}")
endforeach()
message("\n")

# Run git command
execute_process(COMMAND bash "-c" "git rev-parse --short HEAD" OUTPUT_VARIABLE COMMIT_ID)
message("Current commit id: ${COMMIT_ID}\n")

# Include another script
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/hello.cmake")

# Another message mode
message(STATUS "This is a status message")
message(DEBUG "This is a debug message")
message(WARNING "This is a warning message")
message(SEND_ERROR "This message will send an error, but will go through")
message(FATAL_ERROR "This is one fatal error message, will abort current process")
message("This message will not be printed")
