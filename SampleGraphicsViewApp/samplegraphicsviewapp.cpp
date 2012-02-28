#include "samplegraphicsviewapp.h"
#include <QFileDialog>

SampleGraphicsViewApp::SampleGraphicsViewApp(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	m_bSliderPressed = false;

	m_nScaleLevel = 0;

	m_nScaleFactor = ui.horizontalSlider->value();

	m_eFile = eImage;

	//Call OpenDirectory() on selecting File/Open in Menu bar.
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openDirectory()));
	connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(zoom(int)), Qt::DirectConnection);
	connect(ui.horizontalSlider, SIGNAL(sliderPressed()), this, SLOT(onSliderPressed()));
	connect(ui.horizontalSlider, SIGNAL(sliderReleased()), this, SLOT(onSliderReleased()));
	connect(ui.emfButton, SIGNAL(clicked(bool)), this, SLOT(setEmfFileFilter(bool)));
	connect(ui.imageButton, SIGNAL(clicked(bool)), this, SLOT(setImageFileFilter(bool)));
}

SampleGraphicsViewApp::~SampleGraphicsViewApp()
{

}

void SampleGraphicsViewApp::openDirectory()
{
	//Fetch selected directory path.
	QString dirPath = QFileDialog::getExistingDirectory(
											this,
											tr("Select Image Directory"),
											QDir::currentPath(),
											QFileDialog::ShowDirsOnly |
											QFileDialog::DontResolveSymlinks);

	if (!dirPath.isEmpty())
	{
		//Create QDir instance to access selected directory.
		QDir dir(dirPath);

		/*QStringList nameFilters;*/

		//Filter to fetch only images.
		//nameFilters << "*.jpg" << "*.png" << "*.bmp";

		//nameFilters << "*.emf";

		//Fetch all images from folder.
		imageFiles = dir.entryList(nameFilters, QDir::Files|QDir::Readable);

		//Clear existing view.
		ui.graphicsView->clearView();

		ui.graphicsView->setFileType(m_eFile);

		//Set image width and height as per the current zoom value.
		nItemWidth = m_nScaleFactor;

		nItemHeight = m_nScaleFactor;

		for (int index = 0; index <imageFiles.count(); index++)
		{
			imageFiles[index] = dir.path()+QString("/")+imageFiles.at(index);
		}

		ui.graphicsView->showImageOnView(imageFiles);
	}
}

void SampleGraphicsViewApp::setImageFileFilter(bool bSelected)
{
	if (true == bSelected)
	{
		nameFilters << "*.jpg" << "*.png" << "*.bmp";

		m_eFile = eImage;
	}
	else
	{
		nameFilters.clear();
	}
}

void SampleGraphicsViewApp::setEmfFileFilter(bool bSelected)
{
	if (true == bSelected)
	{
		nameFilters << "*.emf";

		m_eFile = eEmf;
		//ui.graphicsView->setFileType(EFileType::eEmf);
	}
	else
	{
		nameFilters.clear();
	}
}

void SampleGraphicsViewApp::zoom(int scalePercentage)
{
	//Zoom value.
	m_nScaleFactor = scalePercentage; 

	ui.graphicsView->setItemSize(m_nScaleFactor);
}


void SampleGraphicsViewApp::onSliderPressed()
{
	m_bSliderPressed = true;

	ui.graphicsView->setTransformationMode(m_bSliderPressed);
}

void SampleGraphicsViewApp::onSliderReleased()
{
	m_bSliderPressed = false;

	ui.graphicsView->setTransformationMode(m_bSliderPressed);

	ui.graphicsView->updateView();
}