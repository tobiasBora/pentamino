#include <QtGui/QApplication>
#include "pentamino.h"
// #include "mainwindow.h"
#include <QTextCodec>
#include <QDebug>
#include "plateau.h"

int main(int argc, char *argv[])
{
    // Pour l'affichage des chaines sans problème en Utf8 :
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));

    qDebug() << "########################################";
    qDebug() << "#########  Debut de l'application #######";
    qDebug() << "########################################";

    Pentamino *pentamino = new Pentamino();
    // pentamino->lancer();

    // QApplication a(argc, argv);
    // MainWindow w;
    // w.showMaximized();
    
    // return a.exec();
    return 0;
}
