int choose_num(int x, int y) {
    if (y < x || (y == x && (y & 1))) return -1;
    return (y & 1) ? (y - 1) : y;
}
