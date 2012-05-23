#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	ofSetFrameRate(30);
    ofBackground(255);

    loadedSuccess = false;    

    renderer.addColors = false;
    
    ofxXmlSettings defaults;
    if(defaults.loadFile("settings.xml")){
        string takeDirectory = defaults.getValue("take", "");
        if(take.loadFromFolder(takeDirectory)){
            depthImages.loadSequence(take.depthFolder);
            cout << "loading " << takeDirectory << " with duration " << depthImages.getDurationInMillis() <<  endl;
            renderer.setup(take.calibrationDirectory);
            depthImages.selectTime(depthImages.getDurationInMillis()/2);
            renderer.setDepthImage(depthImages.getPixels());
			renderer.update();
            renderer.getMesh().clearColors();
            loadedSuccess = true;
        }
        else {
        	loadNewSequence();
        }
    }
    else {
        loadNewSequence();
    }
    
    simplify = 0;
    
    fboRectangle = ofRectangle(0,0, 1280, 720);
    
    fbo.allocate(fboRectangle.width, fboRectangle.height, GL_RGB, 4);
    
    panel.setup();
    panel.add(simplify.setup("simplify", ofxParameter<int>(), 1, 16));
    
    panel.add(pointSize.setup("Point Size", ofxParameter<int>(), 1, 10));
    panel.add(lineWidth.setup("Line Width", ofxParameter<int>(), 1, 10));;
    panel.add(farClip.setup("Far Clip", ofxParameter<float>(), 1, 2000));
    panel.add(edgeClip.setup("Edge Clip", ofxParameter<float>(), 0, 500));

    panel.loadFromFile("guisettings.xml");
    
    cam.setup();
    cam.autosavePosition = true;
    cam.speed = 10;
    cam.setScale(1,-1,1);
    cam.loadCameraPosition();

    for(int i = 0; i < 200; i++){
        ofNode n;
        n.setPosition(ofRandom(-200,200),ofRandom(-200,200),ofRandom(-200,200));
		nodes.push_back(n);
    }
}

//--------------------------------------------------------------
void testApp::loadNewSequence(){
	ofFileDialogResult r = ofSystemLoadDialog("Take", true);
    if(r.bSuccess){
        
        if(take.loadFromFolder(r.getPath())){
            ofxXmlSettings defaults;
            defaults.loadFile("settings.xml");
        	defaults.setValue("take", r.getPath());
            defaults.saveFile();
            depthImages.loadSequence(take.depthFolder);
            renderer.setup(take.calibrationDirectory);
            depthImages.selectTime(depthImages.getDurationInMillis()/2);
            renderer.setDepthImage(depthImages.getPixels());
            renderer.update();
            renderer.getMesh().clearColors();
            
            loadedSuccess = true;
        }
    }
}

//--------------------------------------------------------------
void testApp::update(){
	
    if(!loadedSuccess) return;
	
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    if(!loadedSuccess) return;

    fbo.begin();
    ofClear(255);
    
    cam.begin();
    
    glEnable(GL_DEPTH_TEST);
    ofPushStyle();
    
    //background
    ofPushMatrix();
    ofTranslate(cam.getLookAtDir()*.1);
    ofSetColor(255);
    renderer.drawMesh(false);
    ofPopMatrix();
    
    //points and lines
    ofSetColor(0);
    ofSetLineWidth(1);
    renderer.drawWireFrame(false);
    
    glPointSize(10);
    renderer.drawPointCloud(false);
	ofPopStyle();
    
    glDisable(GL_DEPTH_TEST);
    
    for(int i = 0; i < nodes.size(); i++) nodes[i].draw();
    
    ofDrawGrid();
    
    cam.end();
    
    fbo.end();
    
    ofSetColor(255);
    fbo.getTextureReference().draw(fboRectangle);
    
    panel.draw();
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == ' '){
		renderer.reloadShader();
	}

	if(key == 'f'){
		ofToggleFullscreen();
	}
    
    if(key == 'S'){
        //TODO save frame
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
	cam.usemouse = fboRectangle.inside(x,y); 
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

//--------------------------------------------------------------
void testApp::exit(){
    panel.saveToFile("guisettings.xml");
}
