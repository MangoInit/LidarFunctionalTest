#ifndef CONTROLFORM_H
#define CONTROLFORM_H

#include <QWidget>
#include <flashgodriver.h>

namespace Ui {
class ControlForm;
}

class ControlForm : public QWidget
{
    Q_OBJECT

public:
    explicit ControlForm(QWidget *parent = nullptr);
    ~ControlForm();
    int nums;

signals:
    void sg_control_start(int nums);

    void sg_control_stop(int nums);

    void sg_control_reset(int nums);

private slots:

    void on_pushButton_loopStart_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_loopStop_clicked();

private:
    Ui::ControlForm *ui;
};

#endif // CONTROLFORM_H
