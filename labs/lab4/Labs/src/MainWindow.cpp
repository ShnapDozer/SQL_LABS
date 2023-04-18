#include "include/MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QSettings>
#include <QTabWidget>
#include <QTextEdit>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentRow = -1;

    connect(ui->tables_tw, &QTabWidget::currentChanged, this, &MainWindow::onDbTableWidgetIndexChanged);

    connect(ui->add_pb, &QPushButton::clicked, this, &MainWindow::onAddPbClicked);
    connect(ui->remove_pb, &QPushButton::clicked, this, &MainWindow::onRemovePbClicked);
    connect(ui->setQuery_pb, &QPushButton::clicked, this, &MainWindow::onSetQuetyPbClicked);


    connectDB();
    tableNames = db.tables();
    tabelModel = new QSqlTableModel(this, db);
    formModel = new QSqlQueryModel(this);

    QTableView *tabelView;
    foreach (QString tableName, tableNames) {
        tabelView = new QTableView(this);
        tabelView->setModel(tabelModel);
        connect(tabelView, &QTableView::clicked, this, &MainWindow::onTableViewRowClicked);

        ui->tables_tw->addTab(tabelView, tableName);
        tableViews.push_back(tabelView);
    }

    tabelView = new QTableView(this);
    tabelView->setModel(formModel);

    ui->tables_tw->addTab(tabelView, "Form from query");
    tableViews.push_back(tabelView);

    // Pre-install:
    ui->queryText_te->setText(QString("SELECT * FROM %1").arg(*tableNames.begin()));

    ui->tables_tw->setCurrentWidget(*tableViews.begin());
    ui->setQuery_pb->click();
}

MainWindow::~MainWindow()
{
    QSqlDatabase db = QSqlDatabase::database();
    if(db.isOpen()) {
        db.close();
    }


    delete ui;
}

void MainWindow::connectDB()
{
    QSettings appConf(QString("./cfg/application.cfg"), QSettings::IniFormat);
    appConf.setValue("/InterviewPath", "interviewPath");

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(appConf.value("SQL/HostName").toString());
    db.setDatabaseName(appConf.value("SQL/DatabaseName").toString());
    db.setUserName(appConf.value("SQL/UserName").toString());
    db.setPassword(appConf.value("SQL/Password").toString());
    db.open();

    qWarning() << db.isOpen() << db.tables();

}

void MainWindow::onTableViewRowClicked(const QModelIndex &index)
{
    currentRow = index.row();
}

void MainWindow::onDbTableWidgetIndexChanged(int index)
{
    if(index < tableNames.size()) {
        tabelModel->setTable(tableNames[index]);
        tabelModel->select();
    }

    currentRow = -1;
}

void MainWindow::onAddPbClicked()
{
    tabelModel->insertRow(tabelModel->rowCount());
}

void MainWindow::onRemovePbClicked()
{
    if(currentRow != -1) {
        tabelModel->removeRow(currentRow);
    }
}

void MainWindow::onSetQuetyPbClicked()
{
    const QString query = ui->queryText_te->toPlainText();
    if(!query.isEmpty()) {
        formModel->setQuery(query);
        if (formModel->lastError().isValid()) {
            qWarning() << formModel->lastError().text();
        }
    }
}

