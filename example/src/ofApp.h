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
    float nearclip = 0.1;
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

    bool bEasyCam = false;
    bool bAutopilot = false;

    string lastKey;
    int indexCam = -1;

    bool bSwitch;
    bool bLookAtZero;

    ofRectangle rView;
    ofCamera *c;
    string nameCam;
    void drawScene(){

        ofPushMatrix();
        ofPushStyle();

        //floor
        bool SHOW_floor = true;
        if (SHOW_floor) {
            ofPushMatrix();
            ofPushStyle();
            ofSetColor(ofColor(60));
            ofRotate(90, 0, 0, -1);
            ofDrawGridPlane(1, 5, false);
            ofPopStyle();
            ofPopMatrix();
        }

        //cone
        ofConePrimitive myCone;
        myCone.setOrientation(glm::vec3(0, 0, 180));
        myCone.set(1, 2);
        myCone.setResolution(4, 1, 1);
        myCone.setScale(1.0f);
        ofSetColor(ofColor::black);
        myCone.draw();
        myCone.setScale(1.005f);
        ofSetColor(ofColor::white);
        myCone.drawWireframe();

        //box
//        ofFill();
//        ofSetColor(255);
//        ofDrawBox(1);
//        ofNoFill();
//        ofSetColor(0);
//        ofDrawBox(1);

        //axis
        ofDrawAxis(4);

        ofPopStyle();
        ofPopMatrix();
    }
};
