/*
 * ofxSequence.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: alberto
 */

#include "ofxSequence.h"

ofxSequence::ofxSequence(int alphabet, int hiddenStates, string name) {
	hiddenMarkovModel = new HMM(alphabet, hiddenStates);
	hiddenMarkovModel->name = name;
}

ofxSequence::ofxSequence(string namefile)
{
	ofxXmlSettings XML;
	XML.loadFile(namefile);

	string name = XML.getValue("name", "");
	int alphabet = XML.getValue("alphabet", 0);
	int hiddenStates = XML.getValue("hiddenStates", 0);

	mat prior;
	mat transmat;
	mat obsmat;

	prior = matrix_from_string<mat>( XML.getValue("prior", "") );
	transmat = matrix_from_string<mat>( XML.getValue("transmat", "") );
	obsmat = matrix_from_string<mat>( XML.getValue("obsmat", "") );

	HMM * g = new HMM(alphabet, hiddenStates, prior, transmat, obsmat);
	g->name = name;
	this->hiddenMarkovModel = g;
}

ofxSequence::~ofxSequence() {
	delete hiddenMarkovModel;
	trainSet.clear();
}

double ofxSequence::evaluate(vector<int> newExample) {
	rowvec data1 = conv_to< rowvec >::from(newExample);

	field<rowvec> data(data1.n_rows,1);
	data(0,0) = data1;

	double ret = hiddenMarkovModel->evaluate(data);
	return ret;
}

void ofxSequence::train(int max_iter) {
	cout << "ofxSequence::train" << endl;
	field<rowvec> data(trainSet.size(),1);
	vector< vector< int > >::const_iterator iter;
	int r = 0;
	for ( iter = trainSet.begin(); iter != trainSet.end(); ++iter ) {
		vector<int> x = *iter;
		data(r++,0) = conv_to< rowvec >::from(x);
	}
	cout << "ofxSequence::train data: " << data << endl;
	hiddenMarkovModel->train(data, max_iter);
	cout << "ofxSequence::train ." << endl;
}

void ofxSequence::addExample(vector<int> trainExample) {
	trainSet.push_back(trainExample);
}

void ofxSequence::setName(string name) {
	if(hiddenMarkovModel!=NULL) {
		hiddenMarkovModel->name = name;
	}
}
string ofxSequence::getName() {
	if(hiddenMarkovModel!=NULL) {
		return hiddenMarkovModel->name;
	}
	return "";
}






