#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)

{
    out = new Output;
    error = new QLabel(this);
    error->move(190,50);
    error->resize(150,20);

    l1 = new QLabel(this);
    l2 = new QLabel(this);
    l3 = new QLabel(this);
    l4 = new QLabel(this);
    l5 = new QLabel(this);
    l6 = new QLabel(this);
    l1->setText("Min Terms");
    l2->setText("Output Form");
    l3->setText("Number of variables");
    l4->setText("Canonical");
    l5->setText("SOP/POS");
    l6->setText("Process");
    l1->setGeometry(QRect(QPoint(20,20),QSize(61,21)));
    l2->setGeometry(QRect(QPoint(20,50),QSize(61,21)));
    l3->setGeometry(QRect(QPoint(346,50),QSize(101,20)));
    l4->setGeometry(QRect(QPoint(30,160),QSize(47,13)));
    l5->setGeometry(QRect(QPoint(30,220),QSize(47,13)));
    l6->setGeometry(QRect(QPoint(30,280),QSize(47,13)));

    input_terms = new QLineEdit(this);
    input_terms->setPlaceholderText("Enter min terms (separated by space)");
    input_terms->setGeometry(QRect(QPoint(90,20),QSize(421,20)));

    Solve = new QPushButton(this);
    Solve->setText("Minimize");
    Solve->setGeometry(QRect(QPoint(90,90),QSize(75,23)));

    Clear = new QPushButton(this);
    Clear->setText("Reset");
    Clear->setGeometry(QRect(QPoint(180,90),QSize(75,23)));

    spin_box = new QSpinBox(this);
    spin_box->setGeometry(QRect(QPoint(461,50),QSize(51,22)));
    spin_box->setRange(2,6);
    spin_box->setValue(4);


    pro = new QProgressBar(this);
    pro->setGeometry(QRect(QPoint(290,90),QSize(221,23)));
    pro->setValue(0);

    cano = new QTextBrowser(this);
    cano->setGeometry(QRect(QPoint(90,160),QSize(421,41)));

    sop_pos = new QTextBrowser(this);
    sop_pos->setGeometry(QRect(QPoint(90,220),QSize(421,41)));

    process = new QTextBrowser(this);
    process->setGeometry(QRect(QPoint(90,280),QSize(421,141)));

    sop = new QRadioButton(this);
    sop->setGeometry(QRect(QPoint(90,50),QSize(51,17)));
    sop->setText("SOP");
    sop->setChecked(true); // default option

    pos = new QRadioButton(this);
    pos->setGeometry(QRect(QPoint(150,50),QSize(51,17)));
    pos->setText("POS");

    connect(Solve,SIGNAL(clicked(bool)),this,SLOT(on_solve_clicked()));
    connect(Clear,SIGNAL(clicked(bool)),this,SLOT(on_reset_clicked()));
    connect(sop,SIGNAL(clicked(bool)),this,SLOT(sop_on_demand()));
    connect(pos,SIGNAL(clicked(bool)),this,SLOT(pos_on_demand()));


}
MainWindow::~MainWindow()
{

}

void MainWindow::on_solve_clicked()
{

    int min;
    bool reply;
    min = spin_box->value();
    string user_input = input_terms->text().toStdString();
    pro->show();
    reply =out->getinput(min,user_input);
    if(reply==false)
    {
        error->setText("<font color = #FF0000><H4>Error: Input out of range!!!</H4></font>");
        return;
    }
    pro->setValue(10);
    out->create_table();
    pro->setValue(20);
    out->print_table();
    pro->setValue(30);
    out->create_p_group();
    pro->setValue(40);
    out->print_p_group();
    pro->setValue(50);
    out->create_final_group();
    pro->setValue(70);
    out->print_final_group();
    pro->setValue(80);
    out->finalMinimize();
    pro->setValue(95);
    out->ShowCanonical();
    out->ShowSOP();
    out->ShowPOS();
    pro->setValue(100);
    cano->setText(QString::fromStdString(out->Cano.str()));

    if(sop->isChecked())
        sop_pos->setText(QString::fromStdString(out->SOP.str()));
    else
        sop_pos->setText(QString::fromStdString(out->POS.str()));

    process->setText(QString::fromStdString(out->MainOutput.str()));
}

void MainWindow::sop_on_demand()
{
     sop_pos->clear();
     sop_pos->setText(QString::fromStdString(out->SOP.str()));

}

void MainWindow::pos_on_demand()
{
    sop_pos->clear();
    sop_pos->setText(QString::fromStdString(out->POS.str()));
}

void MainWindow::on_reset_clicked()
{
    out->Reset();
    sop_pos->clear();
    cano->clear();
    process->clear();
    input_terms->clear();
    error->clear();

}
