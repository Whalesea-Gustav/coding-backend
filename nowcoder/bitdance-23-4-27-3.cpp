#include <bits/stdc++.h>

using namespace std;

bool finish(const vector<vector<int>>& matrix)
{
    int H = matrix.size();
    int Col = 5;

    for (int h = 0; h < H; ++h)
    {
        for (int i = 0; i <= 2; ++i)
        {
            if(matrix[h][i] <= 9 && matrix[h][i] == matrix[h][i+1] && matrix[h][i+1] == matrix[h][i+2])
            {
                return false;
            }
        }
    }
    return true;
}

int main() {

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t)
    {
        int H;
        cin >> H;

        vector<vector<int>> matrix(H, vector<int>(5, 0));

        for (int h = 0; h < H; ++h)
        {
            for (int i = 0; i < 5; ++i)
            {
                cin >> matrix[h][i];
            }
        }

        int count = 0;

        while(!finish(matrix))
        {
            //消除操作

            for (int h = 0; h < H; ++h)
            {
                for (int i = 0; i <= 2; ++i)
                {
                    if(matrix[h][i] > 9) continue;

                    int local_count = 1;
                    int j = i + 1;

                    while(j < 5 && matrix[h][j] == matrix[h][i])
                    {
                        j++;
                        local_count++;
                    }

                    if (local_count >= 3)
                    {
                        //消除操作
                        count += local_count * matrix[h][i];
                        for (int k = 0; k < local_count; ++k)
                        {
                            matrix[h][i+k] = 11;
                        }
                    }
                }
            }

            //压缩操作

            for (int col = 0; col < 5; ++col)
            {
                //前后指针处理每一列
                int front = H - 1, back = H - 1;

                while(back >= 0)
                {
                    if (matrix[back][col] <= 9)
                    {
                        matrix[front][col]  = matrix[back][col];
                        front--;
                    }
                    back--;
                }

                //剩下的数据也清零

                while(front >= 0)
                {
                    matrix[front][col] = 11;
                    front--;
                }
            }
        }

        cout << count << endl;
    }
}
