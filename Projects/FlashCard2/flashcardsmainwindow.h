#pragma once
#include "Line.h"
#include "DBManager.h"
#include <iostream>

#ifndef FLASHCARDSMAINWINDOW_H
#define FLASHCARDSMAINWINDOW_H

#include <QMainWindow>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class FlashCardsMainWindow; }
QT_END_NAMESPACE

class FlashCardsMainWindow : public QMainWindow
{
    Q_OBJECT
    std::vector<Line> lines;
    int currentLineIndex;
    DBManager* db;


public:
    FlashCardsMainWindow(QWidget *parent = nullptr,DBManager* db = nullptr);
    ~FlashCardsMainWindow();
    void setLines(std::vector<Line> p);
    void displayLines();
    void handleNextCardButton();
    void handlePreviousCardButton();
    void submitCorrention();

private:
    Ui::FlashCardsMainWindow *ui;
};
#endif // FLASHCARDSMAINWINDOW_H
