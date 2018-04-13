#include "softroboticwidget.h"
#include "ui_softroboticwidget.h"
#include "QProcess"
#include <QMessageBox>
#include <QPainter>
#include <QMetaEnum>
#include <QDesktopWidget>
#include <QScreen>
softroboticWidget::softroboticWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::softroboticWidget)
{
    mode='0';//初始模式为按钮模式
    ui->setupUi(this);
   // ui->pushButton_3->setStyleSheet("border:2px groove gray;border-radius:13px;padding:2px 4px;");//改变按钮的形状
    ui->labelserialstatus->setText(tr("串口关闭"));
    //查找可用的串口
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->comboBoxserial->addItem(serial.portName());
            serial.close();
        }
    }
    //设定串口和姿态过去设定值默认值
    //设置比特率默认值第二项
    //设置数据位默认值第四项
    ui->comboBoxserial->setCurrentIndex(3);
    ui->comboBoxbaud->setCurrentIndex(4);
    ui->comboBoxdata->setCurrentIndex(3);
    ui->lineEditago1->setText(tr("000"));
    ui->lineEditago2->setText(tr("000"));
    ui->lineEditago3->setText(tr("000"));
    ui->lineEditago4->setText(tr("000"));
    ui->lineEditago5->setText(tr("000"));
    ui->lineEditnow1->setText(tr("000"));
    ui->lineEditnow2->setText(tr("000"));
    ui->lineEditnow3->setText(tr("000"));
    ui->lineEditnow4->setText(tr("000"));
    ui->lineEditnow5->setText(tr("000"));
    setPushButtonEnabled(false);
    ui->pushButtonbuttonmode->setEnabled(false);
    ui->pushButtonsend->setEnabled(false);
    qDebug()<<tr("界面设定成功");
}



softroboticWidget::~softroboticWidget()
{
    delete ui;
}

void softroboticWidget::on_pushButtonopen_clicked()
{
    serial=new QSerialPort;
    //设置串口名
    serial->setPortName(ui->comboBoxserial->currentText());
    //打开串口
    if(serial->open(QIODevice::ReadWrite))
    {
        ui->labelserialstatus->setText(tr("串口打开成功"));
  }else
    {
        ui->labelserialstatus->setText(tr("串口打开失败"));
        return;
    }
    //设置波特率
    serial->setBaudRate(ui->comboBoxbaud->currentText().toInt());
    //设置数据位数
    switch(ui->comboBoxdata->currentIndex())
    {
        case 8: serial->setDataBits(QSerialPort::Data8);break;
        default:break;
    }
    //设置奇偶校验
    switch(ui->comboBoxparity->currentIndex())
    {
        case 0: serial->setParity(QSerialPort::NoParity);break;
        default:break;
    }
    //设置停止位
    switch(ui->comboBoxstop->currentIndex())
    {
        case 1:serial->setStopBits(QSerialPort::OneStop);break;
        case 2:serial->setStopBits(QSerialPort::TwoStop);break;
        default: break;
    }
    //设置流控制
    serial->setFlowControl(QSerialPort::NoFlowControl);
    setComBoxEnabled(false);
    setPushButtonEnabled(true);
    ui->pushButtonopen->setEnabled(false);
    ui->pushButtonbuttonmode->setEnabled(false);
    ui->pushButtonsend->setEnabled(false);
    QObject::connect(serial,&QSerialPort::readyRead,this,&softroboticWidget::Read_Data);
}

void softroboticWidget::on_pushButtonclose_clicked()
{
    //关闭串口
    serial->clear();
    serial->close();
    serial->deleteLater();
    //回复使能
    setComBoxEnabled(true);
    setPushButtonEnabled(false);
    ui->pushButtonopen->setEnabled(true);
    ui->pushButtonbuttonmode->setEnabled(false);
    ui->pushButtonsend->setEnabled(false);
    ui->labelserialstatus->setText(tr("串口关闭"));

}

void softroboticWidget::on_pushButtonnum1_in_clicked()
{
    QString senddata;
    if(btnred_flag[1]==0)
    {
        ui->pushButtonnum1_in->setText("进");
        senddata=ON_finger1_IN;
        btnred_flag[1]=1;

    }
    else
    {
        ui->pushButtonnum1_in->setText("停");
        senddata=OFF_finger1_IN;
        btnred_flag[1]=0;

    }
    serial->write(senddata.toLatin1());
    serial->write("\r\n");
    qDebug()<<senddata.length()<<senddata;
    //发送数据控制手指1电磁阀进气阀     都是16个字节数最后一位控制模式


}

void softroboticWidget::on_pushButtonnumall_in_clicked()
{
    QString senddata;
    if(btnred_flag[0]==0)
    {
        ui->pushButtonnumall_in->setText("进");
        senddata=ON_fingerall_IN;
        btnred_flag[0]=1;
    }
    else
    {
        ui->pushButtonnumall_in->setText("停");
        senddata=OFF_fingerall_IN;
        btnred_flag[0]=0;
    }
    serial->write(senddata.toLatin1());
    serial->write("\r\n");
    qDebug()<<senddata.length()<<senddata;
    //发送数据控制所有手指电磁阀进气阀     都是16个字节数最后一位控制模式
}

void softroboticWidget::on_pushButtonnum2_in_clicked()
{
    QString senddata;
    if(btnred_flag[2]==0)
    {
        ui->pushButtonnum2_in->setText("进");
        senddata=ON_finger2_IN;
        btnred_flag[2]=1;
    }
    else
    {
        ui->pushButtonnum2_in->setText("停");
        senddata=OFF_finger2_IN;
        btnred_flag[2]=0;
    }
    serial->write(senddata.toLatin1());
    serial->write("\r\n");
    qDebug()<<senddata.length()<<senddata;
    //发送数据控制手指2电磁阀进气阀     都是16个字节数最后一位控制模式
}

void softroboticWidget::on_pushButtonnum3_in_clicked()
{
    QString senddata;
    if(btnred_flag[3]==0)
    {
        ui->pushButtonnum3_in->setText("进");
        senddata=ON_finger3_IN;
        btnred_flag[3]=1;
    }
    else
    {
        ui->pushButtonnum3_in->setText("停");
        senddata=OFF_finger3_IN;
        btnred_flag[3]=0;
    }
    serial->write(senddata.toLatin1());
    serial->write("\r\n");
    qDebug()<<senddata.length()<<senddata;
    //发送数据控制手指3电磁阀进气阀     都是16个字节数最后一位控制模式
}

void softroboticWidget::on_pushButtonnum4_in_clicked()
{
    QString senddata;
    if(btnred_flag[4]==0)
    {
        ui->pushButtonnum4_in->setText("进");
        senddata=ON_finger4_IN;
        btnred_flag[4]=1;
    }
    else
    {
        ui->pushButtonnum4_in->setText("停");
        senddata=OFF_finger4_IN;
        btnred_flag[4]=0;
    }
    serial->write(senddata.toLatin1());
    serial->write("\r\n");
    qDebug()<<senddata.length()<<senddata;
    //发送数据控制手指4电磁阀进气阀     都是16个字节数最后一位控制模式
}

void softroboticWidget::on_pushButtonnum5_in_clicked()
{
    QString senddata;
    if(btnred_flag[5]==0)
    {
        ui->pushButtonnum5_in->setText("进");
        senddata=ON_finger5_IN;
        btnred_flag[5]=1;
    }
    else
    {
        ui->pushButtonnum5_in->setText("停");
        senddata=OFF_finger5_IN;
        btnred_flag[5]=0;
    }
    serial->write(senddata.toLatin1());
    serial->write("\r\n");
    qDebug()<<senddata.length()<<senddata;
    //发送数据控制手指5电磁阀进气阀     都是16个字节数最后一位控制模式
}

void softroboticWidget::on_pushButtonnumall_out_clicked()
{
    QString senddata;
    if(btngreen_flag[0]==0)
    {
        ui->pushButtonnumall_out->setText("放");
        senddata=ON_fingerall_OUT;
        btngreen_flag[0]=1;
    }
    else
    {
        ui->pushButtonnumall_out->setText("停");
        senddata=OFF_fingerall_OUT;
        btngreen_flag[0]=0;
    }
        serial->write(senddata.toLatin1());
        serial->write("\r\n");

    qDebug()<<senddata.length()<<senddata;
    //发送数据控制所有手指电磁阀放气阀     都是16个字节数最后一位控制模式
}

void softroboticWidget::on_pushButtonnum1_out_clicked()
{
    QString senddata;
    if(btngreen_flag[1]==0)
    {
        ui->pushButtonnum1_out->setText("放");
        senddata=ON_finger1_OUT;
        btngreen_flag[1]=1;

    }
    else
    {
        ui->pushButtonnum1_out->setText("停");
        senddata=OFF_finger1_OUT;
        btngreen_flag[1]=0;
    }
    serial->write(senddata.toLatin1());
    serial->write("\r\n");
    qDebug()<<senddata.length()<<senddata;
    //发送数据控制手指1电磁阀放气阀     都是16个字节数最后一位控制模式
}

void softroboticWidget::on_pushButtonnum2_out_clicked()
{
     QString senddata;
    if(btngreen_flag[2]==0)
    {
        ui->pushButtonnum2_out->setText("放");
        senddata=ON_finger2_OUT;
        btngreen_flag[2]=1;
    }
    else
    {
        ui->pushButtonnum2_out->setText("停");
        senddata=OFF_finger2_OUT;
        btngreen_flag[2]=0;
    }
    serial->write(senddata.toLatin1());
    serial->write("\r\n");
    qDebug()<<senddata.length()<<senddata;
    //发送数据控制手指2电磁阀放气阀     都是16个字节数最后一位控制模式
}

void softroboticWidget::on_pushButtonnum3_out_clicked()
{
     QString senddata;
    if(btngreen_flag[3]==0)
    {
        ui->pushButtonnum3_out->setText("放");
        senddata=ON_finger3_OUT;
        btngreen_flag[3]=1;
    }
    else
    {
        ui->pushButtonnum3_out->setText("停");
        senddata=OFF_finger3_OUT;
        btngreen_flag[3]=0;
    }
    serial->write(senddata.toLatin1());
    serial->write("\r\n");
    qDebug()<<senddata.length()<<senddata;
    //发送数据控制手指3电磁阀放气阀     都是16个字节数最后一位控制模式
}

void softroboticWidget::on_pushButtonnum4_out_clicked()
{
    QString senddata;
    if(btngreen_flag[4]==0)
    {
        ui->pushButtonnum4_out->setText("放");
        senddata=ON_finger4_OUT;
        btngreen_flag[4]=1;
    }
    else
    {
        ui->pushButtonnum4_out->setText("停");
        senddata=OFF_finger4_OUT;
        btngreen_flag[4]=0;
    }
    serial->write(senddata.toLatin1());
    serial->write("\r\n");
    qDebug()<<senddata.length()<<senddata;
    //发送数据控制手指4电磁阀放气阀     都是16个字节数最后一位控制模式
}

void softroboticWidget::on_pushButtonnum5_out_clicked()
{
    QString senddata;
    if(btngreen_flag[5]==0)
    {
        ui->pushButtonnum5_out->setText("放");
        senddata=ON_finger5_OUT;
        btngreen_flag[5]=1;
    }
    else
    {
        ui->pushButtonnum5_out->setText("停");
        senddata=OFF_finger5_OUT;
        btngreen_flag[5]=0;
    }
    serial->write(senddata.toLatin1());
    serial->write("\r\n");
    qDebug()<<senddata.length()<<senddata;
    //发送数据控制手指5电磁阀放气阀     都是16个字节数最后一位控制模式
}

void softroboticWidget::setComBoxEnabled(bool status)
{
    ui->comboBoxserial->setEnabled(status);
    ui->comboBoxbaud->setEnabled(status);
    ui->comboBoxdata->setEnabled(status);
    ui->comboBoxparity->setEnabled(status);
    ui->comboBoxstop->setEnabled(status);
}

void softroboticWidget::setPushButtonEnabled(bool status)
{
    ui->pushButtonclose->setEnabled(status);
    ui->pushButtonnum1_in->setEnabled(status);
    ui->pushButtonnum2_in->setEnabled(status);
    ui->pushButtonnum3_in->setEnabled(status);
    ui->pushButtonnum4_in->setEnabled(status);
    ui->pushButtonnum5_in->setEnabled(status);
    ui->pushButtonnumall_in->setEnabled(status);
    ui->pushButtonnum1_out->setEnabled(status);
    ui->pushButtonnum2_out->setEnabled(status);
    ui->pushButtonnum3_out->setEnabled(status);
    ui->pushButtonnum4_out->setEnabled(status);
    ui->pushButtonnum5_out->setEnabled(status);
    ui->pushButtonnumall_out->setEnabled(status);
    ui->pushButtonstop->setEnabled(status);
    ui->pushButtonclear->setEnabled(status);
    ui->pushButtongiveposemode->setEnabled(status);
}

void softroboticWidget::setbuttoncontrolEnabled(bool status)
{
    ui->pushButtonnum1_in->setEnabled(status);
    ui->pushButtonnum2_in->setEnabled(status);
    ui->pushButtonnum3_in->setEnabled(status);
    ui->pushButtonnum4_in->setEnabled(status);
    ui->pushButtonnum5_in->setEnabled(status);
    ui->pushButtonnumall_in->setEnabled(status);
    ui->pushButtonnum1_out->setEnabled(status);
    ui->pushButtonnum2_out->setEnabled(status);
    ui->pushButtonnum3_out->setEnabled(status);
    ui->pushButtonnum4_out->setEnabled(status);
    ui->pushButtonnum5_out->setEnabled(status);
    ui->pushButtonnumall_out->setEnabled(status);
}

void softroboticWidget::Read_Data()
{
    QByteArray buf;
    QStringList list;
    QString position;

      buf+=serial->readAll();
      QString ReSt(buf);
      list = ReSt.split(QRegExp("\\s+"));
      check=list.length();
  if(check==7)
  {
   if(list[6].toInt()==1)//用来把反馈的数值与给定的数值分开
   {
      if(!buf.isEmpty())
      {
         QString str=ui->textEditposefeedback->toPlainText();
         str+=tr("finger1: ")+list[0]+tr("\n")+
              tr("finger2: ")+list[1]+tr("\n")+
              tr("finger3: ")+list[2]+tr("\n")+
              tr("finger4: ")+list[3]+tr("\n")+
              tr("finger5: ")+list[4]+tr("\n")+
              tr("电机电压：")+list[5]+tr("\n");
         //str+=tr("finger1: ")+list[0]+tr("  电机电压：")+list[6]+tr("\n");
         if(stop_flag==1)//停止标志位
         {
             ui->textEditposefeedback->clear();
             ui->textEditposefeedback->append(str);
         }
      }
      if(num>60)
      {
           ui->textEditposefeedback->clear();
           num=0;
      }
    }else
    {
        ui->lineEditago1->setText(list[0]);
        ui->lineEditago2->setText(list[1]);
        ui->lineEditago3->setText(list[2]);
        ui->lineEditago4->setText(list[3]);
        ui->lineEditago5->setText(list[4]);
    }
      position=list[1];
      positiondata=position.toInt();
      qDebug()<<positiondata<<list.length();
      buf.clear();
 }else
  {
     qDebug()<<tr("接收失败")<<list.length();
     ui->textEditposefeedback->clear();
     buf.clear();
//     qApp->closeAllWindows();
//     QProcess::startDetached(qApp->applicationFilePath(),QStringList());

  }
  num++;

}


void softroboticWidget::on_pushButtonclear_clicked()
{
    ui->textEditposefeedback->clear();
}

void softroboticWidget::on_pushButtonstop_clicked()
{
    if(btnstop_flag==0)
    {
        ui->pushButtonstop->setText("停止");
        btnstop_flag=1;
        stop_flag=0;
    }
    else
    {
        ui->pushButtonstop->setText("运行");
        btnstop_flag=0;
        stop_flag=1;
    }
}

void softroboticWidget::on_pushButtonsend_clicked()
{
    QString sum;
    QString finger1=ui->lineEditnow1->text();
    QString finger2=ui->lineEditnow2->text();
    QString finger3=ui->lineEditnow3->text();
    QString finger4=ui->lineEditnow4->text();
    QString finger5=ui->lineEditnow5->text();

    while(finger1.length()<3)//还没考虑大于的情况
     {
         finger1='0'+finger1;
     }
    while(finger2.length()<3)//还没考虑大于的情况
     {
         finger2='0'+finger2;
     }
    while(finger3.length()<3)//还没考虑大于的情况
     {
         finger3='0'+finger3;
     }
    while(finger4.length()<3)//还没考虑大于的情况
     {
         finger4='0'+finger4;
     }
    while(finger5.length()<3)//还没考虑大于的情况
     {
         finger5='0'+finger5;
     }
     sum=finger1+finger2+finger3+finger4+finger5+mode;
     serial->write(sum.toLatin1());
     serial->write("\r\n");
     qDebug()<<sum.length()<<"\n"<<sum<<"\nfinger1:"<<finger1<<"\tfinger2:"<<finger2<<"\tfinger3:"<<finger3<<"\tfinger4:"<<finger4<<"\tfinger5:"<<finger5;
     ui->lineEditnow1->clear();
     ui->lineEditnow2->clear();
     ui->lineEditnow3->clear();
     ui->lineEditnow4->clear();
     ui->lineEditnow5->clear();

}

void softroboticWidget::on_pushButtonbuttonmode_clicked()
{
    QString senddata;
    ui->pushButtonbuttonmode->setEnabled(false);
    ui->pushButtongiveposemode->setEnabled(true);
    ui->pushButtonsend->setEnabled(false);
    mode='0';
    setbuttoncontrolEnabled(true);
    senddata=OFF_fingerall_IN;
//    serial->write(senddata.toLatin1());
//    serial->write("\r\n");
}

void softroboticWidget::on_pushButtongiveposemode_clicked()
{
    QString senddata;
    ui->pushButtonbuttonmode->setEnabled(true);
    ui->pushButtongiveposemode->setEnabled(false);
    ui->pushButtonsend->setEnabled(true);

    mode='1';
    setbuttoncontrolEnabled(false);
    senddata="0000000000000001";
    serial->write(senddata.toLatin1());
    serial->write("\r\n");
}

void softroboticWidget::on_pushButtonrestart_clicked()
{
    qApp->closeAllWindows();
    QProcess::startDetached(qApp->applicationFilePath(),QStringList());

}

void softroboticWidget::on_pushButtonone_clicked()
{
    QString senddata;
    senddata="1000001501701501";
    serial->write(senddata.toLatin1());
    serial->write("\r\n");
}

void softroboticWidget::on_pushButtontwo_clicked()
{
    QString senddata;
    senddata="1000000001701501";
    serial->write(senddata.toLatin1());
    serial->write("\r\n");
}

void softroboticWidget::on_pushButtonthree_clicked()
{
    QString senddata;
    senddata="1000000000001501";
    serial->write(senddata.toLatin1());
    serial->write("\r\n");
}

void softroboticWidget::on_pushButtonfour_clicked()
{
    QString senddata;
    senddata="1000000000000001";
    serial->write(senddata.toLatin1());
    serial->write("\r\n");
}

void softroboticWidget::on_pushButtonfive_clicked()
{
    QString senddata;
    senddata="0000000000000001";
    serial->write(senddata.toLatin1());
    serial->write("\r\n");
}
