#pragma once

template <typename T>
T IsSortedUntil(T begin, T end) {
    for (auto it = begin; it < end; ++it) {
        if (*(it + 1) < *it) {
            return it + 1;
        }
    }
    return end;
}
