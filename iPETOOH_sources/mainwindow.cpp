#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstring>
#include <fstream>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap run("run.png");
    QIcon runIcon(run);
    ui->toolButton->setIcon(runIcon);
    QPixmap add("new.png");
    QIcon addIcon(add);
    ui->toolButton_2->setIcon(addIcon);
    QPixmap save("save.png");
    QIcon saveIcon(save);
    ui->toolButton_3->setIcon(saveIcon);
    QPixmap open("open.png");
    QIcon openIcon(open);
    ui->toolButton_4->setIcon(openIcon);
    setWindowIcon(QIcon("icon.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_clicked()
{
    std::ofstream cls;
    cls.open("input.koko", std::ofstream::out | std::ofstream::trunc);
    cls.close();
    std::fstream ifs("input.koko");
    QString q = ui->plainTextEdit->toPlainText();
    std::string w = q.toStdString();
    ifs.write(w.c_str(), w.length());
    std::string s((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    s = "xterm -hold -title iPETOOH -e python petooh.py input.koko ";
    system(s.c_str());
}

void MainWindow::on_toolButton_2_clicked()
{
    ui->plainTextEdit->setPlainText("");
}

void MainWindow::on_toolButton_3_clicked()
{
    QFileDialog save(this);
    save.setFileMode(QFileDialog::AnyFile);
    save.setNameFilter(tr("PETOOH files(*.koko)"));
    save.setViewMode(QFileDialog::Detail);
    save.setLabelText(QFileDialog::Accept, "Save");
    save.setWindowTitle("Save File");
    QStringList fileNames;
    if (save.exec()){
        fileNames = save.selectedFiles();
        QString file = fileNames.at(0);
        std::ofstream cls;
        cls.open(file.toStdString() + ".koko", std::ofstream::out | std::ofstream::trunc);
        cls.close();
        std::ofstream s(file.toStdString() + ".koko");
        QString q = ui->plainTextEdit->toPlainText();
        std::string w = q.toStdString();
        s.write(w.c_str(), w.length());
    }
}

void MainWindow::on_toolButton_4_clicked()
{
    QFileDialog open(this);
    open.setFileMode(QFileDialog::AnyFile);
    open.setNameFilter(tr("PETOOH files(*.koko)"));
    open.setViewMode(QFileDialog::Detail);
    open.setWindowTitle("Open File");
    QStringList fileNames;
    if (open.exec()){
        fileNames = open.selectedFiles();
        QString file = fileNames.at(0);
        std::ifstream read(file.toStdString());
        std::string str((std::istreambuf_iterator<char>(read)), std::istreambuf_iterator<char>());
        ui->plainTextEdit->setPlainText(QString::fromStdString(str));
    }
}
