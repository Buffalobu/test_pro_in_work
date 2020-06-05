#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


   // setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    //TitleBar *pTitleBar = new TitleBar(this);

    connect(ui->m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(ui->m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(ui->m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));


    installEventFilter(ui->widget);

    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
   // setWindowTitle("LIT");
    //setWindowIcon(QIcon(":/images/logo_32.jpg"));
    //setWindowIcon(QIcon(":/images/logo_80.jpg"));
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    emit ui->m_pMaximizeButton->clicked();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
    if (ReleaseCapture())
    {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
           SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
       event->ignore();
#else
#endif
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::WindowTitleChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            ui->m_pTitleLabel->setText(pWidget->windowTitle());
            return true;
        }
    }
    case QEvent::WindowIconChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            QIcon icon = pWidget->windowIcon();
            ui->m_pIconLabel->setPixmap(icon.pixmap(ui->m_pIconLabel->size()));
            return true;
        }
    }
    case QEvent::WindowStateChange:
    case QEvent::Resize:
        updateMaximize();
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void MainWindow::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == ui->m_pMinimizeButton)
        {
            pWindow->showMinimized();
        }
        else if (pButton == ui->m_pMaximizeButton)
        {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
        }
        else if (pButton == ui->m_pCloseButton)
        {
            pWindow->close();
        }
    }
}

void MainWindow::updateMaximize()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        bool bMaximize = pWindow->isMaximized();
        if (bMaximize)
        {
            ui->m_pMaximizeButton->setToolTip(tr("Restore"));
            ui->m_pMaximizeButton->setProperty("maximizeProperty", "restore");
        }
        else
        {
            ui->m_pMaximizeButton->setProperty("maximizeProperty", "maximize");
            ui->m_pMaximizeButton->setToolTip(tr("Maximize"));
        }

        ui->m_pMaximizeButton->setStyle(QApplication::style());
    }
}
