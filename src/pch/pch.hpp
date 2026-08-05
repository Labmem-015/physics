#pragma once

#include <atomic>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <print>
#include <sstream>
#include <stop_token>
#include <string>
#include <thread>
#include <vector>
#include <random>

#include <raylib.h>

#define CL_HPP_TARGET_OPENCL_VERSION 300 // Specifies target OpenCL version
#include <CL/opencl.hpp>                 // Core OpenCL C header

#include "utils.hpp"
