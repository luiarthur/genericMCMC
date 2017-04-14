# genericMCMC
My template C++ code to be used with other C++ code in Rcpp

See [the devtools doc][1] and the [Rcpp (section 3.6) doc][2] for
more help.


# Developers

```bash
# Generate docs
R -e "roxygen2::roxygenise()"

# git add .
# git commit
# git push

# Install
R -e "devtools::install_github('luiarthur/genericMCMC')"
```


[1]: http://r-pkgs.had.co.nz/src.html
[2]: http://dirk.eddelbuettel.com/code/rcpp/Rcpp-attributes.pdf
