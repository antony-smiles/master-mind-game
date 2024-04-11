#include<bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
typedef long long ll;
int pos,colors;
set<vector<int> >all_answers;
map<vector<int>,bool> possible_guess;
set<vector<int> >actual_guess;
map<pair<vector<int>,pair<int,int>>,int> score;
map<vector<int>,int> sender;

void generate(int i,vector<int> v){
  if(i>=pos){all_answers.insert(v);return;}
  for(int j=1;j<=colors;j++){v[i]=j;generate(i+1,v);}
}

void possible_guess_generator(){
  possible_guess.clear();
  actual_guess.clear();
  vector<int>aux(colors+1);
  for(vector<int> k: all_answers){
    for(int i=0;i<=colors;i++)aux[i]=0;
   for(int i=0;i<k.size();i++)aux[k[i]-1]++;
  sort(aux.begin(),aux.end());
   if(!possible_guess[aux]){
  possible_guess[aux]=true;
  actual_guess.insert(k);}
}
}

pair<int,int> scorer(vector<int> k,vector<int> z){
  vector<bool> kp(pos),zp(pos);
  int b=0,w=0;
  for(int i=0;i<k.size();i++){if(k[i]==z[i]){b++;kp[i]=true;zp[i]=true;}}
  for(int i=0;i<k.size();i++){
    for(int j=0;j<z.size();j++){
      if(kp[i]==true||zp[j]==true)continue;
      if(k[i]==z[j]){w++;zp[j]=true;kp[i]=true;}
    }
  }
  return make_pair(b,w);
}

int main(){
  int b=0,w=0;
  cout<<"----------------------------------------------------"<<endl;
  cout<<"                   MASTER MIND"<<endl;
  cout<<"----------------------------------------------------"<<endl;
  //  ios_base::sync_with_stdio(false);
  //cin.tie(NULL);
    cout<<"NO.OF POS : ";
    cin>>pos;
    cout<<"NO.OF COLORS : ";
    cin>>colors;
  vector<int>v(pos);
  generate(0,v);

  while(all_answers.size()!=1){
    
  possible_guess_generator();
  //for(vector<int> k:all_answers){
  // for(int i=0;i<k.size();i++)cout<<(char)(k[i]+'A'-1)<<" ";
  // cout<<endl;
  //}
  score.clear();sender.clear();
  for(vector<int> k:actual_guess){
    for(vector<int> z:all_answers){
      pair<int,int> p=scorer(k,z);
      score[make_pair(k,p)]++;
      sender[k]=max(sender[k],score[make_pair(k,p)]);
    }
  }
  int m=1e9;
  vector<int> ans;
  for(auto t:sender){
    if(t.second<m){m=t.second;ans=t.first;}
  }
  for(int i=0;i<ans.size();i++)cout<<(char)(ans[i]+'A'-1)<<" ";cout<<endl;
  cout<<"NO.OF BLACK-BEDS: ";cin>>b;
  cout<<"NO.OF WHITE-BEDS: ";cin>>w;
  pair<int,int> c;c=make_pair(b,w);
  set<vector<int> >deleted;
  for(vector<int> k:all_answers){
    if(c!=scorer(ans,k))deleted.insert(k);
  }
  for(vector<int> k: deleted)all_answers.erase(k);
  }
								cout<<"SOLUTION : ";
  for(vector<int> k:all_answers){for(int i=0;i<k.size();i++)cout<<(char)(k[i]+'A'-1)<<" ";}
								cout<<endl;
}
