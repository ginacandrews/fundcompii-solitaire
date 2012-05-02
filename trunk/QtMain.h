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
	void undoTrigger();
	void updateStatus();
	void updateOneSec();
	void changeBack(int);

private:
	void createMenus();
	void createActions();
	
	QSignalMapper * signalMapper;
	QTimer * statusLoopTimer;
	QTimer * oneSecTimer;
	SolGUI * SolGUIptr;
	QMenu * cardBackMenu;

	QAction * redealAct;
	QAction * undoAct;
	vector<QAction*> backAct;
};

#endif