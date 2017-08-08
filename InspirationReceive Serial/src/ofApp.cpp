#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // open an outgoing connection to HOST:PORT
    sender.setup(HOST, PORT);
    
    volet1.setup(8001);
    volet2.setup(8002);
    volet3.setup(8003);
    volet4.setup(8004);
    
    // we add this listener before setting up so the initial circle resolution is correct
    track1.addListener(this, &ofApp::track1Pressed);
    track2.addListener(this, &ofApp::track2Pressed);
    track3.addListener(this, &ofApp::track3Pressed);
    track4.addListener(this, &ofApp::track4Pressed);
    
    gui.setup(); // most of the time you don't need a name
    gui.add(track1.setup("track1"));
    gui.add(track2.setup("track2"));
    gui.add(track3.setup("track3"));
    gui.add(track4.setup("track4"));
    gui.add(openWipe1.setup("Wipe 1", 0, -1, 1));
    gui.add(openWipe2.setup("Wipe 2", 0, -1, 1));
    gui.add(openWipe3.setup("Wipe 3", 0, -1, 1));
    gui.add(openWipe4.setup("Wipe 4", 0, -1, 1));
    
    
    //create the socket and set to send to 127.0.0.1:11999
    udpConnection.Create();
    udpConnection.Connect("192.168.2.121",2390);
    udpConnection.SetNonBlocking(true);
    
    int baud = 9600;
    serial.listDevices();
    serial.setup(0, baud); //open the first device
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if((ofGetFrameNum() % 50) == 0){
        /*
         // ASK WHO AM I ........
         string message="Tag Size ?";
         udpConnection.Send(message.c_str(),message.length());
         ofLog() << "Asking " << message << ":" << ofToString(ofGetFrameNum());
         */
        
        unsigned char byteReturned;
        //memset(bytesReadString, 0, 2);
        //memset(bytesReturned, 0, 1);
        ofLog() << "Serial is initialized ? " << ofToString(serial.isInitialized());
        
        if(serial.available() > 0){
            while(serial.available() > 0){
                bytesReadString += (char)serial.readByte();
            };
            
            ofLog() << ofGetFrameNum() << " : Read :" << bytesReadString;
            
            //memcpy(bytesReadString, bytesReturned, 1);
            string newMessage = bytesReadString;
            bytesReadString = "";
            
            if(newMessage != tagSize && newMessage.length() == 3){
                
                ofLog() << "Brand new and correct Tag !";
                tagSize = newMessage;
                
                if(ofIsStringInString(tagSize, "X") == true){
                    track_Pressed(1);
                }else if(ofIsStringInString(tagSize, "S") == true){
                    track_Pressed(2);
                }else if(ofIsStringInString(tagSize, "M") == true){
                    track_Pressed(3);
                }else if(ofIsStringInString(tagSize, "L") == true){
                    track_Pressed(4);
                }
                
            }else{
                ofLog() << "No difference (" << ofToString(newMessage.length()) << ")";
            }
        }
        
        
    }
    /*
     char udpMessage[100000];
     udpConnection.Receive(udpMessage,100000);
     string newMessage=udpMessage;
     if(newMessage!=""){
     ofLog() << "Received : " << newMessage;
     if(newMessage != tagSize){
     tagSize = newMessage;
     
     if(tagSize == "X"){
     track_Pressed(1);
     }else if(tagSize == "S"){
     track_Pressed(2);
     }else if(tagSize == "M"){
     track_Pressed(3);
     }else if(tagSize == "L"){
     track_Pressed(4);
     }
     }
     }
     */
    
    
    // check Receiver 1 --
    while(volet1.hasWaitingMessages()){
        ofxOscMessage m;
        // get the next message
        volet1.getNextMessage(m);
        ofLog() << "Get a message from Volet 1 : Adress is = " << m.getAddress();
        // check for mouse moved message
        if(m.getAddress() == "/position"){
            ofLog() << "Position is = " << ofToString(m.getArgAsFloat(0));
            openWipe1 = m.getArgAsFloat(0);
        }
    }
    
    // check Receiver 2 --
    while(volet2.hasWaitingMessages()){
        ofxOscMessage m;
        // get the next message
        volet2.getNextMessage(m);
        ofLog() << "Get a message from Volet 2 : Adress is = " << m.getAddress();
        // check for mouse moved message
        if(m.getAddress() == "/position"){
            ofLog() << "Position is = " << ofToString(m.getArgAsFloat(0));
            openWipe2 = m.getArgAsFloat(0);
        }
    }
    // check Receiver 3 --
    while(volet3.hasWaitingMessages()){
        ofxOscMessage m;
        // get the next message
        volet3.getNextMessage(m);
        ofLog() << "Get a message from Volet 3 : Adress is = " << m.getAddress();
        // check for mouse moved message
        if(m.getAddress() == "/position"){
            ofLog() << "Position is = " << ofToString(m.getArgAsFloat(0));
            openWipe3 = m.getArgAsFloat(0);
        }
    }
    // check Receiver 4 --
    while(volet4.hasWaitingMessages()){
        ofxOscMessage m;
        // get the next message
        volet4.getNextMessage(m);
        ofLog() << "Get a message from Volet 4 : Adress is = " << m.getAddress();
        // check for mouse moved message
        if(m.getAddress() == "/position"){
            ofLog() << "Position is = " << ofToString(m.getArgAsFloat(0));
            openWipe4 = m.getArgAsFloat(0);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    gui.draw();
    
    // display instructions
    string buf;
    buf = "sending osc messages to" + string(HOST) + ofToString(PORT);
    ofDrawBitmapString(buf, 10, 20);
    
    ofDrawBitmapString("Tag Size=" + tagSize, 10, 200);
    
    
}

//--------------------------------------------------------------
void ofApp::track1Pressed(){
    // TRACK 1 Pressed() ----
    track_Pressed(1);
}
//--------------------------------------------------------------
void ofApp::track2Pressed(){
    // TRACK 2 Pressed() ----
    track_Pressed(2);
}
//--------------------------------------------------------------
void ofApp::track3Pressed(){
    // TRACK 3 Pressed() ----
    track_Pressed(3);
}
//--------------------------------------------------------------
void ofApp::track4Pressed(){
    // TRACK 4 Pressed() ----
    track_Pressed(4);
}

//--------------------------------------------------------------
void ofApp::track_Pressed(int _numTrack){
    
    string trackAddress = "/Track";
    trackAddress += ofToString(_numTrack);
    
    ofxOscMessage m1;
    // FIRST SEND THE PLAY
    m1.setAddress(trackAddress);
    m1.addIntArg(1);
    sender.sendMessage(m1, true);
    
    ofxOscMessage m2;
    // FIRST SEND THE STOP
    m2.setAddress(trackAddress);
    m2.addIntArg(0);
    sender.sendMessage(m2, true);
    
    ofLogNotice() << "Track Num send : " << trackAddress;
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    string message="Tag Size ?";
    udpConnection.Send(message.c_str(),message.length());
    
    ofLog() << "Message sent : " << message;
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

