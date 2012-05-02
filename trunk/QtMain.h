#ifndef QTMAIN_H
#define QTMAIN_H

#include <vector>
#include <QMainWindow>

#include "SolGUI.h"

class SolMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	SolMainWindow();
	~SolMainWindow();

public Q_SLOTS:
	void redealTrigger();
	void updateStatus();
	void changeBack(int);

private:
	void createMenus();
	void createActions();
	
	QSignalMapper * signalMapper;
	QTimer * statusLoopTimer;
	SolGUI * SolGUIptr;
	QMenu * cardBackMenu;
	QAction * redealAct;
	vector<QAction*> backAct;
};

#endif