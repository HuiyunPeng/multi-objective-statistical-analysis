int choose_num(int x, int y) {
    if (y < x) return -1;
    if (y & 1) return (y == x) ? -1 : (y - 1);
    return y;
}
