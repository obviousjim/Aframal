#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetFrameRate(30);
	ofEnableAlphaBlending();
	
	numShapes = 30;
	maxObjects = 100;
	radius = 300;
	rotationSpeed = -3;
	boxSize = 6;
	boxDistance = 10;
	
	for(int i = 0; i < numShapes; i++){
		Shape shape;
		float rotation = ofMap(i, 0, numShapes, 0, 360, true);
		int myshapes = ofMap(i, 0, numShapes, 0, maxObjects, true);
		if(i != 0){
			shape.centerOffsets = shapes[i-1].centerOffsets;
		}
		ofVec3f shapeCenter = ofVec3f(ofRandom(-boxDistance, boxDistance),
									  ofRandom(-boxDistance, boxDistance),
									  ofRandom(-boxDistance, boxDistance) );
		shape.centerOffsets.push_back( shapeCenter );
		
		//for(int s = 0; s < myshapes; s++){
		//	ofVec3f shapeCenter = ofVec3f(ofRandom(-boxDistance, boxDistance),
		//								  ofRandom(-boxDistance, boxDistance),
		//								  ofRandom(-boxDistance, boxDistance) );
		//	shape.centerOffsets.push_back( shapeCenter );
		//}
		
		shape.lastRotation = shape.currentRadius = radius;
		shape.currentRotation = rotation;
		shapes.push_back(shape);
	}
	
	cam.autosavePosition = true;
	cam.loadCameraPosition();
	
	stopped = false;
}

//--------------------------------------------------------------
void testApp::update(){
	
	if(stopped) return;
	
	for(int i = 0; i < shapes.size(); i++) {
		shapes[i].lastRotation = shapes[i].currentRotation;
		shapes[i].currentRotation = fmod(shapes[i].currentRotation + rotationSpeed, 360.0f);
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(0);
	
	cam.begin();
	
	for(int i = 0; i < shapes.size(); i++) {
		ofPushMatrix();
		ofPushStyle();
		
		Shape& shape = shapes[i];
		ofNoFill();
		if(shape.currentRotation > shape.lastRotation || stopped){
			ofSetColor(255);
		}
		else{
			ofSetColor(255, 255, 255, 10);
		}
		
		ofVec3f clustercenter = ofVec3f(1, 0, 0).getRotated(shape.currentRotation, ofVec3f(0,1,0)) * shape.currentRadius;
		ofTranslate(clustercenter);
		for(int s = 0; s < shape.centerOffsets.size(); s++){
			ofBox(shape.centerOffsets[s], boxSize);
		}
		
		ofPopStyle();
		ofPopMatrix();
	}
	
	cam.end();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == 'f'){
		ofToggleFullscreen();
	}
	
	if(key == ' '){
		stopped = !stopped;
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