#ifndef PARTICLES_H
#define PARTICLES_H

#include <QtWidgets/QWidget>
#include "ui_particles.h"
#include "LoadShaders.h"
#include "vbm.h"
#include "vmath.h"
#include <qgl.h>

class particles : public QGLWidget
{
	Q_OBJECT

public:
	particles(QGLWidget *parent = 0);
	~particles();
	void initializeGL();
	void paintGL();
	void resizeGL(int w,int h);
	void timerEvent(QTimerEvent *);

private:
	Ui::particlesClass ui;
	enum
	{
    PARTICLE_GROUP_SIZE     = 128,
    PARTICLE_GROUP_COUNT    = 8000,
    PARTICLE_COUNT          = (PARTICLE_GROUP_SIZE * PARTICLE_GROUP_COUNT),
    MAX_ATTRACTORS          = 64
	};
    GLuint  compute_prog;
    GLint   dt_location;

    // Posisition and velocity buffers
    union
    {
        struct
        {
            GLuint position_buffer;
            GLuint velocity_buffer;
        };
        GLuint buffers[2];
    };

    // TBOs
    union
    {
        struct
        {
            GLuint position_tbo;
            GLuint velocity_tbo;
        };
        GLuint tbos[2];
    };

    // Attractor UBO
    GLuint  attractor_buffer;

    // Program, vao and vbo to render a full screen quad
    GLuint  render_prog;
    GLuint  render_vao;
    GLuint  render_vbo;

    // Mass of the attractors
    float attractor_masses[MAX_ATTRACTORS];

    float aspect_ratio;
};

#endif // PARTICLES_H
