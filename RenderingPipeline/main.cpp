#include "RenderingPipeline.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RenderingPipeline w;

	w.setMaximumSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
	w.setMinimumSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
	w.backgroundRole();

	w.show();
	return a.exec();
}
