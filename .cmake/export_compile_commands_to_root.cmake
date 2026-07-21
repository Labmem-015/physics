cmake_minimum_required(VERSION 3.31 FATAL_ERROR)

function(can_generate_compile_commands result_var)
  if(CMAKE_GENERATOR MATCHES "Makefiles|Ninja")
    set(${result_var} TRUE PARENT_SCOPE)
  else()
    set(${result_var} FALSE PARENT_SCOPE)
  endif()
endfunction()

can_generate_compile_commands(exporting_compile_commands_supported)
cmake_print_variables(exporting_compile_commands_supported)

# This is for clangd support. You can comment those lines if you don't use clangd
# Check if the file exists
if(${exporting_compile_commands_supported})
    message(STATUS "Copying 'compile_commands.json' to project source dir")
    add_custom_target(run_after_generation ALL
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_SOURCE_DIR}/compile_commands.json
    )
endif()
