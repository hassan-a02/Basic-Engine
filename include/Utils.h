#pragma once

#include <iostream>

#ifdef DEBUG
#define GL_CHECK(call) do { call; GLenum err = glGetError(); if (err != GL_NO_ERROR) { std::cerr << "GL Error at " << __FILE__ << ":" << __LINE__ << ": " << err; std::exit(EXIT_FAILURE); } } while(0)
#else
#define GL_CHECK(call) call
#endif