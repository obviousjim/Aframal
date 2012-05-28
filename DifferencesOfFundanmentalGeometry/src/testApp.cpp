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
    surface2->setup("surfaces/sphere.gts");

    surface1->getIntersection(*surface2, *result);
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofMesh a,b, c;
    surface1->copyToMesh(a);
    surface2->copyToMesh(b);
    result->copyToMesh(c);
    
    
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2,-25);
    ofRotate(sin(ofGetElapsedTimef()*1.3)*180,0,1,0);
    ofScale(100,100,100);
    
    ofSetColor(255, 255,255,100);
    a.drawWireframe();
    b.drawWireframe();
    
    ofSetColor(255, 0, 0);
    c.drawWireframe(); 
    
	glPopMatrix();
    ofPopStyle();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 's'){
        ofMesh out;
        result->copyToMesh(out);
        out.save("meshTest.ply");
    }
    if(key == OF_KEY_UP){
        result->translate(ofVec3f(0, -1, 0));    
    }
    else if(key == OF_KEY_DOWN){
        result->translate(ofVec3f(0, 1, 0));
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