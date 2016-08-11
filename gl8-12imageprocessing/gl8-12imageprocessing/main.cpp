#include "imgpro.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	imgpro w;
	w.show();
	return a.exec();
}
