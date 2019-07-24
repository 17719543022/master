#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include "Service/dataanalysis.h"
#include <QMainWindow>
#include <QVector>
#include <QImage>
#include <QTimer>

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(DataAnalysis *dataAnalysis,QWidget *parent = nullptr);
    ~SecondWindow();

private:
    Ui::SecondWindow *ui;

    void OnVideoFrame(const QImage& image,const QVector<QRect>& sFacePst);
    void onImageShowTimeOut();

    QMetaObject::Connection m_frameConnection;
    QTimer *m_imgTimer;
    QMetaObject::Connection m_timerConnection;
    QStringList m_imgPathList;
    int m_curIndex;
};

#endif // SECONDWINDOW_H
