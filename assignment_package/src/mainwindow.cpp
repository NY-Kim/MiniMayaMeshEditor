#include "mainwindow.h"
#include <ui_mainwindow.h>
#include "cameracontrolshelp.h"
#include <iostream>
#include <QFileDialog>
#include <QDir>
#include <cmath>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mygl->setFocus();

    this->heSelected = false;
    this->faceSelected = false;
    this->vertexSelected = false;
    this->jointSelected = false;
    this->jsonImported = false;
    this->skinMeshed = false;

    disableSpinBox();
    connect(ui->mygl, SIGNAL(sendMesh(Mesh*)), this, SLOT(slot_addMesh(Mesh*)));
    connect(ui->mygl, SIGNAL(sendSkeleton(Skeleton*)), this, SLOT(slot_addSkeleton(Skeleton*)));

    connect(ui->mygl, SIGNAL(sendSelectedHE(QListWidgetItem*)), this, SLOT(slot_selectHalfEdge(QListWidgetItem*)));
    connect(ui->mygl, SIGNAL(sendSelectedVertex(QListWidgetItem*)), this, SLOT(slot_selectVertex(QListWidgetItem*)));
    connect(ui->mygl, SIGNAL(sendSelectedFace(QListWidgetItem*)), this, SLOT(slot_selectFace(QListWidgetItem*)));

    connect(ui->halfEdgesListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slot_selectHalfEdge(QListWidgetItem*)));
    connect(ui->facesListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slot_selectFace(QListWidgetItem*)));
    connect(ui->vertsListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slot_selectVertex(QListWidgetItem*)));
    connect(ui->jointsListWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(slot_selectJoint(QTreeWidgetItem*)));

    connect(ui->faceRedSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_faceR(double)));
    connect(ui->faceGreenSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_faceG(double)));
    connect(ui->faceBlueSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_faceB(double)));

    connect(ui->vertPosXSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_vertPosX(double)));
    connect(ui->vertPosYSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_vertPosY(double)));
    connect(ui->vertPosZSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_vertPosZ(double)));

    connect(ui->jointPosXSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_jointPosX(double)));
    connect(ui->jointPosYSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_jointPosY(double)));
    connect(ui->jointPosZSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_jointPosZ(double)));

    connect(ui->jointRotX, SIGNAL(clicked(bool)), this, SLOT(slot_jointRotX()));
    connect(ui->jointRotY, SIGNAL(clicked(bool)), this, SLOT(slot_jointRotY()));
    connect(ui->jointRotZ, SIGNAL(clicked(bool)), this, SLOT(slot_jointRotZ()));

    connect(ui->addVertex, SIGNAL(clicked(bool)), this, SLOT(slot_addVertex()));
    connect(ui->triangulate, SIGNAL(clicked(bool)), this, SLOT(slot_triangulate()));
    connect(ui->subdivide, SIGNAL(clicked(bool)), this, SLOT(slot_subdivide()));
    connect(ui->extrudeFace, SIGNAL(clicked(bool)), this, SLOT(slot_extrudeFace()));
    connect(ui->importobj, SIGNAL(clicked(bool)), this, SLOT(slot_importObj()));
    connect(ui->sharp, SIGNAL(clicked(bool)), this, SLOT(slot_sharp()));
    connect(ui->importjson, SIGNAL(clicked(bool)), this, SLOT(slot_importJSON()));
    connect(ui->skinMesh, SIGNAL(clicked(bool)), this, SLOT(slot_skinMesh()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// disable all spinboxes
void MainWindow::disableSpinBox() {
    ui->faceBlueSpinBox->setEnabled(false);
    ui->faceGreenSpinBox->setEnabled(false);
    ui->faceRedSpinBox->setEnabled(false);
    ui->vertPosXSpinBox->setEnabled(false);
    ui->vertPosYSpinBox->setEnabled(false);
    ui->vertPosZSpinBox->setEnabled(false);
    ui->jointPosXSpinBox->setEnabled(false);
    ui->jointPosYSpinBox->setEnabled(false);
    ui->jointPosZSpinBox->setEnabled(false);
    ui->jointRotX->setEnabled(false);
    ui->jointRotY->setEnabled(false);
    ui->jointRotZ->setEnabled(false);
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}

// deselect all vertex, face, and half edge
void MainWindow::deselect() {
    ui->vertsListWidget->selectionModel()->clear();
    ui->facesListWidget->selectionModel()->clear();
    ui->halfEdgesListWidget->selectionModel()->clear();
    ui->jointsListWidget->selectionModel()->clear();
}

// select half edge
void MainWindow::slot_selectHalfEdge(QListWidgetItem *half_edge) {
    this->heSelected = true;
    this->faceSelected = false;
    this->vertexSelected = false;
    this->jointSelected = false;

    ui->mygl->setFocus();
    ui->mygl->reset();
    this->deselect();
    this->disableSpinBox();

    HalfEdge* he = dynamic_cast<HalfEdge*>(half_edge);
    ui->halfEdgesListWidget->item(he->id)->setSelected(true);
    ui->sharp->setChecked(he->sharp);
    ui->mygl->m_halfEdgeDisplay.updateHalfEdge(he);
    ui->mygl->m_halfEdgeDisplay.create();
    ui->mygl->update();
}

// select face & set spinbox
void MainWindow::slot_selectFace(QListWidgetItem *face) {
    this->heSelected = false;
    this->faceSelected = true;
    this->vertexSelected = false;
    this->jointSelected = false;

    ui->mygl->setFocus();
    this->deselect();
    ui->mygl->reset();

    this->disableSpinBox();
    ui->faceRedSpinBox->setEnabled(true);
    ui->faceGreenSpinBox->setEnabled(true);
    ui->faceBlueSpinBox->setEnabled(true);

    Face* f = dynamic_cast<Face*>(face);
    ui->facesListWidget->item(f->id)->setSelected(true);
    ui->sharp->setChecked(f->sharp);
    ui->mygl->m_faceDisplay.updateFace(f);
    ui->mygl->m_faceDisplay.create();
    ui->mygl->update();

    ui->faceRedSpinBox->setValue(f->color[0]);;
    ui->faceGreenSpinBox->setValue(f->color[1]);
    ui->faceBlueSpinBox->setValue(f->color[2]);
}

// select vertex & set spinbox
void MainWindow::slot_selectVertex(QListWidgetItem *vertex) {
    this->heSelected = false;
    this->faceSelected = false;
    this->vertexSelected = true;
    this->jointSelected = false;

    ui->mygl->setFocus();
    this->deselect();
    ui->mygl->reset();

    this->disableSpinBox();
    ui->vertPosXSpinBox->setEnabled(true);
    ui->vertPosYSpinBox->setEnabled(true);
    ui->vertPosZSpinBox->setEnabled(true);

    Vertex* v = dynamic_cast<Vertex*>(vertex);
    ui->vertsListWidget->item(v->id)->setSelected(true);
    ui->sharp->setChecked(v->sharp);
    ui->mygl->m_vertDisplay.updateVertex(v);
    ui->mygl->m_vertDisplay.create();
    ui->mygl->update();

    ui->vertPosXSpinBox->setValue(v->pos[0]);
    ui->vertPosYSpinBox->setValue(v->pos[1]);
    ui->vertPosZSpinBox->setValue(v->pos[2]);
}

void MainWindow::slot_selectJoint(QTreeWidgetItem *joint) {
    this->heSelected = false;
    this->faceSelected = false;
    this->vertexSelected = false;
    this->jointSelected = true;

    ui->mygl->setFocus();
    this->deselect();

    this->disableSpinBox();
    ui->jointPosXSpinBox->setEnabled(true);
    ui->jointPosYSpinBox->setEnabled(true);
    ui->jointPosZSpinBox->setEnabled(true);
    ui->jointRotX->setEnabled(true);
    ui->jointRotY->setEnabled(true);
    ui->jointRotZ->setEnabled(true);

    Joint* j = dynamic_cast<Joint*>(joint);
    ui->mygl->m_skeleton.selectedJoint = j->id;

    ui->jointPosXSpinBox->setValue(j->position[0]);
    ui->jointPosYSpinBox->setValue(j->position[1]);
    ui->jointPosZSpinBox->setValue(j->position[2]);

    this->displayQuat();
    ui->mygl->reset();
    ui->mygl->update();
}

void MainWindow::displayQuat() {
    ui->mygl->setFocus();
    glm::quat quat = ui->mygl->m_skeleton.joints[ui->mygl->m_skeleton.selectedJoint]->rotation;
    ui->theta->setText(QString::fromStdString(std::to_string(acos(quat.w) * 2).substr(0, 4)));
    ui->angle->setText(QString::fromStdString("(" + std::to_string(roundf(quat.x * 100) / 100).substr(0, 4) + ", " +
                                                    std::to_string(roundf(quat.y * 100) / 100).substr(0, 4) + ", " +
                                                    std::to_string(roundf(quat.z * 100) / 100).substr(0, 4) + ")"));
}

void MainWindow::slot_faceR(double r) {
    ui->mygl->setFocus();
    ui->mygl->m_faceDisplay.representedFace->color[0] = r;
    ui->mygl->recreate();
}

void MainWindow::slot_faceG(double g) {
    ui->mygl->setFocus();
    ui->mygl->m_faceDisplay.representedFace->color[1] = g;
    ui->mygl->recreate();
}

void MainWindow::slot_faceB(double b) {
    ui->mygl->setFocus();
    ui->mygl->m_faceDisplay.representedFace->color[2] = b;
    ui->mygl->recreate();
}

void MainWindow::slot_vertPosX(double x) {
    ui->mygl->setFocus();
    if (this->vertexSelected) {
        ui->mygl->m_vertDisplay.representedVertex->pos[0] = x;
        ui->mygl->recreate();
        slot_addMesh(&ui->mygl->m_mesh);
    }
}

void MainWindow::slot_vertPosY(double y) {
    ui->mygl->setFocus();
    if (this->vertexSelected) {
        ui->mygl->m_vertDisplay.representedVertex->pos[1] = y;
        ui->mygl->recreate();
        slot_addMesh(&ui->mygl->m_mesh);
    }
}

void MainWindow::slot_vertPosZ(double z) {
    ui->mygl->setFocus();
    if (this->vertexSelected) {
        ui->mygl->m_vertDisplay.representedVertex->pos[2] = z;
        ui->mygl->recreate();
        slot_addMesh(&ui->mygl->m_mesh);
    }
}

void MainWindow::slot_addVertex() {
    if (this->heSelected) {
        ui->mygl->setFocus();
        ui->mygl->splitHalfEdge();
        ui->mygl->reset();
        ui->mygl->update();

        Mesh* mesh = &ui->mygl->m_mesh;
        slot_addMesh(mesh);
        slot_selectVertex(mesh->vertices[mesh->vertices.size() - 1].get());
    }
}

void MainWindow::slot_triangulate() {
    if (this->faceSelected) {
        ui->mygl->setFocus();
        ui->mygl->triangulate(ui->mygl->m_faceDisplay.representedFace);
        ui->mygl->reset();
        ui->mygl->update();

        slot_addMesh(&ui->mygl->m_mesh);
    }
}

void MainWindow::slot_subdivide() {
    ui->mygl->setFocus();
    ui->mygl->subdivide();
    ui->mygl->reset();
    ui->mygl->update();

    slot_addMesh(&ui->mygl->m_mesh);
}

void MainWindow::slot_extrudeFace() {
    if (this->faceSelected) {
        ui->mygl->setFocus();
        ui->mygl->extrudeFace();
        ui->mygl->reset();
        ui->mygl->update();

        slot_addMesh(&ui->mygl->m_mesh);
    }
}

void MainWindow::slot_importObj() {
    QString filename = QFileDialog::getOpenFileName(0,
                                                    QString("Load OBJ File"),
                                                    QDir::currentPath().append(QString("../..")),
                                                    QString("*.obj"));
    ui->mygl->loadObj(filename);
    ui->mygl->reset();
    ui->mygl->update();

    slot_addMesh(&ui->mygl->m_mesh);
    ui->mygl->setFocus();
    this->skinMeshed = false;
}

void MainWindow::slot_sharp() {
    ui->mygl->setFocus();
    if (this->heSelected) {
        HalfEdge* he = ui->mygl->m_halfEdgeDisplay.representedHalfEdge;
        he->sharp = !he->sharp;
        he->sym->sharp = !he->sym->sharp;
        ui->halfEdgesListWidget->item(he->id)->setSelected(true);
    } else if (this->faceSelected) {
        Face* f = ui->mygl->m_faceDisplay.representedFace;
        f->sharp = !f->sharp;
        ui->facesListWidget->item(f->id)->setSelected(true);
    } else if (this->vertexSelected) {
        Vertex* v = ui->mygl->m_vertDisplay.representedVertex;
        v->sharp = !v->sharp;
        ui->vertsListWidget->item(v->id)->setSelected(true);
    }
}

void MainWindow::slot_importJSON() {
    QString filename = QFileDialog::getOpenFileName(0,
                                                    QString("Load JSON File"),
                                                    QDir::currentPath().append(QString("../..")),
                                                    QString("*.json"));
    ui->mygl->loadJSON(filename);
    ui->mygl->setFocus();
    this->deselect();

    slot_addSkeleton(&ui->mygl->m_skeleton);
    this->jsonImported = true;
    this->skinMeshed = false;
    this->jointSelected = false;
    ui->mygl->m_skeleton.selectedJoint = -1;
    ui->mygl->reset();
    ui->mygl->update();
}


void MainWindow::slot_skinMesh() {
    if (this->jsonImported) {
        ui->mygl->assignMatrix();
        ui->mygl->skinMesh();
        ui->mygl->setFocus();
        ui->mygl->reset();
        ui->mygl->update();
        this->skinMeshed = true;
    }
}

void MainWindow::slot_jointPosX(double x){
    ui->mygl->setFocus();
    if (this->jointSelected) {
        ui->mygl->m_skeleton.joints[ui->mygl->m_skeleton.selectedJoint]->position[0] = x;
        if (this->skinMeshed) {
            ui->mygl->skinMesh();
        }
        ui->mygl->reset();
        ui->mygl->update();
    }
}

void MainWindow::slot_jointPosY(double y){
    ui->mygl->setFocus();
    if (this->jointSelected) {
        ui->mygl->m_skeleton.joints[ui->mygl->m_skeleton.selectedJoint]->position[1] = y;
        if (this->skinMeshed) {
            ui->mygl->skinMesh();
        }
        ui->mygl->reset();
        ui->mygl->update();

    }
}

void MainWindow::slot_jointPosZ(double z){
    ui->mygl->setFocus();
    if (this->jointSelected) {
        ui->mygl->m_skeleton.joints[ui->mygl->m_skeleton.selectedJoint]->position[2] = z;
        if (this->skinMeshed) {
            ui->mygl->skinMesh();
        }
        ui->mygl->reset();
        ui->mygl->update();
    }
}

void MainWindow::slot_jointRotX(){
    ui->mygl->setFocus();
    if (this->jointSelected) {
        ui->mygl->jointRotateX();
        if (this->skinMeshed) {
            ui->mygl->skinMesh();
        }
        ui->mygl->reset();
        ui->mygl->update();
        this->displayQuat();
    }
}

void MainWindow::slot_jointRotY(){
    ui->mygl->setFocus();
    if (this->jointSelected) {
        ui->mygl->jointRotateY();
        if (this->skinMeshed) {
            ui->mygl->skinMesh();
        }
        ui->mygl->reset();
        ui->mygl->update();
        this->displayQuat();
    }
}

void MainWindow::slot_jointRotZ(){
    ui->mygl->setFocus();
    if (this->jointSelected) {
        ui->mygl->jointRotateZ();
        if (this->skinMeshed) {
            ui->mygl->skinMesh();
        }
        ui->mygl->reset();
        ui->mygl->update();
        this->displayQuat();
    }
}

void MainWindow::on_actionCamera_Controls_triggered()
{
    CameraControlsHelp* c = new CameraControlsHelp();
    c->show();
}

void MainWindow::slot_addMesh(Mesh* mesh) {
    for (unsigned int i = 0; i < mesh->half_edges.size(); i++) {
        ui->halfEdgesListWidget->addItem(mesh->half_edges[i].get());
    }

    for (unsigned int i = 0; i < mesh->faces.size(); i++) {
        ui->facesListWidget->addItem(mesh->faces[i].get());
    }

    for (unsigned int i = 0; i < mesh->vertices.size(); i++) {
        ui->vertsListWidget->addItem(mesh->vertices[i].get());
    }
}

void MainWindow::slot_addSkeleton(Skeleton *skeleton) {
    ui->jointsListWidget->addTopLevelItem(skeleton->joints[0].get());
}


