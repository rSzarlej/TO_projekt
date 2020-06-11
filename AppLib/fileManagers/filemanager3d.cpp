#include "filemanager3d.h"
#include "ui_filemanager3d.h"
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <QQuaternion>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <QCamera>
#include <QMesh>
#include <QPointLight>
#include <QOrbitCameraController>

FileManager3d::FileManager3d(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileManager3d)
{
    ui->setupUi(this);

    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();

    container = createWindowContainer(view,this);

    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x575757)));

    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();
    Qt3DRender::QCamera *cameraEntity = view->camera();

    cameraEntity->setPosition(QVector3D(0, 0, 50.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(0.8f);
    lightEntity->addComponent(light);

    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(QVector3D(60, 0, 40.0f));
    lightEntity->addComponent(lightTransform);

    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setCamera(cameraEntity);

    Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();
    cuboidTransform->setScale(10.0f);
    cuboidTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));
    cuboidTransform->setRotation(QQuaternion(1,1.5,1,0).normalized());

    mainEntity = new Qt3DCore::QEntity(rootEntity);
    mainEntity->addComponent(cuboidTransform);
    view->setRootEntity(rootEntity);
}

FileManager3d::~FileManager3d()
{
    delete ui;
}

void FileManager3d::addMesh(QString path)
{
    QUrl data = QUrl::fromLocalFile(path);
    Qt3DRender::QMesh *myMesh = new Qt3DRender::QMesh;
    myMesh->setMeshName("MyMesh");
    myMesh->setSource(data);

    Qt3DExtras::QPhongMaterial *cuboidMaterial = new Qt3DExtras::QPhongMaterial();
    cuboidMaterial->setDiffuse(QColor(QRgb(0x005FFF)));


    mainEntity->addComponent(myMesh);
    mainEntity->addComponent(cuboidMaterial);
}

void FileManager3d::resizeEvent(QResizeEvent *event)
{
    resizeView(this->size());
}

void FileManager3d::resizeView(QSize size)
{
    container->resize(size);
}
