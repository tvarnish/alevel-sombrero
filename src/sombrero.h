#ifndef __SOMBRERO_H_INCLUDED__
#define __SOMBRERO_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <regex>
#include <map>

#include "lib/font.h"
#include "lib/body.h"
#include "lib/image.h"
#include "lib/video.h"
#include "lib/output.h"
#include "lib/misc.h"
#include "lib/matrix.h"
#include "lib/position_vector.h"
#include "lib/linkedlist.h"
#include "lib/units.h"

#include <pngwriter.h>

using namespace std;

class Simulation {
  // Parameters initialised with defaults
  string name = "simulation";
  string outputFolder = "";
  int bodyCount;
  int width = 640;
  int height = 480;
  double scale = (AU / 100);
  double dt = DAY / 2;
  int framerate = 60;
  double gravConst = GR;

  List bodyList;
  Body * body;
  Body * bodyA;
  Body * bodyB;

  string GetTimeUnits(double time);

  // Private Simulation Methods
  void CollideBodies(Body * bodyA, Body * bodyB, double t);

  public:
    // Constructors
  	Simulation();
  	Simulation(int _width, int _height, double _scale, double _dt, int _framerate);
  	Simulation(string _name, int _width, int _height, double _scale, double _dt, int _framerate);

  	// Set Methods
  	void SetOutputDimensions(int _width, int _height) { width = _width; height = _height; };
  	void SetScale(double realDistance, double pixelDistance) { scale = realDistance / pixelDistance; };
  	void SetTimestep(double _dt) { dt = _dt; };
  	void SetFramerate(int _framerate) { framerate = _framerate; };
  	void SetOutputDirectory(string _outputFolder);
  	void SetSimulationName(string _name) { name = _name; };
  	void SetGravitationalConstant(double _gravConst) { gravConst = _gravConst; };

    // Get Methods
  	int GetNumberOfBodies() { return bodyList.GetLength(); };

  	bool LoadBodiesFromFile(string _fileName);
    void SaveOutputFile(string _fileName = "");

    // Generate body setup commands
  	void GenerateRandomShell(int _bodyCount);
  	void GenerateRandomDistribution(int _bodyCount);
    void GenerateRandomDistribution(int _bodyCount, double _width, double _bodyMassMin, double _bodyMassMax, double _radiusMin, double _radiusMax);

    void AddBody(Body * body);
    void ClearBodyList();
    List GetBodyList() { return bodyList; };

    // Simulation Methods
  	void Rotate(string buildingMessage = "");
  	void Scale(double finalRealDistance, double finalPixelDistance, int frameCount, bool updateScale, string buildingMessage = "");
  	void Run(int startingFrame, int framesToSimulate, string buildingMessage = "");
};

#endif