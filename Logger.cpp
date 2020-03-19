#include "Logger.h"
#include "ui_Logger.h"

Logger::Logger(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::Logger();
	ui->setupUi(this);
}

Logger::~Logger()
{
	delete ui;
}

void Logger::log(QString str)
{
	ui->textBrowser->append(str);
}

void Logger::clear()
{
	ui->textBrowser->clear();
}
