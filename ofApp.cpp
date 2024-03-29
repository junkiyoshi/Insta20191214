#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	for (int i = 0; i < 5; i++) {

		auto angle_x = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 0, PI);
		auto angle_y = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 0, PI);
		auto angle_z = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 0, PI);

		auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
		auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
		auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));

		for (int deg = 0; deg < 360; deg += 2) {

			auto location = glm::vec3(300 * cos(deg * DEG_TO_RAD), 300 * sin(deg * DEG_TO_RAD), 0);
			location = glm::vec4(location, 0) * rotation_z * rotation_y * rotation_x;

			this->mesh.addVertex(location);
		}
	}

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		for (int k = 0; k < this->mesh.getNumVertices(); k++) {

			if (i == k) { continue; }

			if (glm::distance(this->mesh.getVertex(i), this->mesh.getVertex(k)) < 50) {

				this->mesh.addIndex(i); this->mesh.addIndex(k);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->mesh.drawWireframe();
	for (auto& vertex : this->mesh.getVertices()) {

		ofDrawSphere(vertex, 2);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}