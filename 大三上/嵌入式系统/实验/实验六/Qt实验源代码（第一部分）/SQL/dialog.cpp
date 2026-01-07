#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("数据库增删改查");
    QWidget::setWindowState(Qt::WindowActive);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    connectDb();
    connect(ui->pushButton_insert,SIGNAL(clicked()),this,SLOT(btnInsterSlot()));
    connect(ui->pushButton_delete,SIGNAL(clicked()),this,SLOT(btnDeleteSlot()));
    connect(ui->pushButton_select,SIGNAL(clicked()),this,SLOT(btnSelectSlot()));
    connect(ui->pushButton_update,SIGNAL(clicked()),this,SLOT(btnUpdateSlot()));
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Dialog::~Dialog()
{
    //关闭数据库
    if(database.isOpen())
        database.close();
    delete ui;
}

void Dialog::connectDb()
{
    //使用Sqlite的驱动获得数据库连接的对象
  database = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库文件的名称
  database.setDatabaseName("Student_info.db");
    //设置用户名 密码
  database.setUserName("ygc");
  database.setPassword("123");
  if(database.open())
  {
      qDebug() << "数据库连接成功";
      //连接成功，建表
    createTable();
  }
  else
  {
      //连接失败
    QSqlError error = database.lastError();
    QMessageBox::critical(this,"错误",error.text());
  }
}

void Dialog::createTable()
{
    //创建一个数据库操作对象
    QSqlQuery sq;
    QString sql = "CREATE TABLE Student(id INTEGER PRIMARY KEY,\
                     name TEXT NOT NULL,age INTEGER)";
    if(sq.exec(sql))
        qDebug() << "建表成功";
    else
        qDebug() << sq.lastError().text();
}


void Dialog::btnInsterSlot()
{
    QString name = ui->lineEdit_name->text();
    if (name == "")
    {
        QMessageBox::warning(this,"警告","请输入完整的信息");
        return;
    }
    int id = ui->spinBox_id->value();
    int age = ui->spinBox_age->value();
    QSqlQuery sq;
    //防止sql注入问题，预处理(:id,:name,:age)
    QString sql = "INSERT INTO student VALUES(?,?,?)";
    //预处理
    sq.prepare(sql);
    //占位符数据替换
    sq.addBindValue(id);
    sq.addBindValue(name);
    sq.addBindValue(age);
    //执行sql语句
    if(sq.exec())
    {
        btnSelectSlot();
        QMessageBox::information(this,"通知","添加成功");
    }
    else
    {
        QString errorMsg = sq.lastError().text();
        QMessageBox::critical(this,"错误",errorMsg);
    }
}

void Dialog::btnDeleteSlot()
{

    int id = ui->spinBox_id->value();
   //判断是否存在
    if(!isStudentExist(id))
    {
        QMessageBox::warning(this,"警告","此学号的学生不存在");
        return;
    }
    QSqlQuery sq;
    //防止sql注入问题，预处理(:id,:name,:age)
    QString sql = "DELETE FROM student WHERE id=:id";
    //预处理
    sq.prepare(sql);
    //占位符数据替换
    sq.addBindValue(id);
    //执行sql语句
    if(sq.exec())
    {
         btnSelectSlot();
        QMessageBox::information(this,"通知","删除成功");
    }
    else
    {
        QString errorMsg = sq.lastError().text();
        QMessageBox::critical(this,"删除失败",errorMsg);
    }
}
// 更新固定学号的人
void Dialog::btnUpdateSlot()
{
    QString name = ui->lineEdit_name->text();
    if (name == "")
    {
        QMessageBox::warning(this,"警告","请输入完整的信息");
        return;
    }
    int id = ui->spinBox_id->value();
    int age = ui->spinBox_age->value();
    //判断是否存在
     if(!isStudentExist(id))
     {
         QMessageBox::warning(this,"警告","此学号的学生不存在");
         return;
     }
    QSqlQuery sq;
    //防止sql注入问题，预处理(:id,:name,:age)
    QString sql = "UPDATE student SET name=:name,age=:age WHERE id=:id";
    //预处理
    sq.prepare(sql);
    //占位符数据替换
    sq.addBindValue(name);
    sq.addBindValue(age);
    sq.addBindValue(id);
    //执行sql语句
    if(sq.exec())
    {
         btnSelectSlot();
        QMessageBox::information(this,"通知","修改成功");
    }
    else
    {
        QString errorMsg = sq.lastError().text();
        QMessageBox::critical(this,"修改失败",errorMsg);
    }
}

void Dialog::btnSelectSlot()
{
    //清空之前的显示
   ui->tableWidget->setRowCount(0);
    QSqlQuery sq;
    QString sql = "SELECT * FROM student ";
    //执行sql语句
    if(sq.exec(sql))
    {
        //遍历
      while(sq.next())
      {
          int id = sq.value("id").toInt();
          QString name =sq.value("name").toString();
          int age =sq.value("age").toInt();
          qDebug() << id << name << age;
          //获取当前表格中的行数
          int rowCount = ui->tableWidget->rowCount();
          //添加空白行
          ui->tableWidget->insertRow(rowCount);
          //给空白行添加数据
          ui->tableWidget->setItem(rowCount,0,new QTableWidgetItem(QString::number(id)));
          ui->tableWidget->setItem(rowCount,1,new QTableWidgetItem(name));
          ui->tableWidget->setItem(rowCount,2,new QTableWidgetItem(QString::number(age)));
      }
    }
    else
    {
        QString errorMsg = sq.lastError().text();
        QMessageBox::critical(this,"执行失败",errorMsg);
    }
}


/**
 * @brief Dialog::isStudentExist
 * @param id 判断输入学号的学生是否存在
 * @return
 */
bool Dialog::isStudentExist(int id)
{
    QSqlQuery sq;
    //防止sql注入问题，预处理(:id,:name,:age)
    QString sql = "SELECT * FROM student WHERE id=:id";
    //预处理
    sq.prepare(sql);
    //占位符数据替换
    sq.addBindValue(id);
    //执行sql语句
    if(sq.exec())
    {
        return sq.next();
    }
    else
    {
        return false;
    }
}



