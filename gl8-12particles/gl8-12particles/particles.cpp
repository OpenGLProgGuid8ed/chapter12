#include "particles.h"
#include <iostream>

using namespace vmath;

static inline float random_float()
{
    float res;
    unsigned int tmp;
    static unsigned int seed = 0xFFFF0C59;

    seed *= 16807;
    tmp = seed ^ (seed >> 4) ^ (seed << 15);
    *((unsigned int *) &res) = (tmp >> 9) | 0x3F800000;

    return (res - 1.0f);
}

static vec3 random_vector(float minmag = 0.0f, float maxmag = 1.0f)
{
    vec3 randomvec(random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f);
    randomvec = normalize(randomvec);
    randomvec *= (random_float() * (maxmag - minmag) + minmag);

    return randomvec;
}

particles::particles(QGLWidget *parent)
	: QGLWidget(parent)
{
	ui.setupUi(this);
	startTimer(100);
}

particles::~particles()
{
	glUseProgram(0);
    glDeleteProgram(compute_prog);
    glDeleteProgram(render_prog);
    glDeleteVertexArrays(1, &render_vao);
}

void particles::initializeGL()
{
	if(glewInit())
	{
		std::cout<<"Unable to Init GLEW"<<std::endl;
		exit(EXIT_FAILURE);
	}
	ShaderInfo cmp_shaders[] ={
		{GL_COMPUTE_SHADER,		"compute.cmp"},
		{GL_NONE,						NULL}
	};
	compute_prog = LoadShaders(cmp_shaders);
	glUseProgram(compute_prog);
	dt_location = glGetUniformLocation(compute_prog,"dt");

	glGenVertexArrays(1,&render_vao);
	glBindVertexArray(render_vao);
	glGenBuffers(2,buffers);
	glBindBuffer(GL_ARRAY_BUFFER,position_buffer);
	glBufferData(GL_ARRAY_BUFFER,PARTICLE_COUNT*sizeof(vec4),NULL,GL_DYNAMIC_COPY);

	vec4* positions = (vec4*) glMapBufferRange(GL_ARRAY_BUFFER,0,
																PARTICLE_COUNT*sizeof(vec4),
																GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	for(int i =0;i<PARTICLE_COUNT;i++)
		positions[i] = vec4(random_vector(-10.0f,10.0f),random_float());
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,NULL);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,velocity_buffer);
	glBufferData(GL_ARRAY_BUFFER,PARTICLE_COUNT*sizeof(vec4),NULL,GL_DYNAMIC_COPY);

	vec4* velocitys = (vec4*) glMapBufferRange(GL_ARRAY_BUFFER,0,
														PARTICLE_COUNT*sizeof(vec4),
														GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	for(int i=0;i<PARTICLE_COUNT;i++)
		velocitys[i] = vec4(random_vector(-0.2f, 0.2f), 0.0f);
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glGenTextures(2,tbos);
	for(int i=0;i<2;i++)
	{
		glBindTexture(GL_TEXTURE_BUFFER,tbos[i]);
		glTexBuffer(GL_TEXTURE_BUFFER,GL_RGBA32F,buffers[i]);
	}

	glGenBuffers(1, &attractor_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, attractor_buffer);
    glBufferData(GL_UNIFORM_BUFFER, 32 * sizeof(vmath::vec4), NULL, GL_STATIC_DRAW);
	for(int i=0;i<MAX_ATTRACTORS;i++)
		attractor_masses[i] = 0.5f + random_float() * 0.5f;
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, attractor_buffer);

	ShaderInfo obj_shaders[] = {
		{GL_VERTEX_SHADER,			"obj.vert"},
		{GL_FRAGMENT_SHADER,		"obj.frag"},
		{GL_NONE,							NULL}
	};
	render_prog = LoadShaders(obj_shaders);
}

void particles::paintGL()
{
	static const GLuint start_ticks = ::GetTickCount() - 100000;
    GLuint current_ticks = ::GetTickCount();
    static GLuint last_ticks = current_ticks;
    float t = ((start_ticks - current_ticks) & 0xFFFFF) / float(0xFFFFF);
    float delta_time = (float)(current_ticks - last_ticks) * 0.075f;

	vec4 * attractors = (vec4 *)glMapBufferRange(GL_UNIFORM_BUFFER,0,32 * sizeof(vec4),
                                                               GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	for (int i = 0; i < 32; i++)
        attractors[i] = vec4(sinf(t * (float)(i + 4) * 7.5f * 20.0f) * 50.0f,
                                    cosf(t * (float)(i + 7) * 3.9f * 20.0f) * 50.0f,
                                    sinf(t * (float)(i + 3) * 5.3f * 20.0f) * 
											cosf(t * (float)(i + 5) * 9.1f) * 100.0f,attractor_masses[i]);
	glUnmapBuffer(GL_UNIFORM_BUFFER);

	if (delta_time >= 2.0f)
    {
        delta_time = 2.0f;
    }

	glUseProgram(compute_prog);
    glBindImageTexture(0, velocity_tbo, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
    glBindImageTexture(1, position_tbo, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	glUniform1f(dt_location, delta_time);

	glDispatchCompute(PARTICLE_GROUP_COUNT, 1, 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	mat4 mvp = perspective(45.0f, aspect_ratio, 0.1f, 1000.0f) * translate(0.0f, 0.0f, -60.0f) *
							rotate(t * 1000.0f, vmath::vec3(0.0f, 1.0f, 0.0f));
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    glUseProgram(render_prog);
    glUniformMatrix4fv(0, 1, GL_FALSE, mvp);
    glBindVertexArray(render_vao);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
	
	glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);
    last_ticks = current_ticks;
}

void particles::resizeGL(int w,int h)
{
	if(0 == h)
		h = 1;
	aspect_ratio = float(h)/w;
	glViewport(0,0,w,h);
	glLoadIdentity();
}

void particles::timerEvent(QTimerEvent*)
{
	updateGL();
}