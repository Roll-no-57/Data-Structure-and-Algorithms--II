#include <bits/stdc++.h>
using namespace std;

#define ll long long
typedef long double ld;
#define INF 1000005

int weight[105];
ll dp[105][100005];

ll knapsack_dynamic_II(int ind, int v, vector<int> &value)
{

    // base case
    if (v == 0)
    {
        return 0;
    }

    if (ind < 0)
    {
        return INF;
    }

    if (dp[ind][v] != -1)
    {
        return dp[ind][v];
    }

    // do not take the item
    ll ans = knapsack_dynamic_II(ind - 1, v, value);

    // take the item
    if (v - value[ind] >= 0)
    {
        ans = min(ans, knapsack_dynamic_II(ind - 1, v - value[ind], value) + weight[ind]);
    }

    dp[ind][v] = ans;

    return dp[ind][v];
}

ll print_indices(int col, int n, vector<int> &value, vector<int> &main_value)
{

    // i the value of the column
    // n is the row number
    // 0 based indexing

    vector<int> selected;

    // cout<<"row col "<<n<<" "<<col<<endl;

    for (int i = n; i > 0; i--)
    {

        if (dp[i][col] != dp[i - 1][col] && col)
        {
            // cout<<" selected "<<i<<endl;

            selected.push_back(i);
            col -= value[i];

            // cout<<"column becomes :" <<col<<endl;
        }
        else
        {
            continue;
        }
    }

    if (col != 0)
    {
        selected.push_back(0);
    }

    ll sum_instances = 0;

    for (auto x : selected)
    {
        cout << x + 1 << "  ";
        sum_instances += main_value[x];
    }
    cout << endl;

    return sum_instances;
}

void print(int row, int col)
{

    for (int i = 0; i <= row; i++)
    {
        for (int j = 0; j <= col; j++)
        {
            cout << dp[i][j] << "       ";
        }
        cout << endl;
    }
}

int find_max(vector<int> &value)
{
    int mx = INT_MIN;
    for (auto x : value)
    {
        mx = max(mx, x);
    }
    return mx;
}

int main()
{

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    memset(dp, -1, sizeof(dp));

    for (int i = 0; i < 105; i++)
    {
        dp[i][0] = 0;
    }

    int n, w;
    cin >> n >> w;

    vector<int> value(n);
    for (int i = 0; i < n; i++)
    {

        cin >> value[i] >> weight[i];
        // max_value = max(value[i], max_value);
    }

    int max_value = find_max(value);

    int mx_col = n * max_value;

    int row, col;

    cout << "Original Instances :" << endl;
    int original_ans;
    for (int i = mx_col; i >= 0; i--)
    {
        ll result = knapsack_dynamic_II(n - 1, i, value);
        if (result <= w)
        {
            original_ans = i;
            cout << "Answer :" << i << endl;
            cout << "Used weight :" << result << endl;
            row = n - 1;
            col = i;
            cout << "Indices :";
            print_indices(col, row, value, value);
            break;
        }
    }
    cout << endl;

    // The second part

    ld ep[] = {0.5, 0.2, 0.1, 0.05};
    ld epsilon;
    for (int r = 0; r < 4; r++)
    {
        epsilon = ep[r];
        cout<<endl;
        cout<<endl;
        cout << "After Reduction : "<<(r+1) << endl;
        ld theta = ((ld)epsilon * (ld)max_value) / (2 * (ld)n);
        cout << "Rounded Instance with Eps: " << epsilon << endl;
        cout << "Theta: " << fixed << setprecision(10) << theta << endl;

        vector<int> reduced_values(n);
        for (int i = 0; i < n; i++)
        {
            reduced_values[i] = ceil((long double)value[i] / theta);
        }

        // calculate the knapsack for the reduced values
        memset(dp, -1, sizeof(dp));

        for (int i = 0; i < 105; i++)
        {
            dp[i][0] = 0;
        }

        int reduced_col = n * find_max(reduced_values);

        int re_row, re_col;

        for (int i = reduced_col; i >= 0; i--)
        {
            ll result = knapsack_dynamic_II(n - 1, i, reduced_values);
            if (result <= w)
            {
                cout << "Answer of reduced instance :" << i << endl;
                cout << "Answer of reduced instance multiplied by theta: " << ((ld)i * (ld)theta) << endl;
                cout << "Indices :";
                re_row = n - 1;
                re_col = i;
                ll rounded_sum = print_indices(re_col, re_row, reduced_values, value);
                cout << "Answer of original instance (rounded up): " << rounded_sum << endl;

                cout << "Used weight :" << result << endl;

                cout << "Ratio: " << fixed << setprecision(10) << ((ld)original_ans / (ld)rounded_sum) << endl;
                break;
            }
        }
        cout << endl;
    }

    // print(row,col,value);
    return 0;
}

/*

8 65
30 15
45 15
140 17
15 50
154 50
7 25
77 23
15 50


Answer :262
Used weight :55
Indices :7 3 2




3 7
3 4
4 6
2 3





42 715
1411 74
1406 75
1406 75
1407 72
1406 73
1407 75
1407 75
1408 74
1409 74
1409 72
1408 72
1412 73
1411 74
1411 75
1408 75
1406 74
1411 74
1410 75
1406 72
1408 74
1410 73
1410 75
1405 73
1411 72
1408 74
1410 74
1408 72
1409 73
1411 74
1409 73
1406 73
1409 75
1405 73
1411 73
1406 73
1409 75
1411 73
1411 75
1407 72
1408 74
1412 72
1409 74



Answer :12701
Used weight :659
Indices :41 37 34 29 24 17 13 12 1



*/
/*


        vector<int> reduced_values(n);

        for (int i = 0; i < n; i++)
        {
            // cout<<value[i]<<" "<<theta<<" "<<(ceil)(1.0*value[i]/theta)<<" "<<value[i]/theta<<endl;
            reduced_values[i] = (ceil)(1.0 * value[i] / theta);
            if (value[i] == max_v)
            {
                reduced_values[i]++;
            }
            // cout<<reduced_values[i]<<endl;
        }

*/
