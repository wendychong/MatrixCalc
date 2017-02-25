#include "mainwindow.h"
#include <QCoreApplication>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QHeaderView>
#include <QMessageBox>
#include <QFont>
#include <QTableWidget>
#include <QDesktopWidget>
#include "matrix.h"

QString value = "", total = "";
QString instruct = "";
int fNum, sNum;
bool addBool = false, subtractBool = false, multiplyBool = false, determinantBool = false, inverseBool = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /*-------------------------------------------------------- the first table */

     // Creating a new table
     table_widget = new QTableWidget(this);
     table_widget->setGeometry(10, 10, 250, 250);
     table_widget->setMaximumSize(250, 250);
     table_widget->setShowGrid(true);
     table_widget->setRowCount(1);
     table_widget->setColumnCount(1);

     // Setting the value of a single cell
     table_widget->setItem(0, 0, new QTableWidgetItem(" "));
     table_widget->setColumnWidth(0, 50);

     table_widget->setEditTriggers(QAbstractItemView::DoubleClicked);
     table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
     table_widget->setSelectionMode(QAbstractItemView::SingleSelection);

     /*-------------------------------------------------------- the second table */
     // Creating a new table
     table_widget2 = new QTableWidget(this);
     table_widget2->setGeometry(450, 10, 250, 250);
     table_widget2->setMaximumSize(250, 250);
     table_widget2->setShowGrid(true);
     table_widget2->setRowCount(1);
     table_widget2->setColumnCount(1);
     // Setting the value of a single cell
     table_widget2->setItem(0, 0, new QTableWidgetItem(" "));
     table_widget2->setColumnWidth(0,50);

     table_widget2->setEditTriggers(QAbstractItemView::DoubleClicked);
     table_widget2->setSelectionBehavior(QAbstractItemView::SelectRows);
     table_widget2->setSelectionMode(QAbstractItemView::SingleSelection);

     /*-------------------------------------------------------- the third table */
     // Creating a new table
     table_widget3 = new QTableWidget(this);
     table_widget3->setGeometry(850, 10, 250, 250);
     table_widget3->setMaximumSize(250, 250);
     table_widget3->setShowGrid(true);
     table_widget3->setRowCount(1);
     table_widget3->setColumnCount(1);
     // Setting the value of a single cell
     table_widget3->setItem(0, 0, new QTableWidgetItem(" "));
     table_widget3->item(0,0)->setTextAlignment(Qt::AlignCenter);
     table_widget3->setColumnWidth(0,50);


     /* -------------------------------------------------------- for labels */

     label = new QLabel(" ", this);
     label->setGeometry(QRect(QPoint(352,100), QSize(50, 50)));

     equalLabel = new QLabel("=", this);
     QFont f("Arial", 25, QFont::StyleNormal);
     equalLabel->setFont(f);
     equalLabel->setGeometry(QRect(QPoint(773,100), QSize(50, 50)));

     instructions_title = new QLabel("Instructions", this);
     instructions_title->setMidLineWidth(3);
     QFont ff("Arial", 15, QFont::StyleNormal);
     instructions_title->setFont(ff);
     instructions_title->setFrameStyle(QFrame::Box);
     instructions_title->setAlignment(Qt::AlignCenter);
     instructions_title->setStyleSheet("QLabel { background-color : white; color : gray; }");
     instructions_title->setGeometry(QRect(QPoint(905, 285), QSize(150, 50)));

     instructions = new QLabel(instruct, this);
     instructions->setMidLineWidth(3);
     instructions->setFrameStyle(QFrame::Box);
     instructions->setAlignment(Qt::AlignLeft);
     instructions->setWordWrap(1);
     instructions->setStyleSheet("QLabel { background-color : white; color : gray; }");
     instructions->setGeometry(QRect(QPoint(830, 350), QSize(300, 200)));

     det1Label = new QLabel(" ", this);
     det1Label->setMidLineWidth(3);
     det1Label->setFrameStyle(QFrame::Box);
     det1Label->setStyleSheet("QLabel { background-color : white; color : gray; }");
     det1Label->setGeometry(QRect(QPoint(75, 470), QSize(100, 50)));

     det2Label = new QLabel(" ", this);
     det2Label->setMidLineWidth(3);
     det2Label->setFrameStyle(QFrame::Box);
     det2Label->setStyleSheet("QLabel { background-color : white; color : gray; }");
     det2Label->setGeometry(QRect(QPoint(525, 470), QSize(100, 50)));


     /* --------------------------------------------------------------------- buttons */

     /* -------------------------------------------------------- for two matrices */

     add_button = new QPushButton("+", this);
     add_button->setGeometry(QRect(QPoint(305,200), QSize(100,50)));
     connect(add_button, SIGNAL(released()), this, SLOT(add()));

     subtract_button = new QPushButton("-", this);
     subtract_button->setGeometry(QRect(QPoint(305,250), QSize(100,50)));
     connect(subtract_button, SIGNAL(released()), this, SLOT(subtract()));

     multiply_button = new QPushButton("x", this);
     multiply_button->setGeometry(QRect(QPoint(305,300), QSize(100,50)));
     connect(multiply_button, SIGNAL(released()), this, SLOT(multiply()));

     scalar_mult_button = new QPushButton("scalar mult.", this);
     scalar_mult_button->setGeometry(QRect(QPoint(305,350), QSize(100,50)));
     connect(scalar_mult_button, SIGNAL(released()), this, SLOT(scalar_mult()));

     /* -------------------------------------------------------- for first matrix */

     add_row_button = new QPushButton("Add Row", this);
     add_row_button->setGeometry(QRect(QPoint(30, 270), QSize(100,50)));
     connect(add_row_button, SIGNAL(released()), this, SLOT(addRow()));

     add_col_button = new QPushButton("Add Col", this);
     add_col_button->setGeometry(QRect(QPoint(130, 270), QSize(100,50)));
     connect(add_col_button, SIGNAL(released()), this, SLOT(addCol()));

     delete_row_button = new QPushButton("Del Row", this);
     delete_row_button->setGeometry(QRect(QPoint(30, 320), QSize(100,50)));
     connect(delete_row_button, SIGNAL(released()), this, SLOT(deleteRow()));

     delete_col_button = new QPushButton("Del Col", this);
     delete_col_button->setGeometry(QRect(QPoint(130, 320), QSize(100,50)));
     connect(delete_col_button, SIGNAL(released()), this, SLOT(deleteCol()));

     determinant_button = new QPushButton("Det", this);
     determinant_button->setGeometry(QRect(QPoint(30, 370), QSize(100,50)));
     connect(determinant_button, SIGNAL(released()), this, SLOT(determinant()));

     inverse_button = new QPushButton("Inv", this);
     inverse_button->setGeometry(QRect(QPoint(130, 370), QSize(100,50)));
     connect(inverse_button, SIGNAL(released()), this, SLOT(inverse()));

     cofactor_button = new QPushButton("Cofactor", this);
     cofactor_button->setGeometry(QRect(QPoint(30, 420), QSize(100,50)));
     connect(cofactor_button, SIGNAL(released()), this, SLOT(cofactor()));

     transpose_button = new QPushButton("Transpose", this);
     transpose_button->setGeometry(QRect(QPoint(130, 420), QSize(100,50)));
     connect(transpose_button, SIGNAL(released()), this, SLOT(transpose()));

     /* -------------------------------------------------------- for second matrix */

     add_row_button2 = new QPushButton("Add Row", this);
     add_row_button2->setGeometry(QRect(QPoint(480, 270), QSize(100,50)));
     connect(add_row_button2, SIGNAL(released()), this, SLOT(addRow2()));

     add_col_button2 = new QPushButton("Add Col", this);
     add_col_button2->setGeometry(QRect(QPoint(580, 270), QSize(100,50)));
     connect(add_col_button2, SIGNAL(released()), this, SLOT(addCol2()));

     delete_row_button2 = new QPushButton("Del Row", this);
     delete_row_button2->setGeometry(QRect(QPoint(480, 320), QSize(100,50)));
     connect(delete_row_button2, SIGNAL(released()), this, SLOT(deleteRow2()));

     delete_col_button2 = new QPushButton("Del Col", this);
     delete_col_button2->setGeometry(QRect(QPoint(580, 320), QSize(100,50)));
     connect(delete_col_button2, SIGNAL(released()), this, SLOT(deleteCol2()));

     determinant_button2 = new QPushButton("Det", this);
     determinant_button2->setGeometry(QRect(QPoint(480, 370), QSize(100,50)));
     connect(determinant_button2, SIGNAL(released()), this, SLOT(determinant2()));

     inverse_button2 = new QPushButton("Inv", this);
     inverse_button2->setGeometry(QRect(QPoint(580, 370), QSize(100,50)));
     connect(inverse_button2, SIGNAL(released()), this, SLOT(inverse2()));

     cofactor_button2 = new QPushButton("Cofactor", this);
     cofactor_button2->setGeometry(QRect(QPoint(480, 420), QSize(100,50)));
     connect(cofactor_button2, SIGNAL(released()), this, SLOT(cofactor2()));

     transpose_button2 = new QPushButton("Transpose", this);
     transpose_button2->setGeometry(QRect(QPoint(580, 420), QSize(100,50)));
     connect(transpose_button2, SIGNAL(released()), this, SLOT(transpose2()));
}


/*------------------------------------------------------------- Functions for 2 Matrices */

void MainWindow::add()
{
     // Display the plus sign
     value = "+";
     QFont f("Arial", 25, QFont::StyleNormal);
     label->setFont(f);
     label->setText(value);

     instruct = "Adding two Matrices:\n"
                "1. Set the size of your matrices in leftmost matrix.\n"
                "2. Push '+' button to set addition format.\n"
                "3. Fill in values.\n"
                "4. Push '+' button again for result.";
     instructions->setText(instruct);


     // Set the second table
     if((table_widget2->columnCount() != table_widget->columnCount()) || (table_widget2->rowCount() != table_widget->rowCount()))
     {
         /*  For the second table  */
         table_widget2->setColumnCount(table_widget->columnCount());
         table_widget2->setRowCount(table_widget->rowCount());
         table_widget2->setColumnWidth(table_widget2->columnCount()-1, 50);

         // for all the items in the table
         for(int i = 0; i < table_widget2->rowCount(); i++)
         {
             for(int k = 0; k < table_widget2->columnCount(); k++)
             {
                 table_widget2->setItem(i, k, new QTableWidgetItem(" "));
                 table_widget2->setColumnWidth(k, 50);
             }
         }
     }

     // For the third table
     if((table_widget3->columnCount() != table_widget->columnCount()) || (table_widget3->rowCount() != table_widget->rowCount()))
     {
         /*  For the answer table  */
         table_widget3->setColumnCount(table_widget->columnCount());
         table_widget3->setRowCount(table_widget->rowCount());

         table_widget3->setColumnWidth(table_widget3->columnCount()-1, 50);

         // for all the items in the table
         for(int i = 0; i < table_widget3->rowCount(); i++)
         {
             for(int k = 0; k < table_widget3->columnCount(); k++)
             {
                 table_widget3->setItem(i, k, new QTableWidgetItem(" "));
                 table_widget3->setColumnWidth(k, 50);
             }
         }
     }

     // Get the values from the first table
     m1.setSize(table_widget->rowCount(), table_widget->columnCount());

     // Get the values from the table
     for(int i = 0; i < table_widget->rowCount(); i++)
     {
         for(int k = 0; k < table_widget->columnCount(); k++)
         {
             QString s = table_widget->item(i, k)->text();
             float value = s.toFloat();
             m1.setValue(i, k, value);
         }
     }

     // Get the values from the second table
     m2.setSize(table_widget2->rowCount(), table_widget2->columnCount());

     // for all the items in the table
     for(int i = 0; i < table_widget2->rowCount(); i++)
     {
         for(int k = 0; k < table_widget2->columnCount(); k++)
         {
             QString s = table_widget2->item(i, k)->text();
             float value = s.toFloat();
             m2.setValue(i, k, value);
         }
     }

     m3.setSize(table_widget3->rowCount(), table_widget3->columnCount());
     m3 = m1.add(m2);

     // As long as the display and matrix are the same size
     if((m3.getRows() == table_widget3->rowCount()) && (m3.getCols() == table_widget3->columnCount()))
     {
         for(int rows = 0; rows < m3.getRows(); rows++)
         {
             for(int cols = 0; cols < m3.getCols(); cols++)
             {
                 float value = m3.getValue(rows, cols);
                 QString b = QString::number(value);
                 table_widget3->item(rows, cols)->setText(b);
             }
         }
     }
}

void MainWindow::subtract()
{
    // Display the minus sign
    value = "-";
    QFont f("Arial", 25, QFont::StyleNormal);
    label->setFont(f);
    label->setText(value);

    instruct = "Subtracting two Matrices:\n"
               "1. Set the size of your matrices in leftmost matrix.\n"
               "2. Push '-' button to set subtraction format.\n"
               "3. Fill in values.\n"
               "4. Push '-' button again for result.";
    instructions->setText(instruct);


    // Set the second table
    if((table_widget2->columnCount() != table_widget->columnCount()) || (table_widget2->rowCount() != table_widget->rowCount()))
    {
        /*  For the second table  */
        table_widget2->setColumnCount(table_widget->columnCount());
        table_widget2->setRowCount(table_widget->rowCount());
        table_widget2->setColumnWidth(table_widget2->columnCount()-1, 50);

        // for all the items in the table
        for(int i = 0; i < table_widget2->rowCount(); i++)
        {
            for(int k = 0; k < table_widget2->columnCount(); k++)
            {
                table_widget2->setItem(i, k, new QTableWidgetItem(" "));
                table_widget2->setColumnWidth(k, 50);
            }
        }
    }

    // For the third table
    if((table_widget3->columnCount() != table_widget->columnCount()) || (table_widget3->rowCount() != table_widget->rowCount()))
    {
        /*  For the answer table  */
        table_widget3->setColumnCount(table_widget->columnCount());
        table_widget3->setRowCount(table_widget->rowCount());

        table_widget3->setColumnWidth(table_widget3->columnCount()-1, 50);

        // for all the items in the table
        for(int i = 0; i < table_widget3->rowCount(); i++)
        {
            for(int k = 0; k < table_widget3->columnCount(); k++)
            {
                table_widget3->setItem(i, k, new QTableWidgetItem(" "));
                table_widget3->setColumnWidth(k, 50);
            }
        }
    }

    // Get the values from the first table
    m1.setSize(table_widget->rowCount(), table_widget->columnCount());

    // Get the values from the table
    for(int i = 0; i < table_widget->rowCount(); i++)
    {
        for(int k = 0; k < table_widget->columnCount(); k++)
        {
            QString s = table_widget->item(i, k)->text();
            float value = s.toFloat();
            m1.setValue(i, k, value);
        }
    }

    // Get the values from the second table
    m2.setSize(table_widget2->rowCount(), table_widget2->columnCount());

    // for all the items in the table
    for(int i = 0; i < table_widget2->rowCount(); i++)
    {
        for(int k = 0; k < table_widget2->columnCount(); k++)
        {
            QString s = table_widget2->item(i, k)->text();
            float value = s.toFloat();
            m2.setValue(i, k, value);
        }
    }

    m3.setSize(table_widget3->rowCount(), table_widget3->columnCount());
    m3 = m1.subtract(m2);

    // As long as the display and matrix are the same size
    if((m3.getRows() == table_widget3->rowCount()) && (m3.getCols() == table_widget3->columnCount()))
    {
        for(int rows = 0; rows < m3.getRows(); rows++)
        {
            for(int cols = 0; cols < m3.getCols(); cols++)
            {
                float value = m3.getValue(rows, cols);
                QString b = QString::number(value);
                table_widget3->item(rows, cols)->setText(b);
            }
        }
    }
}

void MainWindow::multiply()
{
    value = "x";
    QFont f("Arial", 25, QFont::StyleNormal);
    label->setFont(f);
    label->setText(value);

    instruct = "Multiplying two Matrices:\n"
               "1. Set the size of your matrices.\n"
               "2. Push 'x' button. If your dimensions are invalid, the calc. will change your second matrix to valid dimensions.\n"
               "3. Fill in values.\n"
               "4. Push 'x' button again for result.";
    instructions->setText(instruct);

    // The insides of the must be the same
    // ex: (2x3)(3x2)
    if((table_widget->columnCount() != table_widget2->rowCount()))
    {
        /*  For the second table  */
        table_widget2->setRowCount(table_widget->columnCount());
        table_widget2->setColumnWidth(table_widget2->columnCount()-1, 50);

        // for all the items in the table
        for(int i = 0; i < table_widget2->rowCount(); i++)
        {
            for(int k = 0; k < table_widget2->columnCount(); k++)
            {
                table_widget2->setItem(i, k, new QTableWidgetItem(" "));
                table_widget2->setColumnWidth(k, 50);
            }
        }
    }

    if((table_widget3->rowCount() != table_widget->rowCount()) || (table_widget3->columnCount() != table_widget2->columnCount()))
    {
        /*  For the third table  */
        table_widget3->setRowCount(table_widget->rowCount());
        table_widget3->setColumnCount(table_widget2->columnCount());
        table_widget3->setColumnWidth(table_widget2->columnCount()-1, 50);

        // initialize the items in the table
        for(int i = 0; i < table_widget3->rowCount(); i++)
        {
            for(int k = 0; k < table_widget3->columnCount(); k++)
            {
                table_widget3->setItem(i, k, new QTableWidgetItem(" "));
                table_widget3->setColumnWidth(k, 50);
            }
        }
    }


    // Get the values from the first table
    m1.setSize(table_widget->rowCount(), table_widget->columnCount());

    // Get the values from the table
    for(int i = 0; i < table_widget->rowCount(); i++)
    {
        for(int k = 0; k < table_widget->columnCount(); k++)
        {
            QString s = table_widget->item(i, k)->text();
            float value = s.toFloat();
            m1.setValue(i, k, value);
        }
    }

    // Get the values from the second table
    m2.setSize(table_widget2->rowCount(), table_widget2->columnCount());

    // for all the items in the table
    for(int i = 0; i < table_widget2->rowCount(); i++)
    {
        for(int k = 0; k < table_widget2->columnCount(); k++)
        {
            QString s = table_widget2->item(i, k)->text();
            float value = s.toFloat();
            m2.setValue(i, k, value);
        }
    }


    m3.setSize(table_widget3->rowCount(), table_widget3->columnCount());
    m3 = m1.multiply(m2);

    // As long as the display and matrix are the same size
    for(int rows = 0; rows < m3.getRows(); rows++)
    {
        for(int cols = 0; cols < m3.getCols(); cols++)
        {
            float value = m3.getValue(rows, cols);
            QString b = QString::number(value);
            table_widget3->item(rows, cols)->setText(b);
        }
    }
}

void MainWindow::scalar_mult()
{
    // Display the plus sign
    value = "x";
    QFont f("Arial", 25, QFont::StyleNormal);
    label->setFont(f);
    label->setText(value);

    instruct = "Scalar Multiplication:\n"
               "1. Set the size of your matrix in leftmost matrix.\n"
               "2. Push 'scalar mult.' button to set scalar mult. format.\n"
               "3. Fill in values.\n"
               "4. Push 'scalar mult.' button again for result.";
    instructions->setText(instruct);


    // Set the second table to a (1 x 1) matrix
    if((table_widget2->columnCount() != 1) || (table_widget2->rowCount() != 1))
    {
        table_widget2->setColumnCount(1);
        table_widget2->setRowCount(1);

        table_widget2->setItem(0, 0, new QTableWidgetItem(" "));
        table_widget2->setColumnWidth(0, 50);
    }

    // For the third table
    if((table_widget3->columnCount() != table_widget->columnCount()) || (table_widget3->rowCount() != table_widget->rowCount()))
    {
        /*  For the answer table  */
        table_widget3->setColumnCount(table_widget->columnCount());
        table_widget3->setRowCount(table_widget->rowCount());

        table_widget3->setColumnWidth(table_widget3->columnCount()-1, 50);

        // for all the items in the table
        for(int i = 0; i < table_widget3->rowCount(); i++)
        {
            for(int k = 0; k < table_widget3->columnCount(); k++)
            {
                table_widget3->setItem(i, k, new QTableWidgetItem(" "));
                table_widget3->setColumnWidth(k, 50);
            }
        }
    }

    // Get the values from the first table
    m1.setSize(table_widget->rowCount(), table_widget->columnCount());

    // Get the values from the table
    for(int i = 0; i < table_widget->rowCount(); i++)
    {
        for(int k = 0; k < table_widget->columnCount(); k++)
        {
            QString s = table_widget->item(i, k)->text();
            float value = s.toFloat();
            m1.setValue(i, k, value);
        }
    }

    // Get the scalar float
    QString s = table_widget2->item(0, 0)->text();
    float value = s.toFloat();

    m3.setSize(table_widget3->rowCount(), table_widget3->columnCount());
    m3 = m1.multiply(value);

    // As long as the display and matrix are the same size
    if((m3.getRows() == table_widget3->rowCount()) && (m3.getCols() == table_widget3->columnCount()))
    {
        for(int rows = 0; rows < m3.getRows(); rows++)
        {
            for(int cols = 0; cols < m3.getCols(); cols++)
            {
                float value = m3.getValue(rows, cols);
                QString b = QString::number(value);
                table_widget3->item(rows, cols)->setText(b);
            }
        }
    }
}

/*------------------------------------------------------------- Functions for 2 Matrices */


/*------------------------------------------------------------- Functions for First Matrix */

void MainWindow::addRow()
{
    table_widget->setRowCount(table_widget->rowCount()+1);

    int row = table_widget->rowCount();

    // Initialize new cells
    for(int i = 0; i < table_widget->columnCount(); i++)
    {table_widget->setItem((row-1), i, new QTableWidgetItem(" "));}

    m1.setSize(table_widget->rowCount(), table_widget->columnCount());
}

void MainWindow::addCol()
{
    table_widget->setColumnCount(table_widget->columnCount()+1);

    int col = table_widget->columnCount();

    // Initialize new cells
    for(int i = 0; i < table_widget->rowCount(); i++)
    {table_widget->setItem(i, (col-1), new QTableWidgetItem(" "));}

    table_widget->setColumnWidth((col-1), 50);

    m1.setSize(table_widget->rowCount(), table_widget->columnCount());
}

void MainWindow::deleteRow()
{
    table_widget->removeRow(table_widget->rowCount()-1);
    m1.setSize(table_widget->rowCount(), table_widget->columnCount());
}

void MainWindow::deleteCol()
{
    table_widget->removeColumn(table_widget->columnCount()-1);
    m1.setSize(table_widget->rowCount(), table_widget->columnCount());
}

void MainWindow::determinant()
{
    if(table_widget->rowCount() == table_widget->columnCount())
    {
        if(table_widget->rowCount() > 1)
        {
            // Get the values from the first table
            m1.setSize(table_widget->rowCount(), table_widget->columnCount());

            // Get the values from the table
            for(int i = 0; i < table_widget->rowCount(); i++)
            {
                for(int k = 0; k < table_widget->columnCount(); k++)
                {
                    QString s = table_widget->item(i, k)->text();
                    float value = s.toFloat();
                    m1.setValue(i, k, value);
                }
            }

            float ans = m1.det();
            QString b = QString::number(ans);
            det1Label->setText(b);
            det1Label->setAlignment(Qt::AlignCenter);
        }
    }

    else
    {
        // print error: not a square matrix
        //QMessageBox::critical(this, "Not a Square Matrix", "Not a square matrix.");
        QMessageBox abox(this);
        abox.setText("\nNot a square matrix.\nPlease make a square matrix.");
        abox.setIconPixmap(QPixmap(":MyFiles/angry_pikachu.jpg"));
        abox.setParent(this);
        abox.exec();
    }
}

void MainWindow::inverse()
{
    if(table_widget->columnCount() == table_widget->rowCount())
    {
        m1.setSize(table_widget->rowCount(), table_widget->columnCount());

        // for all the items in the table
        for(int i = 0; i < table_widget->rowCount(); i++)
        {
            for(int k = 0; k < table_widget->columnCount(); k++)
            {
                QString s = table_widget->item(i, k)->text();
                float value = s.toFloat();
                m1.setValue(i, k, value);
            }
        }

        Matrix temp(table_widget->rowCount(), table_widget->columnCount());
        if(m1.det()!= 0)
        {
            temp = m1.inverse();

           // As long as the display and matrix are the same size
           if((temp.getRows() == table_widget->rowCount()) && (temp.getCols() == table_widget->columnCount()))
           {
               for(int rows = 0; rows < temp.getRows(); rows++)
               {
                   for(int cols = 0; cols < temp.getCols(); cols++)
                   {

                       float value = temp.getValue(rows, cols);
                       QString b = QString::number(value);
                       table_widget->item(rows, cols)->setText(b);
                   }
               }
           }
        }
        else
        {
            // print error: non-invertible matrix
            QMessageBox::critical(this, "Non-Invertible", "This is a non-invertible matrix.");
        }
    }
    else
    {
        // print error: not a square matrix
        QMessageBox::critical(this, "Not a Square Matrix", "Not a square matrix.");
    }
}

void MainWindow::cofactor()
{
    if(table_widget->columnCount() == table_widget->rowCount())
    {
        m1.setSize(table_widget->rowCount(), table_widget->columnCount());

        // for all the items in the table
        for(int i = 0; i < table_widget->rowCount(); i++)
        {
            for(int k = 0; k < table_widget->columnCount(); k++)
            {
                QString s = table_widget->item(i, k)->text();
                float value = s.toFloat();
                m1.setValue(i, k, value);
            }
        }

        Matrix temp(table_widget->rowCount(), table_widget->columnCount());
        temp = m1.cofactor();

       // As long as the display and matrix are the same size
       if((temp.getRows() == table_widget->rowCount()) && (temp.getCols() == table_widget->columnCount()))
       {
           for(int rows = 0; rows < temp.getRows(); rows++)
           {
               for(int cols = 0; cols < temp.getCols(); cols++)
               {
                   float value = temp.getValue(rows, cols);
                   QString b = QString::number(value);
                   table_widget->item(rows, cols)->setText(b);
               }
           }
       }
    }

    else
    {
        // print error: not a square matrix
        QMessageBox::critical(this, "Square Matrix", "Not a square matrix.");
    }
}

void MainWindow::transpose()
{
    if(table_widget->columnCount() == table_widget->rowCount())
    {
        m1.setSize(table_widget->rowCount(), table_widget->columnCount());

        // for all the items in the table
        for(int i = 0; i < table_widget->rowCount(); i++)
        {
            for(int k = 0; k < table_widget->columnCount(); k++)
            {
                QString s = table_widget->item(i, k)->text();
                float value = s.toFloat();
                m1.setValue(i, k, value);
            }
        }

        Matrix temp(table_widget->rowCount(), table_widget->columnCount());
        temp = m1.transpose();

       // As long as the display and matrix are the same size
       if((temp.getRows() == table_widget->rowCount()) && (temp.getCols() == table_widget->columnCount()))
       {
           for(int rows = 0; rows < temp.getRows(); rows++)
           {
               for(int cols = 0; cols < temp.getCols(); cols++)
               {
                   float value = temp.getValue(rows, cols);
                   QString b = QString::number(value);
                   table_widget->item(rows, cols)->setText(b);
               }
           }
       }
    }

    else
    {
        // print error: not a square matrix
        QMessageBox::critical(this, "Square Matrix", "Not a square matrix.");
    }
}

/*------------------------------------------------------------- Functions for First Matrix */


/*------------------------------------------------------------- Functions for Second Matrix */

void MainWindow::addRow2()
{
    table_widget2->setRowCount(table_widget2->rowCount()+1);

    int row = table_widget2->rowCount();

    // Initialize new cells
    for(int i = 0; i < table_widget2->columnCount(); i++)
    {table_widget2->setItem((row-1), i, new QTableWidgetItem(" "));}

    m2.setSize(table_widget2->rowCount(), table_widget2->columnCount());
}

void MainWindow::addCol2()
{
    table_widget2->setColumnCount(table_widget2->columnCount()+1);

    int col = table_widget2->columnCount();

    // Initialize new cells
    for(int i = 0; i < table_widget2->rowCount(); i++)
    {table_widget2->setItem(i, (col-1), new QTableWidgetItem(" "));}

    table_widget2->setColumnWidth((col-1), 50);

    m2.setSize(table_widget2->rowCount(), table_widget2->columnCount());
}

void MainWindow::deleteRow2()
{
    table_widget2->removeRow(table_widget2->rowCount()-1);
    m2.setSize(table_widget2->rowCount(), table_widget2->columnCount());
}

void MainWindow::deleteCol2()
{
    table_widget2->removeColumn(table_widget2->columnCount()-1);
    m2.setSize(table_widget2->rowCount(), table_widget2->columnCount());
}

void MainWindow::determinant2()
{
    if(table_widget2->rowCount() == table_widget2->columnCount())
    {
        if(table_widget2->rowCount() > 1)
        {
            // Get the values from the first table
            m2.setSize(table_widget2->rowCount(), table_widget2->columnCount());

            // Get the values from the table
            for(int i = 0; i < table_widget2->rowCount(); i++)
            {
                for(int k = 0; k < table_widget2->columnCount(); k++)
                {
                    QString s = table_widget2->item(i, k)->text();
                    float value = s.toFloat();
                    m2.setValue(i, k, value);
                }
            }

            float ans = m2.det();
            QString b = QString::number(ans);
            det2Label->setText(b);
            det2Label->setAlignment(Qt::AlignCenter);
        }
    }

    else
    {
        // print error: not a square matrix
        QMessageBox::critical(this, "Not a Square Matrix", "Not a square matrix.");
    }
}

void MainWindow::inverse2()
{
    if(table_widget2->columnCount() == table_widget2->rowCount())
    {
        m2.setSize(table_widget2->rowCount(), table_widget2->columnCount());

        // for all the items in the table
        for(int i = 0; i < table_widget2->rowCount(); i++)
        {
            for(int k = 0; k < table_widget2->columnCount(); k++)
            {
                QString s = table_widget2->item(i, k)->text();
                float value = s.toFloat();
                m2.setValue(i, k, value);
            }
        }

        Matrix temp(table_widget2->rowCount(), table_widget2->columnCount());
        if(m2.det()!= 0)
        {
            temp = m2.inverse();

           // As long as the display and matrix are the same size
           if((temp.getRows() == table_widget2->rowCount()) && (temp.getCols() == table_widget2->columnCount()))
           {
               for(int rows = 0; rows < temp.getRows(); rows++)
               {
                   for(int cols = 0; cols < temp.getCols(); cols++)
                   {

                       float value = temp.getValue(rows, cols);
                       QString b = QString::number(value);
                       table_widget2->item(rows, cols)->setText(b);
                   }
               }
           }
        }
        else
        {
            // print error: non-invertible matrix
            QMessageBox::critical(this, "Non-Invertible", "This is a non-invertible matrix.");
        }
    }
    else
    {
        // print error: not a square matrix
        QMessageBox::critical(this, "Not a Square Matrix", "Not a square matrix.");
    }
}

void MainWindow::cofactor2()
{
    if(table_widget2->columnCount() == table_widget2->rowCount())
    {
        m2.setSize(table_widget2->rowCount(), table_widget2->columnCount());

        // for all the items in the table
        for(int i = 0; i < table_widget2->rowCount(); i++)
        {
            for(int k = 0; k < table_widget2->columnCount(); k++)
            {
                QString s = table_widget2->item(i, k)->text();
                float value = s.toFloat();
                m2.setValue(i, k, value);
            }
        }

        Matrix temp(table_widget2->rowCount(), table_widget2->columnCount());
        temp = m2.cofactor();

       // As long as the display and matrix are the same size
       if((temp.getRows() == table_widget2->rowCount()) && (temp.getCols() == table_widget2->columnCount()))
       {
           for(int rows = 0; rows < temp.getRows(); rows++)
           {
               for(int cols = 0; cols < temp.getCols(); cols++)
               {
                   float value = temp.getValue(rows, cols);
                   QString b = QString::number(value);
                   table_widget2->item(rows, cols)->setText(b);
               }
           }
       }
    }

    else
    {
        // print error: not a square matrix
        QMessageBox::critical(this, "Square Matrix", "Not a square matrix.");
    }
}

void MainWindow::transpose2()
{
    if(table_widget2->columnCount() == table_widget2->rowCount())
    {
        m2.setSize(table_widget2->rowCount(), table_widget2->columnCount());

        // for all the items in the table
        for(int i = 0; i < table_widget2->rowCount(); i++)
        {
            for(int k = 0; k < table_widget2->columnCount(); k++)
            {
                QString s = table_widget2->item(i, k)->text();
                float value = s.toFloat();
                m2.setValue(i, k, value);
            }
        }

        m3.setSize(table_widget2->rowCount(), table_widget2->columnCount());
        m3 = m2.transpose();

       // As long as the display and matrix are the same size
       if((m3.getRows() == table_widget2->rowCount()) && (m3.getCols() == table_widget2->columnCount()))
       {
           for(int rows = 0; rows < m3.getRows(); rows++)
           {
               for(int cols = 0; cols < m3.getCols(); cols++)
               {
                   float value = m3.getValue(rows, cols);
                   QString b = QString::number(value);
                   table_widget2->item(rows, cols)->setText(b);
               }
           }
       }
    }

    else
    {
        // print error: not a square matrix
        QMessageBox::critical(this, "Square Matrix", "Not a square matrix.");
    }
}

/*------------------------------------------------------------- Functions for Second Matrix */

MainWindow::~MainWindow()
{
}

