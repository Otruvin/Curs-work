#include "optionswindow.h"
#include "ui_optionswindow.h"
#include "searchhelper.h"
#include <QMessageBox>

OptionsWindow::OptionsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsWindow)
{
    ui->setupUi(this);

    this->fileHandler = new FileHandler();
    if(!fileHandler->loadCityUser().isEmpty())
    {
        ui->selectedUserCity->setText(fileHandler->loadCityUser());
    }

    this->completerForCityUserField = new QCompleter(SearchHelper::getListWithCities(), this);
    ui->enterUserCity->setCompleter(completerForCityUserField);
}

OptionsWindow::~OptionsWindow()
{
    delete completerForCityUserField;
    delete fileHandler;
    delete ui;
}

void OptionsWindow::on_buttonBox_accepted()
{
    if(!ui->enterUserCity->text().isEmpty())
    {
        fileHandler->saveCityUser(ui->enterUserCity->text());
        ui->selectedUserCity->setText(fileHandler->loadCityUser());
        ui->enterUserCity->clear();
    }
}

void OptionsWindow::on_resetCityUser_clicked()
{
    if(!fileHandler->loadCityUser().isEmpty())
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Подтверждение очистки города и страны пользователя",
                                                                  "Вы действительно хотите сбросить заданные город и страну пользователя?",
                                                                  QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            ui->enterUserCity->clear();
            fileHandler->clearUserCity();
            ui->selectedUserCity->setText("Ваши город и страна не заданы");
        }

    }else
    {
        QMessageBox::information(this, "Ошибка очистки", "Вы питаетесь сбросить город и страну пользователя, которые не заданы");
    }

}
