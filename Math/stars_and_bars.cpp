//lets x+y+z = 2, and the qus is how many way to make equation valid. here (= 2) is star and (+) is bar.

ll ncr(int n, int r){
    return fact[n] * ifact[n - r] % mod * ifact[r] % mod;
}

ll stars_and_bars(int stars, int bars) {
    return ncr(stars + bars, bars);  // Equivalent to ncr(stars + bars, stars)
}
