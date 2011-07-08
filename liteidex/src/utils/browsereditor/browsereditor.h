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
// Module: browsereditor.h
// Creator: visualfc <visualfc@gmail.com>
// date: 2011-3-26
// $Id: browsereditor.h,v 1.0 2011-5-12 visualfc Exp $

#ifndef BROWSEREDITOR_H
#define BROWSEREDITOR_H

#include "browsereditorimpl.h"

class BrowserEditor : public BrowserEditorImpl
{
    Q_OBJECT
public:
    BrowserEditor();
    virtual QWidget *widget();
    virtual QString displayName() const;
    virtual QIcon icon() const;
    void setWidget(QWidget *w);
    void setDisplayName(const QString &name);
    void setIcon(const QIcon &icon);
protected:
    QWidget *m_widget;
    QString  m_displayName;
    QIcon    m_icon;
};

#endif //BROWSEREDITOR_H