#include <rclcpp/rclcpp.hpp>
#include <chapt4_interfaces/srv/patrol.hpp>
#include <cmath>
#include <chrono>
#include <ctime> 
using Patrol = chapt4_interfaces::srv::Patrol;
using namespace std::chrono_literals;

class PatrolClient : public rclcpp::Node
{
    private:
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Client<Patrol>::SharedPtr patrol_client_;

    public:
    PatrolClient() : rclcpp::Node("turtle_controler")
    {
        srand(time(NULL));//初始化随机数种子
        patrol_client_ = this->create_client<Patrol>("patrol");
        timer_ = this->create_wall_timer(10s,[&]()->void
    {
        //1.检测服务端是否上线
        while(!this->patrol_client_->wait_for_service(1s))
        {
            if(!rclcpp::ok())
            {
                RCLCPP_ERROR(this->get_logger(),"等待服务过程中，rclcpp挂了，我退下了");
                return;
            }
            RCLCPP_INFO(this->get_logger(),"等待服务上线中....");
        }
        //2.构建请求对象
        auto request = std::make_shared<Patrol::Request>();
        request->target_x = rand() % 15;
        request->target_y = rand() % 15;
        RCLCPP_INFO(this->get_logger(),"准备好目标点%f,%f",request->target_x,request->target_y);
        //3.发送请求
        this->patrol_client_->async_send_request(request,[&](rclcpp::Client<Patrol>::SharedFuture result_future)->void{
            auto response = result_future.get();
            if(response->result==Patrol::Response::SUCCESS)
            {
                RCLCPP_INFO(this->get_logger(),"请求巡逻目标点成功");
            }
            if(response->result==Patrol::Response::FAIL)
            {
                RCLCPP_INFO(this->get_logger(),"请求巡逻目标点失败");
            }
        });
    });
    }
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto controller = std::make_shared<PatrolClient>();
    rclcpp::spin(controller);
    rclcpp::shutdown();
    return 0;
}
