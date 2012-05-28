#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(33,33,33);
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
	
  	surface1 = new ofxGtsSurface();
    surface2 = new ofxGtsSurface();
    surface1->setup("surfaces/cube1.gts");
    surface2->setup("surfaces/sphere.gts");

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofMesh a,b;
    surface1->copyToMesh(a);
    surface2->copyToMesh(b);
    
    glPushMatrix();
    glTranslatef(ofGetWidth()/2,ofGetHeight()/2,-25);
    glRotatef(sin(ofGetElapsedTimef()*1.3)*180,0,1,0);
    glScalef(100,100,100);
    ofSetColor(255);
	a.drawWireframe();
    b.drawWireframe();
    
    glEnd();
	glPopMatrix();


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 's'){
        m.save("meshTest.ply");
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