function(copy_cl file)
	if(EXISTS ${PROJECT_SOURCE_DIR}/snippets/${file})
	    message("Copying ${PROJECT_SOURCE_DIR}/snippets/${file} to ${PROJECT_BINARY_DIR}/snippets")
	    file(COPY ${PROJECT_SOURCE_DIR}/snippets/${file} DESTINATION ${PROJECT_BINARY_DIR}/snippets)
	else()
	    message(WARN "File ${PROJECT_SOURCE_DIR}/snippets/${file} not found. Maybe this file didn't created yet, so reconfigure CMake project.")
	endif()
endfunction()

include_directories(./)

# Hello World printing
add_executable(opencl_hello_world opencl_hello_world.cpp)
target_precompile_headers(opencl_hello_world REUSE_FROM app)
target_link_libraries(opencl_hello_world PRIVATE OpenCL::OpenCL) 
copy_cl(hello_world.cl)

# Mandelbrot set
add_executable(mandelbrot_set mandelbrot_set.cpp mandelbrot_set_render.cpp)
target_precompile_headers(mandelbrot_set REUSE_FROM app)
target_link_libraries(mandelbrot_set PRIVATE OpenCL::OpenCL raylib glfw)
copy_cl(mandelbrot_set.cl)

# Check fp64 support
add_executable(check_fp64_support check_fp64_support.cpp)
target_precompile_headers(check_fp64_support REUSE_FROM app)
target_link_libraries(check_fp64_support PRIVATE OpenCL::OpenCL raylib glfw)
