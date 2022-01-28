#pragma once


template <typename T>
void PrintVecOfVec(const vector<vector<T>>& vOv, const string& sep = "\n")
{
    for (auto& v : vOv)
    {
        for (auto& x : v)
            cout << x << " ";
        cout << sep;
    }
    cout << endl;
}
