/*
 * Copyright (C) 2019 Tianjin KYLIN Information Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
 *
 */

#include "letterbuttonwidget.h"
#include "ui_letterbuttonwidget.h"
#include "src/Style/style.h"
#include "letterwidget.h"
#include <QDebug>

LetterButtonWidget::LetterButtonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LetterButtonWidget)
{
    ui->setupUi(this);
    initWidget();
}

LetterButtonWidget::~LetterButtonWidget()
{
    delete ui;
}

void LetterButtonWidget::initWidget()
{
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("border:0px;background:transparent;");
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    this->setFixedSize(320,500);

    gridLayout=new QGridLayout(this);
    gridLayout->setContentsMargins(15,0,6,this->height()-48*6);
    gridLayout->setSpacing(5);
    this->setLayout(gridLayout);

    char btncolor[400];
    sprintf(btncolor,"QToolButton{background:transparent;color:#ffffff;font-size:20px;padding-left:0px;}\
            QToolButton:hover{background-color:%s;color:#ffffff;font-size:20px;}\
            QToolButton:pressed{background-color:%s;color:#ffffff;font-size:20px;}\
            QToolButton:disabled{color:rgba(255, 255, 255, 0.25);}", ClassifyBtnHoverBackground,ClassifyBtnHoverBackground);

    QStringList letterlist;
    letterlist.clear();
    for(int i=0;i<26;i++)
    {
        char letter=static_cast<char>(65+i);
        letterlist.append(QString(QChar(letter)));
    }
    letterlist.append("&&");
    letterlist.append("#");

    for(int row=0;row<6;row++)
    {
        for(int col=0;col<5;col++)
        {
            if(row*5+col<letterlist.size())
            {
                QToolButton* btn=new QToolButton(this);
                btn->setFixedSize(55,48);
                btn->setStyleSheet(QString::fromLocal8Bit(btncolor));
                btn->setText(letterlist.at(row*5+col));
                gridLayout->addWidget(btn,row,col);
                connect(btn, SIGNAL(clicked()), this, SLOT(letterBtnClickedSlot()));
            }
            else {
                break;
            }
        }
    }
}

/**
 * 字母分类按钮槽函数
 */
void LetterButtonWidget::letterBtnClickedSlot()
{
    QToolButton* btn=dynamic_cast<QToolButton *>(QObject::sender());
    QString btnname=btn->text();
    Q_EMIT sendLetterBtnSignal(btnname);
}

/**
 * 接收LetterWidget字母按钮列表
 */
void LetterButtonWidget::recvLetterBtnList(QStringList list)
{
    for(int row=0;row<6;row++)
    {
        for(int col=0;col<5;col++)
        {
            QLayoutItem* item=gridLayout->itemAt(row*5+col);
            QToolButton* btn=static_cast<QToolButton*>(item->widget());
            QString letterstr=btn->text();
            if(list.indexOf(letterstr.at(0))==-1)
                btn->setEnabled(false);

            if(row*5+col==27) break;
        }
    }
}
