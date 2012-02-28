#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QReadWriteLock>

extern int nItemWidth;
extern int nItemHeight;

class CustomItem : public QGraphicsItem
{
	//Q_OBJECT

public:
	CustomItem(const QString& strImagePath, QGraphicsItem* parent = 0);
	~CustomItem();

	virtual QRectF boundingRect() const;

	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

	static void setTransformationMode(Qt::TransformationMode mode);

	void setPos(qreal x, qreal y);

	QPixmap pixmap() const;

	void setPixmap(const QPixmap& pixmap);

	QRect getImageRect();

	const QString& imagePath();

	static const int& CustomItem::getItemMargin();

	static bool bItemUpdate;

public slots:
	void setItem();

protected:
	//void paintEvent(QPaintEvent* e);

	void hoverEnterEvent (QGraphicsSceneHoverEvent * event);

	void hoverLeaveEvent (QGraphicsSceneHoverEvent * event);

private:
	//QFutureWatcher<int> *m_pImage;
	
	QPixmap m_pixmap;

	//QImage getImage(const QString& imagePath);

	static int const m_nMargin = 10;

	QRect m_imageRect;

	QString m_strPath;

	static Qt::TransformationMode m_transformationMode;

	QReadWriteLock lock;

	bool m_bHovered;
};

#endif // CUSTOMITEM_H
