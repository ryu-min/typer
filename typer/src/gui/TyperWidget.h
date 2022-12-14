#pragma once

#include "TextEditRenderer.h"

#include <QWidget>
#include <QTextEdit>
#include <QDebug>
#include <QKeyEvent>

namespace typer
{
    namespace gui
    {

        class TyperTextEdit : public QTextEdit
        {
        public:
            TyperTextEdit( QWidget * parent = nullptr )
                : QTextEdit( parent ) {
                setReadOnly(true);
                setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            }

            void showEvent(QShowEvent * event) override {
                setFocus();
                QTextEdit::showEvent(event);
            }

            void keyPressEvent(QKeyEvent *event) override {
                setReadOnly(false);
                QTextEdit::keyPressEvent(event);
                setReadOnly(true);
            }
        };

        class TyperWidget : public QWidget
        {
            Q_OBJECT
        public:
            TyperWidget( QWidget * parent = nullptr);

        signals:
            void exit();

        private:
            void buildForm();

        private:
            TextEditRenderer * m_textRenderer;
        };
    }
}


