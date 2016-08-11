#include "simplecompute.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	simpleCompute w;
	w.show();
	return a.exec();
}
