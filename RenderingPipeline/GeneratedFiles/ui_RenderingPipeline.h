/********************************************************************************
** Form generated from reading UI file 'RenderingPipeline.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERINGPIPELINE_H
#define UI_RENDERINGPIPELINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RenderingPipelineClass
{
public:

    void setupUi(QWidget *RenderingPipelineClass)
    {
        if (RenderingPipelineClass->objectName().isEmpty())
            RenderingPipelineClass->setObjectName(QStringLiteral("RenderingPipelineClass"));
        RenderingPipelineClass->resize(600, 400);
        RenderingPipelineClass->setMaximumSize(QSize(16777215, 16777215));

        retranslateUi(RenderingPipelineClass);

        QMetaObject::connectSlotsByName(RenderingPipelineClass);
    } // setupUi

    void retranslateUi(QWidget *RenderingPipelineClass)
    {
        RenderingPipelineClass->setWindowTitle(QApplication::translate("RenderingPipelineClass", "RenderingPipeline", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RenderingPipelineClass: public Ui_RenderingPipelineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERINGPIPELINE_H
