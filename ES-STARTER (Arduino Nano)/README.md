## [ES-STARTER](http://iashchuk.com) part of ES-UNLOCKER - Okai ES200B Scooter (Arduino Nano Version)

#### How to connect an Arduino Nano to the ES-200B
To get the ES-200b working you need to cut the exposed wires from the GPS tracker. Warning these wires have different color codes depending if you are going to cut it before or after the waterproof plug. For my scooter I cut it on the GPS tracker side. On the other side the Black and Red wires are still the same. the BTN wire is yellow and the TX is blue I believe.

The Black is ground (GND) The red wire is the VIN 42 volt from the battery. The Blue is called the BTN and this is just to turn on the motor controller. It requires a constant 3.3v. The yellow is TX and will need to be connected to the RX of the Nano. The green is the RX line and is not required but I hooked it up anyways just in case you want some input from the motor controller.

So the first step is to hook up a Buck convertor to the Red (VIN) and black wires (GND) this will step down the relatively high voltage from the battery to something the Arduino can use. Because the battery is 42v you will need a special Buck Convertor that can handle all that voltage. I used an LM2596 based convertor board from amazon. A XL7015 type break out might be a better choice. Make sure to adjust the voltage below 5v.  Now connect the Arduino ground to the buck convertor and the buck's + to the Arduino's VIN

Next connect the yellow TX of the tracker to the Arduino's RX pin. Now connect the Blue (BTN) wire to pin number 5 on the arduino or more simply to the Arduino 3.3v out. Last upload the included arduino .ino file to the nano and away you go. 

If you cant get a hold of buck convertor right away its OK to connect the arduino to a USB battery. That will do the trick.
#### Use your scooter as you want!

## <a name="pictures">Pictures:</a>

IN PROGRESS... Give me some time for graphic details of wiring [ES-STARTER](http://kyivapp.com)

## <a name="dickheads">Для полиглотов:</a>

#### ЦВЕТА ПРОВОДОВ:
ЧЕРНЫЙ - GND (земля).

КРАСНЫЙ - VIN (питание) +42v.

СИНИЙ (м.б. ЖЕЛТЫЙ) - Кнопка Пуск, надо подключить на контакт +3.3v.

ЖЕЛТЫЙ (м.б. СИНИЙ) - TX порт (получатель сигнала), надо подключить к порту RX (источник сигнала) на Arduino Nano.

ЗЕЛЕНЫЙ - RX порт, подключить не обязательно, через него можно получать данные с контроллера.

#### ПОДКЛЮЧАТЬ ПО ПОРЯДКУ:
Желтый к пину RX на Arduino Nano. Синий к пину D5 на Arduino Nano. Загружаем на плату .ino файл и радуемся!

## <a name="license">License:</a>

```ES-STARTER``` is released under the MIT license. Check the ```LICENSE``` file for details.  
Copyright © 2021-2022 <a href="http://iashchuk.com">Alexander Iashchuk</a>.

## <a name="thanks">Thanks to:</a>

Don't forget to check the good jobe done by - [Mr. Spriggs on HACKADAY.IO](https://hackaday.io/project/168667-es-200-electric-scooter-unlocker).

## <a name="contact">Contact:</a>

You can read, follow or drop me a line on my personal Twitter account - [@iAlexander13](https://twitter.com/iAlexander13).  
If you find any issues on the project, you can open a ticket.  
Pull requests are also welcome!

[![iAlexander - Нотатки громадянина України](https://raw.githubusercontent.com/iAlexander/Homepok/master/Footer.jpg)](https://twitter.com/iAlexander13)
