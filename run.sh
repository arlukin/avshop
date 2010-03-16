#!/bin/sh
./build.sh
cd approot
./bin/avshop \
	--docroot ./var/www \
	--config ./etc/wt_config.xml \
	--pid-file /tmp/avShop.pid \
	--http-address 0.0.0.0 --http-port 8080
