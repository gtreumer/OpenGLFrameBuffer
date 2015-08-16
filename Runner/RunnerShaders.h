#ifndef RUNNER_SHADERS_H__
#define RUNNER_SHADERS_H__

#include <string>

namespace
{
	std::string runnerVertShader =
		"precision mediump float; \n"
		"attribute vec4 a_vertex; \n"
		"attribute vec2 a_texture; \n"
		"varying vec2 tex_coords; \n"
		"void main (void) \n"
		"{ \n"
			"tex_coords = a_texture; \n"
			"gl_Position = a_vertex; \n"
		"} \n";

	std::string runnerFragShader = 
		"precision mediump float; \n"
		"uniform sampler2D tex; \n"
		"varying vec2 tex_coords; \n"
		"void main (void)  \n"
		"{ \n"
			"vec4 color = texture2D(tex, tex_coords.st); \n"
			"gl_FragColor = color; \n"
		"} \n";
}

#endif