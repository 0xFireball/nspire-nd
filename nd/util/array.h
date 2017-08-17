
#pragma once

template <typename T>
int arr_size(T* arr) {
    return sizeof(arr) / sizeof(arr[0]);
}
