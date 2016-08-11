#include "simplecompute.h"
#include <iostream>
using namespace vmath;

simpleCompute::simpleCompute(QGLWidget *parent)
	: QGLWidget(parent)
{
	ui.setupUi(this);
}

simpleCompute::~simpleCompute()
{

}

void simpleCompute::initializeGL()
{
	if(glewInit())
	{
		std::cout<<"Unable to Init GLEW"<<std::endl;
		exit(EXIT_FAILURE);
	}
	ShaderInfo cmp_shader[] = {
		{GL_COMPUTE_SHADER,	"compute.cmp"},
		{GL_NONE,						NULL}
	};
	compute_prog = LoadShaders(cmp_shader);
	glGenTextures(1, &output_image);
    glBindTexture(GL_TEXTURE_2D, output_image);
    glTexStorage2D(GL_TEXTURE_2D, 8, GL_RGBA32F, 256, 256);

	ShaderInfo obj_shaders[] ={
		{GL_VERTEX_SHADER,			"obj.vert"},
		{GL_FRAGMENT_SHADER,		"obj.frag"},
		{GL_NONE,							NULL}
	};
	render_prog = LoadShaders(obj_shaders);
	// This is the VAO containing the data to draw the quad (including its associated VBO)
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

void simpleCompute::paintGL()
{
	 // Activate the compute program and bind the output texture image
    glUseProgram(compute_prog);
    glBindImageTexture(0, output_image, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
    glDispatchCompute(8, 16, 1);

    // Now bind the texture for rendering _from_
    glBindTexture(GL_TEXTURE_2D, output_image);

    // Clear, select the rendering program and draw a full screen quad
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(render_prog);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void simpleCompute::resizeGL(int w,int h)
{
	if(0 == h)
		h = 1;
	glViewport(0,0,w,h);
	glLoadIdentity();
}

