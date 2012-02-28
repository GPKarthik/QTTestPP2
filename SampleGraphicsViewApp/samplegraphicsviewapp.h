#ifndef SAMPLEGRAPHICSVIEWAPP_H
#define SAMPLEGRAPHICSVIEWAPP_H

#include <QtGui/QMainWindow>
#include "ui_samplegraphicsviewapp.h"
#include <QGraphicsScene>

class SampleGraphicsViewApp : public QMainWindow
{
	Q_OBJECT

public:
	SampleGraphicsViewApp(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SampleGraphicsViewApp();

public slots:
	void openDirectory();

	void zoom(int scalePercentage);

	void onSliderPressed();

	void onSliderReleased();

	void setImageFileFilter(bool);

	void setEmfFileFilter(bool);

private:
	Ui::SampleGraphicsViewAppClass ui;

	QGraphicsScene m_graphicsScene;

	QStringList imageFiles;

	int m_nScaleFactor;

	int m_nScaleLevel;

	bool m_bSliderPressed;

	QStringList nameFilters;

	EFileType m_eFile;
};

#endif // SAMPLEGRAPHICSVIEWAPP_H
