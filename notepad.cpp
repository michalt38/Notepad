#include "notepad.h"
#include "ui_notepad.h"
#include <QDebug>

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);

    this->setWindowTitle("Untitled");

    connect(ui->actionNew, &QAction::triggered, this, &Notepad::onActionNew);
}

void Notepad::onActionNew()
{
    currentFile.clear();
    ui->textEdit->clear();

    this->setWindowTitle("Untitled");
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::on_actionSave_triggered()
{
    save(currentFile);
}

void Notepad::on_actionSave_as_triggered()
{
    save("");
}

void Notepad::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open file");
    currentFile = fileName;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Error", "Cannot open file: " + file.errorString());
        return;
    }

    this->setWindowTitle(currentFile);

    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());
    file.close();
}

void Notepad::save(QString fileName)
{
    if(fileName.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(this, "Save as");
    }

    QFile file(fileName);
    currentFile = fileName;


    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Error", "Cannot open file: " + file.errorString());
        return;
    }

    this->setWindowTitle(currentFile);

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    file.close();
}

