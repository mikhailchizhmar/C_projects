#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  graphwindow = new GraphWindow();
  // connect(graphwindow, &GraphWindow::firstWindow(), this,
  // &MainWindow::show());

  ui->doubleSpinBox_X->setMaximum(100000000);
  ui->doubleSpinBox_X->setMinimum(-100000000);
  ui->doubleSpinBox_Xmax->setMaximum(10000000);
  ui->doubleSpinBox_Xmax->setMinimum(-10000000);
  ui->doubleSpinBox_Ymax->setMaximum(10000000);
  ui->doubleSpinBox_Ymax->setMinimum(-10000000);

  // ui->doubleSpinBox_Xmax->

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(button_pressed()));

  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this,
          SLOT(button_pressed()));
  connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this,
          SLOT(button_pressed()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(button_pressed()));
  connect(ui->pushButton_power, SIGNAL(clicked()), this,
          SLOT(button_pressed()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(button_pressed()));

  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(button_pressed()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(button_pressed()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::button_pressed() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  ui->label_answer->setText("");
  ui->lineEdit_input->setText(ui->lineEdit_input->text() + button->text());
}

void MainWindow::on_pushButton_C_clicked() {
  ui->label_answer->setText("");
  ui->lineEdit_input->setText("");
}

void MainWindow::on_pushButton_delete_clicked() {
  ui->lineEdit_input->backspace();
}

void MainWindow::on_pushButton_equal_clicked() {
  QByteArray str = (ui->lineEdit_input->text()).toLocal8Bit();
  char *res_str = str.data();
  int len_str = strlen(res_str);
  if (len_str > 255) {
    ui->label_answer->setText("Слишком длинная строка!");
  } else {
    if (!validation(res_str)) {
      ui->label_answer->setText("Ошибка!");
    } else {
      double result = calculate(res_str, ui->doubleSpinBox_X->value());
      ui->label_answer->setText(QString::number(result, 'g', 15));
    }
  }
}

void MainWindow::on_pushButton_plot_clicked() {
  QByteArray func_str = (ui->lineEdit_input->text()).toLocal8Bit();
  char *res_func_str = func_str.data();

  if (!validation(res_func_str)) {
    ui->label_answer->setText("Ошибка!");
  } else {
    double step = 0.01, x0, Xmax = ui->doubleSpinBox_Xmax->value();

    QVector<double> x, y;
    x.clear();
    y.clear();

    for (x0 = -Xmax; x0 <= Xmax; x0 += step) {
      x.push_back(x0);
      y.push_back(calculate(res_func_str, x0));
    }

    graphwindow->plot(x, y, ui->doubleSpinBox_Ymax->value(),
                      ui->doubleSpinBox_Xmax->value());
    graphwindow->show();
  }
}
