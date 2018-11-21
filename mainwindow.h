#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "method.h"
#include "output.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QSpinBox>
#include <QLabel>
#include <QProgressBar>
#include <QTextBrowser>
#include <QString>
#include <string>
#include <iostream>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_solve_clicked();
    void on_reset_clicked();
    void sop_on_demand();
    void pos_on_demand();

private:
    Output *out;
    QLabel* error;
    QLineEdit *input_terms;
    QPushButton *Solve;
    QPushButton *Clear;
    QSpinBox *spin_box;
    QLabel *l1,*l2,*l3,*l4,*l5,*l6;
    QRadioButton *sop,*pos;
    QProgressBar *pro;
    QTextBrowser *cano,*sop_pos,*process;



};

#endif // MAINWINDOW_H
