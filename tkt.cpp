#include <bits/stdc++.h>
#define N 8
using namespace std;

int move_cx[] = {1, 1, 2, 2, -1, -1, -2, -2};
int move_cy[] = {2, -2, 1, -1, 2, -2, 1, -1};

class MyBacktracking{
  public:
    int x;
    int y;
    bool closed;

    MyBacktracking(bool closed = true){
      this->x = 0;
      this->y = 0;
      this->closed = closed;
    }

    bool is_valid_move(int x, int y){
      if ((x >= 0 && y >= 0) && (x < N && y < N)){
        return true;
      }
      return false;
    }

    bool is_empty(int out[], int x, int y){
      if ((this->is_valid_move(x, y)) && (out[y * N + x] < 0)){
        return true;
      }
      return false;
    }

    int getcount(int out[], int x, int y){
      int i, count = 0;
      for (i = 0; i < N; ++i){
        if (this->is_empty(out, (x + move_cx[i]), (y + move_cy[i]))){
          count++;
        }
      }
      return count;
    }

    bool move_process(int out[]){
      int start, count, i, flag = -1, c, min = (N + 1), nx, ny;
      start = rand() % N;
      for (count = 0; count < N; ++count){
        i = (start + count) % N;
        nx = this->x + move_cx[i];
        ny = this->y + move_cy[i];
        if ((this->is_empty(out, nx, ny))){
          c = this->getcount(out, nx, ny);
          if (c < min){
            flag = i;
            min = c;
          }
        }
      }
      if (min == N + 1){
        return false;
      }
      nx = this->x + move_cx[flag];
      ny = this->y + move_cy[flag];

      out[ny * N + nx] = out[(this->y) * N + (this->x)] + 1;
      this->x = nx;
      this->y = ny;
      return true;
    }

    void print_result(int out[]){
      int i, j;
      for (i = 0; i < N; ++i){
        for (j = 0; j < N; ++j){
          cout << out[j * N + i] << "\t";
        }
        cout << "\n";
      }
    }

    bool neighbour(int start_x, int start_y){
      int i;
      for (i = 0; i < N; ++i){
        if (((this->x + move_cx[i]) == start_x) && ((this->y + move_cy[i]) == start_y)){
          return true;
        }
      }
      return false;
    }

    void set_default(int out[]){
      for (int i = 0; i < N * N; ++i){
        out[i] = -1;
      }
    }

    bool generate(int out[]){
      this->set_default(out);
      int i, sx, sy;

      sx = rand() % N;
      sy = rand() % N;
      this->x = sx;
      this->y = sy;

      out[this->y * N + this->x] = 1;
      for (i = 0; i < (N * N) - 1; ++i){
        if (this->move_process(out) == false){
          return false;
        }
      }
      if (this->neighbour(sx, sy) == false && closed){
        return false;
      } else if (this->neighbour(sx, sy) == true && !closed){
        return false;
      }

      this->print_result(out);
      return true;
    }
  };

int main(){
  srand(time(NULL));
  MyBacktracking obj = MyBacktracking();
  int out[N * N];
  while (!obj.generate(out));

  cout << "\n\n\n";

  MyBacktracking obj2 = MyBacktracking(false);
  while (!obj2.generate(out));
  return 0;
}