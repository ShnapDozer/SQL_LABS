#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QStringList>
#include <QModelIndex>

class QTableView;
class QSqlTableModel;
class QSqlQueryModel;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void connectDB();

    Ui::MainWindow *ui;

    int currentRow;

    QStringList tableNames;

    QSqlDatabase db;
    QSqlTableModel *tabelModel;
    QSqlQueryModel *formModel;
    QVector<QTableView*> tableViews;

private slots:
    void onTableViewRowClicked(const QModelIndex &index);

    void onDbTableWidgetIndexChanged(int index);

    void onAddPbClicked();
    void onRemovePbClicked();
    void onSetQuetyPbClicked();

};
#endif // MAINWINDOW_H
