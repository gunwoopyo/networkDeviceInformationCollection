/********************************************************************************
** Form generated from reading UI file 'routingtablewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROUTINGTABLEWINDOW_H
#define UI_ROUTINGTABLEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RoutingTableWindow
{
public:
    QWidget *centralwidget;
    QFrame *titleFrame;
    QLabel *titleText;
    QLabel *subtitleText;
    QFrame *interfaceFrame;
    QLabel *interfaceText;
    QTableWidget *routingTable;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *RoutingTableWindow)
    {
        if (RoutingTableWindow->objectName().isEmpty())
            RoutingTableWindow->setObjectName("RoutingTableWindow");
        RoutingTableWindow->resize(823, 418);
        centralwidget = new QWidget(RoutingTableWindow);
        centralwidget->setObjectName("centralwidget");
        titleFrame = new QFrame(centralwidget);
        titleFrame->setObjectName("titleFrame");
        titleFrame->setGeometry(QRect(30, 30, 761, 51));
        titleFrame->setFrameShape(QFrame::Shape::StyledPanel);
        titleFrame->setFrameShadow(QFrame::Shadow::Raised);
        titleText = new QLabel(titleFrame);
        titleText->setObjectName("titleText");
        titleText->setGeometry(QRect(10, -20, 331, 71));
        QFont font;
        font.setFamilies({QString::fromUtf8("Cantarell Extra Bold")});
        font.setPointSize(15);
        font.setBold(true);
        titleText->setFont(font);
        titleText->setStyleSheet(QString::fromUtf8("color:rgb(94, 92, 100);"));
        subtitleText = new QLabel(titleFrame);
        subtitleText->setObjectName("subtitleText");
        subtitleText->setGeometry(QRect(10, 10, 151, 51));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Cantarell")});
        font1.setPointSize(14);
        font1.setBold(true);
        subtitleText->setFont(font1);
        subtitleText->setStyleSheet(QString::fromUtf8("color:rgb(94, 92, 100);\n"
""));
        interfaceFrame = new QFrame(centralwidget);
        interfaceFrame->setObjectName("interfaceFrame");
        interfaceFrame->setGeometry(QRect(30, 100, 761, 251));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Cantarell")});
        font2.setPointSize(9);
        interfaceFrame->setFont(font2);
        interfaceFrame->setFrameShape(QFrame::Shape::StyledPanel);
        interfaceFrame->setFrameShadow(QFrame::Shadow::Raised);
        interfaceText = new QLabel(interfaceFrame);
        interfaceText->setObjectName("interfaceText");
        interfaceText->setGeometry(QRect(10, 0, 71, 21));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Cantarell Extra Bold")});
        font3.setPointSize(9);
        font3.setBold(true);
        interfaceText->setFont(font3);
        interfaceText->setStyleSheet(QString::fromUtf8("color:rgb(94, 92, 100);"));
        routingTable = new QTableWidget(interfaceFrame);
        if (routingTable->columnCount() < 4)
            routingTable->setColumnCount(4);
        QFont font4;
        font4.setPointSize(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font4);
        routingTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font4);
        routingTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font4);
        routingTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font4);
        routingTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        routingTable->setObjectName("routingTable");
        routingTable->setGeometry(QRect(0, 20, 761, 231));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Cantarell")});
        font5.setPointSize(9);
        font5.setBold(false);
        routingTable->setFont(font5);
        routingTable->setStyleSheet(QString::fromUtf8("color:rgb(94, 92, 100);"));
        routingTable->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        routingTable->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        routingTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        routingTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        routingTable->horizontalHeader()->setDefaultSectionSize(190);
        routingTable->verticalHeader()->setVisible(false);
        routingTable->verticalHeader()->setMinimumSectionSize(25);
        routingTable->verticalHeader()->setDefaultSectionSize(25);
        routingTable->verticalHeader()->setHighlightSections(true);
        RoutingTableWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RoutingTableWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 823, 23));
        RoutingTableWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(RoutingTableWindow);
        statusbar->setObjectName("statusbar");
        RoutingTableWindow->setStatusBar(statusbar);

        retranslateUi(RoutingTableWindow);

        QMetaObject::connectSlotsByName(RoutingTableWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RoutingTableWindow)
    {
        RoutingTableWindow->setWindowTitle(QCoreApplication::translate("RoutingTableWindow", " \353\235\274\354\232\260\355\214\205 \355\205\214\354\235\264\353\270\224", nullptr));
        titleText->setText(QCoreApplication::translate("RoutingTableWindow", "Network Monitoring System  ", nullptr));
        subtitleText->setText(QCoreApplication::translate("RoutingTableWindow", "Netman_labs", nullptr));
        interfaceText->setText(QCoreApplication::translate("RoutingTableWindow", "\353\235\274\354\232\260\355\214\205 \355\205\214\354\235\264\353\270\224", nullptr));
        QTableWidgetItem *___qtablewidgetitem = routingTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("RoutingTableWindow", "\353\252\251\354\240\201\354\247\200 IP \354\243\274\354\206\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = routingTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("RoutingTableWindow", "\354\204\234\353\270\214\353\204\267 \353\247\210\354\212\244\355\201\254", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = routingTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("RoutingTableWindow", "\355\217\254\355\212\270 \353\262\210\355\230\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = routingTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("RoutingTableWindow", "\353\213\244\354\235\214 \355\231\211 IP \354\243\274\354\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RoutingTableWindow: public Ui_RoutingTableWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROUTINGTABLEWINDOW_H
