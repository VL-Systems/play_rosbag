# play_rosbag

Данный пакет предназначен для воспроизведения .bag файлов с рабочим move_base, amcl, map_server

Активный граф во время работы выглядит так:


![graph](https://github.com/VL-Systems/play_rosbag/blob/main/%20image/rosgraph.jpg)


Для того чтобы воспользоваться пакетом нужно:

- в папку /move_base/maps поместить карту .yaml .png
- в start.launch указать название карты
- в start.launch указать путь с названием .bag файла

## Запуск

Для запуска воспроизведения данных необходимо запустить:

`roslaunch rosbag_play start.launch`

Запуститься воспроизведение данных и откроется RViz
