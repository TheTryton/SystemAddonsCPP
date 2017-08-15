#include "SystemAddonsPopup.h"
#include "MusicVisualizer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MusicVisualizer* music_visualizer = new MusicVisualizer();
	music_visualizer->show();

	/*SystemAddonsPopup* system_addons_popup = SystemAddonsPopup::getInstance();
	if (system_addons_popup == NULL)return 0;
	else {
		system_addons_popup->show();
		app.exec();
	}
	*/
	app.exec();
	return 0;
}
