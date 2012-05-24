#include "testApp.h"

static void write_vertex(GtsVertex* v, guint* nv) {
	testApp* app = static_cast<testApp*>(ofGetAppPtr());
	ofVec3f p(
		GTS_POINT(v)->x
		,GTS_POINT(v)->y
		,GTS_POINT(v)->z
	);
	app->vertices.push_back(p);
}

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(33,33,33);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	string file = ofToDataPath("surfaces/horse4.gts",true);
	GtsFile* fp;
	surfaceFromFile = gts_surface_new(
			gts_surface_class()
			,gts_face_class()
			,gts_edge_class()
			,gts_vertex_class()
	);
    
	FILE* cfile;
	cfile = fopen(file.c_str(), "r");
	fp = gts_file_new(cfile);
	if(gts_surface_read(surfaceFromFile,fp)) {
		cout << "file is not a valid gts file." << endl;
	}
	else {
      guint nv = 1;
	  gts_surface_foreach_vertex (surfaceFromFile, (GtsFunc) write_vertex, &nv);
	  cout << vertices.size() << " num vertices" << endl;
	}		
	
	ofxGts gts;
	sphere = gts.createSurface();
	sphere->setup(surfaceFromFile);
    
	//sphere->setupSphere(2);
	test_verts = sphere->getVertices();
	vector<GtsVertex*>::iterator it = test_verts.begin();
	edges = sphere->getEdges();
    triangles = sphere->getTriangles();
}

//--------------------------------------------------------------
void testApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::draw(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	m.clearIndices();
    m.clearVertices();
    
    vector<GtsVertex*>::iterator it = test_verts.begin();
    for(int i = 0; i < test_verts.size(); i++){
        m.getVertices().push_back(ofVec3f(test_verts[i]->p.x,test_verts[i]->p.y,test_verts[i]->p.z)); 
    }
    
    for(int i = 0; i < triangles.size(); i++){
        
        GtsTriangle* tri = triangles[i];
        GtsVertex* a = NULL;
		GtsVertex* b = NULL;
		GtsVertex* c = NULL;
        
        gts_triangle_vertices(tri, &a, &b, &c);
        for(int v = 0; v < test_verts.size(); v++){
            
            if(a == NULL && b == NULL && c == NULL){
                break;
            }
            
            if(a == test_verts[v]){
                m.addIndex(v);
                a = NULL;
            }
            if(b == test_verts[v]){
                m.addIndex(v);                
                b = NULL;
            }
            if(c == test_verts[v]){
                m.addIndex(v);
                c = NULL;
            }
        }        
    }

    
	glPushMatrix();
    glTranslatef(0,0,-100);
    glRotatef(sin(ofGetElapsedTimef()*1.3)*180,0,1,0);
    glScalef(200,200,200);
    ofSetColor(255);
    m.drawWireframe();
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