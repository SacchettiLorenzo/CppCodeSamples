#include "databaseconnection.h"
#include "ui_databaseconnection.h"
#include <thread>

databaseConnection::databaseConnection(QWidget *parent, DBManager* db) :
    QDialog(parent),
    ui(new Ui::databaseConnection)
{
    this->db = db;
    ui->setupUi(this);
    connect(ui->ConnectButton, &QPushButton::clicked ,this, &databaseConnection::dbconnect);
}

databaseConnection::~databaseConnection()
{
    delete ui;
}

void databaseConnection::dbconnect()
{

    DBManager newdb(
        ui->HostLineEdit->text().toStdString().c_str(),
        ui->UsernameLineEdit->text().toStdString().c_str(),
        ui->PasswordLineEdit->text().toStdString().c_str(),
        ui->DatabaseLineEdit->text().toStdString().c_str()
        );
    newdb.SetTable(ui->TableLineEdit->text().toStdString().c_str());

    *db = newdb;

}
