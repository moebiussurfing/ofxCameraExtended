#pragma once

#include "ofMain.h"
#include "ofxCameraExtended.h"

class ofApp : public ofBaseApp{
    
    ofxCameraExtended::EasyCamera easy_cam;
    ofxCameraExtended::OrbitCamera orbit_cam;
    ofxCameraExtended::MorphCamera morph_cam;
    ofxCameraExtended::FixedCamera fixed_cam;
    ofxCameraExtended::FollowCamera follow_cam;
    //float nearclip = 0.001;
    //float farclip = 1000;
	float nearclip = 1;
	float farclip = 10000;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		bool toggleCam = false;

    string lastKey;

	bool bSwitch;

    ofRectangle rView;
    ofCamera *c;


    void drawScene(){

        ofPushMatrix();
        ofPushStyle();

        //ofDrawGrid(30, 1);
        ofDrawAxis(10);

        ofSetLineWidth(0.1);
        ofSetColor(ofColor::blue);
//        ofTranslate(morph_cam.getGlobalPosition());
//        ofTranslate(morph_cam.getGlobalPosition());
        ofNoFill();

        ofSetConeResolution(3, 3, 3);
        ofDrawCone(1, 2);

        ofPopMatrix();
        ofPopStyle();
    }
};
