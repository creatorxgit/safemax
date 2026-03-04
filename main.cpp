#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QDesktopServices>
#include <QUrl>
#include <QRegularExpression>

class CustomPage : public QWebEnginePage {
    Q_OBJECT
public:
    explicit CustomPage(QObject *parent = nullptr) : QWebEnginePage(parent) {}

protected:
    QWebEnginePage::NavigationRequestPolicy acceptNavigationRequest(const QUrl &url,
                                                                   NavigationType type,
                                                                   bool isMainFrame) override
    {
        Q_UNUSED(type)
        Q_UNUSED(isMainFrame)

        // Разрешаем навигацию внутри web.max.ru (включая поддомены).
        // Сравниваем хост: проверяем, содержит ли хост "web.max.ru" в конце.
        QString host = url.host().toLower();
        if (!host.isEmpty()) {
            // Совпадение для web.max.ru и любых поддоменов, например sub.web.max.ru
            QRegularExpression re(R"((^|\.)web\.max\.ru$)");
            if (re.match(host).hasMatch()) {
                return QWebEnginePage::NavigationRequestPolicy::AcceptRequest;
            }
        }

        // Иначе открываем в системном браузере и блокируем навигацию в веб-вью.
        QDesktopServices::openUrl(url);
        return QWebEnginePage::NavigationRequestPolicy::IgnoreRequest;
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWebEngineView *view = new QWebEngineView;
    CustomPage *page = new CustomPage(view);
    view->setPage(page);

    view->load(QUrl("https://web.max.ru/"));

    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout(&window);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(view);

    window.setLayout(layout);
    window.showFullScreen();

    return app.exec();
}

#include "main.moc"
