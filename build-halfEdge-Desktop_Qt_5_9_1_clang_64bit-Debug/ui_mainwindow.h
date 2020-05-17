/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "mygl.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionCamera_Controls;
    QWidget *centralWidget;
    MyGL *mygl;
    QListWidget *vertsListWidget;
    QListWidget *halfEdgesListWidget;
    QListWidget *facesListWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QDoubleSpinBox *vertPosXSpinBox;
    QDoubleSpinBox *vertPosYSpinBox;
    QDoubleSpinBox *vertPosZSpinBox;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QDoubleSpinBox *faceBlueSpinBox;
    QLabel *label_10;
    QDoubleSpinBox *faceGreenSpinBox;
    QDoubleSpinBox *faceRedSpinBox;
    QLabel *label_11;
    QPushButton *addVertex;
    QPushButton *triangulate;
    QPushButton *subdivide;
    QPushButton *extrudeFace;
    QPushButton *importobj;
    QCheckBox *sharp;
    QLabel *label_12;
    QPushButton *importjson;
    QPushButton *skinMesh;
    QTreeWidget *jointsListWidget;
    QLabel *label_13;
    QDoubleSpinBox *jointPosYSpinBox;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QDoubleSpinBox *jointPosXSpinBox;
    QDoubleSpinBox *jointPosZSpinBox;
    QLabel *label_17;
    QPushButton *jointRotX;
    QPushButton *jointRotY;
    QPushButton *jointRotZ;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *theta;
    QLabel *angle;
    QComboBox *joint1;
    QComboBox *joint2;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QDoubleSpinBox *joint1Inf;
    QDoubleSpinBox *joint2Inf;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1020, 621);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionCamera_Controls = new QAction(MainWindow);
        actionCamera_Controls->setObjectName(QStringLiteral("actionCamera_Controls"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        mygl = new MyGL(centralWidget);
        mygl->setObjectName(QStringLiteral("mygl"));
        mygl->setGeometry(QRect(11, 11, 561, 361));
        vertsListWidget = new QListWidget(centralWidget);
        vertsListWidget->setObjectName(QStringLiteral("vertsListWidget"));
        vertsListWidget->setGeometry(QRect(618, 10, 111, 341));
        halfEdgesListWidget = new QListWidget(centralWidget);
        halfEdgesListWidget->setObjectName(QStringLiteral("halfEdgesListWidget"));
        halfEdgesListWidget->setGeometry(QRect(751, 10, 111, 341));
        facesListWidget = new QListWidget(centralWidget);
        facesListWidget->setObjectName(QStringLiteral("facesListWidget"));
        facesListWidget->setGeometry(QRect(884, 10, 111, 341));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(618, 360, 111, 16));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(750, 360, 111, 16));
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(884, 360, 111, 16));
        label_3->setAlignment(Qt::AlignCenter);
        vertPosXSpinBox = new QDoubleSpinBox(centralWidget);
        vertPosXSpinBox->setObjectName(QStringLiteral("vertPosXSpinBox"));
        vertPosXSpinBox->setGeometry(QRect(751, 421, 62, 22));
        vertPosXSpinBox->setMinimum(-99);
        vertPosXSpinBox->setMaximum(99);
        vertPosYSpinBox = new QDoubleSpinBox(centralWidget);
        vertPosYSpinBox->setObjectName(QStringLiteral("vertPosYSpinBox"));
        vertPosYSpinBox->setGeometry(QRect(845, 421, 62, 22));
        vertPosYSpinBox->setMinimum(-99);
        vertPosZSpinBox = new QDoubleSpinBox(centralWidget);
        vertPosZSpinBox->setObjectName(QStringLiteral("vertPosZSpinBox"));
        vertPosZSpinBox->setGeometry(QRect(938, 421, 62, 22));
        vertPosZSpinBox->setMinimum(-99);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(617, 422, 101, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(710, 424, 61, 16));
        label_5->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(804, 424, 61, 16));
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(898, 424, 61, 16));
        label_7->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(898, 454, 61, 16));
        label_8->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(709, 454, 61, 16));
        label_9->setAlignment(Qt::AlignCenter);
        faceBlueSpinBox = new QDoubleSpinBox(centralWidget);
        faceBlueSpinBox->setObjectName(QStringLiteral("faceBlueSpinBox"));
        faceBlueSpinBox->setGeometry(QRect(937, 451, 62, 22));
        faceBlueSpinBox->setMaximum(1);
        faceBlueSpinBox->setSingleStep(0.5);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(617, 452, 71, 16));
        faceGreenSpinBox = new QDoubleSpinBox(centralWidget);
        faceGreenSpinBox->setObjectName(QStringLiteral("faceGreenSpinBox"));
        faceGreenSpinBox->setGeometry(QRect(844, 451, 62, 22));
        faceGreenSpinBox->setMaximum(1);
        faceGreenSpinBox->setSingleStep(0.5);
        faceRedSpinBox = new QDoubleSpinBox(centralWidget);
        faceRedSpinBox->setObjectName(QStringLiteral("faceRedSpinBox"));
        faceRedSpinBox->setGeometry(QRect(751, 451, 62, 22));
        faceRedSpinBox->setMaximum(1);
        faceRedSpinBox->setSingleStep(0.5);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(804, 453, 61, 16));
        label_11->setAlignment(Qt::AlignCenter);
        addVertex = new QPushButton(centralWidget);
        addVertex->setObjectName(QStringLiteral("addVertex"));
        addVertex->setGeometry(QRect(616, 517, 186, 21));
        triangulate = new QPushButton(centralWidget);
        triangulate->setObjectName(QStringLiteral("triangulate"));
        triangulate->setGeometry(QRect(815, 517, 186, 21));
        subdivide = new QPushButton(centralWidget);
        subdivide->setObjectName(QStringLiteral("subdivide"));
        subdivide->setGeometry(QRect(815, 551, 186, 21));
        extrudeFace = new QPushButton(centralWidget);
        extrudeFace->setObjectName(QStringLiteral("extrudeFace"));
        extrudeFace->setGeometry(QRect(616, 551, 186, 21));
        importobj = new QPushButton(centralWidget);
        importobj->setObjectName(QStringLiteral("importobj"));
        importobj->setGeometry(QRect(616, 484, 384, 21));
        sharp = new QCheckBox(centralWidget);
        sharp->setObjectName(QStringLiteral("sharp"));
        sharp->setGeometry(QRect(940, 389, 61, 22));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(43, 574, 111, 16));
        label_12->setAlignment(Qt::AlignCenter);
        importjson = new QPushButton(centralWidget);
        importjson->setObjectName(QStringLiteral("importjson"));
        importjson->setGeometry(QRect(208, 419, 181, 21));
        skinMesh = new QPushButton(centralWidget);
        skinMesh->setObjectName(QStringLiteral("skinMesh"));
        skinMesh->setGeometry(QRect(400, 419, 181, 21));
        jointsListWidget = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        jointsListWidget->setHeaderItem(__qtreewidgetitem);
        jointsListWidget->setObjectName(QStringLiteral("jointsListWidget"));
        jointsListWidget->setGeometry(QRect(14, 419, 181, 151));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(210, 452, 131, 16));
        jointPosYSpinBox = new QDoubleSpinBox(centralWidget);
        jointPosYSpinBox->setObjectName(QStringLiteral("jointPosYSpinBox"));
        jointPosYSpinBox->setGeometry(QRect(427, 450, 62, 22));
        jointPosYSpinBox->setMinimum(-99);
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(496, 453, 31, 16));
        label_14->setAlignment(Qt::AlignCenter);
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(386, 453, 61, 16));
        label_15->setAlignment(Qt::AlignCenter);
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(293, 453, 61, 16));
        label_16->setAlignment(Qt::AlignCenter);
        jointPosXSpinBox = new QDoubleSpinBox(centralWidget);
        jointPosXSpinBox->setObjectName(QStringLiteral("jointPosXSpinBox"));
        jointPosXSpinBox->setGeometry(QRect(334, 450, 62, 22));
        jointPosXSpinBox->setMinimum(-99);
        jointPosXSpinBox->setMaximum(99);
        jointPosZSpinBox = new QDoubleSpinBox(centralWidget);
        jointPosZSpinBox->setObjectName(QStringLiteral("jointPosZSpinBox"));
        jointPosZSpinBox->setGeometry(QRect(520, 450, 62, 22));
        jointPosZSpinBox->setMinimum(-99);
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(210, 482, 91, 16));
        jointRotX = new QPushButton(centralWidget);
        jointRotX->setObjectName(QStringLiteral("jointRotX"));
        jointRotX->setGeometry(QRect(316, 480, 81, 21));
        jointRotY = new QPushButton(centralWidget);
        jointRotY->setObjectName(QStringLiteral("jointRotY"));
        jointRotY->setGeometry(QRect(408, 480, 81, 21));
        jointRotZ = new QPushButton(centralWidget);
        jointRotZ->setObjectName(QStringLiteral("jointRotZ"));
        jointRotZ->setGeometry(QRect(501, 480, 81, 21));
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(210, 511, 91, 16));
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(309, 511, 61, 16));
        label_19->setAlignment(Qt::AlignCenter);
        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(405, 511, 41, 16));
        label_20->setAlignment(Qt::AlignCenter);
        theta = new QLabel(centralWidget);
        theta->setObjectName(QStringLiteral("theta"));
        theta->setGeometry(QRect(359, 511, 41, 16));
        angle = new QLabel(centralWidget);
        angle->setObjectName(QStringLiteral("angle"));
        angle->setGeometry(QRect(442, 511, 141, 16));
        joint1 = new QComboBox(centralWidget);
        joint1->setObjectName(QStringLiteral("joint1"));
        joint1->setGeometry(QRect(348, 537, 91, 24));
        joint2 = new QComboBox(centralWidget);
        joint2->setObjectName(QStringLiteral("joint2"));
        joint2->setGeometry(QRect(348, 566, 91, 24));
        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(210, 541, 81, 16));
        label_22 = new QLabel(centralWidget);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(617, 389, 191, 16));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label_22->setFont(font);
        label_23 = new QLabel(centralWidget);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(14, 389, 271, 16));
        label_23->setFont(font);
        label_24 = new QLabel(centralWidget);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(298, 541, 60, 16));
        label_25 = new QLabel(centralWidget);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(298, 570, 60, 16));
        label_26 = new QLabel(centralWidget);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(451, 541, 60, 16));
        label_27 = new QLabel(centralWidget);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(451, 570, 60, 16));
        joint1Inf = new QDoubleSpinBox(centralWidget);
        joint1Inf->setObjectName(QStringLiteral("joint1Inf"));
        joint1Inf->setGeometry(QRect(521, 537, 61, 25));
        joint1Inf->setMaximum(1);
        joint1Inf->setSingleStep(0.2);
        joint2Inf = new QDoubleSpinBox(centralWidget);
        joint2Inf->setObjectName(QStringLiteral("joint2Inf"));
        joint2Inf->setGeometry(QRect(521, 565, 61, 25));
        joint2Inf->setMaximum(1);
        joint2Inf->setSingleStep(0.2);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1020, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionQuit);
        menuHelp->addAction(actionCamera_Controls);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "OpenGLDemo", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionCamera_Controls->setText(QApplication::translate("MainWindow", "Camera Controls", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Vertices", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Half-Edges", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Faces", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Vertex Position", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "B", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "R", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Face Color", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "G", Q_NULLPTR));
        addVertex->setText(QApplication::translate("MainWindow", "Split Edge", Q_NULLPTR));
        triangulate->setText(QApplication::translate("MainWindow", "Triangulate", Q_NULLPTR));
        subdivide->setText(QApplication::translate("MainWindow", "Subdivide", Q_NULLPTR));
        extrudeFace->setText(QApplication::translate("MainWindow", "Extrude Face", Q_NULLPTR));
        importobj->setText(QApplication::translate("MainWindow", "Import OBJ ", Q_NULLPTR));
        sharp->setText(QApplication::translate("MainWindow", "Sharp", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "Joints", Q_NULLPTR));
        importjson->setText(QApplication::translate("MainWindow", "Import JSON ", Q_NULLPTR));
        skinMesh->setText(QApplication::translate("MainWindow", "Skin Mesh", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "Position (local)", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        label_16->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        label_17->setText(QApplication::translate("MainWindow", "Rotation", Q_NULLPTR));
        jointRotX->setText(QApplication::translate("MainWindow", "rotate X", Q_NULLPTR));
        jointRotY->setText(QApplication::translate("MainWindow", "rotate Y", Q_NULLPTR));
        jointRotZ->setText(QApplication::translate("MainWindow", "rotate Z", Q_NULLPTR));
        label_18->setText(QApplication::translate("MainWindow", "Rotation Angle", Q_NULLPTR));
        label_19->setText(QApplication::translate("MainWindow", "Theta: ", Q_NULLPTR));
        label_20->setText(QApplication::translate("MainWindow", "Axis:", Q_NULLPTR));
        theta->setText(QString());
        angle->setText(QString());
        label_21->setText(QApplication::translate("MainWindow", "Skin Weight ", Q_NULLPTR));
        label_22->setText(QApplication::translate("MainWindow", "MESH OPERATIONS", Q_NULLPTR));
        label_23->setText(QApplication::translate("MainWindow", "JOINT & SKELETON OPERATIONS", Q_NULLPTR));
        label_24->setText(QApplication::translate("MainWindow", "Joint 1", Q_NULLPTR));
        label_25->setText(QApplication::translate("MainWindow", "Joint 2", Q_NULLPTR));
        label_26->setText(QApplication::translate("MainWindow", "Influence", Q_NULLPTR));
        label_27->setText(QApplication::translate("MainWindow", "Influence", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
