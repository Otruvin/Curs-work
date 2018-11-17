#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QDialog>
#include "filehandler.h"
#include <QCompleter>

namespace Ui {
class OptionsWindow;
}

class OptionsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsWindow(QWidget *parent = nullptr);
    ~OptionsWindow();

private slots:
    void on_buttonBox_accepted();

    void on_resetCityUser_clicked();

private:
    Ui::OptionsWindow *ui;
    FileHandler *fileHandler;
    QCompleter *completerForCityUserField;
};

#endif // OPTIONSWINDOW_H
