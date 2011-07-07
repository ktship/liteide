/**************************************************************************
** This file is part of LiteIDE
**
** Copyright (c) 2011 LiteIDE Team. All rights reserved.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or (at your option) any later version.
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
**
** In addition, as a special exception,  that plugins developed for LiteIDE,
** are allowed to remain closed sourced and can be distributed under any license .
** These rights are included in the file LGPL_EXCEPTION.txt in this package.
**
**************************************************************************/
// Module: golangdoc.h
// Creator: visualfc <visualfc@gmail.com>
// date: 2011-7-7
// $Id: golangdoc.h,v 1.0 2011-7-7 visualfc Exp $

#ifndef GOLANGDOC_H
#define GOLANGDOC_H

#include "liteapi.h"
#include <QUrl>
#include <QModelIndex>

class QLabel;
class QListView;
class QStringListModel;
class QComboBox;
class QPushButton;
class ProcessEx;
class DocumentBrowser;
class GolangDoc : public QObject
{
    Q_OBJECT
public:
    explicit GolangDoc(LiteApi::IApplication *app, QObject *parent = 0);
    ~GolangDoc();
signals:

public slots:
    void findPackage(QString);
    void findOutput(QByteArray,bool);
    void findFinish(bool,int,QString);
    void anchorClicked(QUrl);
    void doubleClockedLog(QModelIndex);
    void clearRecentPackages();
protected:
    LiteApi::IApplication   *m_liteApp;
    QWidget *m_widget;
    QStringListModel *m_logModel;
    QListView *m_logListView;
    QComboBox *m_findComboBox;
    ProcessEx  *m_process;
    DocumentBrowser *m_browser;
    QAction *m_browserAct;
    QLabel  *m_resultLabel;
    QString m_findText;
    QString m_goroot;
    QStringList m_logPackage;
    QByteArray  m_findData;
    QByteArray  m_templateData;
};

#endif // GOLANGDOC_H