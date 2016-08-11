#include "imgpro.h"
#include <iostream>
using namespace vmath;


imgpro::imgpro(QGLWidget *parent)
	: QGLWidget(parent)
{
	ui.setupUi(this);
	startTimer(100);
}

imgpro::~imgpro()
{
	glUseProgram(0);
    glDeleteProgram(compute_prog);
    glDeleteProgram(render_prog);
    glDeleteTextures(1, &output_image);
    glDeleteVertexArrays(1, &render_vao);
}

void imgpro::initializeGL()
{
	if(glewInit())
	{
		std::cout<<"Unable to Init GLEW"<<std::endl;
		exit(EXIT_FAILURE);
	}
	ShaderInfo cmp_shaders[] ={
		{GL_COMPUTE_SHADER,	"compute.cmp"},
		{GL_NONE,						NULL}
	};
	compute_prog = LoadShaders(cmp_shaders);
	input_image = vglLoadTexture("C:/Vermilion-Book/trunk/Code/media/test3.dds", 0, NULL);
	
	glGenTextures(1,&intermediate_image);
	glBindTexture(GL_TEXTURE_2D,intermediate_image);
	glTexStorage2D(GL_TEXTURE_2D, 8, GL_RGBA32F, 1024, 1024);

	glGenTextures(1, &output_image);
    glBindTexture(GL_TEXTURE_2D, output_image);
    glTexStorage2D(GL_TEXTURE_2D, 8, GL_RGBA32F, 1024, 1024);

	ShaderInfo obj_shaders[] ={
		{GL_VERTEX_SHADER,			"obj.vert"},
		{GL_FRAGMENT_SHADER,		"obj.frag"},
		{GL_NONE,							NULL}
	};
	render_prog = LoadShaders(obj_shaders);
	glGenVertexArrays(1, &render_vao);
    glBindVertexArray(render_vao);
    glEnableVertexAttribArray(0);
    glGenBuffers(1, &render_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, render_vbo);
    static const float verts[] =
    {
        -1.0f, -1.0f, 0.5f, 1.0f,
         1.0f, -1.0f, 0.5f, 1.0f,
         1.0f,  1.0f, 0.5f, 1.0f,
        -1.0f,  1.0f, 0.5f, 1.0f,
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
}

void imgpro::paintGL()
{
	glUseProgram(compute_prog);
    glBindImageTexture(0, input_image, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F);
    glBindImageTexture(1, intermediate_image, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
    glDispatchCompute(1, 1024, 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    glBindImageTexture(0, intermediate_image, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F);
    glBindImageTexture(1, output_image, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
    glDispatchCompute(1, 1024, 1);

	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, output_image);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0,0.0,0.0,1.0);
    glUseProgram(render_prog);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void imgpro::resizeGL(int w,int h)
{
	if(0 == h)
		h = 1;
	glViewport(0,0,w,h);
	glLoadIdentity();
}

void imgpro::timerEvent(QTimerEvent*)
{
	updateGL();
}