/******************************************************************************\

    CAMotics is an Open-Source simulation and CAM software.
    Copyright (C) 2011-2017 Joseph Coffland <joseph@cauldrondevelopment.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

\******************************************************************************/

#pragma once


#include <QtGlobal>
#if QT_VERSION < QT_VERSION_CHECK(5, 4, 0)
#include <QGLWidget>
#define PLATFORM_GL_WIDGET QGLWidget
#else
#include <QOpenGLWidget>
#define PLATFORM_GL_WIDGET QOpenGLWidget
#endif


namespace CAMotics {
  class QtWin;

  class GLView : public PLATFORM_GL_WIDGET {
    Q_OBJECT;

  public:
    GLView(QWidget *parent = 0);
    ~GLView() {}

    QtWin &getQtWin() const;

    // From QWidget
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    // From QGLWidget
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
  };
}
