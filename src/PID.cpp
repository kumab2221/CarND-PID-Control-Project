#include "PID.h"
#include <iostream>
#include <math.h>
#include <limits>
/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_ , bool twiddle_) {
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;

  p_error     = 0.0;
  i_error     = 0.0;
  d_error     = 0.0;

  twiddle = twiddle_;
  n_eval_steps = 200;
  total_error = 0.0;
  best_error = std::numeric_limits<double>::max();
  dp[0] = Kp*0.1;
  dp[1] = Ki*0.1;
  dp[2] = Kd*0.1;
}

void PID::UpdateError(double cte) {
  // Since d uses the previous value of cte, the order is dip.
  d_error = cte -p_error;
  i_error += cte;
  p_error = cte;

  static int  step         = 0;
  static int  param_index  = 1;
  static bool add_flg      = false;
  static bool subtract_flg = false;
  
  if(!twiddle) return;

  if ((step++ % n_eval_steps) == 0){
      total_error += pow(cte,2);
      if (total_error < best_error) {
          best_error = total_error;
          dp[param_index] *= 1.1;            
          // next parameter
          param_index = (param_index+1) % 3;
          add_flg = subtract_flg = false;
      }
      if (!add_flg && !subtract_flg) {
          AddParameter(param_index, dp[param_index]);
          add_flg = true;
      }
      else if (add_flg && !subtract_flg) {
          AddParameter(param_index, -2 * dp[param_index]);     
          subtract_flg = true;         
      }
      else {
          AddParameter(param_index, dp[param_index]);      
          dp[param_index] *= 0.9;
          param_index = (param_index + 1) % 3;
          add_flg = subtract_flg = false;
      }
      total_error = 0;
      std::cout << Kp << ", " << Ki << "," << Kd << std::endl;        
  }
}

double PID::TotalError() {
  return -(Kp*p_error + Ki*i_error + Kd*d_error);
}

void PID::AddParameter(int index, double amount) {
    switch (index)
    {
    case 0:
      Kp += amount;
      break;
    case 1:
      Ki += amount;
      break;
    case 2:
      Kd += amount;
      break;
    }
}