/*
 * ofxClassifier.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: alberto
 */

#include "ofxClassifier.h"

ofxClassifier::~ofxClassifier() {
	// TODO Auto-generated destructor stub
}

//---------------------------------------------------------------- sequences
ofxClassifier::ofxClassifier(int alphabet, int hiddenStates) {
	this->alphabet = alphabet;
	this->hiddenStates = hiddenStates;
}

void ofxClassifier::addSequence(string name) {
	ofxSequence * n = new ofxSequence(alphabet, hiddenStates, name);
	addSequence(name, n);
}

void ofxClassifier::addSequence(string name, ofxSequence * n) {
	name2gesture[name] = n;
}

ofxSequence *ofxClassifier::sequenceByName(string name) {
	return name2gesture[name];
}

string ofxClassifier::evaluate(vector<int> newObservation, double threashold) {
	cout << "ofxClassifier::evaluate with " << threashold << " threashold." << endl;
	double loglik;
	double maxlik = -std::numeric_limits<double>::max();
	map<double, string> loglik2name;

	map<string, ofxSequence*>::const_iterator i;
	for(i = name2gesture.begin(); i!= name2gesture.end(); ++i) {
		ofxSequence * s = i->second;
		string name = i-> first;
		loglik = s->evaluate(newObservation);
		if (loglik>maxlik)
			maxlik = loglik;
		loglik2name[loglik] = name;
		cout << "ofxClassifier::evaluate ---- " << name << " get: " << loglik << endl;
	}

	if(maxlik>threashold)
		return loglik2name[maxlik];
	else
		return "not recognized";
}

//---------------------------------------------------------------- gestures
ofxClassifier::ofxClassifier(int alphabet, int hiddenStates, int n_centroids, ofRectangle stage) {
	this->alphabet = alphabet;
	this->hiddenStates = hiddenStates;
	this->stage = stage;

	float x,y;
	float sqrt_n = sqrt(n_centroids);
	for (int i = 1; i < sqrt_n; ++i) {
		x = i*stage.width/sqrt_n;
		for (int j = 1; j < sqrt_n; ++j) {
			y = j*stage.height/sqrt_n;
			this->centroids.push_back(ofPoint(x,y));
		}
	}
}

void ofxClassifier::addGesture(string name) {
	ofxGesture * n = new ofxGesture(alphabet, hiddenStates, centroids, stage, name);
	addGesture(name, n);
}

void ofxClassifier::addGesture(string name, ofxGesture *n) {
	this->addSequence(name, n);
}


string ofxClassifier::evaluate(vector<ofPoint> newObservation, double threashold) {
	cout << "ofxClassifier::evaluate ofPoint obs" << endl;
	vector<int> obs = ofxGesture::toObservation(centroids, stage, newObservation);

	return this->evaluate(obs, threashold);
}


ofxGesture * ofxClassifier::gestureByName(string name) {
	return static_cast<ofxGesture *>(name2gesture[name]);
}

void ofxClassifier::load(string namefile)
{
	ofxSequence * n = new ofxSequence(namefile);
	addSequence(n->getName(), n);
}


