// [[Rcpp::depends(genericMCMC)]]

#include<genericMCMC.h>
#include<functional>

using namespace Rcpp;

// Enable C++11 via this plugin (Rcpp 0.10.3 or later)
// [[Rcpp::plugins("cpp11")]]

struct State {
  double p;
};

//[[Rcpp::export]]
NumericVector fit(NumericVector x, double cs, double a, double b, int B, int burn) {

  const double sumx = sum(x);
  const int n = x.size();
  NumericVector out(B);

  auto update = [&](State& s_old, State& s_new) {
    // log prior
    auto lp = [&](double p) {
      double out = -INFINITY;
      if (p > 0 && p < 1) {
        out  = (a-1)*log(p) + (b-1)*log(1-p);
      }
      return out;
    };
    // log like
    auto ll = [&](double p) {
      double out = -INFINITY;
      if (p > 0 && p < 1) {
        out = sumx*log(p) + (n-sumx)*log(1-p);
      }
      return out;
    };

    s_new.p = metropolis(s_old.p, ll, lp, cs);
  };

  auto init = State{ 0.5 };
  auto samps = gibbs<State>(init, update, B, burn, 0);

  for (int i=0; i<B; i++) {
    out[i] = samps[i].p;
  }

  return out;
}
