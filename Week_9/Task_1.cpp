#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double

int weight[105], value[105];
ll dp[105][100005];
#define INF 1000005

ll knapsack_dynamic_II(int ind, int v)
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
    ll ans = knapsack_dynamic_II(ind - 1, v);

    // take the item
    if (v - value[ind] >= 0)
    {
        ans = min(ans, knapsack_dynamic_II(ind - 1, v - value[ind]) + weight[ind]);
    }

    dp[ind][v] = ans;

    return dp[ind][v];
}


void print_indices(int col,int n){

    // i the value of the column 
    // n is the row number 
    // 0 based indexing

    vector<int> selected ;

    // cout<<"row col "<<n<<" "<<col<<endl;
    
    for(int i= n;i>0 ;i--){
        

        if(dp[i][col] != dp[i-1][col] && col){
            // cout<<" selected "<<i<<endl;
            
            selected.push_back(i);
            col-= value[i];

            // cout<<"column becomes :" <<col<<endl;
        }
        else{
            continue;
        }
    }

    if(col!=0) {
        selected.push_back(0);
    }

    for(auto x: selected){
        cout<< x +1<<" ";
    }
    cout<<endl;
    
}

void print(int row ,int col){

    for(int i=0;i<=row;i++){
        for(int j=0;j<=col;j++){
            cout<< dp[i][j] <<"       ";
        }
        cout<<  endl;
    }
}

int main()
{

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    memset(dp, -1, sizeof(dp));
    
    for(int i=0;i<105;i++){
        dp[i][0] = 0;
    }

    int n, w;
    cin >> n >> w;

    int max_value = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        cin  >> value[i] >> weight[i];
        max_value = max(value[i], max_value);
    }

    int mx_col = n*max_value;
    vector<int> indices ;

    int row ,col ;

    for (int i = mx_col; i >= 0; i--)
    {
        ll result = knapsack_dynamic_II(n-1,i);
        if (result <= w)
        {
            cout <<"Answer :" << i << endl;
            cout<< "Used weight :" << result <<endl;
            row = n-1;
            col = i;
            cout<< "Indices :"; print_indices(col,row);
            break;
        }
    }
    cout<<endl;
    // print(row,col);
    return  0;

    
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