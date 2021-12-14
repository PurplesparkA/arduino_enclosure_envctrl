# Arduino 3d printer enclosure environmental control

I wanted to get some space on my desk, and some quiet while 3d printing, so I decided to make an enclosure for my Ender 3 V2.
However, considering its dimensions, I didn't go for the classic Ikea Lack table. And I'm not good at building wood things, so I went for the following:

![Ikea Smastad/Uppfora](https://www.ikea.com/ca/en/images/products/smastad-uppfoera-cabinet-white-gray-with-1-shelf__0922392_pe788153_s5.jpg?f=g)

It's a convenient cabinet with dimensions that suit my needs. I got 2 of those, but the second is for my SLA printer, not covered in this project.

The idea is to control the temperature inside this cabinet (and, in the near future, add some soundproofing to have even less noise).

In order to do that, I decided to go with a bit of electronics with an Arduino as the brains of it all.

# Diagram
First, let's do a diagram of what I want to do:

![Diagram](https://github.com/PurplesparkA/arduino_enclosure_envctrl/blob/master/other_files/enclosure_temp_control_electronics.png)

I first did some testing with an Arduino Uno, but, for the final version, I went with an Arduino Nano, the rest was already acquired.

# Bill of material

Here is all that I'm using in this project:

- [Ikea Smastad/Uppfora](https://www.ikea.com/ca/en/p/smastad-uppfoera-cabinet-white-gray-with-1-shelf-s69389791/)
- [Elegoo Arduino Nano](https://www.amazon.ca/gp/product/B071NMD14Y/ref=ppx_yo_dt_b_asin_title_o08_s01?ie=UTF8&psc=1)
- [Adapter Shield for Arduino Nano](https://www.amazon.ca/gp/product/B07YTZSR72/ref=ppx_yo_dt_b_asin_title_o08_s00?ie=UTF8&psc=1)
- [OLED Display](https://www.amazon.ca/gp/product/B0751LFCZT/ref=ppx_yo_dt_b_asin_title_o00_s01?ie=UTF8&psc=1)
- [DS1820B Temperature sensor](https://www.amazon.ca/gp/product/B012C597T0/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1)
- [Relays for the fan control](https://www.amazon.ca/gp/product/B07DN8DTRW/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&psc=1)
- [Heater fan](https://www.amazon.ca/gp/product/B07YPNYP98/ref=ppx_yo_dt_b_asin_title_o08_s00?ie=UTF8&psc=1)
- [2 Noctua 12V fans](https://www.amazon.ca/gp/product/B07C5VG64V/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1)
- [12V Power supply](https://www.amazon.ca/gp/product/B0776R4SPT/ref=ppx_yo_dt_b_asin_title_o01_s01?ie=UTF8&psc=1)

A soldering iron and solder pewter, and some cabling are also necessary, I've got those:
- [Soldering Iron](https://www.amazon.ca/gp/product/B08LYVSNNM/ref=ppx_yo_dt_b_asin_title_o04_s01?ie=UTF8&psc=1)

# Developing the code of the application

I used an Arduino Uno to do the first tests of this setup, and the code here is the result of those tests. I tested it and it works as I want it to. The code is probably not perfect, as I'm just an amateur at coding, but it does what I need it to.

# Case for the project

I included the source Fusion 360 file for the case I designed for this project, this is not the definitive version, I need to add a few things.
I also included the STL files generated from this Fusion 360 design, for those who would want to give it a go.
The whole dev process was done with VSCode with the Platform.io plugin, and it really works great. I prefer VSCode to Arduino IDE, because Intellisense and git integration.

# Future development

~~1. Change the case design:~~
- ~~Add holes for screwing the display to the top of the case.~~
- ~~Add the possibility to screw the top part to the botton one (for now they're just press fit).~~

2. Depending on how the air circulation is working, change the heating fan+heating unit with a second intake fan and exhaust fan (I planned on putting the cabinet in a cold room I have at my place, but it will stay close to my desk, so no need for heating in this configuration).

3. Use a WiFi enabled board in order to get some IoT capabilities, like, for example, disabling the fans logic when the printer is not in use. Also connect OctoPrint to MQTT and add logic to automatically enable the fans control when a print is starting, then disabling the fans when the print is finished, and also be able to set the maximum temperature, depending on the filament used (it is fixed, for now, for printing PLA).

4. Change the display for a larger one, maybe a Nextion display to have some direct control through the touch screen.
