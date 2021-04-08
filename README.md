### Arduino 3d printer enclosure environmental control

I wanted to get some space on my desk, and some quiet while 3d printing, so I decided to make an enclosure for my Ender 3 V2.
However, considering its dimensions, I didn't go for the classic Ikea Lack table. And I'm not good at building wood things, so I went for the following:

![Ikea Smastad/Uppfora](https://www.ikea.com/ca/en/images/products/smastad-uppfoera-cabinet-white-gray-with-1-shelf__0922392_pe788153_s5.jpg?f=g)

It's a convenient cabinet with dimensions that suit my needs. I got 2 of those, but the second is for my SLA printer, not covered in this project.

The idea is to control the temperature inside this cabinet (and, in the near future, add some soundproofing to have even less noise).

In order to do that, I decided to go with a bit of electronics with an Arduino as the brains of it all.

### Diagram
First, let's do a diagram of what I want to do:

![Diagram](https://github.com/acladenb5/arduino_enclosure_envctrl/blob/master/other_files/enclosure_temp_control_electronics.png)

I first did some testing with an Arduino Uno, but, for the final version, I went with an Arduino Nano, the rest was already acquired.

### Bill of material

Here is all that I'm using in this project:

- [Ikea Smastad/Uppfora](https://www.ikea.com/ca/en/p/smastad-uppfoera-cabinet-white-gray-with-1-shelf-s69389791/)
- [Elegoo Arduino Nano](https://www.amazon.ca/gp/product/B071NMD14Y/ref=ppx_yo_dt_b_asin_title_o08_s01?ie=UTF8&psc=1)
- [Adapter Shield for Arduino Nano](https://www.amazon.ca/gp/product/B07YTZSR72/ref=ppx_yo_dt_b_asin_title_o08_s00?ie=UTF8&psc=1)

*Work in progress*