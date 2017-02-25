#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTextTable>
#include <QTableView>
#include <QTableWidget>
#include <QHBoxLayout>

#include "matrix.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:

    // Functions involving 2 matrices
    void add();
    void subtract();
    void multiply();
    void scalar_mult();

    // Functions for first matrix
    void addRow();
    void addCol();
    void deleteRow();
    void deleteCol();
    void determinant();
    void inverse();

    void cofactor();
    void transpose();

    // Functions for second matrix
    void addRow2();
    void addCol2();
    void deleteRow2();
    void deleteCol2();
    void determinant2();
    void inverse2();

    void cofactor2();
    void transpose2();


private:

    /*------------------- labels */
    QLabel *label;
    QLabel *equalLabel;
    QLabel *instructions_title;
    QLabel *instructions;

    QLabel *det1Label;
    QLabel *det2Label;

    /*------------------- buttons */

    /*---------- for two matrices */
    QPushButton *add_button;
    QPushButton *subtract_button;
    QPushButton *multiply_button;
    QPushButton *scalar_mult_button;

    /*---------- for first matrix */
    QPushButton *add_row_button;
    QPushButton *add_col_button;
    QPushButton *delete_row_button;
    QPushButton *delete_col_button;
    QPushButton *determinant_button;
    QPushButton *inverse_button;

    QPushButton *cofactor_button;
    QPushButton *transpose_button;

    /*---------- for second matrix */
    QPushButton *add_row_button2;
    QPushButton *add_col_button2;
    QPushButton *delete_row_button2;
    QPushButton *delete_col_button2;
    QPushButton *determinant_button2;
    QPushButton *inverse_button2;

    QPushButton *cofactor_button2;
    QPushButton *transpose_button2;

    /*------------------- tables */

    QTableWidget *table_widget;
    QTableWidget *table_widget2;
    QTableWidget *table_widget3;

    /*------------------- matrices */

    Matrix m1;
    Matrix m2;
    Matrix m3;
};

#endif // MAINWINDOW_H
