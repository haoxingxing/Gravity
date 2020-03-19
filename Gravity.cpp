#include "Gravity.h"

#include <iostream>
#include <QPainter>
Gravity::Gravity(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	logger = new Logger;
	logger->show();
	logger->log("Gravity Init");
	MAP.append(new object("A",500, 500, 2000000, 50000000, -50000000,logger));
	MAP.append(new object("B",450, 450, 2000000, -50000000, 50000000,logger));
	//MAP.append(new object("C", 600, 600, 50, 0, 0, logger));
	MAP.append(new object("C", 200, 200, 100000, 100000, -100000, logger));
	MAP.append(new object("D", 600, 600, 5000000, -1000000, 100000, logger));
	connect(&timer, &QTimer::timeout, this, &Gravity::timeout);
	logger->log("Timer started");
	timer.start(1);

}


double clockToMilliseconds(clock_t ticks) {
	// units/(units/time) => time (seconds) * 1000 = milliseconds
	return (ticks / (double)CLOCKS_PER_SEC) * 1000.0;
}
//...
object::object(QString name,double x, double y, double mass, double speedx, double speedy,Logger* logger) :
	x(x), y(y), mass(mass), speedx(speedx), speedy(speedy),logger(logger),name(name)
{
	logger->log(name + ": Init with x=" + QString::number(x) + " y=" + QString::number(y) + " mass=" + QString::number(mass) + " speedx=" + QString::number(speedx) + " speedy=" + QString::number(speedy));
	
}

QPair<double, double> object::Position()
{
	return QPair<double, double>(x, y);
}

double pn(double a, double b)
{
	if (a > b) return 1; else return  -1;
}

void object::ProcObj(object* a)
{
	auto dis = distance(a);
	auto bx = speedx;
	auto by = speedy;

	speedx += pn(a->x, x) * (a->mass) * (a->mass) / (dis) / (mass);
	speedy += pn(a->y, y) * (a->mass) * (a->mass) / (dis)/ (mass);
	logger->log(name + "->" + a->name + " dV=" + QString::number(speedx - bx + speedy - by));
}

void object::ProcEnd()
{
	x += speedx / 1000000000;
	y += speedy / 1000000000;
	logger->log(name + ": Proceed with x=" + QString::number(x) + " y=" + QString::number(y) + " mass=" + QString::number(mass) + " speedx=" + QString::number(speedx) + " speedy=" + QString::number(speedy));

}

double object::distance(object* a)
{
	auto m = double(sqrtl(powl(abs(a->x - x), 2) + powl(abs(a->y - y), 2)));
	logger->log(name + "->" +a->name + " d=" + QString::number(m));
	return m;
}

void Gravity::Proc()
{
	clock_t beginFrame = clock();
	logger->clear();
	logger->log("Step=" + QString::number(step));
	for (size_t i = 0; i < MAP.size(); i++) {
		for (size_t j = 0; j < MAP.size(); j++)
		{
			if (i == j)
				continue;
			MAP[i]->ProcObj(MAP[j]);
		}
	}
	foreach(object * a, MAP) {
		a->ProcEnd();
	}
	step++;

	clock_t endFrame = clock();

	auto deltaTime = endFrame - beginFrame;
	repaint();
	logger->log("FrameTime=" + QString::number(clockToMilliseconds(deltaTime)) + "ms");
	logger->log("FPS="+QString::number(1000/clockToMilliseconds(deltaTime)));

}

void Gravity::paintEvent(QPaintEvent* event)
{
	logger->log("paintEvent");
	QPainter painter(this);
	painter.setPen(QColor(Qt::blue));
	painter.setBrush(QBrush(Qt::yellow));
	foreach(object * o, MAP) {
		painter.drawEllipse(o->Position().first, o->Position().second, 10,10);
	}
}

void Gravity::timeout()
{
	Proc();
}