#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "include/dialoglidar.h"
#include "include/controlform.h"
#include <QScrollArea>
#include <QWheelEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    DialogLidar *m_dialogLidar[50];
    ControlForm *m_controlForm;

    void wheelEvent(QWheelEvent *event);

private slots:
    void sl_control_loopStart(int nums);

    void sl_control_loopStop(int nums);

    void sl_control_reset(int nums);

    void on_action_triggered();

private:
    Ui::MainWindow *ui;
    QScrollArea *scrollArea;
};

#endif // MAINWINDOW_H
