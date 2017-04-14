# Install the library if needed. This is done only once.
# devtools::install_github('luiarthur/genericMCMC')

Rcpp::sourceCpp("fit.cpp")

set.seed(1)
n <- 10000
p <- 0.73
y <- rbinom(n,1,p)

out <- fit(y,.02,.5,.5,2000,1000)
acceptance_rate <- length(unique(out)) / length(out)

# Plot posterior
hist(out,fg='grey',col='grey',border='white',
     main=paste0('Truth = ',p))
abline(v=mean(out),col='red',lwd=2)
