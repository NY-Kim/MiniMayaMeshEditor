#include "mainwindow.h"
#include <ui_mainwindow.h>
#include "cameracontrolshelp.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mygl->setFocus();

    MainWindow::heSelected = false;
    MainWindow::faceSelected = false;

    disableSpinBox();
    connect(ui->mygl, SIGNAL(sendMesh(Mesh*)), this, SLOT(slot_addMesh(Mesh*)));

    connect(ui->mygl, SIGNAL(sendSelectedHE(QListWidgetItem*)), this, SLOT(slot_selectHalfEdge(QListWidgetItem*)));
    connect(ui->mygl, SIGNAL(sendSelectedVertex(QListWidgetItem*)), this, SLOT(slot_selectVertex(QListWidgetItem*)));
    connect(ui->mygl, SIGNAL(sendSelectedFace(QListWidgetItem*)), this, SLOT(slot_selectFace(QListWidgetItem*)));

    connect(ui->halfEdgesListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slot_selectHalfEdge(QListWidgetItem*)));
    connect(ui->facesListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slot_selectFace(QListWidgetItem*)));
    connect(ui->vertsListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slot_selectVertex(QListWidgetItem*)));

    connect(ui->faceRedSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_faceR(double)));
    connect(ui->faceGreenSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_faceG(double)));
    connect(ui->faceBlueSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_faceB(double)));

    connect(ui->vertPosXSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_vertPosX(double)));
    connect(ui->vertPosYSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_vertPosY(double)));
    connect(ui->vertPosZSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_vertPosZ(double)));

    connect(ui->addVertex, SIGNAL(clicked(bool)), this, SLOT(slot_addVertex()));
    connect(ui->triangulate, SIGNAL(clicked(bool)), this, SLOT(slot_triangulate()));
    connect(ui->subdivide, SIGNAL(clicked(bool)), this, SLOT(slot_subdivide()));
    connect(ui->extrudeFace, SIGNAL(clicked(bool)), this, SLOT(slot_extrudeFace()));
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
}

// select half edge
void MainWindow::slot_selectHalfEdge(QListWidgetItem *half_edge) {
    MainWindow::heSelected = true;
    MainWindow::faceSelected = false;

    ui->mygl->setFocus();
    ui->mygl->reset();
    this->deselect();
    this->disableSpinBox();

    HalfEdge* he = dynamic_cast<HalfEdge*>(half_edge);
    ui->halfEdgesListWidget->item(he->id)->setSelected(true);
    ui->mygl->m_halfEdgeDisplay.updateHalfEdge(dynamic_cast<HalfEdge*>(half_edge));
    ui->mygl->m_halfEdgeDisplay.create();
    ui->mygl->update();
}

// select face & set spinbox
void MainWindow::slot_selectFace(QListWidgetItem *face) {
    MainWindow::heSelected = false;
    MainWindow::faceSelected = true;

    ui->mygl->setFocus();
    ui->mygl->reset();
    this->deselect();

    this->disableSpinBox();
    ui->faceRedSpinBox->setEnabled(true);
    ui->faceGreenSpinBox->setEnabled(true);
    ui->faceBlueSpinBox->setEnabled(true);

    Face* f = dynamic_cast<Face*>(face);
    ui->facesListWidget->item(f->id)->setSelected(true);
    ui->mygl->m_faceDisplay.updateFace(f);
    ui->mygl->m_faceDisplay.create();
    ui->mygl->update();

    ui->faceRedSpinBox->setValue(f->color[0]);;
    ui->faceGreenSpinBox->setValue(f->color[1]);
    ui->faceBlueSpinBox->setValue(f->color[2]);
}

// select vertex & set spinbox
void MainWindow::slot_selectVertex(QListWidgetItem *vertex) {
    MainWindow::heSelected = false;
    MainWindow::faceSelected = false;

    ui->mygl->setFocus();
    ui->mygl->reset();
    this->deselect();

    this->disableSpinBox();
    ui->vertPosXSpinBox->setEnabled(true);
    ui->vertPosYSpinBox->setEnabled(true);
    ui->vertPosZSpinBox->setEnabled(true);

    Vertex* v = dynamic_cast<Vertex*>(vertex);
    ui->vertsListWidget->item(v->id)->setSelected(true);
    ui->mygl->m_vertDisplay.updateVertex(v);
    ui->mygl->m_vertDisplay.create();
    ui->mygl->update();

    ui->vertPosXSpinBox->setValue(v->pos[0]);
    ui->vertPosYSpinBox->setValue(v->pos[1]);
    ui->vertPosZSpinBox->setValue(v->pos[2]);
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
    ui->mygl->m_vertDisplay.representedVertex->pos[0] = x;
//    ui->mygl->planarOperation();
    ui->mygl->recreate();
    slot_addMesh(&ui->mygl->m_mesh);
}

void MainWindow::slot_vertPosY(double y) {
    ui->mygl->setFocus();
    ui->mygl->m_vertDisplay.representedVertex->pos[1] = y;
//    ui->mygl->planarOperation();
    ui->mygl->recreate();
    slot_addMesh(&ui->mygl->m_mesh);
}

void MainWindow::slot_vertPosZ(double z) {
    ui->mygl->setFocus();
    ui->mygl->m_vertDisplay.representedVertex->pos[2] = z;
//    ui->mygl->planarOperation();
    ui->mygl->recreate();
    slot_addMesh(&ui->mygl->m_mesh);
}

void MainWindow::slot_addVertex() {
    if (MainWindow::heSelected) {
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
    if (MainWindow::faceSelected) {
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
    if (MainWindow::faceSelected) {
        ui->mygl->setFocus();
        ui->mygl->extrudeFace();
        ui->mygl->reset();
        ui->mygl->update();

        slot_addMesh(&ui->mygl->m_mesh);
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
