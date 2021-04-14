add_library(MathFunctions
			mysqrt.cxx
			${CMAKE_CURRENT_BINARY_DIR}/Table.h
			)

add_executable(MakeTable MakeTable.cxx)


add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
	COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
	DEPENDS MakeTable
	)

# state that anybody linking to us needs to include the current source dir
# to find MathFunctions.h, while we don't.
target_include_directories(MathFunctions
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
		  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
          )

# does this system provide the log and exp functions?
include(CheckSymbolExists)
set(CMAKE_REQUIRED_LIBRARIES "m")
check_symbol_exists(log "math.h" HAVE_LOG)
check_symbol_exists(exp "math.h" HAVE_EXP)

# install rules
install(TARGETS MathFunctions DESTINATION lib)
install(FILES MathFunctions.h DESTINATION include)
