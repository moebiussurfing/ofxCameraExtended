#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(25);
    ofEnableDepthTest();

    // use meter scale
    // easy_cam
    easy_cam.setNearClip(nearclip);
    easy_cam.setFarClip(farclip);
    easy_cam.setDistance(8);

    easy_cam.orbit(0, -90, 25);
    //easy_cam.orbit(45, -15, 30);
    //easy_cam.orbit(0, 0, 1);
    //easy_cam.setGlobalPosition(0,-100,0);
    //easy_cam.setTarget(0, 0, 0);

    // orbit_cam
    orbit_cam.setNearClip(nearclip);
    orbit_cam.setFarClip(farclip);
    //orbit_cam.setParameters(90, 0, 1.5, 300, 0);
    //orbit_cam.setParameters(0, 90, 1.5, 300, 300);

    // morph_cam
    morph_cam.setNearClip(nearclip);
    morph_cam.setFarClip(farclip);

    // fixed_cam
    fixed_cam.setNearClip(nearclip);
    fixed_cam.setFarClip(farclip);

    // follow_cam
    follow_cam.setNearClip(nearclip);
    follow_cam.setFarClip(farclip);

    c = &easy_cam;
}

//--------------------------------------------------------------
void ofApp::update()
{
    // auto morphing
    /*if(ofGetFrameNum()%90==0){*/
    //if (ofGetFrameNum() % 1000 == 0)

    if (bSwitch)
    {
        bSwitch = false;

        ofNode tn;
        float boxsize = 8;
        tn.setPosition(
                       ofRandom(-boxsize, boxsize),
                       ofRandom(-boxsize, boxsize),
                       ofRandom(-boxsize, boxsize));
        tn.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, 1, 0));
        morph_cam.startMorph(tn);

        orbit_cam.setTargetPosition(tn.getGlobalPosition());
        //orbit_cam.setLatitude(10);
        //orbit_cam.setLongitude(90);
        //orbit_cam.setPosition(tn.getGlobalPosition());

        //setParameters(float longitude, float latitude, float radius, float speed_longitude, float speed_latitude)
        //orbit_cam.setParameters(90, 0, 2, 50, 0);//horizontal eje z
        //orbit_cam.setParameters(0, 90, 2, 0, 300);
        //orbit_cam.setParameters(90, 35, 5, 100, 200);//horizontal eje z
        orbit_cam.setParameters(0, 45, 2, 0, 50);//horizontal eje z
    }

    orbit_cam.setTargetPosition(morph_cam.getGlobalPosition());
    //orbit_cam.setTargetPosition(follow_cam.getGlobalPosition());

    easy_cam.update();
    orbit_cam.update();
    morph_cam.update();
    follow_cam.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackgroundGradient(ofColor(40, 40, 40), ofColor(0, 0, 0), OF_GRADIENT_CIRCULAR);

    //-

    ofEnableDepthTest();

    if (bEasyCam)
    {
        easy_cam.begin();
        {
            ofDrawGrid(5, 1);

//            ofPushStyle();
//            ofSetLineWidth(3);
//            ofSetColor(255, 0, 0);
//            ofDrawArrow(ofVec3f(0, 0, 0), ofVec3f(1, 0, 0));
//            ofSetColor(0, 255, 0);
//            ofDrawArrow(ofVec3f(0, 0, 0), ofVec3f(0, 1, 0));
//            ofSetColor(0, 0, 255);
//            ofDrawArrow(ofVec3f(0, 0, 0), ofVec3f(0, 0, 1));
//            ofPopStyle();

            orbit_cam.drawSelf();
            fixed_cam.drawSelf();
            morph_cam.drawSelf();
            if (indexCam != 4) follow_cam.drawSelf();

            drawScene();
        }
        easy_cam.end();
    }

    //--

    //easy cam
    if (!bEasyCam)
    {
        follow_cam.begin();
        {
            drawScene();
        }
        follow_cam.end();
    }


    //--

    //minipreview
    rView.set(5, ofGetHeight()-320 - 5, 480, 320);

    ofPushStyle();

//    ofFill();
//    ofSetColor(16);
//    ofDrawRectRounded(rView,5);

    c->begin(rView);
    {
        drawScene();
    }
    c->end();

    ofNoFill();
    ofSetLineWidth(2.0);
    ofSetColor(200);
    ofDrawRectRounded(rView,5);

    ofPopStyle();

    //--

    ofDisableDepthTest();

    int i = 0;
    string stringNode;
    auto myNode = (ofNode *) &follow_cam;

    string str;
    str += "CAMERA KEYS\n";
    str += "0: RESET\n";
    str += "1: ORBIT\n";
    str += "2: MORPH\n";
    str += "3: FIXED\n";
    str += "4: EASY\n";

    stringNode = "POSITION: " + ofToString(myNode->getPosition());

    ofDrawBitmapStringHighlight(str, 10, 20);
    ofDrawBitmapStringHighlight("LAST: " + lastKey, 10, 120);
    ofDrawBitmapStringHighlight(stringNode, 200, 20);

    //--
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == '0')
    {
        follow_cam.resetFollow();
        c = &follow_cam;
    }
    if (key == '1')
    {
        follow_cam.startFollow((ofNode *) &orbit_cam);
        c = &follow_cam;
    }
    if (key == '2')
    {
        follow_cam.startFollow((ofNode *) &morph_cam);
        c = &follow_cam;
    }
    if (key == '3')
    {
        follow_cam.startFollow((ofNode *) &fixed_cam);
        c = &follow_cam;
    }
    if (key == '4')
    {
        follow_cam.startFollow((ofNode *) &easy_cam);
        c = &follow_cam;
    }

    if (key == ' ')
    {
        bEasyCam = !bEasyCam;
        c = &follow_cam;
    }

    if (key == OF_KEY_RETURN)
    {
        bSwitch = true;
    }

    //if (key == 'm') {
    //	// auto morphing
    //	if (ofGetFrameNum() % 90 == 0) {
    //		ofNode tn;
    //		float boxsize = 8;
    //		tn.setPosition(ofRandom(-boxsize, boxsize), ofRandom(-boxsize, boxsize), ofRandom(-boxsize, boxsize));
    //		tn.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, 1, 0));
    //		morph_cam.startMorph(tn);
    //	}
    //}

    if (key == '0')
    {
        indexCam = 0;
        lastKey = "Reset Follow";
    }
    if (key == '1')
    {
        indexCam = 1;
        lastKey = "Follow orbit_cam";
    }
    if (key == '2')
    {
        indexCam = 2;
        lastKey = "Follow morph_cam";
    }
    if (key == '3')
    {
        indexCam = 3;
        lastKey = "Follow fixed_cam";
    }
    if (key == '4')
    {
        indexCam = 4;
        lastKey = "Follow easy_cam";
    }
    if (key == ' ')
    {
        indexCam = 5;
        lastKey = "Toggle EasyCam";
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
