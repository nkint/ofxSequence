#include "testApp.h"

void testApp::test() {

    // make number easy to read
    fix_stream(cout);

    // initialize a classifier
    ofxClassifier c = ofxClassifier(3,2);

    // a sequence
    c.addSequence("test");

    // some test sequence: for us humans it's simple, a sequence made by 1 followed by some 2
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



void testApp::setup() {
    test();
}


void testApp::update() {
}

void testApp::draw() {
}
