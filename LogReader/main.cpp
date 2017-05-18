#include <QtWidgets\qapplication.h>
#include "CustomWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CustomWindow w;
	w.Init();
	w.show();
	return a.exec();
}
