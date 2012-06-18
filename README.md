#Description
ofxSequence is an addon for openframeworks for classification and recognition of numeric sequences.

#What can i do with it?
You can perform pattern recognition like, for example, gesture recognition.

#How does it work?
First of all you need to collect some similar gesture and "train" a classifier with it.
It will learn some similar feature of a class of gesture.
And do this for a brunch of gesture.
Then, you can give to the classifier a new gesture and it will tell you what is the most similar of the trained ones.

#No, i mean, how does it work under the hood?
It is based on a probabilistic model called [hidden markov model](http://en.wikipedia.org/wiki/Hidden_Markov_model), a mathematical tool for model time-varying data with some hidden stochastic variables.
Theoretical basis of pattern recognition (originally applied to audio speech samples) can be found in [Rabiner paper](http://www.cs.cornell.edu/Courses/cs4758/2012sp/materials/hmm_paper_rabiner.pdf)
It is a porting in c++ of MATLAB code from Kevin Murphy, [HMM MATLAB Toolbox](http://www.cs.ubc.ca/~murphyk/Software/HMM/hmm.html)

#Addon for OpenFrameworks, uh?
Yeah it is an addon for OpenFrameworks but it has also a dependency from [Armadillo](http://arma.sourceforge.net/): a linear algebra libray written in C++ that make life easier when you try to port some MATLAB code in C++ :-)
