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

#include "Color.h"

#include <gcode/ToolPath.h>
#include <camotics/value/ValueGroup.h>

#include <cbang/SmartPointer.h>
#include <cbang/StdTypes.h>

#include <vector>

namespace CAMotics {
  class ToolPathView {
    ValueGroup values;
    cb::SmartPointer<const GCode::ToolPath> path;

    bool byRemote;
    double ratio;
    cb::Vector3D position;
    unsigned line;

    double totalTime;
    double totalDistance;

    double currentTime;
    double currentDistance;
    cb::Vector3D currentPosition;
    unsigned currentLine;
    GCode::Move currentMove;

    bool dirty;

    std::vector<float> vertices;
    std::vector<float> colors;

    unsigned colorVBuf;
    unsigned vertexVBuf;
    unsigned numVertices;
    unsigned numColors;

    bool useVBOs;

  public:
    ToolPathView(ValueSet &valueSet);
    ~ToolPathView();

    bool isEmpty() const {return path.isNull() || path->empty();}

    cb::SmartPointer<const GCode::ToolPath> getPath() const {return path;}
    void setPath(const cb::SmartPointer<const GCode::ToolPath> &path,
                 bool withVBOs);

    cb::Rectangle3D getBounds() const
    {return path.isNull() ? cb::Rectangle3D() : path->getBounds();}

    void setByRatio(double ratio);
    void setByRemote(const cb::Vector3D &position, unsigned line);

    void incTime(double amount = 1);
    void decTime(double amount = 1);

    double getTime() const {return currentTime;}
    bool atStart() const {return getTime() == 0;}
    bool atEnd() const {return getTime() == getTotalTime();}
    double getRemainingTime() const {return totalTime - currentTime;}
    double getTotalTime() const {return totalTime;}
    double getTimeRatio() const {return currentTime / totalTime;}
    double getPercentTime() const {return getTimeRatio() * 100;}

    double getDistance() const {return currentDistance;}
    double getRemainingDistance() const
    {return totalDistance - currentDistance;}
    double getTotalDistance() const {return totalDistance;}
    double getPercentDistance() const
    {return currentDistance / totalDistance * 100;}

    const cb::Vector3D &getPosition() const {return currentPosition;}
    unsigned getProgramLine() const {return currentLine;}
    const GCode::Move &getMove() const {return currentMove;}

    unsigned getTool() const {return getMove().getTool();}
    double getFeed() const {return getMove().getFeed();}
    double getSpeed() const {return getMove().getSpeed();}
    const char *getDirection() const;

    Color getColor(GCode::MoveType type);

    void update();
    void draw();
  };
}
