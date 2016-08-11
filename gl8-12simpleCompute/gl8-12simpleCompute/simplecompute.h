#ifndef SIMPLECOMPUTE_H
#define SIMPLECOMPUTE_H

#include <QtWidgets/QWidget>
#include "ui_simplecompute.h"
#include "LoadShaders.h"
#include "vmath.h"
#include <qgl.h>

class simpleCompute : public QGLWidget
{
	Q_OBJECT

public:
	simpleCompute(QGLWidget *parent = 0);
	~simpleCompute();
	void initializeGL();
	void paintGL();
	void resizeGL(int w,int h);
	
private:
	Ui::simpleComputeClass ui;
	// Member variables
    GLuint  compute_prog;
    GLuint  compute_shader;

    // Texture for compute shader to write into
    GLuint  output_image;

    // Program, vao and vbo to render a full screen quad
    GLuint  render_prog;
    GLuint  render_vao;
    GLuint  render_vbo;
};

#endif // SIMPLECOMPUTE_H
