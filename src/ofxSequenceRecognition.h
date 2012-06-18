#include "ofMain.h"

#include "ofxClassifier.h"
#include "ofxSequence.h"

static
void testClassifier() {
	ofxClassifier c = ofxClassifier(3,2);
	c.addSequence("test");

	vector<int> s;
	s.push_back(1);
	s.push_back(2);
	s.push_back(2);
	s.push_back(2);
	s.push_back(2);
	s.push_back(2);
	s.push_back(2);
	c.sequenceByName("test")->addExample(s);

	s.clear();
	s.push_back(1);
	s.push_back(2);
	s.push_back(2);
	s.push_back(2);
	c.sequenceByName("test")->addExample(s);

	s.clear();
	s.push_back(1);
	s.push_back(2);
	s.push_back(2);
	s.push_back(2);
	s.push_back(2);
	s.push_back(2);
	c.sequenceByName("test")->addExample(s);

	s.clear();
	s.push_back(1);
	s.push_back(2);
	c.sequenceByName("test")->addExample(s);

	s.clear();
	s.push_back(1);
	s.push_back(2);
	s.push_back(2);
	c.sequenceByName("test")->addExample(s);

	c.sequenceByName("test")->train(25);
	cout << "train done" << endl;

	double d;
	s.clear();
	s.push_back(1);
	s.push_back(2);
	d = c.sequenceByName("test")->evaluate(s);
	cout << d << endl;

	s.clear();
	s.push_back(1);
	s.push_back(2);
	s.push_back(2);
	s.push_back(2);
	s.push_back(2);
	d = c.sequenceByName("test")->evaluate(s);
	cout << d << endl;

	s.clear();
	s.push_back(2);
	s.push_back(2);
	d = c.sequenceByName("test")->evaluate(s);
	cout << d << endl;

	s.clear();
	s.push_back(2);
	s.push_back(1);
	s.push_back(1);
	s.push_back(1);
	d = c.sequenceByName("test")->evaluate(s);
	cout << d << endl;
}
