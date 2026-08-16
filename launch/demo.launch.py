from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument(
            'solver_type',
            default_value='mecanum',
            description='Solver type: mecanum or omni'
        ),
        Node(
            package='mecanum_omni',
            executable='mecanum_omni_node',
            name='mecanum_omni_node',
            output='screen',
            parameters=[{
                'solver_type': LaunchConfiguration('solver_type')
            }]
        ),
    ])
