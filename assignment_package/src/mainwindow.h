#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mesh.h>
#include <skeleton.h>


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool heSelected;
    bool faceSelected;
    bool vertexSelected;
    bool jointSelected;
    bool jsonImported;
    bool skinMeshed;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void disableSpinBox();
    void deselect();

private slots:
    void on_actionQuit_triggered();
    void on_actionCamera_Controls_triggered();

    void slot_addMesh(Mesh*);
    void slot_addSkeleton(Skeleton*);

    void slot_selectHalfEdge(QListWidgetItem*);
    void slot_selectFace(QListWidgetItem*);
    void slot_selectVertex(QListWidgetItem*);
    void slot_selectJoint(QTreeWidgetItem*);

    void displayQuat();

    void slot_faceR(double);
    void slot_faceG(double);
    void slot_faceB(double);

    void slot_vertPosX(double);
    void slot_vertPosY(double);
    void slot_vertPosZ(double);

    void slot_jointPosX(double);
    void slot_jointPosY(double);
    void slot_jointPosZ(double);

    void slot_jointRotX(double);
    void slot_jointRotY(double);
    void slot_jointRotZ(double);

    void slot_addVertex();
    void slot_triangulate();
    void slot_subdivide();
    void slot_extrudeFace();
    void slot_importObj();
    void slot_sharp();
    void slot_importJSON();
    void slot_skinMesh();

    void slot_joint1Change(int);
    void slot_joint2Change(int);
    void slot_joint1InfChange(double);
    void slot_joint2InfChange(double);

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
