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

#include "mainwidget.h"

#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(
                QTextCodec::codecForName("UTF-8"));

#ifdef Q_OS_WIN
    a.setFont(QFont("Microsoft YaHei",9));
#endif

    MainWidget w;
    w.show();

    return a.exec();
}
