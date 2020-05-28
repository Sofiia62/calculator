#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

double first_num;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(digits_nums()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(digits_nums()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(digits_nums()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(digits_nums()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(digits_nums()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(digits_nums()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(digits_nums()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(digits_nums()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(digits_nums()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(digits_nums()));
    connect(ui->pushButton_sign,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_percent,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_div,SIGNAL(clicked()),this,SLOT(math()));
    connect(ui->pushButton_mul,SIGNAL(clicked()),this,SLOT(math()));
    connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(math()));
    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(math()));

    ui->pushButton_div->setCheckable(true);
    ui->pushButton_mul->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_nums(){
    QPushButton *button = (QPushButton *)sender();

    double numbers;
    QString new_label;

    if(ui->label->text().contains(".") && button->text() == "0"){
        new_label = ui->label->text()+ button->text();
    }else{
        numbers = (ui->label->text()+ button->text()).toDouble();
        new_label = QString::number(numbers,'g',15);
    }
    ui->label->setText(new_label);
}

void MainWindow::on_pushButton_dot_clicked()
{
    if(!ui->label->text().contains('.')){
        ui->label->setText(ui->label->text() + ".");
    }
}

void MainWindow::operations(){
    QPushButton *button = (QPushButton *)sender();
    double numbers;
    QString new_label;

    if(button->text() == "+/-"){
        numbers = (ui->label->text()).toDouble();
        numbers = numbers * -1;
        new_label = QString::number(numbers,'g',15);

        ui->label->setText(new_label);
    }else if(button->text() == "%"){
        numbers = (ui->label->text()).toDouble();
        numbers = numbers * 0.01;
        new_label = QString::number(numbers,'g',15);

        ui->label->setText(new_label);
    }
}

void MainWindow::math()
{
  QPushButton *button = (QPushButton *)sender();

  first_num = ui->label->text().toDouble();
  ui->label->setText("");
  button->setChecked(true);

}

void MainWindow::on_pushButton_ac_clicked()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_mul->setChecked(false);
    ui->pushButton_div->setChecked(false);

    ui->label->setText("0");
}

void MainWindow::on_pushButton_res_clicked()
{
    double labelNum, second_num;
    QString new_label;

    second_num = ui->label->text().toDouble();

    if(ui->pushButton_plus->isChecked()){
        labelNum = first_num + second_num;
        new_label = QString::number(labelNum,'g',15);

        ui->label->setText(new_label);
        ui->pushButton_plus->setChecked(false);
    }else if(ui->pushButton_minus->isChecked()){
        labelNum = first_num - second_num;
        new_label = QString::number(labelNum,'g',15);

        ui->label->setText(new_label);
        ui->pushButton_minus->setChecked(false);
    }else if(ui->pushButton_div->isChecked()){
        if(second_num == 0){
          ui->label->setText("Eror");
        }else{
           labelNum = first_num / second_num;
           new_label = QString::number(labelNum,'g',15);

           ui->label->setText(new_label);
        }
        ui->pushButton_div->setChecked(false);
    }else if(ui->pushButton_mul->isChecked()){

        labelNum = first_num * second_num;
        new_label = QString::number(labelNum,'g',15);

        ui->label->setText(new_label);
        ui->pushButton_mul->setChecked(false);
  }
    this->DB = QSqlDatabase::addDatabase("QSQLITE");
    this->DB.setDatabaseName(this->pathDB);
    if(this->DB.open()){
     this->query.exec("INSERT INTO last_results VALUES (new_label)");
     this->query.exec("INSERT INTO last_results VALUES (500)");
    }
}



void MainWindow::on_result_show_clicked()
{
    this->pathDB = QFileDialog::getOpenFileName(this, "Open db", "", "Data Base (*db)");
    this->DB = QSqlDatabase::addDatabase("QSQLITE");
    this->DB.setDatabaseName(this->pathDB);

    if(this->DB.open()){
       this->query = QSqlQuery(this->DB);
       this->showData();
    }
}

void MainWindow::showData()
{

   // for(const QString & table_numbers : this->DB.tables()){
     //   ui->table_numbers;
    //}
 //   for(int i=0; i< query.record().count(); i++)
   //     ui->->>addItem(query.record().field(i).name());
    this->query.exec("SELECT * FROM numbers");
    this->addValues();
}

void MainWindow::addValues(){
    while(query.next())
        ui->listWidget->addItem(query.value(0).toString());
}
