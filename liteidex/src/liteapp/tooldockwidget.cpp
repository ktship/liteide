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
// Module: tooldockwidget.cpp
// Creator: visualfc <visualfc@gmail.com>
// date: 2012-9-12
// $Id: tooldockwidget.cpp,v 1.0 2012-9-12 visualfc Exp $

#include "tooldockwidget.h"
#include <QAction>
#include <QIcon>
#include <QLabel>
#include <QHBoxLayout>
#include <QVariant>
#include <QMenu>
#include <QToolButton>
#include <QDebug>

ToolDockWidget::ToolDockWidget(QWidget *parent) :
    QDockWidget(parent), current(0)
{
    m_comboBox = new QComboBox;
    m_comboBox->setMinimumContentsLength(4);
    m_comboBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    m_toolbar = new QToolBar(this);
    m_toolbar->setContentsMargins(0, 0, 0, 0);
    m_toolbar->setIconSize(QSize(15,16));
    m_toolbar->addWidget(m_comboBox);

    QWidget *spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_toolbar->addSeparator();
    m_spacerAct = m_toolbar->addWidget(spacer);

    m_toolbar->addSeparator();

    m_closeAct = new QAction(tr("Close"), m_toolbar);
    m_closeAct->setToolTip(tr("Close"));
    m_closeAct->setIcon(QIcon("icon:images/closetool.png"));
    m_toolbar->addAction(m_closeAct);
    connect(m_closeAct,SIGNAL(triggered()),this,SLOT(close()));
    connect(m_comboBox,SIGNAL(activated(int)),this,SLOT(activeComboBoxIndex(int)));

    this->setTitleBarWidget(m_toolbar);

    m_toolbar->setStyleSheet("QToolBar {border:1 ; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #EEEEEE, stop: 1 #ababab); color : #EEEEEE}");
}

void ToolDockWidget::createMenu(Qt::DockWidgetArea area, bool split)
{
    QMenu *moveMenu = new QMenu(tr("Move To"),this);
    if (area != Qt::TopDockWidgetArea) {
        QAction *act = new QAction(tr("Top"),this);
        act->setData(Qt::TopDockWidgetArea);
        moveMenu->addAction(act);
        connect(act,SIGNAL(triggered()),this,SLOT(moveAction()));
        QAction *act1 = new QAction(tr("Top : Split"),this);
        act1->setData(Qt::TopDockWidgetArea);
        moveMenu->addAction(act1);
        connect(act1,SIGNAL(triggered()),this,SLOT(moveActionSplit()));
    }
    if (area != Qt::BottomDockWidgetArea) {
        QAction *act = new QAction(tr("Bottom"),this);
        act->setData(Qt::BottomDockWidgetArea);
        moveMenu->addAction(act);
        connect(act,SIGNAL(triggered()),this,SLOT(moveAction()));
        QAction *act1 = new QAction(tr("Bottom : Split"),this);
        act1->setData(Qt::BottomDockWidgetArea);
        moveMenu->addAction(act1);
        connect(act1,SIGNAL(triggered()),this,SLOT(moveActionSplit()));
    }
    if (area != Qt::LeftDockWidgetArea) {
        QAction *act = new QAction(tr("Left"),this);
        act->setData(Qt::LeftDockWidgetArea);
        moveMenu->addAction(act);
        connect(act,SIGNAL(triggered()),this,SLOT(moveAction()));
        QAction *act1 = new QAction(tr("Left : Split"),this);
        act1->setData(Qt::LeftDockWidgetArea);
        moveMenu->addAction(act1);
        connect(act1,SIGNAL(triggered()),this,SLOT(moveActionSplit()));
    }
    if (area != Qt::RightDockWidgetArea) {
        QAction *act = new QAction(tr("Right"),this);
        act->setData(Qt::RightDockWidgetArea);
        moveMenu->addAction(act);
        connect(act,SIGNAL(triggered()),this,SLOT(moveAction()));
        QAction *act1 = new QAction(tr("Right : Split"),this);
        act1->setData(Qt::RightDockWidgetArea);
        moveMenu->addAction(act1);
        connect(act1,SIGNAL(triggered()),this,SLOT(moveActionSplit()));
    }

    QMenu *menu = new QMenu;
    if (split) {
        QAction *unsplitAct = new QAction(tr("UnSplit"),this);
        unsplitAct->setData(area);
        connect(unsplitAct,SIGNAL(triggered()),this,SLOT(unsplitAction()));
        menu->addAction(unsplitAct);
    } else {
        QAction *splitAct = new QAction(tr("Split"),this);
        splitAct->setData(area);
        connect(splitAct,SIGNAL(triggered()),this,SLOT(splitAction()));
        menu->addAction(splitAct);
    }
    menu->addAction(moveMenu->menuAction());

    QToolButton *btn = new QToolButton;
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setIcon(QIcon("icon:images/movemenu.png"));
    btn->setMenu(menu);
    btn->setToolTip(tr("Move To"));
    btn->setStyleSheet("QToolButton::menu-indicator {image: none;}");

   m_toolbar->insertWidget(m_closeAct,btn);
}

void ToolDockWidget::moveAction()
{
    QAction *action = static_cast<QAction*>(sender());
    if (!action) {
        return;
    }
    Qt::DockWidgetArea area = (Qt::DockWidgetArea)action->data().toInt();
    emit moveActionTo(area,current,false);
}

void ToolDockWidget::moveActionSplit()
{
    QAction *action = static_cast<QAction*>(sender());
    if (!action) {
        return;
    }
    Qt::DockWidgetArea area = (Qt::DockWidgetArea)action->data().toInt();
    emit moveActionTo(area,current,true);
}

void ToolDockWidget::splitAction()
{
    QAction *action = static_cast<QAction*>(sender());
    if (!action) {
        return;
    }
    Qt::DockWidgetArea area = (Qt::DockWidgetArea)action->data().toInt();
    emit moveActionTo(area,current,true);
}

void ToolDockWidget::unsplitAction()
{
    QAction *action = static_cast<QAction*>(sender());
    if (!action) {
        return;
    }
    Qt::DockWidgetArea area = (Qt::DockWidgetArea)action->data().toInt();
    emit moveActionTo(area,current,false);
}


void ToolDockWidget::setWindowTitle(const QString &text)
{
    QDockWidget::setWindowTitle(text);
}

QAction *ToolDockWidget::addWidget(QWidget *widget)
{
   return m_toolbar->insertWidget(m_closeAct,widget);
}

void ToolDockWidget::setToolMenu(QMenu *menu)
{
    QToolButton *btn = new QToolButton;
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setMenu(menu);

    m_toolbar->insertWidget(m_closeAct,btn);
}

void ToolDockWidget::setWidgetActions(QList<QAction*> actions)
{
    foreach(QAction *action, m_widgetActions) {
        m_toolbar->removeAction(action);
    }
    m_widgetActions = actions;
    foreach(QAction *action, m_widgetActions) {
        m_toolbar->insertAction(m_spacerAct,action);
    }
}

QList<QAction *> ToolDockWidget::actions() const
{
    return m_actions;
}

void ToolDockWidget::removeAction(QAction *action)
{
    if (m_actions.removeAll(action)) {
        if (action == current)
            current = 0;
        int index = m_comboBox->findData((int)action);
        if (index >= 0) {
            m_comboBox->removeItem(index);
        }
        QObject::disconnect(action, SIGNAL(changed()), this, SLOT(actionChanged()));
    }
}

QAction * ToolDockWidget::checkedAction () const
{
    return current;
}

void ToolDockWidget::actionChanged()
{
    QAction *action = qobject_cast<QAction*>(sender());
    Q_ASSERT_X(action != 0, "ActionGroup::actionChanged", "internal error");
    if (action->isChecked()) {
        if (action != current) {
            if(current)
                current->setChecked(false);
            current = action;
            int index = m_comboBox->findData((int)action);
            if (index >= 0) {
                m_comboBox->setCurrentIndex(index);
            }
        }
    } else if (action == current) {
        current = 0;
    }
}

void ToolDockWidget::activeComboBoxIndex(int index)
{
    if (index < 0 || index >= m_comboBox->count()) {
        return;
    }
    bool ok;
    QAction *action =(QAction*)m_comboBox->itemData(index).toInt(&ok);
    if (action && !action->isChecked()) {
        action->setChecked(true);
    }
}

void ToolDockWidget::addAction(QAction *action, const QString &title)
{
    if(!m_actions.contains(action)) {
        m_actions.append(action);
        m_comboBox->addItem(title,QVariant((int)action));
        QObject::connect(action, SIGNAL(changed()), this, SLOT(actionChanged()));
    }
    if (current && current->isChecked()) {
        current->setChecked(false);
    }
    if (action->isChecked()) {
        current = action;
    }
}

