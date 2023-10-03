#pragma once

#include "DBManager.h"
#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <Qdialog.h>

namespace Ui {
class databaseConnection;
}

class databaseConnection : public QDialog
{
    Q_OBJECT;


public:
    explicit databaseConnection(QWidget *parent = nullptr, DBManager* db = nullptr);
    ~databaseConnection();
    void dbconnect();

signals:
    void ConnectButtonPressed(int newValue);

private:
    Ui::databaseConnection *ui;
    DBManager* db;
};

#endif // DATABASECONNECTION_H
