#include "ConsumerThread.hpp"


ConsumerThread::ConsumerThread(uint id, bool_mat &curr, bool_mat &next, vector<float> &tile_hist, PCQueue<Job> &pcQueue,
                               CounterBarrier &barrier, pthread_mutex_t &timerLock)
        : Thread(id), curr(curr), next(next), tile_hist(tile_hist), pcQueue(pcQueue), barrier(barrier),
          timerLock(timerLock) {}

void ConsumerThread::thread_workload() {
  while(true){
      // ?
      //pop job from queue
      Job job=pcQueue.pop();

      if(job.poison){
        break;
      }

      //start timer
      auto gen_start = std::chrono::system_clock::now();
      //execute job
      execute(job);
     //stop timer;
      auto gen_end = std::chrono::system_clock::now();

      //append duration to shared tile history vec
      pthread_mutex_lock(&timerLock);
      tile_hist.push_back((float)std::chrono::duration_cast<std::chrono::microseconds>(gen_end - gen_start).count());
      pthread_mutex_unlock(&timerLock);

      barrier.down();
  }
}

void ConsumerThread::execute(Job &job) {


  vector<bool> new_row;

  int i=job.begin_row;
  for(auto line=curr.begin()+job.begin_row;  line<curr.begin()+job.end_row; line++){
    new_row.clear();
    int j=0;
    for (auto &&curr_cell : (*line)) {
      // Game Logic:
      if(curr_cell) // If piece is alive
      {
        if(neighbors_sum(i,j,curr) == 2 || neighbors_sum(i,j,curr)==3)
        {
          new_row.push_back(true); // If a piece has 2 or 3 neighbors, it'll stay alive
        }else{
          new_row.push_back(false); // Otherwise it'll die
        }
      }

      else // If a piece is dead
      {
        if(neighbors_sum(i,j,curr) == 3)
        {
          new_row.push_back(true); // If a dead piece has 3 neighbors, it revives
        }else{
          new_row.push_back(false); //Otherwise it stays dead
        }
      }

      j++;
    }

    next[i]=new_row;
    i++;
  }

}
