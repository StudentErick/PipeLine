#include "RenderingPipeline.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RenderingPipeline w;

	w.setMaximumSize(QSize(800, 800));
	w.setMinimumSize(QSize(800, 800));
	w.backgroundRole();

	w.show();
	return a.exec();
}
