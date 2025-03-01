#pragma once

#include <QtWidgets/QMainWindow>
#include <QScreen>
#include <QApplication>
#include <QFont>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDateTime>
#include <QMessageBox>


class Serial_Helper : public QMainWindow
{
	Q_OBJECT

public:
	Serial_Helper(QWidget* parent = nullptr);
	~Serial_Helper();

	void setArea_Init();
	void dataArea_Init();
	void serialPort_Init();
	void btnEvent_Init();
	void timerEvent(QTimerEvent* event);

private:
	QRect winSize;
	QHBoxLayout* mainHBoxLayout;
	QWidget* setWidget;     //左侧设置界面
	QWidget* dataWidget;    //右侧数据界面

	/*设置区域*/
	//端口设置
	QVBoxLayout* setVBoxLayout;     //设置界面垂直布局
	QFormLayout* portFormLayout;    //端口设置网格布局
	QFormLayout* dataFormLayout;    //数据设置网格布局

	QLabel* portNameLabel;          //端口号
	QLabel* baudRateLabel;          //波特率
	QLabel* dataBitsLabel;          //数据位
	QLabel* stopBitsLabel;          //停止位
	QLabel* parityLabel;            //校验位
	QLabel* actionLabel;            //操作

	QComboBox* portNameComboBox;    //端口号
	QComboBox* baudRateComboBox;    //波特率
	QComboBox* dataBitsComboBox;    //数据位
	QComboBox* stopBitsComboBox;    //停止位
	QComboBox* parityComboBox;      //校验位
	QPushButton* actionButton;      //操作

	//数据设置
	QLabel* recvModeLabel;			//接收模式
	QLabel* sendModeLabel;			//发送模式
	QComboBox* recvModeComboBox;	//接收模式
	QComboBox* sendModeComboBox;	//发送模式

    QPushButton* clearRecvButton;	//清空接收区
    QPushButton* clearSendButton;	//清空发送区

	/*数据区域*/
	QVBoxLayout* dataVBoxLayout;
    QHBoxLayout* dataHBoxLayout;
	QLabel* recvLabel;
    QLabel* sendLabel;
	QPlainTextEdit* recvPlainTextEdit;
	QPlainTextEdit* sendPlainTextEdit;
    QPushButton* sendButton;

	/*串口通信*/
    QSerialPort* serialPort;
	QVector<QString> ports;
};
