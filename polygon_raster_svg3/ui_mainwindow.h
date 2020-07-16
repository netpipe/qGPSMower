/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QPushButton *btn_svg;
    QPushButton *btn_move;
    QPushButton *btn_finish;
    QSpinBox *sb_stroke;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *sb_radius;
    QPushButton *btn_start;
    QSpinBox *sb_angle;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *lb_left;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1077, 599);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 191, 541));
        btn_svg = new QPushButton(groupBox);
        btn_svg->setObjectName(QStringLiteral("btn_svg"));
        btn_svg->setGeometry(QRect(20, 30, 151, 31));
        btn_move = new QPushButton(groupBox);
        btn_move->setObjectName(QStringLiteral("btn_move"));
        btn_move->setGeometry(QRect(20, 150, 151, 31));
        btn_finish = new QPushButton(groupBox);
        btn_finish->setObjectName(QStringLiteral("btn_finish"));
        btn_finish->setGeometry(QRect(20, 110, 151, 31));
        sb_stroke = new QSpinBox(groupBox);
        sb_stroke->setObjectName(QStringLiteral("sb_stroke"));
        sb_stroke->setGeometry(QRect(80, 190, 81, 22));
        sb_stroke->setMinimum(1);
        sb_stroke->setMaximum(10);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 191, 47, 20));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 231, 47, 20));
        label_2->setFont(font);
        sb_radius = new QSpinBox(groupBox);
        sb_radius->setObjectName(QStringLiteral("sb_radius"));
        sb_radius->setGeometry(QRect(80, 230, 81, 22));
        sb_radius->setMinimum(10);
        sb_radius->setValue(20);
        btn_start = new QPushButton(groupBox);
        btn_start->setObjectName(QStringLiteral("btn_start"));
        btn_start->setGeometry(QRect(20, 70, 151, 31));
        sb_angle = new QSpinBox(groupBox);
        sb_angle->setObjectName(QStringLiteral("sb_angle"));
        sb_angle->setGeometry(QRect(80, 270, 81, 22));
        sb_angle->setMinimum(10);
        sb_angle->setValue(10);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 270, 47, 20));
        label_3->setFont(font);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(60, 310, 61, 20));
        label_4->setFont(font);
        lb_left = new QLabel(centralwidget);
        lb_left->setObjectName(QStringLiteral("lb_left"));
        lb_left->setGeometry(QRect(210, 20, 861, 531));
        lb_left->setFrameShape(QFrame::Box);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1077, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Parameters", Q_NULLPTR));
        btn_svg->setText(QApplication::translate("MainWindow", "Open Svg", Q_NULLPTR));
        btn_move->setText(QApplication::translate("MainWindow", "Animate", Q_NULLPTR));
        btn_finish->setText(QApplication::translate("MainWindow", "Finish Draw", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Stoke:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Radius:", Q_NULLPTR));
        btn_start->setText(QApplication::translate("MainWindow", "Start Draw", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Slope:", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "2020/7/7", Q_NULLPTR));
        lb_left->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
