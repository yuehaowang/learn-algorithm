/************
 * http://hihocoder.com/contest/hiho228/problem/1
 */


#include <stack>
#include <iostream>

using namespace std;

int main()
{
    string inp;
    
    cin >> inp;
    
    int l_arr[inp.size()];
    int r_arr[inp.size()];
    
    stack<int> s;
    
    for (int i = 0; i < inp.size(); i++) {
        char c = inp[i];
        
        if (c == '(') {
            s.push(i);
            l_arr[i] = 1;
        } else {
            l_arr[i] = 0;
            r_arr[s.top()] = i;
            
            s.pop();
        }
    }
    
    for (int j = 0; j < inp.size(); j++) {
        if (l_arr[j] == 1) {
            cout << j + 1 << " " << r_arr[j] + 1 << endl;
        }
    }

    return 0;
}