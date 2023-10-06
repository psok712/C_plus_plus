#pragma once

template <typename T, typename U>
U Copy(T src_begin, T src_end, U dest) {
    for (; src_begin != src_end; (void)++src_begin) {
        *dest = *src_begin;
        (void)++dest;
    }
    return dest;
}

template <typename T, typename U>
U CopyBackward(T src_begin, T src_end, U dest) {
    (void)--src_end;
    for (; src_end >= src_begin; (void)--src_end) {
        (void)--dest;
        *dest = *src_end;
    }
    return dest;
}
