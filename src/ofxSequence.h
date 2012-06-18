/*
 * ofxSequence.h
 *
 *  Created on: Apr 1, 2012
 *      Author: alberto
 */

#ifndef OFXSEQUENCE_H_
#define OFXSEQUENCE_H_

#include "ofMain.h"
#include "ofxXmlSettings.h"

#include "HMM.h"

class ofxSequence {
public:
	ofxSequence(int alphabet, int hiddenStates, string name="");
	ofxSequence(string namefile);
	virtual ~ofxSequence();

	void addExample(vector<int> trainExample);
	void train(int max_iter=10);
	double evaluate(vector<int> newExample);

	string getName();
	void setName(string name);

private:
	vector<vector<int> > trainSet;
	HMM * hiddenMarkovModel;
};

#endif /* OFXSEQUENCE_H_ */
