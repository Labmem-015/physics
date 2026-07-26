function(copy_cl file)
	if(EXISTS ${PROJECT_SOURCE_DIR}/snippets/${file})
	    message("Copying ${PROJECT_SOURCE_DIR}/snippets/${file} to ${PROJECT_BINARY_DIR}/snippets")
	    file(COPY ${PROJECT_SOURCE_DIR}/snippets/${file} DESTINATION ${PROJECT_BINARY_DIR}/snippets)
	else()
	    message(WARN "File ${PROJECT_SOURCE_DIR}/snippets/${file} not found. Maybe this file didn't created yet, so reconfigure CMake project.")
	endif()
endfunction()


# Hello World printing
add_executable(opencl_hello_world opencl_hello_world.cpp)
target_precompile_headers(opencl_hello_world REUSE_FROM app)
target_link_libraries(opencl_hello_world OpenCL::OpenCL)
copy_cl(hello_world.cl)

