/*
 * ofxGesture.h
 *
 *  Created on: Apr 2, 2012
 *      Author: alberto
 */

#ifndef OFXGESTURE_H_
#define OFXGESTURE_H_

#include "ofMain.h"

#include "ofxSequence.h"

class ofxGesture: public ofxSequence {
public:
	ofxGesture(int alphabet, int hiddenStates, vector<ofPoint> & centroids, ofRectangle & stage, string name="");
	ofxGesture(string namefile);
	virtual ~ofxGesture();

	void addExample(vector<ofPoint> trainExample);
	double evaluate(vector<ofPoint> newExample);

	static vector<int> toObservation(vector<ofPoint> centroids, ofRectangle stage, vector<ofPoint> points);
	static int labelPoint(vector<ofPoint> & centroids, ofPoint & p);
	static void rescale(ofRectangle stage, vector<ofPoint> & points);

private:
	vector<ofPoint> centroids;
	ofRectangle stage;

	vector<int> label(vector<ofPoint> data, bool scale);

	static bool _compare_second(pair<int, float> a, pair<int, float> b) { return a.second < b.second; }
	static bool _compare_min_x(ofPoint const &p1, ofPoint const &p2) { return p1.x < p2.x; }
	static bool _compare_min_y(ofPoint const &p1, ofPoint const &p2) { return p1.y < p2.y; }

};

#endif /* OFXGESTURE_H_ */
