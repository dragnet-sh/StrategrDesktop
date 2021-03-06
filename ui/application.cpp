//
// Created by Dmitry Khrykin on 2019-07-15.
//

#include <QFontDatabase>
#include <QSettings>

#include "application.h"

#ifdef Q_OS_WIN

#include <Windows.h>
#include <winsparkle.h>

#endif

QStringList Application::openedFiles = QStringList();

AboutWindow *Application::aboutWindow = nullptr;

QSystemTrayIcon *Application::trayIcon = nullptr;

Application::Application(int &argc, char **argv)
        : QApplication(argc, argv) {
    QSettings().setProperty("lastLaunchedVersion",
                            ApplicationSettings::version);

    setupFonts();

#ifdef Q_OS_MAC

    setupCocoaDelegate();

#endif

    if (argc == 2) {
        launchedByOpenEvent = true;
        auto filePath = QString(argv[1]);

        auto window = new MainWindow(filePath);
        window->show();
    }

    if (!launchedByOpenEvent) {
#ifdef Q_OS_MAC

        QTimer::singleShot(100, [=]() {

#endif

            if (!launchedByOpenEvent) {
                auto window = MainWindow::createLastOpened();
                window->show();
            }

#ifdef Q_OS_MAC

        });

#endif

#ifdef Q_OS_WIN

        win_sparkle_set_appcast_url(ApplicationSettings::appcastURL);
        win_sparkle_init();

#endif
    }
}

Application::~Application() {
    Application::trayIcon->deleteLater();

#ifdef Q_OS_MAC

    releaseCocoaDelegate();

#endif
#ifdef Q_OS_WIN

    win_sparkle_cleanup();

#endif
}

bool Application::event(QEvent *event) {
    if (event->type() == QEvent::FileOpen) {
        launchedByOpenEvent = true;

        auto openEvent = dynamic_cast<QFileOpenEvent *>(event);
        auto filePath = openEvent->file();

        if (!Application::fileIsOpened(filePath)) {
            auto window = new MainWindow(filePath);
            window->show();
        }
    }

    return QApplication::event(event);
}

void Application::setupFonts() {
    if (QFontDatabase::addApplicationFont(":/fonts/FontAwesome.ttf") < 0)
        qWarning() << "FontAwesome cannot be loaded!";

    if (QFontDatabase::addApplicationFont(":/fonts/ionicons.ttf") < 0)
        qWarning() << "Ionicons cannot be loaded!";

#ifdef Q_OS_WIN

    if (QFontDatabase().families().contains("Segoe UI")) {
        auto font = QFont("Segoe UI");
        font.setPixelSize(12);
        setFont(font);
    }

#endif
}

void Application::registerOpenedFile(const QString &filePath) {
    openedFiles.append(filePath);

#ifdef Q_OS_MAC

    registerCocoaRecentFile(filePath);

#endif
}

void Application::markFileClosed(const QString &filePath) {
    openedFiles.removeAll(filePath);
}

bool Application::fileIsOpened(const QString &filePath) {
    return openedFiles.indexOf(filePath) >= 0;
}

void Application::clearRecentFiles() {
#ifdef Q_OS_MAC

    Application::clearCocoaRecentFiles();

#endif
}

#ifdef Q_OS_WIN

void Application::checkForUpdates() {
    win_sparkle_check_update_with_ui();
}

#endif