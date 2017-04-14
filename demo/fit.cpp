// [[Rcpp::depends(genericMCMC)]]

#include <genericMCMC.h>

using namespace Rcpp;

struct State {
  double p;
};

//[[Rcpp::export]]
NumericVector fit(NumericVector x, int cs, double a, double b, int B, int burn) {

  const double sumx = sum(x);
  const int n = x.size();
  NumericVector out(B);

  auto update = [&](State& s_old, State& s_new) {
    // log prior
    auto lp = [&](double p) {
      double out = 1E-10;
      if (p > 0 && p < 1) {
        out  = (a-1)*log(p) + (b-1)*log(1-p);
      }
      return out;
    };
    // log like
    auto ll = [&](double p) {
      double out = 1E-10;
      if (p > 0 && p < 1) {
        out = sumx*log(p) + (n-sumx)*log(1-p);
      }
      return out
    };

    s_new.p = genericMCMC::metropolis(s_old.p, ll, lp, cs);
  }

  auto samps = genericMCMC::gibbs<State>(init, update, B, burn, 0);
  for (int i=0; i<B; i++) {
    out[i] samps[i].p;
  }

  return out;
}
