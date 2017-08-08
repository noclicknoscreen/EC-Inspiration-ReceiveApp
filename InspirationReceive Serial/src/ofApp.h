#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxNetwork.h"

#define HOST "localhost"
#define PORT 5000

//--------------------------------------------------------
class ofApp : public ofBaseApp {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    ofxButton track1;
    ofxButton track2;
    ofxButton track3;
    ofxButton track4;
    
    ofxFloatSlider openWipe1;
    ofxFloatSlider openWipe2;
    ofxFloatSlider openWipe3;
    ofxFloatSlider openWipe4;
    
    ofxPanel gui;

    
    void track1Pressed();
    void track2Pressed();
    void track3Pressed();
    void track4Pressed();
    void track_Pressed(int _numTrack);
    
    ofTrueTypeFont font;
    ofxOscSender sender;
    
    
    ofxOscReceiver volet1;
    ofxOscReceiver volet2;
    ofxOscReceiver volet3;
    ofxOscReceiver volet4;
    
    
    // UDP
    ofxUDPManager udpConnection;
    string        tagSize = "?";
    
    ofSerial	serial;
    //char		bytesRead[1];				// data from serial, we will be trying to read 3
    string		bytesReadString;			// a string needs a null terminator, so we need 3 + 1 bytes

};

