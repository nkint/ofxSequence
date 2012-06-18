/*
 * ofxClassifier.h
 *
 *  Created on: Apr 1, 2012
 *      Author: alberto
 */

#ifndef OFXCLASSIFIER_H_
#define OFXCLASSIFIER_H_

#include "ofMain.h"

#include "ofxSequence.h"
#include "ofxGesture.h"

class ofxClassifier {
public:

	virtual ~ofxClassifier();

	ofxClassifier(int alphabet, int hiddenStates);
	void addSequence(string name);
	void addSequence(string name, ofxSequence * n);
	ofxSequence * sequenceByName(string name);

	ofxClassifier(int alphabet, int hiddenStates, int n_centroids, ofRectangle stage);
	void addGesture(string name);
	void addGesture(string name, ofxGesture * n);
	ofxGesture * gestureByName(string name);

	string evaluate(vector<int> newObservation, double threashold);
	string evaluate(vector<ofPoint> newObservation, double threashold);

	void load(string namefile);

	vector<ofPoint> & getCentroids() {
		return centroids;
	}
	ofRectangle & getStage() {
		return stage;
	}

private:
	int alphabet, hiddenStates;
	vector<ofPoint> centroids;
	ofRectangle stage;

	vector<ofxSequence*> hmms;
	map<string, ofxSequence*> name2gesture;
};

#endif /* OFXCLASSIFIER_H_ */
