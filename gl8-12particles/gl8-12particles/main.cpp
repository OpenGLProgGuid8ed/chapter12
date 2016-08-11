#include "particles.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	particles w;
	w.show();
	return a.exec();
}
