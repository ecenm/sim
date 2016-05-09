all:	clean compex run extract 

compex:
	#g++ packet.cpp queue.cpp node.cpp factory.cpp event.cpp main.cpp -lrt -o main
	g++ -g3 -std=c++0x *.cpp -lrt -o main

run:
	#./main 
	./main 1 config.txt >> log.txt 

extract:
	python extract_log.py 	
	cp results/queue_1.log dummy/64/
	cp results/queue_0.log dummy/64/
	cp results/event_1.log dummy/64/
	cd dummy/64/ && cat event_1.log | grep "^[sa|sd]" | while read l; do i=`echo $$l |awk '{print $$2}'`; echo $$l >> $${i}.log; done
	cd dummy/64/ && sh run.sh

# cat event_1.log | grep "^[a|d]" | while read l; do i=`echo $l |awk '{print $2}'`; echo $l >> ${i}.log; done

draw:
	gnuplot script.plt
	evince plot.ps

rclean:
	rm -f *_es.jpg *_eventsim.txt

clean:
	rm -f main file.txt log.txt *.ps *.jpg log.txt output
	rm -f *.o
	rm -rf results
	cd dummy/64/ && rm -f *.jpg *.log

