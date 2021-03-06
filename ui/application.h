//
// Created by Dmitry Khrykin on 2019-07-15.
//

#ifndef STRATEGR_APPLICATION_H
#define STRATEGR_APPLICATION_H

#include <QApplication>
#include <QFileOpenEvent>
#include <QtDebug>
#include <QTimer>
#include <QSystemTrayIcon>

#include "aboutwindow.h"
#include "mainwindow.h"

#ifdef Q_OS_MAC
Q_FORWARD_DECLARE_OBJC_CLASS(CocoaDelegate);
#endif

class Application : public QApplication {
public:
    Application(int &argc, char **argv);
    ~Application() override;

    static QStringList openedFiles;
    static AboutWindow *aboutWindow;
    static QSystemTrayIcon *trayIcon;

    static void registerOpenedFile(const QString &filePath);
    static void clearRecentFiles();
    static void markFileClosed(const QString &filePath);
    static bool fileIsOpened(const QString &filePath);
    static void checkForUpdates();
private:
    static void setupFonts();

    bool launchedByOpenEvent = false;

#ifdef Q_OS_MAC

    static CocoaDelegate *cocoaDelegate;
    static void registerCocoaRecentFile(const QString &filePath);
    static void clearCocoaRecentFiles();

    void setupCocoaDelegate();
    void releaseCocoaDelegate();

#endif

    bool event(QEvent *event) override;
};

#endif //STRATEGR_APPLICATION_H
