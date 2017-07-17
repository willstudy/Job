class Solution {
public:
    static bool compare( const string &st1,const string &st2){
        string s1 = st1+st2;
        string s2 = st2+st1;
        return s1<s2;
    }

    string PrintMinNumber(vector<int> numbers) {
        string result;
        if(numbers.size()<=0){
            return result;
        }
        vector<string> strNum;
        for(int i=0;i<numbers.size();i++ ){
            stringstream ss;
            ss<<numbers[i];
            string s = ss.str();
            strNum.push_back(s);
        }

        sort(strNum.begin(),strNum.end(),compare);

        for(int i=0;i<strNum.size();i++){
            result+=strNum[i];
        }

        return result;
    }
};
