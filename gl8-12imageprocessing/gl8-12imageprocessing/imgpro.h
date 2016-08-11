#ifndef IMGPRO_H
#define IMGPRO_H

#include <QtWidgets/QWidget>
#include "ui_imgpro.h"
#include "LoadShaders.h"
#include "vmath.h"
#include "vbm.h"
#include "vermilion.h"
#include <qgl.h>
class imgpro : public QGLWidget
{
	Q_OBJECT

public:
	imgpro(QGLWidget *parent = 0);
	~imgpro();
	void initializeGL();
	void paintGL();
	void resizeGL(int w,int h);
	void timerEvent(QTimerEvent*);
private:
	Ui::imgproClass ui;
	// Member variables
    GLuint  compute_prog;
    GLuint  compute_shader;

    // Texture to process
    GLuint  input_image;

    // Texture for compute shader to write into
    GLuint  intermediate_image;
    GLuint  output_image;

    // Program, vao and vbo to render a full screen quad
    GLuint  render_prog;
    GLuint  render_vao;
    GLuint  render_vbo;
};

#endif // IMGPRO_H
