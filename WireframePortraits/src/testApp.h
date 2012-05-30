#pragma once

#include "ofMain.h"
#include "ofxRGBDRenderer.h"
#include "ofxGameCamera.h"
#include "ofxXmlSettings.h"
#include "ofxGui.h"
#include "ofxDepthImageSequence.h"
#include "ofxDepthHoleFiller.h"
#include "ofxRGBDMediaTake.h"

class testApp : public ofBaseApp{
  public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void exit();
    
    ofxRGBDRenderer renderer;
    ofxGameCamera cam;

    ofxRGBDMediaTake take;
    ofxDepthImageSequence depthImages;
    ofxDepthHoleFiller filler;

    ofxPanel panel;
    ofxIntSlider simplify;
    ofxIntSlider pointSize;
    ofxIntSlider lineWidth;
    ofxIntSlider fillKernelSize;
    ofxIntSlider fillPasses;
    
    ofxFloatSlider farClip;
    ofxFloatSlider edgeClip;
    
    ofFbo fbo;
    ofRectangle fboRectangle;
    bool loadedSuccess;
    
    void loadNewSequence();
  
    void refreshRenderer();
    void sliderChanged(float& val);
    void sliderChanged(int& val);
};
