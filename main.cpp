#include "SystemAddonsPopup.h"
#include <QtWidgets/QApplication>

#include <QtMultimedia>

#include <iostream>
using namespace std;

void debugMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	cout << msg.toStdString() << endl;
}
int main(int argc, char *argv[])
{
	qInstallMessageHandler(debugMessageOutput);
	
	QApplication app(argc, argv);

	SystemAddonsPopup* system_addons_popup = SystemAddonsPopup::getInstance();
	if (system_addons_popup == NULL)return 0;
	else {
		system_addons_popup->show();
		app.exec();
	}
	return 0;
}
