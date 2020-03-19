#include "Gravity.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	Gravity w;
	w.show();
	return a.exec();
}