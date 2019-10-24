#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mesh.h>


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool heSelected;
    bool faceSelected;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void disableSpinBox();
    void deselect();

private slots:
    void on_actionQuit_triggered();
    void on_actionCamera_Controls_triggered();

    void slot_addMesh(Mesh*);

    void slot_selectHalfEdge(QListWidgetItem*);
    void slot_selectFace(QListWidgetItem*);
    void slot_selectVertex(QListWidgetItem*);

    void slot_faceR(double);
    void slot_faceG(double);
    void slot_faceB(double);

    void slot_vertPosX(double);
    void slot_vertPosY(double);
    void slot_vertPosZ(double);

    void slot_addVertex();
    void slot_triangulate();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
