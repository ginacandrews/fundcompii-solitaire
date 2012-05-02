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
#ifdef _WIN32
#include <Windows.h>
#endif

#include <qgraphicsview.h>

#include "SolGUI.h"
#include "QtMain.h"
#include <qwidget.h>

using namespace std;

#ifdef _WIN32
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
#else
int main ( int argc, char *argv[] )
#endif
{
#ifdef _WIN32
	int argc = 0;
	char ** argv;
#endif

	QApplication GUILoop(argc, argv);

	SolMainWindow a;

	a.show();
	return GUILoop.exec();

	return 0;

}
