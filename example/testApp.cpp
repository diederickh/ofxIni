#include "testApp.h"

testApp::testApp():ini("example.ini") {
/* Contents of bin/data/example.ini 
 * ------------------------
[game]
server_port=1234
show_score=y # booelan 
loop_game=true # boolean
speed=0.5 # double

[gui]
enabled=y # boolean, y-n,0,1, etc..
 */

	std::cout	<<	"server port: "		<< ini.get("game:server_port",-1)		<< std::endl
				<<	"show_score:"		<< ini.get("game:show_score", false)	<< std::endl
				<<	"loop_game:"		<< ini.get("game:loop_game", true)		<< std::endl
				<<	"speed:"			<< ini.get("game:speed", 0.2)			<< std::endl
				<<	"gui:"				<< ini.get("gui:enabled", false)		<< std::endl;
			
}
//--------------------------------------------------------------
void testApp::setup(){

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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

