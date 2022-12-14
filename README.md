# Spooky Labyrinth

## Трейлер

https://youtu.be/9opa1aY599E


## Сюжет и геймплей

Джон Крамер, более известный как Пила, похитил двух мужчин и устроил для них игру на выживание, проверку насколько они мужчины, суть которой выбраться из сложнейшего лабиринта не прикасаясь к розовым(не мужским) стенам.

## Кадры из игры

Ниже представлены реалистичные, то есть похожие на реальную жизнь, кадры из игры Spooky Labyrinth:
![photo_5240283499452286661_y](https://user-images.githubusercontent.com/91669954/207206206-af497311-0949-428d-8060-764c9c50f94d.jpg)
![photo_5240283499452286664_y](https://user-images.githubusercontent.com/91669954/207206214-33d54dc1-0f56-4fc2-9ad6-0bea5ba12610.jpg)
![photo_5240283499452286662_y](https://user-images.githubusercontent.com/91669954/207206223-6bdc5c20-3fc5-44ec-9d30-4b6f1747cb7c.jpg)
![photo_5240283499452286663_y](https://user-images.githubusercontent.com/91669954/207206230-0e7f1437-13ce-4a74-a31b-21e893380716.jpg)



## Программная часть игры

В нашем проекте мы использовали библиотеку SFML, позволяющую реализовать реалистичную графику в игре:
1) Сначала мы создали карту нашего лабиринта, которая содержала множество стен, нарисованных с помощью прямоугольников
![photo_5240283499452286665_x (1)](https://user-images.githubusercontent.com/91669954/207206316-ca0ce860-fbd2-4743-afef-2571bd6a9857.jpg)

2) Изначально игрок создается на входе в лабиринт. Его положение в этот и последующие моменты времени определяется с помощью координат x,y.
3) В каждый момент времени, помимо координат игрока, мы определяем направление, в котором он смотрит. Угол обзора каждого игрока равен 180 градусам.
4) Затем для каждого игрока в пределах его угла обзора мы посылаем множество лучей, которые позволяют определить расстояние до стен.
5) Для каждого луча мы определяем ближайшую стену, с участком которой он пересекается и сохраняем расстояние до него.
6) Для каждого полученного расстояния мы строим вертикальный прямоугольник, высота которого обратно пропорциональна расстоянию до него.
7) Для отображения других пользователей, попадающих в угол обзора, аналогично определяем расстояние и отображаем их при помощи вертикальных прямоугольников.

Также благодаря SFML в нашем проекте реализовано перемещение игроков:
Программа считывает нажатия клавиш Вверх, Вниз, Вправо, Влево, и обрабатывает их следующим образом:
	1) При нажатии клавиш Вправо, Влево пользователь разворачивается, меняя направление обзора.
	2) При нажатии клавиш Вверх, Вниз пользователь сдвигается в соответствии с направлением обзора.
	
## Мультиплеер

Для реализации мультиплеера была реализована клиент-серверная архитектура с использованием TCP сокета.
При каждом изменении расположения пользователь отправляет на сервер информацию о новом местоположении, а сервер рассылает её остальным пользователям.
Таким образом, каждый пользователь с помощью полученной информации может отображать других игроков.
