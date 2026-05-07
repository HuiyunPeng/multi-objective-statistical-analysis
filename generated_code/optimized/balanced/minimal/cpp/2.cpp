inline float truncate_number(float number) noexcept {
    return number - static_cast<int>(number);
}
