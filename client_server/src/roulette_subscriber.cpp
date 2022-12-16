#include <ros/ros.h>
#include "roulette_service/RouletteGame.h"
#include <ros/console.h>
#include <iostream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "casino_client");
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<roulette_service::RouletteGame> ("casino");
  roulette_service::RouletteGame srv;

  while (ros::ok()){
      ROS_INFO ("WELCOME TO OUR CASINO!");
      ROS_INFO ("\n Please, enter roulette type, you want to play \n [1] Russian roulette \n "
                       "[2] European roulette \n [0] I don't want to play! Just let me leave!");
      std::cin>>  srv.request.roulette_type;
      if ((srv.request.roulette_type < 0) or (srv.request.roulette_type > 2)
        /*or (srv.request.roulette_type.empty)*/) {
          ROS_INFO ("Oops! Seems you haven't chosen roulette type! Pleas, try again.");
          ros::shutdown();
      }
      ROS_INFO ("Enter your bet (1..300 000)");
      std::cin>> srv.request.bet;
      if ((srv.request.bet < 1) or (srv.request.bet > 300000)) {
          ROS_INFO ("Oops! Seems something went wrong with your bet! Pleas, try again.");
          ros::shutdown();
      }

      switch (srv.request.roulette_type){
          case 1: { //Russian roulette
              ROS_INFO ("As Nancy Sinata said \n Bang-Bang...");
              if (client.call(srv)) { // Win
                  if (!srv.response.result) { // -1 <= result <= 0
                      ROS_INFO ("\n ...that awful sound \n Bang-Bang I used to shoot you down \n You won $ %d",
                                srv.response.bank);
                  }
                  else { // Loss
                      ROS_INFO ("\n ...that awful sound \n Bang-Bang you used to shoot me down \n"
                                       "You are Wasted");
                  }
              }
              break;
          }
          case 2: { //European roulette
              ROS_INFO ("\n Please, enter roulette type, you want to play \n [1] I'll bet on number... (1..36) \n "
                        "[2] I'll bet on color... (black/red) \n [3] It would be... (even/odd) \n "
                        "[4] ALL IN ZERO! (0) \n [0] I don't want to play! Just let me leave!");
              std::cin>> srv.request.gamemode;
              if ((srv.request.gamemode < 0) or (srv.request.gamemode > 4)) {
                  ROS_INFO ("Oops! Seems you haven't chosen roulette type! Pleas, try again.");
                  ros::shutdown();
              }

              switch (srv.request.gamemode){
                  case 1: {
                      ROS_INFO ("And your number is...? \n [0] Stop it!");
                      std::cin>> srv.request.value;
                      if (srv.request.value == 0) {
                          break;
                      }
                      if ((srv.request.value < 1) or (srv.request.value > 36)
                        /*or (srv.request.value.empty)*/) {
                          ROS_INFO ("Oops! Seems you have chosen wrong value! Pleas, try again.");
                          ros::shutdown();
                      }
                      break;
                  }
                  case 2: {
                      ROS_INFO ("\n [1] Black \n [2] Red \n [0] Stop it!");
                      std::cin>> srv.request.value;
                      if (srv.request.value == 0) {
                          break;
                      }
                      if ((srv.request.value < 1) or (srv.request.value > 2)
                          /*or (srv.request.value.empty)*/) {
                          ROS_INFO ("Oops! Seems you have chosen wrong value! Pleas, try again.");
                          ros::shutdown();
                      }
                      break;
                  }
                  case 3: {
                      ROS_INFO ("\n [1] Odd \n [2] Even \n [0] Stop it!");
                      std::cin>> srv.request.value;
                      if (srv.request.value == 0) {
                          break;
                      }
                      if ((srv.request.value < 1) or (srv.request.value > 2)
                          /*or (srv.request.value.empty)*/) {
                          ROS_INFO ("Oops! Seems you have chosen wrong value! Pleas, try again.");
                          ros::shutdown();
                      }
                      break;
                  }
                  case 4: {
                      srv.request.value = 0;
                      break;
                  }
                  case 0: {
                      break;
                  }
              }
              if (client.call(srv)) { // 0 <= result <= 1
                  if ((!srv.request.gamemode) or (!srv.request.roulette_type)) {
                      break;
                  }
                  if (!srv.response.result){
                      ROS_INFO ("Sorry to say, but You've lost $ %d \n" /*Your bank now is"*/, srv.response.bank);
                  }
                  else {
                      ROS_INFO ("Wow! You just won $ %d \n" /*Your bank now is"*/, srv.response.bank);
                  }
              }
              else {
                  ROS_INFO ("Failed to call service");
              }
              break;
          }
          case 0: {
              break;
          }
      }
      return 1;
  }


  ros::spin();
  return 0;
}

