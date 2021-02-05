#include <math.h>
#include <uWS/uWS.h>
#include <iostream>
#include <string>
#include "json.hpp"
#include "PID.h"

// for convenience
using nlohmann::json;
using std::string;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
string hasData(string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != string::npos) {
    return "";
  }
  else if (b1 != string::npos && b2 != string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

int main() {
  uWS::Hub h;

  PID pid_s, pid_t;
  //pid_s.Init( 0.2, 0.001, 10, true);
  //pid_s.Init( 0.22, 0.0008559, 12.1, true);
  //pid_s.Init( 0.256729, 0.000732565, 14.4476, true);
  //pid_s.Init( 0.30254, 0.000714756,17.4816, true);
  //pid_s.Init( 0.254162, 0.000813147, 17.3227, true);
  //pid_s.Init( 0.244585, 0.000902593,19.6529, true);
  pid_s.Init( 0.242139, 0.00100188,21.2176, false);

  //pid_t.Init( 0.2, 0.001, 10, true);
  //pid_t.Init( 0.22022, 0.00125442,12.1, true);
  //pid_t.Init( 0.290448, 0.00139241,15.1005, true);
  //pid_t.Init( 0.414385, 0.00148095,19.6036, true);
  //pid_t.Init( 0.501406, 0.00207496,25.2766, true);
  //pid_t.Init( 0.661304, 0.00230321,30.5847, true);
  //pid_t.Init( 0.852678, 0.00264347,34.312, true);
  pid_t.Init( 1.11531, 0.0031178,41.5175, false);

  double target_speed = 40;

  h.onMessage([&pid_s, &pid_t, &target_speed](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, 
                     uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2') {
      auto s = hasData(string(data).substr(0, length));

      if (s != "") {
        auto j = json::parse(s);

        string event = j[0].get<string>();

        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte   = std::stod(j[1]["cte"].get<string>());
          double speed = std::stod(j[1]["speed"].get<string>());
          double angle = std::stod(j[1]["steering_angle"].get<string>());
          double steer_value;
          double throttle_value;
          /**
           * TODO: Calculate steering value here, remember the steering value is
           *   [-1, 1].
           * NOTE: Feel free to play around with the throttle and speed.
           *   Maybe use another PID controller to control the speed!
           */
          pid_s.UpdateError(cte);
          steer_value = pid_s.TotalError();

          pid_t.UpdateError((speed - target_speed)/target_speed);
          throttle_value = pid_t.TotalError() + 0.5;

          // DEBUG
          std::cout << "CTE: " << cte << " Steering Value: " << steer_value 
                    << " Speed Value: " << speed  << std::endl;

          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = throttle_value;
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }  // end "telemetry" if
      } else {
        // Manual driving
        string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }  // end websocket message if
  }); // end h.onMessage

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, 
                         char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  
  h.run();
}