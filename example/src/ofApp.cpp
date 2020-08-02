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
    if (bSwitch)
        //if (ofGetFrameNum() % 1000 == 0)
    {
        bSwitch = false;


        ofNode tn;
        float boxsize = 8;
        tn.setPosition(ofRandom(-boxsize, boxsize), ofRandom(-boxsize, boxsize), ofRandom(-boxsize, boxsize));
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
    ofPushStyle();

    if (toggleCam)
    {
        ofClear(32);
        easy_cam.begin();
        {
            ofDrawGrid(30, 1);

            ofPushStyle();
            ofSetLineWidth(3);
            ofSetColor(255, 0, 0);
            ofDrawArrow(ofVec3f(0, 0, 0), ofVec3f(1, 0, 0));
            ofSetColor(0, 255, 0);
            ofDrawArrow(ofVec3f(0, 0, 0), ofVec3f(0, 1, 0));
            ofSetColor(0, 0, 255);
            ofDrawArrow(ofVec3f(0, 0, 0), ofVec3f(0, 0, 1));
            ofPopStyle();

            orbit_cam.drawSelf();
            morph_cam.drawSelf();
            fixed_cam.drawSelf();
            follow_cam.drawSelf();

            //

            drawScene();


            //

        }
        easy_cam.end();
    }

    //--

    if (!toggleCam)
    {
        follow_cam.begin();
        {
            //

            drawScene();

            //
        }
        follow_cam.end();
    }


    //--

    //minipreview
    rView.set(0, 500, 340, 280);
    c->begin(rView);
    {
        drawScene();
    }
    c->end();
    ofNoFill();
    ofSetColor(ofColor::red);
    ofDrawRectRounded(rView,10);

    //--


    int i = 0;
    string stringNode;
    auto myNode = (ofNode *) &follow_cam;

    ofDrawBitmapStringHighlight("Follow keys: 0:reset, 1:orbit_cam, 2:morph_cam, 3:fixed_cam, 4:easy_cam", glm::vec2(10, 30+(i++)*20), ofColor::white, ofColor::black);

    ofDrawBitmapStringHighlight("last cam: "+lastKey, glm::vec2(10, 30+(i++)*20), ofColor::white, ofColor::black);

    stringNode = "pos: "+ofToString(myNode->getPosition());
    ofDrawBitmapStringHighlight(stringNode, glm::vec2(10, 30+(i++)*20), ofColor::white, ofColor::black);


    //--


    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == '0')
    {
        follow_cam.resetFollow();

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
    }
    if (key == '4')
    {
        follow_cam.startFollow((ofNode *) &easy_cam);
    }

    if (key == ' ')
    {
        toggleCam = !toggleCam;
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
        lastKey = "reset Follow()";
    }
    if (key == '1')
    {
        lastKey = "Follow orbit_cam)";
    }
    if (key == '2')
    {
        lastKey = "Follow morph_cam)";
    }
    if (key == '3')
    {
        lastKey = "Follow fixed_cam)";
    }
    if (key == '4')
    {
        lastKey = "Follow easy_cam)";
    }

    if (key == ' ')
    {
        lastKey = "toggleCam = !toggleCam";
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
