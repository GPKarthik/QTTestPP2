#include "customitem.h"
#include <QPainter>
#include <QPalette>
#include <QPaintEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
//#include <QPaintEngine>

int nItemWidth = 0;

int nItemHeight = 0;

//extern int getImage(const QString& imagePath, CustomItem* item);

Qt::TransformationMode CustomItem::m_transformationMode =  Qt::FastTransformation;

bool CustomItem::bItemUpdate = true;

CustomItem::CustomItem(const QString& strImagePath, QGraphicsItem* parent)
			: QGraphicsItem(parent)
{
	m_strPath = strImagePath;

	m_pixmap = 0;

	m_bHovered = false;

	m_imageRect = QRect(m_nMargin / 2 , m_nMargin / 2, nItemWidth - m_nMargin, nItemHeight - m_nMargin);

	setFlags(ItemIsSelectable | ItemClipsToShape | ItemIsPanel);

	//m_pImage = new QFutureWatcher<int>;
}

CustomItem::~CustomItem()
{
	/*if (m_pImage->isRunning())
	{
	m_pImage->cancel();
	}

	m_pImage->waitForFinished();

	free(m_pImage);*/
}


void CustomItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->save();

	if (option->state & QStyle::State_MouseOver)
	{
		painter->fillRect(boundingRect(), option->palette.dark());
	}
	else if (option->state & QStyle::State_Selected)
	{
		painter->fillRect(boundingRect(), option->palette.highlight());
	}
	else
	{
		painter->fillRect(boundingRect(), option->palette.base()/*QColor(255, 255, 255)*/);
	}

	//HDC hDC = painter->paintEngine()->getDC();

	//painter->paintEngine()->releaseDC(hDC);

	if (false == pixmap().isNull())
	{
		QPixmap modifiedImage = pixmap();

		if (Qt::FastTransformation == m_transformationMode)
		{
			modifiedImage = modifiedImage.scaled(m_imageRect.width(), m_imageRect.height(), Qt::KeepAspectRatio, m_transformationMode);
		}
		else if ((pixmap().width() < m_imageRect.width())
							&&
				 (pixmap().height() < m_imageRect.height()))
		{
			modifiedImage = modifiedImage.scaled(m_imageRect.width(), m_imageRect.height(), Qt::KeepAspectRatio, Qt::FastTransformation);

			//if (false == bItemUpdate)
			//{
			//	painter->restore();

			//	return;
			//}

			//if (m_pImage->isRunning())
			//{
			//	m_pImage->cancel();
			//}

			//m_pImage->waitForFinished();

			//m_pImage->setFuture(QtConcurrent::run(getImage, m_strPath, this));	
		}
		else
		{
			modifiedImage = modifiedImage.scaled(m_imageRect.width(), m_imageRect.height(), Qt::KeepAspectRatio, m_transformationMode);
		}

		painter->drawPixmap(m_imageRect.x() + (m_imageRect.width() - modifiedImage.width()) / 2, 
							m_imageRect.y() + (m_imageRect.height() - modifiedImage.height()) / 2, 
							modifiedImage.width(), 
							modifiedImage.height(), 
							modifiedImage);

	}
	else
	{

		/*if (false == bItemUpdate)
		{
			painter->restore();

			return;
		}

		if (m_pImage->isRunning())
		{
			m_pImage->cancel();
		}

		m_pImage->waitForFinished();

		m_pImage->setFuture(QtConcurrent::run(getImage, m_strPath, this));*/
	}

	painter->restore();
}

//int getImage(const QString& imagePath, CustomItem* item)
//{
//	QImageReader imageReader(imagePath);
//	QSize size;
//	int image_width = item->getImageRect().width();
//	int image_height = item->getImageRect().height();
//
//	if (imageReader.supportsOption(QImageIOHandler::Size))
//	{
//		size = imageReader.size();
//		image_width = size.width();
//		image_height = size.height();
//	}
//
//	double ratio = (double)image_width / (double)image_height;
//
//	if (image_width <= image_height)
//	{
//		image_height = item->getImageRect().height();
//		image_width = ratio * image_height;
//	}
//	else
//	{
//		image_width = item->getImageRect().width();
//		image_height = image_width / ratio;
//	}
//
//	imageReader.setScaledSize(QSize(image_width, image_height));
//	QImage image = imageReader.read();
//
//	item->setPixmap(QPixmap::fromImage(image));
//
//	return 1;
//}

//void CustomItem::setItemSize()
//{
//	//this->setPixmap(QPixmap::fromImage(m_pImage->result()));
//}

void CustomItem::setTransformationMode(Qt::TransformationMode mode)
{
	m_transformationMode = mode;
}

QRectF CustomItem::boundingRect() const
{
	return QRectF(0, 0, nItemWidth, nItemHeight);
}

void CustomItem::setPos(qreal x, qreal y)
{
	m_imageRect.setRect(m_nMargin / 2 , m_nMargin / 2, nItemWidth - m_nMargin, nItemHeight - m_nMargin);

	prepareGeometryChange();
	
	QGraphicsItem::setPos(x, y);
}

void CustomItem::setPixmap(const QPixmap & pixmap)
{
	//lock.lockForWrite();

	prepareGeometryChange();

	m_pixmap = pixmap;

	//lock.unlock();

	//scene()->update(mapToScene(boundingRect()).boundingRect());
	//prepareGeometryChange();
	update();
}

QPixmap CustomItem::pixmap() const
{
	return m_pixmap;
}

QRect CustomItem::getImageRect()
{
	return m_imageRect;
}

const QString& CustomItem::imagePath()
{
	return m_strPath; 
}

const int& CustomItem::getItemMargin()
{
	return m_nMargin;
}

void CustomItem::hoverEnterEvent (QGraphicsSceneHoverEvent * event)
{
	m_bHovered = true;

	QGraphicsItem::hoverEnterEvent(event);
}

void CustomItem::hoverLeaveEvent (QGraphicsSceneHoverEvent * event)
{
	m_bHovered = false;

	QGraphicsItem::hoverLeaveEvent(event);
}