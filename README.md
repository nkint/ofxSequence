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

#ISSUES  ON OS/X

There are some issues on compiling Armadillo on OS/X. Armadillo is a powerfull library very optimized (it could use some highly scalable parallel computing or other black magic that i completely ignore). Due to this heavy optimization there could be some compilation problem in some platform (32 / 64 bit issues) or other stuffs.
Please do not hesitate to open issues or write me for any kind of problem. Share the problems!

##Issue "check()"
From ofZach
See a solution [here]( https://github.com/nkint/ofxSequence/issues/1#issuecomment-11129335 )

##Issue Undefined symbols for architecture i386: "_wrapper_dgemm_"
From ptrigueiros@gmail.com
I'm using a Mac Book Pro with mac osx 10.7.5 and XCode 4.5.
Solution to use ofxSequence with Armadillo library (openFrameworks)

1.     Since mac osx is 64 bits, when we download and compile the source code for Amarillo it becomes 64-bits (x86_64).
        The same happens if we try to install the library via macports.
        Since openFrameworks is 32bits on mac the two don't work together.... :-(
        So, the solution is to force macports to i386.... to install armadillo
2.     Force macports to i386:
        a) edit macports.conf:   
            # sudo vim /opt/local/etc/macports/macports.conf
        b) force i386 on macports: 
            search for build_arch and uncomment that line to build_arch    i386
        c) save macports.conf
        d) install armadillo library
            # sudo port install armadillo (armadillo 3.4 is the current version on my system)
            this process will install some dependencies like boost (i386)
3.     After this you can compile the example that comes with ofxSequence under XCode 4.5.
