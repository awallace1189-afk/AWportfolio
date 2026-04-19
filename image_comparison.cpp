#include &lt;bits/stdc++.h&gt;

using namespace std;

int edit_distance(const vector&lt;int&gt;&amp; A, const vector&lt;int&gt;&amp; B) {
    int m = A.size();
    int n = B.size();
    vector&lt;vector&lt;int&gt;&gt; D(m + 1, vector&lt;int&gt;(n + 1));
    for (int i = 0; i &lt;= m; i++) D[i][0] = i;
    for (int j = 0; j &lt;= n; j++) D[0][j] = j;
    for (int i = 1; i &lt;= m; i++) {
        for (int j = 1; j &lt;= n; j++) {
            int cost = (A[i - 1] != B[j - 1]) ? 1 : 0;
            D[i][j] = min({D[i - 1][j] + 1, D[i][j - 1] + 1, D[i - 1][j - 1] + cost});
        }
    }
    return D[m][n];
}

string compare_images(const vector&lt;vector&lt;int&gt;&gt;&amp; X, const vector&lt;vector&lt;int&gt;&gt;&amp; Y, int thresh) {
    int I = X.size();
    int totalDifference = 0;
    for (int i = 0; i &lt; I; i++) {
        int minVali = edit_distance(X[i], Y[i]);
        totalDifference += minVali;
    }
    if (totalDifference &gt; thresh) {
        return "The images are different";
    } else {
        return "The images are similar";
    }
}

int main() {
    // Example usage
    vector&lt;vector&lt;int&gt;&gt; X = {{0, 1, 0}, {1, 0, 1}};
    vector&lt;vector&lt;int&gt;&gt; Y = {{0, 0, 1, 1, 0}, {1, 1, 0}};
    int thresh = 3;
    cout &lt;&lt; compare_images(X, Y, thresh) &lt;&lt; endl;
    return 0;
}