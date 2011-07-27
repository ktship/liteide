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
// Module: editormanager.h
// Creator: visualfc <visualfc@gmail.com>
// date: 2011-3-26
// $Id: editormanager.h,v 1.0 2011-5-12 visualfc Exp $

#ifndef EDITORMANAGER_H
#define EDITORMANAGER_H

#include "../liteapi/liteapi.h"
#include <QPointer>

using namespace LiteApi;

class LiteTabWidget;
class QStackedWidget;

class EditorManager : public IEditorManager
{
    Q_OBJECT
public:
    ~EditorManager();
    virtual bool initWithApp(IApplication *app);
public:
    virtual IEditor *openEditor(const QString &fileName, const QString &mimeType);
    virtual void addFactory(IEditorFactory *factory);
    virtual void removeFactory(IEditorFactory *factory);
    virtual QList<IEditorFactory*>  factoryList() const;
    virtual QStringList mimeTypeList() const;
public:
    virtual QWidget *widget();
    virtual IEditor *currentEditor() const;
    virtual void setCurrentEditor(IEditor *editor);
    virtual QList<IEditor*> editorList() const;
    virtual void addEditor(IEditor *editor);
    virtual QAction *registerBrowser(IEditor *editor);
    virtual void activeBrowser(IEditor *editor);
public:
    QList<IEditor*> sortedEditorList() const;
public slots:
    virtual bool saveEditor(IEditor *editor = 0);
    virtual bool saveEditorAs(IEditor *editor = 0);
    virtual bool saveAllEditors();
    virtual bool closeEditor(IEditor *editor = 0);
    virtual bool closeAllEditors(bool autoSaveAll = false);
signals:
    void tabAddRequest();
protected:    
    QWidget      *m_widget;
    LiteTabWidget *m_editorTabWidget;
    QMap<QWidget *, IEditor *> m_widgetEditorMap;
    QPointer<IEditor> m_currentEditor;
    QList<IEditorFactory*>    m_factoryList;
    QMap<IEditor*,QAction*>   m_browserActionMap;
 protected slots:
    void editorTabChanged(int);
    void editorTabCloseRequested(int);
    void modificationChanged(bool);
    void toggleBrowserAction(bool);
};

#endif // EDITORMANAGER_H
