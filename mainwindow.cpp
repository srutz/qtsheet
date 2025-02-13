#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "sheet.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QMainWindow>
#include <QResizeEvent>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupSheet();

    // setup buttons to show the sheet
    auto buttonsPanel = new QWidget(this);
    auto buttonsLayout = new QHBoxLayout(buttonsPanel);
    buttonsLayout->setSpacing(8);

    auto showLeftButton = new QPushButton("Show Left Sheet", this);
    connect(showLeftButton, &QPushButton::clicked, this, [this] {
        this->m_sheet->showSheet(this, Sheet::Side::Left);
    });
    auto showRightButton = new QPushButton("Show Right Sheet", this);
    connect(showRightButton, &QPushButton::clicked, this, [this] {
        this->m_sheet->showSheet(this,  Sheet::Side::Right);
    });
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(showLeftButton, 0, Qt::AlignCenter);
    buttonsLayout->addWidget(showRightButton, 0, Qt::AlignCenter);
    buttonsLayout->addStretch();

    auto layout = new QVBoxLayout(this->centralWidget());
    layout->addStretch();
    layout->addWidget(buttonsPanel);
    layout->addStretch();
}

/* Sets up the sheet and its content
 * the sheet is a sliding sidepanel and the content can be any QWidget
 * To close the sheet from your code invoke hideSheet(true);
 * To open the sheet from your code invoke showSheet(QWidget *destination, QWidget *content);
 */
void MainWindow::setupSheet() {
    // setup the sheet's content
    m_sheetContent = new QWidget(this);
    auto sheetLayout = new QVBoxLayout(m_sheetContent);
    sheetLayout->setContentsMargins(9, 0, 13, 0);

    auto header = new QLabel(this);
    header->setText(R"(<html>
        <h2>About qtsheet</h2>
        <p>qtsheet implements the slideing style-sheets for qt.
        The code is free and you just copy 2 files into your project to use it.
        </p>
        <p>Written by Stepan Rutz</p>
        )");
    header->setWordWrap(true);

    auto image = new QLabel(this);
    image->setPixmap(QPixmap(":/resources/pexels-goumbik.jpg"));

    sheetLayout->addWidget(header);
    sheetLayout->addWidget(image);
    sheetLayout->addStretch();

    // add another close button to the sheet
    auto sheetButton = new QPushButton("Close", this);
    connect(sheetButton, &QPushButton::clicked, this, [this] {
        this->m_sheet->hideSheet();
    });
    sheetLayout->addWidget(sheetButton, 0, Qt::AlignRight);

    // create the sheet panel
    m_sheet = new Sheet(m_sheetContent, this);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    /* invoke the layout method on the sheet it you want it
     * to adjust its size during resizing of its parent */
    m_sheet->layout(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
