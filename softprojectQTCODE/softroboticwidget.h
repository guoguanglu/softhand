#ifndef SOFTROBOTICWIDGET_H
#define SOFTROBOTICWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
//第一位表示是进气阀门值还是放气阀门值
//进气阀门发送数据
#define ON_finger1_IN           "0000000000000010"
#define OFF_finger1_IN          "0000000000000020"
#define ON_finger2_IN           "0000000000000030"
#define OFF_finger2_IN          "0000000000000040"
#define ON_finger3_IN           "0000000000000050"
#define OFF_finger3_IN          "0000000000000060"
#define ON_finger4_IN           "0000000000000070"
#define OFF_finger4_IN          "0000000000000080"
#define ON_finger5_IN           "0000000000000090"
#define OFF_finger5_IN          "0000000000000100"
#define ON_fingerall_IN         "0000000000000110"
#define OFF_fingerall_IN        "0000000000000120"

//放气阀门发送数据
#define ON_finger1_OUT           "1000000000000010"
#define OFF_finger1_OUT          "1000000000000020"
#define ON_finger2_OUT           "1000000000000030"
#define OFF_finger2_OUT          "1000000000000040"
#define ON_finger3_OUT           "1000000000000050"
#define OFF_finger3_OUT          "1000000000000060"
#define ON_finger4_OUT           "1000000000000070"
#define OFF_finger4_OUT          "1000000000000080"
#define ON_finger5_OUT           "1000000000000090"
#define OFF_finger5_OUT          "1000000000000100"
#define ON_fingerall_OUT         "1000000000000110"
#define OFF_fingerall_OUT        "1000000000000120"

namespace Ui {
class softroboticWidget;
}

class softroboticWidget : public QWidget
{
    Q_OBJECT

public:
    explicit softroboticWidget(QWidget *parent = 0);
    ~softroboticWidget();

private slots:

    void on_pushButtonnum1_in_clicked();

    void on_pushButtonnumall_in_clicked();

    void on_pushButtonnum2_in_clicked();

    void on_pushButtonnum3_in_clicked();

    void on_pushButtonnum4_in_clicked();

    void on_pushButtonnum5_in_clicked();

    void on_pushButtonnumall_out_clicked();

    void on_pushButtonnum1_out_clicked();

    void on_pushButtonnum2_out_clicked();

    void on_pushButtonnum3_out_clicked();

    void on_pushButtonnum4_out_clicked();

    void on_pushButtonnum5_out_clicked();

    void on_pushButtonopen_clicked();

    void Read_Data(void);

    void on_pushButtonclose_clicked();

    void on_pushButtonclear_clicked();

    void on_pushButtonstop_clicked();

    void on_pushButtonsend_clicked();

    void on_pushButtonbuttonmode_clicked();

    void on_pushButtongiveposemode_clicked();

    void on_pushButtonrestart_clicked();

    void on_pushButtonone_clicked();

    void on_pushButtontwo_clicked();

    void on_pushButtonthree_clicked();

    void on_pushButtonfour_clicked();

    void on_pushButtonfive_clicked();

private:
    Ui::softroboticWidget *ui;
    QSerialPort *serial;
    int stop_flag =1;
    int positiondata;
    int btnstop_flag=0;
    int num=0;
    int check;
    QString mode;//0按钮模式1给定姿态模式;
    int btnred_flag[6]={0,0,0,0,0,0};
    int btngreen_flag[6]={0,0,0,0,0,0};
    void setComBoxEnabled(bool status);
    void setbuttoncontrolEnabled(bool status);
    void setPushButtonEnabled(bool status);


};

#endif // SOFTROBOTICWIDGET_H
