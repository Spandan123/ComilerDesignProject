#include <bits/stdc++.h>
// #include
using namespace std;

int trap(vector<int> &height)
{
    int total_water = 0;
    int n = height.size();
    for (int i = 1; i <= n - 1; i++)
    {
        cout << "Checking height[" << i << "] = " << height[i] << endl;
        int left_height = i;
        int right_height = i;
        while (1)
        {
            if (left_height > 0 && right_height < n && height[left_height - 1] >= height[left_height] && height[right_height + 1] >= height[right_height])
            {
                left_height--;
                right_height++;
                cout << "left_height = " << height[left_height] << " right_height = " << height[right_height] << endl;
            }
            else
            {
                cout << "breaking" << endl;
                break;
            }
        }
        if (left_height == i)
            continue;
        int w_h = min(height[left_height], height[right_height]);
        for (int j = left_height + 1; j <= right_height - 1; j++)
        {
            total_water += (w_h - height[j]);
            height[j] = w_h;
        }
    }
    return total_water;
}

int main(int argc, char *argv[])
{
    vector<int> height = {4, 2, 0, 3, 2, 5};
    /*
        [ 4, 2, 0, 3, 2, 5 ]
        --> [ 4, 2, 2, 3, 2, 5]    water = 2
        --> [ 4, ]
    */
    cout << trap(height) << endl;
    remove(argv[0]);
    return 0;
}