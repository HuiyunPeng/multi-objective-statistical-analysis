int sum_to_n(int n){
    return (n & 1) ? n * ((n + 1) / 2) : (n / 2) * (n + 1);
}
