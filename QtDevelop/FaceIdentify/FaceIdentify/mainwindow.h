#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Common/constants.h"
#include "Common/functions.h"
#include "Service/dataanalysis.h"
#include "Service/sqlitedb.h"
#include "secondwindow.h"

#include <QObject>

#include <QMainWindow>
#include <QVector>
#include <QTableWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotItemClicked(QTableWidgetItem * item);

    void on_shutdownBtn_clicked();

    void on_LiveImageBtn_clicked();

    void on_livePushBtn_clicked();

private:
    Ui::MainWindow *ui;

    void OnVideoFrame(const QImage& image,const QVector<QRect>& sFacePst);
    void OnResponseResult(const FIResult& fiResult);
    void OnResponseResultToClient(const FIResult& fiResult);
    void OnResponseResultData(const FIResult& fiResult);

    void ControlInit();

    QMetaObject::Connection m_frameConnection;
    QMetaObject::Connection m_resultConnection;
    QMetaObject::Connection m_resultToClientConnection;
    QMetaObject::Connection m_resultDataConnection;
    QMetaObject::Connection m_itemClickedConnection;

    DataAnalysis* m_dataAnalysis;
    QVector<FIResult> m_fIResultVector;
    QString m_imgFolderPath;
    SecondWindow* m_secondWindow;
    bool m_bIsTwoScreen;
    HttpClient* m_httpClient;
};
#endif // MAINWINDOW_H
