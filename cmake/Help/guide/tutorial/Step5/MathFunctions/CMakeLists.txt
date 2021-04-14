add_library(MathFunctions mysqrt.cxx)

include(CheckSymbolExists)
set(CMAKE_REQUIRED_LIBRARIES "m")
check_symbol_exists(log "math.h" HAVE_LOG)
check_symbol_exists(exp "math.h" HAVE_EXP)

if(HAVE_EXP AND HAVE_LOG)
	target_compile_definitions(MathFunctions
							 PRIVATE "HAVE_LOG" "HAVE_EXP")
endif()

# state that anybody linking to us needs to include the current source dir
# to find MathFunctions.h, while we don't.
target_include_directories(MathFunctions
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
		  PRIVATE ${CMAKE_BINARY_DIR}
          )

# install rules
install(TARGETS MathFunctions DESTINATION lib)
install(FILES MathFunctions.h DESTINATION include)
