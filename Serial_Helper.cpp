#include "Serial_Helper.h"

Serial_Helper::Serial_Helper(QWidget* parent)
	: QMainWindow(parent)
{
	this->setWindowTitle("串口助手");
	winSize = QApplication::primaryScreen()->geometry();
	this->resize(winSize.width() * 0.45, winSize.height() * 0.5);  // 按比例设置窗口大小

	QFont font = QApplication::font();
	font.setPointSize(11);
    this->setFont(font);

	setCentralWidget(new QWidget(this));        // 设置中心窗口
	QStatusBar* statusBar = this->statusBar();  // 设置状态栏
	mainHBoxLayout = new QHBoxLayout(this);     // 设置主窗口的布局
	setWidget = new QWidget(this);              // 设置设置窗口
	dataWidget = new QWidget(this);             // 设置数据窗口

	mainHBoxLayout->addWidget(setWidget, 1);
	mainHBoxLayout->addWidget(dataWidget, 4);

	statusBar->showMessage("欢迎使用串口助手！");
	this->centralWidget()->setLayout(mainHBoxLayout);

	setArea_Init();
	dataArea_Init();
	btnEvent_Init();
	this->startTimer(500);
}

Serial_Helper::~Serial_Helper()
{
}

void Serial_Helper::setArea_Init()
{
	setVBoxLayout = new QVBoxLayout(this);
	setWidget->setLayout(setVBoxLayout);

	/*端口设置*/
	portNameLabel = new QLabel("端口号", this);
	baudRateLabel = new QLabel("波特率", this);
	dataBitsLabel = new QLabel("数据位", this);
	stopBitsLabel = new QLabel("停止位", this);
	parityLabel = new QLabel("校验位", this);
	actionLabel = new QLabel("操作", this);

	portNameComboBox = new QComboBox(this);
	baudRateComboBox = new QComboBox(this);
	dataBitsComboBox = new QComboBox(this);
	stopBitsComboBox = new QComboBox(this);
	parityComboBox = new QComboBox(this);
	actionButton = new QPushButton("打开串口", this);

	// 波特率
	baudRateComboBox->addItem("9600");
	baudRateComboBox->addItem("19200");
	baudRateComboBox->addItem("38400");
	baudRateComboBox->addItem("57600");
	baudRateComboBox->addItem("115200");

	// 数据位
	dataBitsComboBox->addItem("5");
	dataBitsComboBox->addItem("6");
	dataBitsComboBox->addItem("7");
	dataBitsComboBox->addItem("8");

	// 停止位
	stopBitsComboBox->addItem("1");
	stopBitsComboBox->addItem("1.5");
	stopBitsComboBox->addItem("2");

	// 校验位
	parityComboBox->addItem("NONE");
	parityComboBox->addItem("ODD");
	parityComboBox->addItem("EVEN");

	dataBitsComboBox->setCurrentIndex(3);

	portFormLayout = new QFormLayout(this);
	portFormLayout->addRow(portNameLabel, portNameComboBox);
	portFormLayout->addRow(baudRateLabel, baudRateComboBox);
	portFormLayout->addRow(dataBitsLabel, dataBitsComboBox);
	portFormLayout->addRow(stopBitsLabel, stopBitsComboBox);
	portFormLayout->addRow(parityLabel, parityComboBox);
	portFormLayout->addRow(actionLabel, actionButton);
	setVBoxLayout->addLayout(portFormLayout);
	setVBoxLayout->addStretch();

	/*数据设置*/
	recvModeLabel = new QLabel("接收模式", this);
	sendModeLabel = new QLabel("发送模式", this);

	recvModeComboBox = new QComboBox(this);
	sendModeComboBox = new QComboBox(this);

	recvModeComboBox->addItem("HEX");
	recvModeComboBox->addItem("TEXT");
	sendModeComboBox->addItem("HEX");
	sendModeComboBox->addItem("TEXT");

	dataFormLayout = new QFormLayout(this);
	dataFormLayout->addRow(recvModeLabel, recvModeComboBox);
	dataFormLayout->addRow(sendModeLabel, sendModeComboBox);
	setVBoxLayout->addLayout(dataFormLayout);
	setVBoxLayout->addStretch();
	
	clearRecvButton = new QPushButton("清空接收区", this);
	clearSendButton = new QPushButton("清空发送区", this);
	setVBoxLayout->addWidget(clearRecvButton);
	setVBoxLayout->addWidget(clearSendButton);
}

void Serial_Helper::dataArea_Init()
{
	dataVBoxLayout = new QVBoxLayout(this);
	dataWidget->setLayout(dataVBoxLayout);

	recvLabel = new QLabel("接收区", this);
	sendLabel = new QLabel("发送区", this);

	recvPlainTextEdit = new QPlainTextEdit(this);
	sendPlainTextEdit = new QPlainTextEdit(this);

	recvPlainTextEdit->setReadOnly(true);
	dataVBoxLayout->addWidget(recvLabel);
	dataVBoxLayout->addWidget(recvPlainTextEdit);
	dataVBoxLayout->addWidget(sendLabel);
	dataVBoxLayout->addWidget(sendPlainTextEdit);
	dataVBoxLayout->setStretch(1, 2);
	dataVBoxLayout->setStretch(3, 1);

	sendButton = new QPushButton("发送", this);
	dataHBoxLayout = new QHBoxLayout(this);

	sendButton->setEnabled(false);
	dataHBoxLayout->addStretch();
	dataHBoxLayout->addWidget(sendButton);
	dataVBoxLayout->addLayout(dataHBoxLayout);
}

void Serial_Helper::serialPort_Init()
{
	QSerialPort::BaudRate baudRate;
	QSerialPort::DataBits dataBits;
	QSerialPort::StopBits stopBits;
	QSerialPort::Parity parity;

	QString portNameStr = portNameComboBox->currentText();
	QString baudRateStr = baudRateComboBox->currentText();
	QString dataBitsStr = dataBitsComboBox->currentText();
	QString stopBitsStr = stopBitsComboBox->currentText();
	QString parityStr = parityComboBox->currentText();

	if (baudRateStr == "9600")
		baudRate = QSerialPort::Baud9600;
	else if (baudRateStr == "19200")
		baudRate = QSerialPort::Baud19200;
	else if (baudRateStr == "38400")
		baudRate = QSerialPort::Baud38400;
	else if (baudRateStr == "57600")
		baudRate = QSerialPort::Baud57600;
	else if (baudRateStr == "115200")
		baudRate = QSerialPort::Baud115200;

	if (dataBitsStr == "5")
		dataBits = QSerialPort::Data5;
	else if (dataBitsStr == "6")
		dataBits = QSerialPort::Data6;
	else if (dataBitsStr == "7")
		dataBits = QSerialPort::Data7;
	else if (dataBitsStr == "8")
		dataBits = QSerialPort::Data8;

	if (stopBitsStr == "1")
		stopBits = QSerialPort::OneStop;
	else if (stopBitsStr == "1.5")
		stopBits = QSerialPort::OneAndHalfStop;
	else if (stopBitsStr == "2")
		stopBits = QSerialPort::TwoStop;

	if (parityStr == "NONE")
		parity = QSerialPort::NoParity;
	else if (parityStr == "ODD")
		parity = QSerialPort::OddParity;
	else if (parityStr == "EVEN")
		parity = QSerialPort::EvenParity;

	serialPort = new QSerialPort(this);
	serialPort->setPortName(portNameStr);
	serialPort->setBaudRate(baudRate);
	serialPort->setDataBits(dataBits);
	serialPort->setStopBits(stopBits);
	serialPort->setParity(parity);

	if (serialPort->open(QSerialPort::ReadWrite))
	{
		connect(serialPort, &QSerialPort::readyRead, [=]() {
			QString localTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");    // 获取本地时间
			auto recvData = serialPort->readAll();    // 读取串口数据

			static QByteArray buffer; // 用于缓存接收到的数据
			buffer.append(recvData);  // 把接收到的数据追加到缓存中

			if (buffer.endsWith('\n') || buffer.endsWith("\r\n"))
			{
				QString displayText;
				QString data;
				if (recvModeComboBox->currentText() == "HEX")	// HEX模式
					data = buffer.toHex(' ');
				else											// TEXT模式				
					data = QString::fromUtf8(buffer);

				displayText = QString("[%1] %2").arg(localTime).arg(data);

				buffer.clear();
				recvPlainTextEdit->setUpdatesEnabled(false);
				recvPlainTextEdit->insertPlainText(displayText + "\n");  // 显示当前接收到的行
				recvPlainTextEdit->setUpdatesEnabled(true);

				QScrollBar* scrollBar = recvPlainTextEdit->verticalScrollBar();	// 滚动条自动下滑
				scrollBar->setValue(scrollBar->maximum());
			}
			});
	}
	else
		QMessageBox::critical(this, "错误", "串口打开失败");
}

void Serial_Helper::btnEvent_Init()
{
	connect(actionButton, &QPushButton::clicked, [=]() {
		if (actionButton->text() == "打开串口")
		{
			if (portNameComboBox->currentText() != "")
			{
				serialPort_Init();	// 初始化串口
				actionButton->setText("关闭串口");
				sendButton->setEnabled(true);
			}
			else
			{
				QMessageBox::critical(this, "错误", "串口打开失败，请检查串口是否连接正确");
			}
		}
		else
		{
			serialPort->close();	// 关闭串口
			actionButton->setText("打开串口");
			sendButton->setEnabled(false);
		}
		});

	connect(clearRecvButton, &QPushButton::clicked, [=]() {
		recvPlainTextEdit->clear();
		});

	connect(clearSendButton, &QPushButton::clicked, [=]() {
		sendPlainTextEdit->clear();
		});

	connect(sendButton, &QPushButton::clicked, [=]() {
		QString sendData = sendPlainTextEdit->toPlainText();

		if (sendModeComboBox->currentText() == "HEX")	// HEX发送
		{
			QByteArray arr;
			for (int i = 0; i < sendData.size(); i++)
			{
				if (sendData[i] == ' ')
					continue;
				int num = sendData.mid(i, 2).toUInt(nullptr, 16);
				i++;
				arr.append(num);
			}
			serialPort->write(arr);
		}
		else											// TEXT发送
		{
			int lastIndex = sendData.lastIndexOf("\n");
			if (lastIndex != -1)
				sendData.replace(lastIndex, 1, "\r\n");
			serialPort->write(sendData.toUtf8());		// 将数据转成UTF-8发送出去
		}
		});
}

void Serial_Helper::timerEvent(QTimerEvent* event)
{
	QVector<QString> temp;
	for (const QSerialPortInfo& info : QSerialPortInfo::availablePorts())
		temp.push_back(info.portName());
	std::sort(temp.begin(), temp.end());
	if (temp != ports)
	{
		this->portNameComboBox->clear();
		this->ports = temp;
		for (auto& a : ports)
			this->portNameComboBox->addItem(a);
	}
}