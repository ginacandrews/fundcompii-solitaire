////////////////////////////////////////////////////////////////////////////////
// main.cpp                                                                   //
//  (c) Gina Andrews, Eric Vaughn, Aubrey Zielinski                           //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//    This file is part of Fundamentals of Computing II Solitaire Group.      //
//                                                                            //
//    This program is free software: you can redistribute it and/or modify    //
//    it under the terms of the GNU General Public License as published by    //
//    the Free Software Foundation, either version 3 of the License, or       //
//    (at your option) any later version.                                     //
//                                                                            //
//    This program is distributed in the hope that it will be useful,         //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of          //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           //
//    GNU General Public License for more details.                            //
//                                                                            //
//    You should have received a copy of the GNU General Public License       //
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.   //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <QApplication>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>

#include "SolGUI.h"
#include "QtMain.h"
#include <qwidget.h>

using namespace std;

int main ( int argc, char *argv[] )
{
	QApplication GUILoop(argc, argv);
	//QGraphicsScene scene;
	//QGraphicsView view(&scene);
	//view.show();

	//SolGUI a;
	SolMainWindow a;

	a.show();
	return GUILoop.exec();

	return 0;

}
