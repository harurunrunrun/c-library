struct Compress_Plane{
  private:
    map<long long,unsigned> X_compress;
    map<long long,unsigned> Y_compress;
    vector<long long> X_origin;
    vector<long long> Y_origin;
    vector<long long> add_extra_space(vector<long long> Z,bool extra1,bool extra2){
      unsigned M=Z.size();
      if(extra1){
        Z.reserve(2*M);
        for(unsigned i=0;i<M;i++){
          Z.push_back(Z[i]+1);
        }
      }
      if(extra2){
        Z.reserve(3*M);
        for(unsigned i=0;i<M;i++){
          Z.push_back(Z[i]-1);
        }
      }
      sort(Z.begin(),Z.end());
      Z.erase(unique(Z.begin(),Z.end()),Z.end());
      return Z;
    }
    void compress(const vector<long long>& Z,map<long long,unsigned>& cp){
      for(unsigned i=0;i<Z.size();i++){
        cp[Z[i]]=i;
      }
      return;
    }
  public:
    Compress_Plane()=default;
    Compress_Plane(vector<long long> X,vector<long long> Y,bool extra_plus=true,bool extra_minus=false){
      X_origin=add_extra_space(X,extra_plus,extra_minus);
      Y_origin=add_extra_space(Y,extra_plus,extra_minus);
      compress(X_origin,X_compress);
      compress(Y_origin,Y_compress);
    }
    long long revive_X(unsigned idx){
      return X_origin[idx];
    }
    long long revive_Y(unsigned idy){
      return Y_origin[idy];
    }
    unsigned convert_X(long long idx){
      return X_compress[idx];
    }
    unsigned convert_Y(long long idy){
      return Y_compress[idy];
    }
    unsigned size_X(){
      return X_origin.size();
    }
    unsigned size_Y(){
      return Y_origin.size();
    }
};
