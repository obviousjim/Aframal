#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(33,33,33);
	ofSetFrameRate(30);
    ofEnableAlphaBlending();
    
	ofSetVerticalSync(true);
	surface1 = new ofxGtsSurface();
    surface2 = new ofxGtsSurface();
    result = new ofxGtsSurface();

    surface1->setup("surfaces/cube1.gts");
    surface1->centerAtOrigin();
    surface1->scale(100);
    surface1->translate(ofVec3f(0, 48, 0));
    
    surface2->setup("surfaces/cube1.gts");
    surface2->centerAtOrigin();
    surface2->scale(100);
    
    surface2->rotate(90, ofVec3f(1,0,0));
    
    cout << "intersecting 1 to 2" << endl;
    surface1->getUnion(*surface2, *result);
    
    cam.setup();
    cam.speed = 10;
    cam.autosavePosition = true;
    cam.loadCameraPosition();
    
}

//--------------------------------------------------------------
void testApp::update(){
//    result->rotate(2, ofVec3f(0,1,0));
}

//--------------------------------------------------------------
void testApp::draw(){
    
    cam.begin();
    ofMesh a,b,c;
    surface1->copyTo(a);
    surface2->copyTo(b);
    result->copyTo(c);
    
    ofPushStyle();

    ofSetColor(255, 255,255,10);
    a.drawWireframe();
    b.drawWireframe();
    
    ofSetColor(255, 0, 0);
    c.drawWireframe(); 
    ofPopStyle();
    
    cam.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 'S'){
        ofMesh out;
        result->copyTo(out);
        out.save("output.ply");
    }
    if(key == OF_KEY_UP){
//        accumulation.translate(ofVec3f(0, -1, 0));    
    }
    else if(key == OF_KEY_DOWN){
//        accumulation.translate(ofVec3f(0, 1, 0));
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}