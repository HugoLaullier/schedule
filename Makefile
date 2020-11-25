all:
	easena ez/schedule.ez

compile:
	cd ez && make

run:
	cd ez && ./schedule

clean:
	rm bin/exe