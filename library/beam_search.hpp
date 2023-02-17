#include <queue>
#include <chrono>
#include <vector>
#include <sstream>
#include <string>
#include <limits>
typedef int action_number;

template<class ScoreType>
class Template_State{
  private:
    
  public:
    const ScoreType INF=std::numeric_limits<ScoreType>::max();
    int game_score=0;/*ゲーム上で実際に得た得点*/
    ScoreType evaluated_score=0;/*盤面の評価点*/
    int first_action=-1;
    Template_State(){}
    inline bool isDone(){
      /*
      ゲーム終了判定
      */
      return true;
    }
    void advance(const action_number action){
      /*
      指定したアクションで行動する
      */
    }
    std::vector<int> legalActions()const{
      std::vector<int> actions;
      /*
      現在の盤面からアクション可能なものを列挙
      */
      return actions;
    }
    std::string str()const{
      std::stringstream ss;
      /*
      盤面の状況を文字列化する
      */
      return ss.str();
    }
    void evaluateScore(){
      /*
      現在のスコアを評価する
      */
      evaluated_score=game_score;
    }
    bool operator<(const Template_State& state){
      return evaluated_score<state.evaluated_score;
    }
};

template<class State>
action_number beam_search(const State& state, const int beam_width, const int beam_depth,long long each_time){
  using high_clock=std::chrono::high_resolution_clock;
  std::chrono::high_resolution_clock::time_point start_time=high_clock::now();
  std::priority_queue<State> now_beam;
  State best_state;
  now_beam.push(state);
  for(int i=0;i<beam_depth;i++){
    std::priority_queue<State> next_beam;
    for(int j=0;j<beam_width;j++){
      if(std::chrono::duration_cast<std::chrono::milliseconds>(high_clock::now()-start_time).count()>=each_time){
        return best_state.first_action;
      }
      if(now_beam.empty()){
        break;
      }
      State now_state=now_beam.top();
      now_beam.pop();
      auto legal_actions=now_state.leagalActions();
      for(const auto& action:legal_actions){
        State next_state=now_state;
        next_state.advance(action);
        next_state.evaluateScore();
        if(i==0){
          next_state.first_action=action;
        }
        next_state.push(next_state);
      }
    }
    now_beam=next_beam;
    best_state=now_beam.top();
    if(best_state.isDone()){
      break;
    }
  }
  return best_state.first_action;
}

void test(int beam_width, int beam_depth, long long each_time){
  Template_State<long long> state;
  while(!state.isDone()){
    state.advance(beam_search(state,beam_width,beam_depth,each_time));
  }
}
