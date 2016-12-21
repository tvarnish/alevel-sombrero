#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <ctime>

#include "lib/font.h"
#include "lib/body.h"
#include "lib/image.h"
#include "lib/video.h"
#include "lib/output.h"
#include "lib/misc.h"
#include "lib/matrix.h"
#include "lib/units.h"

#include <pngwriter.h>

using namespace std;

int main(int argc, char * argv[]) {
	string usageStatement = "Usage: ./sombrero [-g --generate] [-r --run]";

	// Need to make these "settable" by the user
	int bodyCount = 200;
	int width = 640;
	int height = 480;

	int framerate = 45;

	Body * bodyArray [bodyCount];

	// No arguments supplied
	if (argc == 1) {
		// No arguments supplied. Exit.
		cout << "No arguments supplied. Must choose an option." << endl;
		cout << usageStatement << endl;
		return 1;
	}

	// Generate Body arrangement
	if (strcmp(argv[1], "-g") == 0 or strcmp(argv[1], "--generate") == 0) {
		if (argc >= 3) {
			// Generate random arrangement of bodies (+ generate rotation video)
			// i.e. create new bodyArray
			if (strcmp(argv[2], "random") == 0) {
				for (int i = 0; i < bodyCount - 1; i++) {
					double r = Random(1e11, 2e11);
					double theta = Random(0, 2 * PI);
					double phi = Random(0, 2 * PI);

					double x = r * cos(theta) * cos(phi);
					double y = r * sin(theta);
					double z = r * cos(theta) * sin(phi);

					double mass = Random(1e23, 1e25);

					bodyArray[i] = new Body(x, y, z, mass, Random(1e6, 9e6), Random(0, 1e4), Random(0, 1e4), Random(0, 1e4));
				}

				bodyArray[bodyCount - 1] = new Body(0.0, 0.0, 0.0, 2e31, 1e8, 0.0, 0.0, 0.0);

				// Save bodies to output.txt
				Output output("init/output.txt", bodyCount, width, height, 100);
				output.AddAllBodies(bodyArray);
				output.Save();
			}

			// Generate rotate video around bodies
			// i.e. Load bodies from file
			else if (strcmp(argv[2], "rotate") == 0) {
				string filename = "init/output.txt";

				if (argc == 4) {
					// Assume that the final argument is the filename
					filename = argv[3];
				}

				if (FileExists(filename)) {
					LoadBodiesFromFile(filename.c_str(), bodyArray);
				}
				else {
					cout << "./sombrero --generate rotate [filename]" << endl;
					cout << "When using rotate, must include valid filename: e.g. init/output.txt" << endl;
					return 1;
				}
			}

			else {
				cout << usageStatement << endl;
				cout << "Must supply generate argument: [random, rotate]" << endl;
				return 1;
			}
		}

		else {
			cout << usageStatement << endl;
			cout << "Must supply generate argument: [random, rotate]" << endl;
			return 1;
		}

		// Generate rotate video around bodies
		Video video = Video("images/", "image_", width, height, framerate);
		video.ClearImageFolder();

		// Rotate bodies about the y-axis
		for (double angle = 0.0; angle < 360.0; angle ++) {
			string imageFileName = "images/image_" + PadWithZeroes(angle, 360) + ".png";
			Image image = Image(imageFileName, width, height, 100);

			for (int i = 0; i < bodyCount; i++) {
				// Rotate body
				Vector p;
				p.Set(bodyArray[i]->GetX(), bodyArray[i]->GetY(), bodyArray[i]->GetZ());

				Vector t;
				t = p.RotateY(angle);
				t = t.RoundValues();

				image.DrawBody(t.GetX(), t.GetY(), 255, 255, 255);
			}

			image.Save();
		}

		// Build video from images
		video.Build("result.mp4", 360);

		return 0;
	}

	// Run simulation
	if (strcmp(argv[1], "-r") == 0 or strcmp(argv[1], "--run") == 0) {
		LoadBodiesFromFile("init/output.txt", bodyArray);

		Video video = Video("images/", "image_", width, height, framerate);
		video.ClearImageFolder();

		int frames = 500;
		double dt = DAY;

		for (int f = 0; f < frames; f++) {
			// Optimised algorithm
			for (int i = 0; i < bodyCount; i++) {
				bodyArray[i]->ResetForce();
			}

			for (int a = 0; a < bodyCount; a++) {
				for (int b = a + 1; b < bodyCount; b++) {
					// Calculate distance
					double xDistance = bodyArray[a]->GetX() - bodyArray[b]->GetX();
					double yDistance = bodyArray[a]->GetY() - bodyArray[b]->GetY();
					double zDistance = bodyArray[a]->GetZ() - bodyArray[b]->GetZ();
					double totalDistance = sqrt(pow(xDistance, 2) + pow(yDistance, 2) + pow(zDistance, 2));

					// Calculate angles
					double phiAngle = atan2(zDistance, sqrt(pow(xDistance, 2) + pow(yDistance, 2)));
					double thetaAngle = atan2(yDistance, xDistance);

					// Calculate force
					double force = GR * ((bodyArray[a]->GetMass() * bodyArray[b]->GetMass()) / (pow(totalDistance, 2)));

					// Add forces to totals
					bodyArray[a]->AddForce(force, phiAngle, thetaAngle);
					bodyArray[b]->AddForce(-force, phiAngle, thetaAngle);
				}
			}

			string imageFileName = "images/image_" + PadWithZeroes(f, frames) + ".png";
			Image image = Image(imageFileName, width, height, 100);

			// Calculate next position for each body
			for (int i = 0; i < bodyCount; i++) {
				bodyArray[i]->Update(dt);
			}

			// Collision Physics
			bool firstCollision = true;

			for (int a = 0; a < bodyCount; a++) {
				for (int b = a + 1; b < bodyCount; b++) {
					// Set up position vectors
					Vector initialA;
					initialA.Set(bodyArray[a]->GetX(), bodyArray[a]->GetY(), bodyArray[a]->GetZ());

					Vector finalA;
					finalA.Set(bodyArray[a]->GetNextX(), bodyArray[a]->GetNextY(), bodyArray[a]->GetNextZ());

					Vector initialB;
					initialB.Set(bodyArray[b]->GetX(), bodyArray[b]->GetY(), bodyArray[b]->GetZ());

					Vector finalB;
					finalB.Set(bodyArray[b]->GetNextX(), bodyArray[b]->GetNextY(), bodyArray[b]->GetNextZ());

					// Check the two lines are not parallel
					Vector lineA = finalA.Subtract(initialA);
					Vector lineB = finalB.Subtract(initialB);

					if (lineA.DotProduct(lineB) != 0) {
						// Calculate collision times
						Vector vectorA = initialB.Subtract(initialA);
						Vector vectorB = (finalB.Subtract(finalA)).Add(initialA.Subtract(initialB));

						double dotProduct = vectorA.DotProduct(vectorB);
						double radiiSum = bodyArray[a]->GetRadius() + bodyArray[b]->GetRadius();

						double determinant = (4 * pow(dotProduct, 2)) - (4 * pow(vectorB.Magnitude(), 2) * (pow(vectorA.Magnitude(), 2) - pow(radiiSum, 2)));
						double time1 = (-2 * dotProduct + sqrt(determinant)) / (2 * pow(vectorB.Magnitude(), 2));
						double time2 = (-2 * dotProduct - sqrt(determinant)) / (2 * pow(vectorB.Magnitude(), 2));

						bool timeValid1 = time1 >= 0 && time1 <= 1;
						bool timeValid2 = time2 >= 0 && time2 <= 1;

						// Check validity
						if (timeValid1 && timeValid2) {
							if (firstCollision == true) {
								cout << "==== FRAME " << to_string(f) << " ====" << endl;
								firstCollision = false;
							}

							if (time1 <= time2) {
								// Collision occurs at time1;
								cout << "Collision occurs at " << to_string(time1)  << ", between [" << to_string(a) << "] and [" << to_string(b) << "]"<< endl;
							}
							else {
								// Collision occurs at time2;
								cout << "Collision occurs at " << to_string(time2)  << ", between [" << to_string(a) << "] and [" << to_string(b) << "]"<< endl;
							}
						}
					}
				}
			}

			if (firstCollision == false) {
				cout << endl;
			}

			// Move each body to their new positions
			for (int i = 0; i < bodyCount; i++) {
				bodyArray[i]->Step();

				image.DrawBody(bodyArray[i]->GetX(), bodyArray[i]->GetY(), 255, 255, 255);
			}

			// Draw information on frame
			image.DrawText("F: " + to_string(f), 10, 10, 255, 255, 255);

			image.Save();
		}

		video.Build("result_run.mp4", frames);

		// Create output.txt
		Output output("init/output.txt", bodyCount, width, height, 100);
		output.AddAllBodies(bodyArray);
		output.Save();

		return 0;
	}

	// No *valid* arguments supplied
	else {
		cout << "No valid arguments provided." << endl;
		cout << usageStatement << endl;
		return 1;
	}

	return 0;
}
