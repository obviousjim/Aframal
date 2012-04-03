#pragma once

#include "ofMain.h"
#include "ofxGameCamera.h"

class Shape {
  public:
	float currentRotation;
	float lastRotation;
	float currentRadius;
	vector<ofVec3f> centerOffsets;
};

class testApp : public ofBaseApp{

  public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	int boxSize;
	int maxObjects;
	int numShapes;
	int radius;
	int rotationSpeed;
	int boxDistance;
	vector<Shape> shapes;
	
	ofxGameCamera cam;
	
	bool stopped;
};
