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
    connect(ui->actionPrint, &QAction::triggered, this, &Notepad::onActionPrint);

    connect(ui->actionExit, &QAction::triggered, [=](){
        QApplication::quit();
    });
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

void Notepad::onActionPrint()
{
    QPrinter printer;
    QPrintDialog pDialog(&printer, this);
    pDialog.open();
    if(pDialog.result() == QDialog::Rejected)
    {
        return;
    }
    ui->textEdit->print(&printer);
}

void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}
