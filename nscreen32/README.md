# setup

> cd nscreen32  
> rm -rf build  
> idf.py set-target esp32  
> idf.py menuconfig  
 
Check in the setting match with the following:  

![setup](../docs/nscreen_lcd_setup.png)  

> idf.py build  
> idf.py -p /dev/whatever_driver flash monitor  
Note: you need to press/hold the download button while issuing the above command
