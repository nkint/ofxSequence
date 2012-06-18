/*
 * HMM.h
 *
 *  Created on: Feb 18, 2012
 *      Author: alberto
 */

#ifndef HMM_H_
#define HMM_H_

#include "matrix.h"

class HMM {
public:
	HMM(int hiddenStates, int alphabet);
	HMM(int hiddenStates, int alphabet, mat prior, mat transmat, mat obsmat);
	virtual ~HMM();

	vector<double> train(field<rowvec> data, int max_iter);
	double evaluate(field<rowvec> data);

    vector<double> getLL() const;
    mat getObsmat() const;
    mat getPrior() const;
    mat getTransmat() const;
    void setObsmat(mat obsmat);
    void setPrior(mat prior);
    void setTransmat(mat transmat);

    int hiddenStates;
    int alphabet;

    string name;

    field<rowvec> _training_data;

protected:
    mat prior;
    mat transmat;
    mat obsmat;

    vector<double> LL;	// log likehoods of train EM procedure

    void _fwdback(mat init_state_distrib, mat _transmat, mat obslik, mat & alpha, mat & beta, mat & gamma, double & loglik, mat & xi_summed, cube & gamma2, cube & obslik2, bool fwd_only, bool compute_gamma2);
    void fwd(mat init_state_distrib, mat _transmat, mat obslik, mat & alpha, mat & beta, mat & gamma, double & loglik, mat & xi_summed, cube & gamma2, cube & obslik2);
    void fwdback(mat init_state_distrib, mat _transmat, mat obslik, mat & gamma, double & loglik, mat & xi_summed);
    bool em_converged(double loglik, double previous_loglik, double threshold);
	void compute_ess_dhmm(mat startprob, mat transmat, mat obsmat, field<rowvec> data, double &loglik, mat &exp_num_trans, mat &exp_num_visits1, mat &exp_num_emit, mat &exp_num_visitsT);
	vector<double> dhmm_em(field<rowvec> data, int max_iter);
	double dhmm_logprob(field<rowvec> data);
};

#endif /* HMM_H_ */
