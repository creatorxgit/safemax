import sys
import re
from PyQt6.QtWidgets import QApplication, QWidget, QVBoxLayout
from PyQt6.QtCore import QUrl
from PyQt6.QtGui import QDesktopServices
from PyQt6.QtWebEngineWidgets import QWebEngineView
from PyQt6.QtWebEngineCore import QWebEnginePage

class CustomPage(QWebEnginePage):
    def acceptNavigationRequest(self, url: QUrl, _type, isMainFrame: bool):
        host = url.host().lower()
        if host and re.search(r'(^|\.)web\.max\.ru$', host):
            return True
        QDesktopServices.openUrl(url)
        return False

def main():
    app = QApplication(sys.argv)
    view = QWebEngineView()
    view.setPage(CustomPage(view))
    view.load(QUrl("https://web.max.ru/"))

    window = QWidget()
    layout = QVBoxLayout(window)
    layout.setContentsMargins(0,0,0,0)
    layout.addWidget(view)
    window.setLayout(layout)
    window.showFullScreen()
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
