#include "customgraphicsview.h"
#include <QtConcurrentMap>
#include <QResizeEvent>
#include <QLabel>
#include <QPainter>
#include <QScrollBar>
#include <QPushButton>
#include <QImageReader>
#include <QImage>
#include <QGraphicsWidget>
#include <QPaintEngine>

QPixmap readEmf(CustomItem* item)
{
	HBITMAP hBitmap = NULL;
	
	HDC hBitmapDC = NULL;

	HBITMAP hBmOldCtrl = NULL;

	//HDC hDC = GetDC(item->window()->winId());

	QList<QGraphicsView*> itemView = item->scene()->views();

	//QPainter painter(itemView[0]->viewport());

	//painter.paintEngine()->setActive(true);

	HDC hDC = GetDC(NULL); //painter.paintEngine()->getDC();

	//hDC =/* painter.paintEngine()->getDC();*/GetDC(itemView[0]->viewport()->winId());
	
	//painter.save();

	//Create new bitmap. 
	hBitmap = CreateCompatibleBitmap(hDC,
									 item->getImageRect().width(),
									 item->getImageRect().height());
	
	//Create compatible DC for new bitmap.
	hBitmapDC = CreateCompatibleDC(hDC);	
	
	//Select bitmap in DC.
	hBmOldCtrl = (HBITMAP)SelectObject(hBitmapDC, hBitmap);	

	HENHMETAFILE hMetaFileHandle = NULL;

	QString strEmfFile = item->imagePath();
	
	hMetaFileHandle = GetEnhMetaFile(strEmfFile.toStdWString().c_str());

	LPENHMETAHEADER pEnhMetaHeader = NULL;

	UINT nBuffSize = GetEnhMetaFileHeader(hMetaFileHandle,
										  0,
										  NULL);

	pEnhMetaHeader = (LPENHMETAHEADER)malloc(nBuffSize);
	
	GetEnhMetaFileHeader(hMetaFileHandle,
						 nBuffSize,
						 pEnhMetaHeader);

	// printable region in pixel
	INT nScreenWidth = GetDeviceCaps(hBitmapDC, HORZRES);
	INT nScreenHeight = GetDeviceCaps(hBitmapDC, VERTRES);

	// printable region in MM
	INT nScreenWidthMM = GetDeviceCaps(hBitmapDC, HORZSIZE) * 100;
	INT nScreenHeightMM = GetDeviceCaps(hBitmapDC, VERTSIZE) * 100;

	// picture size in MM
	INT nPageWidthMM = pEnhMetaHeader->rclFrame.right - pEnhMetaHeader->rclFrame.left;
	INT nPageHeightMM = pEnhMetaHeader->rclFrame.bottom - pEnhMetaHeader->rclFrame.top;

	// convert to pixels for current device
	// EMF size in pixels
	INT nPageWidth = (nPageWidthMM * nScreenWidth)/nScreenWidthMM;
	INT nPageHeight = (nPageHeightMM * nScreenHeight)/nScreenHeightMM;

	DOUBLE dbScaleFactor = 0;

	INT nNewPageWidth = 0;

	INT nNewPageHeight = 0;

	//Identify which one is bigger in the page size.
	if (nPageWidth > nPageHeight)
	{	
		//Compute Height.
		nNewPageHeight = (nPageHeight * item->getImageRect().width()) / nPageWidth;

		//Compute Width.
		nNewPageWidth = item->getImageRect().width();
	}
	else
	{
		//Compute Width.
		nNewPageWidth = (nPageWidth * item->getImageRect().height()) / nPageHeight;

		//Compute Height.
		nNewPageHeight = item->getImageRect().height();
	}

	//width = (width * nPageWidth) / nScreenWidth;

	//height = (height * nPageHeight) / nScreenHeight;

	//RECT rcCtrl = {option.rect.x(), option.rect.y(), option.rect.x() + width, option.rect.y() + height};	

	RECT rcCtrl = {0, 0, nNewPageWidth, nNewPageHeight};
	
	if (FALSE == PlayEnhMetaFile(hBitmapDC,
								 hMetaFileHandle,
								 &rcCtrl))
	{
		//break;
	}

	SelectObject(hBitmapDC, hBmOldCtrl);

	ReleaseDC(NULL, hDC);

	//ReleaseDC(itemView[0]->viewport()->winId(), hDC);

	//painter.paintEngine()->releaseDC(hDC);

	//painter.restore();

	QPixmap image = QPixmap::fromWinHBITMAP(hBitmap, QPixmap::PremultipliedAlpha);

	//ImageGallery* app = dynamic_cast<ImageGallery *>(parent());

	//app->setItemImageSize(index.row(), width, height);

	//Delete object.
	if (NULL != hBitmap)
	{
		DeleteObject(hBitmap);
	
		hBitmap = NULL;
	}
	
	//Delete bitmap DC.
	if (NULL != hBitmapDC)
	{
		DeleteDC(hBitmapDC);
	
		hBitmapDC = NULL;
	}
	
	if (NULL != hMetaFileHandle)
	{
		DeleteEnhMetaFile(hMetaFileHandle);
	}

	return image;
}

QPixmap getImage(CustomItem* item)
{
	QImageReader imageReader(item->imagePath());
	QSize size;
	int image_width = item->getImageRect().width();
	int image_height = item->getImageRect().height();

	if (imageReader.supportsOption(QImageIOHandler::Size))
	{
		size = imageReader.size();
		image_width = size.width();
		image_height = size.height();
	}

	double ratio = (double)image_width / (double)image_height;

	if (image_width <= image_height)
	{
		image_height = item->getImageRect().height();
		image_width = ratio * image_height;
	}
	else
	{
		image_width = item->getImageRect().width();
		image_height = image_width / ratio;
	}

	imageReader.setScaledSize(QSize(image_width, image_height));
	QImage image = imageReader.read();

	//item->setPixmap(QPixmap::fromImage(image));

	return QPixmap::fromImage(image);
}


CustomGraphicsView::CustomGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
	//Set scene.
	this->setScene(&m_graphicsScene);

	//Set width to default View width
	m_nWidth = this->geometry().width();

	//Set width to default View height
	m_nHeight = this->geometry().height();

	//View X-offset
	m_nOffsetX = 20;

	//View Y-offset
	m_nOffsetY = 20;

	m_nRow = 0;

	m_nColoumn = 0;

	m_nMaxColumn = 0;

	eFile = eImage;

	m_itemTransformation = Qt::SmoothTransformation;

	//Set Rendering hint flags of GraphicsView.
	this->setRenderHints (QPainter::TextAntialiasing);

	this->setDragMode(QGraphicsView::RubberBandDrag);

	//Set Cache mode flag.
	//this->setCacheMode (QGraphicsView::NoCache);

	m_pImage = new QFutureWatcher<QPixmap>(this);

	timer = new QTimer(this);

	connect(m_pImage, SIGNAL(resultReadyAt(int)), SLOT(updateItemImage(int)));

	connect(timer, SIGNAL(timeout()), this, SLOT(updateItem()));

	timer->setSingleShot(true);

	//Set Viewport Update mode of the view.
	this->setViewportUpdateMode (QGraphicsView::SmartViewportUpdate);

	connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onSliderPressed(int)));
	//connect(this->verticalScrollBar(), SIGNAL(sliderReleased()), this, SLOT(onSliderReleased()));
}

CustomGraphicsView::~CustomGraphicsView()
{
	m_ItemsNotLoaded.clear();

	if (m_pImage->isRunning())
	{
		m_pImage->cancel();
	}

	m_pImage->waitForFinished();

	delete m_pImage;
	m_pImage = NULL;
}

//Clears view contents.
void CustomGraphicsView::clearView()
{
	//Clear graphics scene
	m_graphicsScene.clear();

	m_ItemsNotLoaded.clear();

	//Reset row & column of view.
	m_nRow = 0;

	m_nColoumn = 0;

	m_nMaxColumn = 0;
}

//Shows image on view.
void CustomGraphicsView::showImageOnView(QStringList strEmfFiles)
{
	//Calculate maximum column to be displayed in a view.
	m_nMaxColumn = (m_nWidth - (m_nOffsetX + (m_nOffsetX / 2))) / (nItemWidth + 10);

	//Loop to add items to the scene.
	for (INT iEmf= 0; iEmf < strEmfFiles.count(); iEmf++)
	{
		CustomItem* pImageLabel = new CustomItem(strEmfFiles[iEmf]);

		pImageLabel->setPos(m_nOffsetX + (m_nColoumn * (nItemWidth + 10)), m_nOffsetY + (m_nRow * (nItemHeight + 10)));

		pImageLabel->setAcceptHoverEvents(true);

		m_graphicsScene.addItem(pImageLabel);

		if (m_nColoumn < (m_nMaxColumn - 1))
		{
			if ((0 == m_nRow)
					&& 
				(0 == m_nColoumn))
			{
				m_sceneRect.setX(0);
				m_sceneRect.setY(0);
				m_sceneRect.setWidth(m_nOffsetX + (m_nOffsetX / 2) + nItemWidth);
				m_sceneRect.setHeight(m_nOffsetY + (m_nOffsetY / 2) + nItemHeight);
			}
			else if (0 == m_nRow)
			{
				m_sceneRect.setWidth(m_sceneRect.width() + nItemWidth + 10);

			}
			else if (0 == m_nColoumn)
			{
				m_sceneRect.setHeight(m_sceneRect.height() + nItemHeight + 10);
			}
			
			m_graphicsScene.setSceneRect(m_sceneRect);

			m_nColoumn++;

		}
		else
		{
			if (0 == m_nRow)
			{
				m_sceneRect.setWidth(m_nWidth);

				m_graphicsScene.setSceneRect(m_sceneRect);
			}

			m_nRow++;

			m_nColoumn = 0;
		}
	}

	if (m_sceneRect.height() < m_nHeight)
	{
		m_sceneRect.setHeight(m_nHeight);

		m_graphicsScene.setSceneRect(m_sceneRect);
	}

	updateView();
}

void CustomGraphicsView::resizeEvent (QResizeEvent* event)
{
	m_nWidth = event->size().width();

	m_nHeight = event->size().height();

	updateView();

	QGraphicsView::resizeEvent(event);
}

void CustomGraphicsView::updateView()
{
	m_nRow = 0;

	m_nColoumn = 0;

	QList<QGraphicsItem *> items = this->items();

	m_nMaxColumn = (m_nWidth - (m_nOffsetX + (m_nOffsetX / 2))) / (nItemWidth + 10);

	if (0 == m_nMaxColumn)
	{
		m_nMaxColumn = 1;
	}

	m_sceneRect.setWidth(m_nWidth);

	m_sceneRect.setHeight(m_nOffsetY + (m_nOffsetY / 2) + (ceil(float(items.count()) / m_nMaxColumn) * (nItemHeight + 10)));

	if (m_sceneRect.height() < m_nHeight)
	{
		m_sceneRect.setHeight(m_nHeight);
	}

	m_graphicsScene.setSceneRect(m_sceneRect);

	for (INT index = items.count() - 1; index >= 0; index--)
	{
		CustomItem* item = dynamic_cast<CustomItem*> (items[index]);

		item->setPos(m_nOffsetX + (m_nColoumn * (nItemWidth + 10)), m_nOffsetY + (m_nRow * (nItemHeight + 10)));

		if (m_nColoumn < (m_nMaxColumn - 1))
		{
			m_nColoumn++;
		}
		else
		{
			m_nRow++;

			m_nColoumn = 0;
		}
	}

	updateItem();

	//if (Qt::FastTransformation ==  m_itemTransformation)
	//{
	//	return;
	//}

	//if (m_pImage->isRunning())
	//{
	//	m_pImage->cancel();
	//}

	//m_visibleItems = this->items(viewport()->rect());

	//m_pImage->waitForFinished();

	//m_pImage->setFuture(QtConcurrent::run(getImage, m_visibleItems));
}

//void CustomGraphicsView::paintEvent(QPaintEvent* e)
//{
//
//	QPainter painter(this->viewport());
//
//	m_nRow = 0;
//
//	m_nColoumn = 0;
//
//	m_nMaxColumn = (m_nWidth - (m_nOffsetX + (m_nOffsetX / 2))) / (nItemWidth + 10);
//
//	//painter.setPen(Qt::blue);
//	//painter.setFont(QFont("Arial", 30));
//	//painter.drawText(e->rect(), Qt::AlignCenter, "Qt");
//
//	painter.save();
//
//	painter.fillRect(e->rect(), QBrush(QColor(108, 108, 108, 255), Qt::SolidPattern));
//
//	int yPos = this->verticalScrollBar()->value();
//
//	QRect viewRect = e->rect().translated(0, yPos);
//
//	//painter.setBackground(QBrush(QColor(108, 108, 108, 255), Qt::SolidPattern));
//
//	QList<QGraphicsItem *> items = this->items();
//
//	for (INT index = items.count() - 1; index >= 0; index--)
//	{
//		QGraphicsProxyWidget* item = dynamic_cast<QGraphicsProxyWidget*> (items[index]);
//
//		QRect itemRect = (item->rect().toRect()).translated(item->pos().toPoint());
//
//		QRect rect = viewRect.intersected(itemRect);
//
//		if ( !rect.isNull() )
//		{
//			//QRectF itemRect = (item->rect());
//
//			itemRect.setX(m_nOffsetX + (m_nColoumn * (nItemWidth + 10)));
//
//			itemRect.setY(m_nOffsetY + (m_nRow * (nItemHeight + 10)));
//
//			//item->setPos(m_nOffsetX + (m_nColoumn * (nItemWidth + 10)), m_nOffsetY + (m_nRow * (nItemHeight + 10)));
//
//			painter.fillRect(itemRect, QColor(255, 0, 0, 255));
//
//			if (m_nColoumn < (m_nMaxColumn - 1))
//			{
//				m_nColoumn++;
//			}
//			else
//			{
//				m_nRow++;
//
//				m_nColoumn = 0;
//			}
//		}
//	}
//	/*QPalette pal = this->palette();
//
//	pal.setColor(QPalette::Base, QColor(108, 108, 108, 255));
//
//	painter.fillRect(e->rect(), pal.color(QPalette::Active, QPalette::Base));
//
//	painter.drawRect(25, 25, 100, 100);*/
//
//	painter.restore();
//}

void CustomGraphicsView::setTransformationMode(bool bSliderPressed)
{
	m_itemTransformation = Qt::SmoothTransformation;

	if (true == bSliderPressed)
	{
		m_itemTransformation = Qt::FastTransformation;
	}

	CustomItem::setTransformationMode(m_itemTransformation);
}

void CustomGraphicsView::setItemSize(int nItemSize)
{
	nItemWidth = nItemSize;

	nItemHeight = nItemSize;

	updateView();
}

void CustomGraphicsView::updateItem()
{
	if (Qt::FastTransformation == m_itemTransformation)
	{
		return;
	}

	if (m_pImage == NULL)
	{
		return;
	}

	if (m_pImage->isRunning())
	{
		m_pImage->cancel();
	}

	//painter.paintEngine()->setActive(true);

	//HDC hDC = painter.paintEngine()->getDC();

	QList<QGraphicsItem*> visibleItems = this->items(viewport()->rect());

	m_pImage->waitForFinished();

	m_ItemsNotLoaded.clear();

	int nItemLoadCount = 0;

	for (int index = 0; index < visibleItems.count(); index++)
	{
		CustomItem* item = dynamic_cast<CustomItem*> (visibleItems[index]);

		if ((true == item->pixmap().isNull())
						||
			((nItemWidth > (item->pixmap().width() + CustomItem::getItemMargin()))
						&&
			 (nItemHeight > (item->pixmap().height() + CustomItem::getItemMargin()))))
		{
			m_ItemsNotLoaded.push_front(item);
		}	
	}

	//m_visibleItems = this->items(viewport()->rect());

	if (eImage == eFile)
	{
		m_pImage->setFuture(QtConcurrent::mapped(m_ItemsNotLoaded, getImage));
	}
	else
	{
		m_pImage->setFuture(QtConcurrent::mapped(m_ItemsNotLoaded, readEmf));
	}

	//m_pImage->waitForFinished();

	//m_pImage->setFuture(QtConcurrent::run(getImage, m_visibleItems));
}

void CustomGraphicsView::onSliderPressed(int)
{
	//m_graphicsScene.update(m_sceneRect);

	if (m_pImage == NULL)
	{
		return;
	}

	if (m_pImage->isRunning())
	{
		m_pImage->cancel();
	}

	timer->start(1000);

	//if (QAbstractSlider::SliderMove	== action)
	//{
	//	CustomItem::bItemUpdate = false;
	//}
	//else
	//{
	//	CustomItem::bItemUpdate = true;
	//}

	//CustomItem::bItemUpdate = false;
}


void CustomGraphicsView::onSliderReleased()
{
	//m_graphicsScene.update(m_sceneRect);

	CustomItem::bItemUpdate = true;

	updateItem();
}

void CustomGraphicsView::updateItemImage(int index)
{
	QPixmap image = /*QPixmap::fromImage*/(m_pImage->resultAt(index));

	m_ItemsNotLoaded[index]->setPixmap(image);
}

//void CustomGraphicsView::wheelEvent(QWheelEvent *event)
//{
//	timer->start(1000);
//
//	if (m_pImage->isRunning())
//	{
//		m_pImage->cancel();
//	}
//
//	QGraphicsView::wheelEvent(event);
//
//	/*updateItem();*/
//	//QTimer *timer = new QTimer(this);
//}

void CustomGraphicsView::setFileType(EFileType eType)
{
	eFile = eType;
}