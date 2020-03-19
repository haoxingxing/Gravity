#pragma once

#include <QWidget>
namespace Ui { class Logger; };

class Logger : public QWidget
{
	Q_OBJECT

public:
	Logger(QWidget *parent = Q_NULLPTR);
	~Logger();
	void log(QString str);
	void clear();
private:
	Ui::Logger *ui;
};
