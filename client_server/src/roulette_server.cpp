#include "ros/ros.h"
#include "stdio.h"
#include "roulette_service/RouletteGame.h"
#include <random>

//int enroll = 1000; //enroll bank
int actual_gen_num = 0; //Debug value. But it may be interesting to see the actual value of random num

bool casino (roulette_service::RouletteGame::Request &req,
                   roulette_service::RouletteGame::Response &res) {

    switch (req.roulette_type) {
        case 1: { //Russian roulette
            int gen_num = rand() % 6;
            if (gen_num > 0) {
                res.result = -1; // Well... Minus one
                //  ROS_INFO("it's Russia");
                res.bank = -1;
            } else {
                res.result = 0;
                res.bank = 130 * req.bet;
            }
            break;
        }
        case 2: {//European roulette
            int gen_num = rand() % 37;
            actual_gen_num = gen_num; // Debug value
            switch (req.gamemode) {
                case 1: //number-play
                case 4: //All-in-ZERO!
                    res.bank = 37 * req.bet;
                    if (req.value == gen_num) {
                        res.result = 1;
                    } else {
                        res.result = 0;
                    }
                    break;
                case 2: //color-play. Probability is the same. Further realization is possible but isn't needed
                    res.bank = req.bet;
                    if (gen_num > 17) {
                        res.result = 1;
                    } else {
                        res.result = 0;
                    }
                case 3: //even-odd-play
                res.bank = req.bet;
                    if (gen_num % 2 == req.value % 2) {
                        res.result = 1;
                    } else {
                        res.result = 0;
                    }
                    ROS_INFO ("res.bank = %d", res.bank);
                    break;
                case 0:{
                    break;
                }

        }

            ROS_INFO("Request: type = %d, gamemode = %d, value = %d, bet = %d", req.roulette_type,
                     req.gamemode, req.value, req.bet);
            ROS_INFO("Send back response: bank_value [%d], result [%d], actual gen_num = [%d]",
                     res.bank, res.result, actual_gen_num);
            return true;
        }
        case 0: {
            break;
        }
    }
}

int main (int argc, char **argv)
{
    ros::init(argc, argv, "casino_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService ("casino", casino);
    ROS_INFO ("Casino is ready");
    ros::spin();

    return 0;
}
