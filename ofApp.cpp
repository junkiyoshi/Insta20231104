#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->font_size = 80;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}


//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	string word = "CreativeCoding";
	auto path_list = font.getStringAsPoints(word, true, false);

	glm::vec3 param = glm::vec3(0, 1, 0);

	for (int i = 0; i < 5; i++) {

		for (auto& path : path_list) {

			vector<ofPolyline> outline = path.getOutline();

			int y = i * 150 - 300;

			ofPushMatrix();
			ofTranslate(0, y, 0);

			ofSetColor(255);
			ofFill();

			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				if (outline_index != 0) { ofNextContour(true); }

				outline[outline_index] = outline[outline_index].getResampledByCount(100);
				auto vertices = outline[outline_index].getVertices();
				for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

					auto location = glm::vec3(vertices[vertices_index].x - this->font.stringWidth(word) * 0.5, vertices[vertices_index].y + this->font.stringHeight(word) * 0.25, 0);
					auto angle = ofMap(ofNoise(i, abs(location.x) * 0.00035 + ofGetFrameNum() * 0.01), 0, 1, -PI * 3, PI * 3);
					auto rotation = glm::rotate(glm::mat4(), angle, param);
					location = glm::vec4(location, 0) * rotation;

					ofVertex(location);
				}
			}
			ofEndShape(true);

			ofSetColor(0);
			ofNoFill();

			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				if (outline_index != 0) { ofNextContour(true); }

				outline[outline_index] = outline[outline_index].getResampledByCount(100);
				auto vertices = outline[outline_index].getVertices();
				for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

					auto location = glm::vec3(vertices[vertices_index].x - this->font.stringWidth(word) * 0.5, vertices[vertices_index].y + this->font.stringHeight(word) * 0.25, 0);
					auto angle = ofMap(ofNoise(i, abs(location.x) * 0.00035 + ofGetFrameNum() * 0.01), 0, 1, -PI * 3, PI * 3);
					auto rotation = glm::rotate(glm::mat4(), angle, param);
					location = glm::vec4(location, 0) * rotation;

					ofVertex(location);
				}
			}
			ofEndShape(true);

			ofPopMatrix();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}