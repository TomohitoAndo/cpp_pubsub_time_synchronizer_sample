## Build

```
cd cpp_pubsub_time_synchronizer_sample
colcon build
```

## Run

Terminal1
```
$ ros2 run cpp_pubsub_message_filter talker 
[INFO 1675161214.212253530] [minimal_publisher]: Publishing: '0'
[INFO 1675161214.712181622] [minimal_publisher]: Publishing: '1'
[INFO 1675161215.212281301] [minimal_publisher]: Publishing: '2'
[INFO 1675161215.712217542] [minimal_publisher]: Publishing: '3'
[INFO 1675161216.212275675] [minimal_publisher]: Publishing: '4'
[INFO 1675161216.712264705] [minimal_publisher]: Publishing: '5'
[INFO 1675161217.212231885] [minimal_publisher]: Publishing: '6'
```

Terminal2
```
$ ros2 run cpp_pubsub_message_filter listener 
[INFO 1675161214.212566160] [minimal_subscriber]: I heard: '0'
[INFO 1675161214.212698842] [minimal_subscriber]: Publishing: '0'
[INFO 1675161214.712336919] [minimal_subscriber]: I heard: '1'
[INFO 1675161214.712370024] [minimal_subscriber]: Publishing: '2'
[INFO 1675161215.212480763] [minimal_subscriber]: I heard: '2'
[INFO 1675161215.212531988] [minimal_subscriber]: Publishing: '4'
[INFO 1675161215.712364690] [minimal_subscriber]: I heard: '3'
[INFO 1675161215.712393592] [minimal_subscriber]: Publishing: '6'
[INFO 1675161216.212735659] [minimal_subscriber]: I heard: '4'
[INFO 1675161216.212855390] [minimal_subscriber]: Publishing: '8'
```

Terminal3
```
$ ros2 run cpp_pubsub_message_filter sync_listener 
[INFO 1675161223.712448553] [minimal_subscriber]: topic1: '19'
[INFO 1675161223.712543354] [minimal_subscriber]: topic2: '38'
[INFO 1675161223.712561817] [minimal_subscriber]: -----------
[INFO 1675161224.213206253] [minimal_subscriber]: topic1: '20'
[INFO 1675161224.213327486] [minimal_subscriber]: topic2: '40'
[INFO 1675161224.213370322] [minimal_subscriber]: -----------
[INFO 1675161224.713037144] [minimal_subscriber]: topic1: '21'
[INFO 1675161224.713151485] [minimal_subscriber]: topic2: '42'
[INFO 1675161224.713193879] [minimal_subscriber]: -----------
[INFO 1675161225.213188221] [minimal_subscriber]: topic1: '22'
[INFO 1675161225.213313536] [minimal_subscriber]: topic2: '44'
[INFO 1675161225.213356906] [minimal_subscriber]: -----------
[INFO 1675161225.712429692] [minimal_subscriber]: topic1: '23'
[INFO 1675161225.712460016] [minimal_subscriber]: topic2: '46'
[INFO 1675161225.712467720] [minimal_subscriber]: -----------
```