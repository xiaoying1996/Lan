#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lan.h"

class Lan : public QMainWindow
{
    Q_OBJECT

public:
    Lan(QWidget *parent = nullptr);
    ~Lan();

private:
    Ui::LanClass ui;
};
