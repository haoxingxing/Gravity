#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Gravity.h"
#include <QVector>
#include <QPair>
#include <QDebug>
#include <QTimer>

#include "Logger.h"

class object {
private:
public:
	double x, y, mass, speedx, speedy;
	QString name;
	Logger* logger;
	object(QString name,double x, double y, double mass, double speedx, double speedy, Logger* logger);
	QPair<double, double> Position();
	void ProcObj(object*);
	void ProcEnd();
	double distance(object*);
};

class Gravity : public QMainWindow
{
	Q_OBJECT

public:
	Gravity(QWidget* parent = Q_NULLPTR);
protected:
	void paintEvent(QPaintEvent* event);
private:
	QTimer timer;
	QVector<object*> MAP;
	Ui::GravityClass ui;
	void timeout();
	void Proc();
	Logger *logger;
	qint64 step = 0;
};
