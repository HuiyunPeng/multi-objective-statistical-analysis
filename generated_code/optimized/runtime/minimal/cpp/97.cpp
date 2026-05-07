int multiply(int a,int b){
    a %= 10;
    if (a < 0) a = -a;
    b %= 10;
    if (b < 0) b = -b;
    return a * b;
}
