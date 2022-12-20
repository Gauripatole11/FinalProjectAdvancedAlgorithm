
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#include <chrono>
using namespace std::chrono;

class GreedyApproach {
    public:
    int binarysearch(int lo,int hi,int val,vector<int> a)
    {
        while(lo<hi)
        {
            int mid=lo+(hi-lo)/2;
            if(a[mid]<val)
                lo=mid+1;
            else
                hi=mid-1;
        }
        return lo;
    }
    int lengthOfLIS(vector<int>& nums) {
        int n=nums.size();
        vector<int> a;
        a.push_back(nums[0]);
        for(int i=1;i<n;i++)
        {
            int k=binarysearch(0,a.size(),nums[i],a);
            // cout<<i<<":"<<k<<":"<<a.size()<<"\n";
            if(k==a.size())
            {
                if(a[k-1]<nums[i])
                    a.push_back(nums[i]);
                else
                    a[k-1]=nums[i];
            }
            else
            {
                if(a[k]>=nums[i])
                    a[k]=nums[i];
                else
                    a[k+1]=nums[i];
            }
            // for(auto j:a)
            //     cout<<j<<":";
            // cout<<"\n";
                
        }
        return a.size();
    }
};



class Bruteforce {
    public:
    int lengthOfLIS(vector<int>& nums) {
        return solve(nums, 0, INT_MIN);
    }
    int solve(vector<int>& nums, int i, int prev) {
        // cant pick any more elements
        if(i >= nums.size()) return 0;                     
        // try skipping the current element           
        int take = 0, dontTake = solve(nums, i + 1, prev);
        // or pick it if it is greater than previous picked element
        if(nums[i] > prev) take = 1 + solve(nums, i + 1, nums[i]);
        // return whichever choice gives max LIS
        return max(take, dontTake);                                  
    }
};


class DynamicProgramming {
    public:
    int lengthOfLIS(vector<int>& nums) {

        vector<int> BIS(nums.size() + 1, INT_MAX);
        int len = 0;
        
        for (int i = 0; i < nums.size(); i++)
        {
            for (int k = 0; k < i; k++)
            {
                if (nums[i] > BIS[k] && nums[i] < BIS[k + 1])
                    BIS[k + 1] = nums[i];
            }
            if (BIS[0] > nums[i])
                BIS[0] = nums[i];
        }
        
        for (len = 0; len < BIS.size(); len++)
            if (BIS[len] >= INT_MAX)
                break;
                
        return len;
    }
};

void print_int_vector(vector<int>path){
    for (int i: path)
        cout << i << ',';
}
void print_float_vector(vector<float>path){
    for (float i: path)
        cout << i << ',';
}

vector<int> generate_test_cases(int n) {
    vector<int> result;
    for (int i=0; i<n; i++) {
        result.push_back(i);
    }
    random_shuffle(result.begin(), result.end());
    return result;
}


int main() {
  int n,i,a,j;
  vector <int> nums;
  vector <float> dp_execution_time, bf_execution_time, greedy_execution_time;
  vector <int> dp_answers, bf_answers, greedy_answers;
  cout << "Enter the number of testcases to try: ";
  cin >> n;
  int q = 1;
  for (i = 0; i < n; i++) {
    nums = generate_test_cases(q);
    q++;
    DynamicProgramming dp;
    Bruteforce bf;
    GreedyApproach greedy;
    print_int_vector(nums);
    cout<<endl;
    auto start = high_resolution_clock::now();
    int dp_sol = dp.lengthOfLIS(nums);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    dp_execution_time.push_back(duration.count());
    dp_answers.push_back(dp_sol);

    start = high_resolution_clock::now();
    int bf_sol = bf.lengthOfLIS(nums);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    bf_execution_time.push_back(duration.count());
    bf_answers.push_back(bf_sol);

    start = high_resolution_clock::now();
    int greedy_sol = bf.lengthOfLIS(nums);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    greedy_execution_time.push_back(duration.count());
    greedy_answers.push_back(greedy_sol);
  }
  
  
  cout<<"dp_answers"<<endl;
  print_int_vector(dp_answers);
  cout<<endl;
  cout<<"bf_answers"<<endl;
  print_int_vector(bf_answers);
  cout<<endl;
  cout<<"greedy_answers"<<endl;
  print_int_vector(greedy_answers);
  cout<<endl;
  cout<<"dp_execution_time"<<endl;
  print_float_vector(dp_execution_time);
  cout<<endl;
  cout<<"bf_execution_time"<<endl;
  print_float_vector(bf_execution_time);
  cout<<endl;
  cout<<"greedy_execution_time"<<endl;
  print_float_vector(greedy_execution_time);

  return 0;
}

/*

Enter the number of testcases to try: 20
0,
0,1,
2,1,0,
1,0,3,2,
1,3,0,2,4,
2,1,5,3,0,4,
2,0,3,6,1,5,4,
0,2,6,1,4,3,7,5,
7,2,0,6,4,5,8,3,1,
0,6,1,8,7,4,5,2,3,9,
2,5,4,9,1,7,6,0,10,3,8,
4,10,11,0,2,8,7,6,5,9,1,3,
3,12,4,1,0,6,9,11,10,2,8,7,5,
7,9,2,12,5,8,3,11,4,6,10,13,0,1,
8,5,10,11,7,4,9,12,3,1,0,14,13,6,2,
15,2,12,7,0,4,8,11,13,5,1,6,10,9,3,14,
7,10,14,4,2,15,11,3,6,16,12,8,5,9,1,0,13,
17,0,2,7,5,8,9,3,13,11,10,4,6,16,14,15,1,12,
2,15,5,8,11,12,0,1,13,9,4,10,16,7,3,14,6,17,18,
8,5,15,18,16,7,0,2,10,4,9,19,13,12,17,11,6,14,1,3,
dp_answers
1,2,1,2,3,3,3,4,4,5,4,4,5,6,5,6,6,8,9,6,
bf_answers
1,2,1,2,3,3,3,4,4,5,4,4,5,6,5,6,6,8,9,6,
greedy_answers
1,2,1,2,3,3,3,4,4,5,4,4,5,6,5,6,6,8,9,6,
dp_execution_time
1,1,1,4,1,1,1,4,1,1,1,2,2,2,2,8,3,3,3,7,
bf_execution_time
0,0,0,0,0,1,2,3,3,4,6,6,10,12,13,20,19,107,67,47,
greedy_execution_time
0,0,0,0,0,0,1,2,2,3,5,5,9,12,12,18,18,89,63,44

*/
