#ifndef UTILS_H
#define UTILS_H

template <typename T>
const T& clamp(const T& v, const T& lo, const T& hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

#endif 