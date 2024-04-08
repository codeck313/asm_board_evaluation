# asm_board_evaluation
## Setup

Assuming ROS Melodic has been installed.
### Setup for Hector SLAM
1. Clone the repo.
   ```sh
   $ git clone https://github.com/codeck313/asm_board_evaluation.git
   ```

2. Catkin build the workspace and source it.
	 ```sh
	 $ catkin build -DCMAKE_BUILD_TYPE=Release
	 $ source devel/setup.bash
	```
3. Starting the RPLidar
	 ```sh
	 $ roslaunch rplidar_ros rplidar_a2m12.launch
	```

4. Running Hector SLAM
	 ```sh
	 $ roslaunch hector_mapping mapping_default.launch
	```
5. Controlling robot using teleop
	 ```sh
	 $ rosrun teleop_twist_keyboard teleop_twist_keyboard.py
	```
One can see the demo of HectorSLAM running on Volta robot [here](https://indianinstituteofscience-my.sharepoint.com/:v:/g/personal/sakshams_iisc_ac_in/EUXoaY-nNm1ArOLA7YDDI8sBmZO-PVMdEl6xRYOVdvo7Qg?e=rET3J5)
### Setup for Obstacle Avoidance
Source the above workspace and run the following launch file. One can edit the target location in the launch file as per need.

```sh
$ rosrun multi_controller bug2.launch
```
One can see the demo of obstacle avoidance running on Volta robot [here](https://indianinstituteofscience-my.sharepoint.com/:v:/g/personal/sakshams_iisc_ac_in/EU_QcgNcvNlEiMfHXlp6UYwBh3YHEQOFhN_MIHcEh_vj5g?e=Sd9PzT)
### Accessing GPS Data
1. Make sure nvgetty service is running
	```sh
	$ sudo  systemctl  stop  nvgetty
	$ sudo  systemctl  start  nvgetty
	```

2. Access the GPS data using the following command:
	```sh
	$ sudo  cat  /dev/ttyTHS0
	```
 You should see output similar to following screenshot
![Screenshot (98)](https://github.com/codeck313/asm_board_evaluation/assets/23121752/63c86ef8-8d52-4cd5-95fe-256034008749)


