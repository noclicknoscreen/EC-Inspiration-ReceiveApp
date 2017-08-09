#include "ofApp.h"

#define RECONNECT_TIME 400

//--------------------------------------------------------------
void ofApp::setup(){
    // we don't want to be running to fast
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    //create the socket and set to send to 127.0.0.1:11999
    udpConnection.Create();
    //udpConnection.Connect("127.0.0.1",11999); // Localhost communication
    udpConnection.Connect("192.168.2.112",2390); // Localhost communication
    udpConnection.SetNonBlocking(true);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(20, 20, 20);
    ofDrawBitmapString("openFrameworks UDP Send Example ", 15, 30);
    
    ofDrawBitmapString("Message written : ", 15, 50);
    ofDrawBitmapString(newMessage, 15, 60);
    
    ofDrawBitmapString("Messages sent : ", 15, 70);
    
    for(unsigned int i=0; i<messages.size(); i++){
        string tempMessage;
        tempMessage += ofToString(i);
        tempMessage += " : ";
        tempMessage += messages[i];
        
        ofDrawBitmapString(tempMessage, 15, 70 + 10 * (i+1));
        //ofDrawLine(stroke[i-1].x,stroke[i-1].y,stroke[i].x,stroke[i].y);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key == OF_KEY_RETURN){
        /*
        string message;
        message += ofGetTimestampString();
        message += " : ";
        message += "Here we go !";
        */
        /*
        for(unsigned int i=0; i<stroke.size(); i++){
            message+=ofToString(stroke[i].x)+"|"+ofToString(stroke[i].y)+"[/p]";
        }
         */
        
        ofLog() << "Message Sent [" << ofGetTimestampString() << "] : " << newMessage;
        udpConnection.Send(newMessage.c_str(),newMessage.length());
        
        messages.push_back(newMessage);
        newMessage = "";
        
    }else{
        newMessage += (char)key;
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
