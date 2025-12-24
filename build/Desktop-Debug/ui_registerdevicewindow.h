/********************************************************************************
** Form generated from reading UI file 'registerdevicewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDEVICEWINDOW_H
#define UI_REGISTERDEVICEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterDeviceWindow
{
public:
    QWidget *centralwidget;
    QPushButton *registDeviceText;
    QFrame *frame;
    QPushButton *registIPAddressText;
    QLineEdit *registIPAddress;
    QPushButton *registCommunityText;
    QLineEdit *registCommunity;
    QPushButton *registPushButton;
    QPushButton *deletePushButton;
    QTableWidget *routerListTable;
    QPushButton *startPushButton;
    QPushButton *registDeviceText_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *RegisterDeviceWindow)
    {
        if (RegisterDeviceWindow->objectName().isEmpty())
            RegisterDeviceWindow->setObjectName("RegisterDeviceWindow");
        RegisterDeviceWindow->setEnabled(true);
        RegisterDeviceWindow->resize(470, 642);
        centralwidget = new QWidget(RegisterDeviceWindow);
        centralwidget->setObjectName("centralwidget");
        registDeviceText = new QPushButton(centralwidget);
        registDeviceText->setObjectName("registDeviceText");
        registDeviceText->setGeometry(QRect(20, 20, 141, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Cantarell")});
        font.setPointSize(13);
        font.setBold(true);
        registDeviceText->setFont(font);
        registDeviceText->setStyleSheet(QString::fromUtf8("color:rgb(94, 92, 100);\n"
"border:none;"));
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(30, 60, 411, 111));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        registIPAddressText = new QPushButton(frame);
        registIPAddressText->setObjectName("registIPAddressText");
        registIPAddressText->setGeometry(QRect(30, 20, 71, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Cantarell Light")});
        font1.setPointSize(10);
        font1.setBold(true);
        registIPAddressText->setFont(font1);
        registIPAddressText->setStyleSheet(QString::fromUtf8("color:rgb(94, 92, 100);\n"
"border:none;"));
        registIPAddress = new QLineEdit(frame);
        registIPAddress->setObjectName("registIPAddress");
        registIPAddress->setGeometry(QRect(110, 20, 161, 31));
        registCommunityText = new QPushButton(frame);
        registCommunityText->setObjectName("registCommunityText");
        registCommunityText->setGeometry(QRect(20, 60, 81, 31));
        registCommunityText->setFont(font1);
        registCommunityText->setStyleSheet(QString::fromUtf8("color:rgb(94, 92, 100);\n"
"border:none;"));
        registCommunity = new QLineEdit(frame);
        registCommunity->setObjectName("registCommunity");
        registCommunity->setGeometry(QRect(110, 60, 161, 31));
        registPushButton = new QPushButton(frame);
        registPushButton->setObjectName("registPushButton");
        registPushButton->setGeometry(QRect(310, 20, 71, 31));
        QFont font2;
        font2.setPointSize(10);
        registPushButton->setFont(font2);
        deletePushButton = new QPushButton(frame);
        deletePushButton->setObjectName("deletePushButton");
        deletePushButton->setGeometry(QRect(310, 60, 71, 31));
        deletePushButton->setFont(font2);
        routerListTable = new QTableWidget(centralwidget);
        if (routerListTable->columnCount() < 2)
            routerListTable->setColumnCount(2);
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(false);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font3);
        routerListTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font3);
        routerListTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        routerListTable->setObjectName("routerListTable");
        routerListTable->setGeometry(QRect(30, 240, 411, 351));
        QFont font4;
        font4.setPointSize(9);
        routerListTable->setFont(font4);
        routerListTable->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        routerListTable->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        routerListTable->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        routerListTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        routerListTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        routerListTable->horizontalHeader()->setDefaultSectionSize(205);
        routerListTable->horizontalHeader()->setStretchLastSection(true);
        routerListTable->verticalHeader()->setVisible(false);
        startPushButton = new QPushButton(centralwidget);
        startPushButton->setObjectName("startPushButton");
        startPushButton->setGeometry(QRect(340, 200, 101, 31));
        startPushButton->setFont(font2);
        registDeviceText_2 = new QPushButton(centralwidget);
        registDeviceText_2->setObjectName("registDeviceText_2");
        registDeviceText_2->setGeometry(QRect(30, 200, 141, 41));
        registDeviceText_2->setFont(font);
        registDeviceText_2->setStyleSheet(QString::fromUtf8("color:rgb(94, 92, 100);\n"
"border:none;"));
        RegisterDeviceWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RegisterDeviceWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 470, 23));
        RegisterDeviceWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(RegisterDeviceWindow);
        statusbar->setObjectName("statusbar");
        RegisterDeviceWindow->setStatusBar(statusbar);

        retranslateUi(RegisterDeviceWindow);

        QMetaObject::connectSlotsByName(RegisterDeviceWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RegisterDeviceWindow)
    {
        RegisterDeviceWindow->setWindowTitle(QCoreApplication::translate("RegisterDeviceWindow", "\354\236\245\353\271\204\354\240\225\353\263\264\353\223\261\353\241\235", nullptr));
        registDeviceText->setText(QCoreApplication::translate("RegisterDeviceWindow", "\353\235\274\354\232\260\355\204\260 \354\240\225\353\263\264 \353\223\261\353\241\235", nullptr));
        registIPAddressText->setText(QCoreApplication::translate("RegisterDeviceWindow", "IP Address", nullptr));
        registCommunityText->setText(QCoreApplication::translate("RegisterDeviceWindow", "Community", nullptr));
        registPushButton->setText(QCoreApplication::translate("RegisterDeviceWindow", "\353\223\261\353\241\235", nullptr));
        deletePushButton->setText(QCoreApplication::translate("RegisterDeviceWindow", " \354\202\255\354\240\234", nullptr));
        QTableWidgetItem *___qtablewidgetitem = routerListTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("RegisterDeviceWindow", "IP \354\243\274\354\206\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = routerListTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("RegisterDeviceWindow", "Community", nullptr));
        startPushButton->setText(QCoreApplication::translate("RegisterDeviceWindow", "\354\213\234\354\236\221", nullptr));
        registDeviceText_2->setText(QCoreApplication::translate("RegisterDeviceWindow", "\353\252\250\353\213\210\355\204\260\353\247\201 \354\236\245\353\271\204 \354\204\240\355\203\235", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDeviceWindow: public Ui_RegisterDeviceWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDEVICEWINDOW_H
