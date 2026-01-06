#nova - carter - pointcloud - stats
rclcpp ros2 system to analyse pointcloud and odom stats from a nova carter
    rosbag,
    recorded from isaac sim

```bash
#terminal 1
                source /
            opt / ros / humble / setup.zsh cd ~ / ros2_ws source install /
            setup.zsh ros2 bag play ~ / ros2_ws / bags /
            carter_cloud_odom_33s-- loop
```

```bash
#terminal 2
                source /
            opt / ros / humble / setup.zsh cd ~ / ros2_ws source install /
            setup.zsh colcon build-- packages -
        select carter_bag_stats ros2 bag play ~ / ros2_ws / bags /
            carter_cloud_odom_33s-- loop
```