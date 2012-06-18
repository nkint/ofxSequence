/*
 * ofxGesture.cpp
 *
 *  Created on: Apr 2, 2012
 *      Author: alberto
 */

#include "ofxGesture.h"

ofxGesture::ofxGesture(int alphabet, int hiddenStates, vector<ofPoint> & centroids, ofRectangle & stage, string name) :
	ofxSequence(alphabet, hiddenStates, name) {
	this->centroids = centroids;
	this->stage = stage;
}

ofxGesture::ofxGesture(string namefile) :
	ofxSequence(namefile) {
}

ofxGesture::~ofxGesture() {

}

double ofxGesture::evaluate(vector<ofPoint> newExample) {
	vector<int> labels = toObservation(centroids, stage, newExample);
	return ofxSequence::evaluate(labels);
}

void ofxGesture::addExample(vector<ofPoint> trainExample) {
	vector<int> labels = toObservation(centroids, stage, trainExample);
	ofxSequence::evaluate(labels);
}

vector<int> ofxGesture::toObservation(vector<ofPoint> centroids, ofRectangle stage, vector<ofPoint> points) {
	ofxGesture::rescale(stage, points);

	vector<int> labeled_points;
	// label data ( computational complexity O(centroids*data) )
	int N = points.size();

	for(int i = 0;i < N;++i){
		ofPoint& p = points[i];
		int l = labelPoint(centroids, p);
		labeled_points.push_back(l);
	}
	return labeled_points;
}

int ofxGesture::labelPoint(vector<ofPoint> & centroids, ofPoint & p) {
    int K = centroids.size();
    map<int,float> id2distance;
    for(int j = 0;j < K;++j){
        id2distance[j] = p.distanceSquared(centroids[j]);
    }
    pair<int,float> min = *min_element(id2distance.begin(), id2distance.end(), _compare_second);

    return min.first +1; // +1 because labels must begin from 1 and not from 0
}

void ofxGesture::rescale(ofRectangle stage, vector<ofPoint> & points) {
	// find AABB
	float min_x = 0, min_y = 0, max_x = 0, max_y = 0;
	if(points.size() > 1){
		min_x = (*std::min_element(points.begin(), points.end(), &_compare_min_x)).x;
		min_y = (*std::min_element(points.begin(), points.end(), &_compare_min_y)).y;
		max_x = (*std::max_element(points.begin(), points.end(), &_compare_min_x)).x;
		max_y = (*std::max_element(points.begin(), points.end(), &_compare_min_y)).y;
	}

	float w = max_x - min_x;
	float h = max_y - min_y;

	float target_w, target_h, ratio;
	if (w>h) {
		target_w = stage.width;
		ratio = target_w/w;
		target_h = h*ratio;
	} else {
		target_h = stage.height;
		ratio = target_h/h;
		target_w = w*ratio;
	}

	// scale the values
	int size = points.size();
	for(int i = 0;i < size;++i){
		points[i].x = ofMap(points[i].x, min_x, max_x, 0, target_w);
		points[i].y = ofMap(points[i].y, min_y, max_y, 0, target_h);
	}
}




