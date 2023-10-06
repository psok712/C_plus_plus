#include "cstring.h"

size_t Strlen(const char* str) {
    size_t count = 0;
    for (auto it = str; *it != '\0'; ++it) {
        ++count;
    }
    return count;
}

int Strcmp(const char* first, const char* second) {
    if (Strlen(first) == Strlen(second) && Strlen(first) == 0) {
        return 0;
    }

    while (*first != '\0' || *second != '\0') {
        if (*first > *second) {
            return 1;
        } else if (*first < *second) {
            return -1;
        }
        ++first;
        ++second;
    }
    if (Strlen(first) > Strlen(second)) {
        return 1;
    } else if (Strlen(first) < Strlen(second)) {
        return -1;
    } else if (Strlen(first) == Strlen(second)) {
        return 0;
    }
    return -1;
}

int Strncmp(const char* first, const char* second, size_t count) {
    if ((Strlen(first) == Strlen(second) && Strlen(first) == 0) || count == 0 ||
        (first == nullptr && second == nullptr)) {
        return 0;
    } else if (first == nullptr) {
        return -1;
    } else if (second == nullptr) {
        return 1;
    }

    for (size_t i = 0; i < count; ++i, ++first, ++second) {
        if (*first == '\0' || *second == '\0') {
            break;
        }

        if (*first > *second) {
            return 1;
        } else if (*first < *second) {
            return -1;
        }

        if (i == count - 1) {
            return 0;
        }
    }
    if (Strlen(first) > Strlen(second)) {
        return 1;
    } else if (Strlen(first) < Strlen(second)) {
        return -1;
    }
    return 0;
}

char* Strcpy(char* dest, const char* src) {
    for (auto it = src; *it != '\0'; ++it) {
        if (it == dest) {
            dest = new char[Strlen(dest)];
        }
    }

    for (auto it = src; *it != '\0'; ++it) {
        dest[it - src] = *it;
    }
    dest[Strlen(src)] = '\0';
    return dest;
}

char* Strncpy(char* dest, const char* src, size_t count) {
    for (auto it = src; *it != '\0'; ++it) {
        if (it == dest) {
            dest = new char[Strlen(dest)];
        }
    }

    size_t i = 0;
    for (auto it = src; i < count; ++i) {
        if (static_cast<size_t>(it - src) < Strlen(src)) {
            dest[it - src] = *it;
            ++it;
        } else {
            dest[i] = '\0';
        }
    }
    return dest;
}

char* Strcat(char* dest, const char* src) {
    size_t length = Strlen(dest);
    for (auto it = src; *it != '\0'; ++it) {
        dest[length + it - src] = *it;
    }
    dest[length + Strlen(src)] = '\0';
    return dest;
}

char* Strncat(char* dest, const char* src, size_t count) {
    if (count >= Strlen(src)) {
        return Strcat(dest, src);
    }

    size_t length = Strlen(dest);
    size_t i = 0;
    for (auto it = src; i < count; ++it, ++i) {
        dest[length + i] = *it;
    }
    dest[length + i] = '\0';
    return dest;
}

const char* Strchr(const char* str, char symbol) {
    if (symbol == '\0') {
        return str + Strlen(str);
    }

    for (auto it = str; *it != '\0'; ++it) {
        if (*it == symbol) {
            return it;
        }
    }
    return nullptr;
}

const char* Strrchr(const char* str, char symbol) {
    if (symbol == '\0') {
        return str + Strlen(str);
    }

    const char* iter = nullptr;
    for (auto it = str; *it != '\0'; ++it) {
        if (*it == symbol) {
            iter = it;
        }
    }
    return iter;
}

size_t Strspn(const char* dest, const char* src) {
    size_t count = 0;

    for (auto it = dest; *it != '\0'; ++it) {
        bool flag = false;
        for (auto iter = src; *iter != '\0'; ++iter) {
            if (*iter == *it) {
                ++count;
                flag = true;
                break;
            }
        }
        if (!flag) {
            return count;
        }
    }
    return count;
}

size_t Strcspn(const char* dest, const char* src) {
    size_t count = 0;

    for (auto it = dest; *it != '\0'; ++it) {
        for (auto iter = src; *iter != '\0'; ++iter) {
            if (*iter == *it) {
                return count;
            }
        }
        ++count;
    }
    return count;
}

const char* Strpbrk(const char* dest, const char* breakset) {
    for (auto it = dest; *it != '\0'; ++it) {
        for (auto iter = breakset; *iter != '\0'; ++iter) {
            if (*it == *iter) {
                return it;
            }
        }
    }
    return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
    if (Strlen(str) == Strlen(pattern) && Strlen(str) == 0) {
        return str;
    } else if (Strlen(str) < Strlen(pattern) || str == nullptr || pattern == nullptr) {
        return nullptr;
    }
    for (auto it = str; *it != '\0'; ++it) {
        bool flag = true;
        if (Strlen(it) < Strlen(pattern)) {
            break;
        }
        for (auto iter1 = it, iter2 = pattern; *iter2 != '\0'; ++iter1, ++iter2) {
            if (*iter1 != *iter2) {
                flag = false;
                break;
            }
        }
        if (flag && Strlen(it) >= Strlen(pattern)) {
            return it;
        }
    }
    return nullptr;
}
