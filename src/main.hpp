#pragma once

#include <print>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include <cstdint>
#include <atomic>
#include <cmath>

#include <raylib.h>

#define CL_HPP_TARGET_OPENCL_VERSION 300 // Specifies target OpenCL version
#include <CL/opencl.hpp> // Core OpenCL C header
