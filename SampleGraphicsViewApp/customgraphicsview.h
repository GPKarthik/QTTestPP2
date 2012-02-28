#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QStringList>
#include <QFutureWatcher>
#include <QTimer>
#include "customitem.h"
#include <Windows.h>

enum EFileType
{
	eImage = 0,

	eEmf
};

class CustomGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	CustomGraphicsView(QWidget *parent);
	~CustomGraphicsView();

	void clearView();

	void showImageOnView(QStringList strEmfFiles);

	void setFileType(EFileType eType); 

	//void initialize();

protected:
	//void paintEvent(QPaintEvent* e);
	//void wheelEvent(QWheelEvent *event);

public slots:
	void updateView();

	void setTransformationMode(bool bSliderPressed = false);

	void setItemSize(int nItemSize);

	void onSliderPressed(int);

	void onSliderReleased();

	void updateItem();

	void updateItemImage(int index);

protected:
	virtual void resizeEvent (QResizeEvent* event);

private:
	QFutureWatcher<QPixmap> *m_pImage;

	QGraphicsScene m_graphicsScene;

	INT m_nWidth;

	INT m_nHeight;

	INT m_nRow;

	INT m_nColoumn;

	INT m_nMaxColumn;

	INT m_nOffsetX;

	INT m_nOffsetY;

	QRectF m_sceneRect;

	QVector<CustomItem*> m_ItemsNotLoaded;

	Qt::TransformationMode m_itemTransformation;

	QTimer *timer;

	EFileType eFile;
};

#endif // CUSTOMGRAPHICSVIEW_H
