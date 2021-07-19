//
// Created by mbaratella on 17/07/2021.
//

#ifndef PAGERANK_HITS_H
#define PAGERANK_HITS_H

#include <utility>
#include "../Utilities/Utilities.h"
#include "../CSR/CSR.h"

class HITS {
protected:
    CSR csrHub;
    vector<double> hubScores;
    CSR csrAut;
    vector<double> autScores;

public:
    HITS(CSR csrHub, CSR csrAut);

    const CSR &getCsrHub() const;

    void setCsrHub(const CSR &csrHub);

    const CSR &getCsrAut() const;

    void setCsrAut(const CSR &csrAut);

    void compute(bool showRanking);

    const vector<double> &getHubScores() const;

    void setHubScores(const vector<double> &hubScores);

    const vector<double> &getAutScores() const;

    void setAutScores(const vector<double> &autScores);

protected:
    /**
     * Compute authority or hub scores
     *
     * @param isHubScore: if true compute hub scores, otherwise compute authority scores
     * @return
     */
    int hits(bool isHubScore);
};


#endif //PAGERANK_HITS_H
