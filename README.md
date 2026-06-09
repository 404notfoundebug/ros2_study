# ROS2学习代码仓库

本仓库用于记录我在学习ROS2过程中的代码实践，主要内容包括ROS2节点通信、话题发布与订阅、服务通信、参数配置、TF坐标变换、Gazebo仿真、RViz2可视化以及基于Nav2的路点导航功能。

## 项目简介

本项目基于ROS2Humble开发，主要围绕移动机器人基础功能展开学习与实践。通过编写C++和Python节点，完成机器人控制、服务调用、参数调整、仿真环境搭建和自主导航等功能。

该仓库不是一个完整的商业级机器人系统，而是一个ROS2学习过程记录，适合用于展示个人学习成果、代码实践和机器人开发基础能力。

## 技术栈

* Ubuntu22.04
* ROS2Humble
* C++
* Python
* Gazebo
* RViz2
* Nav2
* Xacro/URDF
* colcon
* Git/GitHub

## 主要学习内容

### 1.ROS2基础通信

实现了ROS2中常见的通信机制，包括：

* 节点创建
* 话题发布与订阅
* 服务端与客户端通信
* 参数声明、读取与动态修改
* 定时器回调函数

相关内容主要用于理解ROS2中节点之间的数据交互方式。

### 2.turtlesim控制实验

基于`turtlesim`完成了小乌龟控制实验，包括：

* 发布速度指令控制小乌龟运动
* 订阅位姿信息
* 根据目标点计算距离和角度
* 实现简单的自动巡逻逻辑

### 3.自定义服务实验

自定义`Patrol.srv`服务文件，通过客户端发送目标坐标，服务端接收目标点后控制机器人运动。

该部分主要用于学习ROS2中服务通信的基本流程，包括接口定义、服务注册、客户端请求和回调处理。

### 4.TF坐标变换学习

学习并使用`tf2`完成坐标系监听与转换，理解机器人中常见的坐标关系，例如：

* `map`
* `odom`
* `base_footprint`
* `base_link`

该部分主要用于理解机器人定位、导航中坐标变换的作用。

### 5.URDF/Xacro机器人建模

使用URDF和Xacro描述机器人模型，包括：

* 机器人底盘
* 左右轮
* 万向轮
* IMU
* 激光雷达
* 摄像头
* 机器人惯性参数

通过模块化的Xacro文件组织机器人结构，提高模型复用性和可维护性。

### 6.Gazebo仿真

在Gazebo中加载机器人模型和自定义仿真世界，实现机器人模型的显示与仿真运行。

主要内容包括：

* 加载自定义world文件
* 使用`robot_state_publisher`发布机器人状态
* 使用`spawn_entity.py`将机器人生成到Gazebo中
* 配置差速驱动插件
* 配置`ros2_control`控制器

### 7.RViz2可视化

使用RViz2查看机器人模型、坐标系、雷达数据和地图信息，用于辅助调试机器人状态。

主要观察内容：

* RobotModel
* TF
* LaserScan
* Map
* Odometry
* Navigation路径

### 8.Nav2路点导航

基于Nav2实现机器人在地图中的多目标点导航，使用Python调用`nav2_simple_commander`完成路点任务。

主要功能包括：

* 初始化导航器
* 设置初始位姿
* 等待Nav2激活
* 设置多个目标点
* 控制机器人依次导航到指定位置

## 项目目录说明

```bash
ros2_study/
├── chapt3/
│   └── topic_ws/              # ROS2话题通信相关实验
├── chapt4/
│   └── chapt4_ws/             # ROS2服务通信、参数、控制实验
├── chapt6/
│   └── chapt6_ws/             # 机器人建模、Gazebo仿真相关实验
├── chapt7/
│   └── chapt7_ws/             # Nav2导航与路点巡逻实验
└── README.md
```

## 运行环境

推荐环境如下：

```bash
Ubuntu 22.04
ROS2 Humble
Gazebo Classic
Nav2
colcon
```

安装ROS2Humble后，需要先加载环境变量：

```bash
source /opt/ros/humble/setup.bash
```

进入对应工作空间后编译：

```bash
colcon build
```

编译完成后加载当前工作空间环境：

```bash
source install/setup.bash
```

## 常用运行命令

### 运行turtlesim

```bash
ros2 run turtlesim turtlesim_node
```

### 运行自定义节点

```bash
ros2 run demo_cpp_topic turtle_circle
```

### 运行服务端

```bash
ros2 run demo_cpp_service turtle_control
```

### 运行客户端

```bash
ros2 run demo_cpp_service patrol_client
```

### 启动Gazebo仿真

```bash
ros2 launch fishbot_description gazebo_sim.launch.py
```

### 启动RViz2显示机器人模型

```bash
ros2 launch fishbot_description display_robot.launch.py
```

### 运行Nav2路点导航节点

```bash
ros2 run autopartol_robot partol_node
```

## 学习收获

通过本项目的学习，我掌握了ROS2机器人开发中的基础流程，包括节点通信、服务调用、参数配置、坐标变换、机器人建模、仿真环境搭建和导航功能调用。

同时，我也熟悉了ROS2项目的基本开发流程，包括：

* 创建功能包
* 编写节点代码
* 配置`package.xml`
* 配置`CMakeLists.txt`或`setup.py`
* 使用`colcon build`编译
* 使用`source install/setup.bash`加载环境
* 使用launch文件统一启动多个节点

## 遇到的问题与解决

学习过程中遇到过一些常见问题，例如：

* 功能包名称拼写错误导致找不到包
* Xacro文件路径错误导致模型加载失败
* Gazebo中机器人模型无法正常生成
* `ros2_control`控制器加载失败
* 虚拟机网络异常影响依赖安装
* GitHub代码同步不完整
* Nav2启动后坐标系或地图未正确加载

这些问题帮助我进一步理解了ROS2项目结构、环境变量、依赖配置和仿真调试流程。

## 后续计划

后续计划继续完善以下内容：

* 优化机器人模型结构
* 完善Gazebo仿真环境
* 继续学习Nav2导航参数配置
* 增加自动巡逻任务逻辑
* 尝试结合真实机器人或AGV平台进行测试
* 整理更多学习笔记和实验记录

## 说明

本仓库主要用于个人ROS2学习记录，代码以学习和实验为主，部分功能仍在持续完善中。
