void compute(string pat, int m , vector<int>&lps){
        int len = 0, i = 1;
        lps[0] = 0;
        while(i < m){
            if(pat[i] == pat[len]){
                lps[i] = len + 1;
                len++,i++;
            }
            else{
                if(len != 0){
                    len = lps[len - 1];
                }
                else{
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }
  
  
  
  
    vector<int> search(string& pat, string& txt) {
        int n = txt.length();
        int m = pat.length();
        vector<int>ans;
        vector<int>lps(m+1,0);
        compute(pat,m,lps);
        int i = 0, j = 0;
        while(i < n){
            if(txt[i] == pat[j]){
                i++, j++;
            }
            else{
                if(j != 0){
                    j = lps[j-1];
                }
                else{
                    i++;
                }
            }
            if(j == m){
                ans.push_back(i - m);
                j = lps[j - 1];
            }
        }
        return ans;
    }
