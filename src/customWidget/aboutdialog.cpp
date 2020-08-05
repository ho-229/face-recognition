/* ======================================================================
 * This file is part of the Face-recognition
 * Copyright (C) 2020 Ho 229
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 *
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ======================================================================== */

#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QMessageBox>

#if _MSC_VER >= 1600
    #pragma execution_character_set("utf-8")
#endif

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    this->initUI();
    this->initSignalSlots();
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::initUI()
{
    this->setFixedSize(this->size());
    this->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
}

void AboutDialog::initSignalSlots()
{
    connect(ui->aboutQtBtn,&QPushButton::clicked,
            [this]{ QMessageBox::aboutQt(this); });
}
