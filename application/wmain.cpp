#include "wmain.h"
#include "ui_wmain.h"

#include <QAction>
#include <QMenuBar>
#include <QResizeEvent>
#include <QFileDialog>

#include "linktyperepository.h"

HIC::WMain::WMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WMain)
{
    ui->setupUi(this);

    loadLinkTypes();

    //////////////// Preloaded Robot /////////////////////////////////////////////
    PDC::Robot* robot = _application.robot();
    robot->AppendLink(new PDC::Link(PDC::LinkTypeRepository::Get("base1")));
    robot->AppendLink(new PDC::Link(PDC::LinkTypeRepository::Get("middle2")));
    robot->AppendLink(new PDC::Link(PDC::LinkTypeRepository::Get("middle2")));
    robot->AppendLink(new PDC::Link(PDC::LinkTypeRepository::Get("middle2")));
    robot->AppendLink(new PDC::Link(PDC::LinkTypeRepository::Get("middle2")));
    //////////////////////////////////////////////////////////////////////////////

    ui->glWidget->setRobot(_application.robot());
    ui->robotControl->setGLWidget(ui->glWidget);

    QObject::connect(ui->rotXSlider,SIGNAL(valueChanged(int)),this,SLOT(rotXSliderValueChanged(int)));
    QObject::connect(ui->rotYSlider,SIGNAL(valueChanged(int)),this,SLOT(rotYSliderValueChanged(int)));
    QObject::connect(ui->rotZSlider,SIGNAL(valueChanged(int)),this,SLOT(rotZSliderValueChanged(int)));

    QObject::connect(ui->transXSlider,SIGNAL(valueChanged(int)),this,SLOT(transXSliderValueChanged(int)));
    QObject::connect(ui->transYSlider,SIGNAL(valueChanged(int)),this,SLOT(transYSliderValueChanged(int)));
    QObject::connect(ui->transZSlider,SIGNAL(valueChanged(int)),this,SLOT(transZSliderValueChanged(int)));
}

HIC::WMain::~WMain()
{
    delete ui;
}

void HIC::WMain::loadLinkTypes()
{
    QString linktypeDirPath = QCoreApplication::applicationDirPath() + tr("/linktypes/");
    QDir linktypeDir = QDir(linktypeDirPath);
    QStringList nameFilters;
    nameFilters.append(QString("*.linktype"));
    QStringList fileList = linktypeDir.entryList(nameFilters);

    std::vector<std::string> linkTypeFilePaths;
    for (QStringList::iterator iterator = fileList.begin(); iterator != fileList.end(); iterator++)
    {
        linkTypeFilePaths.push_back(iterator->toStdString());
    }

    QDir::setCurrent(linktypeDirPath);
    _application.loadLinkTypeList(linkTypeFilePaths);
    QDir::setCurrent(QCoreApplication::applicationDirPath());
}

void HIC::WMain::rotXSliderValueChanged(int value)
{
    double angle = value * 3.6;
    ui->glWidget->rotateX(angle);    
}

void HIC::WMain::rotYSliderValueChanged(int value)
{
    double angle = value * 3.6;
    ui->glWidget->rotateY(angle);
}

void HIC::WMain::rotZSliderValueChanged(int value)
{
    double angle = value * 3.6;
    ui->glWidget->rotateZ(angle);
}

void HIC::WMain::transXSliderValueChanged(int value)
{
    ui->glWidget->translateX(value);
}

void HIC::WMain::transYSliderValueChanged(int value)
{
    ui->glWidget->translateY(value);
}

void HIC::WMain::transZSliderValueChanged(int value)
{
    ui->glWidget->translateZ(value);
}



