# play_rosbag

Данный пакет предназначен для воспроизведения .bag файлов с рабочим move_base, amcl, map_server

Активный граф во время работы выглядит так:

<<<<<<< HEAD
![graph](image/rosgraph.jpg)
=======
![graph](image/rosgraph.png)
>>>>>>> ff611fc58a3ac390926f91559091ebcfbc8e115c

Для того чтобы воспользоваться пакетом нужно:

- в папку /move_base/maps поместить карту .yaml .png
- в start.launch указать название карты
- в start.launch указать путь с названием .bag файла

## Запуск

Для запуска воспроизведения данных необходимо запустить:

`roslaunch rosbag_play start.launch`

Запуститься воспроизведение данных и откроется RViz
