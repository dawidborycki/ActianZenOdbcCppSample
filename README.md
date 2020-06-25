# Info
 This repository shows how to use ODBC to programatically access Actian Zen database using C++

# Instructions
Here are the steps you need to take to run the sample

## Install Actian Zen
```sudo apt-get install unixodbc
sudo tar -C /usr/local -xvf Zen-Edge-Community-linux-armhf-14.10.035.000.tar.gz
cd /usr/local/actianzen/etc 
sudo ./preinstall.hs
sudo ./postinstall.sh
```

## Install unixodbc-dev
``` 
sudo apt-get install unixodbc-dev
```

## Build the app
```
g++ main.cpp -o actianSample -lodbc
```

## Run the app
```./actianSample
