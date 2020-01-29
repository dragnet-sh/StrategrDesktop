#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QTime>
#include <QWidget>
#include <QLocale>
#include <QGuiApplication>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>

#include "Rect.hpp"

/* TimeUtils */

QString humanTimeForMinutes(int mins);

int minutesFromQTime(const QTime &time);

QTime QTimeFromMinutes(int minutes);
QString QStringForMinutes(int minutes);

int currentMinutes();
int currentSeconds();

/* Widgets */
template<class T>
T *findParentWidget(QWidget *childWidget) {
    auto *widget = childWidget->parentWidget();
    while (widget) {
        auto *mainScene = qobject_cast<T *>(widget);
        if (mainScene) {
            return mainScene;
        } else {
            widget = widget->parentWidget();
        }
    }

    return nullptr;
}

double devicePixelRatio();

stg::Rect RectFromQRect(const QRect &rect);

/* Strings */
namespace StringUtils {
    QString toSentenceCase(QString string);
}

/* Multithreading */

void dispatchToMainThread(const std::function<void()> &callback);

#endif // UTILS_H
