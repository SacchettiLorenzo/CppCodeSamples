#include "flashcardsmainwindow.h"
#include "ui_flashcardsmainwindow.h"
#include <algorithm>
#include <random>
#include <iostream>

FlashCardsMainWindow::FlashCardsMainWindow(QWidget *parent, DBManager* db)
    : QMainWindow(parent),
     ui(new Ui::FlashCardsMainWindow())
{
    ui->setupUi(this);
    this->db = db;
    currentLineIndex = 0;
    connect(ui->nextCardButton, &QToolButton::released, this, &FlashCardsMainWindow::handleNextCardButton);
    connect(ui->previousCardButton, &QToolButton::released, this, &FlashCardsMainWindow::handlePreviousCardButton);
    connect(ui->Submit, &QPushButton::released, this, &FlashCardsMainWindow::submitCorrention);
}

FlashCardsMainWindow::~FlashCardsMainWindow()
{
    delete ui;
}

void FlashCardsMainWindow::setLines(std::vector<Line> p)
{
    this->lines = p;
    auto rd = std::random_device();
    auto rng = std::default_random_engine {rd()};
    std::shuffle(std::begin(lines), std::end(lines),rng);
}



void FlashCardsMainWindow::displayLines()
{
    std::cout << "displayLines()" << std::endl;
    ui->actual_label->setText(this->lines.at(currentLineIndex).italian.c_str());
    ui->actual_count->setText(std::to_string(this->lines.at(currentLineIndex).count).c_str());
    ui->traffic_light->setStyleSheet("background-color: rgb(50, 50, 50);");
    ui->actual_lineEdit->setText("");
     ui->correctAnsware->setText("");

    if(lines.size() > 0 && currentLineIndex > 0){
        ui->previous_label->setText(this->lines.at(currentLineIndex-1).italian.c_str());
    }else{
        ui->previous_label->setText("");
    }


    if(lines.size() >= currentLineIndex+1)
    ui->next_label->setText(this->lines.at(currentLineIndex+1).italian.c_str());
}

void FlashCardsMainWindow::handleNextCardButton()
{
    if(currentLineIndex < lines.size())
    currentLineIndex++;
    displayLines();
}

void FlashCardsMainWindow::handlePreviousCardButton()
{
    if(currentLineIndex > 0)
    currentLineIndex--;
    displayLines();
}

void FlashCardsMainWindow::submitCorrention()
{
    std::string submittedValue = ui->actual_lineEdit->text().toStdString();
    std::cout << (submittedValue.c_str()  == lines.at(currentLineIndex).english.c_str()) << std::endl;
    if(submittedValue  == lines.at(currentLineIndex).english){
    lines.at(currentLineIndex).count++;
    ui->traffic_light->setStyleSheet("background-color: rgb(76, 175, 80);");
    ui->actual_count->setText(std::to_string(lines.at(currentLineIndex).count).c_str());
    db->UpdateRecord(lines.at(currentLineIndex).id, lines.at(currentLineIndex));
    }else{
    ui->traffic_light->setStyleSheet("background-color: rgb(244, 67, 54);");
    ui->correctAnsware->setText(lines.at(currentLineIndex).english.c_str());
    }

}



