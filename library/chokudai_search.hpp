#include <vector>
#include <queue>
#include <chrono>
template<class State>
int chokudai_search(const State& state, const int beam_width, const int beam_depth, const int beam_number, long long each_time){
  using high_clock=std::chrono::high_resolution_clock;
  std::chrono::high_resolution_clock::time_point start_time=high_clock::now();
  std::vector<std::priority_queue<State>> beam(beam_depth+1);
  beam[0].push(state);
  for(int i=0;i<beam_number;i++){
    for(int j=0;j<beam_depth;j++){
      std::priority_queue<State>& now_beam=beam[j];
      std::priority_queue<State>& next_beam=beam[j+1];
      for(int k=0;k<beam_width;k++){
        if(now_beam.empty()){
          break;
        }
        State now_state=now_beam.top();
        if(now_state.isDone()){
          break;
        }
        now_beam.pop();
        auto legal_actions=now_state.legalActions();
        for(const auto& action:legal_actions){
          State next_state=now_state;
          next_state.advance(action);
          next_state.evaluateScore();
          if(j==0){
            next_state.first_action=action;
          }
          next_beam.push(next_state);
        }
      }
    }
    if(std::chrono::duration_cast<std::chrono::milliseconds>(high_clock::now()-start_time).count()>=each_time){
      break;
    }
  }
  for(int i=beam_depth;i>=0;i--){
    const std::priority_queue<State>& now_beam=beam[i];
    if(!now_beam.empty()){
      return now_beam.top().first_action;
    }
  }
  return -1;
}
